<?php
function cowpro_fund_withdraw($form, &$form_state) {
	$form = array ();

	$custodian_key = custodian_default_provider_key();
	$custodian_title = custodian_readable_provider_title($custodian_key);
	$interface = array($custodian_key => $custodian_title);
	$form ['withdraw_interface'] = array (
			'#type' => 'radios',
			'#title' => '提现渠道',
			'#default_value' => $custodian_key,
			'#options' => $interface,
			'#description' => ''
	);

	$form += cowpro_fund_get_bankcard ();

	GLOBAL $user;
	$balance = custodian_get_balance($user);
	$withdraw = 0;
	if ($balance) {
		$withdraw = $balance ['withdraw'];
	}

	$form ['withdraw_balance'] = array (
			'#markup' => "<p>可提现余额(元)：$withdraw</p>",
	);
	$form ['amount'] = array (
			'#type' => 'numberfield',
			'#title' => '提现金额(元)',
			'#step' => 0.01,
			'#min' => 0,
			'#max' => 999999,
			'#default_value' => 0,
			'#input' => TRUE
	);

	$form ['withdraw'] = array (
			'#type' => 'submit',
			'#value' => '提现'
	);

	return $form;
}
function cowpro_fund_withdraw_validate($form, &$form_state) {
	if ($form_state['clicked_button']['#name'] == 'op') {
		if (( float ) trim ( $form_state ['input'] ['amount'] ) <= 0) {
			form_error ( $form ['amount'], "请填写有效的提现金额" );
		}
	}
}
function cowpro_fund_withdraw_submit($form, &$form_state) {
	if ($form_state['clicked_button']['#name'] == 'op') {
		$uid = $GLOBALS['user']->uid;
		$amount = $form_state ['input'] ['amount'];
		$card = cowpro_customer_profile_load_one_row_with_conditions ( $uid, 'bank_card' );
		$entity_value = array(
				'uid' => $uid,
				'status' => FALSE,
				'type' => 'WITHDRAW',
				'amount' => $amount,
		);
		$entity = entity_create('cowpro_fund_journal', $entity_value);
		$entity = entity_get_controller('cowpro_fund_journal')->save($entity);
		$journal_id = $entity->journal_id;

		$result = custodian_cowpro_fund_withdraw($uid, $amount,	$card, $journal_id);
	} else if ($form_state['clicked_button']['#name'] == 'bankcard_operator') {
		$uid = $GLOBALS ['user']->uid;
		$profile = cowpro_customer_profile_load_one_row_with_conditions ( $uid, 'bank_card' );
		custodian_bank_card_operator_submit($form_state ['values'] ['operator'], $profile);
	} else if ($form_state['clicked_button']['#name'] == 'add_bankcard') {
		$form_state['redirect'] = 'registration_wizard/bank_card';
	}
}
function cowpro_fund_get_bankcard($reset = FALSE) {
	$form = array ();
	$form ['bankcard'] = array (
			'#type' => 'fieldset',
			'#title' => '',
			'#prefix' => '<div id="bankcard">',
			'#suffix' => '</div>'
	);

	$uid = $GLOBALS ['user']->uid;
	$profile = cowpro_customer_profile_load_one_row_with_conditions ( $uid, 'bank_card' );
	if ($profile) {
		$form['bankcard']['bankcard_information'] = array(
				'#markup' => _cowpro_fund_withdraw_mask($profile->card_no, 4, 8) . '@' . $profile->cardholder . '@' . $profile->bank_name . '<br/>',
		);
		$operator = custodian_get_bank_card_operator($profile);
		if ($operator != NULL) {
			$form['bankcard'] ['operator'] = array (
					'#type' => 'submit',
					'#name' => 'bankcard_operator',
					'#value' => $operator,
					//'#submit' => array('cowpro_customer_customer_profile_form_submit'),
			);
		}

	} else {
		$form ['bankcard']['add_bankcard'] = array(
				'#type' => 'button',
				'#name' => 'add_bankcard',
				'#value' => '添加银行卡',
		);
	}
	return $form;
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
function _cowpro_fund_withdraw_mask ( $str, $start = 0, $length = null ) {
	$mask = preg_replace ( "/\S/", "*", $str );
	if( is_null ( $length )) {
		$mask = substr ( $mask, $start );
		$str = substr_replace ( $str, $mask, $start );
	}else{
		$mask = substr ( $mask, $start, $length );
		$str = substr_replace ( $str, $mask, $start, $length );
	}
	return $str;
}