<?php

class cowpro_users_handler_field_mmm extends views_handler_field {
  function render($values) {
  	$result = '';
    $uid = $this->get_value($values);

    $profile = cowpro_customer_profile_load_one_row_with_conditions($uid, 'moneymoremore');
    if ($profile) {
    	$result = $profile->mmm_account_number;//乾多多数字账户(可用于登录)
    	$result .= '(' . $profile->mmm_id . ')';//用户的乾多多标识(以m开头)
	    $profile->mmm_authorize_type_1;//投标转账授权
	    $profile->mmm_authorize_type_2;//还款转账授权
	    $profile->mmm_authorize_type_3;//二次分配审核授权
	    if ($profile->mmm_account_number && $profile->mmm_id) {
	    	$result = '已关联';
	    	if ( $profile->mmm_authorize_type_1 && $profile->mmm_authorize_type_2 && $profile->mmm_authorize_type_3) {
	    		$result .= ';已授权';
	    	} else {
	    		$result .= ';未授权！';
	    	}
	    } else {
	    	$result = '请关联乾多多帐户！';
	    }
    } else {
    	$result = '请关联乾多多帐户！';
    }

    return $result;
  }
}
