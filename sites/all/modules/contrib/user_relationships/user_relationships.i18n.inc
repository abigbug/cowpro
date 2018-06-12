<?php
/**
 * @file
 * Internationalization (i18n) hooks
 */

/**
 * Implements hook_i18n_string_info().
 */
function user_relationships_i18n_string_info() {
  return array(
    'user_relationships' => array(
      'title' => t('User Relationships'),
      'description' => t('Translations for relationship type names'),
      'format' => FALSE,
      'list' => TRUE,
    ),
  );
}

/**
 * Implements hook_i18n_object_info().
 */
function user_relationships_i18n_object_info() {
  $info['user_relationships_type'] = array(
    // Generic object title.
    'title' => t('Relationship type'),
    // The object key field.
    'key' => 'rtid',
    // The object load callback.
    'load callback' => 'user_relationships_type_load',
    // Placeholders for automatic paths.
    'placeholders' => array(
      '%user_relationships_type' => 'rtid',
    ),
    // To produce edit links automatically.
    'edit path' => 'admin/config/people/relationships/%user_relationships_type/edit',
    // Auto-generate translate tab.
    'translate tab' => 'admin/config/people/relationships/%user_relationships_type/translate',
    // Properties for string translation.
    'string translation' => array(
      // Text group that will handle this object's strings.
      'textgroup' => 'user_relationships',
      // Object type property for string translation.
      'type' => 'type',
      // Table where the object is stored, to automate string lists
      'table' => 'user_relationship_types',
      // Translatable properties of these objects.
      'properties' => array(
        'name' => t('Name'),
        'plural_name' => t('Plural name'),
        'name_capitalized' => t('Capitalized name'),
        'plural_name_capitalized' => t('Plural capitalized name'),
        'reverse_name' => t('Reversed name'),
        'reverse_plural_name' => t('Reversed plural name'),
        'reverse_name_capitalized' => t('Reversed capitalized name'),
        'reverse_plural_name_capitalized' => t('Reversed capitalized plural name'),
      ),
      // Path to translate strings to every language.
      'translate path' => 'admin/config/people/relationships/%user_relationships_type/translate/%i18n_language',
    )
  );
  return $info;
}
