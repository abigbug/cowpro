<?php

/**
 * @file
 * SMS User Rules Implementation.
 *
 */

/*
 * Implements hook_rules_event_info().
 *
 * @ingroup rules
 */
function sms_user_rules_event_info() {
  return array(
    'sms_user_number_validated' => array(
      'label' => t('User validated SMS code'),
      'group' => t('SMS'),
      'variables' => array(
        'user' => array(
          'type' => 'user',
          'label' => t('User validated SMS code'),
        ),
      ),
    ),
    'sms_user_number_removed' => array(
      'label' => t('User removed mobile phone number'),
      'group' => t('SMS'),
      'variables' => array(
        'user' => array(
          'type' => 'user',
          'label' => t('User removed mobile phone number'),
        ),
      ),
    ),
  );
}

/**
 * Implements hook_rules_action_info().
 */
function sms_user_rules_action_info() {
  return array(
    'sms_action_user_send' => array(
      'label' => t('Send SMS message to user'),
      'group' => t('SMS'),
      'parameter' => array(
        'user' => array(
          'type' => 'user',
          'label' => t('User'),
        ),
        'message' => array(
          'type' => 'text',
          'label' => t('Message'),
        ),
      ),
    ),
    'sms_action_match_user' => array(
      'label' => t('Match mobile number to user'),
      'group' => t('SMS'),
      'parameter' => array(
        'number' => array(
          'type' => 'text',
          'label' => t('Phone number'),
        ),
      ),
      'new variables' => array(
        'user_loaded' => array(
          'type' => 'user',
          'label' => t('Loaded user'),
          // 'label callback' => 'rules_action_load_node_variable_label',
        ),
      ),
    ),
    // Actions for opting out and opting in for sms messages from the site.
    'sms_action_opt_out' => array(
      'label' => t('Let user opt out of sms messages from the site via SMS.'),
      'group' => t('SMS'),
      'arguments' => array(
        'sms:select' => array(
          'label' => t('SMS Message'),
          'description' => t('The SMS message and metadata.'),
          'type' => 'sms',
        ),
      ),
    ),
    'sms_action_opt_in' => array(
      'label' => t('Let user opt in for sms messages from the site via SMS.'),
      'group' => t('SMS'),
      'arguments' => array(
        'sms:select' => array(
          'label' => t('SMS Message'),
          'description' => t('The SMS message and metadata.'),
          'type' => 'sms',
        ),
      ),
    ),
  );
}

/**
 * Rules action callback to send sms message to user.
 *
 * @param object $user
 *   The user to whom the message will be sent.
 * @param string $message
 *   The message to be sent.
 */
function sms_action_user_send($user, $message) {
  sms_user_send($user->uid, $message);
}

/**
 * Rules action callback to match number to user.
 *
 * @param string $number
 *   The number to which we want to get the user.
 *
 * @return array
 *   An array conforming to rules conventions with the key 'user_loaded' and a
 *   value corresponding to the user with the specified number.
 */
function sms_action_match_user($number) {
  return array('user_loaded' => user_load(sms_user_get_uid($number)));
}

/**
 * Action Implementation: Check the SMS User opt out checkbox.
 *
 * @param array $sms
 *   The message that was sent and it's metadata.
 */
function sms_action_opt_out($sms) {
  $account = user_load(sms_user_get_uid($sms['number']));
  if (isset($account->sms_user)) {
    $data = $account->sms_user;
  }
  else {
    $data = Array();
  }
  $data['sms_user_opt_out'] = TRUE;
  user_save($account, array('sms_user' => $data), 'mobile');
}

/**
 * Action Implementation: Uncheck SMS User the opt out checkbox.
 *
 * @param array $sms
 *   The message that was sent and it's metadata.
 */
function sms_action_opt_in($sms) {
  $account = user_load(sms_user_get_uid($sms['number']));
  if (isset($account->sms_user)) {
    $data = $account->sms_user;
  }
  else {
    $data = Array();
  }
  $data['sms_user_opt_out'] = FALSE;
  user_save($account, array('sms_user' => $data), 'mobile');
}
