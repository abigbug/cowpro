<?php

/**
 * @file
 * Virtual Gateway for the sms_devel module of the SMS Framework.
 *
 * @package sms
 * @subpackage sms_devel
 */

/*
 A table is required to store activity, to be queried by the interactor page
 Note: I have changed the "server-side number" nomenclature from "sender" &
 "in_number" to simply "gw_number".
 */

define('SMS_DEVEL_VIRTUALGW_TYPE_OUT',      0);
define('SMS_DEVEL_VIRTUALGW_TYPE_IN',       1);
define('SMS_DEVEL_VIRTUALGW_TYPE_RECEIPT', 2);

/**
 * Callback for sending messages.
 *
 * Options for this send function:
 *   gw_number - The sender of the message. MSISDN or text string. Min=3, max=11 chars.
 *   reference - Message reference tag (to appear on any receipt).
 *
 * @param string $number
 *   MSISDN of message recipient. Should include the country code prefix.
 * @param string $message
 *   Message body text.
 * @param array $options
 *   Options array from SMS Framework.
 *
 * @return array
 *   Gateway response array with the following keys:
 *   - status: true (successful) or false (failed).
 *   - status_code: standardized sms gateway status codes.
 *   - gateway_status_code: gateway-specific status code.
 *   - gateway_status_text: text describing the gateway-specific status code.
 */
function sms_devel_virtualgw_send($number, $message, $options) {
  // Set a default sender if it is not specified
  if (! array_key_exists('gw_number', $options)) {
    $options['gw_number'] = '99999';
  }

  // Set a default reference if it is not specified
  if (! array_key_exists('reference', $options)) {
    $options['reference'] = md5($number . $message);
  }

  // Write log record for outgoing message
  sms_devel_virtualgw_log_insert(SMS_DEVEL_VIRTUALGW_TYPE_OUT, $number, $message, $options);

  // Invoke additional virtual gateway features eg: autoreplies, receipts.
  sms_devel_virtualgw_sendlogic($number, $message, $options);

  // Always return success
  return array(
    'status' => TRUE,
    'status_code' => SMS_GW_OK,
    'gateway_status_code' => 'OK',
    'gateway_status_text' => 'sms_devel_virtualgw: send: OK',
  );
}


/**
 * Handles incoming messages.
 *
 * @param string $number
 *   The sender numbers.
 * @param string $message
 *   The message received.
 * @param array $options
 *   Array of options.
 */
function sms_devel_virtualgw_receiver($number = NULL, $message = NULL, $options = array()) {
  // Handle HTTP requests rather than direct function calls
  if ($number === NULL) {
    $number  = $_REQUEST['number'];
    $message = (array_key_exists('message', $_REQUEST)) ? $_REQUEST['message'] : 'NO_MESSAGE';
    $options['gw_number'] = (array_key_exists('gw_number', $_REQUEST)) ? $_REQUEST['gw_number'] : 'NO_GW_NUMBER';
    $options['reference'] = (array_key_exists('reference', $_REQUEST)) ? $_REQUEST['reference'] : 'NO_REFERENCE';
  }

  // Write log record for incoming message
  sms_devel_virtualgw_log_insert(SMS_DEVEL_VIRTUALGW_TYPE_IN, $number, $message, $options);

  // Call SMS Framework incoming message handler
  sms_incoming($number, $message, $options);
}


/**
 * Writes incoming and outgoing messages to the log.
 *
 * @param string $type
 *   The message type (incoming or outgoing).
 * @param string $number
 *   The sender numbers.
 * @param string $message
 *   The message received.
 * @param array $options
 *   Array of options.
 *
 * @return boolean
 *   true if logging was successful, false otherwise.
 */
function sms_devel_virtualgw_log_insert($type, $number = '', $message = '', $options = array()) {
  $options_z = serialize($options);
  $result = $id = db_insert('sms_devel_virtualgw')
    ->fields(array(
      'created' => REQUEST_TIME,
      'type' => $type,
      'number' => $number,
      'message' => $message,
      'options' => $options_z,
    ))
    ->execute();
  return $result;
}


/**
 * Invokes additional virtual gateway features eg: autoreplies, receipts.
 *
 * @param string $number
 *   The recipient numbers.
 * @param string $message
 *   The message being sent.
 * @param array $options
 *   An array of options.
 */
function sms_devel_virtualgw_sendlogic($number, $message, $options) {
  $autoreply_enabled = variable_get('sms_devel_virtualgw_autoreply_enabled', FALSE);
  $autoreply_format  = variable_get('sms_devel_virtualgw_autoreply_format',   '');
  $receipts_enabled  = variable_get('sms_devel_virtualgw_receipts_enabled',   FALSE);

  if ($autoreply_enabled) {
    // TODO Figure out the tokens logic
    // $echo_message = $autoreply_format . $message;
    $echo_message = 'echo: ' . $message;

    // Swap the numbers for the echo.
    $echo_number  = $options['gw_number'];
    $echo_options = array('gw_number' => $number);

    // Echo
    sms_devel_virtualgw_receiver($echo_number, $echo_message, $echo_options);
  }

  if ($receipts_enabled) {
    // Trigger a message delivery receipt
    $status = SMS_MSG_STATUS_DELIVERED;
    $reference = $options['reference'];
    $options['gateway_message_status'] = 'DELIVERED';
    $options['gateway_message_status_text'] = 'Message delivered OK';

    sms_receipt($number, $reference, $status, $options);
  }
}


/**
 * Ajax page callback providing logged virtual gateway activity.
 */
function sms_devel_virtualgw_js_getactivity() {
  // We should not need to get a default limit - expect it in the request
  $limit = 50;
  // Get limit from request
  if (array_key_exists('rows', $_REQUEST)) {
    $limit = $_REQUEST['rows'];
  }
  // Handle zero or null limit
  if ( ! $limit ) {
    $limit = 1;
  }

  $lines = array();

  $result = db_query("SELECT * FROM {sms_devel_virtualgw} ORDER BY created LIMIT %d", $limit)->execute();
  foreach ($result as $row) {
    $options = unserialize($row->options);
    switch ($row->type) {
      case SMS_DEVEL_VIRTUALGW_TYPE_OUT:
        $from = $options['sender'];
        $to   = $row->number;
        break;
      case SMS_DEVEL_VIRTUALGW_TYPE_IN:
        $from = $row->number;
        $to   = $options['sender'];
        break;
      case SMS_DEVEL_VIRTUALGW_TYPE_RECEIPT:
        // Receipt
    }
    $dir = $row->type;
    $msg = $row->message;

    $lines[] = "$dir $from $to $msg";
  }

  $output = implode("\n", $lines);

  $form_state = array(
    'storage' => NULL,
    'submitted' => FALSE,
  );
  $form_build_id = check_plain($_POST['form_build_id']);
  // Get the form from the cache.
  $form = form_get_cache($form_build_id, $form_state);
  $args = $form['#parameters'];
  $form_id = array_shift($args);
  // We will run some of the submit handlers so we need to disable redirecting.
  $form_state['#redirect'] = FALSE;
  // We need to process the form, prepare for that by setting a few internals
  // variables.
  $form['#post'] = $_POST;
  $form['#programmed'] = FALSE;
  $form_state['post'] = $_POST;
  // Build, validate and if possible, submit the form.
  drupal_process_form($form_id, $form, $form_state);
  // This call recreates the form relying solely on the form_state that the
  // drupal_process_form set up.
  $form = drupal_rebuild_form($form_id, $form_state, $args, $form_build_id);
  // Render the new output.
  $logfield = $form['sms_devel_virtualgw_log']['sms_devel_virtualgw_logfield'];
  $logfield['#value'] = $output;
  unset($logfield['#prefix'], $logfield['#suffix']); // Prevent duplicate wrappers.
  $output = drupal_render($logfield);

  drupal_json_output(array('status' => TRUE, 'data' => $output));
}


/**
 * Performs an ajax send to virtual gateway.
 */
function sms_devel_virtualgw_ahah_send() {
  $result = drupal_http_request(
    url('sms/virtualgw/receiver', array('absolute' => TRUE)), array('headers' => array('Content-Type' => 'application/x-www-form-urlencoded'), 'method' => 'POST', 'data' => http_build_query(array(
      'number' => $_POST['sms_devel_virtualgw_from'],
      'message' => $_POST['sms_devel_virtualgw_message'],
      'gw_number' => $_POST['sms_devel_virtualgw_to'],
    ), '', '&')));

  // Return a good status
  drupal_json_output(array('status' => TRUE));
}
