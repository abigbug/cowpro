<?php

class cowpro_report_handler_field_real_name extends views_handler_field {
  function render($values) {
    $uid = $this->get_value($values);

    $profile_real_name = cowpro_customer_profile_load_one_row_with_conditions ( $uid, 'real_name' );
    if ($profile_real_name) {
    	$name = $profile_real_name->name;
    } else {
    	$name = '';
    }
    return $name;
  }
}
