<?php

/**
 * @file
 * Integrates Revisioning module's paths into ThemeKey.
 *
 * @author mkalkbrenner | Markus Kalkbrenner
 *   @see http://drupal.org/user/124705
 */


/**
 * Implements hook_themekey_paths().
 */
function themekey_revisioning_themekey_paths() {
  $paths = array();

  $paths[] = array('path' => 'node/#node:nid/unpublish');
  $paths[] = array('path' => 'node/#node:nid/revisions/#node:vid/view');
  $paths[] = array('path' => 'node/#node:nid/revisions/#node:vid/edit');
  $paths[] = array('path' => 'node/#node:nid/revisions/#node:vid/publish');
  $paths[] = array('path' => 'node/#node:nid/revisions/#node:vid/unpublish');
  $paths[] = array('path' => 'node/#node:nid/revisions/#node:vid/revert');
  $paths[] = array('path' => 'node/#node:nid/revisions/#node:vid/delete');
  $paths[] = array('path' => 'node/#node:nid/revisions/#node:vid/compare');

  return $paths;
}
