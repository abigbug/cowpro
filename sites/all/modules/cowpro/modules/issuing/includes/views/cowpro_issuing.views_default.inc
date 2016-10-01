<?php

/**
 * Views for the default issuing UI.
 */

/**
 * Implements hook_views_default_views().
 */
function cowpro_issuing_views_default_views() {
	$views = array ();

	$view = new view ();
	$view->name = 'all_issuing';
	$view->description = '';
	$view->tag = 'default';
	$view->base_table = 'node';
	$view->human_name = '贷款管理';
	$view->core = 7;
	$view->api_version = '3.0';
	$view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

	/* Display: Master */
	$handler = $view->new_display ( 'default', 'Master', 'default' );
	$handler->display->display_options ['title'] = '我的投资';
	$handler->display->display_options ['use_more_always'] = FALSE;
	$handler->display->display_options ['access'] ['type'] = 'role';
	$handler->display->display_options ['access'] ['role'] = array (
			4 => '4'
	);
	$handler->display->display_options ['cache'] ['type'] = 'none';
	$handler->display->display_options ['query'] ['type'] = 'views_query';
	$handler->display->display_options ['exposed_form'] ['type'] = 'basic';
	$handler->display->display_options ['exposed_form'] ['options'] ['reset_button_label'] = '重置';
	$handler->display->display_options ['pager'] ['type'] = 'full';
	$handler->display->display_options ['pager'] ['options'] ['items_per_page'] = '10';
	$handler->display->display_options ['pager'] ['options'] ['tags'] ['first'] = '? 第一页';
	$handler->display->display_options ['pager'] ['options'] ['tags'] ['previous'] = '? 前一页';
	$handler->display->display_options ['pager'] ['options'] ['tags'] ['next'] = '下一页 ?';
	$handler->display->display_options ['pager'] ['options'] ['tags'] ['last'] = '末页 ?';
	$handler->display->display_options ['style_plugin'] = 'table_megarows';
	$handler->display->display_options ['style_options'] ['columns'] = array (
			'title' => 'title',
			'field_applicant' => 'field_applicant',
			'view_issuing' => 'view_issuing'
	);
	$handler->display->display_options ['style_options'] ['default'] = '-1';
	$handler->display->display_options ['style_options'] ['info'] = array (
			'title' => array (
					'sortable' => 0,
					'default_sort_order' => 'asc',
					'align' => '',
					'separator' => '',
					'empty_column' => 0
			),
			'field_applicant' => array (
					'sortable' => 0,
					'default_sort_order' => 'asc',
					'align' => '',
					'separator' => '',
					'empty_column' => 0
			),
			'view_issuing' => array (
					'align' => '',
					'separator' => '',
					'empty_column' => 0
			)
	);
	$handler->display->display_options ['style_options'] ['scroll_padding'] = '120';
	$handler->display->display_options ['row_plugin'] = 'fields';
	/* 字段: 内容: 标题 */
	$handler->display->display_options ['fields'] ['title'] ['id'] = 'title';
	$handler->display->display_options ['fields'] ['title'] ['table'] = 'node';
	$handler->display->display_options ['fields'] ['title'] ['field'] = 'title';
	$handler->display->display_options ['fields'] ['title'] ['label'] = '';
	$handler->display->display_options ['fields'] ['title'] ['alter'] ['word_boundary'] = FALSE;
	$handler->display->display_options ['fields'] ['title'] ['alter'] ['ellipsis'] = FALSE;
	/* 字段: 内容: 申请人 */
	$handler->display->display_options ['fields'] ['field_applicant'] ['id'] = 'field_applicant';
	$handler->display->display_options ['fields'] ['field_applicant'] ['table'] = 'field_data_field_applicant';
	$handler->display->display_options ['fields'] ['field_applicant'] ['field'] = 'field_applicant';
	$handler->display->display_options ['fields'] ['field_applicant'] ['settings'] = array (
			'user_reference_view_mode' => 'full'
	);
	/* 字段: Issuing: 操作 */
	$handler->display->display_options ['fields'] ['view_issuing'] ['id'] = 'view_issuing';
	$handler->display->display_options ['fields'] ['view_issuing'] ['table'] = 'field_data_field_issuing';
	$handler->display->display_options ['fields'] ['view_issuing'] ['field'] = 'view_issuing';
	$handler->display->display_options ['fields'] ['view_issuing'] ['add_destination'] = 1;
	/* Sort criterion: 内容: Post date */
	$handler->display->display_options ['sorts'] ['created'] ['id'] = 'created';
	$handler->display->display_options ['sorts'] ['created'] ['table'] = 'node';
	$handler->display->display_options ['sorts'] ['created'] ['field'] = 'created';
	$handler->display->display_options ['sorts'] ['created'] ['order'] = 'DESC';
	/* Filter criterion: 内容: 类型 */
	$handler->display->display_options ['filters'] ['type'] ['id'] = 'type';
	$handler->display->display_options ['filters'] ['type'] ['table'] = 'node';
	$handler->display->display_options ['filters'] ['type'] ['field'] = 'type';
	$handler->display->display_options ['filters'] ['type'] ['value'] = array (
			'cowpro_issuing' => 'cowpro_issuing'
	);
	/* Filter criterion: 内容: 贷款表 (field_issuing:status) */
	$handler->display->display_options ['filters'] ['field_issuing_status'] ['id'] = 'field_issuing_status';
	$handler->display->display_options ['filters'] ['field_issuing_status'] ['table'] = 'field_data_field_issuing';
	$handler->display->display_options ['filters'] ['field_issuing_status'] ['field'] = 'field_issuing_status';
	$handler->display->display_options ['filters'] ['field_issuing_status'] ['operator'] = 'not in';
	$handler->display->display_options ['filters'] ['field_issuing_status'] ['value'] = array (
			'UNAUDITED' => 'UNAUDITED'
	);

	/* Display: 贷款管理 */
	$handler = $view->new_display ( 'page', '贷款管理', 'page' );
	$handler->display->display_options ['defaults'] ['access'] = FALSE;
	$handler->display->display_options ['access'] ['type'] = 'role';
	$handler->display->display_options ['access'] ['role'] = array (
			4 => '4'
	);
	$handler->display->display_options ['path'] = 'issuing-manage';
	$handler->display->display_options ['menu'] ['type'] = 'normal';
	$handler->display->display_options ['menu'] ['title'] = '贷款管理';
	$handler->display->display_options ['menu'] ['weight'] = '0';
	$handler->display->display_options ['menu'] ['context'] = 0;
	$handler->display->display_options ['menu'] ['context_only_inline'] = 0;

	/* Display: 待审核的贷款 */
	$handler = $view->new_display ( 'page', '待审核的贷款', 'page_1' );
	$handler->display->display_options ['defaults'] ['title'] = FALSE;
	$handler->display->display_options ['title'] = '待审核';
	$handler->display->display_options ['defaults'] ['filter_groups'] = FALSE;
	$handler->display->display_options ['defaults'] ['filters'] = FALSE;
	/* Filter criterion: 内容: 类型 */
	$handler->display->display_options ['filters'] ['type'] ['id'] = 'type';
	$handler->display->display_options ['filters'] ['type'] ['table'] = 'node';
	$handler->display->display_options ['filters'] ['type'] ['field'] = 'type';
	$handler->display->display_options ['filters'] ['type'] ['value'] = array (
			'cowpro_issuing' => 'cowpro_issuing'
	);
	/* Filter criterion: 内容: 贷款表 (field_issuing:status) */
	$handler->display->display_options ['filters'] ['field_issuing_status'] ['id'] = 'field_issuing_status';
	$handler->display->display_options ['filters'] ['field_issuing_status'] ['table'] = 'field_data_field_issuing';
	$handler->display->display_options ['filters'] ['field_issuing_status'] ['field'] = 'field_issuing_status';
	$handler->display->display_options ['filters'] ['field_issuing_status'] ['value'] = array (
			'UNAUDITED' => 'UNAUDITED'
	);
	$handler->display->display_options ['path'] = 'issuing-manage/unaudited';
	$handler->display->display_options ['menu'] ['type'] = 'normal';
	$handler->display->display_options ['menu'] ['title'] = '待审核';
	$handler->display->display_options ['menu'] ['weight'] = '0';
	$handler->display->display_options ['menu'] ['context'] = 0;
	$handler->display->display_options ['menu'] ['context_only_inline'] = 0;

	/* Display: 全部贷款 */
	$handler = $view->new_display ( 'page', '全部贷款', 'page_2' );
	$handler->display->display_options ['defaults'] ['access'] = FALSE;
	$handler->display->display_options ['access'] ['type'] = 'role';
	$handler->display->display_options ['access'] ['role'] = array (
			6 => '6',
			5 => '5'
	);
	$handler->display->display_options ['path'] = 'issuing-list';
	$handler->display->display_options ['menu'] ['type'] = 'normal';
	$handler->display->display_options ['menu'] ['title'] = '全部贷款';
	$handler->display->display_options ['menu'] ['weight'] = '0';
	$handler->display->display_options ['menu'] ['context'] = 0;
	$handler->display->display_options ['menu'] ['context_only_inline'] = 0;

	/* Display: 我的贷款 */
	$handler = $view->new_display ( 'page', '我的贷款', 'page_3' );
	$handler->display->display_options ['defaults'] ['access'] = FALSE;
	$handler->display->display_options ['access'] ['type'] = 'role';
	$handler->display->display_options ['access'] ['role'] = array (
			6 => '6'
	);
	$handler->display->display_options ['defaults'] ['arguments'] = FALSE;
	/* Contextual filter: 内容: 申请人 (field_applicant) */
	$handler->display->display_options ['arguments'] ['field_applicant_uid'] ['id'] = 'field_applicant_uid';
	$handler->display->display_options ['arguments'] ['field_applicant_uid'] ['table'] = 'field_data_field_applicant';
	$handler->display->display_options ['arguments'] ['field_applicant_uid'] ['field'] = 'field_applicant_uid';
	$handler->display->display_options ['arguments'] ['field_applicant_uid'] ['default_action'] = 'default';
	$handler->display->display_options ['arguments'] ['field_applicant_uid'] ['exception'] ['title'] = '全部';
	$handler->display->display_options ['arguments'] ['field_applicant_uid'] ['default_argument_type'] = 'current_user';
	$handler->display->display_options ['arguments'] ['field_applicant_uid'] ['summary'] ['number_of_records'] = '0';
	$handler->display->display_options ['arguments'] ['field_applicant_uid'] ['summary'] ['format'] = 'default_summary';
	$handler->display->display_options ['arguments'] ['field_applicant_uid'] ['summary_options'] ['items_per_page'] = '25';
	$handler->display->display_options ['defaults'] ['filter_groups'] = FALSE;
	$handler->display->display_options ['defaults'] ['filters'] = FALSE;
	/* Filter criterion: 内容: 类型 */
	$handler->display->display_options ['filters'] ['type'] ['id'] = 'type';
	$handler->display->display_options ['filters'] ['type'] ['table'] = 'node';
	$handler->display->display_options ['filters'] ['type'] ['field'] = 'type';
	$handler->display->display_options ['filters'] ['type'] ['value'] = array (
			'cowpro_issuing' => 'cowpro_issuing'
	);
	$handler->display->display_options ['path'] = 'issuing-list/debtor';
	$handler->display->display_options ['menu'] ['type'] = 'normal';
	$handler->display->display_options ['menu'] ['title'] = '我的贷款';
	$handler->display->display_options ['menu'] ['weight'] = '0';
	$handler->display->display_options ['menu'] ['context'] = 0;
	$handler->display->display_options ['menu'] ['context_only_inline'] = 0;

	/* Display: 我的投资 */
	$handler = $view->new_display ( 'page', '我的投资', 'page_4' );
	$handler->display->display_options ['defaults'] ['access'] = FALSE;
	$handler->display->display_options ['access'] ['type'] = 'role';
	$handler->display->display_options ['access'] ['role'] = array (
			5 => '5'
	);
	$handler->display->display_options ['defaults'] ['arguments'] = FALSE;
	/* Contextual filter: 内容: 申请人 (field_applicant) */
	$handler->display->display_options ['arguments'] ['field_applicant_uid'] ['id'] = 'field_applicant_uid';
	$handler->display->display_options ['arguments'] ['field_applicant_uid'] ['table'] = 'field_data_field_applicant';
	$handler->display->display_options ['arguments'] ['field_applicant_uid'] ['field'] = 'field_applicant_uid';
	$handler->display->display_options ['arguments'] ['field_applicant_uid'] ['default_action'] = 'default';
	$handler->display->display_options ['arguments'] ['field_applicant_uid'] ['exception'] ['title'] = '全部';
	$handler->display->display_options ['arguments'] ['field_applicant_uid'] ['default_argument_type'] = 'current_user';
	$handler->display->display_options ['arguments'] ['field_applicant_uid'] ['summary'] ['number_of_records'] = '0';
	$handler->display->display_options ['arguments'] ['field_applicant_uid'] ['summary'] ['format'] = 'default_summary';
	$handler->display->display_options ['arguments'] ['field_applicant_uid'] ['summary_options'] ['items_per_page'] = '25';
	$handler->display->display_options ['path'] = 'issuing-list/lender';
	$handler->display->display_options ['menu'] ['type'] = 'normal';
	$handler->display->display_options ['menu'] ['title'] = '我的投资';
	$handler->display->display_options ['menu'] ['weight'] = '0';
	$handler->display->display_options ['menu'] ['context'] = 0;
	$handler->display->display_options ['menu'] ['context_only_inline'] = 0;

	$views [$view->name] = $view;

	$view = new view ();
	$view->name = 'repayment_schedule';
	$view->description = '';
	$view->tag = 'default';
	$view->base_table = 'node';
	$view->human_name = '还款详情';
	$view->core = 7;
	$view->api_version = '3.0';
	$view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

	/* Display: Master */
	$handler = $view->new_display ( 'default', 'Master', 'default' );
	$handler->display->display_options ['use_more_always'] = FALSE;
	$handler->display->display_options ['access'] ['type'] = 'perm';
	$handler->display->display_options ['cache'] ['type'] = 'none';
	$handler->display->display_options ['query'] ['type'] = 'views_query';
	$handler->display->display_options ['exposed_form'] ['type'] = 'basic';
	$handler->display->display_options ['exposed_form'] ['options'] ['reset_button_label'] = '重置';
	$handler->display->display_options ['pager'] ['type'] = 'full';
	$handler->display->display_options ['pager'] ['options'] ['tags'] ['first'] = '« 第一页';
	$handler->display->display_options ['pager'] ['options'] ['tags'] ['previous'] = '‹ 前一页';
	$handler->display->display_options ['pager'] ['options'] ['tags'] ['next'] = '下一页 ›';
	$handler->display->display_options ['pager'] ['options'] ['tags'] ['last'] = '末页 »';
	$handler->display->display_options ['style_plugin'] = 'table';
	$handler->display->display_options ['style_options'] ['columns'] = array (
			'title' => 'title'
	);
	$handler->display->display_options ['style_options'] ['default'] = '-1';
	$handler->display->display_options ['style_options'] ['info'] = array (
			'title' => array (
					'sortable' => 0,
					'default_sort_order' => 'asc',
					'align' => '',
					'separator' => '',
					'empty_column' => 0
			)
	);
	/* Relationship: 还款详情: 付款方用户ID */
	$handler->display->display_options ['relationships'] ['payer_uid'] ['id'] = 'payer_uid';
	$handler->display->display_options ['relationships'] ['payer_uid'] ['table'] = 'cowpro_repayment_schedule';
	$handler->display->display_options ['relationships'] ['payer_uid'] ['field'] = 'payer_uid';
	$handler->display->display_options ['relationships'] ['payer_uid'] ['label'] = '付款用户';
	$handler->display->display_options ['relationships'] ['payer_uid'] ['required'] = TRUE;
	/* Relationship: 还款详情: 收款方用户ID */
	$handler->display->display_options ['relationships'] ['receiver_uid'] ['id'] = 'receiver_uid';
	$handler->display->display_options ['relationships'] ['receiver_uid'] ['table'] = 'cowpro_repayment_schedule';
	$handler->display->display_options ['relationships'] ['receiver_uid'] ['field'] = 'receiver_uid';
	$handler->display->display_options ['relationships'] ['receiver_uid'] ['label'] = '收款用户';
	$handler->display->display_options ['relationships'] ['receiver_uid'] ['required'] = TRUE;
	/* 字段: 用户: 名称 */
	$handler->display->display_options ['fields'] ['name'] ['id'] = 'name';
	$handler->display->display_options ['fields'] ['name'] ['table'] = 'users';
	$handler->display->display_options ['fields'] ['name'] ['field'] = 'name';
	$handler->display->display_options ['fields'] ['name'] ['relationship'] = 'payer_uid';
	$handler->display->display_options ['fields'] ['name'] ['label'] = '付款用户';
	/* 字段: 用户: 名称 */
	$handler->display->display_options ['fields'] ['name_1'] ['id'] = 'name_1';
	$handler->display->display_options ['fields'] ['name_1'] ['table'] = 'users';
	$handler->display->display_options ['fields'] ['name_1'] ['field'] = 'name';
	$handler->display->display_options ['fields'] ['name_1'] ['relationship'] = 'receiver_uid';
	$handler->display->display_options ['fields'] ['name_1'] ['label'] = '收款用户';
	/* 字段: 期次: period */
	$handler->display->display_options ['fields'] ['period'] ['id'] = 'period';
	$handler->display->display_options ['fields'] ['period'] ['table'] = 'cowpro_repayment_schedule';
	$handler->display->display_options ['fields'] ['period'] ['field'] = 'period';
	/* 字段: 还款详情: payable_amount */
	$handler->display->display_options ['fields'] ['payable_amount'] ['id'] = 'payable_amount';
	$handler->display->display_options ['fields'] ['payable_amount'] ['table'] = 'cowpro_repayment_schedule';
	$handler->display->display_options ['fields'] ['payable_amount'] ['field'] = 'payable_amount';
	/* 字段: 还款详情: paid_amount */
	$handler->display->display_options ['fields'] ['paid_amount_1'] ['id'] = 'paid_amount_1';
	$handler->display->display_options ['fields'] ['paid_amount_1'] ['table'] = 'cowpro_repayment_schedule';
	$handler->display->display_options ['fields'] ['paid_amount_1'] ['field'] = 'paid_amount';
	/* 字段: 还款详情: receivable_amount */
	$handler->display->display_options ['fields'] ['receivable_amount'] ['id'] = 'receivable_amount';
	$handler->display->display_options ['fields'] ['receivable_amount'] ['table'] = 'cowpro_repayment_schedule';
	$handler->display->display_options ['fields'] ['receivable_amount'] ['field'] = 'receivable_amount';
	/* 字段: 还款详情: received_amount */
	$handler->display->display_options ['fields'] ['received_amount'] ['id'] = 'received_amount';
	$handler->display->display_options ['fields'] ['received_amount'] ['table'] = 'cowpro_repayment_schedule';
	$handler->display->display_options ['fields'] ['received_amount'] ['field'] = 'received_amount';
	/* 字段: 还款详情: 最后还款日 */
	$handler->display->display_options ['fields'] ['deadline'] ['id'] = 'deadline';
	$handler->display->display_options ['fields'] ['deadline'] ['table'] = 'cowpro_repayment_schedule';
	$handler->display->display_options ['fields'] ['deadline'] ['field'] = 'deadline';
	$handler->display->display_options ['fields'] ['deadline'] ['date_format'] = 'short';
	$handler->display->display_options ['fields'] ['deadline'] ['second_date_format'] = 'short';
	/* 字段: 还款详情: 状态 */
	$handler->display->display_options ['fields'] ['status'] ['id'] = 'status';
	$handler->display->display_options ['fields'] ['status'] ['table'] = 'cowpro_repayment_schedule';
	$handler->display->display_options ['fields'] ['status'] ['field'] = 'status';
	/* Contextual filter: 内容: Nid */
	$handler->display->display_options ['arguments'] ['nid'] ['id'] = 'nid';
	$handler->display->display_options ['arguments'] ['nid'] ['table'] = 'node';
	$handler->display->display_options ['arguments'] ['nid'] ['field'] = 'nid';
	$handler->display->display_options ['arguments'] ['nid'] ['exception'] ['title'] = '全部';
	$handler->display->display_options ['arguments'] ['nid'] ['default_argument_type'] = 'fixed';
	$handler->display->display_options ['arguments'] ['nid'] ['summary'] ['number_of_records'] = '0';
	$handler->display->display_options ['arguments'] ['nid'] ['summary'] ['format'] = 'default_summary';
	$handler->display->display_options ['arguments'] ['nid'] ['summary_options'] ['items_per_page'] = '25';

	$views [$view->name] = $view;

$view = new view();
$view->name = 'creditor_assignment';
$view->description = '';
$view->tag = 'cowpro';
$view->base_table = 'node';
$view->human_name = '债权转让';
$view->core = 7;
$view->api_version = '3.0';
$view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

/* Display: Defaults */
$handler = $view->new_display('default', 'Defaults', 'default');
$handler->display->display_options['title'] = '债权转让';
$handler->display->display_options['use_more_always'] = FALSE;
$handler->display->display_options['use_more_text'] = '更多';
$handler->display->display_options['group_by'] = TRUE;
$handler->display->display_options['access']['type'] = 'perm';
$handler->display->display_options['cache']['type'] = 'none';
$handler->display->display_options['query']['type'] = 'views_query';
$handler->display->display_options['query']['options']['query_comment'] = FALSE;
$handler->display->display_options['exposed_form']['type'] = 'basic';
$handler->display->display_options['exposed_form']['options']['submit_button'] = '应用';
$handler->display->display_options['exposed_form']['options']['reset_button'] = TRUE;
$handler->display->display_options['exposed_form']['options']['reset_button_label'] = '重置';
$handler->display->display_options['exposed_form']['options']['exposed_sorts_label'] = '排序依据';
$handler->display->display_options['exposed_form']['options']['sort_asc_label'] = '升序';
$handler->display->display_options['exposed_form']['options']['sort_desc_label'] = '降序';
$handler->display->display_options['pager']['type'] = 'full';
$handler->display->display_options['pager']['options']['items_per_page'] = '50';
$handler->display->display_options['pager']['options']['offset'] = '0';
$handler->display->display_options['pager']['options']['id'] = '0';
$handler->display->display_options['pager']['options']['expose']['items_per_page_label'] = '每页条目数';
$handler->display->display_options['pager']['options']['expose']['items_per_page_options_all_label'] = '- 全部 -';
$handler->display->display_options['pager']['options']['expose']['offset_label'] = '偏移量';
$handler->display->display_options['pager']['options']['tags']['first'] = '« 第一页';
$handler->display->display_options['pager']['options']['tags']['previous'] = '‹ 前一页';
$handler->display->display_options['pager']['options']['tags']['next'] = '下一页 ›';
$handler->display->display_options['pager']['options']['tags']['last'] = '末页 »';
$handler->display->display_options['style_plugin'] = 'table_megarows';
$handler->display->display_options['style_options']['columns'] = array(
  'title' => 'title',
  'name_1' => 'name_1',
  'receivable_amount' => 'receivable_amount',
  'deadline' => 'deadline',
  'period' => 'period',
  'nid' => 'nid',
  'data' => 'data',
  'view_creditor_assignment' => 'view_creditor_assignment',
);
$handler->display->display_options['style_options']['default'] = '-1';
$handler->display->display_options['style_options']['info'] = array(
  'title' => array(
    'sortable' => 0,
    'default_sort_order' => 'asc',
    'align' => '',
    'separator' => '',
    'empty_column' => 0,
  ),
  'name_1' => array(
    'sortable' => 0,
    'default_sort_order' => 'asc',
    'align' => '',
    'separator' => '',
    'empty_column' => 0,
  ),
  'receivable_amount' => array(
    'align' => '',
    'separator' => '',
    'empty_column' => 0,
  ),
  'deadline' => array(
    'align' => '',
    'separator' => '',
    'empty_column' => 0,
  ),
  'period' => array(
    'align' => '',
    'separator' => '',
    'empty_column' => 0,
  ),
  'nid' => array(
    'sortable' => 0,
    'default_sort_order' => 'asc',
    'align' => '',
    'separator' => '',
    'empty_column' => 0,
  ),
  'data' => array(
    'align' => '',
    'separator' => '',
    'empty_column' => 0,
  ),
  'view_creditor_assignment' => array(
    'align' => '',
    'separator' => '',
    'empty_column' => 0,
  ),
);
$handler->display->display_options['style_options']['scroll_padding'] = '120';
$handler->display->display_options['style_options']['loading_text'] = '正在加载...';
$handler->display->display_options['row_plugin'] = 'fields';
/* 关联: 还款详情: 收款方用户ID */
$handler->display->display_options['relationships']['receiver_uid']['id'] = 'receiver_uid';
$handler->display->display_options['relationships']['receiver_uid']['table'] = 'cowpro_repayment_schedule';
$handler->display->display_options['relationships']['receiver_uid']['field'] = 'receiver_uid';
$handler->display->display_options['relationships']['receiver_uid']['label'] = '收款用户';
$handler->display->display_options['relationships']['receiver_uid']['required'] = TRUE;
/* 字段: 内容: 标题 */
$handler->display->display_options['fields']['title']['id'] = 'title';
$handler->display->display_options['fields']['title']['table'] = 'node';
$handler->display->display_options['fields']['title']['field'] = 'title';
/* 字段: 用户: 名称 */
$handler->display->display_options['fields']['name_1']['id'] = 'name_1';
$handler->display->display_options['fields']['name_1']['table'] = 'users';
$handler->display->display_options['fields']['name_1']['field'] = 'name';
$handler->display->display_options['fields']['name_1']['relationship'] = 'receiver_uid';
$handler->display->display_options['fields']['name_1']['label'] = '收款用户';
$handler->display->display_options['fields']['name_1']['exclude'] = TRUE;
/* 字段: 还款详情: creditor_assignment_amount */
$handler->display->display_options['fields']['data']['id'] = 'data';
$handler->display->display_options['fields']['data']['table'] = 'cowpro_repayment_schedule';
$handler->display->display_options['fields']['data']['field'] = 'data';
$handler->display->display_options['fields']['data']['label'] = '债权转让金额';
/* 字段: SUM(还款详情: receivable_amount) */
$handler->display->display_options['fields']['receivable_amount']['id'] = 'receivable_amount';
$handler->display->display_options['fields']['receivable_amount']['table'] = 'cowpro_repayment_schedule';
$handler->display->display_options['fields']['receivable_amount']['field'] = 'receivable_amount';
$handler->display->display_options['fields']['receivable_amount']['group_type'] = 'sum';
$handler->display->display_options['fields']['receivable_amount']['label'] = '应收款';
$handler->display->display_options['fields']['receivable_amount']['set_precision'] = TRUE;
$handler->display->display_options['fields']['receivable_amount']['precision'] = '2';
/* 字段: COUNT(还款详情: period) */
$handler->display->display_options['fields']['period']['id'] = 'period';
$handler->display->display_options['fields']['period']['table'] = 'cowpro_repayment_schedule';
$handler->display->display_options['fields']['period']['field'] = 'period';
$handler->display->display_options['fields']['period']['group_type'] = 'count';
$handler->display->display_options['fields']['period']['label'] = '待还款期数';
$handler->display->display_options['fields']['period']['separator'] = '';
/* 字段: MIN(还款详情: 最后还款日) */
$handler->display->display_options['fields']['deadline']['id'] = 'deadline';
$handler->display->display_options['fields']['deadline']['table'] = 'cowpro_repayment_schedule';
$handler->display->display_options['fields']['deadline']['field'] = 'deadline';
$handler->display->display_options['fields']['deadline']['group_type'] = 'min';
$handler->display->display_options['fields']['deadline']['label'] = '最近还款日';
$handler->display->display_options['fields']['deadline']['date_format'] = 'long';
$handler->display->display_options['fields']['deadline']['second_date_format'] = 'long';
/* 字段: 内容: Nid */
$handler->display->display_options['fields']['nid']['id'] = 'nid';
$handler->display->display_options['fields']['nid']['table'] = 'node';
$handler->display->display_options['fields']['nid']['field'] = 'nid';
$handler->display->display_options['fields']['nid']['exclude'] = TRUE;
/* 字段: Issuing: 操作 */
$handler->display->display_options['fields']['view_creditor_assignment']['id'] = 'view_creditor_assignment';
$handler->display->display_options['fields']['view_creditor_assignment']['table'] = 'field_data_field_issuing';
$handler->display->display_options['fields']['view_creditor_assignment']['field'] = 'view_creditor_assignment';
/* Filter criterion: 还款详情: 状态 */
$handler->display->display_options['filters']['status_1']['id'] = 'status_1';
$handler->display->display_options['filters']['status_1']['table'] = 'cowpro_repayment_schedule';
$handler->display->display_options['filters']['status_1']['field'] = 'status';
$handler->display->display_options['filters']['status_1']['value'] = array(
  'ASSIGNABLE' => 'ASSIGNABLE',
);

/* Display: 债权转让 */
$handler = $view->new_display('page', '债权转让', 'creditor_assignment');
$handler->display->display_options['defaults']['title'] = FALSE;
$handler->display->display_options['title'] = '债权转让';
$handler->display->display_options['path'] = 'creditor-assignment';
$handler->display->display_options['menu']['type'] = 'normal';
$handler->display->display_options['menu']['title'] = '债权转让';
$handler->display->display_options['menu']['weight'] = '0';
$handler->display->display_options['menu']['context'] = 0;
$handler->display->display_options['menu']['context_only_inline'] = 0;
$translatables['creditor_assignment'] = array(
  t('Defaults'),
  t('债权转让'),
  t('更多'),
  t('应用'),
  t('重置'),
  t('排序依据'),
  t('升序'),
  t('降序'),
  t('每页条目数'),
  t('- 全部 -'),
  t('偏移量'),
  t('« 第一页'),
  t('‹ 前一页'),
  t('下一页 ›'),
  t('末页 »'),
  t('收款用户'),
  t('标题'),
  t('债权转让金额'),
  t('应收款'),
  t('.'),
  t(','),
  t('待还款期数'),
  t('最近还款日'),
  t('Nid'),
  t('操作'),
);

	$views [$view->name] = $view;

	return $views;
}
