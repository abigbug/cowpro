<?php
const JPP_DEBUG = TRUE;

function jiupaipay_callback($action) {
	$data = $_REQUEST;

	$result = TRUE;
	switch ($action) {
		case 'register_password' : // 设置交易密码
			include_once 'jiupaipay.createnewacct.inc';
			$result = jiupaipay_register_password_callback ( $data );
			break;
		case 'modify_password' : // 修改交易密码
			include_once 'jiupaipay.pwd.inc';
			$result = jiupaipay_modify_password_callback ( $data );
			break;
		case 'reset_password' : // 重置交易密码
			include_once 'jiupaipay.pwd.inc';
			$result = jiupaipay_reset_password_callback ( $data );
			break;
		case 'jiupaipay_step_1' : // 宜商行绑定银行卡，校验交易密码回调
			include_once 'jiupaipay.bank_card.inc';
			$result = jiupaipay_bank_card_callback ( $data, 1 );
			break;
		case 'jiupaipay_step_2' : // 宜商行解绑银行卡
			include_once 'jiupaipay.bank_card.inc';
			$result = jiupaipay_bank_card_callback ( $data, 2 );
			break;
		case 'jiupaipay_step_3' : // 宜商行绑定银行卡再次回调
			include_once 'jiupaipay.bank_card.inc';
			$result = jiupaipay_bank_card_callback ( $data, 3 );
			break;
		case 'jiupaipay_step_4' : // 宜商行授权
			include_once 'jiupaipay.authorize.inc';
			$result = jiupaipay_authorize_callback ( $data );
			break;
		case 'jiupaipay_step_5' : // 宜商行充值回调
			include_once 'jiupaipay.topup.inc';
			$result = jiupaipay_topup_callback ( $data );
			break;
		case 'jiupaipay_bank_return' : // 银行充值回调同步
			include_once 'jiupaipay.topup.inc';
			$result = jiupaipay_topup_bank_return ( $data );
			break;
		case 'jiupaipay_bank_notify' : // 银行充值回调同步
			include_once 'jiupaipay.topup.inc';
			//此处回调较特殊，其它回调，宜商行是以 HTTP POST 的方式传数据
			//这里，宜商行是用 raw POST data 的方式传数据，
			//所以要用 file_get_contents ( "php://input" ) 把数据读出来
			$data = file_get_contents ( "php://input" );
			$result = jiupaipay_topup_bank_notify ( $data );
			break;
		case 'jiupaipay_step_7' : // 提现校验密码回调
			include_once 'jiupaipay.withdraw.inc';
			$result = jiupaipay_withdraw_callback ( $data );
			break;
	}

	if (JPP_DEBUG) {
		include 'jiupaipay.const.code.inc';
		if (array_key_exists($action, $YBCCB_CALLBACK_ACTION)) {
			$action_helper = '(' . $YBCCB_CALLBACK_ACTION[$action] . ')';
		} else {
			$action_helper = '';
		}
		if (($action == 'jiupaipay_bank_notify') || ($action == 'jiupaipay_bank_return')) {
			if (! empty ( $data )) {
				$debug_data = json_decode ( $data, true );
			} else {
				$debug_data = '';
			}
		} else {
			$debug_data = $data;
		}
		$msg = print_r ( $debug_data, true );
		$businessSeqNo = '';
		if (array_key_exists('businessSeqNo', $debug_data)) {
			$businessSeqNo = $debug_data['businessSeqNo'] . '; ';
		} else if (array_key_exists('inBody', $debug_data) && array_key_exists('businessSeqNo', $debug_data['inBody'])) {
			//在以下两种情况下：(($action == 'jiupaipay_bank_notify') || ($action == 'jiupaipay_bank_return'))
			//宜商行回传的数据包括 ['inBody'] 和 ['reqHeader']
			$businessSeqNo = $debug_data['inBody']['businessSeqNo'] . '; ';
		}
		watchdog('YBCCB', "callback $action $action_helper; businessSeqNo $businessSeqNo; $msg", NULL, WATCHDOG_DEBUG);//YBCCB 意指“宜宾市商业银行”
	}

	if ($result) {
		echo "SUCCESS";
	}
	drupal_exit ();
}

// 返回当前时间戳的毫秒级字符串，长度为14个字符
function _jiupaipay_get_microtime() {
	list ( $usec, $sec ) = explode ( " ", microtime () );
	$result = sprintf ( "%'.10d%'.04d", $sec, $usec * 10000 );
	return $result;
}

// 校验交易密码
/*
 * $uid 用户id
 * $step 步骤（1,银行卡绑定.2,解绑银行卡.3,授权......）
 */
function jiupaipay_check_pwd($uid, $step, $data = NULL) {
	global $base_url;
	include_once ("libs/RSA.php");
	$rsa_private_key = variable_get ( PRIVATE_KEY_ON_JIUPAIPAY );
	$rsa_public_key = variable_get ( PUBLIC_KEY_ON_JIUPAIPAY );
	$rsa = new RSA ( $rsa_private_key, $rsa_public_key );

	$register_password_data ['systemCode'] = "jbz";
	$register_password_data ['userId'] = $uid;
	$register_password_data ['backURL'] = $base_url . "/cowpro/jiupaipay/callback/jiupaipay_step_" . $step;
	$register_password_data ['signTime'] = round ( microtime ( true ) * 1000 );
	$password_sign_info = $register_password_data ['signTime'] . "|" . $register_password_data ['userId'];
	$register_password_data ['signature'] = $rsa->sign ( $password_sign_info );
	$register_password_data ['businessSeqNo'] = "jbz" . date ( "Ymd", time () ) . time ();
	$real_name = cowpro_customer_profile_load_one_row_with_conditions ( $uid, "real_name" );
	$card_no = cowpro_customer_profile_load_one_row_with_conditions ( $uid, "bank_card" );
	$submit_html = "";

	$register_password_data ['userName'] = $real_name->name;
	if ($step == 1) { // 绑卡
		$register_password_data ['operType'] = "B01";
		$register_password_data ['cardNo'] = $card_no->card_no;
		$submit_html .= '<input id="cardNo" name="cardNo" value="' . $register_password_data ['cardNo'] . '" type="hidden" />';
	} else if ($step == 2) { // 解绑
		$register_password_data ['operType'] = "B02";
		$register_password_data ['cardNo'] = $card_no->card_no;
	} else if ($step == 4) { // 授权
		$register_password_data ['operType'] = "B04";
	} else if ($step == 5) { // 充值
		if ($data ['method'] == 1) {
			$register_password_data ['operType'] = "R02";
		} else if ($data ['method'] == 2) {
			$register_password_data ['operType'] = "R01";
		}
		$register_password_data ['amount'] = $data ['amount'];
		$submit_html .= '<input id="amount" name="amount" value="' . $register_password_data ['amount'] . '" type="hidden" />';
	} else if ($step == 7) { // 提现
		$register_password_data ['operType'] = "W01";
		$register_password_data ['amount'] = $data ['amount'];
		$submit_html .= '<input id="amount" name="amount" value="' . $register_password_data ['amount'] . '" type="hidden" />';
	}

	if (! empty ( $data )) {
		$sql_data ['data'] = serialize ( $data );
		$sql_data ['businessSeqNo'] = $register_password_data ['businessSeqNo'];
		$sql_data ['uid'] = $uid;
		db_insert ( 'jiupaipay_data_tmp' )->fields ( array (
				'data' => $sql_data ['data'],
				'businessSeqNo' => $sql_data ['businessSeqNo'],
				'uid' => $uid
		) )->execute ();
	}

	if (_jiupaipay_ismobile_sevice ()) {
		$url = JPP_CHECK_TRANSACTION_PASSWORD_URL_MOBILE;
	} else {
		$url = JPP_CHECK_TRANSACTION_PASSWORD_URL;
	}

	$html = '
    <form id="formu" name="formu" action="' . $url . '" method="get">
            <input id="systemCode" name="systemCode" value="' . $register_password_data ['systemCode'] . '" type="hidden" />
            <input id="userId" name="userId" value="' . $register_password_data ['userId'] . '" type="hidden" />
            <input id="backURL" name="backURL" value="' . $register_password_data ['backURL'] . '" type="hidden" />
            <input id="signTime" name="signTime" value="' . $register_password_data ['signTime'] . '" type="hidden" />
            <input id="signature" name="signature" value="' . $register_password_data ['signature'] . '" type="hidden" />
            <input id="businessSeqNo" name="businessSeqNo" value="' . $register_password_data ['businessSeqNo'] . '" type="hidden" />
            <input id="operType" name="operType" value="' . $register_password_data ['operType'] . '" type="hidden" />
            <input id="userName" name="userName" value="' . $register_password_data ['userName'] . '" type="hidden" />
            ' . $submit_html . '
            <script language="javascript">window.onload=function(){document.formu.submit();}</script>
    </form>';

	echo $html;
	drupal_exit ();
}

// 公共请求头部
function jiupaipay_header($txnType) {
	// 请求报文头
	$header ['version'] = '1.0';
	$header ['merchantCode'] = 'jbz';
	$header ['txnType'] = $txnType;
	$header ['clientSn'] = $header ['txnType'] . "@" . round ( microtime ( true ) * 1000 );
	$header ['clientDate'] = date ( "Ymd", time () );
	$header ['clientTime'] = date ( "His", time () );
	$header ['fileName'] = "";
	$header ['signTime'] = round ( microtime ( true ) * 1000 );
	return $header;
}

// 宜商行API
function jiupaipay_curl_api($data) {
	if (JPP_DEBUG) {
		global $user;
		$uname = $user->name;
		$msg = print_r ( $data, true );
		$clientSn = 'clientSn:' . $data['reqHeader']['clientSn'] . '; ';

		include 'jiupaipay.const.code.inc';
		$txn = $data['reqHeader']['txnType'];
		$txnType = 'txnType:' . $txn . '; ';
		if (array_key_exists($txn, $YBCCB_TXN_TYPE)) {
			$txnType = $YBCCB_TXN_TYPE[$txn] . ' ' . $txnType;
		}
		if (array_key_exists('businessSeqNo', $data ['inBody'])) {
			$businessSeqNo = 'businessSeqNo:' . $data ['inBody']['businessSeqNo'] . '; ';
		}else{
			$businessSeqNo = '';
		}

		if (array_key_exists('businessOrderNo', $data ['inBody'])) {
			$businessOrderNo = 'businessOrderNo:' . $data ['inBody']['businessOrderNo'] . '; ';
		} else {
			$businessOrderNo = '';
		}
		watchdog('YBCCB', "$uname $txnType $clientSn $businessSeqNo $businessOrderNo $msg", NULL, WATCHDOG_DEBUG);//YBCCB 意指“宜宾市商业银行”
	}

	$ch = curl_init ( JPP_URL );
	curl_setopt ( $ch, CURLOPT_URL, JPP_URL );
	curl_setopt ( $ch, CURLOPT_HEADER, 0 );
	curl_setopt ( $ch, CURLOPT_POST, 1 );
	curl_setopt ( $ch, CURLOPT_POSTFIELDS, json_encode ( $data ) );
	curl_setopt ( $ch, CURLOPT_RETURNTRANSFER, 1 );
	curl_setopt ( $ch, CURLOPT_SSL_VERIFYPEER, false );
	curl_setopt ( $ch, CURLOPT_HTTPHEADER, array (
			'Content-Type: application/json',
			'Content-Length: ' . strlen ( json_encode ( $data ) )
	) );

	$result = curl_exec ( $ch );
	if (curl_errno ( $ch )) {
		echo 'Errno ' . curl_error ( $ch ); // 捕抓异常
		exit ();
	}
	curl_close ( $ch );
	return $result;
}

// 判断是否是移动端
function _jiupaipay_ismobile_sevice() {
	$browser = browscap_get_browser ();
	if ($browser ['ismobiledevice'] == "true") {
		return true;
	} else {
		return false;
	}
}

// h5 验签
function _jiupaipay_verify_h5($data) {
	$rsa_private_key = variable_get ( PRIVATE_KEY_ON_JIUPAIPAY );
	$rsa_public_key = variable_get ( PUBLIC_KEY_ON_JIUPAIPAY );
	$rsa = new RSA ( $rsa_private_key, $rsa_public_key );
	$dataStr = $data ['signTime'] . "|" . $data ['userId'];
	$verify = $rsa->verify ( $dataStr, $data ['signature'] );
	return $verify;
}

// 接口验签
function _jiupaipay_verify_api($data, $sign, $signtime) {
	$dataStr = implode ( "|", $data );
	$dataStr = $signtime . "|" . $dataStr;
	$rsa_private_key = variable_get ( PRIVATE_KEY_ON_JIUPAIPAY );
	$rsa_public_key = variable_get ( PUBLIC_KEY_ON_JIUPAIPAY );
	$rsa = new RSA ( $rsa_private_key, $rsa_public_key );
	$verify = $rsa->verify ( $dataStr, $sign );
	return $verify;
}

//记录执行 jiupaipay_repayment() 方法之后，宜商行服务器返回给我们的错误信息
function _jiupaipay_repayment_debug($repayment_schedules, $execute_result) {
	if (! JPP_DEBUG) {
		return;
	}

	$values = array_values ( $repayment_schedules );
	$repayment = array_shift ( $values );
	$nid = '标的编号:' . $repayment->issuing_id;

	$result_from_jpp = $execute_result['data']['value'];


	$data ['interface_module'] = 'jiupaipay';
	$data ['value'] = $result;

	$result_jpp ['external_reference_id'] = $result ['respHeader'] ['serviceSn'];
	$result_jpp ['data'] = $data;
	$result_jpp ['message'] = $result ['respHeader'] ['respMsg'];
	$result_jpp ['result_code'] = $result ['respHeader'] ['respCode'];


	$msg = print_r ( $result_from_jpp, true );
	$clientSn = 'clientSn:' . $result_from_jpp['reqHeader']['clientSn'] . '; ';

	include 'jiupaipay.const.code.inc';
	$txn = $result_from_jpp['reqHeader']['txnType'];
	$txnType = 'txnType:' . $txn . '; ';
	if (array_key_exists($txn, $YBCCB_TXN_TYPE)) {
		$txnType = $YBCCB_TXN_TYPE[$txn] . ' ' . $txnType;
	}
	if (array_key_exists('businessSeqNo', $result_from_jpp ['inBody'])) {
		$businessSeqNo = 'businessSeqNo:' . $result_from_jpp ['inBody']['businessSeqNo'] . '; ';
	}else{
		$businessSeqNo = '';
	}

	if ($execute_result ['success']) {
		$watches_conditions = WATCHDOG_DEBUG;
	} else {
		$watches_conditions = WATCHDOG_ERROR;
	}
	watchdog('YBCCB', "$nid $txnType $clientSn $businessSeqNo $msg", NULL, $watches_conditions);//YBCCB 意指“宜宾市商业银行”
}
