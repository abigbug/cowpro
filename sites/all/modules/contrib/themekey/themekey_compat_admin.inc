<?php

/**
 * @file
 *
 * @author Markus Kalkbrenner | bio.logis GmbH
 *   @see http://drupal.org/user/124705
 */


/**
 * Form builder for the form to enable modules for ThemeKey compatibility mode.
 *
 * @ingroup forms
 */
function themekey_compat_settings_form() {
  $form = array();

  $modules = module_implements('custom_theme');
  $modules = array_diff($modules, array('themekey'));
  $modules = array_merge($modules, variable_get('themekey_compat_modules_enabled', array()));
  asort($modules);

  if (!empty($modules)) {
    $modules_list = system_list('module_enabled');
    $options = array();
    foreach ($modules as $module) {
      $name = $module;
      if (isset($modules_list[$module]->info) && !empty($modules_list[$module]->info['name'])) {
        $name = $modules_list[$module]->info['name'] . ' (' . $modules_list[$module]->info['description'] . ')';
      }
      if ('system' == $module) {
        $name = preg_replace("/\)$/", ' ' . t('Provides the "Administration theme".') . ')', $name);
      }
      $options[$module] = $name;
    }

    $form['themekey_compat']['modules_enabled'] = array(
      '#type' => 'fieldset',
      '#title' => t('Modules'),
      '#collapsible' => TRUE,
      '#collapsed' => FALSE,
    );

    $form['themekey_compat']['modules_enabled']['themekey_compat_modules_enabled'] = array(
      '#type' => 'checkboxes',
      '#title' => t('Modules to become part of the Theme Switching Rule Chain'),
      '#description' => t("Optionally disable the theme switching capability of core and additional modules. Their theme switching capabilities will become part of ThemeKey's theme switching rule chain instead and therefor configurable."),
      '#default_value' => variable_get('themekey_compat_modules_enabled', array()),
      '#options' => $options,
    );

    $form['themekey_compat']['modules_no_default_theme'] = array(
      '#type' => 'fieldset',
      '#title' => t('No Default Theme'),
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
    );

    $form['themekey_compat']['modules_no_default_theme']['themekey_compat_modules_no_default_theme'] = array(
      '#type' => 'checkboxes',
      '#title' => t('Ignore the theme decision of these modules if they select the default theme'),
      '#default_value' => variable_get('themekey_compat_modules_no_default_theme', array()),
      '#options' => $options,
    );

    $form['buttons']['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Save configuration'),
    );
  }
  else {
    $form['themekey_compat']['no_module'] = array(
      '#type' => 'markup',
      '#value' => t('No different theme switching module installed.'),
    );
  }

  return $form;
}

/**
 * Form submission handler for themekey_compat_settings_form().
 *
 * @see themekey_compat_settings_form()
 */
function themekey_compat_settings_form_submit($form, &$form_state) {
  $modules_enabled = array();
  $modules_no_default_theme = array();

  foreach ($form_state['values']['themekey_compat_modules_enabled'] as $module => $enabled) {
    if ($enabled) {
      $modules_enabled[] = $module;
    }
  }

  variable_set('themekey_compat_modules_enabled', $modules_enabled);

  if (!empty($modules_enabled)) {
    drupal_set_message(filter_xss(t('You integrated some modules in Theme Switching Rule Chain. !link',
      array('!link' => l(t('Review the Theme Switching Rule Chain.'), 'admin/config/user-interface/themekey/properties')))),
      'warning');
  }

  foreach ($form_state['values']['themekey_compat_modules_no_default_theme'] as $module => $enabled) {
    if ($enabled) {
      $modules_no_default_theme[] = $module;
    }
  }

  variable_set('themekey_compat_modules_no_default_theme', $modules_no_default_theme);

  module_load_include('inc', 'themekey', 'themekey_build');

  themekey_rebuild();

  foreach ($form_state['values']['themekey_compat_modules_enabled'] as $module => $enabled) {
    themekey_update_static_rule('themekey_compat:module_' . $module . '_triggers_theme', $enabled);
  }

  cache_clear_all('module_implements', 'cache_bootstrap');

  drupal_set_message(t('The configuration options have been saved.'));
}
