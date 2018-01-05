<?php
include_once 'jiupaipay.const.inc';
include_once ("libs/RSA.php");
include_once ("jiupaipay.fun.inc");
include_once ("libs/AES.php");
include_once ("libs/Common.php");

/*

 */
function jiupaipay_authorize($uid,$businessSeqNo) {   
        $header = jiupaipay_header("U00004");
        
        $aes = new AES(JPP_AES_KEY,JPP_AES_IV);
        $post_data = array();
        $post_data['customerId'] = $uid;
        $post_data['businessSeqNo'] = $businessSeqNo;
        $post_data['busiTradeType'] = 'B04';
        $post_data['fundTradetype'] = 'T99';
        $post_data['protocolNo'] = "jbz@@@".round(microtime(true) * 1000);
        $post_data['note'] = "";
        ksort($post_data);
        $signInfo = $header['signTime'];
        foreach( $post_data as $value ){
            $signInfo .= "|".$value;
        }
        
        $post_data['customerId'] = $aes->encrypt($uid);
        $post_data['protocolNo'] = $aes->encrypt($post_data['protocolNo']);
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
            $profile = cowpro_customer_profile_load_one_row_with_conditions($uid, 'jiupaipay');
            if ($profile == NULL) {
                    $profile = cowpro_customer_profile_new('jiupaipay', $uid);
            }
            $profile->jpp_authorize = TRUE;
            cowpro_customer_profile_save($profile);
            drupal_set_message("授权成功");
            
            global $base_url;
            drupal_goto($base_url."/registration_wizard/jiupaipay");
        }else{
            echo $result['respHeader']['respMsg'];
        }


}

//验证交易密码 成功之后回调授权
function jiupaipay_authorize_callback($data){
    global $user;
    if( intval($data['flag']) == 1 ) {
        jiupaipay_authorize($data['userId'],$data['businessSeqNo']);
    }
}
?>