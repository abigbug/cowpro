<?php

/**
 * @file
 * Provides metadata for the issuing entity.
 */

/**
 * Implements hook_entity_property_info().
 */
function cowpro_issuing_entity_property_info() {
  $info = array();

  // Add meta-data about the basic cowpro_issuing properties.
  $properties = &$info['cowpro_issuing']['properties'];

  $properties['issuing_id'] = array(
    'label' => t('Issuing ID'),
    'description' => t('The internal numeric ID of the issuing.'),
    'type' => 'integer',
    'schema field' => 'issuing_id',
  );
  $properties['category'] = array(
    'label' => t('Category'),
    'description' => t('The category of the issuing.'),
    'type' => 'token',
    'setter callback' => 'entity_property_verbatim_set',
    'setter permission' => 'administer cowpro_issuing entities',
    'options list' => 'cowpro_issuing_category_options_list',
    'required' => TRUE,
    'schema field' => 'type',
  );
  $properties['uid'] = array(
    'label' => t('User ID'),
    'type' => 'integer',
    'description' => t("The unique ID of the user the issuing belongs to."),
    'setter callback' => 'entity_property_verbatim_set',
    'setter permission' => 'administer cowpro_issuing entities',
    'clear' => array('user'),
    'schema field' => 'uid',
  );
  $properties['user'] = array(
    'label' => t('User'),
    'type' => 'user',
    'description' => t("The user the issuing belongs to."),
    'getter callback' => 'cowpro_issuing_get_properties',
    'setter callback' => 'cowpro_issuing_set_properties',
    'setter permission' => 'administer cowpro_issuing entities',
    'required' => TRUE,
    'computed' => TRUE,
    'clear' => array('uid'),
  );
  $properties['status'] = array(
    'label' => t('Status'),
    'description' => '标的状态.',
    'setter callback' => 'entity_property_verbatim_set',
    'setter permission' => 'administer cowpro_issuing entities',
    'type' => 'boolean',
    'schema field' => 'status',
  );
  $properties['created'] = array(
    'label' => t('Date created'),
    'description' => t('The date the issuing was created.'),
    'type' => 'date',
    'setter callback' => 'entity_property_verbatim_set',
    'setter permission' => 'administer cowpro_issuing entities',
    'schema field' => 'created',
  );
  $properties['changed'] = array(
    'label' => t('Date updated'),
    'description' => t('The date the issuing was last updated.'),
    'type' => 'date',
    'setter callback' => 'entity_property_verbatim_set',
    'setter permission' => 'administer cowpro_issuing entities',
    'schema field' => 'changed',
  );

  $properties = &$info['cowpro_repayment_schedule']['properties'];
  $properties['payer_user'] = array(
    'label' => t('付款人'),
    'description' => '付款人',
    'type' => 'user',
    'getter callback' => '_cowpro_message_rules_payer_user_get',
    'computed' => TRUE,
  );
  $properties['receiver_user'] = array(
    'label' => t('收款人'),
    'description' => '收款人',
    'type' => 'user',
    'getter callback' => '_cowpro_message_rules_receiver_user_get',
  	'computed' => TRUE,
  );
  $properties['capital_integer'] = array(
		'label' => t('当期本金(整数)'),
		'description' => '当期本金(整数)',
		'type' => 'integer',
 		'getter callback' => '_cowpro_message_rules_capital_integer_get',
    'computed' => TRUE,
  );
  $properties['interest_integer'] = array(
  		'label' => t('当期利息(整数)'),
  		'description' => '当期利息(整数)',
  		'type' => 'integer',
  		'getter callback' => '_cowpro_message_rules_interest_integer_get',
  		'computed' => TRUE,
  );

  /*
		'loan_amounts_decimal' => array(
      'label' => t('贷款总额'),
      'description' => '贷款总金额',
      'type' => 'decimal',
      'getter callback' => '_cowpro_message_rules_loan_amounts_decimal_get',
    'computed' => TRUE,
    ),
    'loan_amounts_integer' => array(
      'label' => t('贷款总额(整数)'),
      'description' => '贷款总金额(整数)',
      'type' => 'integer',
      'getter callback' => '_cowpro_message_rules_loan_amounts_integer_get',
    ),

   */

  return $info;
}
