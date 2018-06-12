<?php

/**
 * @file
 * Provides mobile_detect rules as ThemeKey properties.
 *
 * @author Markus Kalkbrenner | bio.logis GmbH
 *   @see http://drupal.org/user/124705
 */


/**
 * Implements hook_themekey_properties().
 *
 * Provides additional properties for the ThemeKey module:
 * - mobile_detect:is...
 *
 * @return
 *   array of themekey properties and mapping functions
 */
function themekey_mobile_detect_themekey_properties() {
  $properties = array('attributes' => array(), 'maps' => array());

  if (!module_exists('mobile_detect_api')) {
    if ($mobile_detect = mobile_detect_get_object()) {
      require_once DRUPAL_ROOT . '/' . drupal_get_path('module', 'themekey') . '/modules/themekey.mobile_detect_api.inc';

      $properties = themekey_mobile_detect_api_themekey_properties_helper($mobile_detect);

      foreach ($properties['maps'] as &$map) {
        $map['callback'] = 'themekey_mobile_detect_dummy2rule';
      }
    }
  }

  return $properties;
}


/**
 * ThemeKey mapping function to set a
 * ThemeKey property's value (destination)
 * with the aid of another ThemeKey property (source).
 *
 * src: system:dummy
 * dst: mobile_detect:is...
 *
 * @param $nid
 *   a node id
 * @param $args
 *   array, keys required:
 *    - 'method'
 *
 * @return
 *   string 'true' or 'false'
 *   or NULL if mobile_detect is not available
 */
function themekey_mobile_detect_dummy2rule($nid, $args) {
  if ($mobile_detect = mobile_detect_get_object()) {
    return ($mobile_detect->{$args['method']}()) ? 'true' : 'false';
  }

  return NULL;
}
