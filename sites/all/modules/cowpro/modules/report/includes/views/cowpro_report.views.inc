<?php

/**
 * Implements hook_views_data().
 */
function cowpro_report_views_data() {
	$data = array();

	$data['cowpro_fund_bankcard']['table']['group'] = '银行卡';

	$data['cowpro_fund_bankcard']['table']['base'] = array(
			'field' => 'bankcard_id',
			'title' => '银行卡',
			'help' => '用户的银行卡资料',
	);

	$data['cowpro_fund_bankcard']['table']['join'] = array(
			 'users' => array(
			 		'left_field' => 'uid',
			 		'field' => 'uid',
			 ),
	);

	$data['cowpro_fund_bankcard']['cardholder'] = array(
			'title' => '持卡人姓名',
			'help' => '持卡人姓名',
			'field' => array(
					'handler' => 'views_handler_field',
			),
			/*
			'real field' => 'bankcard_id',
			'field' => array(
					'handler' => 'cowpro_report_handler_field_bankcard_holder',
			),
			*/
	);
	$data['cowpro_fund_bankcard']['card_no'] = array(
			'title' => '银行卡号',
			'help' => '银行卡号',
			'field' => array(
					'handler' => 'views_handler_field',
			),
			/*
			'real field' => 'bankcard_id',
			'field' => array(
					'handler' => 'cowpro_report_handler_field_bankcard_no',
			),
			*/
	);
	$data['cowpro_fund_bankcard']['bank_name'] = array(
			'title' => '开户行',
			'help' => '开户行',
			'field' => array(
					'handler' => 'views_handler_field',
			),
			/*
			'real field' => 'bankcard_id',
			'field' => array(
					'handler' => 'cowpro_report_handler_field_bankcard_bank_name',
			),
			*/
	);
	$data['cowpro_fund_bankcard']['bank_branch'] = array(
			'title' => '开户行网点',
			'help' => '开户行网点',
			'field' => array(
					'handler' => 'views_handler_field',
			),
			/*
			'real field' => 'bankcard_id',
			'field' => array(
					'handler' => 'cowpro_report_handler_field_bankcard_bank_branch',
			),
			*/
	);
	$data['cowpro_fund_bankcard']['uid'] = array(
			'title' => '用户名',
			'help' => '用户名',
			'field' => array(
					'handler' => 'cowpro_repayment_schedule_handler_field_real_name',
					'click sortable' => TRUE,
			),
			'argument' => array(
					'handler' => 'views_handler_argument_user_uid',
					'name field' => 'name', // display this field in the summary
			),
			'filter' => array(
					'title' => '用户ID',
					'handler' => 'cowpro_users_handler_filter_user',
			),
			'sort' => array(
					'handler' => 'views_handler_sort',
			),
			'relationship' => array(
					'title' => '用户ID',
					'help' => '用户ID',
					'handler' => 'views_handler_relationship',
					'base' => 'users',
					'base field' => 'uid',
					'field' => 'uid',
					'label' => '用户',
			),
	);

	$data['users']['name_detail'] = array(
			'title' => '用户昵称与实名',
			'help' => '用户昵称与真实姓名',
			'real field' => 'uid',
			'field' => array(
					'handler' => 'cowpro_users_handler_field_name_detail',
			),
			'filter' => array(
					'handler' => 'cowpro_users_handler_filter_user',
			),
	);

	$data['users']['real_name'] = array(
			'title' => '实名认证',
			'help' => '用户已通过实名认证',
			'real field' => 'uid',
			'field' => array(
					'handler' => 'cowpro_users_handler_field_real_name',
			),
	);
	$data['users']['mmm'] = array(
			'title' => '乾多多注册',
			'help' => '乾多多注册',
			'real field' => 'uid',
			'field' => array(
					'handler' => 'cowpro_users_handler_field_mmm',
			),
	);
	$data['users']['mobile_certification'] = array(
			'title' => '手机验证',
			'help' => '手机验证',
			'real field' => 'uid',
			'field' => array(
					'handler' => 'cowpro_users_handler_field_mobile',
			),
			'filter' => array(
					'handler' => 'cowpro_users_handler_filter_mobile',
			),
	);
	$data['users']['payment_password'] = array(
			'title' => '投标密码',
			'help' => '投标密码',
			'real field' => 'uid',
			'field' => array(
					'handler' => 'cowpro_users_handler_field_payment_password',
			),
	);
	$data['users']['referee'] = array(
			'title' => '推荐人',
			'help' => '推荐人',
			'real field' => 'uid',
			'field' => array(
					'handler' => 'cowpro_users_handler_field_referee',
			),
			'filter' => array(
					'handler' => 'cowpro_users_handler_filter_referee',
			),
	);

	$data['userpoints_txn']['cowpro_operation'] = array(
			'title' => '操作、动作',
			'help' => '提供操作、动作相关的链接',
			'real field' => 'txn_id',
			'field' => array(
					'handler' => 'cowpro_userpoints_txn_handler_field_operation',
			),
			'filter' => array(
					'handler' => 'views_handler_filter_string',
			),
			'sort' => array(
					'handler' => 'views_handler_sort',
			),
	);
	$data['userpoints_txn']['cowpro_status'] = array(
			'title' => '交易状态',
			'help' => '以友好的方式显示交易状态',
			'real field' => 'status',
			'field' => array(
					'handler' => 'cowpro_userpoints_txn_handler_field_status',
			),
			'filter' => array(
					'handler' => 'cowpro_userpoints_txn_handler_filter_status_select',
			),
			'sort' => array(
					'handler' => 'views_handler_sort',
			),
	);

	return $data;
}
