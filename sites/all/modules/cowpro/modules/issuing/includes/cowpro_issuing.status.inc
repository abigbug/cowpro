<?php
function _cowpro_issuing_user_view($account, $view_mode) {
	global $user;
	if (user_access('Administer customer profiles') || ($user->uid == $account->uid) || _cowpro_issuing_user_relationship_check($user->uid, $account->uid)) {
		_cowpro_issuing_user_view_debtor($account, $view_mode);
		_cowpro_issuing_user_view_lender($account, $view_mode);
		_cowpro_issuing_user_view_payable($account, $view_mode);
		_cowpro_issuing_user_view_receivable($account, $view_mode);
	}
}

function _cowpro_issuing_user_view_debtor($account, $view_mode) {
	$role = user_role_load_by_name('debtor');
	if (user_has_role($role->rid, $account)) {
		$uid = $account->uid;
		$capital = db_query("SELECT SUM(capital) FROM {cowpro_repayment_schedule} WHERE receiver_uid = -1 AND payer_uid = $uid")->fetchField();
		$count = db_query("SELECT COUNT(DISTINCT issuing_id) FROM {cowpro_repayment_schedule} WHERE receiver_uid = -1 AND payer_uid = $uid")->fetchField();
		$payable_amount = db_query("SELECT SUM(payable_amount) FROM {cowpro_repayment_schedule} WHERE receiver_uid = -1 AND payer_uid = $uid")->fetchField();
		$paid_amount = db_query("SELECT SUM(paid_amount) FROM {cowpro_repayment_schedule} WHERE receiver_uid = -1 AND payer_uid = $uid")->fetchField();

		$account->content['debtor'] = array(
				'#type' => 'user_profile_category',
				'#title' => '贷款详情',
				'#weight' => 0,
		);
		$account->content['debtor']['debtor_1'] = array(
				'#type' => 'user_profile_item',
				'#title' => '贷款总额',
				'#markup' => $capital,
		);
		$account->content['debtor']['debtor_2'] = array(
				'#type' => 'user_profile_item',
				'#title' => '贷款笔数',
				'#markup' => $count,
		);
		$account->content['debtor']['debtor_3'] = array(
				'#type' => 'user_profile_item',
				'#title' => '已还本息',
				'#markup' => $payable_amount,
		);
		$account->content['debtor']['debtor_4'] = array(
				'#type' => 'user_profile_item',
				'#title' => '待还本息',
				'#markup' => $paid_amount,
		);
	}
}

function _cowpro_issuing_user_view_payable($account, $view_mode) {
	$role = user_role_load_by_name('debtor');
	if (user_has_role($role->rid, $account)) {
		$view = views_get_view('due_in_list');
		$view->set_display('due_in_list_debtor');
		$view->set_arguments(array($account->uid));
		$view->pre_execute();
		$view->execute();

		$account->content['due_in_list_debtor'] = array(
				'#type' => 'user_profile_category',
				'#title' => '近期待还款',
				'#weight' => 0,
		);
		$account->content['due_in_list_debtor']['due_in_list_debtor_1'] = array(
				'#type' => 'user_profile_item',
				'#title' => '待还款清单',
				'#markup' => $view->render(),
		);
	}
}

function _cowpro_issuing_user_view_receivable($account, $view_mode) {
	$view = views_get_view('due_in_list');
	$view->set_display('due_in_list_lender');
	$view->set_arguments(array($account->uid));
	$view->pre_execute();
	$view->execute();

	$account->content['due_in_list_lender'] = array(
			'#type' => 'user_profile_category',
			'#title' => '近期待收款',
			'#weight' => 0,
			'#prefix' => '<div class="cowpro_issuing_views">',
			'#suffix' => '</div>',
	);
	$account->content['due_in_list_lender']['due_in_list_lender_1'] = array(
			'#type' => 'user_profile_item',
			'#title' => '待收款清单',
			'#markup' => $view->render(),
	);
}

function _cowpro_issuing_user_view_lender($account, $view_mode) {
	$uid = $account->uid;
	$capital = db_query("SELECT SUM(capital) FROM {cowpro_repayment_schedule} WHERE receiver_uid = $uid")->fetchField();
	$count = db_query("SELECT COUNT(DISTINCT issuing_id) FROM {cowpro_repayment_schedule} WHERE receiver_uid = $uid")->fetchField();
	$received_amount = db_query("SELECT SUM(received_amount) FROM {cowpro_repayment_schedule} WHERE receiver_uid = $uid")->fetchField();
	$receivable_amount = db_query("SELECT SUM(receivable_amount - received_amount) FROM {cowpro_repayment_schedule} WHERE receiver_uid = $uid")->fetchField();
	if ($capital === NULL) {
		$capital = 0;
	}
	if ($count === NULL) {
		$count = 0;
	}
	if ($received_amount === NULL) {
		$received_amount = 0;
	}
	if ($receivable_amount === NULL) {
		$receivable_amount = 0;
	}

	$account->content['debtor'] = array(
			'#type' => 'user_profile_category',
			'#title' => '投资统计',
			'#weight' => 0,
	);
	$account->content['debtor']['debtor_1'] = array(
			'#type' => 'user_profile_item',
			'#title' => '投资总额',
			'#markup' => $capital,
	);
	$account->content['debtor']['debtor_2'] = array(
			'#type' => 'user_profile_item',
			'#title' => '投资笔数',
			'#markup' => $count,
	);
	$account->content['debtor']['debtor_3'] = array(
			'#type' => 'user_profile_item',
			'#title' => '已收本息',
			'#markup' => $received_amount,
	);
	$account->content['debtor']['debtor_4'] = array(
			'#type' => 'user_profile_item',
			'#title' => '待收本息',
			'#markup' => $receivable_amount,
	);
}

/**
 * 检查 $uid 是否是 $requestee_id 的朋友关系
 * @param unknown $uid
 * @param unknown $requestee_id
 * @return boolean
 */
function _cowpro_issuing_user_relationship_check($uid, $requestee_id) {
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
