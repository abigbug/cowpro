<?php

/**
 * @file
 * Definition of views_handler_filter_string.
 */

/**
 * Basic textfield filter to handle string filtering commands
 * including equality, like, not like, etc.
 *
 * @ingroup views_filter_handlers
 */
class cowpro_rewards_issuing_large_handler_filter_user_real_name extends views_handler_filter {
  // exposed filter options
  var $always_multiple = TRUE;

  function option_definition() {
  	$options = parent::option_definition();

  	$options['expose']['contains']['required'] = array('default' => FALSE, 'bool' => TRUE);

  	return $options;
  }

  /*function operators() {
  	$operators = array(
  			'=' => array(
  					'title' => t('Is equal to'),
  					'short' => t('='),
  					'method' => 'op_equal',
  					'values' => 1,
  			),
  	);

  	return $operators;
  }*/

  /**
   * Build strings from the operators() for 'select' options
   */
  /*
  function operator_options($which = 'title') {
  	$options = array();
  	foreach ($this->operators() as $id => $info) {
  		$options[$id] = $info[$which];
  	}

  	return $options;
  }
  */

  function admin_summary() {
  }

  function operator_form(&$form, &$form_state) {
  	$form['operator'] = array();
  }

  /*function value_validate($form, &$form_state) {

  	$matches = array();
  	$regex = '/^\d+$/';
  	$value = trim($form_state['values']['options']['value']);
  	$uid = -1;
  	if(preg_match($regex, $value, $matches)){
  		$result = db_select('cowpro_customer_profile', 'profile')->fields('profile', array('uid'))->condition('type', 'mobile')->condition('search_field', $value)->execute()->fetchAssoc();
  		if ($result) {
  			$uid = $result['uid'];
  		}
  	} else if ($value != '') {
  		$user = user_load_by_name($value);
  		if ($user !== FALSE) {
  			$uid = $user->uid;
  		}
  	}
	$form_state['values']['options']['value'] = $uid;
  }*/

  /*
  function accept_exposed_input($input) {
  	$rc = parent::accept_exposed_input($input);

  	if ($rc) {
  		// If we have previously validated input, override.
  		if (isset($this->validated_exposed_input)) {
  			$this->value = $this->validated_exposed_input;
  		}
  	}

  	return $rc;
  }
  */

  function value_form(&$form, &$form_state) {
  	$form['value'] = array(
  			'#type' => 'textfield',
  			'#title' => '用户的手机号码或者昵称',
  			'#description' => '输入用户的手机号码或昵称.',
  			'#autocomplete_path' => 'cowpro/referee/autocomplete',
  	);
  }

  function query() {
  	$matches = array();
  	$regex = '/^\d+$/';
  	$value = trim($this->value);
  	$uid = -1;
  	if(preg_match($regex, $value, $matches)){
  		$result = db_select('cowpro_customer_profile', 'profile')->fields('profile', array('uid'))->condition('type', 'mobile')->condition('search_field', $value)->execute()->fetchAssoc();
  		if ($result) {
  			$uid = $result['uid'];
  		}
  	} else if ($value != '') {
  		$user = user_load_by_name($value);
  		if ($user !== FALSE) {
  			$uid = $user->uid;
  		}
  	}

  	$this->query->add_where($this->options['group'], "cowpro_rewards_issuing_large.uid", $uid, "=");
  }
}
