<?php

/**
 * @file
 *
 *
 * @see themekey.module
 *
 * @author Markus Kalkbrenner | bio.logis GmbH
 *   @see http://drupal.org/user/124705
 */


/**
 * Implements hook_themekey_disabled_paths().
 */
function themekey_admin_menu_themekey_disabled_paths() {
  return array('js/admin_menu/cache');
}
