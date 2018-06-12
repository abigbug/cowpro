<?php

/**
 * @file
 * Provides some ThemeKey properties related to the path module.
 *
 * @author Markus Kalkbrenner | bio.logis GmbH
 *   @see http://drupal.org/user/124705
 */


/**
 * Implements hook_themekey_properties().
 *
 * Provides additional properties for the ThemeKey module:
 * - path:node_alias
 *
 * @return
 *   array of themekey properties and mapping functions
 */
function themekey_path_themekey_properties() {
  // Attributes of properties
  $attributes = array();
  $attributes['path:node_alias'] = array(
    'description' => t('Path: Node alias - The path alias assigned to a node.'),
    'validator' => '',
    'page cache' => THEMEKEY_PAGECACHE_SUPPORTED,
  );

  // Mapping functions
  $maps = array();
  $maps[] = array(
    'src' => 'node:nid',
    'dst' => 'path:node_alias',
    'callback' => 'themekey_path_nid2alias',
  );

  return array('attributes' => $attributes, 'maps' => $maps);
}

/**
 * ThemeKey mapping function to set a
 * ThemeKey property's value (destination)
 * with the aid of another ThemeKey property (source).
 *
 * src: node:nid
 * dst: path:node_alias
 *
 * @param $nid
 *   a node id
 *
 * @return
 *   string
 *   or NULL if no value could be mapped
 */
function themekey_path_nid2alias($nid) {
  $node_path = 'node/' . $nid;
  $alias = drupal_get_path_alias($node_path);
  if ($alias != $node_path) {
    return $alias;
  }
  return NULL;
}
