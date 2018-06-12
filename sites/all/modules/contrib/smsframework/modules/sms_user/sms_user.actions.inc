<?php

/**
 * @file
 * SMS User Action Implementation.
 */

/**
 * Implements hook_action_info().
 */
function sms_user_action_info() {
  $info['sms_user_send_sms_action'] = array(
    'type' => 'user',
    'label' => t('Send SMS to Users'),
    'configurable' => TRUE,
  );
  return $info;
}

/**
 * Callback for the 'Send SMS to Users' action.
 *
 * @param object $user
 *   The user to which the message will be sent.
 * @param array $context
 *   The action context.
 */
function sms_user_send_sms_action(&$user, $context) {
  $message = $context['sms_text'];
  sms_user_send($user->uid, $message);
}

/**
 * Input form for the 'Send SMS to Users' action.
 *
 * @param array $context
 *   The action context.
 *
 * @return array
 *   The form array.
 */
function sms_user_send_sms_action_form($context) {
  $limit = variable_get('sms_user_max_chars', SMS_USER_MAX_CHARS);
  drupal_add_js(drupal_get_path('module', 'sms_user') . '/sms_user.js');

  $form['sms_text'] = array(
    '#type' => 'textarea',
    '#title' => 'SMS Text',
    '#required' => TRUE,
  );
  $form['sms_limit'] = array(
    '#type' => 'markup',
    '#prefix' => '<div id="keystrokes" class="description" limit="' . $limit . '"><span></span>',
    '#value' => t('@max chars max', array('@max' => $limit)),
    '#suffix' => '</div>',
  );

  return $form;
}

/**
 * Form validation handler for the 'Send SMS to Users' action.
 */
function sms_user_send_sms_action_validate($form, $form_state) {
  $sms_text = $form_state['values']['sms_text'];
  if (empty($sms_text)) {
    form_set_error('sms_text', t('This field is required'));
  }
  $length = drupal_strlen($sms_text);
  if ($length > variable_get('sms_user_max_chars', SMS_USER_MAX_CHARS)) {
    $error = t('SMS too long: (@text) [length=@len]',
        array('@text' => $sms_text, '@len' => $length));
    form_set_error('sms_text', $error);
  }
}

/**
 * Form submit handler for the 'Send SMS to Users' action.
 */
function sms_user_send_sms_action_submit($form, $form_state) {
  $context['sms_text'] = $form_state['values']['sms_text'];
  return $context;
}
