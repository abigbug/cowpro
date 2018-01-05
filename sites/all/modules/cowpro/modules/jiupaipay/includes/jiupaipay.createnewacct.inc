<?php
include_once 'jiupaipay.const.inc';
include_once ("libs/RSA.php");
include_once ("jiupaipay.fun.inc");
include_once ("libs/AES.php");
include_once ("libs/Common.php");

/**
 * 创建新帐户
 *
 * @param array $user
 */
function jiupaipay_create_new_acct($user) {
        //请求报文头
        $header = jiupaipay_header("U00001");

        $aes = new AES(JPP_AES_KEY,JPP_AES_IV);
        $post_data = array();
        $post_data['customerId'] = $user['uid'];
        $post_data['businessSeqNo'] = "jbz".date("Ymd",time()).time();
        $post_data['busiTradeType'] = 'U01';
	$post_data['ctype'] = "00";
        $post_data['crole'] = '00';
        $post_data['companyName'] = "";
        $post_data['username'] = $user['name'];
        $post_data['certType'] = "00";
        $post_data['certNo'] = $user['id_no'];
        $post_data['certFImage'] = "";
        $post_data['certBImage'] = "";
        $post_data['certInfo'] = "";
        $post_data['idvalidDate'] = "";
        $post_data['idexpiryDate'] = "";
        $post_data['jobType'] = "0";
        $post_data['job'] = "";
        $post_data['postcode'] = "441000";
        $post_data['address'] = "襄阳市XXXXX";
        $post_data['national'] = "10";
        $post_data['completeFlag'] = "0";
        $post_data['phoneNo'] = "";
        $post_data['uniSocCreCode'] = "";
        $post_data['uniSocCreDir'] = "";
        $post_data['bizLicDomicile'] = "";
        $post_data['entType'] = "";
        $post_data['dateOfEst'] = "";
        $post_data['corpacc'] = "";
        $post_data['corpAccBankNo'] = "";
        $post_data['corpAccBankNm'] = "";
        $post_data['bindFlag'] = "00";
        $post_data['bindType'] = "";
        $post_data['acctype'] = "0";
        $post_data['oldbankAccountNo'] = "";
        $post_data['bankAccountNo'] = "";
        $post_data['bankAccountName'] = "";    
        $post_data['bankAccountTelNo'] = "";
        $post_data['phoneNo'] = $user['mobile_number'];
        $post_data['note'] = "";
       // var_dump($post_data);
        ksort($post_data);
        $signInfo = $header['signTime'];
        foreach( $post_data as $value ){
            $signInfo .= "|".$value;
        } 
        $post_data['customerId'] = $aes->encrypt($user['uid']);
        $post_data['username'] = $aes->encrypt($user['name']);
        $post_data['certNo'] = $aes->encrypt($user['id_no']);
        $post_data['address'] = $aes->encrypt("襄阳市XXXXX");
        $post_data['phoneNo'] = $aes->encrypt($user['mobile_number']);
        
        $rsa_private_key = variable_get(PRIVATE_KEY_ON_JIUPAIPAY);
	$rsa_public_key = variable_get(PUBLIC_KEY_ON_JIUPAIPAY);
	$rsa = new RSA ($rsa_private_key, $rsa_public_key);
	$signData = $rsa->sign ( $signInfo );
        
        $header['signature'] = $signData;
        $curl_post_data['reqHeader'] = $header;
        $curl_post_data['inBody'] = $post_data;
        
        $result = jiupaipay_curl_api($curl_post_data);
        $result = json_decode($result,true);
        //var_dump($result);
        if( $result['respHeader']['respCode'] == 'P2P0000' ) {
            $account = $aes->decrypt($result['outBody']['accNo']);
            $profile = cowpro_customer_profile_load_one_row_with_conditions($user['uid'], 'jiupaipay');
            if ($profile == NULL) {
                    $profile = cowpro_customer_profile_new('jiupaipay', $user['uid']);
            }
            $profile->jpp_account_number = $account;//九派支付台账账号
            $profile->jpp_result_code = $result['respHeader']['respCode'];//返回码(p2p0000表示成功,)
            $profile->jpp_result_message = $result['respHeader']['respMsg'];//返回信息(与respCode对应的文字信息)
            $profile->verified = 1;
            $profile->uid = $user['uid'];
            cowpro_customer_profile_save($profile);
            //echo "关联九派支付成功";
            
            //设置交易密码
            global $base_url;
            //$backUrl = urlencode('https://'.$_SERVER['HTTP_HOST'].$_SERVER['PHP_SELF'].'?'.$_SERVER['QUERY_STRING']);
            $register_password_data['systemCode'] = "jbz";
            $register_password_data['userId'] = $user['uid'];
            
            $register_password_data['backURL'] = $base_url."/cowpro/jiupaipay/callback/register_password";
            $register_password_data['signTime'] = round(microtime(true) * 1000);
            $password_sign_info = $register_password_data['signTime']."|". $register_password_data['userId'];
            $register_password_data['signature'] = $rsa->sign($password_sign_info);
            $register_password_data['businessSeqNo'] = "jbz_resiger_password".date("Ymd",time()).time();
 
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
        }else{
            drupal_set_message($result['respHeader']['respMsg']);
        }
       
}

// 设置交易密码回调
function jiupaipay_register_password_callback($data) {
    global $user;
    if( intval($data['flag']) == 1 ) {
        $profile = cowpro_customer_profile_load_one_row_with_conditions($data['userId'], 'jiupaipay');
        if ($profile == NULL) {
                $profile = cowpro_customer_profile_new('jiupaipay', $data['userId']);
        }
        $base_url ;
        $profile->jpp_password = true;
        cowpro_customer_profile_save($profile);
       // echo "设置九派交易密码成功";
        drupal_set_message("关联九派托管成功");
         global $base_url;
        drupal_goto($base_url."/registration_wizard/jiupaipay");
    }
}

?>