<?php
include_once 'moneymoremore.const.inc';
include_once ("libs/RSA.php");
include_once ("libs/Common.php");

/**
 * 账户余额查询(WS)
 *
 * @param int $uid
 */
function _moneymoremore_cowpro_fund_query_balance($uid) {
	$result = array ();
	$profile = cowpro_customer_profile_load_one_row_with_conditions ( $uid, 'moneymoremore' );
	if ($profile == NULL) {
		$result ['status'] = FALSE;
		$result ['code'] = 'COWPRO-1';
		$result ['msg'] = '没有找到托管账户信息';
		$result ['balance'] = 0;
		$result ['lock'] = 0;
		$result ['account_number'] = '';
		return $result;
	}

	$platformId = $profile->mmm_id;
	$platformType = "1"; // 1.托管账户;2.自有账户
	$platformMoneymoremore = variable_get ( PLATFORM_ACCOUNT_ON_MONEYMOREMORE );

	$common = new Common ();
	$dataStr = $platformId . $platformType . $platformMoneymoremore;
	if ($common->getAntiState () == 1) {
		$dataStr = strtoupper ( md5 ( $dataStr ) );
	}
	$private_key = variable_get(PRIVATE_KEY_ON_MONEYMOREMORE);
	$public_key = variable_get(PUBLIC_KEY_ON_MONEYMOREMORE);
	$rsa = new RSA ($private_key, $public_key);
	$signInfo = $rsa->sign ( $dataStr );

	$url = MMM_URL_QUERY_BALANCE;
	$param = array (
			'PlatformId' => $platformId,
			'PlatformType' => $platformType,
			'PlatformMoneymoremore' => $platformMoneymoremore,
			'SignInfo' => $signInfo
	);

	// use key 'http' even if you send the request to https://...
	$options = array (
			'http' => array (
					'header' => "Content-type: application/x-www-form-urlencoded\r\n",
					'method' => 'POST',
					'content' => http_build_query ( $param )
			)
	);
	$context = stream_context_create ( $options );
	$response = file_get_contents ( $url, false, $context );

	$values = explode ( '|', $response );//网贷平台可提现余额|可投标余额(子账户可用余额+公共账户可用余额)|子账户冻结余额
	$result = array();
	if (sizeof ( $values ) == 3) {
		$result ['status'] = TRUE;
		$result ['code'] = '0';
		$result ['msg'] = '';
		$result ['withdraw'] = $values [0];
		$result ['balance'] = $values [1];
		$result ['lock'] = $values [2];
		$result ['account_number'] = $platformId;
	} else {
		$result ['status'] = FALSE;
		$result ['code'] = '0';
		$result ['msg'] = $response;
		$result ['withdraw'] = 0;
		$result ['balance'] = 0;
		$result ['lock'] = 0;
		$result ['account_number'] = $platformId;
	}

	//watchdog('moneymoremore', "moneymoremore_cowpro_fund_query_balance: $response", NULL, WATCHDOG_DEBUG);
	return $result;
}
