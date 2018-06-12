<?php

/**
 * Implements hook_themekey_properties().
 */
function themekey_themekey_simpletest_themekey_properties() {
  // Attributes of properties
  $attributes = array();
  $attributes['themekey_simpletest:global_property_test'] = array(
    'description' => t('Simpletest: global property test - value is 1.'),
    'validator' => 'themekey_validator_ctype_digit',
    'page cache' => THEMEKEY_PAGECACHE_UNSUPPORTED,
  );
  $attributes['themekey_simpletest:custom_theme_alter_test'] = array(
    'description' => t('Simpletest: gcustom theme alter test - value is 1.'),
    'validator' => 'themekey_validator_ctype_digit',
    'page cache' => THEMEKEY_PAGECACHE_UNSUPPORTED,
  );

  $maps = array();

  return array('attributes' => $attributes, 'maps' => $maps);
}

/**
 * Implements hook_themekey_global().
 */
function themekey_themekey_simpletest_themekey_global() {
  $parameters = array();
  $parameters['themekey_simpletest:global_property_test'] = 1;
  $parameters['themekey_simpletest:custom_theme_alter_test'] = 1;

  return $parameters;
}

/**
 * Implements hook_themekey_custom_theme_alter().
 */
function themekey_themekey_simpletest_themekey_custom_theme_alter(&$custom_theme, $rules_matched) {
  $rule = reset($rules_matched);
  if ('themekey_simpletest:custom_theme_alter_test' == $rule->property) {
    $custom_theme = 'seven';
  }
}
