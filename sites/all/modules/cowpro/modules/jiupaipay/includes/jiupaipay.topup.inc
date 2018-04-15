<?php
include_once 'jiupaipay.const.inc';
include_once 'jiupaipay.fun.inc';
include_once ("libs/RSA.php");
include_once ("libs/AES.php");
include_once ("libs/Common.php");

/**
 * 充值
 *
 * $rechargeType:
 * <label><input type="radio" name="rechargeTypeVal" value="" checked="checked"> 网银充值</label>
 * <label><input type="radio" name="rechargeTypeVal" value="2"> 快捷支付</label>
 */
function jiupaipay_topup($uid, $amount, $rechargeType, $journal_id, $businessSeqNo) {
	$header = jiupaipay_header ( "T00001" );

	$aes = new AES ( JPP_AES_KEY, JPP_AES_IV );
	$post_data = array ();
	$post_data ['businessSeqNo'] = $businessSeqNo;
	$post_data ['businessOrderNo'] = "jbz" . sprintf ( "%'.08d-%d", $journal_id, _jiupaipay_get_microtime () );

	if( $rechargeType == 1 ) {
      $post_data['rType'] = 'R02';
    }else if( $rechargeType == 2 ){
      $post_data['rType'] = "R01";
    }else if( $rechargeType == 3 ){
      $post_data['rType'] = "R03";
    }

  	 if( $post_data['rType'] != "R03" ) {
       $profile = cowpro_customer_profile_load_one_row_with_conditions ( $uid, 'jiupaipay' );
       $profile_bank_card = cowpro_customer_profile_load_one_row_with_conditions ( $uid, 'bank_card' );
       $profile->jpp_authorize ? $post_data['entrustflag'] = '01' : $post_data['entrustflag'] = "00";
       $cebitAccountNo = $profile->jpp_account_number;
       $card_number = $profile_bank_card->card_no;
     }else{
       $cebitAccountNo = JBZ_PM;
       $post_data['entrustflag'] = "01";
       $card_number = JBZ_BANK_CARD;
     }

	$accountList = array (
			"oderNo" => 11,
			"cebitAccountNo" => $cebitAccountNo,
			"debitAccountNo" => "",
			"currency" => "CNY",
			"amount" => $amount,
			"otherAmounttype" => "01",
			"otherAmount" => "",
	);

	$post_data ['deductType'] = "";
	$post_data ['busiBranchNo'] = "";
	$post_data ['payType'] = "00";
	$post_data ['bankAccountNo'] = $card_number;
	$post_data ['secBankaccNo'] = "";
	$post_data ['note'] = "";
	$post_data ['platformAccountNo'] = "";
	$post_data ['accountList'] [] = $accountList;
	$post_data_tmp = $post_data;

	$oderNo = $post_data_tmp ["accountList"] [0] ['oderNo'];
	unset ( $post_data_tmp ["accountList"] [0] ['oderNo'] );
	foreach ( $post_data_tmp ['accountList'] [0] as $key => $value ) {
		$post_data_tmp [$key . $oderNo] = $value;
	}
	unset ( $post_data_tmp ['accountList'] );
	ksort ( $post_data_tmp );
	ksort ( $post_data );

	$signInfo = $header ['signTime'];
	foreach ( $post_data_tmp as $value ) {
		$signInfo .= "|" . $value;
	}

	$post_data ['bankAccountNo'] = $aes->encrypt ( $post_data ['bankAccountNo'] );
    if( !empty( $accountList['cebitAccountNo'] ) ) {
      $post_data["accountList"][0]['cebitAccountNo'] = $aes->encrypt($accountList['cebitAccountNo']);
    }
    if( !empty( $post_data['secBankaccNo'] ) ) {
      $post_data['secBankaccNo'] = $aes->encrypt($post_data['secBankaccNo']);
    }

	$rsa_private_key = variable_get ( PRIVATE_KEY_ON_JIUPAIPAY );
	$rsa_public_key = variable_get ( PUBLIC_KEY_ON_JIUPAIPAY );
	$rsa = new RSA ( $rsa_private_key, $rsa_public_key );
	$signData = $rsa->sign ( $signInfo );
	$header ['signature'] = $signData;

	$curl_post_data ['reqHeader'] = $header;
	$curl_post_data ['inBody'] = $post_data;

	$result = jiupaipay_curl_api ( $curl_post_data );
	$result = json_decode ( $result, true );
	//var_dump($result);die();
	if ($result ['respHeader'] ['respCode'] == 'P2PS000') {
		$success = TRUE;
        }else{
            $success = FALSE;
        }

	$external_reference_id = $result ['respHeader'] ['serviceSn'];
	if ($post_data ['rType'] != "R02") {
		global $base_url;
		// custodian_cowpro_fund_topup_callback($success, $journal_id, $external_reference_id, 'jiupaipay', $result);
		if ($success) {
			//drupal_set_message ( "已受理" );
			//drupal_goto ( $base_url . "/user" );
            drupal_goto( $base_url . "/cowpro/jiupaipay/topup_feedback/".$journal_id);
		} else {
                        custodian_cowpro_fund_topup_callback ( $success, $journal_id, $external_reference_id, 'jiupaipay', $result );
                        drupal_set_message ( $result ['respHeader'] ['respMsg'], "error" );
                        drupal_goto ( $base_url . "/user" );
		}
	}
	if ($result ['respHeader'] ['respCode'] == 'P2PS000' && $post_data ['rType'] == "R02") {

		// 调用网银列表页面
		$data_pay ['OUT_ID'] = "jbz_pay" . round ( microtime ( true ) * 1000 );
		$data_pay ['TRAN_TIME'] = date ( "YmdHis", time () );
		$data_pay ['GOODS_NAME'] = "充值";
		$data_pay ['COMM_NO'] = "003222";
		$data_pay ['ORDER_NO'] = $post_data ['businessOrderNo'];
		$data_pay ['USER_IP'] = ip_address ();
		global $base_url;
		$data_pay ['BACK_URL'] = $base_url . JPP_BANK_PAY_BACK_URL;
		$data_pay ['FRONT_URL'] = $base_url . JPP_BANK_PAY_FRONT_URL;
		$data_pay ['ACCT_NO'] = "123123213";
		$data_pay ['ACCT_NAME'] = "123123";
		$data_pay ['B_ACCT_NO'] = "01573201000000528";
		$data_pay ['B_ACCT_NAME'] = "湖北余钱宝互联网科技有限公司";
		$data_pay ['SUB_SOURCE_TYPE'] = "jbz";
		$data_pay ['PAY_AMT'] = $amount;
		$data_pay ['GOODS_NAME'] = "充值";

		$data_tmp = $data_pay;
		unset ( $data_tmp ['BACK_URL'] );
		unset ( $data_tmp ['FRONT_URL'] );

		ksort ( $data_tmp );
		$signInfoPay = "";
		foreach ( $data_tmp as $key => $value ) {
			$signInfoPay .= $key . "=" . $value . "&";
		}
		$signInfoPay .= "key=" . PAY_KEY;
		// var_dump($signInfoPay);die();
		$data_pay ['SIGNATURE'] = strtolower ( MD5 ( $signInfoPay ) );

		$html = '
        <form id="formu" name="formu" action="' . JPP_BANK_API_URL . '" method="post">
                <input id="OUT_ID" name="OUT_ID" value="' . $data_pay ['OUT_ID'] . '" type="hidden" />
                <input id="TRAN_TIME" name="TRAN_TIME" value="' . $data_pay ['TRAN_TIME'] . '" type="hidden" />
                <input id="GOODS_NAME" name="GOODS_NAME" value="' . $data_pay ['GOODS_NAME'] . '" type="hidden" />
                <input id="COMM_NO" name="COMM_NO" value="' . $data_pay ['COMM_NO'] . '" type="hidden" />
                <input id="ORDER_NO" name="ORDER_NO" value="' . $data_pay ['ORDER_NO'] . '" type="hidden" />
                <input id="USER_IP" name="USER_IP" value="' . $data_pay ['USER_IP'] . '" type="hidden" />
                <input id="BACK_URL" name="BACK_URL" value="' . $data_pay ['BACK_URL'] . '" type="hidden" />
                <input id="FRONT_URL" name="FRONT_URL" value="' . $data_pay ['FRONT_URL'] . '" type="hidden" />
                <input id="ACCT_NO" name="ACCT_NO" value="' . $data_pay ['ACCT_NO'] . '" type="hidden" />
                <input id="ACCT_NAME" name="ACCT_NAME" value="' . $data_pay ['ACCT_NAME'] . '" type="hidden" />
                <input id="B_ACCT_NO" name="B_ACCT_NO" value="' . $data_pay ['B_ACCT_NO'] . '" type="hidden" />
                <input id="B_ACCT_NAME" name="B_ACCT_NAME" value="' . $data_pay ['B_ACCT_NAME'] . '" type="hidden" />
                <input id="SUB_SOURCE_TYPE" name="SUB_SOURCE_TYPE" value="' . $data_pay ['SUB_SOURCE_TYPE'] . '" type="hidden" />
                <input id="SIGNATURE" name="SIGNATURE" value="' . $data_pay ['SIGNATURE'] . '" type="hidden" />
                <input id="GOODS_NAME" name="GOODS_NAME" value="' . $data_pay ['GOODS_NAME'] . '" type="hidden" />
                <input id="PAY_AMT" name="PAY_AMT" value="' . $data_pay ['PAY_AMT'] . '" type="hidden" />
                <script language="javascript">window.onload=function(){document.formu.submit();}</script>
        </form>';
		echo $html;
		drupal_exit ();
	}
}

// 充值回调
function jiupaipay_topup_callback($data) {
	global $user;
	if (intval ( $data ['flag'] ) == 1 && _jiupaipay_verify_h5 ( $data )) {
		$result = db_query ( "SELECT data FROM jiupaipay_data_tmp WHERE uid=:uid AND businessSeqNo = :businessSeqNo", array (
				":uid" => $data ['userId'],
				":businessSeqNo" => $data ['businessSeqNo']
		) )->fetchField ();
		$result = unserialize ( $result );
		jiupaipay_topup ( $data ['userId'], $result ['amount'], $result ['method'], $result ['journal_id'], $data ['businessSeqNo'] );
	}
}
// 充值银行同步回调
function jiupaipay_topup_bank_return($data) {
	global $base_url;
	drupal_goto ( $base_url . "/user" );
}

// 充值银行异步回调
function jiupaipay_topup_bank_notify($data) {
	$result_string = $data;
	if (! empty ( $result_string )) {
		$result = json_decode ( $result_string, true );
		$success = false;

		if ($result ['inBody'] ['respCode'] == "P2P0000") {
			$success = true;
		}

		$external_reference_id = $result ['inBody'] ['businessSeqNo'];
		$tdata = array ();
		$tdata = db_query ( "SELECT data FROM jiupaipay_data_tmp WHERE businessSeqNo = :businessSeqNo", array (
				":businessSeqNo" => $result ['inBody'] ['oldbusinessSeqNo']
		) )->fetchField ();
		if (! empty ( $tdata )) {
			$tdata = unserialize ( $tdata );
			if (array_key_exists ( "method", $tdata )) {
				custodian_cowpro_fund_topup_callback ( $success, $tdata ['journal_id'], $external_reference_id, 'jiupaipay', $result );
			} else {
				custodian_cowpro_fund_withdraw_callback ( $success, $tdata ['journal_id'], $external_reference_id, 'jiupaipay', $result );
			}
		}

		$header ['version'] = '1.0';
		$header ['merchantCode'] = 'jbz';
		$header ['txnType'] = "R00001";
		$header ['clientSn'] = $header ['txnType'] . "@" . round ( microtime ( true ) * 1000 );
		$header ['clientDate'] = date ( "Ymd", time () );
		$header ['clientTime'] = date ( "His", time () );
		$header ['serviceSn'] = $result ['reqHeader'] ['clientSn'];
		$header ['serviceDate'] = $result ['reqHeader'] ['clientDate'];
		$header ['serviceTime'] = $result ['reqHeader'] ['clientTime'];
		$header ['respCode'] = $result ['inBody'] ['respCode'];
		$header ['respMsg'] = $result ['inBody'] ['respMsg'];
		$header ['signTime'] = round ( microtime ( true ) * 1000 );
		$header ['signature'] = "";

		$result_jpp ['reqHeader'] = $header;
		$result_jpp ['outBody'] = "";
		echo json_encode ( $result_jpp );
	}
}
