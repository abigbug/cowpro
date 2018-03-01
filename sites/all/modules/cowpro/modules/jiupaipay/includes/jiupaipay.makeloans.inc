<?php
include_once 'jiupaipay.issuing_publish.inc';

/**
 * 满标，将资金划转到贷款申请人的帐户
 * @param int $nid
 *        	标的的 node id
 */
function jiupaipay_make_loans_to($nid) {

        //标的信息同步
        $issuing_publish = jiupaipay_issuing_publish($nid,"P04","02");
        //$message = implode('|', $issuing_publish);
        //watchdog('_cowpro_issuing_make_loans_to_form_submit', $message);

        if( $issuing_publish['success']) {

            //请求报文头
            $header = jiupaipay_header("T00004");

            $node = node_load($nid);
            $uid = $node->field_applicant ['und'] [0] ['uid'];//融资人ID
            $aes = new AES(JPP_AES_KEY,JPP_AES_IV);
            $profile_jiupaipay = cowpro_customer_profile_load_one_row_with_conditions($uid, 'jiupaipay');

            $post_data = array();
            $post_data['businessSeqNo'] = "jbz".date("Ymd",time()).time();
            $post_data['busiTradeType'] = 'T03';
            $post_data['entrustflag'] = "01";
            $issuing_accno = db_query("SELECT issuing_object_accno FROM jiupaipay_issuing_accno WHERE nid=:nid",array(":nid"=>$nid))->fetchField();
            $loanAmount = $node->field_issuing[LANGUAGE_NONE][0]['loan_amounts'];//贷款总额
            $accountList = array(
                "oderNo"=>1,
                "oldbusinessSeqNo"=>"",
                "oldOderNo"=>"",
                "debitAccountNo"=> $issuing_accno,
                "cebitAccountNo"=> $profile_jiupaipay->jpp_account_number,
                "currency" => "CNY",
                "amount" => $loanAmount,
                "summaryCode"=> "T03"
                );
            $post_data['accountList'][] = $accountList;
            $contractList = array(
                "oderNo"=>2,
                "contractType"=>"03",
                "contractRole"=>"03",
                "contractFileNm"=>"jbz_".$uid,
                "debitUserid"=>"",
                "cebitUserid"=>""
                );
            $post_data['contractList'][] = $contractList;
            $post_data['objectId'] = $nid;
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
            //var_dump($result);
            if( $result['respHeader']['respCode'] == 'P2P0000' ) {
                $result_jpp['success'] = TRUE;
                //标的信息同步 放款
                 $issuing_publish = jiupaipay_issuing_publish($nid,"P04","03");
                 //var_dump($issuing_publish);
            }else{
                $result_jpp['success'] = FALSE;
            }

            $data['interface_module'] = 'jiupaipay';
            $data['value'] = $result;

            $result_jpp['external_reference_id'] = $result['respHeader']['serviceSn'];
            $result_jpp['data'] = $data;
            $result_jpp['message'] = $result['respHeader']['respMsg'];
            $result_jpp['result_code'] = $result['respHeader']['respCode'];
            return $result_jpp;
        }else{
            return $issuing_publish['message'];
        }

}

