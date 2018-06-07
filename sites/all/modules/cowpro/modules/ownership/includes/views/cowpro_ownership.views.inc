<?php
/**
 * Implements hook_views_data().
 */
function cowpro_ownership_views_data(){
	$data['users']['rtype'] = array(
			'title' => '关系类型',
			'help' => '关系类型',
			'real field' => 'uid',
			'field' => array(
					'handler' => 'cowpro_ownership_handler_field_rtype',
			),
	);
	$data['users']['manager_name'] = array(
			'title' => '客户经理',
			'help' => '客户经理名称',
			'real field' => 'uid',
			'field' => array(
					'handler' => 'cowpro_ownership_handler_field_manager_name',
			),
			'sort' => array(
					'handler' => 'views_handler_sort',
			),
			'filter' => array(
					'handler' => 'cowpro_ownership_handler_filter_manager_name',
			),
	);
        
	return $data;
}