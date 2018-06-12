<?php

/**
 * @file
 * Rules module integration for the custodianframework.
 */

/**
 * Implements hook_rules_event_info().
 */
function custodian_rules_event_info() {
  return array(
    'custodian_incoming' => array(
      'label' => t('A SMS message is received'),
      'access callback' => 'custodian_rules_access_callback',
      'module' => 'custodian',
      'group' => t('SMS'),
      'variables' => array(
        'custodian' => array(
          'label' => t('SMS Message'),
          'description' => t('The SMS message and metadata.'),
          'type' => 'custodian',
        ),
      ),
    ),
  );
}

/**
 * Implements hook_rules_data_info().
 */
function custodian_rules_data_info() {
  return array(
    'custodian' => array(
      'label' => t('SMS Message'),
      'wrap' => TRUE,
      'property info' => _custodian_rules_custodian_info(),
    ),
  );
}

/**
 * Defines property info for custodian messages.
 */
function _custodian_rules_custodian_info() {
  return array(
    'number' => array(
      'type' => 'text',
      'label' => t('The number which sent the SMS message'),
    ),
    'message' => array(
      'type' => 'text',
      'label' => ('The SMS message'),
    ),
  );
}

/**
 * Implements hook_rules_action_info().
 */
function custodian_rules_action_info() {
  return array(
    'custodian_send' => array(
      'label' => t('Send custodian'),
      'group' => t('SMS'),
      'parameter' => array(
        'to' => array(
          'type' => 'text',
          'label' => t('To'),
          'description' => t('The destination SMS number'),
        ),
        'message' => array(
          'type' => 'text',
          'label' => t('Message'),
          'description' => t("The custodian message body."),
        ),
      ),
      'base' => 'custodian_rules_action_custodian_send',
      'access callback' => 'custodian_rules_access_callback',
    ),
  );
}

/**
 * Action Implementation: Send custodian.
 *
 * @param string $to
 *   The custodian recipient.
 * @param string $message
 *   The message to be sent.
 */
function custodian_rules_action_custodian_send($to, $message) {
  custodian_send($to, $message);
}

/**
 * Access callback for the SMS Rules integration.
 *
 * @param string $type
 *  The access type.
 *
 * @return bool
 *  true if the user has access, false if not.
 */
function custodian_rules_access_callback($type) {
  return user_access('administer custodianframework');
}

/**
 * Implements hook_rules_condition_info()
 */
function custodian_rules_condition_info() {
  return array(
    'custodian_message_contains_keyword' => array(
      'label' => t('An incoming SMS message contains keyword'),
      'arguments' => array(
        'custodian:select' => array(
          'label' => t('SMS Message'),
          'description' => t('The SMS message and metadata.'),
          'type' => 'custodian',
        ),
        'keyword' => array(
          'label' => t('Keyword'),
          'description' => t("The keyword to look for."),
          'type' => 'text',
        ),
      ),
      'access callback' => 'custodian_rules_access_callback',
      'module' => 'custodian',
      'group' => t('SMS'),
    ),
  );
}

/**
 * Condition custodian_message_contains_keyword
 */
function custodian_message_contains_keyword($custodian, $keyword) {
  return (strpos($custodian['message'],trim($keyword)) !== FALSE) ? TRUE : FALSE;
}
