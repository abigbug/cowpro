<?php

/**
 * @file
 * Provides some views properties
 */

/**
 * Implements hook_themekey_properties().
 *
 * Provides additional properties for module ThemeKey:
 * - views:vid
 * - views:machine_name
 * - views:human_name
 *
 * @return
 *   array of themekey properties and mapping functions
 */
function themekey_views_themekey_properties() {
  // Attributes of properties
  $attributes = array();

  if (module_exists('views')) {

    $attributes['views:vid'] = array(
      'description' => t('Views: VID - The vid of a view (vid)'),
      'validator' => 'themekey_validator_ctype_digit',
      'page cache' => THEMEKEY_PAGECACHE_SUPPORTED,
    );

    $attributes['views:machine_name'] = array(
      'description' => t('Views: Machine Name - The machine name of a view'),
      'page cache' => THEMEKEY_PAGECACHE_SUPPORTED,
    );

    $attributes['views:human_name'] = array(
      'description' => t('Views: Human Name - The (human readable) name of a view'),
      'page cache' => THEMEKEY_PAGECACHE_SUPPORTED,
    );

    // Mapping functions
    $maps = array();
    $maps[] = array(
      'src' => 'drupal:get_q',
      'dst' => 'views:vid',
      'callback' => 'themekey_views_getq2vid',
    );

    $maps[] = array(
      'src' => 'drupal:get_q',
      'dst' => 'views:machine_name',
      'callback' => 'themekey_views_getq2machine_name',
    );

    $maps[] = array(
      'src' => 'drupal:get_q',
      'dst' => 'views:human_name',
      'callback' => 'themekey_views_getq2human_name',
    );

    $return = array('attributes' => $attributes, 'maps' => $maps);

  }

  return $return;
}


/**
 * ThemeKey mapping function to set a
 * ThemeKey property's value (destination)
 * with the aid of another ThemeKey property (source).
 *
 * src: drupal:get_q
 * dst: views:vid
 *
 * @param $get_q
 *   a drupal path
 *
 * @return
 *   int
 *   or NULL if no value could be mapped
 */
function themekey_views_getq2vid($get_q) {
  return themekey_views_get_simple_property_by_getq($get_q, 'vid');
}

/**
 * ThemeKey mapping function to set a
 * ThemeKey property's value (destination)
 * with the aid of another ThemeKey property (source).
 *
 * src: drupal:get_q
 * dst: views:machine_name
 *
 * @param $get_q
 *   a drupal path
 *
 * @return
 *   string
 *   or NULL if no value could be mapped
 */
function themekey_views_getq2machine_name($get_q) {
  return themekey_views_get_simple_property_by_getq($get_q, 'name');
}

/**
 * ThemeKey mapping function to set a
 * ThemeKey property's value (destination)
 * with the aid of another ThemeKey property (source).
 *
 * src: drupal:get_q
 * dst: views:human_name
 *
 * @param $get_q
 *   a drupal path
 *
 * @return
 *   string
 *   or NULL if no value could be mapped
 */
function themekey_views_getq2human_name($get_q) {
  return themekey_views_get_simple_property_by_getq($get_q, 'human_name');
}

/**
 * Helper function to to get the value of a simple view property by
 * the view's drupal path
 *
 * @param $get_q
 *   a drupal path
 * @param $property
 *   name of a "simple" view property
 *
 * @return
 *   string
 *   or NULL if no value could be mapped
 */
function themekey_views_get_simple_property_by_getq($get_q, $property) {
  static $all_views = NULL;

  if (is_null($all_views)) {
    $all_views = views_get_all_views();
  }

  if (!empty($all_views)) {
    foreach ($all_views as $views_name => $view) {
      // IF VIEW HAS A PATH WHICH IS EQUAL
      if ($view->get_url() == $get_q) {
        return $view->$property;
      }
    }
  }

  return NULL;
}
