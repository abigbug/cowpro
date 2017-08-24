<?php
function moneymoremore_callback($action) {
	$msg = print_r($_POST, true);
	//watchdog('moneymoremore_watchdog', "callback $action: $msg", NULL, WATCHDOG_DEBUG);

	$result = TRUE;
	switch ($action) {
		case 'moneymoremore_create_new_acct':
			include_once 'moneymoremore.createnewacct.inc';
			$result = moneymoremore_create_new_acct_callback();
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
