<?php

/**
 * Views for the fund journal.
 */

/**
 * Implements hook_views_default_views().
 */
function cowpro_fund_views_default_views() {
	$view = new view ();
	$view->name = 'cowpro_fund_journal';
	$view->description = '资金流水账.';
	$view->tag = 'cowpro';
	$view->base_table = 'cowpro_fund_journal';
	$view->human_name = '资金流水账';
	$view->core = 7;
	$view->api_version = '3.0';
	$view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

	/* Display: Defaults */
	$handler = $view->new_display ( 'default', 'Defaults', 'default' );
	$handler->display->display_options ['title'] = '资金流水账';
	$handler->display->display_options ['use_more_always'] = FALSE;
	$handler->display->display_options ['use_more_text'] = '更多';
	$handler->display->display_options ['access'] ['type'] = 'role';
	$handler->display->display_options ['access'] ['role'] = array (
			6 => '6',
			5 => '5',
			4 => '4'
	);
	$handler->display->display_options ['cache'] ['type'] = 'none';
	$handler->display->display_options ['query'] ['type'] = 'views_query';
	$handler->display->display_options ['query'] ['options'] ['query_comment'] = FALSE;
	$handler->display->display_options ['exposed_form'] ['type'] = 'basic';
	$handler->display->display_options ['exposed_form'] ['options'] ['submit_button'] = '应用';
	$handler->display->display_options ['exposed_form'] ['options'] ['reset_button'] = TRUE;
	$handler->display->display_options ['exposed_form'] ['options'] ['reset_button_label'] = '重置';
	$handler->display->display_options ['exposed_form'] ['options'] ['exposed_sorts_label'] = '排序依据';
	$handler->display->display_options ['exposed_form'] ['options'] ['sort_asc_label'] = '升序';
	$handler->display->display_options ['exposed_form'] ['options'] ['sort_desc_label'] = '降序';
	$handler->display->display_options ['pager'] ['type'] = 'full';
	$handler->display->display_options ['pager'] ['options'] ['items_per_page'] = '50';
	$handler->display->display_options ['pager'] ['options'] ['offset'] = '0';
	$handler->display->display_options ['pager'] ['options'] ['id'] = '0';
	$handler->display->display_options ['pager'] ['options'] ['expose'] ['items_per_page_label'] = '每页条目数';
	$handler->display->display_options ['pager'] ['options'] ['expose'] ['items_per_page_options_all_label'] = '- 全部 -';
	$handler->display->display_options ['pager'] ['options'] ['expose'] ['offset_label'] = '偏移量';
	$handler->display->display_options ['pager'] ['options'] ['tags'] ['first'] = '« 第一页';
	$handler->display->display_options ['pager'] ['options'] ['tags'] ['previous'] = '‹ 前一页';
	$handler->display->display_options ['pager'] ['options'] ['tags'] ['next'] = '下一页 ›';
	$handler->display->display_options ['pager'] ['options'] ['tags'] ['last'] = '末页 »';
	$handler->display->display_options ['style_plugin'] = 'table';
	$handler->display->display_options ['style_options'] ['columns'] = array (
			'journal_id' => 'journal_id',
			'internal_reference_id' => 'internal_reference_id',
			'uid' => 'uid',
			'type' => 'type',
			'amount' => 'amount',
			'created' => 'created'
	);
	$handler->display->display_options ['style_options'] ['default'] = 'journal_id';
	$handler->display->display_options ['style_options'] ['info'] = array (
			'journal_id' => array (
					'sortable' => 1,
					'default_sort_order' => 'asc',
					'align' => '',
					'separator' => '',
					'empty_column' => 0
			),
			'internal_reference_id' => array (
					'sortable' => 0,
					'default_sort_order' => 'asc',
					'align' => '',
					'separator' => '',
					'empty_column' => 0
			),
			'uid' => array (
					'sortable' => 1,
					'default_sort_order' => 'asc',
					'align' => '',
					'separator' => '',
					'empty_column' => 0
			),
			'type' => array (
					'sortable' => 1,
					'default_sort_order' => 'asc',
					'align' => '',
					'separator' => '',
					'empty_column' => 0
			),
			'amount' => array (
					'sortable' => 1,
					'default_sort_order' => 'desc',
					'align' => '',
					'separator' => '',
					'empty_column' => 0
			),
			'created' => array (
					'sortable' => 1,
					'default_sort_order' => 'desc',
					'align' => '',
					'separator' => '',
					'empty_column' => 0
			)
	);
	$handler->display->display_options ['style_options'] ['empty_table'] = TRUE;
	/* 无任何结果时的行为: 资金明细: Empty text */
	$handler->display->display_options ['empty'] ['empty_text'] ['id'] = 'empty_text';
	$handler->display->display_options ['empty'] ['empty_text'] ['table'] = 'cowpro_fund_journal';
	$handler->display->display_options ['empty'] ['empty_text'] ['field'] = 'empty_text';
	/* 字段: 资金明细: journal_id */
	$handler->display->display_options ['fields'] ['journal_id'] ['id'] = 'journal_id';
	$handler->display->display_options ['fields'] ['journal_id'] ['table'] = 'cowpro_fund_journal';
	$handler->display->display_options ['fields'] ['journal_id'] ['field'] = 'journal_id';
	$handler->display->display_options ['fields'] ['journal_id'] ['label'] = '流水号';
	/* 字段: 资金明细: 业务类型 */
	$handler->display->display_options ['fields'] ['type'] ['id'] = 'type';
	$handler->display->display_options ['fields'] ['type'] ['table'] = 'cowpro_fund_journal';
	$handler->display->display_options ['fields'] ['type'] ['field'] = 'type';
	$handler->display->display_options ['fields'] ['type'] ['label'] = '交易类型';
	/* 字段: 资金明细: 贷款申请表 */
	$handler->display->display_options ['fields'] ['internal_reference_id'] ['id'] = 'internal_reference_id';
	$handler->display->display_options ['fields'] ['internal_reference_id'] ['table'] = 'cowpro_fund_journal';
	$handler->display->display_options ['fields'] ['internal_reference_id'] ['field'] = 'internal_reference_id';
	$handler->display->display_options ['fields'] ['internal_reference_id'] ['label'] = '内部参考凭证';
	/* 字段: 资金明细: amount */
	$handler->display->display_options ['fields'] ['amount'] ['id'] = 'amount';
	$handler->display->display_options ['fields'] ['amount'] ['table'] = 'cowpro_fund_journal';
	$handler->display->display_options ['fields'] ['amount'] ['field'] = 'amount';
	$handler->display->display_options ['fields'] ['amount'] ['label'] = '金额';
	/* 字段: 资金明细: 时间 */
	$handler->display->display_options ['fields'] ['created'] ['id'] = 'created';
	$handler->display->display_options ['fields'] ['created'] ['table'] = 'cowpro_fund_journal';
	$handler->display->display_options ['fields'] ['created'] ['field'] = 'created';
	/* 字段: 资金明细: 结果 */
	$handler->display->display_options ['fields'] ['status'] ['id'] = 'status';
	$handler->display->display_options ['fields'] ['status'] ['table'] = 'cowpro_fund_journal';
	$handler->display->display_options ['fields'] ['status'] ['field'] = 'status';
	/* 上下文过滤器: 资金明细: 用户 */
	$handler->display->display_options ['arguments'] ['uid'] ['id'] = 'uid';
	$handler->display->display_options ['arguments'] ['uid'] ['table'] = 'cowpro_fund_journal';
	$handler->display->display_options ['arguments'] ['uid'] ['field'] = 'uid';
	$handler->display->display_options ['arguments'] ['uid'] ['default_action'] = 'not found';
	$handler->display->display_options ['arguments'] ['uid'] ['exception'] ['title'] = '全部';
	$handler->display->display_options ['arguments'] ['uid'] ['default_argument_type'] = 'fixed';
	$handler->display->display_options ['arguments'] ['uid'] ['summary'] ['number_of_records'] = '0';
	$handler->display->display_options ['arguments'] ['uid'] ['summary'] ['format'] = 'default_summary';
	$handler->display->display_options ['arguments'] ['uid'] ['summary_options'] ['items_per_page'] = '25';
	$handler->display->display_options ['arguments'] ['uid'] ['specify_validation'] = TRUE;
	/* 过滤规则: 资金明细: 业务类型 */
	$handler->display->display_options ['filters'] ['type'] ['id'] = 'type';
	$handler->display->display_options ['filters'] ['type'] ['table'] = 'cowpro_fund_journal';
	$handler->display->display_options ['filters'] ['type'] ['field'] = 'type';
	$handler->display->display_options ['filters'] ['type'] ['exposed'] = TRUE;
	$handler->display->display_options ['filters'] ['type'] ['expose'] ['operator_id'] = 'type_op';
	$handler->display->display_options ['filters'] ['type'] ['expose'] ['label'] = '业务类型';
	$handler->display->display_options ['filters'] ['type'] ['expose'] ['operator'] = 'type_op';
	$handler->display->display_options ['filters'] ['type'] ['expose'] ['identifier'] = 'type';
	$handler->display->display_options ['filters'] ['type'] ['expose'] ['remember_roles'] = array (
			2 => '2',
			1 => 0,
			6 => 0,
			3 => 0,
			4 => 0,
			5 => 0
	);

	/* Display: 资金流水账 */
	$handler = $view->new_display ( 'page', '资金流水账', 'journal' );
	$handler->display->display_options ['defaults'] ['title'] = FALSE;
	$handler->display->display_options ['title'] = '资金流水账';
	$handler->display->display_options ['path'] = 'user/%/journal';
	$handler->display->display_options ['menu'] ['type'] = 'tab';
	$handler->display->display_options ['menu'] ['title'] = '资金流水账';
	$handler->display->display_options ['menu'] ['weight'] = '0';
	$handler->display->display_options ['menu'] ['context'] = 0;
	$handler->display->display_options ['menu'] ['context_only_inline'] = 0;
	$translatables ['cowpro_fund_journal'] = array (
			t ( 'Defaults' ),
			t ( '资金流水账' ),
			t ( '更多' ),
			t ( '应用' ),
			t ( '重置' ),
			t ( '排序依据' ),
			t ( '升序' ),
			t ( '降序' ),
			t ( '每页条目数' ),
			t ( '- 全部 -' ),
			t ( '偏移量' ),
			t ( '« 第一页' ),
			t ( '‹ 前一页' ),
			t ( '下一页 ›' ),
			t ( '末页 »' ),
			t ( '流水号' ),
			t ( '.' ),
			t ( ',' ),
			t ( '交易类型' ),
			t ( '贷款申请表流水号' ),
			t ( '金额' ),
			t ( '时间' ),
			t ( '结果' ),
			t ( '全部' ),
			t ( '业务类型' )
	);

	$views = array ();
	$views [$view->name] = $view;

	return $views;
}
