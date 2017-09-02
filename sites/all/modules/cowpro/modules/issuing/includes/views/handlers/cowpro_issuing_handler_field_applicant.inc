<?php

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

class cowpro_issuing_handler_field_applicant extends views_handler_field {
  function render($values) {
  	//$issuing_id = $this->get_value($values, 'entity_id');
  	$issuing_id = $values->nid;
  	$node = node_load($issuing_id);
  	$uid = $node->field_applicant[LANGUAGE_NONE] [0]['uid'];

  	$profile_real_name = cowpro_customer_profile_load_one_row_with_conditions ( $uid, 'real_name' );
  	if ($profile_real_name) {
  		$real_name = $profile_real_name->name;
  	} else {
  		$real_name = '';
  	}
  	$user = user_load($uid);
  	$userpath = 'user/' . $user->uid;
  	$result = l($user->name . "($real_name)", $userpath);
  	return $result;
  }
}
