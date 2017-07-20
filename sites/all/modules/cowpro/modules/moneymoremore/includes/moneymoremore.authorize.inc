<?php
include_once 'moneymoremore.const.inc';
include_once ("libs/RSA.php");
include_once ("libs/Common.php");

/*
 * $typeOpen
 * 1:投标转账授权： 开启后，则XXXP2P公司可以以投标的名义将您账户内资金划拨至XXXP2P公司指定的乾多多账户，谨慎操作。
 * 2:还款转账授权： 开启后，则XXXP2P公司可以以还款的名义将您账户内资金划拨至XXXP2P公司指定的乾多多账户，谨慎操作。
 * 3:二次分配授权： 开启后，若XXXP2P公司对转入您乾多多账户的资金设置全额二次分配或者部分二次分配，则该笔资金到您乾多多账户后，
 * 乾多多会将二次分配的资金自动转入XXXP2P公司指定的二次分配资金接受人的乾多多账户内，谨慎操作
 */
function moneymoremore_authorize($user, $typeOpen='1,2,3') {
	$action = MMM_URL_AUTHORIZE;

	$moneymoremoreId = $user ['mmm_id'];
	$platformMoneymoremore = variable_get(PLATFORM_ACCOUNT_ON_MONEYMOREMORE);
	$authorizeTypeOpen = $typeOpen;
	$authorizeTypeClose = "";
	$common = new Common ();
	if ($common->getAntiState () == 0) {
		$randomTimeStamp = "";
	} else if ($common->getAntiState () == 1) {
		$randomTimeStamp = $common->getRandomTimeStamp ();
	}

	$remark1 = $user['uid'];
	$remark2 = '';
	$remark3 = '';

  global $base_url;
  $destination = array('destination' => url(current_path(), array('absolute' => FALSE, 'query' => drupal_get_query_parameters())));
	$returnURL = url($base_url . MMM_URL_RESPONSE . 'moneymoremore_authorize', array('query' => $destination));
	$notifyURL = $base_url . MMM_URL_NOTIRY . 'moneymoremore_authorize';

	$dataStr = $moneymoremoreId . $platformMoneymoremore . $authorizeTypeOpen . $authorizeTypeClose . $randomTimeStamp . $remark1 . $remark2 . $remark3 . $returnURL . $notifyURL;
	$private_key = variable_get(PRIVATE_KEY_ON_MONEYMOREMORE);
	$public_key = variable_get(PUBLIC_KEY_ON_MONEYMOREMORE);
	$rsa = new RSA ($private_key, $public_key);
	$signInfo = $rsa->sign ( $dataStr );

	$html = '
	<form id="formu" name="formu" action="' . $action . '" method="post">
		<input id="MoneymoremoreId" name="MoneymoremoreId" value="' . $moneymoremoreId . '" type="hidden" />
		<input id="PlatformMoneymoremore" name="PlatformMoneymoremore" value="' . $platformMoneymoremore . '" type="hidden" />
		<input id="AuthorizeTypeOpen" name="AuthorizeTypeOpen" value="' . $authorizeTypeOpen . '" type="hidden" />
		<input id="AuthorizeTypeClose" name="AuthorizeTypeClose" value="' . $authorizeTypeClose . '" type="hidden" />
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
	$h = htmlentities($html, NULL, 'UTF-8');
	//watchdog('moneymoremore_watchdog', 'moneymoremore_authorize: ' . $h, NULL, WATCHDOG_DEBUG);
	drupal_exit();
}

// 用户授权回调
function moneymoremore_authorize_callback() {
	//$msg = print_r($_POST, true);
	//watchdog('moneymoremore_watchdog', "moneymoremore_authorize_callback: $msg", NULL, WATCHDOG_DEBUG);
	if (! _moneymoremore_authorize_verify_signature ()) {
		return FALSE;
	}

	$authorize_type1 = FALSE;
	$authorize_type2 = FALSE;
	$authorize_type3 = FALSE;
	$pieces = explode ( ',', $_POST["AuthorizeTypeOpen"] );
	foreach($pieces as $piece) {
		switch ($piece) {
			case '1':
				$authorize_type1 = TRUE;
				break;
			case '2':
				$authorize_type2 = TRUE;
				break;
			case '3':
				$authorize_type3 = TRUE;
				break;
		}
	}

	if (($_POST ["ResultCode"] == '88') ||($_POST ["ResultCode"] == '08')) {
		$uid = $_POST ["Remark1"];
		$profile = cowpro_customer_profile_load_one_row_with_conditions($uid, 'moneymoremore');
		$profile->mmm_authorize_type_1 =  $authorize_type1;
		$profile->mmm_authorize_type_2 =  $authorize_type2;
		$profile->mmm_authorize_type_3 =  $authorize_type3;
		cowpro_customer_profile_save($profile);
	}
	return TRUE;
}

function _moneymoremore_authorize_verify_signature() {
	$MoneymoremoreId = $_POST ["MoneymoremoreId"];
	$PlatformMoneymoremore = $_POST ["PlatformMoneymoremore"];
	$AuthorizeTypeOpen = $_POST ["AuthorizeTypeOpen"];
	$AuthorizeTypeClose = $_POST ["AuthorizeTypeClose"];
	$AuthorizeType = $_POST ["AuthorizeType"];
	$RandomTimeStamp = $_POST ["RandomTimeStamp"];
	$Remark1 = $_POST ["Remark1"];
	$Remark2 = $_POST ["Remark2"];
	$Remark3 = $_POST ["Remark3"];
	$ResultCode = $_POST ["ResultCode"];
	$Message = $_POST ["Message"];
	$SignInfo = $_POST ["SignInfo"];

	$dataStr = $MoneymoremoreId . $PlatformMoneymoremore . $AuthorizeTypeOpen . $AuthorizeTypeClose . $AuthorizeType . $RandomTimeStamp . $Remark1 . $Remark2 . $Remark3 . $ResultCode;
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