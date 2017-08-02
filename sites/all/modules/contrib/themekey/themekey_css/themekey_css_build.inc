<?php

/**
 * @file
 * The functions in this file are the back end of ThemeKey which should be
 * used only if you configure something, but not when ThemeKey switches themes.
 *
 * @author Markus Kalkbrenner | bio.logis GmbH
 *   @see http://drupal.org/user/124705
 */


/**
 * Creates options array for a theme select box.
 *
 * Example:
 *   $form['theme'] = array(
 *     '#type' => 'select',
 *     '#title' => t('Theme'),
 *     '#options' => themekey_theme_options(),
 *   );
 *
 * @param $default
 *   Boolean to indicate if options array should contain
 *   'System default' theme. Default is TRUE.
 * @param $admin
 *   Boolean to indicate if options array should contain
 *   'Administration theme'. Default is FALSE.
 *
 * @return
 *   options array for a theme select box
 */
function themekey_css_options() {
  return variable_get('themekey_css_files', array());
}


/**
 * Loads all ThemeKey Rules from the database.
 * Therefore, it uses recursion to build the rule chains.
 *
 * @return
 *   sorted array containing all ThemeKey rules
 */
function themekey_css_load_rules() {
  return themekey_abstract_load_rules('themekey_css_rules');
}


/**
 * Stores ThemeKey rules in database.
 * It creates a new dataset or updates an existing one.
 *
 * @param $item
 *   reference to an associative array
 *   containing a ThemeKey rule structure:
 *   - id
 *   - property
 *   - operator
 *   - value
 *   - weight
 *   - theme
 *   - enabled
 *   - wildcards
 *   - parent
 *
 * @param $module
 *   name of the module that sets the item
 *
 * @throws ThemeKeyRuleConflictException
 */
function themekey_css_rule_set(&$item, $module = 'themekey_css') {
  themekey_abstract_rule_set('themekey_css_rules', $item, $module);
}


/**
 * Deletes a ThemeKey rule from database.
 *
 * @param $id
 *   id of the rule to be deleted from database
 *
 * @throws ThemeKeyRuleDeletionException
 */
function themekey_css_rule_del($id) {
  return themekey_abstract_rule_del('themekey_css_rules', $id);
}

/**
 * Disables a ThemeKey rule and all children.
 *
 * @param $id
 *   id of the rule to be ddisabled
 */
function themekey_css_rule_disable($id) {
  themekey_abstract_rule_disable('themekey_css_rules', $id);
}

function themekey_css_scan() {
  // Get current list of items.
  if (!function_exists('file_scan_directory')) {
    require_once DRUPAL_ROOT . '/includes/file.inc';
  }

  $files = array();
  foreach (file_scan_directory(DRUPAL_ROOT, '@\.css$@i', array('recurse' => TRUE, 'nomask' => '/(\.\.?|git|simpletest)$/')) as $file) {
    $path = str_replace(DRUPAL_ROOT . '/', '', $file->uri);
    if (themekey_check_css_exists($path)) {
      $files[$path] = $path;
    }
  }

  ksort($files);
  variable_set('themekey_css_files', $files);
}