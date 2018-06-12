<?php
require_once 'cowpro_issuing.repayment_schedule.fun.inc';

/**
 * callback.
 * 债权转让
 */
function _cowpro_issuing_creditor_assignment($node) {
	ctools_include ( 'modal' );
	ctools_include ( 'ajax' );
	$form_state = array (
			'title' => '债权转让：' . $node->title,
			'node' => $node,
			'ajax' => TRUE,
	);
	$output = ctools_modal_form_wrapper ( '_cowpro_issuing_creditor_assignment_form', $form_state );
	print ajax_render ( $output );
	exit ();
}

function _cowpro_issuing_get_assignable_schedules($issuing_id) {
	$uid = $GLOBALS ['user']->uid;
	$query = new EntityFieldQuery ();
	$query->entityCondition ( 'entity_type', 'cowpro_repayment_schedule' )->propertyCondition ( 'issuing_id', $issuing_id )->propertyCondition ( 'receiver_uid', $uid )->propertyCondition ( 'status', 'WAITING_FOR' )->propertyOrderBy ( 'deadline', 'ASC' );
	$result = $query->execute ();
	$ids = array_keys ( $result ['cowpro_repayment_schedule'] );
	$repayment_schedules = entity_load ( 'cowpro_repayment_schedule', $ids );
	return $repayment_schedules;
}

function _cowpro_issuing_creditor_assignment_form($form, &$form_state) {
	$node = $form_state ['node'];
	$issuing = $node->field_issuing [LANGUAGE_NONE] [0];
	$issuing_id = $node->nid;
	$repayment_schedules = _cowpro_issuing_get_assignable_schedules($issuing_id);
	$values = array_values ( $repayment_schedules );
	$repayment = array_shift ( $values );
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

	$tips = '<ul>';
	$tips .= '<li>债权转让期间，如果到债务人进行还款付息操作的时候仍然无人承接，将自动撤销转让。</li>';
	$tips .= '<li>债权转让的费用为转让管理费。平台向转出人收取，不向购买人收取任何费用。</li>';
	$tips .= '</ul>';
	$form ['tips'] = array (
			'#type' => 'markup',
			'#markup' => $tips,
	);

	$form ['amount'] = array (
			'#type' => 'numberfield',
			'#title' => '转让金额(元)',
			'#description' => '',
			'#min' => 1,
			'#max' => $bid_avail,
			'#input' => TRUE,
	);
	$form ['submit'] = array (
			'#type' => 'submit',
			'#value' => '转让',
	);
	$form ['cancel'] = array (
			'#type' => 'submit',
			'#value' => '取消',
	);

	return $form;
}

/**
 * Validation callback for _cowpro_issuing_creditor_assignment_form().
 */
function _cowpro_issuing_creditor_assignment_form_validate($form, &$form_state) {
	if ($form_state ['values'] ['op'] === $form_state ['values'] ['submit']) {
		//在这里对转让金额进行有效性验证，$form_state ['values']['amount']
		//form_set_error ( 'bid', '请填写有效的投资金额(大于零)' );
		/*
		$bid_avail = _cowpro_issuing_bid_avail($form_state['nid'], $form_state['loan_amounts']);
		if ($form_state ['values']['amount'] > $bid_avail) {
			form_set_error ( 'bid', "请注意，当前最大可投资金额为 $bid_avail 元" );
		}
		if ($form_state ['values']['amount'] <= 0) {
			form_set_error ( 'bid', '请填写有效的投资金额(大于零)' );
		}
		*/
	}
}

function _cowpro_issuing_creditor_assignment_form_submit(&$form, &$form_state) {
	if ($form_state ['values'] ['op'] === $form_state ['values'] ['submit']) {
		$amount = $form_state['input']['amount'];
		$amount = floatval($amount);
		$node = $form_state ['node'];
		$issuing_id = $node->nid;
		$repayment_schedules = _cowpro_issuing_get_assignable_schedules($issuing_id);
		foreach ( $repayment_schedules as $schedule_id => $repayment ) {
			$repayment->status = 'ASSIGNABLE';
			$next_data_serial = _cowpro_issuing_get_repayment_schedule_data_serial($repayment);
			$repayment->data[] = array(
					'serial' => $next_data_serial,
					'timestamp' => time(),
					'operate' => 'creditor_assignment',
					'amount' => $amount,//转让价格
			);
			entity_save ( 'cowpro_repayment_schedule', $repayment );
		}

		$args = array();
		$args[] = $amount;
		$args[] = $issuing_id;
		$args[] = $repayment_schedules;
		$hook = 'cowpro_issuing_creditor_assignment';
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
			$message = '开始转让...';
			drupal_set_message($message);
		} else {
			$message = '转让失败:' . $return['message'] . '<br/>代码：' . $return['result_code'];
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
