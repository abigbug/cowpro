<?php
/**
 * Implements hook_views_data().
 */
function cowpro_large_amount_rewards_views_data()
{

    $data = array();
    $data['cowpro_rewards_issuing_large']['table']['group'] = '大额奖励明细';
    $data['cowpro_rewards_issuing_large']['table']['base'] = array(
    	'field' => 'uid',
        'title' => '大额奖励明细',
        'help' => '',
    );

    // The uid field
    $data['cowpro_rewards_issuing_large']['user_real_name'] = array(
    		'title' => '用户名称',
    		'help' => '大额奖励用户名称',
                'real field' => 'uid',
    		'field' => array(
    				'handler' => 'cowpro_rewards_issuing_large_handler_field_user_real_name',
    		),
                 'filter' => array(
				'handler' => 'cowpro_rewards_issuing_large_handler_filter_user_real_name',
		),
    );

    // The rewards_amount field
    $data['cowpro_rewards_issuing_large']['rewards_amount'] = array(
    		'title' => '奖金',
    		'help' => '大额奖励的奖金',
    		'field' => array(
    				'handler' => 'views_handler_field',
    		),
                 'filter' => array(
				'handler' => 'views_handler_filter_numeric',
		),
    );
    $data['cowpro_rewards_issuing_large']['status'] = array(
            'title' => '是否发送奖金',
            'real field' => 'status',
            'help' => '是否发送奖金',
            'field' => array(
                            'handler' => 'cowpro_rewards_issuing_large_handler_field_status',
            ),
            'filter' => array(
                            'handler' => 'views_handler_filter_numeric',
            ),
    );
    $data['cowpro_rewards_issuing_large']['rewards_date'] = array(
            'title' => '奖金月份',
            'help' => '奖金月份',
            'field' => array(
                            'handler' => 'views_handler_field',
            ),
            'filter' => array(
                            'handler' => 'views_handler_filter_string',
            ),
    );

    return $data;
}

/**
 * Implements hook_views_data_alter().
 */
function cowpro_large_amount_rewards_views_data_alter(&$data) {

  $data['node']['table']['join']['cowpro_rewards_issuing_large']= array(
          'left_table' => 'cowpro_rewards_issuing_large',
          'left_field' => 'issuing_id',
          'field' => 'nid',
  );

}
