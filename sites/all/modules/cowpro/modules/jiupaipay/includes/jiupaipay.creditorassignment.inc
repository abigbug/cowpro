<?php
include_once 'jiupaipay.const.inc';
include_once 'jiupaipay.fun.inc';
include_once ("libs/RSA.php");
include_once ("libs/AES.php");
include_once ("libs/Common.php");

/**
 * 债权转让
 *
 * @param $amount 转让价格
 * @param $issuing_id 贷款申请表编号
 * @param $seller_uid 卖家UID
 * @param $buyer_uid 买家UID
 * @return
 *
 */
function jiupaipay_creditor_assignment($amount, $issuing_id, $seller_uid, $buyer_uid) {
	 //请求报文头
        $header = jiupaipay_header("T00004");

        $aes = new AES(JPP_AES_KEY,JPP_AES_IV);
        $profile_seller = cowpro_customer_profile_load_one_row_with_conditions($seller_uid, 'jiupaipay');
        $profile_buy = cowpro_customer_profile_load_one_row_with_conditions($buyer_uid, 'jiupaipay');

        $post_data = array();
        $post_data['businessSeqNo'] = "jbz".date("Ymd",time()).time();
        $post_data['busiTradeType'] = 'T07';
        $post_data['entrustflag'] = "01";
        $accountList = array(
            "oderNo"=>1,
            "oldbusinessSeqNo"=>"",
            "oldOderNo"=>"",
            "debitAccountNo"=> $profile_buy->jpp_account_number,
            "cebitAccountNo"=> $profile_seller->jpp_account_number,
            "currency" => "CNY",
            "amount" => $amount,
            "summaryCode"=> "T07"
            );
        $post_data['accountList'][] = $accountList;
        $contractList = array(
               "oderNo"=>2,
               "contractType"=>"04",
               "contractRole"=>"04",
               "contractFileNm"=>"jbz_".$buyer_uid."_".$seller_uid."_".$issuing_id."_".date("Ymd",time(0)),
               "debitUserid"=>$buyer_uid,
               "cebitUserid"=>$seller_uid
               );
        $post_data['contractList'][] = $contractList;
        $post_data['objectId'] = $issuing_id;
        $post_data['note'] = "";

        $post_data_tmp = $post_data;
        $oderNo = $post_data_tmp["accountList"][0]['oderNo'];
        unset($post_data_tmp["accountList"][0]['oderNo']);
        foreach( $post_data_tmp['accountList'][0] as $key=>$value ){
            $post_data_tmp[$key.$oderNo] = $value;
        }
        
        $oderNo_1 = $post_data_tmp["contractList"][0]['oderNo'];
        unset($post_data_tmp["contractList"][0]['oderNo']);
        foreach( $post_data_tmp['contractList'][0] as $key=>$value ){
            $post_data_tmp[$key.$oderNo_1] = $value;
        }

        unset($post_data_tmp['accountList']);
        unset($post_data_tmp['contractList']);
        ksort($post_data_tmp);

        $signInfo = $header['signTime'];   
        foreach( $post_data_tmp as $value ){
            $signInfo .= "|".$value;
        }

        $post_data["accountList"][0]['debitAccountNo'] = $aes->encrypt($accountList['debitAccountNo']);
        $post_data["accountList"][0]['cebitAccountNo'] = $aes->encrypt($accountList['cebitAccountNo']);
        $post_data["contractList"][0]['debitUserid'] = $aes->encrypt($contractList['debitUserid']);
        $post_data["contractList"][0]['cebitUserid'] = $aes->encrypt($contractList['cebitUserid']);
        $post_data['objectId'] = $aes->encrypt($post_data['objectId']);
        $rsa_private_key = variable_get(PRIVATE_KEY_ON_JIUPAIPAY);
        $rsa_public_key = variable_get(PUBLIC_KEY_ON_JIUPAIPAY);
        $rsa = new RSA ($rsa_private_key, $rsa_public_key);
        $signData = $rsa->sign ( $signInfo );
        $header['signature'] = $signData;

        $curl_post_data['reqHeader'] = $header;
        $curl_post_data['inBody'] = $post_data;
        
        $result = jiupaipay_curl_api($curl_post_data);
        $result_jpp = array();
        $result = json_decode($result,true);
       // var_dump($result);
        if( $result['respHeader']['respCode'] == 'P2P0000' ) {
            $result_jpp['success'] = TRUE;
            $result_jpp['external_reference_id'] = $result['respHeader']['serviceSn'];
        }else{
            $result_jpp['success'] = FALSE;
        }

        $data['interface_module'] = 'jiupaipay';
        $data['value'] = $result;

        $result_jpp['data'] = $data;
        $result_jpp['message'] = $result['respHeader']['respMsg'];
        $result_jpp['result_code'] = $result['respHeader']['respCode'];
        return $result_jpp;
}
