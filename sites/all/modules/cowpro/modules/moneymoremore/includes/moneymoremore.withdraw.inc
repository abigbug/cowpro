<?php
include_once 'moneymoremore.const.inc';
include_once 'moneymoremore.fun.inc';
include_once ("libs/RSA.php");
include_once ("libs/Common.php");

/**
 * 提现
 * $uid 提现用户的uid
 * $amount 提现金额
 * $card 用户指定用于提现的银行卡，是一个'cowpro_fund_bankcard'的entity对象
 * $card 对象实例的属性包括：
 *   bankcard_id,uid,type,card_no,cardholder,bank_name,bank_branch,province,city,
 *   详细信息可参考源代码文件cowpro_fund_bankcard.controller.inc
 */
function moneymoremore_withdraw($uid, $amount, $card, $journal_id) {
	include_once 'moneymoremore.const.code.inc';
	$action = MMM_URL_WITHDRAWALS;

	global $base_url;
	$destination = array('destination' => url(current_path(), array('absolute' => FALSE, 'query' => drupal_get_query_parameters())));
	$returnURL = url($base_url . MMM_URL_RESPONSE . 'moneymoremore_withdraw', array('query' => $destination));
	$notifyURL = $base_url . MMM_URL_NOTIRY . 'moneymoremore_withdraw';

	$orderNo = sprintf("%'.08d-%d", $journal_id, _moneymoremore_get_microtime());

	$profile = cowpro_customer_profile_load_one_row_with_conditions ( $uid, 'moneymoremore' );
	$userMoneymoremore = $profile->mmm_id;
	$platformMoneymoremore = variable_get ( PLATFORM_ACCOUNT_ON_MONEYMOREMORE );

	//$feePercent = "0";//0-100之间的数;0表示手续费100%由用户承担;100表示手续费100%由平台承担;默认是0
	$feePercent = "100";//0-100之间的数;0表示手续费100%由用户承担;100表示手续费100%由平台承担;默认是0
	$feeMax = "";//先计算出用户需要承担的手续费，与FeeMax比较，取两者中较小的值为用户实际承担的手续费
	$feeRate = "";//四位小数，由平台指定本次提现的手续费率，不得低于签约基准费率，如果为空，则按照签约基准费率计算手续费
	//$feeQuota = 0;//手续费由P2P平台代付

	$cardNo = $card->card_no;
	$cardType = $card->type;
	$branchBankName = $card->bank_branch;

	$found = FALSE;
	$province_tmp = $card->province;
	foreach($MMM_PROVINCE_CODE as $key=>$value){
		if (strpos($key, $province_tmp) !== FALSE) {
			$province = $value;
			$found = TRUE;
			break;
		}
	}
	if (!$found) {
		$msg = '乾多多不支持的地区(省)：' . $card->province . '，日记帐流水号：' . $orderNo . ', 请联系网站管理员。';
		watchdog('moneymoremore', 'moneymoremore_withdraw: ' . $msg, NULL, WATCHDOG_WARNING);
		drupal_set_message($msg, 'warning');
		return;
	}

	$found = FALSE;
	$city_tmp = $card->city;
	foreach($MMM_CITY_CODE[$province] as $key=>$value){
		if (strpos($key, $city_tmp) !== FALSE) {
			$city = $value;
			$found = TRUE;
			break;
		}
	}
	if (!$found) {
		$msg = '乾多多不支持的地区(市)：' . $card->province . '-' . $card->city . '，日记帐流水号：' . $orderNo . ', 请联系网站管理员。';
		watchdog('moneymoremore', 'moneymoremore_withdraw: ' . $msg, NULL, WATCHDOG_WARNING);
		drupal_set_message($msg, 'warning');
		return;
	}

	if (array_key_exists($card->bank_name, $MMM_BANK_CODE)) {
		$bankCode = $MMM_BANK_CODE[$card->bank_name];
	} else {
		$msg = '乾多多不支持的银行：' . $card->bank_name . '，日记帐流水号：' . $orderNo . ', 请联系网站管理员。';
		watchdog('moneymoremore', 'moneymoremore_withdraw: ' . $msg, NULL, WATCHDOG_WARNING);
		drupal_set_message($msg, 'warning');
		return;
	}

	$common = new Common ();
	if ($common->getAntiState () == 0) {
		$randomTimeStamp = "";
	} else if ($common->getAntiState () == 1) {
		$randomTimeStamp = $common->getRandomTimeStamp ();
	}
	$remark1 = "";
	$remark2 = "";
	$remark3 = "";
	$dataStr = $userMoneymoremore.$platformMoneymoremore.$orderNo.$amount.$feePercent.$feeMax.$feeRate.$cardNo.$cardType.$bankCode.$branchBankName.$province.$city.$randomTimeStamp.$remark1.$remark2.$remark3.$returnURL.$notifyURL;
	if($common->getAntiState() == 1)
	{
		$dataStr = strtoupper(md5($dataStr));
	}
	$private_key = variable_get(PRIVATE_KEY_ON_MONEYMOREMORE);
	$public_key = variable_get(PUBLIC_KEY_ON_MONEYMOREMORE);
	$rsa = new RSA ($private_key, $public_key);
	$signInfo = $rsa->sign($dataStr);
	$cardNoEncrypted = $rsa->encrypt($cardNo);

	$html = '
	<form id="formu" name="formu" action="'.$action.'" method="post">
		<input id="WithdrawMoneymoremore" name="WithdrawMoneymoremore" value="'.$userMoneymoremore.'" type="hidden" />
		<input id="PlatformMoneymoremore" name="PlatformMoneymoremore" value="'.$platformMoneymoremore.'" type="hidden" />
		<input id="OrderNo" name="OrderNo" value="'.$orderNo.'" type="hidden" />
		<input id="Amount" name="Amount" value="'.$amount.'" type="hidden" />
		<input id="FeePercent" name="FeePercent" value="'.$feePercent.'" type="hidden" />
		<input id="FeeMax" name="FeeMax" value="'.$feeMax.'" type="hidden" />
		<input id="FeeRate" name="FeeRate" value="'.$feeRate.'" type="hidden" />
		<input id="CardNo" name="CardNo" value="'.$cardNoEncrypted.'" type="hidden" />
		<input id="CardType" name="CardType" value="'.$cardType.'" type="hidden" />
		<input id="BankCode" name="BankCode" value="'.$bankCode.'" type="hidden" />
		<input id="BranchBankName" name="BranchBankName" value="'.$branchBankName.'" type="hidden" />
		<input id="Province" name="Province" value="'.$province.'" type="hidden" />
		<input id="City" name="City" value="'.$city.'" type="hidden" />
		<input id="RandomTimeStamp" name="RandomTimeStamp" value="'.$randomTimeStamp.'" type="hidden" />
		<input id="Remark1" name="Remark1" value="'.$remark1.'" type="hidden" />
		<input id="Remark2" name="Remark2" value="'.$remark2.'" type="hidden" />
		<input id="Remark3" name="Remark3" value="'.$remark3.'" type="hidden" />
		<input id="ReturnURL" name="ReturnURL" value="'.$returnURL.'" type="hidden" />
		<input id="NotifyURL" name="NotifyURL" value="'.$notifyURL.'" type="hidden" />
		<input id="SignInfo" name="SignInfo" value="'.$signInfo.'" type="hidden" />
		<script language="javascript">window.onload=function(){document.formu.submit();}</script>
	</form>
			';
	echo $html;
	$h = htmlentities($html, NULL, 'UTF-8');
	watchdog('moneymoremore', 'moneymoremore_withdraw: ' . $h, NULL, WATCHDOG_DEBUG);
	drupal_exit();
}

// 提现回调
function moneymoremore_withdraw_callback() {
	//$msg = print_r($_POST, true);
	//watchdog('moneymoremore', "moneymoremore_withdraw_callback: $msg", NULL, WATCHDOG_DEBUG);
	if (! _moneymoremore_withdraw_verify_signature ()) {
		return FALSE;
	}

	$orderNo = $_POST ["OrderNo"];
	$arr = explode('-', $orderNo);
	$journal_id = (int)$arr[0];
	$external_reference_id = $_POST ["LoanNo"];
	$result = array();
	foreach($_POST as $key=>$value){
		$result[$key] = $value;
	}
	unset($result['SignInfo']);

	custodian_cowpro_fund_withdraw_callback(TRUE, $journal_id, $external_reference_id, 'moneymoremore', $result);

	return TRUE;
}

function _moneymoremore_withdraw_verify_signature() {
	$WithdrawMoneymoremore = $_POST["WithdrawMoneymoremore"];
	$PlatformMoneymoremore = $_POST["PlatformMoneymoremore"];
	$LoanNo = $_POST["LoanNo"];
	$OrderNo = $_POST["OrderNo"];
	$Amount = $_POST["Amount"];
	$FeeMax = $_POST["FeeMax"];
	$FeeWithdraws = $_POST["FeeWithdraws"];
	$FeePercent = $_POST["FeePercent"];
	$Fee = $_POST["Fee"];
	$FreeLimit = $_POST["FreeLimit"];
	$FeeRate = $_POST["FeeRate"];
	$FeeSplitting = $_POST["FeeSplitting"];
	$RandomTimeStamp = $_POST["RandomTimeStamp"];
	$Remark1 = $_POST["Remark1"];
	$Remark2 = $_POST["Remark2"];
	$Remark3 = $_POST["Remark3"];
	$ResultCode = $_POST["ResultCode"];
	$Message = $_POST["Message"];
	$SignInfo = $_POST["SignInfo"];
	//$ReturnTimes = $_POST["ReturnTimes"];

	$dataStr = $WithdrawMoneymoremore.$PlatformMoneymoremore.$LoanNo.$OrderNo.$Amount.$FeeMax.$FeeWithdraws.$FeePercent.$Fee.$FreeLimit.$FeeRate.$FeeSplitting.$RandomTimeStamp.$Remark1.$Remark2.$Remark3.$ResultCode;
	$common = new Common();
	if($common->getAntiState() == 1)
	{
		$dataStr = strtoupper(md5($dataStr));
	}
	$private_key = variable_get(PRIVATE_KEY_ON_MONEYMOREMORE);
	$public_key = variable_get(PUBLIC_KEY_ON_MONEYMOREMORE);
	$rsa = new RSA ($private_key, $public_key);
	$SignInfo=$rsa->sign($dataStr);
	$verifySignature = $rsa->verify($dataStr,$SignInfo);
	return $verifySignature;
}
