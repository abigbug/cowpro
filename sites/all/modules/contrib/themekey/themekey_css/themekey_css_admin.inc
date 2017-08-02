<?php

/**
 * @file
 * Contains all form manipulations required by ThemeKey CSS.
 *
 * @author Markus Kalkbrenner | bio.logis GmbH
 *   @see http://drupal.org/user/124705
 */

require_once DRUPAL_ROOT . '/' . drupal_get_path('module', 'themekey_css') . '/themekey_css_build.inc';
require_once DRUPAL_ROOT . '/' . drupal_get_path('module', 'themekey') . '/themekey_admin.inc';


/**
 * Form builder for the rule chain.
 *
 * The form will not be validated. All changes will be saved immediately.
 * Validation will happen when the form displays the stored configuration.
 * Otherwise all the drag'n'drop stuff will not work.
 *
 * @see themekey_form_alter()
 * @see themekey_rule_chain_form_submit()
 * @see themekey_rule_chain_form_set_error()
 *
 * @ingroup forms
 */
function themekey_css_rule_chain_form($form, &$form_state) {
  return themekey_abstract_rule_chain_form($form, $form_state, array(
    'load_rules_callback' => 'themekey_css_load_rules',
    'themes' => themekey_css_options(),
    'rule_delete_path' => 'admin/config/user-interface/themekey/css/delete/',
  ));
}

/**
 * Validation of
 * @see themekey_rule_chain_form()
 */
function themekey_css_rule_chain_form_validate(&$form, $form_state) {
  themekey_abstract_rule_chain_form_validate($form, $form_state, array(
    'check_enabled_callback' => 'themekey_check_css_exists',
    'not_enabled_message' => t('CSS file does not exist.'),
  ));
}

/**
 * Form submission handler for themekey_rule_chain_form().
 *
 * @see themekey_rule_chain_form()
 */
function themekey_css_rule_chain_form_submit($form, &$form_state) {
  themekey_abstract_rule_chain_form_submit($form, $form_state, array(
    'rule_set_callback' => 'themekey_css_rule_set',
  ));
}


/**
 * Menu callback -- ask for confirmation of ThemeKey rule deletion
 */
function themekey_css_admin_delete_rule_confirm($form, &$form_state, $arg, $themekey_property_id) {
  $form['themekey_property_id'] = array(
    '#type' => 'value',
    '#value' => $themekey_property_id,
  );

  $title = themekey_css_format_rule_as_string($themekey_property_id);

  return confirm_form($form,
    t('Are you sure you want to delete the ThemeKey rule, %title?', array('%title' => $title)),
    'admin/config/user-interface/themekey/css',
    t('This action cannot be undone.'),
    t('Delete'),
    t('Cancel')
  );
}


/**
 * Execute ThemeKey rule deletion
 */
function themekey_css_admin_delete_rule_confirm_submit($form, &$form_state) {
  if ($form_state['values']['confirm']) {
    themekey_css_rule_del($form_state['values']['themekey_property_id']);
  }

  $form_state['redirect'] = 'admin/config/user-interface/themekey/css';
}

/**
 * Themes themekey_css_rule_chain_form() and adds drag'n'drop features.
 *
 * @ingroup themeable
 */
function theme_themekey_css_rule_chain_form($variables) {
  return theme_themekey_abstract_rule_chain_form($variables, array(
    'header' => array(
      t('Adding CSS Rule Chain'),
      t('CSS'),
      t('Enabled'),
      t('Operation'),
      t('Parent'),
      t('Weight'),
      t('Page<br />Cache'),
    )
  ));
}