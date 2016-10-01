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
class cowpro_fund_journal_handler_field_status extends views_handler_field {
  function render($values) {
  	$options = array();
  	$options[1] = '成功';
  	$options[0] = '失败';
  	$options[2] = '流标返款';

    $value = $this->get_value($values);

    return $options[$value];
  }
}
