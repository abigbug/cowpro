<?php

class cowpro_users_handler_field_mobile extends views_handler_field {
  function construct() {
    parent::construct();
    if (!isset($this->options['hide_tel'])) {
      $this->options['hide_tel'] = '';
    }
  }

  function option_definition() {
    $options = parent::option_definition();

    $options['hide_tel'] = array('default' => FALSE, 'bool' => TRUE);

    return $options;
  }

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    $form['hide_tel'] = array(
      '#type' => 'checkbox',
      '#title' => '隐藏部分号码',
      '#default_value' => $this->options['hide_tel'],
      '#description' => '用于电话号码隐藏部分显示',
      '#weight' => -100,
    );
  }
/*
  function query() {
    $this->ensure_my_table();
    $this->add_additional_fields();
  }
  */
  function render($values) {
    $result = '';
    $mobile_number='';
    $uid = $this->get_value($values);
    //var_dump($values);die();
    $profile = cowpro_customer_profile_load_one_row_with_conditions($uid, 'mobile');
    if ($profile) {
        $mobile_number=$profile->mobile_number;
        if($this->options['hide_tel']==1){
    	  $result = substr_replace($mobile_number, '****', 5, 4);
        }else{
    	  $result = $mobile_number;
        }
    } else {
    	$result = '';
    }
    return $result;
  }
}
