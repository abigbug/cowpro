<?php

/**
 * Views for the default customer UI.
 */

/**
 * Implements hook_views_default_views().
 */
function cowpro_customer_ui_views_default_views() {
  $views = array();

  // Customer profile admin list at admin/cowpro/customer-profiles.
  $view = new view();
  $view->name = 'cowpro_customer_profiles';
  $view->description = 'A list of customer profiles of all types.';
  $view->tag = 'cowpro';
  $view->base_table = 'cowpro_customer_profile';
  $view->human_name = '用户资料';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Defaults */
  $handler = $view->new_display('default', 'Defaults', 'default');
  $handler->display->display_options['title'] = '用户资料';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'administer cowpro_customer_profile entities';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['query_comment'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['reset_button'] = TRUE;
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '50';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'profile_id' => 'profile_id',
    'cowpro_customer_profile' => 'cowpro_customer_profile',
    'name' => 'name',
    'type' => 'type',
    'verified' => 'verified',
    'edit_customer_profile' => 'edit_customer_profile',
    'delete_customer_profile' => 'delete_customer_profile',
  );
  $handler->display->display_options['style_options']['default'] = 'profile_id';
  $handler->display->display_options['style_options']['info'] = array(
    'profile_id' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'cowpro_customer_address' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'name' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'type' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'verified' => array(
      'sortable' => 1,
      'default_sort_order' => 'desc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'edit_customer_profile' => array(
      'align' => '',
      'separator' => '&nbsp;&nbsp;&nbsp;',
      'empty_column' => 0,
    ),
    'delete_customer_profile' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  $handler->display->display_options['style_options']['empty_table'] = TRUE;
  /* No results behavior: CowPro Customer Profile: Empty text */
  $handler->display->display_options['empty']['empty_text']['id'] = 'empty_text';
  $handler->display->display_options['empty']['empty_text']['table'] = 'cowpro_customer_profile';
  $handler->display->display_options['empty']['empty_text']['field'] = 'empty_text';
  $handler->display->display_options['empty']['empty_text']['add_path'] = 'admin/cowpro/customer-profiles/add';
  /* Relationship: CowPro Customer Profile: Owner */
  $handler->display->display_options['relationships']['uid']['id'] = 'uid';
  $handler->display->display_options['relationships']['uid']['table'] = 'cowpro_customer_profile';
  $handler->display->display_options['relationships']['uid']['field'] = 'uid';
  /* Field: CowPro Customer Profile: Profile ID */
  $handler->display->display_options['fields']['profile_id']['id'] = 'profile_id';
  $handler->display->display_options['fields']['profile_id']['table'] = 'cowpro_customer_profile';
  $handler->display->display_options['fields']['profile_id']['field'] = 'profile_id';
  $handler->display->display_options['fields']['profile_id']['link_to_profile'] = 1;
  /* Field: CowPro Customer profile: Address */
  $handler->display->display_options['fields']['cowpro_customer_address']['id'] = 'cowpro_customer_address';
  $handler->display->display_options['fields']['cowpro_customer_address']['table'] = 'field_data_cowpro_customer_address';
  $handler->display->display_options['fields']['cowpro_customer_address']['field'] = 'cowpro_customer_address';
  $handler->display->display_options['fields']['cowpro_customer_address']['label'] = 'Name';
  $handler->display->display_options['fields']['cowpro_customer_address']['click_sort_column'] = 'country';
  $handler->display->display_options['fields']['cowpro_customer_address']['settings'] = array(
    'use_widget_handlers' => 0,
    'format_handlers' => array(
      0 => 'name-oneline',
    ),
  );
  /* Field: User: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'users';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['relationship'] = 'uid';
  $handler->display->display_options['fields']['name']['label'] = 'User';
  /* Field: CowPro Customer Profile: Type */
  $handler->display->display_options['fields']['type']['id'] = 'type';
  $handler->display->display_options['fields']['type']['table'] = 'cowpro_customer_profile';
  $handler->display->display_options['fields']['type']['field'] = 'type';
  $handler->display->display_options['fields']['type']['link_to_profile'] = 0;
  /* Field: CowPro Customer Profile: verified */
  $handler->display->display_options['fields']['verified']['id'] = 'verified';
  $handler->display->display_options['fields']['verified']['table'] = 'cowpro_customer_profile';
  $handler->display->display_options['fields']['verified']['field'] = 'verified';
  $handler->display->display_options['fields']['verified']['type'] = '已认证-末认证';
  $handler->display->display_options['fields']['verified']['not'] = 0;
  /* Field: CowPro Customer Profile: Edit link */
  $handler->display->display_options['fields']['edit_customer_profile']['id'] = 'edit_customer_profile';
  $handler->display->display_options['fields']['edit_customer_profile']['table'] = 'cowpro_customer_profile';
  $handler->display->display_options['fields']['edit_customer_profile']['field'] = 'edit_customer_profile';
  $handler->display->display_options['fields']['edit_customer_profile']['label'] = 'Operations';
  /* Field: CowPro Customer Profile: Delete link */
  $handler->display->display_options['fields']['delete_customer_profile']['id'] = 'delete_customer_profile';
  $handler->display->display_options['fields']['delete_customer_profile']['table'] = 'cowpro_customer_profile';
  $handler->display->display_options['fields']['delete_customer_profile']['field'] = 'delete_customer_profile';
  /* Filter criterion: CowPro Customer profile: Address (cowpro_customer_address:name_line) */
  $handler->display->display_options['filters']['cowpro_customer_address_name_line']['id'] = 'cowpro_customer_address_name_line';
  $handler->display->display_options['filters']['cowpro_customer_address_name_line']['table'] = 'field_data_cowpro_customer_address';
  $handler->display->display_options['filters']['cowpro_customer_address_name_line']['field'] = 'cowpro_customer_address_name_line';
  $handler->display->display_options['filters']['cowpro_customer_address_name_line']['operator'] = 'contains';
  $handler->display->display_options['filters']['cowpro_customer_address_name_line']['exposed'] = TRUE;
  $handler->display->display_options['filters']['cowpro_customer_address_name_line']['expose']['operator_id'] = 'cowpro_customer_address_name_line_op';
  $handler->display->display_options['filters']['cowpro_customer_address_name_line']['expose']['label'] = 'Filter by names containing';
  $handler->display->display_options['filters']['cowpro_customer_address_name_line']['expose']['operator'] = 'cowpro_customer_address_name_line_op';
  $handler->display->display_options['filters']['cowpro_customer_address_name_line']['expose']['identifier'] = 'name';

  /* Display: Admin page */
  $handler = $view->new_display('page', 'Admin page', 'page_1');
	$handler->display->display_options['path'] = 'admin/cowpro/customer-profiles/list';
	$handler->display->display_options['menu']['type'] = 'normal';
	$handler->display->display_options['menu']['title'] = '浏览用户资料';
	$handler->display->display_options['menu']['weight'] = '-10';
	$handler->display->display_options['menu']['name'] = 'management';
	$handler->display->display_options['menu']['context'] = 0;
	$handler->display->display_options['menu']['context_only_inline'] = 0;
  $handler->display->display_options['tab_options']['title'] = '浏览用户资料';
  $handler->display->display_options['tab_options']['description'] = '管理网站上的用户资料以及资料的类型(Manage customer profiles and profile types).';
  $handler->display->display_options['tab_options']['weight'] = '0';
  $handler->display->display_options['tab_options']['name'] = 'user-menu';

  $translatables['cowpro_customer_profiles'] = array(
    t('Defaults'),
    t('Customer profiles'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('Items per page'),
    t('- All -'),
    t('Offset'),
    t('« first'),
    t('‹ previous'),
    t('next ›'),
    t('last »'),
    t('Profile owner'),
    t('Profile ID'),
    t('Name'),
    t('User'),
    t('Type'),
    t('Status'),
    t('Operations'),
    t('Delete link'),
    t('Filter by names containing'),
    t('Admin page'),
  );

  $views[$view->name] = $view;

  return $views;
}
