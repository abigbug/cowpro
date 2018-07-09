<?php
/**
 * Implements hook_views_data().
 */
function cowpro_cash_coupon_views_data()
{
    $data['userpoints_txn']['the_rules'] = array(
            'title' => '代金券使用规则',
            'help' => '代金券满多少可用',
            'real field' => 'txn_id',
            'field' => array(      
              'handler' => 'userpoints_txn_handler_field_the_rules',
            ),     
            'filter' => array(
              'handler' => 'views_handler_filter_string',
            ),
    );
    return $data;
}
