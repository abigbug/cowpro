<?php
require_once 'cowpro_issuing.repayment_schedule.fun.inc';
require_once 'cowpro_issuing.creditor_assignment.fun.inc';

/**
 * callback.
 * 购买债权
 */
function _cowpro_issuing_buy_creditor_assignment($node, $user) {
	ctools_include ( 'modal' );
	ctools_include ( 'ajax' );
	$form_state = array (
			'title' => '购买债权：' . $node->title,
			'node' => $node,
			'user' => $user,
			'ajax' => TRUE,
	);
	$output = ctools_modal_form_wrapper ( '_cowpro_issuing_buy_creditor_assignment_form', $form_state );
	print ajax_render ( $output );
	exit ();
}

function _cowpro_issuing_buy_creditor_assignment_form($form, &$form_state) {
	$node = $form_state ['node'];
	$user = $form_state ['user'];
	$issuing = $node->field_issuing [LANGUAGE_NONE] [0];
	$issuing_id = $node->nid;
	$repayment_schedules = _cowpro_issuing_get_assigning_schedules($issuing_id, $user->uid);
	$values = array_values ( $repayment_schedules );
	$repayment = array_shift ($values );
	$bid_amount =  _cowpro_issuing_get_creditor_assignment_amount($repayment);
	$deadline = $repayment->deadline;
	$period_count = count ( $repayment_schedules );
	$amount = 0;
	$content = '<tr><td>期次</td><td>收款时间</td><td>收款金额</td></tr>';
	foreach ( $repayment_schedules as $schedule_id => $repayment ) {
		$row = '<tr><td>' . $repayment->period . '</td><td>' . gmdate ( "Y年m月d日", $repayment->deadline ) . '</td><td>' . $repayment->receivable_amount . '</td></tr>';
		$content .= $row;
		$amount += $repayment->receivable_amount;
	}
	$content = "<table>$content</table>";

	$detail = '<ul>';
	$detail .= '<li>项目名称：' . $node->title . '</li>';
	$detail .= '<li>下个还款日：' . gmdate ( "Y年m月d日", $deadline ) . '</li>';
	$detail .= '<li>待还期数：' . $period_count . '</li>';
	$detail .= '<li>剩余本息合计：' . $amount . '</li>';
	$detail .= '</ul>';
	$form ['detail'] = array (
			'#type' => 'markup',
			'#markup' => $detail,
	);

	$form ['content'] = array (
			'#type' => 'markup',
			'#markup' => $content,
	);

	$form ['amount'] = array (
			'#type' => 'numberfield',
			'#title' => '转让金额(元)',
			'#description' => '',
			'#default_value' => $bid_amount,
			'#disabled' => TRUE,
	);
	$form ['submit'] = array (
			'#type' => 'submit',
			'#value' => '购买债权',
	);
	$form ['cancel'] = array (
			'#type' => 'submit',
			'#value' => '取消',
	);

	return $form;
}

function _cowpro_issuing_buy_creditor_assignment_form_submit(&$form, &$form_state) {
	if ($form_state ['values'] ['op'] === $form_state ['values'] ['submit']) {
		$node = $form_state ['node'];
		$seller = $form_state ['user'];
		$seller_uid = $seller->uid;
		global $user;
		$buyer_uid = $user->uid;
		$issuing_id = $node->nid;
		$repayment_schedules = _cowpro_issuing_get_assigning_schedules($issuing_id, $seller_uid);
		$values = array_values ( $repayment_schedules );
		$repayment = array_shift ( $values);
		$amount =  _cowpro_issuing_get_creditor_assignment_amount($repayment);

		$count = count($repayment_schedules);
		$updated = db_update('cowpro_repayment_schedule')
			->condition('issuing_id', $issuing_id)
			->condition('receiver_uid', $seller_uid)
			->condition('status', 'ASSIGNABLE')
			->fields(array('status' => 'LOCKED'))
			->execute();
		$locked = TRUE;
		if (($count == 0) || ($count != $updated)) {
			$locked = FALSE;
		}

		if ($locked) {
			$result = custodian_cowpro_fund_buy_creditor_assignment($amount, $issuing_id, $seller_uid, $buyer_uid);
			if (!$result['success']) {
				$updated = db_update('cowpro_repayment_schedule')
				->condition('issuing_id', $issuing_id)
				->condition('receiver_uid', $seller_uid)
				->condition('status', 'LOCKED')
				->fields(array('status' => 'ASSIGNABLE'))
				->execute();
			}
		} else {
			$result = array(
					'success' => FALSE,
					'message' => '未能锁定债权',
					'result_code' => 'COWPRO_ERR_02',
			);
		}
		cowpro_issuing_buy_creditor_assignment_finished($result['success'], $repayment_schedules, $buyer_uid, $seller_uid, $amount, $result);
		if ($result['success']) {
			$message = '已成功购买债权';
			drupal_set_message($message);
		} else {
			$message = '购买债权失败:' . $result['message'] . '<br/>代码：' . $result['result_code'];
			drupal_set_message($message, 'error');
		}

		ctools_include ( 'modal' );
		ctools_include ( 'ajax' );
		$commands = array ();
		$commands[] = ctools_ajax_command_reload();
		print ajax_render ( $commands );
		exit ();
	} else {
		ctools_include('modal');
		ctools_include('ajax');
		$commands = array ();
		$commands [] = ctools_modal_command_dismiss ();
		print ajax_render ( $commands );
		exit ();
	}
}

function cowpro_issuing_buy_creditor_assignment_finished($success, $repayment_schedules, $buyer_uid, $seller_uid, $amount, $result) {
	if ($success) {
		foreach ( $repayment_schedules as $schedule_id => $repayment ) {
			$repayment->receiver_uid = $buyer_uid;
			$repayment->status = 'WAITING_FOR';
			$next_data_serial = _cowpro_issuing_get_repayment_schedule_data_serial($repayment);
			$repayment->data[] = array(
					'serial' => $next_data_serial,
					'timestamp' => time(),
					'operate' => 'buy_creditor_assignment',
					'buyer' => $buyer_uid,
					'seller' => $seller_uid,
					'amount' => $amount,
					'memo' => $return['memo'],
			);
			entity_save ( 'cowpro_repayment_schedule', $repayment );
		}
	}

	$values =  array_values ( $repayment_schedules );
	$repayment = array_shift($values);
	$args = array();
	$args[] = $success;
	$args[] = $repayment->issuing_id;
	$args[] = $buyer_uid;
	$args[] = $seller_uid;
	$args[] = $amount;
	$hook = 'cowpro_fund_buy_creditor_assignment_finished';
	foreach (module_implements($hook) as $module) {
		$function = $module . '_' . $hook;
		if (function_exists($function)) {
			call_user_func_array($function, $args);
		}
	}
}
