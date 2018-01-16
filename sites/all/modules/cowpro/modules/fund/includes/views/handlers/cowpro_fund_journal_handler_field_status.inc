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
  	$options[99] = '未知';

  	$msg = NULL;
    $value = $this->get_value($values);
    if ($value == 0) {
    	$journal_id = $values->cowpro_fund_journal_journal_id;
    	$entity = entity_load_single('cowpro_fund_journal', $journal_id);
    	$data = $entity->data;
    	if ($data && array_key_exists('interface_module', $data)) {
    		$function = $data['interface_module'] . '_result_parser';
    		if (function_exists($function)) {
    			$msg = $function($values->cowpro_fund_journal_type, $data);
    		}
    	}
    }

    if ($msg != NULL) {
    	return $options[$value] . "($msg)";
    } else {
    	return $options[$value];
    }
  }
}
