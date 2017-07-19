<?php
/**
 * callback.
 * 流标退款
 */
function _cowpro_issuing_failing($node) {
	ctools_include ( 'modal' );
	ctools_include ( 'ajax' );
	$form_state = array (
			'nid' => $node->nid,
			'node' => $node,
			'ajax' => TRUE
	);
	$output = ctools_modal_form_wrapper ( '_cowpro_issuing_failing_form', $form_state );
	print ajax_render ( $output );
	exit ();
}

function _cowpro_issuing_failing_form($form, &$form_state) {
	$form['information'] = array(
			'#markup' => "<p>流标操作将把资金退回到投资人帐户</p>",
	);
	$form ['submit'] = array (
			'#type' => 'submit',
			'#value' => '流标退款',
			'#weight' => 100
	);
	$form ['cancel'] = array (
			'#type' => 'submit',
			'#value' => '取消',
			'#weight' => 200
	);
	return $form;
}

function _cowpro_issuing_failing_form_submit(&$form, &$form_state) {
	if ($form_state ['values'] ['op'] === $form_state ['values'] ['submit']) {
		$nid = $form_state['nid'];

		$conditions = array();
		$conditions['internal_reference_id'] = 'ISSUING-' . $nid;
		$conditions['type'] = 'BID';
		$conditions['status'] = TRUE;
		$ids = FALSE;
		$reset = TRUE;
		$bid_items = entity_load('cowpro_fund_journal', $ids, $conditions, $reset);
		if (count($bid_items) == 0) {
			//该标的没有人投标, 不需要进行资金的返还操作
			$result['success'] = TRUE;
		} else {
			$result = custodian_cowpro_fund_issuing_failing($nid);
		}

		//更新ISSUING的状态
		_cowpro_issuing_failing_finished($result['success'], $nid);
		if ($result['success']) {
			$message = '流标操作完成';
			drupal_set_message($message);
		} else {
			$message = '流标操作失败:' . $result['message'] . '<br/>代码：' . $result['result_code'];
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
 * 将issuing的status置成 INVITE_BIDS_FAILED 状态
 * @param 贷款申请表的编号 $nid
 */
function _cowpro_issuing_failing_finished($result, $nid) {
	if ($result) {
		_cowpro_issuing_failing_finished_update_node($nid);
		_cowpro_issuing_failing_finished_update_journal($nid);
	}
}

function _cowpro_issuing_failing_finished_update_node($nid) {
	//更新issuing的状态，置为INVITE_BIDS_FAILED
	$node = node_load($nid);
	$node->field_issuing[LANGUAGE_NONE][0]['status'] = 'INVITE_BIDS_FAILED';
	node_save($node);
}

function _cowpro_issuing_failing_finished_update_journal($nid) {
	//在表cowpro_fund_journal里面登记每一位相关投资人的退款
	$conditions = array();
	$conditions['internal_reference_id'] = 'ISSUING-' . $nid;
	$conditions['type'] = 'BID';
	$conditions['status'] = TRUE;
	$ids = FALSE;
	$reset = TRUE;
	$bid_items = entity_load('cowpro_fund_journal', $ids, $conditions, $reset);
	foreach ($bid_items as $item) {
		$entity_value = array(
				'uid' => $item->uid,
				'status' => TRUE,
				'type' => 'ISSUING_FAILING',
				'amount' => $item->amount,
				'internal_reference_id' => 'ISSUING-' . $nid,
				'external_reference_id' => $item->external_reference_id,
		);
		$entity = entity_create('cowpro_fund_journal', $entity_value);
		entity_get_controller('cowpro_fund_journal')->save($entity);
		$item->status = 2;
		entity_get_controller('cowpro_fund_journal')->save($item);
	}
}