<?php

/**
 * @file
 * Provide views data and handlers for media_library.module.
 *
 * @ingroup views_module_handlers
 */

/**
 * Implements hook_views_data().
 */
function media_library_views_data() {
  // published status
  $data['file_managed']['library'] = array(
    'title' => t('Library'),
    'help' => t('Whether or not the file is in the media library.'),
    'field' => array(
      'handler' => 'views_handler_field_boolean',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_boolean_operator',
      'label' => t('Library'),
      'type' => 'yes-no',
      'use equal' => TRUE, // Use status = 1 instead of status <> 0 in WHERE statment
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );

  return $data;
}

/**
 * Implements hook_views_default_views_alter().
 */
function media_library_views_default_views_alter(&$views) {
  if (isset($views['media_default'])) {
    // Modify the title of the media_browser_1 display.
    $handler =& $views['media_default']->display['media_browser_1']->handler;
    $handler->display->display_options['title'] = 'All Files';

    /* Display: Media library */
    $handler = $views['media_default']->new_display('media_browser', 'Media library', 'media_browser_2');
    $handler->display->display_options['defaults']['title'] = FALSE;
    $handler->display->display_options['title'] = 'Media Library';
    $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
    $handler->display->display_options['defaults']['filter_groups'] = FALSE;
    $handler->display->display_options['defaults']['filters'] = FALSE;
    /* Filter criterion: File: Status */
    $handler->display->display_options['filters']['status']['id'] = 'status';
    $handler->display->display_options['filters']['status']['table'] = 'file_managed';
    $handler->display->display_options['filters']['status']['field'] = 'status';
    $handler->display->display_options['filters']['status']['value'] = array(
      1 => '1',
    );
    /* Filter criterion: File: Name */
    $handler->display->display_options['filters']['filename']['id'] = 'filename';
    $handler->display->display_options['filters']['filename']['table'] = 'file_managed';
    $handler->display->display_options['filters']['filename']['field'] = 'filename';
    $handler->display->display_options['filters']['filename']['operator'] = 'contains';
    $handler->display->display_options['filters']['filename']['exposed'] = TRUE;
    $handler->display->display_options['filters']['filename']['expose']['operator_id'] = 'filename_op';
    $handler->display->display_options['filters']['filename']['expose']['label'] = 'File name';
    $handler->display->display_options['filters']['filename']['expose']['operator'] = 'filename_op';
    $handler->display->display_options['filters']['filename']['expose']['identifier'] = 'filename';
    /* Filter criterion: File: Type */
    $handler->display->display_options['filters']['type']['id'] = 'type';
    $handler->display->display_options['filters']['type']['table'] = 'file_managed';
    $handler->display->display_options['filters']['type']['field'] = 'type';
    $handler->display->display_options['filters']['type']['exposed'] = TRUE;
    $handler->display->display_options['filters']['type']['expose']['operator_id'] = 'type_op';
    $handler->display->display_options['filters']['type']['expose']['label'] = 'Type';
    $handler->display->display_options['filters']['type']['expose']['operator'] = 'type_op';
    $handler->display->display_options['filters']['type']['expose']['identifier'] = 'type';
    /* Filter criterion: File: Library */
    $handler->display->display_options['filters']['library']['id'] = 'library';
    $handler->display->display_options['filters']['library']['table'] = 'file_managed';
    $handler->display->display_options['filters']['library']['field'] = 'library';
    $handler->display->display_options['filters']['library']['value'] = '1';

    // return views
    return $views;
  }
}
