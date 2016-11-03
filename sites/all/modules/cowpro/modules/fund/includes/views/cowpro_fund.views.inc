<?php
/**
 * Implements hook_views_data().
 */
function cowpro_fund_views_data()
{

    $data = array();

    $data['cowpro_fund_journal']['table']['group'] = '资金明细';

    $data['cowpro_fund_journal']['table']['base'] = array(
        'title' => '资金明细',
        'help' => '包括充值、提现、投标…… 等等各种资金明细',
    );

    $data['cowpro_fund_journal']['table']['join'] = array(
    		'node' => array(
    				'left_field' => 'issuing_id',
    				'field' => 'nid',
    		),
    );

    // The journal_id field
    $data['cowpro_fund_journal']['journal_id'] = array(
    		'title' => 'journal_id',
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

    // The issuing_id field
    $data['cowpro_fund_journal']['issuing_id'] = array(
    		'title' => 'issuing_id',
    		'help' => '贷款申请表编号',
    		'field' => array(
    				'handler' => 'views_handler_field_numeric',
    		),
    		'sort' => array(
    				'handler' => 'views_handler_sort',
    		),
    		'filter' => array(
    				'handler' => 'views_handler_filter_numeric',
    		),
		    'relationship' => array(
		    		'handler' => 'views_handler_relationship',
		    		'base' => 'node',
		    		'base field' => 'nid',
		    		'field' => 'issuing_id',
		    		'label' => '贷款申请表',
		    ),
    );

    // Expose the internal_reference_id.
    $data['cowpro_fund_journal']['internal_reference_id'] = array(
    		'title' => '内部参考凭证',
    		'help' => '与该资金明细账相关的内部凭证，例如：贷款申请表、还款计划表.',
    		'field' => array(
    				'handler' => 'cowpro_fund_journal_handler_field_issuing_title',
    		),
    		'filter' => array(
    				'handler' => 'views_handler_filter_string',
    		),
    		'sort' => array(
    				'handler' => 'views_handler_sort',
    		),
    		/*
    		'relationship' => array(
    				'handler' => 'views_handler_relationship',
    				'base' => 'node',
    				'field' => 'nid',
    				'label' => '贷款申请表',
    		),
    		*/
    );

    // The uid field
    $data['cowpro_fund_journal']['uid'] = array(
    		'title' => '用户',
    		'help' => '与该资金明细账相关的用户',
    		'field' => array(
    				'handler' => 'views_handler_field_user',
    				'click sortable' => TRUE,
    		),
    		'argument' => array(
    				'handler' => 'views_handler_argument_user_uid',
    				'name field' => 'name', // display this field in the summary
    		),
    		'filter' => array(
    				'title' => t('Name'),
    				'handler' => 'views_handler_filter_user_name',
    		),
    		'sort' => array(
    				'handler' => 'views_handler_sort',
    		),
    		'relationship' => array(
    				'title' => '用户',
    				'help' => '将资金明细与用户相关联',
    				'handler' => 'views_handler_relationship',
    				'base' => 'users',
    				'base field' => 'uid',
    				'field' => 'uid',
    				'label' => '用户',
    		),
    );

    // The type field
    $data['cowpro_fund_journal']['type'] = array(
    		'title' => '业务类型',
    		'help' => '业务类型.',
    		'field' => array(
    				'handler' => 'cowpro_fund_journal_handler_field_type',
    		),
    		'sort' => array(
    				'handler' => 'views_handler_sort',
    		),
    		'filter' => array(
    				'handler' => 'cowpro_fund_journal_handler_filter_type',
    		),
    );

    // The amount field
    $data['cowpro_fund_journal']['amount'] = array(
    		'title' => 'amount',
    		'help' => '金额',
    		'field' => array(
    				'handler' => 'cowpro_fund_journal_handler_field_amount',
    		),
    		'sort' => array(
    				'handler' => 'views_handler_sort',
    		),
    		'filter' => array(
    				'handler' => 'views_handler_filter_numeric',
    		),
    );

    // The created field
    $data['cowpro_fund_journal']['created'] = array(
    		'title' => '时间',
    		'help' => '业务发生的时间',
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

    // The status field
    //在数据库里，status字段 1:表示交易成功; 0:表示交易失败; 针对type=BID这钟类型，还有status=2这种情况，表示"投标"以后"流标返款"成功的用例
    $data['cowpro_fund_journal']['status'] = array(
    		'title' => '结果',
    		'help' => '业务执行的结果',
    		'field' => array(
    				'handler' => 'cowpro_fund_journal_handler_field_status',
    		),
    		'sort' => array(
    				'handler' => 'views_handler_sort',
    		),
    		'filter' => array(
    				'handler' => 'cowpro_fund_journal_handler_filter_status',
    		),
    );

    $data['cowpro_fund_journal']['empty_text'] = array(
    		'title' => t('Empty text'),
    		'help' => t('Displays an appropriate empty text message for cowpro fund lists.'),
    		'area' => array(
    				'handler' => 'cowpro_fund_journal_handler_area_empty_text',
    		),
    );

    return $data;
}