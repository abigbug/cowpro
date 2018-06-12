<?php
include_once 'moneymoremore.const.inc';
include_once 'moneymoremore.fun.inc';
include_once ("libs/RSA.php");
include_once ("libs/Common.php");
include_once ("libs/LoanInfoBean.php");
include_once ("libs/LoanInfoSecondaryBean.php");

/**
 * 提现
 * $uid 提现用户的uid
 * $amount 提现金额
 * $card 用户指定用于提现的银行卡，是一个'cowpro_fund_bankcard'的entity对象
 * $card 对象实例的属性包括：
 *   bankcard_id,uid,type,card_no,cardholder,bank_name,bank_branch,province,city,
 *   详细信息可参考源代码文件cowpro_fund_bankcard.controller.inc
 */
function moneymoremore_internal_trans($uid_from, $uid_to, $amt) {
	$url = MMM_URL_TRANSFER;

	global $base_url;
	$destination = array('destination' => url(current_path(), array('absolute' => FALSE, 'query' => drupal_get_query_parameters())));
	$returnURL = url($base_url . MMM_URL_RESPONSE . 'moneymoremore_internal_trans', array('query' => $destination));
	$notifyURL = $base_url . MMM_URL_NOTIRY . 'moneymoremore_internal_trans';

	$platformMoneymoremore = variable_get ( PLATFORM_ACCOUNT_ON_MONEYMOREMORE );

	$batchno = _moneymoremore_get_microtime();//	请求时间	是	例如 1405668253874
	$orderNo = sprintf("%'.06d", $uid_from)."IT".sprintf("%'.06d", $uid_to).'#'.$batchno;
	$arrloaninfo = array ();
	$amount = round($amt,2);//	转账金额
	$secondaryJsonList = "";
	$profile = cowpro_customer_profile_load_one_row_with_conditions ( $uid_from, 'moneymoremore' );
	$userFromMmmId = $profile->mmm_id;
	$profile = cowpro_customer_profile_load_one_row_with_conditions ( $uid_to, 'moneymoremore' );
	$userToMmmId = $profile->mmm_id;

	$loaninfo = new LoanInfoBean ( $userFromMmmId, $userToMmmId, $orderNo, $batchno, "", "", $amount, $amount, "内部转账", "", $secondaryJsonList );
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
	$private_key = variable_get(PRIVATE_KEY_ON_MONEYMOREMORE);
	$public_key = variable_get(PUBLIC_KEY_ON_MONEYMOREMORE);
	$rsa = new RSA ($private_key, $public_key);
	$signInfo = $rsa->sign ( $dataStr );
	$loanJsonList = urlencode ( $loanJsonList );

	$url = MMM_URL_TRANSFER;
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
					'content' => http_build_query ( $param )
			)
	);
	$context = stream_context_create ( $options );
	$response = file_get_contents ( $url, false, $context );

	// 双乾接口文档：
	// 自动转账除了会通知NotifyURL外，还会将参数以JSON字符串的形式直接输出在页面上，
	// 如果不需要审核，其中包含2个JSON，一个action为空，表示转账成功，另一个action=1，表示审核通过
	$result = json_decode($response);

	$result_mmm = array();
	if (!is_array($result)) {
		//如果双乾在处理的时候，有交易没有成功，那么$response只有一个JSON对象
		//重复转账侦测功能。
		//还款类转账执行时乾多多会检测1小时内，付款人、收款人、金额、标号四个要素。
		//若存在完全一致的转账，手动转账将弹出确认提示框；自动转账将转账失败，报错返回码为44，此功能可临时性关闭
		$result_mmm['success'] = FALSE;
		$result_mmm['message'] = $result->Message;
		$result_mmm['result_code'] = $result->ResultCode;
	} else {
		$loanList = json_decode(urldecode($result[0]->LoanJsonList));
		$orderNo = $loanList[0]->OrderNo;
		$loanNo = $loanList[0]->LoanNo;
		$result_mmm['success'] = TRUE;
		$result_mmm['message'] = $result[0]->Message;
		$result_mmm['result_code'] = $result[0]->ResultCode;
	}
	watchdog('moneymoremore_internal_trans', 'success:' . $result_mmm['success'] . ';message:' . $result_mmm['message'] . ';result_code:' . $result_mmm['result_code']);
	return $result_mmm;
}
