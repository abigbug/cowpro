<?php

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

class cowpro_issuing_handler_field_progress extends views_handler_field {
  function render($values) {
  	$path = drupal_get_path ( 'module', 'cowpro_issuing' );
  	include_once $path . '/includes/cowpro_issuing.bid.inc';

  	$issuing_id = $this->get_value($values, 'entity_id');
  	$node = node_load($issuing_id);
  	$issuing = $node->field_issuing [LANGUAGE_NONE] [0];
  	$bid_avail = _cowpro_issuing_bid_avail ( $node->nid, $issuing['loan_amounts'] );
    $progress = (int)((($issuing ['loan_amounts']-$bid_avail) / $issuing ['loan_amounts']) * 100);

    return $progress;
  }
}
