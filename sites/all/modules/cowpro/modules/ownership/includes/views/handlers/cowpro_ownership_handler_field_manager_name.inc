<?php

class cowpro_ownership_handler_field_manager_name extends views_handler_field {
	function render($values) {
		$uid = $this->get_value($values);
		$relationship_type = user_relationships_type_load(array('name'=>'客户归属'));
		$relationships = user_relationships_load(array(
			'requester_id' => $uid,
			'rtid'    => $relationship_type->rtid,
		));
                $relationship = array_shift($relationships);
                if ($relationship) {
                    $requestee_id=$relationship->requestee_id;
                    $profile_requestee_name = cowpro_customer_profile_load_one_row_with_conditions ( $requestee_id, 'real_name' );
                    if ($profile_requestee_name) {
                            $requestee_name= $profile_requestee_name->name;
                    } else {
                            $requestee_name = '';
                    }
                    $user = user_load($requestee_id);
                    $userpath = 'user/' . $user->uid;
                    $result = l($user->name . "($requestee_name)", $userpath); 
                }else{
                    $result="";
                }
		return $result;
	}
}
