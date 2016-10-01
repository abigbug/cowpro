<?php
include_once 'moneymoremore.const.inc';
include_once ("libs/RSA.php");
include_once ("libs/Common.php");
include_once ("moneymoremore.transferaudit.inc");

/**
 * 流标，将投资人的资金退回
 * @param int $nid
 *        	标的的 node id
 */
function moneymoremore_issuing_failing($nid) {
	$auditType = 2;//审核类型;1.通过;2.退回
	$resultCode = '';
	$message = '';
  global $base_url;
	$notifyURL = $base_url . MMM_URL_NOTIRY . 'moneymoremore_issuing_failing';
	$result = moneymoremore_transfer_audit($nid, $auditType, $notifyURL, $resultCode, $message);
	$resultCode = $result->ResultCode;
	$message = $result->Message;
	$result_mmm = array();
	if (($resultCode === '88') || ($resultCode === '17')) {
		//"ResultCode":"17","Message":"审核对象重复提交"
		$result_mmm['success'] = TRUE;
	} else {
		$result_mmm['success'] = FALSE;
	}
	$result_mmm['message'] = $message;
	$result_mmm['result_code'] = $resultCode;
	return 	$result_mmm;
}

function moneymoremore_issuing_failing_callback() {
	if (! _moneymoremore_transfer_audit_verify_signature ()) {
		return FALSE;
	}
	//暂时没有需要处理的逻辑
	return TRUE;
}
