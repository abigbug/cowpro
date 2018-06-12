<?php
function cowpro_fund_settings_form($form, &$form_state) {
	$form ['fund_imprest_account'] = array (
			'#title' => '备用金账户',
			'#type' => 'textfield',
			'#autocomplete_path' => 'user/autocomplete',
			'#default_value' => variable_get ( 'fund_imprest_account', '' ),
	);
	return system_settings_form($form);
}
