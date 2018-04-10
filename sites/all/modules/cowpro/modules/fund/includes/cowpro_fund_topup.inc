<?php

function cowpro_fund_topup($form, &$form_state) {
	$form = array();
	$form['topup_information'] = array(
			'#markup' => '<ul><li>即时充值所产生的转账费用，由第三方平台收取，充值费用视平台而定。</li><li>请注意您的银行卡充值限制，以免造成不便。</li><li><a href=http://www.jinbeizeng.com/node/749>快捷支付限额表</a></li><li><a href=http://www.jinbeizeng.com/node/748>个人网银限额表</a></li><li>如果充值金额没有及时到账，请和客服联系。</li><li>充值必须大于1元</li></ul>',
	);

	$custodian_key = custodian_default_provider_key();
	$custodian_title = custodian_readable_provider_title($custodian_key);
	$interface = array($custodian_key => $custodian_title);
	$form['topup_interface'] = array(
			'#type' => 'radios',
			'#title' => '充值渠道',
			'#default_value' => $custodian_key,
			'#options' => $interface,
			'#description' => '',
	);

	$form ['amount'] = array (
			'#type' => 'numberfield',
			'#title' => '充值金额(元)',
			'#min' => 0,
			'#max' => 999999,
			'#default_value' => 0,
			'#input' => TRUE,
	);

	$method = custodian_get_topup_method();
	if ($method != NULL) {
		reset($method);
		$first_key = key($method);
		$form['topup_method'] = array(
				'#type' => 'radios',
				'#title' => '充值方式',
				'#default_value' => $first_key,
				'#options' => $method,
				'#description' => '',
		);
	}

	$form['topup'] = array(
			'#type' => 'submit',
			'#value' => '充值',
	);

	return $form;

}

/**
 * Form validate handler for the fund_topup form.
 */
function cowpro_fund_topup_validate($form, &$form_state) {
	if ($form_state['values']['amount'] <= 0) {
		form_set_error ( '充值', '充值金额必须大于零.' );
	}
}

function cowpro_fund_topup_submit($form, &$form_state) {
	$amount = $form_state['input']['amount'];
	$method = isset($form_state['input']['topup_method']) ? $form_state['input']['topup_method'] : '';
	//$moudle = $form_state['input']['topup_interface'];

	$uid = $GLOBALS['user']->uid;
	$entity_value = array(
			'uid' => $uid,
			'status' => 99,
			'type' => 'TOPUP',
			'amount' => $amount,
	);
	$entity = entity_create('cowpro_fund_journal', $entity_value);
	$entity = entity_get_controller('cowpro_fund_journal')->save($entity);
	$journal_id = $entity->journal_id;

	$result = custodian_cowpro_fund_topup($uid, $amount, $method, $journal_id);
	if (isset($result['success']) && $result['success']) {
		drupal_set_message($result['message']);
	} else if (isset($result['success']) && !$result['success']) {
		drupal_set_message($result['message'], 'error');
	}
}

function _cowpro_fund_topup_callback($success, $journal_id, $external_reference_id, $interface_module, $result) {
	$entity = entity_load_single('cowpro_fund_journal', $journal_id);
	$entity->status = $success;
	if (isset($external_reference_id)) {
		$entity->external_reference_id = $external_reference_id;
	}
	$data = array();
	$data['interface_module'] = $interface_module;
	$data['result'] = $result;
	$entity->data = $data;
	entity_get_controller('cowpro_fund_journal')->save($entity);

	$args = array();
	$args[] = $success;
	$args[] = $journal_id;
	$hook = 'cowpro_fund_topup_finished';
	foreach (module_implements($hook) as $module) {
		$function = $module . '_' . $hook;
		if (function_exists($function)) {
			call_user_func_array($function, $args);
		}
	}
}