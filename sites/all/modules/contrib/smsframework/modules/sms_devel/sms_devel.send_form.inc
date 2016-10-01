<?php

/**
 * @file
 * Test send form include for the sms_devel module of the SMS Framework.
 *
 * @package sms
 * @subpackage sms_devel
 */


/**
 * Form constructor for sms_devel test send form.
 *
 * @see sms_devel_send_form_submit()
 */
function sms_devel_send_form($form, &$form_state) {
  // Message to the user about the form.
  $form['about'] = array(
    '#type' => 'item',
    '#value' => 'This is a basic form that contains:<ul><li>include sms_send_form()</li><li>message text field</li><li>submit button</li></ul>The form validation includes sms_send_form_validate().<br/>The form submission includes sms_send_form_submit() which sends the message, and a little note that the form submitted ok.',
  );

  // Include the sms_send_form from the SMS Framework core.
  $form = array_merge($form, sms_send_form());

  // Message text field for the send form.
  $form['message'] = array(
    '#type' => 'textarea',
    '#title' => t('Message'),
    '#rows' => 4,
    '#cols' => 40,
    '#resizable' => FALSE,
  );

  // Submit button for the send form.
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => 'Send Message',
    '#validate' => array('sms_send_form_validate'),
    '#submit' => array('sms_send_form_submit', 'sms_devel_send_form_submit'),
  );

  // Receive Message Button for testing incoming messages.
  $form['receive'] = array(
    '#type' => 'submit',
    '#value' => 'Receive Message',
    '#submit' => array('sms_devel_receive_form_submit'),
  );

  return $form;
}

/**
 * Submit handler for sms_devel test send form.
 *
 * @see sms_devel_send_form()
 */
function sms_devel_send_form_submit($form, &$form_state) {
  // Display a message to the user.
  $number  = $form_state['values']['number'];
  $message = $form_state['values']['message'];
  drupal_set_message(check_plain(t("Form submitted ok for number $number and message: $message")));
}

/**
 * Submit handler for Receive Message button on sms_devel test send form.
 *
 * @see sms_devel_send_form()
 */
function sms_devel_receive_form_submit($form, &$form_state) {
  // Display a message to the user.
  $number  = $form_state['values']['number'];
  $message = $form_state['values']['message'];
  sms_incoming($number, $message);
  drupal_set_message(check_plain(t("Message received from number $number and message: $message")));
}
