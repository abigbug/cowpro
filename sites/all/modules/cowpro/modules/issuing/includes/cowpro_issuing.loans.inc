<?php
/**
 * callback.
 * 满标放款
 */
function _cowpro_issuing_make_loans_to($node) {
	ctools_include ( 'modal' );
	ctools_include ( 'ajax' );
	$form_state = array (
			'nid' => $node->nid,
			'node' => $node,
			'ajax' => TRUE
	);
	$output = ctools_modal_form_wrapper ( '_cowpro_issuing_make_loans_to_form', $form_state );
	print ajax_render ( $output );
	exit ();
}

function _cowpro_issuing_make_loans_to_form($form, &$form_state) {
	$form['information'] = array(
			'#markup' => "<p>满标放款操作将把资金发放到贷款人帐户</p>",
	);
	$form ['submit'] = array (
			'#type' => 'submit',
			'#value' => '满标放款',
			'#weight' => 100
	);
	$form ['cancel'] = array (
			'#type' => 'submit',
			'#value' => '取消',
			'#weight' => 200
	);
	return $form;
}

function _cowpro_issuing_make_loans_to_form_submit(&$form, &$form_state) {
	if ($form_state ['values'] ['op'] === $form_state ['values'] ['submit']) {
		$nid = $form_state['nid'];

		//更新issuing的放款时间
		$node = node_load($nid);
		$node->field_issuing[LANGUAGE_NONE][0]['make_loans_time'] = REQUEST_TIME;
		node_save($node);

		$result = custodian_cowpro_fund_make_loans_to($nid);
		//$message = implode('|', $result);
		//watchdog('_cowpro_issuing_make_loans_to_form_submit', $message);
		_cowpro_issuing_loans_finished($result['success'], $nid);
		if ($result['success']) {
			$message = '放款成功';
			drupal_set_message($message);
		} else {
			$message = '放款失败:' . $result['message'] . '<br/>代码：' . $result['result_code'];
			drupal_set_message($message, 'error');
		}

		ctools_include ( 'modal' );
		ctools_include ( 'ajax' );
		$commands = array ();
		$commands[] = ctools_ajax_command_reload();
		print ajax_render ( $commands );
		exit ();
	} else {
		$commands = array ();
		$commands [] = ctools_modal_command_dismiss ();
		print ajax_render ( $commands );
		exit ();
	}
}

/**
 * 将issuing的status标记为REPAYMENT状态
 * @param 贷款申请表的编号 $nid
 */
function _cowpro_issuing_loans_finished($success, $nid) {
	if ($success) {
		_cowpro_issuing_loans_finished_update_node($nid);
		_cowpro_issuing_loans_finished_update_journal($nid);
	}
	$conditions = array();
	$conditions['internal_reference_id'] = 'ISSUING-' . $nid;
	$conditions['type'] = 'BID';
	$conditions['status'] = TRUE;
	$ids = FALSE;
	$reset = TRUE;
	$fund_journals = entity_load('cowpro_fund_journal', $ids, $conditions, $reset);

	$args = array();
	$args[] = $success;
	$args[] = $nid;
	$args[] = $fund_journals;
	$hook = 'cowpro_fund_make_loans_to_finished';
	foreach (module_implements($hook) as $module) {
		$function = $module . '_' . $hook;
		if (function_exists($function)) {
			call_user_func_array($function, $args);
		}
	}
}

function _cowpro_issuing_loans_finished_update_node($nid) {
		//更新issuing的状态，置为REPAYMENT
		$node = node_load($nid);
		$node->field_issuing[LANGUAGE_NONE][0]['status'] = 'REPAYMENT';
		node_save($node);
}

function _cowpro_issuing_loans_finished_update_journal($nid) {
	$node = node_load($nid);

	//在表cowpro_fund_journal里面登记
	//记录该笔资金已划拨到贷款申请人帐户
	$entity_value = array(
			'uid' => $node->field_applicant [LANGUAGE_NONE] [0] ['uid'],// 贷款申请人
			'status' => TRUE,
			'type' => 'MAKE_LOANS_TO',
			'amount' => $node->field_issuing[LANGUAGE_NONE][0]['loan_amounts'],
			'internal_reference_id' => 'ISSUING-' . $nid,
	);
	$entity = entity_create('cowpro_fund_journal', $entity_value);
	entity_get_controller('cowpro_fund_journal')->save($entity);

	//生成还款计划表
	$issuing = $node->field_issuing [LANGUAGE_NONE] [0];
	$applicant = $node->field_applicant [LANGUAGE_NONE] [0];
	cowpro_issuing_create_repayment_schedule($node->nid, $applicant, $issuing);
}