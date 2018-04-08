<?php

/*
 * gender - 性别
 */
class cowpro_users_handler_field_idcard_gender extends views_handler_field {
  function render($values) {
  	$result = '';
    $uid = $this->get_value($values);

    $profile = cowpro_customer_profile_load_one_row_with_conditions($uid, 'real_name');
    if ($profile) {
    	$id = $profile->id_no;
    	$gender = intval(substr($id, 16, 1));
    	if ($gender%2 == 1) {
    		$result = '男';
    	} else {
    		$result = '女';
    	}
    }

    return $result;
  }
}