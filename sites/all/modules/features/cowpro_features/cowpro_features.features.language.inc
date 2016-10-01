<?php
/**
 * @file
 * cowpro_features.features.language.inc
 */

/**
 * Implements hook_locale_default_languages().
 */
function cowpro_features_locale_default_languages() {
  $languages = array();

  // Exported language: zh-hans.
  $languages['zh-hans'] = array(
    'language' => 'zh-hans',
    'name' => 'Chinese, Simplified',
    'native' => '简体中文',
    'direction' => 0,
    'enabled' => 1,
    'plurals' => 2,
    'formula' => '($n!=1)',
    'domain' => '',
    'prefix' => 'zh-hans',
    'weight' => 0,
  );
  return $languages;
}
