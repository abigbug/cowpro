<?php
include_once 'moneymoremore.const.inc';
include_once ("libs/RSA.php");
include_once ("libs/Common.php");

/*
 * $auditType 审核类型;1.通过;2.退回;3.二次分配同意;4.二次分配不同意;5.提现通过;6.提现退回
 * 以下审核接口默认双乾服务器已经为P2P平台打开了无密码审核开关
 * 在上线之前，需要确认“双乾无密码审核”开关已打开，否则代码会出错
 */
function moneymoremore_transfer_audit($nid, $auditType, $notifyURL, &$resultCode, &$message) {
	$conditions = array();
	$conditions['internal_reference_id'] = 'ISSUING-' . $nid;
	$conditions['type'] = 'BID';
	$conditions['status'] = TRUE;
	$ids = FALSE;
	$reset = TRUE;
	$bid_items = entity_load('cowpro_fund_journal', $ids, $conditions, $reset);
	$loanNoList = '';
	foreach ($bid_items as $item) {
		$loanNoList .= ',' . $item->external_reference_id;
	}
	$loanNoList = substr ( $loanNoList, 1 ); // 删除开头的“逗号”

	$platformMoneymoremore = variable_get ( PLATFORM_ACCOUNT_ON_MONEYMOREMORE );
	$common = new Common ();
	if ($common->getAntiState () == 0) {
		$randomTimeStamp = "";
	} else if ($common->getAntiState () == 1) {
		$randomTimeStamp = $common->getRandomTimeStamp ();
	}
	$remark1 = '';
	$remark2 = '';
	$remark3 = '';
	$returnURL = '';
	$dataStr = $loanNoList . $platformMoneymoremore . $auditType . $randomTimeStamp . $remark1 . $remark2 . $remark3 . $returnURL . $notifyURL;
	if ($common->getAntiState () == 1) {
		$dataStr = strtoupper ( md5 ( $dataStr ) );
	}
	$private_key = variable_get(PRIVATE_KEY_ON_MONEYMOREMORE);
	$public_key = variable_get(PUBLIC_KEY_ON_MONEYMOREMORE);
	$rsa = new RSA ($private_key, $public_key);
	$signInfo = $rsa->sign ( $dataStr );

	$url = MMM_URL_AUDIT;
	$param = array (
			'LoanNoList' => $loanNoList,
			'PlatformMoneymoremore' => $platformMoneymoremore,
			'AuditType' => $auditType,
			'RandomTimeStamp' => $randomTimeStamp,
			'Remark1' => $remark1,
			'Remark2' => $remark2,
			'Remark3' => $remark3,
			'ReturnURL' => $returnURL,
			'NotifyURL' => $notifyURL,
			'SignInfo' => $signInfo
	);

	// use key 'http' even if you send the request to https://...
	$options = array (
			'http' => array (
					'header' => "Content-type: application/x-www-form-urlencoded\r\n",
					'method' => 'POST',
					'content' => http_build_query ( $param )
			)
	);
	$context = stream_context_create ( $options );
	$response = file_get_contents ( $url, false, $context );
	$h = var_export($param, true);
	$h = "nid=$nid;$h";
	//watchdog('moneymoremore', 'moneymoremore_transfer_audit: ' . $h, NULL, WATCHDOG_DEBUG);
	//watchdog('moneymoremore', 'moneymoremore_transfer_audit_response: ' . $response, NULL, WATCHDOG_DEBUG);

	//$resultCode,$message将做为“形参”返回给调用者
	$result = json_decode ( $response );
	if (property_exists($result, 'ResultCode')) {
		$resultCode = $result->ResultCode;
	} else {
		$resultCode = '';
	}
	if (property_exists($result, 'Message')) {
		$message = $result->Message;
	} else {
		$message = '';
	}
	return $result;
}
function _moneymoremore_transfer_audit_verify_signature() {
	$LoanNoList = $_POST ["LoanNoList"];
	$LoanNoListFail = $_POST ["LoanNoListFail"];
	$PlatformMoneymoremore = $_POST ["PlatformMoneymoremore"];
	$AuditType = $_POST ["AuditType"];
	$RandomTimeStamp = $_POST ["RandomTimeStamp"];
	$Remark1 = $_POST ["Remark1"];
	$Remark2 = $_POST ["Remark2"];
	$Remark3 = $_POST ["Remark3"];
	$ResultCode = $_POST ["ResultCode"];
	$Message = $_POST ["Message"];
	$SignInfo = $_POST ["SignInfo"];
	//$ReturnTimes = $_POST ["ReturnTimes"];

	$dataStr = $LoanNoList . $LoanNoListFail . $PlatformMoneymoremore . $AuditType . $RandomTimeStamp . $Remark1 . $Remark2 . $Remark3 . $ResultCode;
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
