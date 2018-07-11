<?php
include_once 'jiupaipay.issuing_publish.inc';
include_once 'jiupaipay.ledger_account.inc';

/**
 * 按期还款
 */
function jiupaipay_repayment($repayment_schedules) {
	$values = array_values ( $repayment_schedules );
	$repayment = array_shift ( $values );
	$payer_uid = $repayment->payer_uid;

	$profile_jiupaipay = cowpro_customer_profile_load_one_row_with_conditions ( $payer_uid, 'jiupaipay' );
	$nid = $repayment->issuing_id;
        $interest = 0;// 利息
        $capital = 0;//本金
	foreach ( $repayment_schedules as $repayment ) {
                if( $repayment->period != $repayment->period_total ) {
                    $interest += $repayment->interest - $repayment->paid_amount;
                }else{
                    $capital += $repayment->capital;
                    $interest += $repayment->interest;
                }
	}
    $pay_total_amount = $interest + $capital;
    $issuing_account = db_query("SELECT issuing_object_accno FROM {jiupaipay_issuing_accno} WHERE nid=$nid")->fetchField();
    //查询标地台账余额
    $issuing_amount = jiupaipay_ledger_account($issuing_account);
    //标的还款金额，等于总金额减去标的台账余额（防止标的还款的时候钱在标的台账上，没下发到投资人台账上）
    $pay_total_amount = $pay_total_amount - $issuing_amount;

	// 请求报文头
	$header = jiupaipay_header ( "T00004" );

	$aes = new AES ( JPP_AES_KEY, JPP_AES_IV );
	$post_data = array ();
	$post_data ['busiTradeType'] = 'T04';
	$post_data ['businessSeqNo'] = "jbz" . date ( "Ymd", time () ) . time () . "@" . $post_data ['busiTradeType'];
	$post_data ['entrustflag'] = "01";
	$issuing_accno = db_query ( "SELECT distinct issuing_object_accno FROM jiupaipay_issuing_accno WHERE nid=:nid", array (
			":nid" => $nid
	) )->fetchField ();
        //先利息后本金， 判断如果是最后一起还款本金加利息，分别上送 本金T04，利息T12
        if( $capital == 0 ) {
            $post_data ['accountList'] [] = array (
                            "oderNo" => 1,
                            "oldbusinessSeqNo" => "",
                            "oldOderNo" => "",
                            "debitAccountNo" => $profile_jiupaipay->jpp_account_number,
                            "cebitAccountNo" => $issuing_accno,
                            "currency" => "CNY",
                            "amount" => $interest,
                            "summaryCode" => "T12",
            );
        }else{
             $post_data ['accountList'] [] = array (
                                                "oderNo" => 1,
                                                "oldbusinessSeqNo" => "",
                                                "oldOderNo" => "",
                                                "debitAccountNo" => $profile_jiupaipay->jpp_account_number,
                                                "cebitAccountNo" => $issuing_accno,
                                                "currency" => "CNY",
                                                "amount" => $interest,
                                                "summaryCode" => "T12",
                                            );
                        
             $post_data ['accountList'] [] = array (
                                                "oderNo" => 2,
                                                "oldbusinessSeqNo" => "",
                                                "oldOderNo" => "",
                                                "debitAccountNo" => $profile_jiupaipay->jpp_account_number,
                                                "cebitAccountNo" => $issuing_accno,
                                                "currency" => "CNY",
                                                "amount" => $capital,
                                                "summaryCode" => "T04",
                                            );
        }

	$post_data ['contractList'] = array ();
	$post_data ['objectId'] = $nid;
	$post_data ['note'] = "";
          
	$post_data_tmp = $post_data;

	foreach ( $post_data_tmp ['accountList'] as $key => $value ) {
                foreach( $value as $_key=>$_value ){
                    if( $_key != 'oderNo' ) {
                        $post_data_tmp [$_key . $value['oderNo']] = $_value;
                    }
                }
	}

	unset ( $post_data_tmp ['accountList'] );
	unset ( $post_data_tmp ['contractList'] );
	ksort ( $post_data_tmp );

	$signInfo = $header ['signTime'];
	foreach ( $post_data_tmp as $value ) {
		$signInfo .= "|" . $value;
	}

        foreach( $post_data ["accountList"] as $key=>$value ){
            $post_data ["accountList"][$key]['debitAccountNo'] = $aes->encrypt ( $value ['debitAccountNo'] );
            $post_data ["accountList"][$key]['cebitAccountNo'] = $aes->encrypt ( $value ['cebitAccountNo'] );
        }

	$post_data ['objectId'] = $aes->encrypt ( $post_data ['objectId'] );
	$rsa_private_key = variable_get ( PRIVATE_KEY_ON_JIUPAIPAY );
	$rsa_public_key = variable_get ( PUBLIC_KEY_ON_JIUPAIPAY );
	$rsa = new RSA ( $rsa_private_key, $rsa_public_key );
	$signData = $rsa->sign ( $signInfo );
	$header ['signature'] = $signData;

	$curl_post_data ['reqHeader'] = $header;
	$curl_post_data ['inBody'] = $post_data;

	$result = jiupaipay_curl_api ( $curl_post_data );
	$result_jpp = array ();
	$result = json_decode ( $result, true );

	if ($result ['respHeader'] ['respCode'] == 'P2P0000') {
		$result_jpp ['success'] = TRUE;
	} else {
		$result_jpp ['success'] = FALSE;
	}

	$data = array();
	$data ['interface_module'] = 'jiupaipay';
	$data ['value'] = $result;

	$result_jpp ['external_reference_id'] = $result ['respHeader'] ['serviceSn'];
	$result_jpp ['data'] = $data;
	$result_jpp ['message'] = $result ['respHeader'] ['respMsg'];
	$result_jpp ['result_code'] = $result ['respHeader'] ['respCode'];
	return jiupaipay_repayment_pay_for ( $repayment_schedules, $result_jpp );
}

/**
 * 出款
 */
function jiupaipay_repayment_pay_for($repayment_schedules, $result_repayment) {
	$values = array_values ( $repayment_schedules );
	$repayment = array_shift ( $values );
	$payer_uid = $repayment->payer_uid;

	$nid = $repayment->issuing_id;

	if ($result_repayment ['success']) {
		$i = 0;
		$post_data = array ();
		$issuing_accno = db_query ( "SELECT distinct issuing_object_accno FROM jiupaipay_issuing_accno WHERE nid=:nid", array (
				":nid" => $nid
		) )->fetchField ();
		foreach ( $repayment_schedules as $repayment ) {
			$pay_amount = $repayment->payable_amount - $repayment->paid_amount;
			$profile_jiupaipay = cowpro_customer_profile_load_one_row_with_conditions ( $repayment->receiver_uid, 'jiupaipay' );
			$accountList = array (
					"amount" => $pay_amount,
					"oderNo" => $i ++,
					"oldbusinessSeqNo" => "",
					"oldOderNo" => "",
					"debitAccountNo" => $issuing_accno,
					"cebitAccountNo" => $profile_jiupaipay->jpp_account_number,
					"currency" => "CNY",
					"summaryCode" => "T05",
			);
			$post_data ['accountList'] [] = $accountList;
		}
		// 请求报文头
		$header = jiupaipay_header ( "T00004" );

		$aes = new AES ( JPP_AES_KEY, JPP_AES_IV );
		$post_data ['busiTradeType'] = 'T05';
		$post_data ['businessSeqNo'] = "jbz" . date ( "Ymd", time () ) . time () . "@" . $post_data ['busiTradeType'];
		$post_data ['entrustflag'] = "01";

		$post_data ['contractList'] = array ();
		$post_data ['objectId'] = $nid;
		$post_data ['note'] = "";

		$post_data_tmp = $post_data;

		foreach ( $post_data_tmp ['accountList'] as $key => $value ) {
			foreach ( $value as $_key => $_value ) {
				if ($_key != "oderNo") {
					$post_data_tmp [$_key . $value ['oderNo']] = $_value;
				}
			}
		}

		unset ( $post_data_tmp ['accountList'] );
		unset ( $post_data_tmp ['contractList'] );
		ksort ( $post_data_tmp );

		$signInfo = $header ['signTime'];
		foreach ( $post_data_tmp as $value ) {
			$signInfo .= "|" . $value;
		}

		foreach ( $post_data ['accountList'] as $key => $value ) {
			$post_data ['accountList'] [$key] ['debitAccountNo'] = $aes->encrypt ( $value ['debitAccountNo'] );
			$post_data ['accountList'] [$key] ['cebitAccountNo'] = $aes->encrypt ( $value ['cebitAccountNo'] );
		}
		$post_data ['objectId'] = $aes->encrypt ( $post_data ['objectId'] );
		$rsa_private_key = variable_get ( PRIVATE_KEY_ON_JIUPAIPAY );
		$rsa_public_key = variable_get ( PUBLIC_KEY_ON_JIUPAIPAY );
		$rsa = new RSA ( $rsa_private_key, $rsa_public_key );
		$signData = $rsa->sign ( $signInfo );
		$header ['signature'] = $signData;

		$curl_post_data ['reqHeader'] = $header;
		$curl_post_data ['inBody'] = $post_data;
		$result = jiupaipay_curl_api ( $curl_post_data );
		$result_jpp = array ();
		$result = json_decode ( $result, true );
		if ($result ['respHeader'] ['respCode'] == 'P2P0000') {
			$result_jpp ['success'] = TRUE;
		} else {
			$result_jpp ['success'] = FALSE;
		}
		$data = array();
		$data ['interface_module'] = 'jiupaipay';
		$data ['value'] = $result;
		$result_jpp ['external_reference_id'] = $result ['respHeader'] ['serviceSn'];
		$result_jpp ['data'] = $data;
		$result_jpp ['message'] = $result ['respHeader'] ['respMsg'];
		$result_jpp ['result_code'] = $result ['respHeader'] ['respCode'];
		return $result_jpp;
	} else {
		return $result_repayment;
	}
}
