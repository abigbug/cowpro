<?php
include_once 'moneymoremore.const.inc';
function _moneymoremore_settings_form($form, &$form_state) {
	$form = $form + _moneymoremore_get_settings_element();
	/*
	$form['actions'] = array(
			'#type' => 'actions',
	);
	$form['actions']['submit'] = array(
			'#type' => 'submit',
			'#value' => t("Save"),
			'#weight' => 10,
	);
	return system_settings_form($form);
	*/
	return $form;
}

function _moneymoremore_get_settings_element() {
	$element = array();
	$element['platform_account_on_moneymoremore'] = array(
			'#type' => 'textfield',
			'#title' => '平台账号',
			'#default_value' => variable_get(PLATFORM_ACCOUNT_ON_MONEYMOREMORE, ''),
			'#description' => 'P2P平台在乾多多服务器的账号，由乾多多提供',
			'#size' => 60,
			'#maxlength' => 60,
			'#required' => TRUE,
	);
	$element['public_key_on_moneymoremore'] = array(
			'#type' => 'textarea',
			'#title' => '公钥',
			'#default_value' => variable_get(PUBLIC_KEY_ON_MONEYMOREMORE, ''),
			'#description' => '用于与乾多多服务器进行加密通信的公钥，由乾多多提供',
			'#required' => TRUE,
	);
	$element['private_key_on_moneymoremore'] = array(
			'#type' => 'textarea',
			'#title' => '私钥',
			'#default_value' => variable_get(PRIVATE_KEY_ON_MONEYMOREMORE, ''),
			'#description' => '用于与乾多多服务器进行加密通信的私钥，由乾多多提供',
			'#required' => TRUE,
	);

	return $element;
}
