<?php

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

class cowpro_issuing_handler_field_annual_rate extends views_handler_field {
  function render($values) {
 
  	//$issuing_id = $this->get_value($values, 'entity_id');
  	$issuing_id = $this->get_value($values);
  	$node = node_load($issuing_id);
  	$issuing = $node->field_issuing [LANGUAGE_NONE] [0];
  	$annual_rate = $issuing ['annual_rate'];

    return $annual_rate."%";
  }
}
