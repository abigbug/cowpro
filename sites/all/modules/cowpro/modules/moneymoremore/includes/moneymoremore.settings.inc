<?php
include_once 'moneymoremore.const.inc';
function _moneymoremore_settings_form($form, &$form_state) {
	$form = $form + _moneymoremore_get_settings_element();
	return system_settings_form($form);
}

function _moneymoremore_get_settings_element() {
	$element = array();
	$element[PLATFORM_ACCOUNT_ON_MONEYMOREMORE] = array(
			'#type' => 'textfield',
			'#title' => '平台账号',
			'#default_value' => variable_get(PLATFORM_ACCOUNT_ON_MONEYMOREMORE, ''),
			'#description' => 'P2P平台在乾多多服务器的账号，由乾多多提供',
			'#size' => 60,
			'#maxlength' => 60,
			'#required' => TRUE,
	);
	$element[PUBLIC_KEY_ON_MONEYMOREMORE] = array(
			'#type' => 'textarea',
			'#title' => '公钥',
			'#default_value' => variable_get(PUBLIC_KEY_ON_MONEYMOREMORE, ''),
			'#description' => '用于与乾多多服务器进行加密通信的公钥，由乾多多提供',
			'#required' => TRUE,
	);
	$element[PRIVATE_KEY_ON_MONEYMOREMORE] = array(
			'#type' => 'textarea',
			'#title' => '私钥',
			'#default_value' => variable_get(PRIVATE_KEY_ON_MONEYMOREMORE, ''),
			'#description' => '用于与乾多多服务器进行加密通信的私钥，由乾多多提供',
			'#required' => TRUE,
	);

	return $element;
}
