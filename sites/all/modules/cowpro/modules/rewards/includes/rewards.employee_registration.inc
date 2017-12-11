<?php
function cowpro_rewards_employee_registration_form($form, &$form_state) {
	$form ['description'] = array (
			'#type' => 'markup',
			'#markup' => t ( '请将员工手机号码填入下面编辑框，每行一个号码（长度为十一位数字），系统将逐行按手机号码查找用户并将其标记为“员工”.<br/><br/>' ),
	);
	$form['phone_list'] = array(
			'#title' => '手机号码',
			'#type' => 'textarea',
	);
	$form ['submit'] = array (
			'#type' => 'submit',
			'#value' => '开始登记',
	);
	return $form;
}

/**
 * Submit handler.
 *
 * @param array $form
 *        	Form API form.
 * @param array $form_state
 *        	Form API form.
 */
function cowpro_rewards_employee_registration_form_submit($form, &$form_state) {
	$batch = cowpro_rewards_employee_registration_go_batch($form_state['input']['phone_list']);
	batch_set ( $batch );
}
function cowpro_rewards_employee_registration_go_batch($phone_list) {
	$count = 0;
	$operations = array ();
	foreach(explode(PHP_EOL, $phone_list) as $phone_num) {
		$phone = _cowpro_rewards_clearInvisibleCharacter ($phone_num);
		if (empty($phone)) {
			continue;
		}
		$count ++;
		$operations [] = array (
				'cowpro_rewards_employee_registration_op_user',
				array (
						$phone,
						t ( '(登记员工，手机号码 @phone)', array (
								'@phone' => $phone,
						) )
				)
		);
	}

	drupal_set_message ( t ( '登记员工，共  @num 项', array (
			'@num' => $count,
	) ) );

	$batch = array (
		'operations' => $operations,
		'finished' => 'cowpro_rewards_employee_registration_batch_finished',
		'file' => drupal_get_path('module', 'rewards') . '/includes/rewards.employee_registration.inc',
	);
	return $batch;
}
function cowpro_rewards_employee_registration_op_user($phone, $operation_details, &$context) {
	$isMbl = preg_match("/^1[34578]\d{9}$/", $phone) ? true : false;
	if( !$isMbl ) {
		$context ['message'] = t ( '手机号码格式不正确！"@phone"', array (
				'@phone' => $phone,
		) );
		$context['results'][] = $context ['message'];
		return;
	}

	$result = db_select('cowpro_customer_profile', 'profile')->fields('profile', array('uid', 'search_field'))->condition('type', 'mobile')->condition('search_field', $phone)->execute()->fetchAssoc();
	if (! $result) {
		$context ['message'] = t ( '手机号码未找到！"@phone"', array (
				'@phone' => $phone,
		) );
		$context['results'][] = $context ['message'];
		return;
	}
	$uid = $result['uid'];
	$user = user_load($uid);
	$role = user_role_load_by_name('员工');
	if (user_has_role($role->rid, $user)) {
		$context ['message'] = t ( '老员工(@name)："@phone"', array (
				'@name' => $user->name,
				'@phone' => $phone,
		) );
		$context['results'][] = $context ['message'];
		return;
	} else {
		user_multiple_role_edit(array($user->uid), 'add_role', $role->rid);
		$context ['message'] = t ( '新员工登记 (@name)： "@phone"', array (
				'@name' => $user->name,
				'@phone' => $phone,
		) );
		$context['results'][] = $context ['message'];
	}
}
function cowpro_rewards_employee_registration_batch_finished($success, $results, $operations) {
	if ($success) {
		// Here we could do something meaningful with the results.
		// We just display the number of ojbect we processed...
		/*
		drupal_set_message ( t ( '共迁移用户 @count 个.', array (
		'@count' => count ( $results )
		) ) );
		*/
		foreach ($results as $result) {
			drupal_set_message($result);
		}
		drupal_set_message('登记完成');
	} else {
		// An error occurred.
		// $operations contains the operations that remained unprocessed.
		$error_operation = reset ( $operations );
		drupal_set_message ( t ( 'An error occurred while processing @operation with arguments : @args', array (
				'@operation' => $error_operation [0],
				'@args' => print_r ( $error_operation [0], TRUE )
		) ), 'error' );
	}
}

/**
 * 清理字符串中的部分不可见控制字符
 *
 * @param string $string 待处理字符串
 * @return string 处理后的字符串
 * @author fising(at)qq.com
 */
function _cowpro_rewards_clearInvisibleCharacter($string = '')
{
	/* 排除 tab, \n, \r 三个字符 */
	//$do_not_searches = array(chr(9), chr(10), chr(13));
	$do_not_searches = array();

	/* 需清理的字符列表 */
	$searches = array();

	for ($i = 0; $i <= 31; $i++)
	{
		if (!in_array(chr($i), $do_not_searches))
		{
			$searches[] = chr($i);
		}
	}

	$searches[] = chr(127);

	return str_replace($searches, '', $string);
}