<?php

/**
 * @file
 * Rules module integration for the smsframework.
 */

/**
 * Implements hook_rules_event_info().
 */
function sms_rules_event_info() {
  return array(
    'sms_incoming' => array(
      'label' => t('A SMS message is received'),
      'access callback' => 'sms_rules_access_callback',
      'module' => 'sms',
      'group' => t('SMS'),
      'variables' => array(
        'sms' => array(
          'label' => t('SMS Message'),
          'description' => t('The SMS message and metadata.'),
          'type' => 'sms',
        ),
      ),
    ),
  );
}

/**
 * Implements hook_rules_data_info().
 */
function sms_rules_data_info() {
  return array(
    'sms' => array(
      'label' => t('SMS Message'),
      'wrap' => TRUE,
      'property info' => _sms_rules_sms_info(),
    ),
  );
}

/**
 * Defines property info for sms messages.
 */
function _sms_rules_sms_info() {
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
function sms_rules_action_info() {
  return array(
    'sms_send' => array(
      'label' => t('Send sms'),
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
          'description' => t("The sms message body."),
        ),
      ),
      'base' => 'sms_rules_action_sms_send',
      'access callback' => 'sms_rules_access_callback',
    ),
  );
}

/**
 * Action Implementation: Send sms.
 *
 * @param string $to
 *   The sms recipient.
 * @param string $message
 *   The message to be sent.
 */
function sms_rules_action_sms_send($to, $message) {
  sms_send($to, $message);
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
function sms_rules_access_callback($type) {
  return user_access('administer smsframework');
}

/**
 * Implements hook_rules_condition_info()
 */
function sms_rules_condition_info() {
  return array(
    'sms_message_contains_keyword' => array(
      'label' => t('An incoming SMS message contains keyword'),
      'arguments' => array(
        'sms:select' => array(
          'label' => t('SMS Message'),
          'description' => t('The SMS message and metadata.'),
          'type' => 'sms',
        ),
        'keyword' => array(
          'label' => t('Keyword'),
          'description' => t("The keyword to look for."),
          'type' => 'text',
        ),
      ),
      'access callback' => 'sms_rules_access_callback',
      'module' => 'sms',
      'group' => t('SMS'),
    ),
  );
}

/**
 * Condition sms_message_contains_keyword
 */
function sms_message_contains_keyword($sms, $keyword) {
  return (strpos($sms['message'],trim($keyword)) !== FALSE) ? TRUE : FALSE;
}
