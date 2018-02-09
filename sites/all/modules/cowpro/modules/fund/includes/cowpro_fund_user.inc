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
        <span class="name"><a class="logout" href="#logout#">退出</a></span>
	</div>
	<div class="user_info ">
	<div class="user_img"></div>
	<div class="user_info_d">
          <div>我的待收款：#receivable_amount#</div>
          <div>可提现余额：#withdraw_ye#</div>
          <div>我 的 积 分：#points#</div>
          <div>我 的 奖 金：#points_money#</div>
	</div>
	</div>
        <div class="user_money">
	<a href="#user_center#">账户中心</a>
	<a href="#fund#">资金记录</a>
	<a href="#checkin#">#checkin_status#</a>
        </div>
	<div class="user_money">
	<a href="#registration_wizard#">个人资料</a>
	<a href="#topup#">充值</a>
	<a href="#withdraw#">提现</a>
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
                $receivable_amount=cowpro_issuing_get_user_status($uid);                        //我的待收款
                $balance = custodian_get_balance($GLOBALS ['user']);
                $withdraw_ye = 0;
                if ($balance) {
                    $withdraw_ye = $balance ['balance'];                //可提现余额
                }
                $points = userpoints_get_current_points($uid);           //我的积分
                $points_money=userpoints_get_current_points($uid, _cowpro_shop_get_user_points_money_tid());   //我的奖金
                $points_money = $points_money / 100;

		$html = str_replace('#user_name#', $GLOBALS ['user']->name, $html);
		$html = str_replace('#user_center#', $user_center, $html);
		$html = str_replace('#registration_wizard#', $registration_wizard, $html);
		$html = str_replace('#fund#', $fund, $html);
		$html = str_replace('#topup#', $topup, $html);
		$html = str_replace('#withdraw#', $withdraw, $html);
		$html = str_replace('#checkin#', $checkin, $html);
		$html = str_replace('#checkin_status#', $checkin_status, $html);
		$html = str_replace('#logout#', $logout, $html);
		$html = str_replace('#receivable_amount#', $receivable_amount, $html);
		$html = str_replace('#withdraw_ye#', $withdraw_ye, $html);
		$html = str_replace('#points#', $points, $html);
		$html = str_replace('#points_money#', $points_money, $html);
		$result = array(
				'#markup' => $html,
		);
		return $result;
	}else{
		$html = <<<html
<div class="login_block">
      <div class="login_background" style="opacity: 0.5;"></div>
           <div class="after_login">
                <div class="fast_login">快速登录</div>
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
