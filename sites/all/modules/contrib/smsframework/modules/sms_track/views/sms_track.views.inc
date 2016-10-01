<?php

/**
 * @file
 * SMS Framework Message Tracking feature module: views
 *
 * @package sms
 * @subpackage sms_track
 */

/**
 * Implements hook_views_handlers().
 */
function sms_track_views_handlers() {
  return array(
    'info' => array(
      'path' => drupal_get_path('module', 'sms_track') . '/views',
    ),
    'handlers' => array(
      'sms_track_handler_field_direction' => array(
        'parent' => 'views_handler_field',
      ),
      'sms_track_handler_field_local_number' => array(
        'parent' => 'views_handler_field',
      ),
      'sms_track_handler_field_gateway' => array(
        'parent' => 'views_handler_field',
      ),
    ),
  );
}


/**
 * Implements hook_views_data().
 */
function sms_track_views_data() {
  // TODO: I have left id and options out of this until I can work out how the handlers work.
  return array(
    'sms_track' => array(
      'table' => array(
        'group' => t('SMS Archive'),
        'base' => array(
          'field' => 'id',
          'title' => t('SMS Archive'),
          'help' => t("An archive of sent and received SMS messages."),
          'weight' => 0,
        ),
      ),
      'id' => array(
        'title' => t('ID'),
        'help' => t('Message archive ID.'),
        'field' => array(
          'handler' => 'views_handler_field_numeric',
          'click sortable' => TRUE,
        ),
        'argument' => array(
          'handler' => 'views_handler_argument_numeric',
          'numeric' => TRUE,
        ),
        'filter' => array(
          'handler' => 'views_handler_filter_numeric',
          'numeric' => TRUE,
        ),
        'sort' => array(
          'handler' => 'views_handler_sort_numeric',
          'numeric' => TRUE,
        ),
      ),
      'created' => array(
        'title' => t('Timestamp'),
        'help' => t('Message creation timestamp.'),
        'field' => array(
          'handler' => 'views_handler_field_date',
          'click sortable' => TRUE,
        ),
        'argument' => array(
          'handler' => 'views_handler_argument_date',
        ),
        'filter' => array(
          'handler' => 'views_handler_filter',
        ),
        'sort' => array(
          'handler' => 'views_handler_sort_date',
        ),
      ),
      'dir' => array(
        'title' => t('Direction'),
        'help' => t('Incoming or Outgoing.'),
        'field' => array(
          'handler' => 'sms_track_handler_field_direction',
          'click sortable' => TRUE,
        ),
        'argument' => array(
          'handler' => 'views_handler_argument',
        ),
        'filter' => array(
          'handler' => 'views_handler_filter',
        ),
        'sort' => array(
          'handler' => 'views_handler_sort',
        ),
      ),
      'number' => array(
        'title' => t('Remote number'),
        'help' => t('Phone number of remote recipient/sender.'),
        'field' => array(
          'handler' => 'views_handler_field',
          'click sortable' => TRUE,
        ),
        'argument' => array(
          'handler' => 'views_handler_argument',
        ),
        'filter' => array(
          'handler' => 'views_handler_filter',
        ),
        'sort' => array(
          'handler' => 'views_handler_sort',
        ),
      ),
      'message' => array(
        'title' => t('Message'),
        'help' => t('The message body text.'),
        'field' => array(
          'handler' => 'views_handler_field',
          'click sortable' => TRUE,
        ),
        'argument' => array(
          'handler' => 'views_handler_argument',
        ),
        'filter' => array(
          'handler' => 'views_handler_filter',
        ),
        'sort' => array(
          'handler' => 'views_handler_sort',
        ),
      ),
      'local_number' => array(
        'real field' => 'options',
        'title' => t('Local number'),
        'help' => t('Phone number or ID of remote recipient/sender.'),
        'field' => array(
          'handler' => 'sms_track_handler_field_local_number',
          'click sortable' => TRUE,
        ),
        'argument' => array(
          'handler' => 'views_handler_argument',
        ),
        'filter' => array(
          'handler' => 'views_handler_filter',
        ),
        'sort' => array(
          'handler' => 'views_handler_sort',
        ),
      ),
      'gateway' => array(
        'real field' => 'options',
        'title' => t('Gateway'),
        'help' => t('SMS gateway module name.'),
        'field' => array(
          'handler' => 'sms_track_handler_field_gateway',
          'click sortable' => TRUE,
        ),
        'argument' => array(
          'handler' => 'views_handler_argument',
        ),
        'filter' => array(
          'handler' => 'views_handler_filter',
        ),
        'sort' => array(
          'handler' => 'views_handler_sort',
        ),
      ),
      // Additional Author and Recipient ID fields.
      'author' => array(
        'title' => t('Author'),
        'help' => t('User ID of remote author.'),
        'field' => array(
          'handler' => 'views_handler_field',
          'click sortable' => TRUE,
        ),
        'argument' => array(
          'handler' => 'views_handler_argument',
        ),
        'filter' => array(
          'handler' => 'views_handler_filter',
        ),
        'sort' => array(
          'handler' => 'views_handler_sort',
        ),
        'relationship' => array(
          'title' => t('SMS Author'),
          'help' => t('Relate sms to the user who created it. This relationship will create one record for each sms sent by the user.'),
          'handler' => 'views_handler_relationship',
          'base' => 'users',
          'base field' => 'uid',
          'field' => 'author',
          'label' => t('Author'),
        ),
      ),
      'recipient' => array(
        'title' => t('Recipient'),
        'help' => t('User ID of remote recipient.'),
        'field' => array(
          'handler' => 'views_handler_field',
          'click sortable' => TRUE,
        ),
        'argument' => array(
          'handler' => 'views_handler_argument',
        ),
        'filter' => array(
          'handler' => 'views_handler_filter',
        ),
        'sort' => array(
          'handler' => 'views_handler_sort',
        ),
        'relationship' => array(
          'title' => t('SMS Recipient'),
          'help' => t('Relate sms to the user who received it. This relationship will create one record for each sms received by the user.'),
          'handler' => 'views_handler_relationship',
          'base' => 'users',
          'base field' => 'uid',
          'field' => 'recipient',
          'label' => t('Recipient'),
        ),
      ),
    ),
  );
}

/**
 * Implements hook_views_query_alter()
 */
function sms_track_views_query_alter(&$view, &$query) {
  // Use an OR condition for the contextual filters.
  if ($view->name == 'my_messages') {
    $query->where[0]['type'] = 'OR';
  }
}

/**
 * Implements hook_views_post_render()
 */
function sms_track_views_post_render(&$view, &$output, &$cache) {
  // Change the class names of rows to lowercase after token replacement.
  if ($view->name == 'my_messages') {
    $results = $view->result;
    foreach ($results as $key => $value) {
      if ($results[$key]->sms_track_dir == "0") {
        $output = preg_replace('/Outbound/', 'outbound', $output, 1);
      }
      elseif ($results[$key]->sms_track_dir == "1") {
        $output = preg_replace('/Inbound/', 'inbound', $output, 1);
      }
    }
  }
}
