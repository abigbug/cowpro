<?php
include_once 'moneymoremore.const.inc';
include_once 'moneymoremore.fun.inc';
include_once ("libs/RSA.php");
include_once ("libs/Common.php");
include_once ("libs/LoanInfoBean.php");
include_once ("libs/LoanInfoSecondaryBean.php");

/**
 * 投标
 *
 * @param int $uid
 *        	用户ID
 * @param float $amount
 *        	投资金额
 * @param int $nid
 *        	标的的 node id
 * @return string
 */
function moneymoremore_bid($uid, $amount, $nid, $journal_id) {
	$url = MMM_URL_TRANSFER;

	global $base_url;
	$destination = array('destination' => url(current_path(), array('absolute' => FALSE, 'query' => drupal_get_query_parameters())));
	$returnURL = url($base_url . MMM_URL_RESPONSE . 'moneymoremore_bid', array('query' => $destination));
	$notifyURL = $base_url . MMM_URL_NOTIRY . 'moneymoremore_bid';

	$platformMoneymoremore = variable_get ( PLATFORM_ACCOUNT_ON_MONEYMOREMORE );

	//todo 要有一个扩展接口可以定义“借款人手续费”
	$lenderFee = 0; // 借款人手续费

	$profile = cowpro_customer_profile_load_one_row_with_conditions ( $uid, 'moneymoremore' );
	$userLoanOutMmmId = $profile->mmm_id;

	$node = node_load($nid);
	$wrapper = entity_metadata_wrapper('node', $node);
	$applicant = $wrapper->field_applicant->value();
	$profile = cowpro_customer_profile_load_one_row_with_conditions ( $applicant->uid, 'moneymoremore' );
	$userLoanInMmmId = $profile->mmm_id;
	$loanAmount = $node->field_issuing[LANGUAGE_NONE][0]['loan_amounts'];//贷款总额

	$orderNo = sprintf("%'.08d-%d", $journal_id, _moneymoremore_get_microtime());
	$batchNo = sprintf("%'.08d-%d", $nid, $node->created);

	$secondaryJsonList = "";
	if ($lenderFee != 0) {
		$secondary = new LoanInfoSecondaryBean ( $platformMoneymoremore, $lenderFee, "手续费", $nid );
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

	$loaninfo = new LoanInfoBean ( $userLoanOutMmmId, $userLoanInMmmId, $orderNo, $batchNo, "", "", $amount, $loanAmount, "投标", "", $secondaryJsonList );
	$arrloaninfo = array (
			'0' => array (
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
			)
	);
	$loanJsonList = json_encode ( $arrloaninfo );
	$transferAction = "1"; // 1.投标;2.还款;3.其他
	$loanAction = "2"; // 1.手动转账; 2.自动转账; 手动弹出密码验证页面 自动不弹
	$transferType = "2"; // 1.桥连; 2.直连
	$needAudit = ""; // 空.需要审核;1.自动通过
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
					'content' => http_build_query ( $param )
			)
	);
	$context = stream_context_create ( $options );
	$response = file_get_contents ( $url, false, $context );
	$result = json_decode ( $response );
	$LoanJsonList = $result->LoanJsonList;
	$LoanJsonList = urldecode ( $LoanJsonList );
	$arrloaninfo = json_decode ( $LoanJsonList );
	$loaninfo = $arrloaninfo [0];
	$external_reference_id = $loaninfo->LoanNo;
	//_moneymoremore_bid_process_response($result);
	$resultCode = $result->ResultCode;
	$message = $result->Message;
	$data = array();
	$data['interface_module'] = 'moneymoremore';
	$data['value'] = $result;

	$result_mmm = array();
	if ($resultCode === '88') {
		$result_mmm['success'] = TRUE;
	} else {
		$result_mmm['success'] = FALSE;
	}
	$result_mmm['external_reference_id'] = $external_reference_id;
	$result_mmm['data'] = $data;
	$result_mmm['message'] = $message;
	$result_mmm['result_code'] = $resultCode;
	return 	$result_mmm;
}

/*
function _moneymoremore_bid_process_response($result) {
	$LoanJsonList = $result->LoanJsonList;
	$LoanJsonList = urldecode ( $LoanJsonList );
	$arrloaninfo = json_decode ( $LoanJsonList );
	$loaninfo = $arrloaninfo [0];
	$orderNo = $loaninfo->OrderNo;
	$batchNo = $loaninfo->BatchNo;

	$entity = entity_load_single('cowpro_fund_journal', $orderNo);
	if ($result->ResultCode == '88') {
		$status = TRUE;
	} else {
		$status = FALSE;
	}
	$entity->status = $status;
	$entity->external_reference_id = $loaninfo->LoanNo;
	$data = array();
	$data['interface_module'] = 'moneymoremore';
	$data['value'] = $result;
	//$entity->data = serialize($data);
	$entity->data = $data;
	entity_get_controller('cowpro_fund_journal')->save($entity);
}
*/

/**
 * 投标回调
 */
function moneymoremore_bid_callback() {
	//$msg = print_r($_POST, true);
	//watchdog('moneymoremore', "moneymoremore_bid_callback: $msg", NULL, WATCHDOG_DEBUG);
	if (! _moneymoremore_bid_verify_signature ()) {
		return FALSE;
	}
	/*
	$LoanJsonList = $_POST ["LoanJsonList"];
	$LoanJsonList = urldecode ( $LoanJsonList );
	$arrloaninfo = json_decode ( $LoanJsonList );
	$loaninfo = $arrloaninfo [0];
	$orderNo = $loaninfo->OrderNo;
	$batchNo = $loaninfo->BatchNo;

	$entity = entity_load_single('cowpro_fund_journal', $orderNo);
	if ($_POST ["ResultCode"] == '88') {
		$status = TRUE;
	} else {
		$status = FALSE;
	}
	$entity->status = $status;
	$entity->external_reference_id = $loaninfo->LoanNo;
	$data = array();
	$data['interface_module'] = 'moneymoremore';
	foreach($_POST as $key=>$value){
		$data[$key] = $value;
	}
	unset($data['SignInfo']);
	//$entity->data = serialize($data);
	$entity->data = $data;
	entity_get_controller('cowpro_fund_journal')->save($entity);

	cowpro_issuing_bid_finished($batchNo);
	*/
	return TRUE;
}

function _moneymoremore_bid_verify_signature() {
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
