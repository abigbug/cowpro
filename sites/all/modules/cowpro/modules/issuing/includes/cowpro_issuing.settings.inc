<?php
function cowpro_issuing_settings_form($form, &$form_state) {
	$form = $form + _cowpro_issuing_get_settings_element();
	$form['actions'] = array(
			'#type' => 'actions',
	);
	$form['actions']['submit'] = array(
			'#type' => 'submit',
			'#value' => t("Save"),
			'#weight' => 10,
	);
	return system_settings_form($form);
}

function _cowpro_issuing_get_settings_element($issuing = NULL) {
	$data = isset($issuing) && isset($issuing['data']) ? $issuing['data'] : array();
	$element = array();
	$element['deal_service_fee'] = array(
			'#type' => 'numberfield',
			'#title' => '成交服务费',
			'#default_value' => isset($data['deal_service_fee']) ? $data['deal_service_fee'] : variable_get('deal_service_fee', 0),
			'#precision' => 3,
			'#decimals' => 0,
			'#minimum' => 0,
			'#maximum' => 999,
			'#description' => '% 成交服务费 = 本金总额×服务费率 0即不收取',
	);
	$element['borrower_management_fee'] = array(
			'#type' => 'numberfield',
			'#title' => '借款者管理费',
			'#default_value' => isset($data['borrower_management_fee']) ? $data['borrower_management_fee'] : variable_get('borrower_management_fee', 0),
			'#precision' => 3,
			'#decimals' => 0,
			'#minimum' => 0,
			'#maximum' => 999,
			'#description' => '% 管理费 = 本金总额×管理费率 0即不收取',
	);
	$element['investor_management_fee'] = array(
			'#type' => 'numberfield',
			'#title' => '投资者管理费',
			'#default_value' => isset($data['investor_management_fee']) ? $data['investor_management_fee'] : variable_get('investor_management_fee', 0),
			'#precision' => 3,
			'#decimals' => 0,
			'#minimum' => 0,
			'#maximum' => 999,
			'#description' => '% 管理费 = 投资总额×管理费率 0即不收取',
	);
	$element['interest_management_fee'] = array(
			'#type' => 'numberfield',
			'#title' => '投资者利息管理费',
			'#default_value' => isset($data['interest_management_fee']) ? $data['interest_management_fee'] : variable_get('interest_management_fee', 0),
			'#precision' => 3,
			'#decimals' => 0,
			'#minimum' => 0,
			'#maximum' => 999,
			'#description' => '% 管理费 = 实际得到的利息×管理费率 0即不收取(如果是VIP会员将从VIP会员配置里读取)',
	);
	$element['charges_for_late_payments'] = array(
			'#type' => 'numberfield',
			'#title' => '普通逾期管理费',
			'#default_value' => isset($data['charges_for_late_payments']) ? $data['charges_for_late_payments'] : variable_get('charges_for_late_payments', 0),
			'#precision' => 3,
			'#decimals' => 0,
			'#minimum' => 0,
			'#maximum' => 999,
			'#description' => '% 逾期管理费总额 = 逾期本息总额×对应逾期管理费率×逾期天数 0即不收取',
	);
	$element['charges_for_serious_overdue'] = array(
			'#type' => 'numberfield',
			'#title' => '严重逾期管理费',
			'#default_value' => isset($data['charges_for_serious_overdue']) ? $data['charges_for_serious_overdue'] : variable_get('charges_for_serious_overdue', 0),
			'#precision' => 3,
			'#decimals' => 0,
			'#minimum' => 0,
			'#maximum' => 999,
			'#description' => '% 逾期管理费总额 = 逾期本息总额×对应逾期管理费率×逾期天数 0即不收取',
	);

	$element['assignment_of_credit_management_fee'] = array(
			'#type' => 'numberfield',
			'#title' => '债权转让管理费',
			'#default_value' => isset($data['assignment_of_credit_management_fee']) ? $data['assignment_of_credit_management_fee'] : variable_get('assignment_of_credit_management_fee', 0),
			'#precision' => 3,
			'#decimals' => 0,
			'#minimum' => 0,
			'#maximum' => 999,
			'#description' => '% 管理费 = 转让金额×管理费率 0即不收取',
	);
	$element['prepayment_penalty'] = array(
			'#type' => 'numberfield',
			'#title' => '提前还款罚金',
			'#default_value' => isset($data['prepayment_penalty']) ? $data['prepayment_penalty'] : variable_get('prepayment_penalty', 0),
			'#precision' => 3,
			'#decimals' => 0,
			'#minimum' => 0,
			'#maximum' => 999,
			'#description' => '% 罚金 = 剩余本金×补偿利率 0即不收取',
	);
	$element['investor_rebate'] = array(
			'#type' => 'numberfield',
			'#title' => '投资人返利',
			'#default_value' => isset($data['investor_rebate']) ? $data['investor_rebate'] : variable_get('investor_rebate', 0),
			'#precision' => 3,
			'#decimals' => 0,
			'#minimum' => 0,
			'#maximum' => 999,
			'#description' => '% 返利金额=投标金额×返利百分比【需满标】',
	);
/*
	 借款者获得积分:
	 borrower gain points
	 0
	 【非信用积分】

	 投资返还积分比率:
	 Investor gain points
	 0
	 % 投标返还积分 = 投标金额 ×返还比率【需满标】(如果是VIP会员将从VIP会员配置里读取)【非信用积分】

	 申请延期:
	 100.00
	 % 当还款金额大于或等于设置的额度，借款人如果资金不够，可申请延期还款，延期还款就是平台代其还此借款。借款人未还部分由平台跟借款人协商。
	 */

	//允许扩展模块对“贷款申请表”的内容进行扩充
	$element = $element + module_invoke_all('cowpro_issuing_get_settings_element', $issuing);

	return $element;
}