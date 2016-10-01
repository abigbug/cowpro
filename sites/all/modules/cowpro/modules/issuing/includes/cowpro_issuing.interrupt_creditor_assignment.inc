<?php
require_once 'cowpro_issuing.repayment_schedule.fun.inc';
require_once 'cowpro_issuing.creditor_assignment.fun.inc';

/**
 * callback.
 * 中止债权转让
 */
function _cowpro_issuing_interrupt_creditor_assignment($node, $user) {
	ctools_include ( 'modal' );
	ctools_include ( 'ajax' );
	$form_state = array (
			'title' => '中止债权转让：' . $node->title,
			'node' => $node,
			'user' => $user,
			'ajax' => TRUE,
	);
	$output = ctools_modal_form_wrapper ( '_cowpro_issuing_interrupt_creditor_assignment_form', $form_state );
	print ajax_render ( $output );
	exit ();
}

function _cowpro_issuing_interrupt_creditor_assignment_form($form, &$form_state) {
	$node = $form_state ['node'];
	$user = $form_state ['user'];
	$issuing = $node->field_issuing [LANGUAGE_NONE] [0];
	$issuing_id = $node->nid;
	$repayment_schedules = _cowpro_issuing_get_assigning_schedules($issuing_id, $user->uid);
	$values =  array_values ( $repayment_schedules );
	$repayment = array_shift ( $values );
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
			'#value' => '中止转让',
	);
	$form ['cancel'] = array (
			'#type' => 'submit',
			'#value' => '取消',
	);

	return $form;
}

function _cowpro_issuing_interrupt_creditor_assignment_form_submit(&$form, &$form_state) {
	if ($form_state ['values'] ['op'] === $form_state ['values'] ['submit']) {
		$amount = $form_state['input']['amount'];
		$node = $form_state ['node'];
		$user = $form_state ['user'];
		$issuing_id = $node->nid;
		$repayment_schedules = _cowpro_issuing_get_assigning_schedules($issuing_id, $user->uid);
		foreach ( $repayment_schedules as $schedule_id => $repayment ) {
			$repayment->status = 'WAITING_FOR';
			$next_data_serial = _cowpro_issuing_get_repayment_schedule_data_serial($repayment);
			$repayment->data[] = array(
					'serial' => $next_data_serial,
					'timestamp' => time(),
					'operate' => 'interrupt_creditor_assignment',
			);
			entity_save ( 'cowpro_repayment_schedule', $repayment );
		}

		$args = array();
		$args[] = $amount;
		$args[] = $issuing_id;
		$args[] = $repayment_schedules;
		$hook = 'cowpro_issuing_interrupt_creditor_assignment';
		$return = array(
				'success' => TRUE,
		);
		foreach (module_implements($hook) as $module) {
			$function = $module . '_' . $hook;
			if (function_exists($function)) {
				$result = call_user_func_array($function, $args);
				if (isset($result) && is_array($result)) {
					$return = array_merge_recursive($return, $result);
				}
				elseif (isset($result)) {
					$return[] = $result;
				}
			}
		}
		if ($return['success']) {
			$message = '已成功中止转让...';
		} else {
			$message = '中止转让失败:' . $return['message'] . '<br/>代码：' . $return['result_code'];
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
		ctools_include('modal');
		ctools_include('ajax');
		$commands = array ();
		$commands [] = ctools_modal_command_dismiss ();
		print ajax_render ( $commands );
		exit ();
	}
}
