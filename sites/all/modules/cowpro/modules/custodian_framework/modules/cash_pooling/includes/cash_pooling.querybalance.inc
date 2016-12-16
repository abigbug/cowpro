<?php
/**
 * 账户余额查询
 *
 * @param int $uid
 */
function cash_pooling_cowpro_fund_query_balance($uid) {
	$result = array ();
	$result ['status'] = TRUE;
	$result ['code'] = '0';
	$result ['msg'] = '';
	$result ['balance'] = 999;
	$result ['lock'] = 9;
	$result ['account_number'] = 'id_xxx';
	return $result;
}
