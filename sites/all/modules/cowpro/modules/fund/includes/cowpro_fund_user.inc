<?php

/**
 * A module-defined block content function.
*/
function _cowpro_fund_user_contents() {
	if( user_is_logged_in() ) {
		$html = <<<html
<div class="login_block">
	<div class="login_background" style="opacity: 0.5;"></div>
	<div class="after_login">
	<div class="user_name">
	<span class="name">账户名：<span>#user_name#</span></span>
	</div>
	<div class="user_info ">
	<div class="user_img"></div>

	<div class="user_info_d">
	<a href="#user_center#">账户中心</a>
	<a href="#registration_wizard#">个人资料</a>
	<a href="#fund#">资金记录</a>
	<a href="#checkin#">#checkin_status#</a>
	</div>
	</div>
	<div class="user_money">
	<a href="#topup#">充值</a>
	<a href="#withdraw#">提现</a>
	<a class="logout" href="#logout#">退出</a>
	</div>
	</div>
	</div>
html;

		global $base_url;
		$user_center = "$base_url/user";
		$registration_wizard = "$base_url/registration_wizard";
		$fund = "$base_url/cowpro/fund";
		$topup = "$base_url/cowpro/fund/topup";
		$withdraw = "$base_url/cowpro/fund/withdraw";
		$logout = "$base_url/user/logout";
		if (cowpro_rewards_have_checked_in()) {
			$checkin = '#';
			$checkin_status = '已签到';
		} else {
			$checkin = "$base_url/cowpro/rewards/check_in";
			$checkin_status = '签到';
		}
		$uid = $GLOBALS ['user']->uid;
		$html = str_replace('#user_name#', $GLOBALS ['user']->name, $html);
		$html = str_replace('#user_center#', $user_center, $html);
		$html = str_replace('#registration_wizard#', $registration_wizard, $html);
		$html = str_replace('#fund#', $fund, $html);
		$html = str_replace('#topup#', $topup, $html);
		$html = str_replace('#withdraw#', $withdraw, $html);
		$html = str_replace('#checkin#', $checkin, $html);
		$html = str_replace('#checkin_status#', $checkin_status, $html);
		$html = str_replace('#logout#', $logout, $html);
		$html = str_replace('#user_name#', $GLOBALS ['user']->name, $html);
		$result = array(
				'#markup' => $html,
		);
		return $result;
	}else{
		$html = <<<html
<div class="login_block">
      <div class="login_background" style="opacity: 0.5;"></div>
           <div class="after_login">
                <div class="fast_login">快速登陆</div>
                #form#
           </div>
     </div>
</div>
html;

		$form = drupal_get_form("user_login");
		$html = str_replace('#form#', render($form), $html);
		$result = array(
				'#markup' => $html,
		);
		return $result;
	}


}
