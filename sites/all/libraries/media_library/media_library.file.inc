<?php

/**
 * @file
 * File hooks implemented by the Media Library module.
 */

/**
 * Implements hook_file_operations().
 */
function media_library_file_operations() {
  $operations = array(
    'add_to_library' => array(
      'label' => t('Add selected files to the media library'),
      'callback' => 'file_entity_mass_update',
      'callback arguments' => array('updates' => array('library' => INCLUDE_IN_LIBRARY)),
    ),
    'remove_from_library' => array(
      'label' => t('Remove selected files from the media library'),
      'callback' => 'file_entity_mass_update',
      'callback arguments' => array('updates' => array('library' => EXCLUDE_FROM_LIBRARY)),
    ),
  );

  return $operations;
}
