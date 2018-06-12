<?php

/**
 * @file
 * SMS Framework hooks.
 */

/**
 * Defines information for an SMS Gateway.
 *
 * @return array
 */
function hook_gateway_info() {
  return array(
    'my_gateway' => array(
      'name' => 'My Gateway',
      'send' => 'my_gateway_send',
      'receive' => TRUE,
      'configure form' => 'my_gateway_admin_form',
      'send form' => 'my_gateway_send_form',
    ),
  );
}

/**
 * Alter gateway information.
 *
 * This hook gives you a chance to modify gateways after all plugin definitions
 * are discovered.
 *
 * @param array $gateway_info
 *   An array containing gateway information.
 * @param string $gateway_id
 *   The gateway ID.
 */
function hook_sms_gateway_info_alter($gateway_info, $gateway_id) {
  if ($gateway_id === 'log') {
    $gateway_info['name'] = t('The Logger');
  }
}

/**
 * Handle and process incoming SMS messages.
 *
 * @param string $op
 *   Either 'pre process', 'process' or 'post process'.
 * @param string $number
 *   The recipient phone number.
 * @param string $message
 *   The incoming SMS message.
 * @param array $options
 *   An array of options for the SMS message.
 */
function hook_sms_incoming($op, $number, $message, array $options) {
  switch ($op) {
    case 'pre process':
      watchdog('sms', t('Incoming message received from @number', array('@number' => $number)));
      break;
    case 'post process':
      drupal_mail('sms', 'incoming', 'user@example.com', 'en', array());
      break;
  }
}

/**
 * Handle and process SMS message receipts from gateways.
 *
 * @param string $op
 *   Either 'pre process', 'process' or 'post process'.
 * @param string $number
 *   The recipient phone number.
 * @param string $reference
 *   The unique reference ID for this particular message and recipient.
 * @param string $message_status
 *   The SMS message status from the predefined SMS_GW_* or SMS_MSG_STATUS_*
 *   codes.
 * @param array $options
 *   An array of options for the SMS message.
 */
function hook_sms_receipt($op, $number, $reference, $message_status, array $options) {
  switch ($op) {
    case 'pre process':
      watchdog('sms', t('Message receipt with status @status from @number', array('@number' => $number, '@status' => $message_status)));
      break;
    case 'post process':
      drupal_mail('sms', 'receipt', 'user@example.com', 'en', array());
      break;
  }
}
