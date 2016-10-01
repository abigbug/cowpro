<?php
/**
 * @file
 * cowpro_features.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function cowpro_features_field_group_info() {
  $field_groups = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_contract|node|cowpro_issuing|form';
  $field_group->group_name = 'group_contract';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'cowpro_issuing';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => '合同',
    'weight' => '10',
    'children' => array(
      0 => 'field_contract_credit_assignment',
      1 => 'field_contract_loan',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-contract field-group-fieldset',
        'required_fields' => 1,
      ),
    ),
  );
  $field_groups['group_contract|node|cowpro_issuing|form'] = $field_group;

  // Translatables
  // Included for use with string extractors like potx.
  t('合同');

  return $field_groups;
}
