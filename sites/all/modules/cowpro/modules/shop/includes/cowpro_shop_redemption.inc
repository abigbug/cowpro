<?php
function cowpro_shop_redemption_form($form, &$form_state) {
	form_load_include ( $form_state, 'inc', 'cowpro_shop', 'cowpro_shop_redemption' );

	$uid = $GLOBALS ['user']->uid;
	$max_points = userpoints_get_current_points($uid, _cowpro_shop_get_user_points_money_tid());
	$max_points = $max_points / 100;

	$form = array ();
	$form ['help'] = array (
			'#markup' => '最大可兑现数量：' . $max_points,
	);
	$form ['points'] = array (
			'#type' => 'textfield',
			'#title' => '数量',
			'#default_value' => $max_points,
			'#size' => 8,
			'#maxlength' => 8,
			'#required' => TRUE
	);
	$form ['submit'] = array (
			'#type' => 'submit',
			'#name' => 'submit',
			'#value' => '确认兑现',
			'#ajax' => array (
					'callback' => 'cowpro_shop_redemption_done'
			)
	);
	$form ['cancel'] = array (
			'#markup' => l ( '取消', '#', array (
					'attributes' => array (
							'class' => 'ctools-close-modal'
					)
			) )
	);
	return $form;
}
function cowpro_shop_redemption_done($form, &$form_state) {
	$uid = $GLOBALS ['user']->uid;
	$max_points = userpoints_get_current_points($uid, _cowpro_shop_get_user_points_money_tid());
	$max_points = $max_points / 100;

	ctools_include ( 'modal' );
	ctools_include ( 'ajax' );
	if (!is_numeric($form_state['input'] ['points'])) {
		$error = '请输入有效的兑现数量！';
		ctools_ajax_render_error ( $error );
	} else if (intval($form_state['input'] ['points']) > $max_points) {
		$error = "可兑现数量最多为$max_points ！";
		ctools_ajax_render_error ( $error );
	} else if (intval($form_state['input'] ['points']) < 100) {
		$error = "兑现数量必须大于等于100，或者是100的整数倍 ！";
		ctools_ajax_render_error ( $error );
	} else if (intval($form_state['input'] ['points']) % 100 != 0) {
		$error = "兑现数量必须大于等于100，或者是100的整数倍 ！";
		ctools_ajax_render_error ( $error );
	} else {
		$amount = intval($form_state['input'] ['points']);
		$uid_from = NULL;//user_load_by_name ( variable_get ( 'fund_imprest_account', '' ) )->uid; // 转出账户ID
		global $user;
		$uid_to = $user->uid;
		$comment = '(' . $user->name . ')' . '兑现奖金';

		$result = custodian_cowpro_fund_internal_trans($uid_from, $uid_to, $amount, $comment);

		if ($result['success']) {
			$term = current ( taxonomy_get_term_by_name ( '奖金' ) );
			$desc = "兑现奖金：" . $amount . "元";
			$params = array (
					'uid' => $user->uid,
					'points' => 0 - $amount * 100,
					'description' => $desc,
					'display' => false,
					'tid' => $term->tid,
			);
			userpoints_userpointsapi ( $params );
			drupal_set_message('转账成功');
		} else {
			drupal_set_message('转账失败，' . $result['message'], 'warning');
			watchdog('internal_trans', $result['message']. '; code:' . $result['result_code']);
		}

		$commands = array ();
		$url = $GLOBALS['base_url'] . '/myuserpoints';
		$commands[] = ctools_ajax_command_redirect($url, 0);
		print ajax_render ( $commands );
		exit ();
	}
}
/*
function _cowpro_fund_withdraw_callback($success, $journal_id, $external_reference_id, $interface_module, $result) {
	if ($success) {
		$entity = entity_load_single('cowpro_fund_journal', $journal_id);
		$entity->status = TRUE;
		$entity->external_reference_id = $external_reference_id;
		$data = array();
		$data['interface_module'] = $interface_module;
		$data['result'] = $result;
		$entity->data = $data;
		entity_get_controller('cowpro_fund_journal')->save($entity);
	}

	$args = array();
	$args[] = $success;
	$args[] = $journal_id;
	$hook = 'cowpro_fund_withdraw_finished';
	foreach (module_implements($hook) as $module) {
		$function = $module . '_' . $hook;
		if (function_exists($function)) {
			call_user_func_array($function, $args);
		}
	}
}
*/