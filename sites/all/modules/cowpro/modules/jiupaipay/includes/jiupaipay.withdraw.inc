<?php
include_once 'jiupaipay.const.inc';
include_once 'jiupaipay.fun.inc';
include_once ("libs/RSA.php");
include_once ("libs/AES.php");
include_once ("libs/Common.php");

/**
 * 提现
 * $uid 提现用户的uid
 * $amount 提现金额
 * $card 用户指定用于提现的银行卡，是一个'cowpro_fund_bankcard'的entity对象
 * $card 对象实例的属性包括：
 * bankcard_id,uid,type,card_no,cardholder,bank_name,bank_branch,province,city,
 * 详细信息可参考源代码文件cowpro_fund_bankcard.controller.inc
 */
function jiupaipay_withdraw($uid, $amount, $card, $journal_id, $businessSeqNo) {
	$header = jiupaipay_header ( "T00001" );

	$aes = new AES ( JPP_AES_KEY, JPP_AES_IV );
	$post_data = array ();
	$post_data ['businessSeqNo'] = $businessSeqNo;
	$post_data ['businessOrderNo'] = "jbz" . sprintf ( "%'.08d-%d", $journal_id, _jiupaipay_get_microtime () );
	$post_data ['rType'] = "W01";
	$profile = cowpro_customer_profile_load_one_row_with_conditions ( $uid, 'jiupaipay' );
	$profile->jpp_authorize ? $post_data ['entrustflag'] = '01' : $post_data ['entrustflag'] = "00";
	$accountList = array (
			"oderNo" => 11,
			"cebitAccountNo" => "",
			"debitAccountNo" => $profile->jpp_account_number,
			"currency" => "CNY",
			"amount" => $amount,
			"otherAmounttype" => "01",
			"otherAmount" => "",
	);

	$post_data ['deductType'] = "";
	$post_data ['busiBranchNo'] = "";
	$post_data ['payType'] = "00";
	$post_data ['bankAccountNo'] = $card->card_no;
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
	$post_data ["accountList"] [0] ['debitAccountNo'] = $aes->encrypt ( $accountList ['debitAccountNo'] );

	$rsa_private_key = variable_get ( PRIVATE_KEY_ON_JIUPAIPAY );
	$rsa_public_key = variable_get ( PUBLIC_KEY_ON_JIUPAIPAY );
	$rsa = new RSA ( $rsa_private_key, $rsa_public_key );
	$signData = $rsa->sign ( $signInfo );
	$header ['signature'] = $signData;

	$curl_post_data ['reqHeader'] = $header;
	$curl_post_data ['inBody'] = $post_data;

	$result = jiupaipay_curl_api ( $curl_post_data );
	$result = json_decode ( $result, true );
	// var_dump($result);
	// $success = $result['respHeader']['respCode'] == 'P2PS000';
	global $base_url;
	$external_reference_id = $result ['respHeader'] ['serviceSn'];
	if ($result ['respHeader'] ['respCode'] == 'P2PS000') {
		// custodian_cowpro_fund_withdraw_callback($success, $journal_id, $external_reference_id, 'jiupaipay', $result);
		drupal_set_message ( "受理成功" );
		drupal_goto ( $base_url . "/user" );
	} else {
                $success = false;
                custodian_cowpro_fund_withdraw_callback ( $success, $journal_id, $external_reference_id, 'jiupaipay', $result );
		drupal_set_message ( $result ['respHeader'] ['respMsg'], "error" );
		drupal_goto ( $base_url . "/user" );
	}
}

// 提现校验密码回调
function jiupaipay_withdraw_callback($data) {
	global $user;
	if (intval ( $data ['flag'] ) == 1 && _jiupaipay_verify_h5 ( $data )) {
		$result = db_query ( "SELECT data FROM jiupaipay_data_tmp WHERE uid=:uid AND businessSeqNo = :businessSeqNo", array (
				":uid" => $data ['userId'],
				":businessSeqNo" => $data ['businessSeqNo']
		) )->fetchField ();
		$result = unserialize ( $result );
		jiupaipay_withdraw ( $data ['userId'], $result ['amount'], $result ['card'], $result ['journal_id'], $data ['businessSeqNo'] );
	}
}
