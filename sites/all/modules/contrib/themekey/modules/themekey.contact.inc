<?php

/**
 * Implements hook_themekey_properties().
 *
 * Provides additional properties for the ThemeKey module:
 *   themekey_ui:node_triggers_theme
 *   themekey_ui:author_triggers_theme
 *
 * @return
 *   array of themekey properties
 */
function themekey_contact_themekey_properties() {

  // Attributes for properties
  $attributes = array();

  // Mapping functions
  $maps = array();

  $maps[] = array(
    'src' => 'contact:uid',
    'dst' => 'themekey_ui:author_triggers_theme',
    'callback' => 'themekey_contact_uid2theme',
  );

  return array('attributes' => $attributes, 'maps' => $maps);
}

/**
 * Implements hook_themekey_paths().
 */
function themekey_contact_themekey_paths() {
  $paths = array();

  $paths[] = array('path' => 'user/#contact:uid/contact');

  return $paths;
}

/**
 * Implements hook_themekey_ui_author_theme_selected().
 */
function themekey_contact_themekey_ui_author_theme_selected($uid, $theme) {
  global $base_root;

  $cid = $base_root . '/contact/' . $uid;

  cache_clear_all($cid, 'cache_page');
  cache_clear_all($cid . '/', 'cache_page', TRUE);
}

/**
 * This function implements the interface of a ThemeKey
 * mapping function but doesn't set a ThemeKey property's
 * value. It sets the Drupal static themekey_custom_theme
 * which will cause ThemeKey to use this theme.
 *
 * @param $uid
 *   the user's id to be contacted, current value of ThemeKey property contact:uid
 *
 * @return
 *   string "static" if global custom theme has been set
 *   or NULL if no theme has been assigned to the contact form
 */
function themekey_contact_uid2theme($uid) {
  return themekey_ui_author2theme($uid);
}
