<?php
include_once 'jiupaipay.const.inc';
include_once ("libs/RSA.php");
include_once ("jiupaipay.fun.inc");
include_once ("libs/AES.php");
include_once ("libs/Common.php");

/*
 *
 */
function jiupaipay_ledger_account() {
	$header = jiupaipay_header ( "C00002" );

	$aes = new AES ( JPP_AES_KEY, JPP_AES_IV );
	$post_data = array ();
	$post_data ['checkType'] = "03";
	$post_data ['customerId'] = "";
	$post_data ['accountNo'] = JBZ_PM;
	$post_data ['beginDate'] = '';
	$post_data ['endDate'] = "";
	$post_data ['beginPage'] = "";
	$post_data ['endPage'] = "";
	$post_data ['showNum'] = 10;
	$post_data ['note'] = "";
	ksort ( $post_data );
	$signInfo = $header ['signTime'];
	foreach ( $post_data as $value ) {
		$signInfo .= "|" . $value;
	}

	$post_data ['accountNo'] = $aes->encrypt ( $post_data ['accountNo'] );
	$rsa_private_key = variable_get ( PRIVATE_KEY_ON_JIUPAIPAY );
	$rsa_public_key = variable_get ( PUBLIC_KEY_ON_JIUPAIPAY );
	$rsa = new RSA ( $rsa_private_key, $rsa_public_key );
	$signData = $rsa->sign ( $signInfo );

	$header ['signature'] = $signData;
	$curl_post_data ['reqHeader'] = $header;
	$curl_post_data ['inBody'] = $post_data;

	$result = jiupaipay_curl_api ( $curl_post_data );
	$result = json_decode ( $result, true );

	var_dump ( $result );
	die ();
	if ($result ['respHeader'] ['respCode'] == 'P2P0000') {
	} else {
		echo $result ['respHeader'] ['respMsg'];
	}
}

?>