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
class cowpro_issuing_handler_filter_issuing_title extends views_handler_filter {
  // exposed filter options
  var $always_multiple = TRUE;

  function option_definition() {
  	$options = parent::option_definition();

  	$options['expose']['contains']['required'] = array('default' => FALSE, 'bool' => TRUE);

  	return $options;
  }

  /*
  function operators() {
  	$operators = array(
  			'=' => array(
  					'title' => t('Is equal to'),
  					'short' => t('='),
  					'method' => 'op_equal',
  					'values' => 1,
  			),
  	);

  	return $operators;
  }
  */

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

  /*
  function value_validate($form, &$form_state) {

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
  }
  */

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
  			'#title' => '贷款标题',
  			'#description' => '输入贷款标题，可以是标题中的关键字.',
  			'#autocomplete_path' => 'issuing/autocomplete',
  	);
  }

  function query() {
  	$title = trim($this->value);
  	$result = db_select('node')->fields('node', array('nid', 'title'))->condition('type', 'cowpro_issuing', '=')->condition('title', $title, '=')->execute()->fetchAssoc();
	$nid = $result['nid'];
	$table = $this->ensure_my_table();
  	$this->query->add_where($this->options['group'], "$table.nid", $nid, "=");
  }
}
