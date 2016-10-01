<?php
include_once 'moneymoremore.const.inc';
include_once 'moneymoremore.fun.inc';
include_once ("libs/RSA.php");
include_once ("libs/Common.php");

/**
 * 充值
 *
 * $rechargeType:
 *  <label><input type="radio" name="rechargeTypeVal" value="" checked="checked"> 网银充值</label>
 *  <label><input type="radio" name="rechargeTypeVal" value="2"> 快捷支付</label>
 *  <label><input type="radio" name="rechargeTypeVal" value="3"> 汇款充值</label>
 *  <label><input type="radio" name="rechargeTypeVal" value="4"> 企业网银</label>
 */
function moneymoremore_topup($uid, $amount, $rechargeType, $journal_id) {
	$action = MMM_URL_RECHARGE;

	global $base_url;
	$destination = array('destination' => url(current_path(), array('absolute' => FALSE, 'query' => drupal_get_query_parameters())));
	$returnURL = url($base_url . MMM_URL_RESPONSE . 'moneymoremore_topup', array('query' => $destination));
	$notifyURL = $base_url . MMM_URL_NOTIRY . 'moneymoremore_topup';

	$orderNo = sprintf("%'.08d-%d", $journal_id, _moneymoremore_get_microtime());

	$profile = cowpro_customer_profile_load_one_row_with_conditions ( $uid, 'moneymoremore' );
	if (! $profile) {
		drupal_set_message(sprintf('没有绑定乾多多账号(uid：%d)', $uid), 'warning');
		return;
	}

	$userMoneymoremore = $profile->mmm_id;
	$platformMoneymoremore = variable_get ( PLATFORM_ACCOUNT_ON_MONEYMOREMORE );
	//$rechargeType = "";
	/*
	* $rechargeType:
	空.网银充值
	1.代扣充值(暂不可用)
	2.快捷支付
	3.汇款充值
	4.企业网银

	* $feeType
	1.充值成功时从充值人账户全额扣除
	2.充值成功时从平台自有账户全额扣除
	3.充值成功时从充值人账户扣除与提现手续费的差值
	4.充值成功时从平台自有账户扣除与提现手续费的差值
	快捷支付、汇款充值、企业网银必填，其他类型留空
	快捷支付可以填1、2、3、4
	汇款充值可以填1、2
	企业网银可以填1、2
	*/
	if ($rechargeType === '') {
		$feeType = "";
	} else {
		$feeType = "2";
	}
	$cardNo = "";
	$common = new Common ();
	if ($common->getAntiState () == 0) {
		$randomTimeStamp = "";
	} else if ($common->getAntiState () == 1) {
		$randomTimeStamp = $common->getRandomTimeStamp ();
	}
	$remark1 = "";
	$remark2 = "";
	$remark3 = "";

	$dataStr = $userMoneymoremore . $platformMoneymoremore . $orderNo . $amount . $rechargeType . $feeType . $cardNo . $randomTimeStamp . $remark1 . $remark2 . $remark3 . $returnURL . $notifyURL;
	if ($common->getAntiState () == 1) {
		$dataStr = strtoupper ( md5 ( $dataStr ) );
	}
	$private_key = variable_get(PRIVATE_KEY_ON_MONEYMOREMORE);
	$public_key = variable_get(PUBLIC_KEY_ON_MONEYMOREMORE);
	$rsa = new RSA ($private_key, $public_key);
	$signInfo = $rsa->sign ( $dataStr );

	if (! empty ( $cardNo )) {
		$cardNo = $rsa->encrypt ( $cardNo );
	}

	$html = '
	<form id="formu" name="formu" action="' . $action . '" method="post">
		<input id="RechargeMoneymoremore" name="RechargeMoneymoremore" value="' . $userMoneymoremore . '" type="hidden" />
		<input id="PlatformMoneymoremore" name="PlatformMoneymoremore" value="' . $platformMoneymoremore . '" type="hidden" />
		<input id="OrderNo" name="OrderNo" value="' . $orderNo . '" type="hidden" />
		<input id="Amount" name="Amount" value="' . $amount . '" type="hidden" />
		<input id="RechargeType" name="RechargeType" value="' . $rechargeType . '" type="hidden" />
		<input id="FeeType" name="FeeType" value="' . $feeType . '" type="hidden" />
		<input id="CardNo" name="CardNo" value="' . $cardNo . '" type="hidden" />
		<input id="RandomTimeStamp" name="RandomTimeStamp" value="' . $randomTimeStamp . '" type="hidden" />
		<input id="Remark1" name="Remark1" value="' . $remark1 . '" type="hidden" />
		<input id="Remark2" name="Remark2" value="' . $remark2 . '" type="hidden" />
		<input id="Remark3" name="Remark3" value="' . $remark3 . '" type="hidden" />
		<input id="ReturnURL" name="ReturnURL" value="' . $returnURL . '" type="hidden" />
		<input id="NotifyURL" name="NotifyURL" value="' . $notifyURL . '" type="hidden" />
		<input id="SignInfo" name="SignInfo" value="' . $signInfo . '" type="hidden" />
		<script language="javascript">window.onload=function(){document.formu.submit();}</script>
	</form>
				';
	echo $html;
	//$h = htmlentities($html, NULL, 'UTF-8');
	//watchdog('moneymoremore', 'moneymoremore_topup: ' . $h, NULL, WATCHDOG_DEBUG);
	drupal_exit();
}

// 充值回调
function moneymoremore_topup_callback() {
	//$msg = print_r($_POST, true);
	//watchdog('moneymoremore', "moneymoremore_topup_callback: $msg", NULL, WATCHDOG_DEBUG);
	if (! _moneymoremore_topup_verify_signature ()) {
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

	custodian_cowpro_fund_topup_callback(TRUE, $journal_id, $external_reference_id, 'moneymoremore', $result);

	return TRUE;
}

function _moneymoremore_topup_verify_signature() {
	$RechargeMoneymoremore = $_POST ["RechargeMoneymoremore"];
	$PlatformMoneymoremore = $_POST ["PlatformMoneymoremore"];
	$LoanNo = $_POST ["LoanNo"];
	$OrderNo = $_POST ["OrderNo"];
	$Amount = $_POST ["Amount"];
	$Fee = $_POST ["Fee"];
	$FeePlatform = $_POST ["FeePlatform"];
	$RechargeType = $_POST ["RechargeType"];
	$FeeType = $_POST ["FeeType"];
	$CardNoList = $_POST ["CardNoList"];
	$RandomTimeStamp = $_POST ["RandomTimeStamp"];
	$Remark1 = $_POST ["Remark1"];
	$Remark2 = $_POST ["Remark2"];
	$Remark3 = $_POST ["Remark3"];
	$ResultCode = $_POST ["ResultCode"];
	$Message = $_POST ["Message"];
	$SignInfo = $_POST ["SignInfo"];
	//$ReturnTimes = $_POST ["ReturnTimes"];

	if (! empty ( $CardNoList )) {
		$private_key = variable_get(PRIVATE_KEY_ON_MONEYMOREMORE);
		$public_key = variable_get(PUBLIC_KEY_ON_MONEYMOREMORE);
		$rsa = new RSA ($private_key, $public_key);
		$CardNoList = $rsa->decrypt ( $CardNoList );
		if (empty ( $CardNoList )) {
			$CardNoList = "";
		}
	}

	$dataStr = $RechargeMoneymoremore . $PlatformMoneymoremore . $LoanNo . $OrderNo . $Amount . $Fee . $FeePlatform . $RechargeType . $FeeType . $CardNoList . $RandomTimeStamp . $Remark1 . $Remark2 . $Remark3 . $ResultCode;
	$common = new Common ();
	if ($common->getAntiState () == 1) {
		$dataStr = strtoupper ( md5 ( $dataStr ) );
	}
	$private_key = variable_get(PRIVATE_KEY_ON_MONEYMOREMORE);
	$public_key = variable_get(PUBLIC_KEY_ON_MONEYMOREMORE);
	$rsa = new RSA ($private_key, $public_key);
	$verifySignature = $rsa->verify ( $dataStr, $SignInfo );
	return $verifySignature;
}
