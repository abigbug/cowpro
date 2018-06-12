<?php

/**
 * @file
 * Provides some user attributes as ThemeKey properties.
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
 * Provides additional properties for module ThemeKey:
 * - user:hostname
 * - user:language
 * - user:name
 * - user:uid
 *
 * @return
 *   array of themekey properties and mapping functions
 */
function themekey_user_themekey_properties() {
  // Attributes for properties
  $attributes = array();
  $attributes['user:hostname'] = array(
    'description' => t("User: Hostname - The user hostname property which is the IP address of client machine, adjusted for reverse proxy. Text from Drupal bootstrap.inc:
      If Drupal is behind a reverse proxy, we use the X-Forwarded-For header instead of \$_SERVER['REMOTE_ADDR'], which would be the IP address of the proxy server, and not the client's."),
    'validator' => 'themekey_validator_http_host',
    'page cache' => THEMEKEY_PAGECACHE_UNSUPPORTED,
  );
  $attributes['user:language'] = array(
    'description' => t('User: Language - The language the user has set in the settings of his profile page.
      Format is the language code (for example "en" for English or "de" for German) that can be found on !link.',
      array('!link' => l(t('!path', array('!path' => 'admin/config/regional/language/overview')), 'admin/config/regional/language/overview'))),
    'validator' => 'themekey_validator_language',
    'page cache' => THEMEKEY_PAGECACHE_SUPPORTED,
  );
  $attributes['user:name'] = array(
    'description' => t('User: Name - The username of the user. See !link for your users.', array('!link' => l(t('!path', array('!path' => 'admin/people/people')), 'admin/people/people'))),
    'page cache' => THEMEKEY_PAGECACHE_SUPPORTED,
  );
  $attributes['user:uid'] = array(
    'description' => t('User: ID - The id of the user (uid). The user id can be found in the URL of the users profile page, "user/23" or "user/23/edit" (23 = uid). See !link for your users.',
      array('!link' => l(t('!path', array('!path' => 'admin/people/people')), 'admin/people/people'))),
    'validator' => 'themekey_validator_ctype_digit',
    'page cache' => THEMEKEY_PAGECACHE_SUPPORTED,
  );
  $attributes['user:role'] = array(
    'description' => t("User: Role - Defined user roles (examples: 'anonymous user', 'authenticated user')"),
    'validator' => 'themekey_validator_role',
    'page cache' => THEMEKEY_PAGECACHE_SUPPORTED,
  );

  // Mapping functions
  $maps = array();

  $maps[] = array(
    'src' => 'profile:uid',
    'dst' => 'themekey_ui:author_triggers_theme',
    'callback' => 'themekey_user_profile2theme',
  );

  return array('attributes' => $attributes, 'maps' => $maps);
}

/**
 * Implements hook_themekey_paths().
 */
function themekey_user_themekey_paths() {
  $paths = array();

  $paths[] = array('path' => 'user/#profile:uid');
  $paths[] = array('path' => 'user/#profile:uid/edit');

  return $paths;
}


/**
 * Implements hook_themekey_global().
 */
function themekey_user_themekey_global() {
  global $user;

  $parameters = array();

  $parameters['user:hostname'] = !empty($user->hostname) ? $user->hostname : NULL;
  $parameters['user:language'] = !empty($user->language) ? $user->language : NULL;
  $parameters['user:name'] = !empty($user->name) ? $user->name : NULL;
  $parameters['user:uid'] = $user->uid;
  $parameters['user:role'] = $user->roles;

  if ('user' == themekey_get_q() && user_is_logged_in()) {
    // required by themekey_ui:author_triggers_theme
    $parameters['profile:uid'] = $user->uid; // a user watches his own profile
  }

  return $parameters;
}

/**
 * Implements hook_themekey_ui_author_theme_selected().
 */
function themekey_user_themekey_ui_author_theme_selected($uid, $theme) {
  global $base_root;

  $cid = $base_root . '/user/' . $uid;

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
 *   the user's id of the profile, current value of ThemeKey property profile:uid
 *
 * @return
 *   string "static" if global custom theme has been set
 *   or NULL if no theme has been assigned to the contact form
 */
function themekey_user_profile2theme($uid) {
  return themekey_ui_author2theme($uid);
}
