<?php

/**
 * @file
 * Provides some node attributes as ThemeKey properties.
 *
 * @author Markus Kalkbrenner | bio.logis GmbH
 *   @see http://drupal.org/user/124705
 *
 * @author profix898
 *   @see http://drupal.org/user/35192
 */


/**
 * Implements hook_themekey_properties().
 *
 * Provides additional properties for the ThemeKey module:
 * - locale:language
 * - locale:language_content
 * - locale:language_from_browser
 *
 * @return
 *   array of themekey properties and mapping functions
 */
function themekey_locale_themekey_properties() {
  // Attributes for properties
  $attributes = array();
  $attributes['locale:language'] = array(
    'description' => t('Locale: Language - The code of the current site language, formatted like "en" or "de" or "neutral". See !link for the codes of your enabled languages',
      array('!link' => l(t('!path', array('!path' => 'admin/config/language')), 'admin/config/language'))),
    'validator' => 'themekey_validator_language',
    'page cache' => THEMEKEY_PAGECACHE_SUPPORTED,
  );
  $attributes['locale:language_content'] = array(
    'description' => t('Locale: Language Content - The code of the current content language, formatted like "en" or "de" or "neutral". See !link for the codes of your enabled languages',
      array('!link' => l(t('!path', array('!path' => 'admin/config/language')), 'admin/config/language'))),
    'validator' => 'themekey_validator_language',
    'page cache' => THEMEKEY_PAGECACHE_SUPPORTED,
  );
  $attributes['locale:language_from_browser'] = array(
    'description' => t('Locale: Language From Browser - Identify best matching language from the Accept-language HTTP header we got.'),
    'validator' => 'themekey_validator_language',
    'page cache' => THEMEKEY_PAGECACHE_UNSUPPORTED,
  );

  $maps = array();
  $maps[] = array(
    'src' => 'system:dummy',
    'dst' => 'locale:language_from_browser',
    'callback' => 'themekey_locale_dummy2language_from_browser');

  return array('attributes' => $attributes, 'maps' => $maps);
}


/**
 * Implements hook_themekey_paths().
 */
function themekey_locale_themekey_global() {
  global $language;
  global $language_content;

  $parameters = array();

  if (empty($language->language) || LANGUAGE_NONE == $language->language) {
    $parameters['locale:language'] = 'neutral';
  }
  else {
    $parameters['locale:language'] = $language->language;
  }

  if (empty($language_content->language) || LANGUAGE_NONE == $language_content->language) {
    $parameters['locale:language_content'] = 'neutral';
  }
  else {
    $parameters['locale:language_content'] = $language->language;
  }

  return $parameters;
}

/**
 * ThemeKey mapping function to set a
 * ThemeKey property's value (destination)
 * with the aid of another ThemeKey property (source).
 *
 * src: system:dummy
 * dst: locale:language_from_browser
 *
 * @param $dummy
 *   string containing current value of ThemeKey property system:dummy
 *
 * @return
 *   The language code as string or NULL
 */
function themekey_locale_dummy2language_from_browser($dummy) {
  // This implementation is simple but too expensive to be handled by
  // themekey_locale_themekey_global() on every page request.
  $langcode = locale_language_from_browser(language_list());
  return ($langcode) ? $langcode : NULL;
}
