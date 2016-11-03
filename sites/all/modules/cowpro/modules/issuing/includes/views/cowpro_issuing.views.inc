<?php

/**
 * Implements hook_field_views_data().
 */
function cowpro_issuing_field_views_data($field) {
	$data = field_views_field_default_views_data($field);
	$data['field_data_field_issuing']['table']['group']  = 'Issuing';
	$data['field_data_field_issuing']['table']['entity type']  = 'node';

	foreach ($data as $table_name => $table_data) {
		foreach ($table_data as $field_name => $field_data) {
			if (isset($field_data['filter']['field_name']) && $field_name == 'field_issuing_status') {
				$data[$table_name][$field_name]['filter']['handler'] = 'cowpro_issuing_handler_filter_status_select';
			}
		}
	}

	// Expose links to operate on the issuing.
	$data['field_data_field_issuing']['view_issuing'] = array(
			'field' => array(
					'title' => t('Operations'),
					'help' => '提供与《贷款申请表》相关的上下文菜单',
					'handler' => 'cowpro_issuing_handler_field_issuing_operations',
			),
	);

	// Expose links to operate on the node.
	$data['field_data_field_issuing']['view_node'] = array(
			'field' => array(
					'title' => t('Operations'),
					'help' => '提供与 node 相关的上下文菜单',
					'handler' => 'cowpro_issuing_handler_field_node_operations',
			),
	);

	// Expose links to operate on the creditor assignment.
	$data['field_data_field_issuing']['view_creditor_assignment'] = array(
			'field' => array(
					'title' => t('Operations'),
					'help' => '提供与"债权转让"相关的上下文菜单',
					'handler' => 'cowpro_creditor_assignment_handler_field_operations',
			),
	);

	return $data;
}

/**
 * Implements hook_views_data().
 */
function cowpro_issuing_views_data() {
	// Basic table information.

	// Define the base group of this table. Fields that don't
	// have a group defined will go into this field by default.
	$data['cowpro_repayment_schedule']['table']['group']  = '还款详情';

	$data['cowpro_repayment_schedule']['table']['base'] = array(
			'title' => '还款详情',
			'help' => '还款详情',
	);

	// For other base tables, explain how we join
	$data['cowpro_repayment_schedule']['table']['join'] = array(
			'node' => array(
					'left_field' => 'nid',
					'field' => 'issuing_id',
			),
			/*
			'user' => array(
					'left_field' => 'uid',
					'field' => 'payer_uid',
			),
			'user' => array(
					'left_field' => 'uid',
					'field' => 'receiver_uid',
			),
			*/
	);

	// ----------------------------------------------------------------
	// Fields
	// The schedule_id field
	/*
	$data['cowpro_repayment_schedule']['schedule_id_idx'] = array(
			'title' => 'schedule_id',
			'help' => '流水号',
			'field' => array(
					'handler' => 'views_handler_field_numeric',
			),
			'sort' => array(
					'handler' => 'views_handler_sort',
			),
			'filter' => array(
					'handler' => 'views_handler_filter_numeric',
			),
	);
	*/

	// Expose the issuing_id.
	/*
	$data['cowpro_repayment_schedule']['issuing_id'] = array(
			'title' => '贷款申请表',
			'help' => '与该资金明细账相关的贷款申请表.',
			'field' => array(
					'handler' => 'views_handler_field_numeric',
			),
			'filter' => array(
					'handler' => 'views_handler_filter_numeric',
			),
			'argument' => array(
					'handler' => 'views_handler_argument_numeric',
			),
			'sort' => array(
					'handler' => 'views_handler_sort',
			),
			'relationship' => array(
					'handler' => 'views_handler_relationship',
					'base' => 'node',
					'field' => 'nid',
					'label' => '贷款申请表',
			),
	);
	*/
	$data['cowpro_repayment_schedule']['issuing_id'] = array(
			'title' => '贷款名称',
			'help' => '贷款名称.',
			'field' => array(
					'handler' => 'cowpro_issuing_handler_field_title',
			),
			'filter' => array(
					'handler' => 'views_handler_filter_numeric',
			),
			'argument' => array(
					'handler' => 'views_handler_argument_numeric',
			),
			'sort' => array(
					'handler' => 'views_handler_sort',
			),
			'relationship' => array(
					'handler' => 'views_handler_relationship',
					'base' => 'node',
					'field' => 'nid',
					'label' => '贷款申请表',
			),
	);

	// The period field
	$data['cowpro_repayment_schedule']['period'] = array(
			'title' => 'period',
			'help' => '期次',
			'field' => array(
					'handler' => 'views_handler_field_numeric',
			),
			'sort' => array(
					'handler' => 'views_handler_sort',
			),
			'filter' => array(
					'handler' => 'views_handler_filter_numeric',
			),
	);

	// The payer_uid field
	$data['cowpro_repayment_schedule']['payer_uid'] = array(
			'title' => '付款方',
			'help' => '付款方用户',
			'field' => array(
					'handler' => 'cowpro_issuing_handler_field_payer_name',
					'click sortable' => TRUE,
			),
			'argument' => array(
					'handler' => 'views_handler_argument_user_uid',
					'name field' => 'name', // display this field in the summary
			),
			'filter' => array(
					'title' => '付款方用户ID',
					'handler' => 'views_handler_filter_user_name',
			),
			'sort' => array(
					'handler' => 'views_handler_sort',
			),
			'relationship' => array(
					'title' => '付款方用户ID',
					'help' => '付款方用户ID',
					'handler' => 'views_handler_relationship',
					'base' => 'users',
					'base field' => 'uid',
					'field' => 'payer_uid',
					'label' => '用户',
			),
	);

	// The receiver_uid field
	$data['cowpro_repayment_schedule']['receiver_uid'] = array(
			'title' => '收款方',
			'help' => '收款方用户',
			'field' => array(
					'handler' => 'cowpro_issuing_handler_field_receiver_name',
					'click sortable' => TRUE,
			),
			'argument' => array(
					'handler' => 'views_handler_argument_user_uid',
					'name field' => 'name', // display this field in the summary
			),
			'filter' => array(
					'title' => '收款方用户ID',
					'handler' => 'views_handler_filter_numeric',
			),
			'sort' => array(
					'handler' => 'views_handler_sort',
			),
			'relationship' => array(
					'title' => '收款方用户ID',
					'help' => '收款方用户ID',
					'handler' => 'views_handler_relationship',
					'base' => 'users',
					'base field' => 'uid',
					'field' => 'receiver_uid',
					'label' => '用户',
			),
	);

	// The status field
	$data['cowpro_repayment_schedule']['status'] = array(
			'title' => '状态',
			'help' => '状态.',
			'field' => array(
					'handler' => 'cowpro_repayment_schedule_handler_field_status',
			),
			'sort' => array(
					'handler' => 'views_handler_sort',
			),
			'filter' => array(
					'handler' => 'cowpro_repayment_schedule_handler_filter_status',
			),
	);

	// The payable_amount field
	$data['cowpro_repayment_schedule']['payable_amount'] = array(
			'title' => 'payable_amount',
			'help' => '应付款金额',
			'field' => array(
					'handler' => 'cowpro_fund_journal_handler_field_amount',
					'float' => TRUE,
			),
			'sort' => array(
					'handler' => 'views_handler_sort',
			),
			'filter' => array(
					'handler' => 'views_handler_filter_numeric',
			),
	);

	// The paid_amount field
	$data['cowpro_repayment_schedule']['paid_amount'] = array(
			'title' => 'paid_amount',
			'help' => '已付款金额',
			'field' => array(
					'handler' => 'cowpro_fund_journal_handler_field_amount',
					'float' => TRUE,
			),
			'sort' => array(
					'handler' => 'views_handler_sort',
			),
			'filter' => array(
					'handler' => 'views_handler_filter_numeric',
			),
	);

	// The receivable_amount field
	$data['cowpro_repayment_schedule']['receivable_amount'] = array(
			'title' => 'receivable_amount',
			'help' => '应收款金额',
			'field' => array(
					'handler' => 'cowpro_fund_journal_handler_field_amount',
					'float' => TRUE,
			),
			'sort' => array(
					'handler' => 'views_handler_sort',
			),
			'filter' => array(
					'handler' => 'views_handler_filter_numeric',
			),
	);

	// The received_amount field
	$data['cowpro_repayment_schedule']['received_amount'] = array(
			'title' => 'received_amount',
			'help' => '已收款金额',
			'field' => array(
					'handler' => 'cowpro_fund_journal_handler_field_amount',
					'float' => TRUE,
			),
			'sort' => array(
					'handler' => 'views_handler_sort',
			),
			'filter' => array(
					'handler' => 'views_handler_filter_numeric',
			),
	);

	// The deadline field
	$data['cowpro_repayment_schedule']['deadline'] = array(
			'title' => '最后还款日',
			'help' => '最后还款时间',
			'field' => array(
					'handler' => 'views_handler_field_date',
			),
			'sort' => array(
					'handler' => 'views_handler_sort_date',
			),
			'filter' => array(
					'handler' => 'views_handler_filter_date',
			),
	);

	// 债权转让金额
	$data['cowpro_repayment_schedule']['data'] = array(
			'title' => 'creditor_assignment_amount',
			'help' => '债权转让金额',
			'field' => array(
					'handler' => 'cowpro_creditor_assignment_handler_field_amount',
					'float' => TRUE,
			),
			'sort' => array(
					'handler' => 'views_handler_sort',
			),
			'filter' => array(
					'handler' => 'views_handler_filter_numeric',
					//'handler' => 'cowpro_creditor_assignment_handler_filter_amount',
			),
	);

	$data['cowpro_repayment_schedule']['empty_text'] = array(
			'title' => t('Empty text'),
			'help' => t('Displays an appropriate empty text message for cowpro repayment schedule lists.'),
			'area' => array(
					'handler' => 'cowpro_repayment_schedule_handler_area_empty_text',
			),
	);

	return $data;
}

/**
 * Implements hook_views_data_alter().
 *
 * @param $data
 *   Information about Views' tables and fields.
 */
/*
function cowpro_issuing_views_data_alter(&$data) {
	// Add the Title form field to
	$data['cowpro_repayment_schedule']['operation'] = array(
			'field' => array(
					'title' => '操作',
					'help' => '操作',
					'handler' => 'cowpro_repayment_schedule_handler_operation',
			),
	);
}
*/