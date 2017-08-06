<?php
include_once 'moneymoremore.const.inc';
include_once ("libs/RSA.php");
include_once ("libs/Common.php");
include_once ("libs/LoanInfoBean.php");
include_once ("libs/LoanInfoSecondaryBean.php");

/**
 * 按期还款
 */
/*
 * “平台”收取的费用
 * 	：借款者 的管理费 + 管理逾期罚息  $v['repay_manage_money'] + $v['repay_manage_impose_money'];
 * 	：投资者 的(本金)管理费 + 利息管理费  $v['manage_money'] + $v['manage_interest_money'];
 *
 * “投资者” 收取的费用
 * 	：本金 + 利息 + 罚息 - (本金)管理费 - 利息管理费
 * 		$v['self_money'] + $v['interest_money'] + $v['impose_money'] - $v['manage_money'] - $v['manage_interest_money']
 * 	：奖励 （奖励费用，由平台支出）
 * 		$v['reward_money']
 * 	注：$item['month_repay_money'] = $v['repay_money'] = $v['self_money'] + $v['interest_money']
 *
 *
 * “借款者” 需要支出的费用 = 借款者 的管理费 + 管理逾期罚息 + (本金 + 利息 + 罚息)
 * 	 $v['repay_manage_money'] + $v['repay_manage_impose_money'] + $v['self_money'] + $v['interest_money'] + $v['impose_money']
 *
 *
 * “平台” 需要支付
 * 	支付给“投资者”的奖励 $v['reward_money']
 * 	支付给“推荐人”的  [“投资者”利息管理费返利 ] $v['manage_interest_money_rebate']
 *
 *  支付给“推荐人”的 [“借款者”管理费返利 ] fanwe.fanwe_deal_repay.manage_money_rebate 需要本期所有的还完后，才计算
 */
function moneymoremore_repayment($repayment_schedules) {
	$url = MMM_URL_TRANSFER;

	global $base_url;
	$destination = array('destination' => url(current_path(), array('absolute' => FALSE, 'query' => drupal_get_query_parameters())));
	$returnURL = '';
	$notifyURL = $base_url . MMM_URL_NOTIRY . 'moneymoremore_repayment';

	$platformMoneymoremore = variable_get ( PLATFORM_ACCOUNT_ON_MONEYMOREMORE );

	$values = array_values ( $repayment_schedules );
	$repayment = array_shift($values);
	$payer_uid = $repayment->payer_uid;
	$profile = cowpro_customer_profile_load_one_row_with_conditions ( $payer_uid, 'moneymoremore' );
	$userLoanOutMmmId = $profile->mmm_id;// 借款人, 现在要还款，所以是OUT

	$node = node_load($repayment->issuing_id);
	$issuing_id = $repayment->issuing_id;
	$batchNo = sprintf("%'.08d-%d", $issuing_id, $node->created);
	$loan_amounts = db_query("SELECT i.field_issuing_loan_amounts FROM {field_data_field_issuing} i WHERE i.entity_id = $issuing_id")->fetchField();//标的总金额
	$r = sprintf ( "%'.08d", $repayment->issuing_id );
	$r = date("YmdHis") . "RP" . $r;
	$idForOrderNo = $r;

	$arrloaninfo = array ();
	$count = 0;
	foreach ($repayment_schedules as $repayment) {
		$receiver_uid = $repayment->receiver_uid;
		$profile = cowpro_customer_profile_load_one_row_with_conditions ( $receiver_uid, 'moneymoremore' );
		$userLoanInMmmId = $profile->mmm_id;// 借款人, 现在要还款，所以是OUT

		$r = sprintf ( "%'.04d", $count+1 );
		$r = "I" . $r;
		$orderNo = $idForOrderNo . "U" . sprintf ( "%'.06d", $receiver_uid ) . $r;
		$secondaryJsonList = "";
		/*
		//如果有要收取的费用，就在这里处理，（乾多多平台将此称为“二次分配”）
		if ($v ['fee'] != 0) {
			$secondary = new LoanInfoSecondaryBean ( $platformMoneymoremore, $v ['fee'], "利息管理费", $deal ['id'] );
			$arrsecondary = array (
					'0' => array (
							"LoanInMoneymoremore" => $secondary->LoanInMoneymoremore,
							"Amount" => $secondary->Amount,
							"TransferName" => $secondary->TransferName,
							"Remark" => $secondary->Remark
					)
			);
			$secondaryJsonList = json_encode ( $arrsecondary );
		}
		*/
		$pay_amount = $repayment->payable_amount - $repayment->paid_amount;
		$loaninfo = new LoanInfoBean ( $userLoanOutMmmId, $userLoanInMmmId, $orderNo, $batchNo, "", "", $pay_amount, $loan_amounts, "还款", "", $secondaryJsonList );
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
		$arrloaninfo ["$count"] = $repay;
		$count = $count + 1;
	}

	$loanJsonList = json_encode ( $arrloaninfo );
	$transferAction = "2"; // 1.投标;2.还款;3.其他
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
	$private_key = variable_get(PRIVATE_KEY_ON_MONEYMOREMORE);
	$public_key = variable_get(PUBLIC_KEY_ON_MONEYMOREMORE);
	$rsa = new RSA ($private_key, $public_key);
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
			'SignInfo' => $signInfo
	);
	// use key 'http' even if you send the request to https://...
	$options = array (
			'http' => array (
					'header' => "Content-type: application/x-www-form-urlencoded\r\n",
					'method' => 'POST',
					'content' => http_build_query ( $param ),
					'timeout' => 180,//将超时时间设置为三分钟，乾多多服务器（这个问题可能只限于乾多多测试服务器）有时候响应延时可能会比较长，把以要多等一段时间
			)
	);
	$context = stream_context_create ( $options );
	$response = @file_get_contents ( $url, false, $context );
	if ( $response === FALSE ) {
		watchdog('moneymoremore_watchdog', 'moneymoremore_repayment: ' . $response, NULL, WATCHDOG_DEBUG);
		$opt = print_r ($options, TRUE);
		watchdog('moneymoremore_watchdog', 'moneymoremore_repayment options: ' . $opt, NULL, WATCHDOG_DEBUG);
		//$error = error_get_last();
		$result_mmm = array();
		$result_mmm['success'] = FALSE;
		$result_mmm['message'] = $http_response_header[0];
		$result_mmm['result_code'] = 999;//$error['type'];
		return $result_mmm;
	}

	// 双乾接口文档：
	// 自动转账除了会通知NotifyURL外，还会将参数以JSON字符串的形式直接输出在页面上，
	// 如果不需要审核，其中包含2个JSON，一个action为空，表示转账成功，另一个action=1，表示审核通过
	$result = json_decode ( $response );

	$result_mmm = array();
	if (! is_array ( $result )) {
		watchdog('moneymoremore_watchdog', 'moneymoremore_repayment: ' . $response, NULL, WATCHDOG_DEBUG);
		// 如果双乾在处理的时候，有交易没有成功，那么$response只有一个JSON对象
		// 重复转账侦测功能。
		// 还款类转账执行时乾多多会检测1小时内，付款人、收款人、金额、标号四个要素。
		// 若存在完全一致的转账，手动转账将弹出确认提示框；自动转账将转账失败，报错返回码为44，此功能可临时性关闭
		$result_mmm['success'] = FALSE;
		$result_mmm['message'] = $result->Message;
		$result_mmm['result_code'] = $result->ResultCode;
		return $result_mmm;
	}

	$loanList = json_decode ( urldecode ( $result [0]->LoanJsonList ) );

	$orderNo = $loanList [0]->OrderNo;
	$loanNo = $loanList [0]->LoanNo;
	$resultCode = $result [0]->ResultCode;
	$message = $result [0]->Message;
	if ($resultCode == '88') {
		$result_mmm['success'] = TRUE;
		$result_mmm['message'] = '还款成功';
	} else {
		$result_mmm['success'] = FALSE;
		$result_mmm['message'] = $message;
		$result_mmm['result_code'] = $resultCode;
	}
	return $result_mmm;
}

/**
 * 按期还款回调
 */
function moneymoremore_repayment_callback() {
	//$msg = print_r($_POST, true);
	//watchdog('moneymoremore_watchdog', "moneymoremore_repayment_callback: $msg", NULL, WATCHDOG_DEBUG);
	if (! _moneymoremore_repayment_verify_signature ()) {
		return FALSE;
	}
	//暂时没有需要处理的逻辑
	return TRUE;
}

function _moneymoremore_repayment_verify_signature() {
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
