<?php
/**
 * 投标
 *
 * @param int $uid
 *        	用户ID
 * @param float $amount
 *        	投资金额
 * @param int $nid
 *        	标的的 node id
 * @return string
 */
function cash_pooling_bid($uid, $amount, $nid, $journal_id) {
	$result = array();
	$result['success'] = TRUE;
	$result['external_reference_id'] = '';
	$result['data'] = '';
	$result['message'] = '';
	$result['result_code'] = '';
	return 	$result;
}
