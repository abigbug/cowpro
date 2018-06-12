<?php
/**
 * Implements hook_views_data().
 */
function jiupaipay_views_data()
{
    $data = array();
    $data['jiupaipay_files_data']['table']['group'] = '宜宾银行对账信息';
    $data['jiupaipay_files_data']['table']['base'] = array(
    	'field' => 'uid',
        'title' => '宜宾银行对账信息',
        'help' => '包括充值、提现、投标…… 等等各种资金明细',
    );
    $data['jiupaipay_files_data']['table']['join'] = array(      
        'users' => array(
          'left_field' => 'uid',
          'field' => 'uid',
        ),
    );

    // The business_no field
    $data['jiupaipay_files_data']['business_no'] = array(
    		'title' => '业务流水号',
    		'help' => '业务流水号',
    		'field' => array(
    				'handler' => 'views_handler_field',
    		),
    );

    // The file_name field
    $data['jiupaipay_files_data']['file_name'] = array(
    		'title' => '对账文件名称',
    		'help' => '对账文件名称',
    		'field' => array(
    				'handler' => 'views_handler_field',
    		),
    );

    // Expose the business_type.
    $data['jiupaipay_files_data']['business_type'] = array(
    		'title' => '业务类型',
    		'help' => '业务类型',
    		'field' => array(
    				'handler' => 'jiupaipay_files_data_handler_field_business_type',
    		),
    		'filter' => array(
    				'handler' => 'jiupaipay_files_data_handler_filter_business_type',
    		),
    );

    // The uid field
    $data['jiupaipay_files_data']['uid'] = array(
		'title' => '用户实名',
		'help' => '用户昵称与真实姓名',
		'real field' => 'uid',
		'field' => array(
		  'handler' => 'jiupaipay_files_data_handler_field_real_name',
		),
		'filter' => array(
		  'handler' => 'jiupaipay_files_data_handler_filter_user',
		),
    );
    // The turnover field
    $data['jiupaipay_files_data']['turnover'] = array(
    		'title' => '交易金额',
    		'help' => '交易金额',
    		'field' => array(
    				'handler' => 'jiupaipay_files_data_handler_field_turnover',
    		),
    		'filter' => array(
    				'handler' => 'views_handler_filter_numeric',
    		),
    );

    // The created field
    $data['jiupaipay_files_data']['file_date'] = array(
    		'title' => '时间',
    		'help' => '业务发生的时间',
    		'field' => array(      
                  'handler' => 'views_handler_field_date',
                  'click sortable' => TRUE,
    		),     
                'sort' => array(
                  'handler' => 'views_handler_sort_date',
                ),
    		'filter' => array(
    		  'handler' => 'views_handler_filter_date',
    		),
    );
    return $data;
}