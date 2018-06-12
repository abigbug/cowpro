<?php
include_once 'jiupaipay.const.inc';
function _jiupaipay_settings_form($form, &$form_state) {
	$form = $form + _jiupaipay_get_settings_element ();
	return system_settings_form ( $form );
}
function _jiupaipay_get_settings_element() {
	$element = array ();
	$element [PLATFORM_ACCOUNT_ON_JIUPAIPAY] = array (
			'#type' => 'textfield',
			'#title' => '平台账号',
			'#default_value' => variable_get ( PLATFORM_ACCOUNT_ON_JIUPAIPAY, '' ),
			'#description' => 'P2P平台在九派支付服务器的账号，由九派支付提供',
			'#size' => 60,
			'#maxlength' => 60,
			'#required' => TRUE
	);
	$element [PUBLIC_KEY_ON_JIUPAIPAY] = array (
			'#type' => 'textarea',
			'#title' => '公钥',
			'#default_value' => variable_get ( PUBLIC_KEY_ON_JIUPAIPAY, '' ),
			'#description' => '用于与九派支付服务器进行加密通信的公钥，由九派支付提供',
			'#required' => TRUE,
	);
	$element [PRIVATE_KEY_ON_JIUPAIPAY] = array (
			'#type' => 'textarea',
			'#title' => '私钥',
			'#default_value' => variable_get ( PRIVATE_KEY_ON_JIUPAIPAY, '' ),
			'#description' => '用于与九派支付服务器进行加密通信的私钥，由九派支付提供',
			'#required' => TRUE,
	);

	return $element;
}
