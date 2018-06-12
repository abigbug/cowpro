<?php

/**
 * @file
 * The admin custodian functions.
 */

/**
 * Select default custodian provider form.
 */
function custodian_settings_form($form, &$form_state) {
  $providers = custodian_providers();

  foreach ($providers as $identifier => $provider) {
    //$active = ($identifier == variable_get('custodian_default_provider', 'cash_pooling'));
    //$form[$provider['name']]['id'] = array('#markup' => $identifier);
    if ( isset($provider['configure form'] ) and ( function_exists($provider['configure form'] ))) {
      $config = l(t('configure'), 'admin/cowpro/config_custodian/' . $identifier);
    }
    else {
      $config = t('无配置项');
    }
    $options[$identifier] = $provider['name'] . "...($config)";
  }

  $form['custodian_default_provider'] = array(
    '#type' => 'radios',
    '#options' => $options,
    '#default_value' => variable_get('custodian_default_provider', 'cash_pooling'),
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('设为默认托管服务商'),
  );

  return $form;
}

/**
 * Form submission handler for custodian_admin_default_form().
 *
 * @see custodian_admin_default_form()
 */
function custodian_settings_form_submit($form, &$form_state) {
  // Process form submission to set the default provider
  if ($form_state['values']['custodian_default_provider']) {
    drupal_set_message('已更新默认资金托管服务商');
    variable_set('custodian_default_provider', $form_state['values']['custodian_default_provider']);
  }
}

/**
 * Returns HTML for the admin default provider form.
 *
 * @param $form
 *  An form array.
 *
 * @ingroup themeable
 */
/*
function theme_custodian_admin_default_form($variables) {
  $form = $variables['form'];
  $rows = array();
  foreach ($form as $name => $element) {
    if (is_array($element) and isset($element['id']) and is_array($element['id'])) {
      $rows[] = array(
        drupal_render($form['default'][$element['id']['#markup']]),
        check_plain($name),
        $element['configure']['#markup'],
      );
      unset($form[$name]);
    }
  }
  $header = array(t('Default'), t('Name'), array(
      'data' => t('Operations'),
      'colspan' => 1,
    ));
  $output = '';
  $output .= theme('table', array('header' => $header, 'rows' => $rows));
  $output .= drupal_render_children($form);

  return $output;
}
*/

/**
 * Form builder for the custodian provider configuration form.
 *
 * @param @provider_id
 *  The ID of the custodian provider.
 *
 * @see custodian_admin_provider_form_validate()
 * @see custodian_admin_provider_form_submit()
 */
function custodian_admin_provider_form($form, &$form_state, $provider_id) {
  $provider = custodian_providers('provider', $provider_id);
  if ($provider && function_exists($provider['configure form'])) {
    drupal_set_title(t('@provider 配置', array('@provider' => $provider['name'])), PASS_THROUGH);
    $form = $provider['configure form']($form, $form_state);

    $form['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Save'),
    );
    $form['provider'] = array(
      '#type' => 'value',
      '#value' => $provider,
    );

    return $form;
  }
  drupal_not_found();
  exit();
}

/**
 * Form validation handler for custodian_admin_provider_form().
 *
 * @see custodian_admin_provider_form()
 * @see custodian_admin_provider_form_submit()
 */
function custodian_admin_provider_form_validate($form, &$form_state) {
  // Pass validation to provider
  $function = $form_state['values']['provider']['configure form'] . '_validate';
  if (function_exists($function)) {
    $function($form, $form_state);
  }
}

/**
 * Form submission handler for custodian_admin_provider_form().
 *
 * @see custodian_admin_provider_form()
 * @see custodian_admin_provider_form_validate()
 */
function custodian_admin_provider_form_submit($form, &$form_state) {
  $function = $form_state['values']['provider']['configure form'] . '_submit';
  if (function_exists($function)) {
    $function($form, $form_state);
  }
	drupal_set_message('资金托管服务商配置项已保存。');
  $form_state['redirect'] = 'admin/cowpro/config_custodian';
}
