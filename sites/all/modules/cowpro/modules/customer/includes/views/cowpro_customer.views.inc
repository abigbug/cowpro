<?php

/**
 * Export Drupal CowPro customer profiles to Views.
 */

/**
 * Implements hook_views_data()
 */
function cowpro_customer_views_data() {
  $data = array();

  $data['cowpro_customer_profile']['table']['group']  = t('CowPro Customer Profile');

  $data['cowpro_customer_profile']['table']['base'] = array(
    'field' => 'profile_id',
    'title' => t('CowPro Customer Profile'),
    'help' => t('Customer profiles containing addresses and other customer information.'),
    'access query tag' => 'cowpro_customer_profile_access',
  );
  $data['cowpro_customer_profile']['table']['entity type'] = 'cowpro_customer_profile';

  // Expose the profile ID.
  $data['cowpro_customer_profile']['profile_id'] = array(
    'title' => t('Profile ID'),
    'help' => t('The unique internal identifier of the profile.'),
    'field' => array(
      'handler' => 'cowpro_customer_handler_field_customer_profile',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
    ),
  );

  // Expose the profile type.
  $data['cowpro_customer_profile']['type'] = array(
    'title' => t('Type'),
    'help' => t('The human-readable name of the type of the customer profile.'),
    'field' => array(
      'handler' => 'cowpro_customer_handler_field_customer_profile_type',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'cowpro_customer_handler_filter_customer_profile_type',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );

  // Expose the owner uid.
  $data['cowpro_customer_profile']['uid'] = array(
    'title' => t('Owner'),
    'help' => t('Relate a profile to the user it belongs to.'),
    'relationship' => array(
      'handler' => 'views_handler_relationship',
      'base' => 'users',
      'field' => 'uid',
      'label' => t('Profile owner'),
    ),
  );

  // Expose the profile verified.
  $data['cowpro_customer_profile']['verified'] = array(
    'title' => '认证',
    'help' => '用户资料是否经过认证.',
    'field' => array(
      'handler' => 'views_handler_field_boolean',
      'click sortable' => TRUE,
      'output formats' => array(
        'active-disabled' => array('已认证', '末认证'),
      ),
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_boolean_operator',
      'label' => t('Active'),
      'type' => 'yes-no',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );

  // Expose the created and changed timestamps.
  $data['cowpro_customer_profile']['created'] = array(
    'title' => t('Created date'),
    'help' => t('The date the profile was created.'),
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

  $data['cowpro_customer_profile']['created_fulldate'] = array(
    'title' => t('Created date'),
    'help' => t('In the form of CCYYMMDD.'),
    'argument' => array(
      'field' => 'created',
      'handler' => 'views_handler_argument_node_created_fulldate',
    ),
  );

  $data['cowpro_customer_profile']['created_year_month'] = array(
    'title' => t('Created year + month'),
    'help' => t('In the form of YYYYMM.'),
    'argument' => array(
      'field' => 'created',
      'handler' => 'views_handler_argument_node_created_year_month',
    ),
  );

  $data['cowpro_customer_profile']['created_timestamp_year'] = array(
    'title' => t('Created year'),
    'help' => t('In the form of YYYY.'),
    'argument' => array(
      'field' => 'created',
      'handler' => 'views_handler_argument_node_created_year',
    ),
  );

  $data['cowpro_customer_profile']['created_month'] = array(
    'title' => t('Created month'),
    'help' => t('In the form of MM (01 - 12).'),
    'argument' => array(
      'field' => 'created',
      'handler' => 'views_handler_argument_node_created_month',
    ),
  );

  $data['cowpro_customer_profile']['created_day'] = array(
    'title' => t('Created day'),
    'help' => t('In the form of DD (01 - 31).'),
    'argument' => array(
      'field' => 'created',
      'handler' => 'views_handler_argument_node_created_day',
    ),
  );

  $data['cowpro_customer_profile']['created_week'] = array(
    'title' => t('Created week'),
    'help' => t('In the form of WW (01 - 53).'),
    'argument' => array(
      'field' => 'created',
      'handler' => 'views_handler_argument_node_created_week',
    ),
  );

  $data['cowpro_customer_profile']['changed'] = array(
    'title' => t('Updated date'),
    'help' => t('The date the profile was last updated.'),
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

  $data['cowpro_customer_profile']['changed_fulldate'] = array(
    'title' => t('Updated date'),
    'help' => t('In the form of CCYYMMDD.'),
    'argument' => array(
      'field' => 'changed',
      'handler' => 'views_handler_argument_node_created_fulldate',
    ),
  );

  $data['cowpro_customer_profile']['changed_year_month'] = array(
    'title' => t('Updated year + month'),
    'help' => t('In the form of YYYYMM.'),
    'argument' => array(
      'field' => 'changed',
      'handler' => 'views_handler_argument_node_created_year_month',
    ),
  );

  $data['cowpro_customer_profile']['changed_timestamp_year'] = array(
    'title' => t('Updated year'),
    'help' => t('In the form of YYYY.'),
    'argument' => array(
      'field' => 'changed',
      'handler' => 'views_handler_argument_node_created_year',
    ),
  );

  $data['cowpro_customer_profile']['changed_month'] = array(
    'title' => t('Updated month'),
    'help' => t('In the form of MM (01 - 12).'),
    'argument' => array(
      'field' => 'changed',
      'handler' => 'views_handler_argument_node_created_month',
    ),
  );

  $data['cowpro_customer_profile']['changed_day'] = array(
    'title' => t('Updated day'),
    'help' => t('In the form of DD (01 - 31).'),
    'argument' => array(
      'field' => 'changed',
      'handler' => 'views_handler_argument_node_created_day',
    ),
  );

  $data['cowpro_customer_profile']['changed_week'] = array(
    'title' => t('Updated week'),
    'help' => t('In the form of WW (01 - 53).'),
    'argument' => array(
      'field' => 'changed',
      'handler' => 'views_handler_argument_node_created_week',
    ),
  );

  // Expose links to operate on the profile.
  $data['cowpro_customer_profile']['view_customer_profile'] = array(
    'field' => array(
      'title' => t('Link'),
      'help' => t('Provide a simple link to the administrator view of the profile.'),
      'handler' => 'cowpro_customer_handler_field_customer_profile_link',
    ),
  );
  $data['cowpro_customer_profile']['edit_customer_profile'] = array(
    'field' => array(
      'title' => t('Edit link'),
      'help' => t('Provide a simple link to edit the profile.'),
      'handler' => 'cowpro_customer_handler_field_customer_profile_link_edit',
    ),
  );
  $data['cowpro_customer_profile']['delete_customer_profile'] = array(
    'field' => array(
      'title' => t('Delete link'),
      'help' => t('Provide a simple link to delete the profile.'),
      'handler' => 'cowpro_customer_handler_field_customer_profile_link_delete',
    ),
  );

  $data['cowpro_customer_profile']['empty_text'] = array(
    'title' => t('Empty text'),
    'help' => t('Displays an appropriate empty text message for customer profile lists.'),
    'area' => array(
      'handler' => 'cowpro_customer_handler_area_empty_text',
    ),
  );

  return $data;
}
