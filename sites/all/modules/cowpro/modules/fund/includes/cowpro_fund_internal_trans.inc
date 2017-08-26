<?php
function cowpro_fund_internal_trans($form, &$form_state) {
	$form = array ();
	$form['user_to'] = array(
			'#type' => 'textfield',
			'#title' => '转账给：',
			'#description' => '收款人昵称(用户名)',
			'#maxlength' => 60,
			'#default_value' => '',
			'#autocomplete_path' =>	'cowpro/referee/autocomplete',
			'#weight' => -1,
			'#reguired' => TRUE,
	);

	GLOBAL $user;
	$balance = custodian_get_balance($user);
	$withdraw = 0;
	if ($balance) {
		$withdraw = $balance ['withdraw'];
	}

	$form ['withdraw_balance'] = array (
			'#markup' => "<p>可转账金额(元)：$withdraw</p>",
	);
	$form ['amount'] = array (
			'#type' => 'numberfield',
			'#title' => '转账金额(元)',
			'#step' => 0.01,
			'#min' => 0,
			'#max' => 999999,
			'#default_value' => 0,
			'#input' => TRUE
	);

	$form['submit'] = array(
			'#type' => 'submit',
			'#value' => t('Submit'),
			'#id' => 'submit',
			'#ajax' => array(
					'callback' => 'cowpro_fund_internal_trans_submit',
					'method' => 'replace',
					'wrapper' => 'submit',
			),
			//'#submit' => array('cowpro_fund_internal_trans_submit'),
	);
	return $form;
}

function cowpro_fund_internal_trans_validate($form, &$form_state) {
	if (( float ) trim ( $form_state ['input'] ['amount'] ) <= 0) {
		form_error ( $form ['amount'], "请填写有效的转账金额" );
	}
}

function cowpro_fund_internal_trans_submit($form, &$form_state) {
	if (isset($form_state['input']['agree']) && ($form_state['input']['agree'] == '同意转账')) {
		return cowpro_fund_internal_trans_do($form, $form_state);
	}
	$amount = $form_state ['input'] ['amount'];
	$uid_to = -1;
	$user_to_string = $form_state ['input'] ['user_to'];
	$matches = array();
	$regex = '/^\d+$/';
	if(preg_match($regex, $user_to_string, $matches)){
		if ($user_to_string) {
			$result = db_select('cowpro_customer_profile', 'profile')->fields('profile', array('uid'))->condition('type', 'mobile')->condition('search_field', $user_to_string)->range(0, 1)->execute()->fetchAssoc();
			if ($result) {
				$uid_to = $result['uid'];
			}
		}
	} else {
		$user = user_load_by_name($user_to_string);
		if ($user) {
			$uid_to = $user->uid;
		}
	}
	return cowpro_fund_internal_trans_confirm($uid_to, $amount, $form_state);
}

/**
 * 确认转账对像
 */
function cowpro_fund_internal_trans_confirm($uid_to, $amount, &$form_state) {
	$form = array();
	$uid_from = $GLOBALS['user']->uid;
	$form_state['uid_from'] = $uid_from;
	$form_state['uid_to'] = $uid_to;
	$form_state['amount'] = $amount;
	$form_state['agree'] = TRUE;
	$user_to = user_load($uid_to);
	$profile_real_name = cowpro_customer_profile_load_one_row_with_conditions ( $uid_to, 'real_name' );
	if ($profile_real_name) {
		$real_name = $profile_real_name->name;
	} else {
		$real_name = '';
	}
	$real_name = _cowpro_fund_internal_trans_utf_substr2($real_name);
	$msg = '向 ' . $user_to->name . '(' . $real_name . ')' . ' 转账 ' . $amount . '元';
	$form['information'] = array(
			'#markup' => "<p>$msg</p>",
	);
	global $base_url;
	$form ['agree'] = array (
			'#type' => 'submit',
			'#id' => 'agree',
			'#name' => 'agree',
			'#value' => '同意转账',
			'#weight' => 100,
			'#ajax' => array(
					'callback' => 'cowpro_fund_internal_trans_do',
					'method' => 'replace',
					'wrapper' => 'submit',
			),
	);

	$form ['cancel'] = array (
			'#type' => 'submit',
			'#value' => '取消',
			'#attributes' => array('onClick' => 'window.location("#"); return false;'),
			'#weight' => 200
	);
	return $form;
}

function cowpro_fund_internal_trans_do($form, &$form_state) {
	$uid_from = $form_state['uid_from'];
	$uid_to = $form_state['uid_to'];
	$amount = $form_state['amount'];
	watchdog('trans', "$uid_from;$uid_to;$amount");

	$result = custodian_cowpro_fund_internal_trans($uid_from, $uid_to, $amount);


	$form = array();
	$form['information'] = array(
			'#markup' => "<p>helloooo</p>",
	);
	return $form;
}

function __cowpro_fund_internal_trans_confirm_form_submit(&$form, &$form_state) {
	if ($form_state ['values'] ['op'] === $form_state ['values'] ['submit']) {
		$uid_to = $form_state['uid_to'];
		$amount = $form_state['amount'];
		$uid_from = $GLOBALS['user']->uid;

		$result = custodian_cowpro_fund_internal_trans($uid_from, $uid_to, $amount);
		if ($result['success']) {
			$message = '转账操作完成';
			drupal_set_message($message);
		} else {
			$message = '转账操作失败:' . $result['message'] . '<br/>代码：' . $result['result_code'];
			drupal_set_message($message, 'error');
		}

		ctools_include ( 'modal' );
		ctools_include ( 'ajax' );
		$commands = array ();
		$commands[] = ctools_ajax_command_reload();
		print ajax_render ( $commands );
		exit ();
	} else {
		$commands = array ();
		$commands [] = ctools_modal_command_dismiss ();
		print ajax_render ( $commands );
		exit ();
	}
}

function _cowpro_fund_internal_trans_utf_substr2($str){
	$pa = "/[\x01-\x7f]|[\xc2-\xdf][\x80-\xbf]|\xe0[\xa0-\xbf][\x80-\xbf]|[\xe1-\xef][\x80-\xbf][\x80-\xbf]|\xf0[\x90-\xbf][\x80-\xbf][\x80-\xbf]|[\xf1-\xf7][\x80-\xbf][\x80-\xbf][\x80-\xbf]/";
	preg_match_all($pa, $str, $t_string);
	if (count($t_string[0])==1) {
		return $str;
	} else if(count($t_string[0])==2) {
		return _cowpro_fund_internal_trans_cut_str($str, 1, 0).'****';
	} else {
		return _cowpro_fund_internal_trans_cut_str($str, 1, 0).'****';//.cut_str($str, 1, -1);
	}
}

function _cowpro_fund_internal_trans_cut_str($string, $sublen, $start = 0, $code = 'UTF-8')
{
	if($code == 'UTF-8')
	{
		$pa = "/[\x01-\x7f]|[\xc2-\xdf][\x80-\xbf]|\xe0[\xa0-\xbf][\x80-\xbf]|[\xe1-\xef][\x80-\xbf][\x80-\xbf]|\xf0[\x90-\xbf][\x80-\xbf][\x80-\xbf]|[\xf1-\xf7][\x80-\xbf][\x80-\xbf][\x80-\xbf]/";
		preg_match_all($pa, $string, $t_string);

		if(count($t_string[0]) - $start > $sublen) return join('', array_slice($t_string[0], $start, $sublen));
		return join('', array_slice($t_string[0], $start, $sublen));
	}
	else
	{
		$start = $start*2;
		$sublen = $sublen*2;
		$strlen = strlen($string);
		$tmpstr = '';

		for($i=0; $i< $strlen; $i++)
		{
			if($i>=$start && $i< ($start+$sublen))
			{
				if(ord(substr($string, $i, 1))>129)
				{
					$tmpstr.= substr($string, $i, 2);
				}
				else
				{
					$tmpstr.= substr($string, $i, 1);
				}
			}
			if(ord(substr($string, $i, 1))>129) $i++;
		}
		return $tmpstr;
	}
}
