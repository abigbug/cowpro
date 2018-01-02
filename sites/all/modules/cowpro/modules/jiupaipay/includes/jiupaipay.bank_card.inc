<?php
include_once 'jiupaipay.const.inc';
include_once ("libs/RSA.php");
include_once ("jiupaipay.fun.inc");
include_once ("libs/AES.php");
include_once ("libs/Common.php");

/**
 * 解绑银行卡
 *
 * @param array $user
 * @param string $businessSeqNo 校验交易密码流水
 */
function jiupaipay_bank_card_unbundling($user,$businessSeqNo) {
        $header = jiupaipay_header("U00001");
        
        $profile_bank_card = cowpro_customer_profile_load_one_row_with_conditions($user->uid, 'bank_card');
        if ($profile_bank_card == NULL) {
                $profile = cowpro_customer_profile_new('bank_card', $user->uid);
        }
        
        $profile_mobile = cowpro_customer_profile_load_one_row_with_conditions($user->uid, 'mobile');
        if ($profile_mobile == NULL) {
                $profile_mobile = cowpro_customer_profile_new('mobile', $user->uid);
        }
        $aes = new AES(JPP_AES_KEY,JPP_AES_IV);
        $post_data = array();
        $post_data['customerId'] = $user->uid;
        $post_data['businessSeqNo'] = $businessSeqNo;
        $post_data['busiTradeType'] = 'B02';
	$post_data['ctype'] = "00";
        $post_data['crole'] = '00';
        $post_data['companyName'] = "";
        $post_data['username'] = "";
        $post_data['certType'] = "00";
        $post_data['certNo'] = "";
        $post_data['certFImage'] = "";
        $post_data['certBImage'] = "";
        $post_data['certInfo'] = "";
        $post_data['idvalidDate'] = "";
        $post_data['idexpiryDate'] = "";
        $post_data['jobType'] = "0";
        $post_data['job'] = "";
        $post_data['postcode'] = "441000";
        $post_data['address'] = "";
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
        $post_data['bindType'] = "99";
        $post_data['acctype'] = "0";
        $post_data['oldbankAccountNo'] = "";
        $post_data['bankAccountNo'] = $profile_bank_card->card_no;
        $post_data['bankAccountName'] = $profile_bank_card->cardholder;    
        $post_data['bankAccountTelNo'] = $profile_bank_card->mobile;
        $post_data['phoneNo'] = $profile_mobile->mobile_number;
        $post_data['note'] = "";
       // var_dump($post_data);
        ksort($post_data);
        $signInfo = $header['signTime'];
        foreach( $post_data as $value ){
            $signInfo .= "|".$value;
        } 
        $post_data['customerId'] = $aes->encrypt($user->uid);
        $post_data['bankAccountNo'] = $aes->encrypt($profile_bank_card->card_no);
        $post_data['phoneNo'] = $aes->encrypt($profile_mobile->mobile_number);
        $post_data['bankAccountName'] = $aes->encrypt($profile_bank_card->cardholder);
        $post_data['bankAccountTelNo'] = $aes->encrypt($profile_bank_card->mobile);
        
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
            $profile = cowpro_customer_profile_load_one_row_with_conditions($user->uid, 'jiupaipay');
            if ($profile == NULL) {
                    $profile = cowpro_customer_profile_new('jiupaipay', $user->uid);
            }
            $profile->jpp_bank_card = FALSE;//九派支付台账账号
            cowpro_customer_profile_save($profile);
            
            drupal_set_message("解绑银行卡成功");
            drupal_goto(SERVER_HOST."/registration_wizard");
            //echo "解绑银行卡成功";
        }else{
            echo $result['respHeader']['respMsg'];
        }
       
}

function jiupaipay_bank_card($user,$businessSeqNo){
    include_once ("libs/RSA.php");
     $rsa_private_key = variable_get(PRIVATE_KEY_ON_JIUPAIPAY);
     $rsa_public_key = variable_get(PUBLIC_KEY_ON_JIUPAIPAY);
     $rsa = new RSA ($rsa_private_key, $rsa_public_key);
     
    $profile_bank_card = cowpro_customer_profile_load_one_row_with_conditions($user->uid, 'bank_card');
    if ($profile_bank_card == NULL) {
            $profile_bank_card = cowpro_customer_profile_new('bank_card', $user->uid);
    }
    
    $profile_real_name = cowpro_customer_profile_load_one_row_with_conditions($user->uid, 'real_name');
    if ($profile_real_name == NULL) {
            $profile_real_name = cowpro_customer_profile_new('real_name', $user->uid);
    }
    
     $bank_card_data = array();
     $bank_card_data['systemCode'] = "jbz";
     $bank_card_data['userId'] = $user->uid;
     $bank_card_data['cardNo'] = $profile_bank_card->card_no;
     $bank_card_data['idCardNo'] = $profile_real_name->id_no;
     $bank_card_data['bankName'] = $profile_bank_card->bank_name;
     $bank_card_data['cardPhoneNumber'] = $profile_bank_card->mobile;
     $bank_card_data['userName'] = $profile_bank_card->cardholder;
     $bank_card_data['channelname'] = "金贝增";
     $bank_card_data['userNameType'] = "2";
     $bank_card_data['idCardNoType'] = "2";
     $bank_card_data['cardNoType'] = "2";
     $bank_card_data['cardPhoneNumberType'] = "2";
     $bank_card_data['backURL'] = SERVER_HOST."/cowpro/jiupaipay/callback/jiupaipay_step_3";
     $bank_card_data['signTime'] = round(microtime(true) * 1000);
     $bank_card_sign_data = $bank_card_data['signTime']."|". $bank_card_data['userId'];
     $bank_card_data['signature'] = $rsa->sign($bank_card_sign_data);
     $bank_card_data['businessSeqNo'] = $businessSeqNo;
     
     
     $html = '
 <form id="formu" name="formu" action="' . JPP_BANK_CARD_URL . '" method="get">
         <input id="systemCode" name="systemCode" value="' .  $bank_card_data['systemCode'] . '" type="hidden" />
         <input id="userId" name="userId" value="' .  $bank_card_data['userId'] . '" type="hidden" />
         <input id="backURL" name="backURL" value="' .  $bank_card_data['backURL'] . '" type="hidden" />
         <input id="signTime" name="signTime" value="' .  $bank_card_data['signTime'] . '" type="hidden" />
         <input id="signature" name="signature" value="' .  $bank_card_data['signature'] . '" type="hidden" /> 
         <input id="businessSeqNo" name="businessSeqNo" value="' .  $bank_card_data['businessSeqNo'] . '" type="hidden" />
         <input id="cardNo" name="cardNo" value="' .  $bank_card_data['cardNo'] . '" type="hidden" />
         <input id="idCardNo" name="idCardNo" value="' .  $bank_card_data['idCardNo'] . '" type="hidden" />
         <input id="bankName" name="bankName" value="' .  $bank_card_data['bankName'] . '" type="hidden" />
         <input id="userName" name="userName" value="' .  $bank_card_data['userName'] . '" type="hidden" />
         <input id="channelname" name="channelname" value="' .  $bank_card_data['channelname'] . '" type="hidden" />
         <input id="userNameType" name="userNameType" value="' .  $bank_card_data['userNameType'] . '" type="hidden" />
         <input id="idCardNoType" name="idCardNoType" value="' .  $bank_card_data['idCardNoType'] . '" type="hidden" />
         <input id="cardNoType" name="cardNoType" value="' .  $bank_card_data['cardNoType'] . '" type="hidden" />
         <input id="cardNoType" name="cardPhoneNumber" value="' .  $bank_card_data['cardPhoneNumber'] . '" type="hidden" />
         <input id="cardPhoneNumberType" name="cardPhoneNumberType" value="' .  $bank_card_data['cardPhoneNumberType'] . '" type="hidden" />
         <script language="javascript">window.onload=function(){document.formu.submit();}</script>
 </form>';
     echo $html;
     drupal_exit();
    
}

function jiupaipay_bank_card_callback($data,$step) {
    global $user;
    if( $data['flag'] == 1 && $data['userId'] == $user->uid ) {
        if( $step == 1 ) {
            //绑定银行卡
            jiupaipay_bank_card($user,$data['businessSeqNo']);
        }else if( $step == 2 ){
            //解绑银行卡
            jiupaipay_bank_card_unbundling($user,$data['businessSeqNo']);
        }else if( $step == 3 ){
            if( $data['userId'] == $user->uid && $data['flag'] == 1 ) {
                $profile_jiupaipay = cowpro_customer_profile_load_one_row_with_conditions($user->uid, 'jiupaipay');
                if ($profile_jiupaipay == NULL) {
                        $profile_jiupaipay = cowpro_customer_profile_new('jiupaipay', $user->uid);
                }
                $profile_jiupaipay->jpp_bank_card = TRUE;
                cowpro_customer_profile_save($profile_jiupaipay);
                drupal_set_message("绑定银行卡成功");
                drupal_goto(SERVER_HOST.'/registration_wizard');
            }else{
                drupal_set_message("绑定银行卡失败");
            }
        }
    }
}
