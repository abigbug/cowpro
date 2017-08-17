<?php
function cowpro_shop_redemption_form($form, &$form_state) {
	$uid = $GLOBALS ['user']->uid;
	$max_points = userpoints_get_current_points($uid, _cowpro_shop_get_user_points_money_tid());

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

	ctools_include ( 'modal' );
	ctools_include ( 'ajax' );
	if (!is_numeric($form_state['input'] ['points'])) {
		$error = '请输入有效的兑现数量！';
		ctools_ajax_render_error ( $error );
	} else if (intval($form_state['input'] ['points']) > $max_points) {
		$error = "可兑现数量最多为$max_points ！";
		ctools_ajax_render_error ( $error );
	} else {

		drupal_set_message('兑现成功！');

		$commands = array ();
		$commands [] = ajax_command_replace ( '#bankcard-list', drupal_render ( $element ) );
		$commands [] = ctools_modal_command_dismiss ();
		print ajax_render ( $commands );
		exit ();
	}
}
function cowpro_shop_ctools_modal_dismiss() {
	ctools_include ( 'modal' );
	ctools_include ( 'ajax' );
	$commands = array ();
	$commands[] = ctools_modal_command_dismiss();
	$commands[] = ctools_ajax_command_redirect();
	print ajax_render ( $commands );
	exit ();
}
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
