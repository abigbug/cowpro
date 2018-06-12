<?php

/**
 * @file
 * Provides some og attributes as ThemeKey properties.
 *
 * @author Markus Kalkbrenner | bio.logis GmbH
 *   @see http://drupal.org/user/124705
 *
 * @author daggerhart
 *   @see http://drupal.org/user/167806
 */

/**
 * Implements hook_themekey_properties().
 *
 * Provides additional properties for module ThemeKey:
 * - overlay:mode
 *
 * @return
 * array of themekey properties and mapping functions
 */
function themekey_overlay_themekey_properties() {
  // Attributes for properties
  $attributes = array();
  $attributes['overlay:mode'] = array(
    'description' => t("Overlay: Mode - The current overlay mode used to show the content. Note: If you add such a rule, the mode 'none' will not work anymore. That means that different modules won't be able to turn off overlay manually. That's not an issue for drupal core. See !link for details.",
      array('!link' => l(t('function overlay_set_mode documentation'), 'https://api.drupal.org/api/drupal/modules!overlay!overlay.module/function/overlay_set_mode/7'))),
    'validator' => 'themekey_validator_overlay_mode',
    'page cache' => THEMEKEY_PAGECACHE_UNSUPPORTED,
  );

  // Mapping functions
  $maps = array();
  $maps[] = array('src' => 'system:dummy',
                  'dst' => 'overlay:mode',
                  'callback' => 'themekey_overlay_dummy2mode');

  return array('attributes' => $attributes, 'maps' => $maps);
}

/**
 * ThemeKey mapping function to set a
 * ThemeKey property's value (destination)
 * with the aid of another ThemeKey property (source).
 *
 * src: system:dummy
 * dst: overlay:mode
 *
 * @param $nid
 *   a node id
 *
 * @return
 *   string
 */
function themekey_overlay_dummy2mode() {
  // hook_init() is called after hook_custom_theme()
  if (module_exists('locale')) {
    // overlay_init() LOCALE_LANGUAGE_NEGOTIATION_URL_PREFIX which is defined
    // in locale.inc that gets loaded by locale_init().
    include_once DRUPAL_ROOT . '/includes/locale.inc';
  }
  overlay_init();
  return overlay_get_mode();
}
