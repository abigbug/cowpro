<?php

function cowpro_fund_topup($form, &$form_state) {
	$form = array();
	$form['topup_information'] = array(
			'#markup' => '<ul><li>即时充值所产生的转账费用，由第三方平台收取，充值费用视平台而定。</li><li>请注意您的银行卡充值限制，以免造成不便。</li><li>如果充值金额没有及时到账，请和客服联系。</li></ul>',
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

	$method = array(
			'' => '网银充值',
			'2' => '快捷支付',
			'3' => '汇款充值',
			'4' => '企业网银',
	);
	$form['topup_method'] = array(
			'#type' => 'radios',
			'#title' => '充值方式',
			'#default_value' => '',
			'#options' => $method,
			'#description' => '',
	);

	$form['topup'] = array(
			'#type' => 'submit',
			'#value' => '充值',
	);

	return $form;

}

function cowpro_fund_topup_submit($form, &$form_state) {
	$amount = $form_state['input']['amount'];
	$method = $form_state['input']['topup_method'];
	//$moudle = $form_state['input']['topup_interface'];

	$uid = $GLOBALS['user']->uid;
	$entity_value = array(
			'uid' => $uid,
			'status' => FALSE,
			'type' => 'TOPUP',
			'amount' => $amount,
	);
	$entity = entity_create('cowpro_fund_journal', $entity_value);
	$entity = entity_get_controller('cowpro_fund_journal')->save($entity);
	$journal_id = $entity->journal_id;

	$result = custodian_cowpro_fund_topup($uid, $amount, $method, $journal_id);
}

function _cowpro_fund_topup_callback($success, $journal_id, $external_reference_id, $interface_module, $result) {
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
	$hook = 'cowpro_fund_topup_finished';
	foreach (module_implements($hook) as $module) {
		$function = $module . '_' . $hook;
		if (function_exists($function)) {
			call_user_func_array($function, $args);
		}
	}
}