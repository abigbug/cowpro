<?php
/**
 * A module-defined block content function.
 */
function _cowpro_fund_balance_contents() {
		$uid = $GLOBALS ['user']->uid;
		$msg = custodian_cowpro_fund_balance_contents($uid);
		$result = array(
				'#markup' => '<div>' . $msg . '</div>',
		);
		return $result;
}

function _cowpro_fund_user_view($account, $view_mode) {
	global $user;
	if (user_access('Administer customer profiles') || ($user->uid == $account->uid) || _cowpro_issuing_user_relationship_check($user->uid, $account->uid)) {
		custodian_user_view_fund($account, $view_mode);
	}
}

/**
 * 检查 $uid 是否是 $requestee_id 的朋友关系
 * @param unknown $uid
 * @param unknown $requestee_id
 * @return boolean
 */
function _cowpro_fund_user_relationship_check($uid, $requestee_id) {
	$relationship_type = user_relationships_type_load(array('name'=>'朋友'));
	$relationships = user_relationships_load(array(
			'requester_id' => $uid,
			'rtid'    => $relationship_type->rtid,
	));

	$relationship = array_shift($relationships);
	if (! $relationship) {
		return FALSE;
	}
	$uid_referree = $relationship->requestee_id;
	return $uid_referree == $requestee_id;
}
