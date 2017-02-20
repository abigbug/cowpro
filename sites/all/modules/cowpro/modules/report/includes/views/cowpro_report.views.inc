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
	return $data;
}
