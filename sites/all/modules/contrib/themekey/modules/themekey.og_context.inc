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
 * - group:id
 * - group:type
 *
 * @return
 * array of themekey properties and mapping functions
 */
function themekey_og_context_themekey_properties() {
  // Attributes for properties
  $attributes = array();
  $attributes['group:id'] = array(
    'description' => t('Group: ID - The og group ID'),
    'validator' => 'themekey_validator_ctype_digit',
    'page cache' => THEMEKEY_PAGECACHE_SUPPORTED,
  );
  $attributes['group:type'] = array(
    'description' => t('Group: Type - The type of an og group'),
    'validator' => 'themekey_validator_og_group_type',
    'page cache' => THEMEKEY_PAGECACHE_SUPPORTED,
  );

  // Mapping functions
  $maps = array();
  $maps[] = array('src' => 'node:nid',
                  'dst' => 'group:id',
                  'callback' => 'themekey_og_context_nid2gid');
  $maps[] = array('src' => 'node:nid',
                  'dst' => 'group:type',
                  'callback' => 'themekey_og_context_nid2type');

  return array('attributes' => $attributes, 'maps' => $maps);
}

/**
 * Implements hook_themekey_paths().
 */
function themekey_og_context_themekey_paths() {
  $paths = array();

  $paths[] = array('path' => 'group/%group:type/#group:id');

  return $paths;
}

/**
 * ThemeKey mapping function to set a
 * ThemeKey property's value (destination)
 * with the aid of another ThemeKey property (source).
 *
 * src: node:nid
 * dst: group:id
 *
 * @param $nid
 *   a node id
 *
 * @return
 *   int
 *   or NULL if no value could be mapped
 */
function themekey_og_context_nid2gid($nid) {
  // look for group info from context
  if ($group = og_context()) {
    return $group['gid'];
  }

  return NULL;
}


/**
 * ThemeKey mapping function to set a
 * ThemeKey property's value (destination)
 * with the aid of another ThemeKey property (source).
 *
 * src: node:nid
 * dst: group:type
 *
 * @param $nid
 *   a node id
 *
 * @return
 *   string
 *   or NULL if no value could be mapped
 */
function themekey_og_context_nid2type($nid) {
  // look for group info from context
  if ($group = og_context()) {
    return $group['group_type'];
  }

  return NULL;
}
