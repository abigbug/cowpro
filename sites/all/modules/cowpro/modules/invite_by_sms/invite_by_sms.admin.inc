<?php

/**
 * Settings form for Invite By SMS
 *
 * @return array
 */
function invite_by_sms_settings_form() {
  $form['invite_default_sms_body'] = array(
    '#type' => 'textarea',
    '#title' => t('Mail template'),
    '#default_value' => variable_get('invite_default_sms_body', ''),
    '#required' => TRUE,
    '#description' => t('Use the syntax [token] if you want to insert a replacement pattern.'),
  );

  $form['invite_default_replace_tokens'] = array(
    '#type' => 'checkbox',
    '#title' => t('Apply token replacements'),
    '#default_value' => variable_get('invite_default_replace_tokens', TRUE),
    '#description' => t('Whether token replacement patterns should be applied.'),
  );

  if (module_exists('token')) {
    $form['token_help'] = array(
      '#title' => t('Replacement patterns'),
      '#type' => 'fieldset',
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
    );

    $form['token_help']['help'] = array(
      '#markup' => theme('token_tree', array('token_types' => array('user', 'profile', 'invite'))),
    );
  }

  return system_settings_form($form);

}
