<?php
include_once 'moneymoremore.const.inc';
include_once ("libs/RSA.php");
include_once ("libs/Common.php");

/**
 * 创建新帐户
 *
 * @param array $user
 */
function moneymoremore_create_new_acct($user) {
	$action = MMM_URL_REGISTER;

	/*
	 * 1表示全自动，
	 * 2表示半自动
	 * 全自动会生成随机的登录密码和支付密码发送到用户的手机，安保问题需要登录乾多多后台设置
	 */
	$registerType = "2";

	/*
	 * 空表示个人账户
	 * 1表示企业账户
	 */
	$accountType = "";
	$uid = $user['uid'];
	$mobile = $user['mobile_number'];
	$email = '';
	$realName = $user['name'];
	$identificationNo = $user['id_no'];
	$image1 = "";
	$image2 = "";
	$loanPlatformAccount = $mobile;
	$platformMoneymoremore = variable_get(PLATFORM_ACCOUNT_ON_MONEYMOREMORE);

	$common = new Common ();
	if ($common->getAntiState () == 0) {
		$randomTimeStamp = "";
	} else if ($common->getAntiState () == 1) {
		$randomTimeStamp = $common->getRandomTimeStamp ();
	}

	$remark1 = $uid;
	$remark2 = '';
	$remark3 = '';

  global $base_url;
  $destination = array('destination' => url(current_path(), array('absolute' => FALSE, 'query' => drupal_get_query_parameters())));
	$returnURL = url($base_url . MMM_URL_RESPONSE . 'moneymoremore_create_new_acct', array('query' => $destination));
	$notifyURL = $base_url . MMM_URL_NOTIRY . 'moneymoremore_create_new_acct';

	$dataStr = $registerType . $accountType . $mobile . $email . $realName . $identificationNo . $image1 . $image2 . $loanPlatformAccount . $platformMoneymoremore . $randomTimeStamp . $remark1 . $remark2 . $remark3 . $returnURL . $notifyURL;
	if ($common->getAntiState () == 1) {
		$dataStr = strtoupper ( md5 ( $dataStr ) );
	}
	$private_key = variable_get(PRIVATE_KEY_ON_MONEYMOREMORE);
	$public_key = variable_get(PUBLIC_KEY_ON_MONEYMOREMORE);
	$rsa = new RSA ($private_key, $public_key);
	$signInfo = $rsa->sign ( $dataStr );

	$html = '
	<form id="formu" name="formu" action="' . $action . '" method="post">
		<input id="RegisterType" name="RegisterType" value="' . $registerType . '" type="hidden" />
		<input id="AccountType" name="AccountType" value="' . $accountType . '" type="hidden" />
		<input id="Mobile" name="Mobile" value="' . $mobile . '" type="hidden" />
		<input id="Email" name="Email" value="' . $email . '" type="hidden" />
		<input id="RealName" name="RealName" value="' . $realName . '" type="hidden" />
		<input id="IdentificationNo" name="IdentificationNo" value="' . $identificationNo . '" type="hidden" />
		<input id="Image1" name="Image1" value="' . $image1 . '" type="hidden" />
		<input id="Image2" name="Image2" value="' . $image2 . '" type="hidden" />
		<input id="LoanPlatformAccount" name="LoanPlatformAccount" value="' . $loanPlatformAccount . '" type="hidden" />
		<input id="PlatformMoneymoremore" name="PlatformMoneymoremore" value="' . $platformMoneymoremore . '" type="hidden" />
		<input id="RandomTimeStamp" name="RandomTimeStamp" value="' . $randomTimeStamp . '" type="hidden" />
		<input id="Remark1" name="Remark1" value="' . $remark1 . '" type="hidden" />
		<input id="Remark2" name="Remark2" value="' . $remark2 . '" type="hidden" />
		<input id="Remark3" name="Remark3" value="' . $remark3 . '" type="hidden" />
		<input id="ReturnURL" name="ReturnURL" value="' . $returnURL . '" type="hidden" />
		<input id="NotifyURL" name="NotifyURL" value="' . $notifyURL . '" type="hidden" />
		<input id="SignInfo" name="SignInfo" value="' . $signInfo . '" type="hidden" />
	</form>
	<script language="javascript">window.onload=function(){document.formu.submit();}</script>
';

	echo $html;
	$h = htmlentities($html, NULL, 'UTF-8');
	watchdog('moneymoremore', 'moneymoremore_create_new_acct: ' . $h, NULL, WATCHDOG_DEBUG);
	drupal_exit();
}

// 创建新帐户回调
function moneymoremore_create_new_acct_callback() {
	//$msg = print_r($_POST, true);
	//watchdog('moneymoremore', "moneymoremore_create_new_acct_callback: $msg", NULL, WATCHDOG_DEBUG);
	if (! _moneymoremore_create_new_acct_verify_signature ()) {
		return FALSE;
	}
	if (($_POST ["ResultCode"] == '88') || ($_POST ["ResultCode"] == '16')) {//88:绑定成功；16：网贷平台账号已绑定
		$uid = $_POST ["Remark1"];
		$profile = cowpro_customer_profile_new('moneymoremore', $uid);
		$profile->mmm_account_number =  $_POST ["AccountNumber"];//乾多多数字账户(可用于登录)
		$profile->mmm_id = $_POST ["MoneymoremoreId"];//用户的乾多多标识(以m开头)
		$profile->mmm_auth_state = $_POST ["AuthState"];//实名认证状态(1.未实名认证,2.快捷支付认证,3.其他认证)
		$profile->mmm_result_code = $_POST ["ResultCode"];//返回码(88表示成功,其它代码参考《乾多多自主清算系统接口参数说明.doc》)
		$profile->mmm_result_message = $_POST ["Message"];//返回信息(与result_code对应的文字信息)
		$profile->verified = 1;
		$profile->uid = $uid;
		cowpro_customer_profile_save($profile);
	}
	return TRUE;
}

function _moneymoremore_create_new_acct_verify_signature() {
	$AccountType = $_POST ["AccountType"];
	$AccountNumber = $_POST ["AccountNumber"];
	$Mobile = $_POST ["Mobile"];
	$Email = $_POST ["Email"];
	$RealName = $_POST ["RealName"];
	$IdentificationNo = $_POST ["IdentificationNo"];
	$LoanPlatformAccount = $_POST ["LoanPlatformAccount"];
	$MoneymoremoreId = $_POST ["MoneymoremoreId"];
	$PlatformMoneymoremore = $_POST ["PlatformMoneymoremore"];
	$AuthFee = $_POST ["AuthFee"];
	$AuthState = $_POST ["AuthState"];
	$RandomTimeStamp = $_POST ["RandomTimeStamp"];
	$Remark1 = $_POST ["Remark1"];
	$Remark2 = $_POST ["Remark2"];
	$Remark3 = $_POST ["Remark3"];
	$ResultCode = $_POST ["ResultCode"];
	$Message = $_POST ["Message"];
	$SignInfo = $_POST ["SignInfo"];

	$dataStr = $AccountType . $AccountNumber . $Mobile . $Email . $RealName . $IdentificationNo . $LoanPlatformAccount . $MoneymoremoreId . $PlatformMoneymoremore . $AuthFee . $AuthState . $RandomTimeStamp . $Remark1 . $Remark2 . $Remark3 . $ResultCode;
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
?>