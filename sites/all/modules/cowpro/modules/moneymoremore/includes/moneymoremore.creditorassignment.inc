<?php
include_once 'moneymoremore.const.inc';
include_once 'moneymoremore.fun.inc';
include_once ("libs/RSA.php");
include_once ("libs/Common.php");
// include_once ("moneymoremore.transferaudit.inc");
include_once ("libs/LoanInfoBean.php");
include_once ("libs/LoanInfoSecondaryBean.php");

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
function moneymoremore_creditor_assignment($amount, $issuing_id, $seller_uid, $buyer_uid) {
	$url = MMM_URL_TRANSFER;

	global $base_url;
	$returnURL = '';
	$notifyURL = $base_url . MMM_URL_NOTIRY . 'moneymoremore_creditor_assignment';

	$platformMoneymoremore = variable_get ( PLATFORM_ACCOUNT_ON_MONEYMOREMORE );

	$secondaryJsonList = '';
	/*
	 * $pFromFee = $transfer['transfer_amount']*$user_load_transfer_fee*0.01;// '出让方手续费 否 金额单位元，不能为负，允许为0 ',
	 * if ($pFromFee != 0) {
	 * $pFromFee = str_replace(',', '', number_format($pFromFee,2));
	 * $secondary = new LoanInfoSecondaryBean ( $platformMoneymoremore, $pFromFee, "债权转让手续费", $deal_id );
	 * $arrsecondary = array (
	 * '0' => array (
	 * "LoanInMoneymoremore" => $secondary->LoanInMoneymoremore,
	 * "Amount" => $secondary->Amount,
	 * "TransferName" => $secondary->TransferName,
	 * "Remark" => $secondary->Remark
	 * )
	 * );
	 * $secondaryJsonList = json_encode ( $arrsecondary );
	 * }
	 */

	$node = node_load($issuing_id);
	$orderNo = sprintf("%'.08d-%d", $issuing_id, $node->created) . "CA" . sprintf ( "%'.06d", $seller_uid ) . "to" . sprintf ( "%'.06d", $buyer_uid );
	$batchNo = sprintf("%'.08d-%d", $issuing_id, $node->created);
	$arrloaninfo = array ();
	$profile = cowpro_customer_profile_load_one_row_with_conditions ( $seller_uid, 'moneymoremore' );
	$sellerMmmId = $profile->mmm_id;
	$profile = cowpro_customer_profile_load_one_row_with_conditions ( $buyer_uid, 'moneymoremore' );
	$buyerMmmId = $profile->mmm_id;
	$loaninfo = new LoanInfoBean ( $buyerMmmId, $sellerMmmId, $orderNo, $batchNo, '', '', $amount, $amount, "债权转让", "", $secondaryJsonList );
	$repay = array (
			"LoanOutMoneymoremore" => $loaninfo->LoanOutMoneymoremore,
			"LoanInMoneymoremore" => $loaninfo->LoanInMoneymoremore,
			"OrderNo" => $loaninfo->OrderNo,
			"BatchNo" => $loaninfo->BatchNo,
			"ExchangeBatchNo" => $loaninfo->ExchangeBatchNo,
			"AdvanceBatchNo" => $loaninfo->AdvanceBatchNo,
			"Amount" => $loaninfo->Amount,
			"FullAmount" => $loaninfo->FullAmount,
			"TransferName" => $loaninfo->TransferName,
			"Remark" => $loaninfo->Remark,
			"SecondaryJsonList" => $loaninfo->SecondaryJsonList
	);
	$arrloaninfo ["0"] = $repay;

	$loanJsonList = json_encode ( $arrloaninfo );
	$transferAction = "2"; // 1.投标;2.还款;3.其他.因为如果选“其他”，那么只能平台账户间可以自动转帐， 别的账户不能自动转账，所以这里只好选“还款”
	$loanAction = "2"; // 1.手动转账; 2.自动转账; 手动弹出密码验证页面 自动不弹
	$transferType = "2"; // 1.桥连; 2.直连
	$needAudit = "1"; // 空.需要审核;1.自动通过
	$common = new Common ();
	if ($common->getAntiState () == 0) {
		$randomTimeStamp = "";
	} else if ($common->getAntiState () == 1) {
		$randomTimeStamp = $common->getRandomTimeStamp ();
	}
	$remark1 = "";
	$remark2 = "";
	$remark3 = "";

	$dataStr = $loanJsonList . $platformMoneymoremore . $transferAction . $loanAction . $transferType . $needAudit . $randomTimeStamp . $remark1 . $remark2 . $remark3 . $returnURL . $notifyURL;
	if ($common->getAntiState () == 1) {
		$dataStr = strtoupper ( md5 ( $dataStr ) );
	}
	$private_key = variable_get ( PRIVATE_KEY_ON_MONEYMOREMORE );
	$public_key = variable_get ( PUBLIC_KEY_ON_MONEYMOREMORE );
	$rsa = new RSA ( $private_key, $public_key );
	$signInfo = $rsa->sign ( $dataStr );
	$loanJsonList = urlencode ( $loanJsonList );

	$param = array (
			'LoanJsonList' => $loanJsonList,
			'PlatformMoneymoremore' => $platformMoneymoremore,
			'TransferAction' => $transferAction,
			'Action' => $loanAction,
			'TransferType' => $transferType,
			'NeedAudit' => $needAudit,
			'RandomTimeStamp' => $randomTimeStamp,
			'Remark1' => $remark1,
			'Remark2' => $remark2,
			'Remark3' => $remark3,
			'ReturnURL' => $returnURL,
			'NotifyURL' => $notifyURL,
			'SignInfo' => $signInfo,
	);

	// use key 'http' even if you send the request to https://...
	$options = array (
			'http' => array (
					'header' => "Content-type: application/x-www-form-urlencoded\r\n",
					'method' => 'POST',
					'content' => http_build_query ( $param ),
			)
	);
	$context = stream_context_create ( $options );
	$response = file_get_contents ( $url, false, $context );

	$result_mmm = array();

	// 双乾接口文档：
	// 自动转账除了会通知NotifyURL外，还会将参数以JSON字符串的形式直接输出在页面上，
	// 如果不需要审核，其中包含2个JSON，一个action为空，表示转账成功，另一个action=1，表示审核通过
	$result = json_decode ( $response );
	if (! is_array ( $result )) {
		// 如果双乾在处理的时候，有交易没有成功，那么$response只有一个JSON对象
		// 重复转账侦测功能。
		// 还款类转账执行时乾多多会检测1小时内，付款人、收款人、金额、标号四个要素。
		// 若存在完全一致的转账，手动转账将弹出确认提示框；自动转账将转账失败，报错返回码为44，此功能可临时性关闭
		$result_mmm['success'] = FALSE;
		$result_mmm['message'] = $result->Message;
		$result_mmm['result_code'] = $result->ResultCode;
	} else {
		$loanList = json_decode ( urldecode ( $result [0]->LoanJsonList ) );
		$orderNo = $loanList [0]->OrderNo;
		$loanNo = $loanList [0]->LoanNo;
		$resultCode = $result [0]->ResultCode;
		$message = $result [0]->Message;
		$memo = $orderNo;
		if ($resultCode === '88') {
			$result_mmm['success'] = TRUE;
		} else {
			$result_mmm['success'] = FALSE;
		}
		$result_mmm['message'] = $message;
		$result_mmm['result_code'] = $resultCode;
		$result_mmm['memo'] = $memo;
	}
	return 	$result_mmm;
}

/**
 * 债权转让回调
 */
function moneymoremore_creditor_assignment_callback() {
	//$msg = print_r($_POST, true);
	//watchdog('moneymoremore_watchdog', "moneymoremore_repayment_callback: $msg", NULL, WATCHDOG_DEBUG);
	if (! _moneymoremore_creditor_assignment_verify_signature ()) {
		return FALSE;
	}
	//暂时没有需要处理的逻辑
	return TRUE;
}

function _moneymoremore_creditor_assignment_verify_signature() {
	$LoanJsonList = $_POST ["LoanJsonList"];
	$LoanJsonList = urldecode ( $LoanJsonList );
	$PlatformMoneymoremore = $_POST ["PlatformMoneymoremore"];
	$RandomTimeStamp = $_POST ["RandomTimeStamp"];
	$Remark1 = $_POST ["Remark1"];
	$Remark2 = $_POST ["Remark2"];
	$Remark3 = $_POST ["Remark3"];
	$ResultCode = $_POST ["ResultCode"];
	$Message = $_POST ["Message"];
	$SignInfo = $_POST ["SignInfo"];
	//$ReturnTimes = $_POST ["ReturnTimes"];

	$dataStr = $LoanJsonList . $PlatformMoneymoremore . $RandomTimeStamp . $Remark1 . $Remark2 . $Remark3 . $ResultCode;
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
