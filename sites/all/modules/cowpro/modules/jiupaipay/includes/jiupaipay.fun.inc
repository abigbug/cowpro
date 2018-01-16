<?php
function jiupaipay_callback($action) {
	$msg = print_r($_GET, true);
        $data = $_REQUEST;
	//watchdog('moneymoremore_watchdog', "callback $action: $msg", NULL, WATCHDOG_DEBUG);

	$result = TRUE;
	switch ($action) {
                case 'register_password':  //设置交易密码
			include_once 'jiupaipay.createnewacct.inc';
			$result = jiupaipay_register_password_callback($data);
			break;
                 case 'modify_password':  //修改交易密码
			include_once 'jiupaipay.pwd.inc';
			$result = jiupaipay_modify_password_callback($data);
			break;   
                 case 'reset_password':  //重置交易密码
			include_once 'jiupaipay.pwd.inc';
			$result = jiupaipay_reset_password_callback($data);
			break;        
                 case 'jiupaipay_step_1':  //九派绑定银行卡，校验交易密码回调
			include_once 'jiupaipay.bank_card.inc';
			$result = jiupaipay_bank_card_callback($data,1);
			break;
                case 'jiupaipay_step_2':  //九派解绑银行卡
			include_once 'jiupaipay.bank_card.inc';
			$result = jiupaipay_bank_card_callback($data,2);
			break;
                case 'jiupaipay_step_3':  //九派绑定银行卡再次回调
			include_once 'jiupaipay.bank_card.inc';
			$result = jiupaipay_bank_card_callback($data,3);
			break;   
                case 'jiupaipay_step_4':  //九派授权
			include_once 'jiupaipay.authorize.inc';
			$result = jiupaipay_authorize_callback($data);
			break;   
                case 'jiupaipay_step_5':  //九派充值回调
			include_once 'jiupaipay.topup.inc';
			$result = jiupaipay_topup_callback($data);
			break; 
                case 'jiupaipay_bank_return':  //银行充值回调同步
			include_once 'jiupaipay.topup.inc';
			$result = jiupaipay_topup_bank_return($data);
			break;
                case 'jiupaipay_bank_notify':  //银行充值回调同步
			include_once 'jiupaipay.topup.inc';
			$result = jiupaipay_topup_bank_notify($data);
			break;    
                case 'jiupaipay_step_7':  //提现校验密码回调
			include_once 'jiupaipay.withdraw.inc';
			$result = jiupaipay_withdraw_callback($data);
			break;
		case 'moneymoremore_authorize':
			include_once 'moneymoremore.authorize.inc';
			$result = moneymoremore_authorize_callback();
			break;
		case 'moneymoremore_topup':
			include_once 'moneymoremore.topup.inc';
			$result = moneymoremore_topup_callback();
			break;
		case 'moneymoremore_withdraw':
			include_once 'moneymoremore.withdraw.inc';
			$result = moneymoremore_withdraw_callback();
			break;
		case 'moneymoremore_bid':
			include_once 'moneymoremore.bid.inc';
			$result = moneymoremore_bid_callback();
			break;
		case 'moneymoremore_issuing_failing':
			include_once 'moneymoremore.issuingfailing.inc';
			$result = moneymoremore_issuing_failing_callback();
			break;
		case 'moneymoremore_make_loans_to':
			include_once 'moneymoremore.makeloans.inc';
			$result = moneymoremore_make_loans_to_callback();
			break;
		case 'moneymoremore_repayment':
			include_once 'moneymoremore.repayment.inc';
			$result = moneymoremore_repayment_callback();
			break;
		case 'moneymoremore_creditor_assignment':
			include_once 'moneymoremore.creditorassignment.inc';
			$result = moneymoremore_creditor_assignment_callback();
			break;
	}

	if ($result) {
		echo "SUCCESS";
	}
	drupal_exit();
}

function moneymoremore_response($action) {
	switch ($action) {
		case 'moneymoremore_create_new_acct':
			_moneymoremore_goto_response_page('moneymoremore_create_new_acct');
			break;
		case 'moneymoremore_authorize':
			_moneymoremore_goto_response_page('moneymoremore_authorize');
			break;
		case 'moneymoremore_topup':
			_moneymoremore_goto_response_page('moneymoremore_topup');
			break;
		case 'moneymoremore_withdraw':
			_moneymoremore_goto_response_page('moneymoremore_withdraw');
			break;
	}
}

function _moneymoremore_goto_response_page($op) {
	if (isset($_POST ["ResultCode"])) {
		$result_code = $_POST ["ResultCode"];
	} else {
		$result_code = '-1';
	}
	if (isset($_POST ["Message"])) {
		$message = $_POST ["Message"];
	} else {
		$message = '';
	}
	if ($result_code == '88') {
		$message_type = 'status';
	} else {
		$message_type = 'error';
	}
	if (($op == 'moneymoremore_authorize') && ($result_code == '08')) {
		//请求开启的授权已开启
		$message_type = 'status';
	}
	if ($message_type != 'error') {
		drupal_set_message(sprintf('%s', $message), $message_type);
	} else {
		drupal_set_message(sprintf('%s(乾多多代码：%s)', $message, $result_code), $message_type);
	}
	drupal_goto($_GET['destination']);
}

//返回当前时间戳的毫秒级字符串，长度为14个字符
function _moneymoremore_get_microtime()
{
	list($usec, $sec) = explode(" ", microtime());
	$result = sprintf ( "%'.10d%'.04d", $sec,$usec*10000 );
	return $result;
}

//校验交易密码
/*
 * $uid 用户id
 * $step 步骤（1,银行卡绑定.2,解绑银行卡.3,授权......） 
 *  */
function jiupaipay_check_pwd($uid,$step,$data = NULL){
        global $base_url;
        include_once ("libs/RSA.php");
        $rsa_private_key = variable_get(PRIVATE_KEY_ON_JIUPAIPAY);
	$rsa_public_key = variable_get(PUBLIC_KEY_ON_JIUPAIPAY);
	$rsa = new RSA ($rsa_private_key, $rsa_public_key);
        
        $register_password_data['systemCode'] = "jbz";
        $register_password_data['userId'] = $uid;
        $register_password_data['backURL'] = $base_url."/cowpro/jiupaipay/callback/jiupaipay_step_".$step;
        $register_password_data['signTime'] = round(microtime(true) * 1000);
        $password_sign_info = $register_password_data['signTime']."|". $register_password_data['userId'];
        $register_password_data['signature'] = $rsa->sign($password_sign_info);
        $register_password_data['businessSeqNo'] = "jbz".date("Ymd",time()).time();
        $real_name = cowpro_customer_profile_load_one_row_with_conditions($uid,"real_name");
        $card_no = cowpro_customer_profile_load_one_row_with_conditions($uid,"bank_card");
        $submit_html = "";
        
        $register_password_data['userName'] = $real_name->name;
        if( $step == 1 ) { //绑卡
            $register_password_data['operType'] = "B01";
            $register_password_data['cardNo'] = $card_no->card_no;
            $submit_html .= '<input id="cardNo" name="cardNo" value="' .  $register_password_data['cardNo'] . '" type="hidden" />';
        }else if( $step == 2 ) {//解绑
            $register_password_data['operType'] = "B02";
            $register_password_data['cardNo'] = $card_no->card_no;
        }else if( $step == 4 ){//授权
            $register_password_data['operType'] = "B04";
            
        }else if( $step == 5 ){//充值
            if( $data['method'] == 1 ) {
                $register_password_data['operType'] = "R02";
            }else if( $data['method'] == 2 ){
                $register_password_data['operType'] = "R01";
            }
            $register_password_data['amount'] = $data['amount'];
            $submit_html .= '<input id="amount" name="amount" value="' .  $register_password_data['amount'] . '" type="hidden" />';
        }else if( $step == 7 ) {// 提现
            $register_password_data['operType'] = "W01";
            $register_password_data['amount'] = $data['amount'];
            $submit_html .= '<input id="amount" name="amount" value="' .  $register_password_data['amount'] . '" type="hidden" />';
        }
         
        if( !empty($data) ) {
            $sql_data['data'] = serialize($data);
            $sql_data['businessSeqNo'] = $register_password_data['businessSeqNo'];
            $sql_data['uid'] = $uid;
            db_insert('jiupaipay_data_tmp')
          ->fields(array(
            'data' => $sql_data['data'],
            'businessSeqNo' => $sql_data['businessSeqNo'],
            'uid' => $uid,
            ))
          ->execute();
        }

        if( ismobile_sevice() ) {
            $url = JPP_CHECK_TRANSACTION_PASSWORD_URL_MOBILE;
        }else{
            $url = JPP_CHECK_TRANSACTION_PASSWORD_URL;
        }

        $html = '
    <form id="formu" name="formu" action="' . $url . '" method="get">
            <input id="systemCode" name="systemCode" value="' .  $register_password_data['systemCode'] . '" type="hidden" />
            <input id="userId" name="userId" value="' .  $register_password_data['userId'] . '" type="hidden" />
            <input id="backURL" name="backURL" value="' .  $register_password_data['backURL'] . '" type="hidden" />
            <input id="signTime" name="signTime" value="' .  $register_password_data['signTime'] . '" type="hidden" />
            <input id="signature" name="signature" value="' .  $register_password_data['signature'] . '" type="hidden" /> 
            <input id="businessSeqNo" name="businessSeqNo" value="' .  $register_password_data['businessSeqNo'] . '" type="hidden" />
            <input id="operType" name="operType" value="' .  $register_password_data['operType'] . '" type="hidden" />
            <input id="userName" name="userName" value="' .  $register_password_data['userName'] . '" type="hidden" />
            '.$submit_html.'
            <script language="javascript">window.onload=function(){document.formu.submit();}</script>
    </form>';
   
        echo $html;
        drupal_exit();
}

//公共请求头部
function jiupaipay_header($txnType){
    //请求报文头
    $header['version'] = '1.0';
    $header['merchantCode'] = 'jbz';
    $header['txnType'] = $txnType;
    $header['clientSn'] = $header['txnType']."@".round(microtime(true) * 1000);
    $header['clientDate'] = date("Ymd",time());
    $header['clientTime'] = date("His",time());
    $header['fileName'] = "";
    $header['signTime'] = round(microtime(true) * 1000);
    return $header;
}

//九派API
function jiupaipay_curl_api($data){
    $ch = curl_init(JPP_URL);
    curl_setopt($ch, CURLOPT_URL, JPP_URL);
    curl_setopt($ch, CURLOPT_HEADER, 0);  
    curl_setopt($ch, CURLOPT_POST, 1);
    curl_setopt($ch, CURLOPT_POSTFIELDS,json_encode($data));
    curl_setopt($ch, CURLOPT_RETURNTRANSFER,1);
    curl_setopt($ch, CURLOPT_SSL_VERIFYPEER, false);
    curl_setopt($ch, CURLOPT_HTTPHEADER, array(
        'Content-Type: application/json',
        'Content-Length: ' . strlen(json_encode($data)))
    );

    $result = curl_exec($ch);
    if (curl_errno($ch)) {
        echo 'Errno '.curl_error($ch);//捕抓异常
        exit();
    }
    curl_close($ch);
    return $result;
}

//判断是否是移动端
function ismobile_sevice(){
    $browser = browscap_get_browser();
    if( $browser['ismobiledevice'] == "true" ) {
        return true;
    }else{
        return false;
    }
}

//h5 验签
function verify_h5($data){     
    $rsa_private_key = variable_get(PRIVATE_KEY_ON_JIUPAIPAY);
    $rsa_public_key = variable_get(PUBLIC_KEY_ON_JIUPAIPAY);
    $rsa = new RSA ($rsa_private_key, $rsa_public_key);
    $dataStr = $data['signTime']."|".$data['userId'];
    $verify = $rsa->verify($dataStr, $data['signature']);
    return $verify;
}
//接口验签
function verify_api($data,$sign,$signtime){
    
    $dataStr = implode("|", $data);
    $dataStr = $signtime."|".$dataStr;
    $rsa_private_key = variable_get(PRIVATE_KEY_ON_JIUPAIPAY);
    $rsa_public_key = variable_get(PUBLIC_KEY_ON_JIUPAIPAY);
    $rsa = new RSA ($rsa_private_key, $rsa_public_key);
    $verify = $rsa->verify($dataStr, $sign);
    return $verify;
}
