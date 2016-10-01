<?php

/**
 * Implements hook_features_api().
 */
function user_relationships_features_api() {
  return array(
    'user_relationship' => array(
      'name' => t('User Relationships'),
      'default_hook' => 'user_relationships_default_relationships',
      'default_file' => FEATURES_DEFAULTS_INCLUDED,
      'feature_source' => TRUE,
      'file' => drupal_get_path('module', 'user_relationships') . '/user_relationships.features.inc',
    )
  );
}

/**
 * Implements hook_features_export_options().
 */
function user_relationship_features_export_options() {
  $options = array();
  foreach (user_relationships_types_load() as $relationship) {
    if ($relationship->machine_name) {
      $options[$relationship->machine_name] = $relationship->name;
    }
  }
  return $options;
}

/**
 * Implements hook_features_export().
 */
function user_relationship_features_export($data, &$export, $module_name = '') {
  $pipe = array();
  $map = features_get_default_map('user_relationship');
  foreach ($data as $relationship) {
    // If another module provides this style, add it as a dependency
    if (isset($map[$relationship]) && $map[$relationship] != $module_name) {
      $module = $map[$relationship];
      $export['dependencies'][$module] = $module;
    }
    // Otherwise, export the style
    elseif (user_relationships_type_load(array('machine_name' => $relationship))) {
      $export['dependencies']['user_relationships'] = 'user_relationships';
      $export['features']['user_relationship'][$relationship] = $relationship;
    }
  }
  return $pipe;
}

/**
 * Implements hook_features_export_render().
 */
function user_relationship_features_export_render($module_name, $data, $export = NULL) {
  $code = array();
  $code[] = '  $relationships = array();';
  $code[] = '';
  foreach ($data as $name) {
    if ($original = user_relationships_type_load(array('machine_name' => $name))) {
      $relationship = clone $original;
      unset($relationship->rtid);
      $relationship_export = features_var_export($relationship, '  ');
      $relationship_identifier = features_var_export($name);
      $code[] = "  // Exported user_relationship style: {$name}.";
      $code[] = "  \$relationships[{$relationship_identifier}] = {$relationship_export};";
      $code[] = "";
    }
  }
  $code[] = '  return $relationships;';
  $code = implode("\n", $code);
  return array('user_relationships_default_relationships' => $code);
}

/**
 * Implements hook_features_revert().
 */
function user_relationship_features_revert($module) {
  user_relationship_features_rebuild($module);
}

/**
 * Implements of hook_features_rebuild().
 */
function user_relationship_features_rebuild($module) {
  if ($user_relationships = features_get_default('user_relationship', $module)) {
    foreach ($user_relationships as $machine_name => $user_relationship) {
      $user_relationship = (object) $user_relationship;

      drupal_static_reset('user_relationships_types_load');
      if ($existing_relationship = user_relationships_type_load(array('machine_name' => $machine_name))) {
        $user_relationship->rtid = $existing_relationship->rtid;
      }
      user_relationships_type_save($user_relationship);
    }
  }
}
