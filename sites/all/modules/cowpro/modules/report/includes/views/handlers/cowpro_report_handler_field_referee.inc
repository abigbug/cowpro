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
    	$user_referree = user_load($uid_referree);
    	$userpath = 'user/' . $user_referree->uid;
    	$result = l($user_referree->name, $userpath);
    }
    return $result;
  }
}
