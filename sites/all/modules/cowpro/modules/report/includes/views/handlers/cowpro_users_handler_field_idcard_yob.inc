<?php

/*
 * yob - year of birth
 */
class cowpro_users_handler_field_idcard_yob extends views_handler_field {
  function render($values) {
  	$result = 9999;
    $uid = $this->get_value($values);

    $profile = cowpro_customer_profile_load_one_row_with_conditions($uid, 'real_name');
    if ($profile) {
    	$id = $profile->id_no;
    	$yob = intval(substr($id, 6, 4));
    	$result = $yob;
    }

    return $result;
  }
}