<?php

/**
 * Implements hook_views_data().
 */
function cowpro_report_views_data() {
	$data['users']['real_name'] = array(
			'title' => '实名认证',
			'help' => '用户已通过实名认证',
			'real field' => 'uid',
			'field' => array(
					'handler' => 'cowpro_report_handler_field_real_name',
			),
	);
	$data['users']['mmm'] = array(
			'title' => '乾多多注册',
			'help' => '乾多多注册',
			'real field' => 'uid',
			'field' => array(
					'handler' => 'cowpro_report_handler_field_mmm',
			),
	);
	$data['users']['mobile_certification'] = array(
			'title' => '手机验证',
			'help' => '手机验证',
			'real field' => 'uid',
			'field' => array(
					'handler' => 'cowpro_report_handler_field_mobile',
			),
	);
	$data['users']['payment_password'] = array(
			'title' => '投标密码',
			'help' => '投标密码',
			'real field' => 'uid',
			'field' => array(
					'handler' => 'cowpro_report_handler_field_payment_password',
			),
	);
	$data['users']['referee'] = array(
			'title' => '推荐人',
			'help' => '推荐人',
			'real field' => 'uid',
			'field' => array(
					'handler' => 'cowpro_report_handler_field_referee',
			),
	);

	return $data;
}
