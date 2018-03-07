<?php
include_once 'jiupaipay.const.inc';
include_once ("libs/RSA.php");
include_once ("libs/encrypt.php");
include_once ("libs/AES.php");
include_once ("libs/Common.php");

/**
 * 账户余额查询(WS)
 *
 * @param int $uid
 */
function _jiupaipay_cowpro_fund_query_balance($uid) {
	$result = array ();
	$profile = cowpro_customer_profile_load_one_row_with_conditions ( $uid, 'jiupaipay' );
	if ($profile == NULL) {
		$result ['status'] = FALSE;
		$result ['code'] = 'COWPRO-1';
		$result ['msg'] = '没有找到托管账户信息';
		$result ['balance'] = 0;
		$result ['lock'] = 0;
		$result ['account_number'] = '';
		return $result;
	}
	// 请求报文头
	$header ['version'] = '1.0';
	$header ['merchantCode'] = 'jbz';
	$header ['txnType'] = 'C00002';
	$header ['clientSn'] = $header ['txnType'] . "@" . round ( microtime ( true ) * 1000 );
	$header ['clientDate'] = date ( "Ymd", time () );
	$header ['clientTime'] = date ( "His", time () );
	$header ['fileName'] = "";
	$header ['signTime'] = round ( microtime ( true ) * 1000 );

	$aes = new AES ( JPP_AES_KEY, JPP_AES_IV );
	$post_data = array ();
	$post_data ['accountNo'] = "";
	$post_data ['beginDate'] = "";
	$post_data ['beginPage'] = "1";
	$post_data ['checkType'] = '01';
	$post_data ['customerId'] = $uid;
	$post_data ['endDate'] = "";
	$post_data ['endPage'] = "1";
	$post_data ['note'] = "123";
	$post_data ['showNum'] = "10";

	ksort ( $post_data );
	$signInfo = $header ['signTime'];
	foreach ( $post_data as $value ) {
		$signInfo .= "|" . $value;
	}
	$post_data ['customerId'] = $aes->encrypt ( $uid );
	// var_dump($post_data);

	$rsa_private_key = variable_get ( PRIVATE_KEY_ON_JIUPAIPAY );
	$rsa_public_key = variable_get ( PUBLIC_KEY_ON_JIUPAIPAY );
	$rsa = new RSA ( $rsa_private_key, $rsa_public_key );
	$signData = $rsa->sign ( $signInfo );

	$header ['signature'] = $signData;
	$curl_post_data ['reqHeader'] = $header;
	$curl_post_data ['inBody'] = $post_data;

	$ch = curl_init ( JPP_URL );
	curl_setopt ( $ch, CURLOPT_URL, JPP_URL );
	curl_setopt ( $ch, CURLOPT_HEADER, 0 );
	curl_setopt ( $ch, CURLOPT_POST, 1 );
	curl_setopt ( $ch, CURLOPT_POSTFIELDS, json_encode ( $curl_post_data ) );
	curl_setopt ( $ch, CURLOPT_RETURNTRANSFER, 1 );
	curl_setopt ( $ch, CURLOPT_SSL_VERIFYPEER, false );
	curl_setopt ( $ch, CURLOPT_HTTPHEADER, array (
			'Content-Type: application/json',
			'Content-Length: ' . strlen ( json_encode ( $curl_post_data ) )
	) );

	$response = curl_exec ( $ch );
	if (curl_errno ( $ch )) {
		echo 'Errno ' . curl_error ( $ch ); // 捕抓异常
	}
	curl_close ( $ch );
	$response = json_decode ( $response, true );
	// var_dump($response);
	$result = array ();
	if ($response ['respHeader'] ['respCode'] == 'P2P0000') {
		$result ['status'] = TRUE;
		$result ['code'] = '0';
		$result ['msg'] = '';
		$result ['withdraw'] = number_format ( $response ['outBody'] ['withdrawalamount'], 2, ".", "" ); // 可提现余额
		$result ['balance'] = number_format ( $response ['outBody'] ['availableamount'], 2, ".", "" ); // 可投标余额
		$result ['lock'] = number_format ( $response ['outBody'] ['transitamount'], 2, ".", "" ); // 冻结金额
		//$result ['asset'] =$response['outBody']['assetamount'] ; //账户总资产
		$result ['account_number'] = $aes->encrypt ( $response ['outBody'] ['accountNo'] ); // 台账账号
	} else {
		$result ['status'] = FALSE;
		$result ['code'] = '0';
		$result ['msg'] = '托管账号详情查询失败';
		$result ['withdraw'] = 0;
		$result ['balance'] = 0;
		$result ['lock'] = 0;
		// $result ['asset'] =0;
		$result ['account_number'] = '';
	}
	return $result;
}
