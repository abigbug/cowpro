<?php

/**
 * @file
 * Integrates Print module's paths into ThemeKey.
 *
 * @author Markus Kalkbrenner | bio.logis GmbH
 *   @see http://drupal.org/user/124705
 */


/**
 * Implements hook_themekey_paths().
 */
function themekey_print_themekey_paths() {
  $paths = array();

  $paths[] = array('path' => 'print/#node:nid');
  $paths[] = array('path' => 'printpdf/#node:nid');
  $paths[] = array('path' => 'printmail/#node:nid');

  return $paths;
}
