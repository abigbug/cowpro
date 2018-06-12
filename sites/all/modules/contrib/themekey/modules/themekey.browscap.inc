<?php

/**
 * @file
 * Provides some browsecap attributes as ThemeKey properties.
 *
 * @author Markus Kalkbrenner | bio.logis GmbH
 *   @see http://drupal.org/user/124705
 */


/**
 * Implements hook_themekey_properties().
 *
 * Provides additional properties for module ThemeKey:
 * - browscap:comment
 * - browscap:browser
 * - browscap:version
 * - browscap:majorver
 * - browscap:minorver
 * - browscap:platform
 * - browscap:platform_version
 * - browscap:ismobiledevice
 * - browscap:istablet
 * - browscap:issyndicationreader
 * - browscap:crawler
 * - browscap:cssversion
 * - browscap:parent
 * - browscap:useragent
 * - browscap:browser_name_pattern
 *
 * @return
 *   array of themekey properties and mapping functions
 */
function themekey_browscap_themekey_properties() {
  // Attributes for properties
  $attributes = array();
  $attributes['browscap:comment'] = array(
    'description' => t("Browscap: Comment"),
    'page cache' => THEMEKEY_PAGECACHE_UNSUPPORTED,
  );
  $attributes['browscap:browser'] = array(
    'description' => t("Browscap: Browser"),
    'page cache' => THEMEKEY_PAGECACHE_UNSUPPORTED,
  );
  $attributes['browscap:version'] = array(
    'description' => t("Browscap: Version"),
    'page cache' => THEMEKEY_PAGECACHE_UNSUPPORTED,
  );
  $attributes['browscap:majorver'] = array(
    'description' => t("Browscap: Major Version"),
    'page cache' => THEMEKEY_PAGECACHE_UNSUPPORTED,
  );
  $attributes['browscap:minorver'] = array(
    'description' => t("Browscap: Minor Version"),
    'page cache' => THEMEKEY_PAGECACHE_UNSUPPORTED,
  );
  $attributes['browscap:platform'] = array(
    'description' => t("Browscap: Platform"),
    'page cache' => THEMEKEY_PAGECACHE_UNSUPPORTED,
  );
  $attributes['browscap:platform_version'] = array(
    'description' => t("Browscap: Platform Version"),
    'page cache' => THEMEKEY_PAGECACHE_UNSUPPORTED,
  );
  $attributes['browscap:ismobiledevice'] = array(
    'description' => t("Browscap: Is mobile device"),
    'validator' => 'themekey_validator_string_boolean',
    'page cache' => THEMEKEY_PAGECACHE_UNSUPPORTED,
  );
  $attributes['browscap:istablet'] = array(
    'description' => t("Browscap: Is tablet"),
    'validator' => 'themekey_validator_string_boolean',
    'page cache' => THEMEKEY_PAGECACHE_UNSUPPORTED,
  );
  $attributes['browscap:issyndicationreader'] = array(
    'description' => t("Browscap: Is syndication reader"),
    'validator' => 'themekey_validator_string_boolean',
    'page cache' => THEMEKEY_PAGECACHE_UNSUPPORTED,
  );
  $attributes['browscap:crawler'] = array(
    'description' => t("Browscap: Crawler"),
    'validator' => 'themekey_validator_string_boolean',
    'page cache' => THEMEKEY_PAGECACHE_UNSUPPORTED,
  );
  $attributes['browscap:cssversion'] = array(
    'description' => t("Browscap: CSS Version"),
    'validator' => 'themekey_validator_ctype_digit',
    'page cache' => THEMEKEY_PAGECACHE_UNSUPPORTED,
  );
  $attributes['browscap:parent'] = array(
    'description' => t("Browscap: Parent"),
    'page cache' => THEMEKEY_PAGECACHE_UNSUPPORTED,
  );
  $attributes['browscap:useragent'] = array(
    'description' => t("Browscap: User Agent"),
    'page cache' => THEMEKEY_PAGECACHE_UNSUPPORTED,
  );
  $attributes['browscap:browser_name_pattern'] = array(
    'description' => t("Browscap: Browser Name Pattern"),
    'page cache' => THEMEKEY_PAGECACHE_UNSUPPORTED,
  );

  return array('attributes' => $attributes);
}


/**
 * Implements hook_themekey_global().
 */
function themekey_browscap_themekey_global() {
  $browser = browscap_get_browser();

  $parameters = array();
  $parameters['browscap:comment'] = array_key_exists('comment', $browser) ? $browser['comment'] : NULL;
  $parameters['browscap:browser'] = array_key_exists('browser', $browser) ? $browser['browser'] : NULL;
  $parameters['browscap:version'] = array_key_exists('version', $browser) ? $browser['version'] : NULL;
  $parameters['browscap:majorver'] = array_key_exists('majorver', $browser) ? $browser['majorver'] : NULL;
  $parameters['browscap:minorver'] = array_key_exists('minorver', $browser) ? $browser['minorver'] : NULL;
  $parameters['browscap:platform'] = array_key_exists('platform', $browser) ? $browser['platform'] : NULL;
  $parameters['browscap:platform_version'] = array_key_exists('platform_version', $browser) ? $browser['platform_version'] : NULL;
  $parameters['browscap:ismobiledevice'] = array_key_exists('ismobiledevice', $browser) ? $browser['ismobiledevice'] : NULL;
  $parameters['browscap:istablet'] = array_key_exists('istablet', $browser) ? $browser['istablet'] : NULL;
  $parameters['browscap:issyndicationreader'] = array_key_exists('issyndicationreader', $browser) ? $browser['issyndicationreader'] : NULL;
  $parameters['browscap:crawler'] = array_key_exists('crawler', $browser) ? $browser['crawler'] : NULL;
  $parameters['browscap:cssversion'] = array_key_exists('cssversion', $browser) ? $browser['cssversion'] : NULL;
  $parameters['browscap:parent'] = array_key_exists('parent', $browser) ? $browser['parent'] : NULL;
  $parameters['browscap:useragent'] = array_key_exists('useragent', $browser) ? $browser['useragent'] : NULL;
  $parameters['browscap:browser_name_pattern'] = array_key_exists('browser_name_pattern', $browser) ? $browser['browser_name_pattern'] : NULL;

  foreach ($parameters as $key => $value) {
    if (strpos($key, 'browscap:is') === 0 && is_numeric($value)) {
      // In some setups browsecap returns integers instead of strings. We have
      // to convert them back to strings to keep rules exportable.
      // See https://drupal.org/node/2118987
      $parameters[$key] = $value ? 'true' : 'false';
    }
  }

  return $parameters;
}
