<?php

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

class cowpro_issuing_handler_field_loan_amounts extends views_handler_field {
  function render($values) {

  	//$issuing_id = $this->get_value($values, 'entity_id');
  	$issuing_id = $values->nid;
  	$node = node_load($issuing_id);
  	$issuing = $node->field_issuing [LANGUAGE_NONE] [0];
  	$loan_amounts = $issuing ['loan_amounts'];

    return $loan_amounts;
  }
}
