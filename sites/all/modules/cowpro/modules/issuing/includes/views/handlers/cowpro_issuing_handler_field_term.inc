<?php

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

class cowpro_issuing_handler_field_term extends views_handler_field {
  function render($values) {
  	$path = drupal_get_path ( 'module', 'cowpro_issuing' );
  	include_once $path . '/includes/cowpro_issuing.repayment_schedule.fun.inc';

  	//$issuing_id = $this->get_value($values, 'entity_id');
  	$issuing_id = $values->nid;
  	$node = node_load($issuing_id);
  	$issuing = $node->field_issuing [LANGUAGE_NONE] [0];
  	$loan_term_readable = _cowpro_issuing_get_readable_loan_term($issuing ['loan_term']);

    return $loan_term_readable;
  }
}
