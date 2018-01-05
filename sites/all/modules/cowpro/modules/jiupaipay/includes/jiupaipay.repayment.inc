<?php
include_once 'jiupaipay.issuing_publish.inc';
include_once 'jiupaipay.outMoney.inc';

/**
 * 按期还款
 */
function jiupaipay_repayment($repayment_schedules) {

    $values = array_values ( $repayment_schedules );
    $repayment = array_shift($values);
    $payer_uid = $repayment->payer_uid;

    $profile_jiupaipay = cowpro_customer_profile_load_one_row_with_conditions ( $payer_uid, 'jiupaipay' );
    $nid = $repayment->issuing_id;
    $pay_total_amount = 0;
    foreach ($repayment_schedules as $repayment) {
        $pay_amount = $repayment->payable_amount - $repayment->paid_amount;
        $pay_total_amount += $pay_amount;
    }
    
    //请求报文头
    $header = jiupaipay_header("T00004");

    $aes = new AES(JPP_AES_KEY,JPP_AES_IV);
    $post_data = array();
    $post_data['busiTradeType'] = 'T04';
    $post_data['businessSeqNo'] = "jbz".date("Ymd",time()).time()."@".$post_data['busiTradeType'];
    $post_data['entrustflag'] = "01";
    $issuing_accno = db_query("SELECT distinct issuing_object_accno FROM jiupaipay_issuing_accno WHERE nid=:nid",array(":nid"=>$nid))->fetchField();

    $accountList = array(
        "oderNo"=>1,
        "oldbusinessSeqNo"=>"",
        "oldOderNo"=>"",
        "debitAccountNo"=> $profile_jiupaipay->jpp_account_number,
        "cebitAccountNo"=> $issuing_accno,
        "currency" => "CNY",
        "amount" => $pay_total_amount,
        "summaryCode"=> "T04"
        );
    $post_data['accountList'][] = $accountList;
    $post_data['contractList'] = array();
    $post_data['objectId'] = $nid;
    $post_data['note'] = "";

    $post_data_tmp = $post_data;
    $oderNo = $post_data_tmp["accountList"][0]['oderNo'];
    unset($post_data_tmp["accountList"][0]['oderNo']);
    foreach( $post_data_tmp['accountList'][0] as $key=>$value ){
        $post_data_tmp[$key.$oderNo] = $value;
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

    if( $result['respHeader']['respCode'] == 'P2P0000' ) {
        $result_jpp['success'] = TRUE;
    }else{
        $result_jpp['success'] = FALSE;
    }

    $data['interface_module'] = 'jiupaipay';
    $data['value'] = $result;

    $result_jpp['external_reference_id'] = $result['respHeader']['serviceSn'];
    $result_jpp['data'] = $data;
    $result_jpp['message'] = $result['respHeader']['respMsg'];
    $result_jpp['result_code'] = $result['respHeader']['respCode'];
    return jiupaipay_outMoney($repayment_schedules,$result_jpp);
    //return $result_jpp;

}
