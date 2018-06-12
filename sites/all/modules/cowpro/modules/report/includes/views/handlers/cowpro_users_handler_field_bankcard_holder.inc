<?php

class cowpro_users_handler_field_bankcard_holder extends views_handler_field {
  function render($values) {
  	$result = '';
    $uid = $this->get_value($values);

    $profile = cowpro_customer_profile_load_one_row_with_conditions($uid, 'bank_card');
    if ($profile) {
    	$result = $profile->cardholder;
    }

    return $result;
  }
}
