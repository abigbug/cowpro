<?php

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

class cowpro_userpoints_txn_handler_field_status extends views_handler_field {
  function render($values) {
  	$status = $this->get_value($values);
  	$status_array = userpoints_txn_status();
  	return $status_array[$status];
  }
}
