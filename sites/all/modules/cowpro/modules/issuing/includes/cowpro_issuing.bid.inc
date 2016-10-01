<?php
/**
 * callback.
 * 我要投资
 */
function _cowpro_issuing_bid($node) {
	ctools_include ( 'modal' );
	ctools_include ( 'ajax' );
	$issuing = $node->field_issuing [LANGUAGE_NONE] [0];
	$form_state = array (
			'title' => $node->title,
			'nid' => $node->nid,
			'loan_amounts' => $issuing['loan_amounts'],
			'bid_amount' => 0,
			'node' => $node,
			'ajax' => TRUE,
	);
	$output = ctools_modal_form_wrapper ( '_cowpro_issuing_bid_form', $form_state );
	print ajax_render ( $output );
	exit ();
}

function _cowpro_issuing_bid_form($form, &$form_state) {
	$bid_avail = _cowpro_issuing_bid_avail ( $form_state['nid'], $form_state['loan_amounts'] );
	$form ['amount'] = array (
			'#type' => 'numberfield',
			'#title' => '投资金额(元)',
			'#description' => '',
			'#min' => 1,
			'#max' => $bid_avail,
			'#input' => TRUE,
			'#weight' => 10,
	);
	$form['information'] = array(
			'#markup' => "<p>当前最大可投资金额为 $bid_avail 元</p>",
	);
	$form ['submit'] = array (
			'#type' => 'submit',
			'#value' => '投标',
			'#weight' => 100,
	);
	$form ['cancel'] = array (
			'#type' => 'submit',
			'#value' => '取消',
			'#weight' => 200,
	);
	return $form;
}

function _cowpro_issuing_bid_avail($nid, $loan_amounts) {
	$query = db_select('cowpro_fund_journal', 'j');
	$query->addExpression('SUM(amount)', 'total');
  $query->condition('j.internal_reference_id', 'ISSUING-' . $nid, '=');
  $query->condition('j.type', 'BID', '=');
  $query->condition('j.status', TRUE, '=');
  $result = $query->execute()->fetchAll();
  $bid_avail = $loan_amounts - $result[0]->total;
	return $bid_avail;
}

function _cowpro_issuing_bid_list($nid) {
	$query = db_select('cowpro_fund_journal', 'j');
	$query->addField('j', 'uid');
	$query->addField('j', 'amount');
	$query->addField('j', 'created');
	$query->condition('j.internal_reference_id', 'ISSUING-' . $nid, '=');
  $query->condition('j.type', 'BID', '=');
  $query->condition('j.status', TRUE, '=');
  $result = $query->execute()->fetchAll();
	return $result;
}

/**
 * Validation callback for _cowpro_issuing_bid_form().
 */
function _cowpro_issuing_bid_form_validate($form, &$form_state) {
	if ($form_state ['values'] ['op'] === $form_state ['values'] ['submit']) {
		$bid_avail = _cowpro_issuing_bid_avail($form_state['nid'], $form_state['loan_amounts']);
		if ($form_state ['values']['amount'] > $bid_avail) {
			form_set_error ( 'bid', "请注意，当前最大可投资金额为 $bid_avail 元" );
		}
		if ($form_state ['values']['amount'] <= 0) {
			form_set_error ( 'bid', '请填写有效的投资金额(大于零)' );
		}
	}
}

function _cowpro_issuing_bid_form_submit(&$form, &$form_state) {
	if ($form_state ['values'] ['op'] === $form_state ['values'] ['submit']) {
		$amount = $form_state['input']['amount'];
		$nid = $form_state['nid'];
		$uid = $GLOBALS['user']->uid;
		$entity_value = array(
				'uid' => $uid,
				'status' => FALSE,
				'type' => 'BID',
				'amount' => $amount,
				'internal_reference_id' => 'ISSUING-' . $nid,
		);
		$entity = entity_create('cowpro_fund_journal', $entity_value);
		entity_get_controller('cowpro_fund_journal')->save($entity);
		$journal_id = $entity->journal_id;

		$result = custodian_cowpro_fund_bid($uid, $amount, $nid, $journal_id);

		$entity = entity_load_single('cowpro_fund_journal', $journal_id);
		if ($result['success']) {
			$status = TRUE;
		} else {
			$status = FALSE;
		}
		$entity->status = $status;
		$entity->external_reference_id =$result['external_reference_id'];
		$entity->data = $result['data'];
		entity_get_controller('cowpro_fund_journal')->save($entity);

		_cowpro_issuing_bid_finished($result['success'], $nid, $journal_id);
		if ($result['success']) {
			$message = '投标成功';
		} else {
			$message = '投标失败:' . $result['message'] . '<br/>代码：' . $result['result_code'];
		}
		drupal_set_message($message);

		ctools_include ( 'modal' );
		ctools_include ( 'ajax' );
		ctools_add_js('ajax-responder','ajax-responder');
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
 * 检查issuing的投标总额，如果投标总额等于贷款申请额，就将status标记为INVITE_BIDS_SUCCEED状态
 * @param 贷款申请表的编号 $nid
 */
function _cowpro_issuing_bid_finished($success, $nid, $journal_id) {
	if ($success) {
		$loan_amounts = db_query("SELECT i.field_issuing_loan_amounts FROM {field_data_field_issuing} i WHERE i.entity_id = $nid")->fetchField();
		//watchdog('issuing debug', "_cowpro_issuing_bid_finished: nid=$nid; loan_amounts=$loan_amounts", NULL, WATCHDOG_DEBUG);
		if (_cowpro_issuing_bid_avail($nid, $loan_amounts) == 0) {
			//watchdog('issuing debug', "_cowpro_issuing_bid_finished: _cowpro_issuing_bid_avail==0", NULL, WATCHDOG_DEBUG);
			db_query("UPDATE {field_data_field_issuing} SET field_issuing_status = '" . COWPRO_ISSUING_STATUS_INVITE_BIDS_SUCCEED . "' WHERE entity_id = $nid");
			//参考 http://stackoverflow.com/questions/9870608/how-to-clear-node-custom-field-cache-in-drupal-7
			//how to clear node custom field cache in drupal 7
			cache_clear_all("field:node:$nid", 'cache_field');
			entity_get_controller('node')->resetCache(array($nid));
		}
	}

	$args = array();
	$args[] = $success;
	$args[] = $nid;
	$args[] = $journal_id;
	$hook = 'cowpro_fund_bid_finished';
	foreach (module_implements($hook) as $module) {
		$function = $module . '_' . $hook;
		if (function_exists($function)) {
			call_user_func_array($function, $args);
		}
	}
}