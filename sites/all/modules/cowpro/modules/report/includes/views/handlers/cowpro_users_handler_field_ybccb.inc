<?php

class cowpro_users_handler_field_ybccb extends views_handler_field {
  function render($values) {
  	$result = '';
    $uid = $this->get_value($values);

    $profile = cowpro_customer_profile_load_one_row_with_conditions($uid, 'jiupaipay');
    if ($profile) {
	    if (!$profile->jpp_password) {
	    	$result = '未设置交易密码';
	    } else if (!$profile->jpp_authorize) {
	    	$result = '未授权';
    	} else if (!$profile->jpp_bank_card) {
    		$result = '未绑卡';
		} else {
			$result = '已关联';
		}
    } else {
    	$result = '请关联宜商行帐户！';
    }

    return $result;
  }
}