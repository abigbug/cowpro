<?php

/**
 * @file
 * Definition of cowpro_fund_journal_handler_field_status.
 */

/**
 * Field handler to output the name of journal status.
 *
 * @ingroup views_field_handlers
 */
class cowpro_shop_deliver_handler_field_status extends views_handler_field {
  function render($values) {
  	$options = array();
  	$options[0] = '未处理';
  	$options[1] = '已处理';

    $value = $this->get_value($values);

    if ($value === NULL) {
    	return $options[0];
    } else {
    	return $options[$value];
    }
  }
}
