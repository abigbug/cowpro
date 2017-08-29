<?php

class cowpro_report_handler_field_referee extends views_handler_field {
  function render($values) {
  	$result = '';
    $uid = $this->get_value($values);

    $relationship_type = user_relationships_type_load(array('name'=>'朋友'));
    $relationships = user_relationships_load(array(
    		'requester_id' => $uid,
    		'rtid'    => $relationship_type->rtid,
    ));

    $relationship = array_shift($relationships);
    if ($relationship) {
    	$uid_referree = $relationship->requestee_id;

    	$profile_real_name = cowpro_customer_profile_load_one_row_with_conditions ( $uid_referree, 'real_name' );
    	if ($profile_real_name) {
    		$real_name = $profile_real_name->name;
    	} else {
    		$real_name = '';
    	}

    	$user_referree = user_load($uid_referree);
    	$userpath = 'user/' . $user_referree->uid;
    	$result = l($user_referree->name . "($real_name)", $userpath);
    }
    return $result;
  }
}
