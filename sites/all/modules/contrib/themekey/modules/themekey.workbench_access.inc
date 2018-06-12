<?php

/**
 * @file
 * Integrates Workbench Access module into ThemeKey.
 *
 * @see themekey.module
 *
 * @author richard.french
 *   @see http://drupal.org/user/2388234
 *
 * @author Markus Kalkbrenner | bio.logis GmbH
 *   @see http://drupal.org/user/124705
 */


/**
 * Implements hook_themekey_properties().
 *
 * Provides additional properties for the ThemeKey module:
 *   workbench_access:access_id
 *
 * @return
 *   array of themekey properties
 */
function themekey_workbench_access_themekey_properties() {

  $attributes = array();
  $attributes['workbench_access:access_id'] = array(
    'description' => t('Workbench: Access ID - The id of the of the taxonomy term used as the access id'),
    'validator' => 'themekey_validator_ctype_digit',
    'page cache' => THEMEKEY_PAGECACHE_SUPPORTED,
  );

  $maps = array();

  $maps[] = array(
    'src' => 'node:nid',
    'dst' => 'workbench_access:access_id',
    'callback' => 'themekey_workbench_access_nid2access_id',
  );


  return array('attributes' => $attributes, 'maps' => $maps);
}


/**
 * ThemeKey mapping function to set a
 * ThemeKey property's value (destination)
 * with the aid of another ThemeKey property (source).
 *
 * src: node:nid
 * dst: workbench_access:access_id
 *
 * @param $nid
 *   a node id
 *
 * @return
 *   int
 *   or NULL if no value could be mapped
 */
function themekey_workbench_access_nid2access_id($nid) {
  $aids = array();

  $query = db_select('workbench_access_node', 'wban');
  $query->addField('wban', 'access_id');
  $query->condition('wban.nid', $nid);
  $result = $query->execute();

  foreach ($result as $item) {
    $aids[] = $item->access_id;
  }

  return count($aids) ? $aids : NULL;
}
