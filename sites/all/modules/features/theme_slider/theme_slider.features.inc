<?php
/**
 * @file
 * theme_slider.features.inc
 */

/**
 * Implements hook_views_api().
 */
function theme_slider_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_node_info().
 */
function theme_slider_node_info() {
  $items = array(
    'slide' => array(
      'name' => t('Slide'),
      'base' => 'node_content',
      'description' => t('Use to create slides in header-slider.'),
      'has_title' => '1',
      'title_label' => t('标题'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
