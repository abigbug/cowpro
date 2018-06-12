<?php

/**
 * @file
 * Virtual Gateway for the sms_devel module: Admin forms include
 *
 * @package sms
 * @subpackage sms_devel
 */


/**
 * Form constructor for the gateway module configuration form.
 *
 * @param array $configuration
 *   Array containing configuration information.
 *
 * @return
 *   Drupal form array.
 *
 * @see sms_devel_virtualgw_form()
 */
function sms_devel_virtualgw_settings_form($configuration) {
  $form['sms_devel_virtualgw_link'] = array(
    '#type' => 'item',
    '#value' => 'See also: ' . l(t('Virtual Gateway dashboard'), 'admin/smsframework/devel/virtualgw'),
  );

  return $form;
}


/**
 * Form constructor for the virtual gateway configuration.
 */
function sms_devel_virtualgw_form($form, &$form_state) {
  $form['sms_devel_virtualgw_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Settings'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['sms_devel_virtualgw_settings']['sms_devel_virtualgw_autoreply_enabled'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable autoreply'),
    '#default_value' => variable_get('sms_devel_virtualgw_autoreply_enabled', FALSE),
  );
  $form['sms_devel_virtualgw_settings']['sms_devel_virtualgw_autoreply_format'] = array(
    '#type' => 'textarea',
    '#rows' => 4,
    '#cols' => 40,
    '#resizable' => FALSE,
    '#default_value' => variable_get('sms_devel_virtualgw_autoreply_format', 'echo: {message}'),
    '#description' => t('If enabled then the gateway will reply to your messages through sms_incoming()<br />You may use these tokens: {number} {gw_number} {message} {reference}'),
  );
  $form['sms_devel_virtualgw_settings']['sms_devel_virtualgw_receipts_enabled'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable receipts'),
    '#default_value' => variable_get('sms_devel_virtualgw_receipts_enabled', FALSE),
    '#description' => t('If enabled then the gateway will provide a message receipt through sms_receipt()'),
  );
  $form['sms_devel_virtualgw_settings']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
    '#submit' => array('sms_devel_virtualgw_form_save_settings'),
  );

  $form['sms_devel_virtualgw_send'] = array(
    '#type' => 'fieldset',
    '#title' => t('Send a message from the gateway to SMS Framework'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['sms_devel_virtualgw_send']['sms_devel_virtualgw_from'] = array(
    '#type' => 'textfield',
    '#title' => check_plain(t('From ($number)')),
    '#size' => 30,
  );
  $form['sms_devel_virtualgw_send']['sms_devel_virtualgw_to'] = array(
    '#type' => 'textfield',
    '#title' => check_plain(t('To ($options[\'gw_number\'])')),
    '#size' => 30,
  );
  $form['sms_devel_virtualgw_send']['sms_devel_virtualgw_message'] = array(
    '#type' => 'textarea',
    '#title' => check_plain(t('Message ($message)')),
    '#rows' => 4,
    '#cols' => 40,
    '#resizable' => FALSE,
  );
  $form['sms_devel_virtualgw_send']['send'] = array(
    '#type' => 'button',
    '#value' => t('Send'),
    // '#ahah' => array(
      // 'page' => 'admin/smsframework/devel/virtualgw/send',
    '#ajax' => array(
      'callback' => 'sms_devel_virtualgw_send', // TODO Make sure this is equivalent to the lines above.
      // 'event'   => 'mousedown',
      // 'method'  => 'replace',
      // 'wrapper' => 'logfield',
    ),
    // onclick="sendSmsMessage();"
  );

  $form['sms_devel_virtualgw_log'] = array(
    '#type' => 'fieldset',
    '#title' => t('Activity log'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  $form['sms_devel_virtualgw_log']['sms_devel_virtualgw_logfield_refresh'] = array(
    '#type' => 'checkbox',
    '#title' => t('Refresh the logfield'),
    '#default_value' => (variable_get('sms_devel_virtualgw_logfield_refresh', 1)) ? 1 : 0,
    // onchange="toggleRefresh(this.checked);"
  );
  $form['sms_devel_virtualgw_log']['sms_devel_virtualgw_logfield_showsent'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show sent messages'),
    '#default_value' => (variable_get('sms_devel_virtualgw_logfield_showsent', 1)) ? 1 : 0,
  );
  $form['sms_devel_virtualgw_log']['sms_devel_virtualgw_logfield_showreceived'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show received messages'),
    '#default_value' => (variable_get('sms_devel_virtualgw_logfield_showreceived', 1)) ? 1 : 0,
  );
  $form['sms_devel_virtualgw_log']['sms_devel_virtualgw_logfield_showreceipts'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show message receipts'),
    '#default_value' => (variable_get('sms_devel_virtualgw_logfield_showreceipts', 1)) ? 1 : 0,
  );
  $form['sms_devel_virtualgw_log']['sms_devel_virtualgw_logfield_lines'] = array(
    '#type' => 'textfield',
    '#title' => t('Number of recent activity records to pull'),
    '#size' => 4,
  );
  $form['sms_devel_virtualgw_log']['sms_devel_virtualgw_logfield_refreshes'] = array(
    '#type' => 'item',
    '#title' => t('Refresh count'),
    '#value' => t(''),
  );
  $form['sms_devel_virtualgw_log']['sms_devel_virtualgw_logfield'] = array(
    '#type' => 'textarea',
    '#title' => t('Virtual gateway activity'),
    '#rows' => 20,
    '#cols' => 60,
    '#resizable' => TRUE,
    '#prefix' => '<div id="logfield">',
    '#value' => 'Sorry, this feature is not finished yet.',
    '#suffix' => '</div>',
  );
  $form['sms_devel_virtualgw_log']['get'] = array(
    '#type' => 'button',
    '#value' => t('Get activity'),
    // '#ahah' => array(
      // 'path' => 'admin/smsframework/devel/virtualgw/getactivity',
    '#ajax' => array(
      'callback' => 'sms_devel_virtualgw_js_getactivity', // TODO Make sure this is equivalent to the lines above.
      // 'event'   => 'mousedown',
      'method' => 'replace',
      'wrapper' => 'logfield',
    ),
    // onclick="sendSmsMessage();"
  );

  return $form;
}


/**
 * Submit handler for sms_devel_virtualgw_form().
 *
 * @see sms_devel_virtualgw_form()
 */
function sms_devel_virtualgw_form_save_settings($form, &$form_state) {
  variable_set('sms_devel_virtualgw_autoreply_enabled',
    $form_state['values']['sms_devel_virtualgw_autoreply_enabled']);
  variable_set('sms_devel_virtualgw_autoreply_format',
    $form_state['values']['sms_devel_virtualgw_autoreply_format']);
  variable_set('sms_devel_virtualgw_receipts_enabled',
    $form_state['values']['sms_devel_virtualgw_receipts_enabled']);
}


/**
 * Admin View page
 *
 * @return
 *   HTML content string.
 */
/*
 function sms_devel_virtualgw_admin_view() {
 $content = views_embed_view('sms_devel_virtualgw', $display_id = 'default');
 return $content;
 }
 */
