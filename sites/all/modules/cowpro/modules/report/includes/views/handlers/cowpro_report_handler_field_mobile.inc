<?php

class cowpro_report_handler_field_mobile extends views_handler_field {
  function render($values) {
  	$result = '';
    $uid = $this->get_value($values);

    $profile = cowpro_customer_profile_load_one_row_with_conditions($uid, 'mobile');
    return $profile->mobile_number;
  }
}
