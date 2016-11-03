<?php

/**
 * callback.
 * 网站代偿
 */
function _cowpro_issuing_temporary_advance($node) {
	$temporary_advance = TRUE;
	_cowpro_issuing_repayment($node, $temporary_advance);
}

/**
 * callback.
 * 按期还款
 */
function _cowpro_issuing_repayment($node, $temporary_advance=FALSE) {
	ctools_include ( 'modal' );
	ctools_include ( 'ajax' );
	$issuing = $node->field_issuing [LANGUAGE_NONE] [0];
	$form_state = array (
			'temporary_advance' => $temporary_advance,
			'title' => $node->title,
			'nid' => $node->nid,
			'loan_amounts' => $issuing ['loan_amounts'],
			'bid_amount' => 0,
			'node' => $node,
			'ajax' => TRUE,
	);
	$output = ctools_modal_form_wrapper ( '_cowpro_issuing_repayment_form', $form_state );
	print ajax_render ( $output );
	exit ();
}

function _cowpro_issuing_repayment_form($form, &$form_state) {
	/*
	if ($form_state ['temporary_advance'] === TRUE) {
		$val = FALSE;
		if ($form_state['input']['temporary_advance']) {
			$val = TRUE;
		}
		$form ['temporary_advance'] = array (
				'#type' => 'checkbox',
				'#default_value' => $val,
				'#title' => '网站代偿',
		);
	}
	*/
	$form ['repayment_schedule'] = array (
			'#type' => 'markup',
			'#markup' => views_embed_view ( 'repayment_schedule_debtor', 'default', $form_state['nid']),
			'#weight' => 1,
	);
	return $form;
}

function _cowpro_issuing_repayment_form_submit(&$form, &$form_state) {

	if ($form_state ['values'] ['op'] === $form_state ['values'] ['submit']) {
		$amount = $form_state ['input'] ['amount'];
		$nid = $form_state ['nid'];
		$result = custodian_cowpro_fund_repayment($amount, $nid);
		$commands = array ();
		$commands [] = ctools_modal_command_dismiss ();
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
 * Renders a View for display in some other element.
 *
 * @param $view_key The
 *        	ID of the View to embed.
 * @param $display_id The
 *        	ID of the display of the View that will actually be rendered.
 * @param $arguments An
 *        	array of arguments to pass to the View.
 *
 * @return The rendered output of the chosen View display.
 */
function _cowpro_issuing_embed_view($view_id, $display_id, $arguments) {
	// Load the specified View.
	$view = views_get_view ( $view_id );
	$view->set_display ( $display_id );

	// Set the specific arguments passed in.
	$view->set_arguments ( $arguments );

	// Override the view url, if an override was provided.
	if (! empty ( $override_url )) {
		$view->override_url = $override_url;
	}

	// Prepare and execute the View query.
	$view->pre_execute ();
	$view->execute ();

	// Return the rendered View.
	return $view->render ();
}

function _cowpro_issuing_repayment_action(&$entities, $context = array()) {
	$repayment_list = array();
	foreach ($entities as $entity) {
		$repayment_object = new StdClass;
		$repayment_object->issuing_id = $entity->issuing_id;
		$repayment_object->period = $entity->period;
		$repayment_list[] = $repayment_object;
	}
	$entities = array();
	foreach ($repayment_list as $repayment_object) {
		$conditions = array (
			'issuing_id' => $repayment_object->issuing_id,
			'period' => $repayment_object->period,
			'status' => 'WAITING_FOR',
		);
		$reset = FALSE;
		$schedules = entity_load ( 'cowpro_repayment_schedule', FALSE, $conditions, $reset );
		foreach ($schedules as $schedule) {
			if ($schedule->receiver_uid != -1) {
				$entities[] = $schedule;
			}
		}
	}
	$result = custodian_cowpro_fund_repayment($entities);
	_cowpro_issuing_repayment_finished($result['success'], $entities);

	if ($result['success']) {
		$message = '还款成功';
	} else {
		$message = '还款失败:' . $result['message'] . '<br/>代码：' . $result['result_code'];
	}
	drupal_set_message($message);

	ctools_include ( 'modal' );
	ctools_include ( 'ajax' );
	ctools_add_js('ajax-responder','ajax-responder');
	$commands = array ();
	$commands[] = ctools_ajax_command_reload();
	print ajax_render ( $commands );
	exit ();
}

function _cowpro_issuing_repayment_finished($success, $repayment_schedules) {
	if ($success) {
		_cowpro_issuing_repayment_update($repayment_schedules);
	}
	$values = array_values ( $repayment_schedules );
	$repayment = array_shift($values);
	$nid = $repayment->issuing_id;

	$args = array();
	$args[] = $success;
	$args[] = $nid;
	$args[] = $repayment_schedules;
	$hook = 'cowpro_fund_repayment_finished';
	foreach (module_implements($hook) as $module) {
		$function = $module . '_' . $hook;
		if (function_exists($function)) {
			call_user_func_array($function, $args);
		}
	}
}

function _cowpro_issuing_repayment_update($repayment_schedules) {
	$paid_amount = 0;//累计贷款人本期还款总额
	foreach ($repayment_schedules as $repayment) {
		$repayment->status = 'COMPLETED';
		$repayment->paid_amount = $repayment->payable_amount;
		$repayment->received_amount = $repayment->receivable_amount;
		entity_save ( 'cowpro_repayment_schedule', $repayment );

		$paid_amount += $repayment->payable_amount;

		//登记债权人的收款流水帐
		$issuing_id = $repayment->issuing_id;
		$period = $repayment->period;
		$period_total = $repayment->period_total;
		$internal_reference_id = 'ISSUING-' . $issuing_id . ';PERIOD-' . $period . '/' . $period_total;
		$journal = array(
				'uid' => $repayment->receiver_uid,
				'status' => TRUE,
				'type' => 'REPAYMENT_RECEIPTS',
				'amount' => $repayment->receivable_amount,
				'internal_reference_id' => $internal_reference_id,
				//'internal_reference_id' => 'REPAYMENT-' . $repayment->schedule_id,
				'external_reference_id' => '',
		);
		$entity = entity_create('cowpro_fund_journal', $journal);
		entity_get_controller('cowpro_fund_journal')->save($entity);
	}

	$values = array_values ( $repayment_schedules );
	$repayment = array_shift($values);
	$issuing_id = $repayment->issuing_id;
	$period = $repayment->period;
	$period_total = $repayment->period_total;

	//cowpro_repayment_schedule表中，每一期的还款记录中有一个receiver_uid=-1的记录
	//是为了views输出方便而存在的冗余记录
	//在当期还款完毕以后，我们要在这里更新这条记录
	$conditions = array (
			'issuing_id' => $issuing_id,
			'period' => $period,
			'receiver_uid' => -1,
			'status' => 'WAITING_FOR',
	);
	$reset = FALSE;
	$schedules = entity_load ( 'cowpro_repayment_schedule', FALSE, $conditions, $reset );
	$schedule = array_shift($schedules);
	if ($schedule) {
		$schedule->paid_amount = $schedule->paid_amount + $paid_amount;
		if ($schedule->payable_amount == $schedule->paid_amount) {
			$schedule->status = 'COMPLETED';
		}
		entity_save ( 'cowpro_repayment_schedule', $schedule );
	}

	//登记贷款人的付款流水帐
	$internal_reference_id = 'ISSUING-' . $issuing_id . ';PERIOD-' . $period . '/' . $period_total;
	$journal = array(
			'uid' => $repayment->payer_uid,
			'status' => TRUE,
			'type' => 'REPAYMENT_PAYMENTS',
			'amount' => $paid_amount,
			'internal_reference_id' => $internal_reference_id,
			'external_reference_id' => '',
	);
	$entity = entity_create('cowpro_fund_journal', $journal);
	entity_get_controller('cowpro_fund_journal')->save($entity);

	//表cowpro_repayment_schedule可能因为正在进行债权转让而将status字段标记为"ASSIGNABLE"
	//这种情况下，系统要自动中止债权转让，将status字段重新标记为"WAITING_FOR"
	$count = db_update('cowpro_repayment_schedule')
	->fields(array('status' => 'WAITING_FOR'))
  ->condition('issuing_id', $issuing_id)
  ->condition('status', 'ASSIGNABLE')
  ->execute();
	/*
	watchdog('cowpro_repayment', '中止与“issuing_id:%id”相关的债权转让，更新cowpro_repayment_schedule记录，共 %count 条',
			array('%id' => $issuing_id, '%count' => $count), WATCHDOG_DEBUG);
			*/

  $query = db_select('cowpro_repayment_schedule', 's');
  $query->addExpression('COUNT(*)', 'count');
  $query->condition('issuing_id', $issuing_id);
  $query->condition('status', 'WAITING_FOR');
  $result = $query->execute()->fetchAll();
  $count = $result[0]->count;

  if ($count == 0) {
	  //更新issuing的状态，置为FINISHED
	  $node = node_load($issuing_id);
	  $node->field_issuing[LANGUAGE_NONE][0]['status'] = 'FINISHED';
	  node_save($node);
  }

}