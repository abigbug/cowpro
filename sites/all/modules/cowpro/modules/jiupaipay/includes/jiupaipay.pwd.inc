<?php
include_once 'jiupaipay.const.inc';
include_once ("libs/RSA.php");
include_once ("jiupaipay.fun.inc");
include_once ("libs/AES.php");
include_once ("libs/Common.php");

/**
 * 修改交易密码
 *
 * @param int $uid
 */
function jiupaipay_modify_pwd($uid) {    
    //修改交易密码

    $rsa_private_key = variable_get(PRIVATE_KEY_ON_JIUPAIPAY);
    $rsa_public_key = variable_get(PUBLIC_KEY_ON_JIUPAIPAY);
    $rsa = new RSA ($rsa_private_key, $rsa_public_key);
    $register_password_data['systemCode'] = "jbz";
    $register_password_data['userId'] = $uid;
    $register_password_data['backURL'] = "https://test.jinbeizeng.com/cowpro/jiupaipay/callback/modify_password";
    $register_password_data['signTime'] = round(microtime(true) * 1000);
    $password_sign_info = $register_password_data['signTime']."|". $register_password_data['userId'];
    $register_password_data['signature'] = $rsa->sign($password_sign_info);
    $register_password_data['businessSeqNo'] = "jbz_modify_password".date("Ymd",time()).time();

    $html = '
<form id="formu" name="formu" action="' . JPP_MODIFY_TRANSACTION_PASSWORD_URL . '" method="get">
        <input id="systemCode" name="systemCode" value="' .  $register_password_data['systemCode'] . '" type="hidden" />
        <input id="userId" name="userId" value="' .  $register_password_data['userId'] . '" type="hidden" />
        <input id="backURL" name="backURL" value="' .  $register_password_data['backURL'] . '" type="hidden" />
        <input id="signTime" name="signTime" value="' .  $register_password_data['signTime'] . '" type="hidden" />
        <input id="signature" name="signature" value="' .  $register_password_data['signature'] . '" type="hidden" /> 
        <input id="businessSeqNo" name="businessSeqNo" value="' .  $register_password_data['businessSeqNo'] . '" type="hidden" />
        <script language="javascript">window.onload=function(){document.formu.submit();}</script>
</form>';

    echo $html;
    drupal_exit();
       
}

// 设置交易密码回调
function jiupaipay_modify_password_callback($data) {
    global $user;
    if( $data['flag'] == 1 && $data['userId'] == $user->uid ) {
        $profile = cowpro_customer_profile_load_one_row_with_conditions($user->uid, 'jiupaipay');
        if ($profile == NULL) {
                $profile = cowpro_customer_profile_new('jiupaipay', $user->uid);
        }
        $profile->jpp_password = true;
        drupal_set_message("修改交易密码成功");
        drupal_goto(SERVER_HOST."/registration_wizard/jiupaipay");
    }
}


/**
 * 重置交易密码
 *
 * @param int $uid
 */
function jiupaipay_reset_pwd($uid) {    

    $rsa_private_key = variable_get(PRIVATE_KEY_ON_JIUPAIPAY);
    $rsa_public_key = variable_get(PUBLIC_KEY_ON_JIUPAIPAY);
    $rsa = new RSA ($rsa_private_key, $rsa_public_key);
    $register_password_data['systemCode'] = "jbz";
    $register_password_data['userId'] = $uid;
    $register_password_data['backURL'] = SERVER_HOST."/cowpro/jiupaipay/callback/reset_password";
    $register_password_data['signTime'] = round(microtime(true) * 1000);
    $password_sign_info = $register_password_data['signTime']."|". $register_password_data['userId'];
    $register_password_data['signature'] = $rsa->sign($password_sign_info);
    $register_password_data['businessSeqNo'] = "jbz_modify_password".date("Ymd",time()).time();

    $html = '
<form id="formu" name="formu" action="' . JPP_RESET_TRANSACTION_PASSWORD_URL . '" method="get">
        <input id="systemCode" name="systemCode" value="' .  $register_password_data['systemCode'] . '" type="hidden" />
        <input id="userId" name="userId" value="' .  $register_password_data['userId'] . '" type="hidden" />
        <input id="backURL" name="backURL" value="' .  $register_password_data['backURL'] . '" type="hidden" />
        <input id="signTime" name="signTime" value="' .  $register_password_data['signTime'] . '" type="hidden" />
        <input id="signature" name="signature" value="' .  $register_password_data['signature'] . '" type="hidden" /> 
        <input id="businessSeqNo" name="businessSeqNo" value="' .  $register_password_data['businessSeqNo'] . '" type="hidden" />
        <script language="javascript">window.onload=function(){document.formu.submit();}</script>
</form>';

    echo $html;
    drupal_exit();
       
}

// 设置交易密码回调
function jiupaipay_reset_password_callback($data) {
    global $user;
    if( $data['flag'] == 1 && $data['userId'] == $user->uid ) {
        $profile = cowpro_customer_profile_load_one_row_with_conditions($user->uid, 'jiupaipay');
        if ($profile == NULL) {
                $profile = cowpro_customer_profile_new('jiupaipay', $user->uid);
        }
        $profile->jpp_password = true;
        drupal_set_message("重置交易密码成功");
        drupal_goto("https://test.jinbeizeng.com/registration_wizard/jiupaipay");
    }
}


/**
 * 设置交易密码
 *
 * @param int $uid
 */
function jiupaipay_register_pwd($uid) {    

    $rsa_private_key = variable_get(PRIVATE_KEY_ON_JIUPAIPAY);
    $rsa_public_key = variable_get(PUBLIC_KEY_ON_JIUPAIPAY);
    $rsa = new RSA ($rsa_private_key, $rsa_public_key);
    $register_password_data['systemCode'] = "jbz";
    $register_password_data['userId'] = $uid;
    $register_password_data['backURL'] = SERVER_HOST."/cowpro/jiupaipay/callback/register_password";
    $register_password_data['signTime'] = round(microtime(true) * 1000);
    $password_sign_info = $register_password_data['signTime']."|". $register_password_data['userId'];
    $register_password_data['signature'] = $rsa->sign($password_sign_info);
    $register_password_data['businessSeqNo'] = "jbz_register_password".date("Ymd",time()).time();

    $html = '
<form id="formu" name="formu" action="' . JPP_REGISTER_TRANSACTION_PASSWORD_URL . '" method="get">
        <input id="systemCode" name="systemCode" value="' .  $register_password_data['systemCode'] . '" type="hidden" />
        <input id="userId" name="userId" value="' .  $register_password_data['userId'] . '" type="hidden" />
        <input id="backURL" name="backURL" value="' .  $register_password_data['backURL'] . '" type="hidden" />
        <input id="signTime" name="signTime" value="' .  $register_password_data['signTime'] . '" type="hidden" />
        <input id="signature" name="signature" value="' .  $register_password_data['signature'] . '" type="hidden" /> 
        <input id="businessSeqNo" name="businessSeqNo" value="' .  $register_password_data['businessSeqNo'] . '" type="hidden" />
        <script language="javascript">window.onload=function(){document.formu.submit();}</script>
</form>';

    echo $html;
    drupal_exit();
       
}


?>