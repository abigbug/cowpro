<?php
/**
 * Implements hook_views_data().
 */
function cowpro_shop_views_data()
{

	$data = array();

	$data['cowpro_shop_deliver']['table']['group'] = '商品兑换记录';
	$data['cowpro_shop_deliver']['table']['entity type'] = 'cowpro_shop_deliver';
	$data['cowpro_shop_deliver']['table']['base'] = array(
			'field' => 'deliver_id',
			'title' => '商品兑换记录',
			'help' => '用来标记用户提交的兑换否已被处理',
	);

	$data['cowpro_shop_deliver']['table']['join'] = array(
			// Index this array by the table name to which this table refers.
			// 'left_field' is the primary key in the referenced table.
			// 'field' is the foreign key in this table.
			'userpoints_txn' => array(
					'left_field' => 'txn_id',
					'field' => 'txn_id',
			),
	);

	// The deliver_id field
	$data['cowpro_shop_deliver']['deliver_id'] = array(
			'title' => 'deliver_id',
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

	$data['cowpro_shop_deliver']['txn_id'] = array(
			'title' => t('Transaction ID'),
			'help' => t('Userpoints Transaction ID'),
			'field' => array(
					'handler' => 'views_handler_field',
			),
			'filter' => array(
					'handler' => 'views_handler_filter_numeric',
			),
			'sort' => array(
					'handler' => 'views_handler_sort',
			),
			'relationship' => array(
					'base' => 'userpoints_txn', // The name of the table to join with.
					'base field' => 'txn_id', // The name of the field on the joined table.
					// 'field' => 'nid' -- see hook_views_data_alter(); not needed here.
					'handler' => 'views_handler_relationship',
					'label' => '商品兑换记录',
					'title' => 'userpoints_txn兑换记录',
					'help' => '商品兑换记录',
			),
	);

	// The status field
	$data['cowpro_shop_deliver']['status'] = array(
			'title' => 'status',
			'help' => '处理状态',
			'field' => array(
					'handler' => 'cowpro_shop_deliver_handler_field_status',
			),
			'sort' => array(
					'handler' => 'views_handler_sort',
			),
			'filter' => array(
					'handler' => 'cowpro_shop_deliver_handler_filter_status',
			),
	);

	// The created field
	$data['cowpro_shop_deliver']['created'] = array(
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

	return $data;
}

/**
 * Implements hook_views_data_alter().
 */
function cowpro_shop_views_data_alter(&$data) {

  $data['userpoints_txn']['table']['join']['cowpro_shop_deliver']= array(
          'left_table' => 'cowpro_shop_deliver',
          'left_field' => 'txn_id',
          'field' => 'txn_id',
  );
  $data['userpoints_txn']['txn_id']['relationship'][] = array(
  				'base' => 'cowpro_shop_deliver',
  				'field' => 'txn_id',
  				'label' => '商品兑换',
  				'handler' => 'views_handler_relationship',
  );

}
