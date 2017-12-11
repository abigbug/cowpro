<?php
/**
 * Determines whether the current user may perform the operation on the issuing.
 *
 * @param $op The
 *        	operation to be performed on the node. Possible values are:
 *        	- 'view brief'://查看贷款申请表(AJAX方式)
 *        	- 'view repayment schedule'://查看还款计划表(AJAX方式)
 *        	- 'view issuing'://查看贷款申请表
 *        	- 'review issuing'://审核贷款
 *        	- 'review again'://重新审核贷款(针对处理“流标”状态的贷款)
 *        	- 'make loans to'://满标放款
 *        	- 'failing issuing'://流标返还
 *        	- 'bid issuing'://我要投资
 *        	- 'creditor assignment'://债权转让
 *        	- 'interrupt creditor assignment'://中止债权转让
 *        	- 'buy creditor assignment'://购买债权
 *        	- 'issuing repayment'://到期还款
 *        	- 'view contract'://查看合同
 *        	- 'download contract'://下载合同
 *        	- 'register custodian'://将标的信息注册到第三方托管服务商
 *
 * @param $node The
 *        	node object on which the operation is to be performed, or node type
 *        	(e.g. 'forum') for "create" operation.
 * @param $account Optional,
 *        	a user object representing the user for whom the operation is to
 *        	be performed. Determines access for a user other than the current user.
 *
 * @return TRUE if the operation may be performed, FALSE otherwise.
 */
function _cowopro_issuing_access($op, $node, $account = NULL) {
	if ($node->type != 'cowpro_issuing') {
		return FALSE;
	}

	$result = FALSE;
	$issuing = $node->field_issuing [LANGUAGE_NONE] [0];
	if (empty ( $account )) {
		$account = $GLOBALS ['user'];
	}

	switch ($op) {
		case 'view repayment schedule' : // 查看还款计划表(AJAX方式)
			$applicant = $node->field_applicant [LANGUAGE_NONE] [0]; // 贷款申请人
			$result = _cowpro_issuing_user_access_repayment_schedule($node->nid, $issuing, $applicant, $account);
			break;
		case 'view brief' : // 查看贷款申请表(AJAX方式)
		case 'view issuing' : // 查看贷款申请表
			if ($issuing ['status'] === COWPRO_ISSUING_STATUS_UNAUDITED) {
				$applicant = $node->field_applicant [LANGUAGE_NONE] [0]; // 贷款申请人
				$result = user_access ( 'review issuing', $account );
				if ($applicant ['uid'] === $account->uid) {
					$result = TRUE;
				}
			} else {
				$result = TRUE;
			}
			break;
		case 'review issuing' : // 审核贷款
			if ($issuing ['status'] === COWPRO_ISSUING_STATUS_UNAUDITED) {
				$result = user_access ( 'review issuing', $account );
			}
			break;
		case 'review again' : // 重新审核贷款
			if ($issuing ['status'] === COWPRO_ISSUING_STATUS_INVITE_BIDS_FAILED) {
				$result = user_access ( 'review issuing', $account );
			}
			break;
		case 'make loans to' : // 满标放款
			if ($issuing ['status'] === COWPRO_ISSUING_STATUS_INVITE_BIDS_SUCCEED) {
				$result = user_access ( 'make loans to', $account );
			}
			break;
		case 'failing issuing' : // 流标返还
			if (($issuing ['status'] === COWPRO_ISSUING_STATUS_AUDITED) || ($issuing ['status'] === COWPRO_ISSUING_STATUS_INVITE_BIDS_START) || ($issuing ['status'] === COWPRO_ISSUING_STATUS_INVITE_BIDS_SUCCEED)) {
				$result = user_access ( 'failing issuing', $account );
			}
			break;
		case 'bid issuing' : // 我要投资
			if ($issuing ['status'] === COWPRO_ISSUING_STATUS_INVITE_BIDS_START) {
				$applicant = $node->field_applicant [LANGUAGE_NONE] [0]; // 贷款申请人
				if ($applicant ['uid'] != $account->uid) {
					$result = user_access ( 'bid issuing', $account );
				}
			}
			break;
		case 'creditor assignment' : // 债权转让
			if ($issuing ['status'] === COWPRO_ISSUING_STATUS_REPAYMENT) {
				// 该“标的”的债权人才有权限转让自己的债权
				$result = _cowpro_issuing_user_access_creditor_assignment($node->nid, $account);
			}
			break;
		case 'interrupt creditor assignment' : // 中止债权转让
			if ($issuing ['status'] === COWPRO_ISSUING_STATUS_REPAYMENT) {
				// 该“标的”的债权人才有权限转让自己的债权
				$result = _cowpro_issuing_user_access_interrupt_creditor_assignment($node->nid, $account);
			}
			break;
		case 'buy creditor assignment' : // 购买债权
			if ($issuing ['status'] === COWPRO_ISSUING_STATUS_REPAYMENT) {
				// 该“标的”的债权人才有权限转让自己的债权
				$result = _cowpro_issuing_user_access_buy_creditor_assignment($node->nid, $account);
			}
			break;
		case 'issuing repayment' : // 到期还款
			if ($issuing ['status'] === COWPRO_ISSUING_STATUS_REPAYMENT) {
				$applicant = $node->field_applicant [LANGUAGE_NONE] [0]; // 贷款申请人
				if (($applicant ['uid'] == $account->uid) || (user_access ( 'admin repayment', $account ))) {
					$result = TRUE;
				}
			}
			break;
		case 'temporary advance' : // 网站代偿
			if ($issuing ['status'] === COWPRO_ISSUING_STATUS_REPAYMENT) {
				$result = user_access ( 'temporary advance', $account );
			}
			break;
		case 'view contract' : // 查看合同
			global $user;
			if ($user->uid == 0) {
				$result = FALSE;//user is not logged in
			} else {
				$result = TRUE;
			}
			break;
		case 'download contract' : // 下载合同
			$result = TRUE;
			break;
		case 'register custodian' : // 将标的信息注册到第三方托管服务商
			if (($node->field_issuing[LANGUAGE_NONE][0]['status'] == COWPRO_ISSUING_STATUS_AUDITED)
				&& custodian_cowpro_fund_issuing_publish_defined()) {
				$result = user_access ( 'make loans to', $account );
			} else {
				$result = FALSE;
			}
			break;
	}
	return $result;
}

/**
 * 判断当前用户是否有权查看指定的还款计划表
 * @param 贷款申请表的ID $nid
 * @param 贷款申请人 $applicant
 * @param 贷款申请表 $issuing
 * @param 当前用户的帐号 $account
 * 如果用户有权查看还款计划表，就返回TRUE
 * 否则，就返回FALSE
 */
function _cowpro_issuing_user_access_repayment_schedule($nid, $issuing, $applicant, $account) {
	return TRUE;
	$result = FALSE;
	if (($issuing ['status'] === COWPRO_ISSUING_STATUS_REPAYMENT)
			|| ($issuing ['status'] === COWPRO_ISSUING_STATUS_FINISHED)) {
				if (user_access ( 'review issuing', $account )) { // 有贷款审核权限的用户可以查看还款计划表
					$result = TRUE;
				} else if ($applicant ['uid'] === $account->uid) { //贷款者本人可以查看还款计划表
					$result = TRUE;
				} else {
					$journal_list = cowpro_issuing_bid_list($nid);
					foreach ($journal_list as $journal) {
						if ($journal->uid === $account->uid) {
							$result = TRUE;
							break;
						}
					}
				}
			}
	return $result;
}

/**
 * 判断当前用户是否有权执行“债权转让”
 * @param 贷款申请表的ID $nid
 * @param 当前用户的帐号 $account
 * 如果用户有权执行“债权转让”，就返回TRUE
 * 否则，就返回FALSE
 */
function _cowpro_issuing_user_access_creditor_assignment($nid, $account) {
	$result = FALSE;
	$uid = $account->uid;
	$conditions = array (
			'issuing_id' => $nid,
			'receiver_uid' => $account->uid,
			'status' => 'WAITING_FOR',
	);
	$reset = FALSE;
	$schedules = entity_load ( 'cowpro_repayment_schedule', FALSE, $conditions, $reset );
	if (sizeof($schedules) > 0) {
		$result = TRUE;
	}
	return $result;
}

/**
 * 判断当前用户是否有权执行“中止债权转让”
 * @param 贷款申请表的ID $nid
 * @param 当前用户的帐号 $account
 * 如果用户有权执行“中止债权转让”，就返回TRUE
 * 否则，就返回FALSE
 */
function _cowpro_issuing_user_access_interrupt_creditor_assignment($nid, $account) {
	$result = FALSE;
	$uid = $account->uid;
	$conditions = array (
			'issuing_id' => $nid,
			'receiver_uid' => $account->uid,
			'status' => 'ASSIGNABLE',
	);
	$reset = FALSE;
	$schedules = entity_load ( 'cowpro_repayment_schedule', FALSE, $conditions, $reset );
	if (sizeof($schedules) > 0) {
		$result = TRUE;
	}
	return $result;
}

/**
 * 判断当前用户是否有权执行“购买债权”
 * @param 贷款申请表的ID $nid
 * @param 债权出让用户的帐号 $account
 * 如果用户有权执行“购买债权”，就返回TRUE
 * 否则，就返回FALSE
 */
function _cowpro_issuing_user_access_buy_creditor_assignment($nid, $account) {
	$result = FALSE;
	$uid = $account->uid;
	if ($uid == $GLOBALS ['user']->uid) {
		//买卖双方不能是同一个用户
		return FALSE;
	}
	$conditions = array (
			'issuing_id' => $nid,
			'receiver_uid' => $account->uid,
			'status' => 'ASSIGNABLE',
	);
	$reset = FALSE;
	$schedules = entity_load ( 'cowpro_repayment_schedule', FALSE, $conditions, $reset );
	if (sizeof($schedules) > 0) {
		$result = TRUE;
	}
	return $result;
}

/**
 * 执行 $op 指定的操作
 *
 * @param $op The
 *        	operation to be performed on the node. Possible values are:
 *        	- 'view brief'://查看贷款申请表(AJAX方式)
 *        	- 'view repayment schedule'://查看还款计划表(AJAX方式)
 *        	- 'view issuing'://查看贷款申请表
 *        	- 'review issuing'://审核贷款
 *        	- 'review again'://重新审核贷款(针对处理“流标”状态的贷款)
 *        	- 'make loans to'://满标放款
 *        	- 'failing issuing'://流标返还
 *        	- 'bid issuing'://我要投资
 *        	- 'creditor assignment'://债权转让
 *        	- 'interrupt creditor assignment'://中止债权转让
 *        	- 'buy creditor assignment'://购买债权
 *        	- 'issuing repayment'://到期还款
 *        	- 'view contract'://查看合同
 *        	- 'download contract'://下载合同
 *        	- 'register custodian'://将标的信息注册到第三方托管服务商
 *
 * @param $node The
 *        	node object on which the operation is to be performed, or node type
 *        	(e.g. 'forum') for "create" operation.
 * @param $account Optional,
 *        	a user object representing the user for whom the operation is to
 *        	be performed. Determines access for a user other than the current user.
 *
 * @return TRUE if the operation may be performed, FALSE otherwise.
 */
function _cowpro_issuing_command($op, $node, $account = NULL) {
	if ($node->type != 'cowpro_issuing') {
		return FALSE;
	}

	$result = FALSE;
	$issuing = $node->field_issuing [LANGUAGE_NONE] [0];
	if (empty ( $account )) {
		$account = $GLOBALS ['user'];
	}

	switch ($op) {
		case 'view brief' : // 查看贷款申请表(AJAX方式)
			return _cowpro_issuing_brief_view($node);
			break;
		case 'view repayment schedule' : // 查看还款计划表(AJAX方式)
			return _cowpro_issuing_repayment_schedule_view($node, $account);
			break;
		case 'view issuing' : // 查看贷款申请表
			break;
		case 'review issuing' : // 审核贷款
			require_once 'cowpro_issuing.review.inc';
			return _cowpro_issuing_review($node);
			break;
		case 'review again' : // 重新审核贷款(针对处理“流标”状态的贷款)
			require_once 'cowpro_issuing.review.inc';
			return _cowpro_issuing_review($node);
			break;
		case 'make loans to' : // 满标放款
			require_once 'cowpro_issuing.loans.inc';
			return _cowpro_issuing_make_loans_to($node);
			break;
		case 'failing issuing' : // 流标返还
			require_once 'cowpro_issuing.failing.inc';
			return _cowpro_issuing_failing($node);
			break;
		case 'bid issuing' : // 我要投资
			require_once 'cowpro_issuing.bid.inc';
			return _cowpro_issuing_bid($node);
			break;
		case 'creditor assignment' : // 债权转让
			require_once 'cowpro_issuing.creditor_assignment.inc';
			return _cowpro_issuing_creditor_assignment($node);
			break;
		case 'interrupt creditor assignment' : // 中止债权转让
			require_once 'cowpro_issuing.interrupt_creditor_assignment.inc';
			return _cowpro_issuing_interrupt_creditor_assignment($node, $account);
			break;
		case 'buy creditor assignment' : // 购买债权
			require_once 'cowpro_issuing.buy_creditor_assignment.inc';
			return _cowpro_issuing_buy_creditor_assignment($node, $account);
			break;
		case 'issuing repayment' : // 到期还款
			require_once 'cowpro_issuing.repayment.inc';
			return _cowpro_issuing_repayment($node);
			break;
		case 'temporary advance' : // 网站代偿
			require_once 'cowpro_issuing.repayment.inc';
			return _cowpro_issuing_temporary_advance($node);
			break;
		case 'view contract' : // 查看合同
			require_once 'cowpro_issuing.contract.inc';
			return _cowpro_issuing_contract_view($node);
			break;
		case 'download contract' : // 下载合同
			require_once 'cowpro_issuing.contract.inc';
			return _cowpro_issuing_contract_download($node);
			break;
		case 'register custodian' : // 将标的信息注册到第三方托管服务商
			require_once 'cowpro_issuing.register.inc';
			return _cowpro_issuing_register($node);
			break;
		}
	return $result;
}

/**
 * Displays a view of brief issuing referenced from the given node, in a megarow.
 */
function _cowpro_issuing_brief_view($node) {
	$title = $node->title;
	$output = views_embed_view ( 'issuing_brief', 'default', $node->nid );

	return views_megarow_display ( $title, $output, $node->nid );
}

/**
 * Displays a view of repayment schedule referenced from the given node, in a megarow.
 */
function _cowpro_issuing_repayment_schedule_view($node, $account) {
	/*
	$title = $node->title;
	$output = views_embed_view ( 'repayment_schedule', 'default', $node->nid );
	return views_megarow_display ( $title, $output, $node->nid );
	*/
	ctools_include ( 'modal' );
	ctools_include ( 'ajax' );

	$title = $node->title;
	if ($account) {
		$uid = $account->uid;
	} else {
		$uid = -1;
	}
	$content = views_embed_view ( 'repayment_schedule', 'default', $node->nid, $uid );
	$output = array ();
	$output [] = ctools_modal_command_display ( $title, $content );
	print ajax_render ( $output );
	exit ();
}
