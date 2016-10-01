<?php
/**
 * @file
 * cowpro_permission.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function cowpro_permission_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'access comments'.
  $permissions['access comments'] = array(
    'name' => 'access comments',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'comment',
  );

  // Exported permission: 'access content'.
  $permissions['access content'] = array(
    'name' => 'access content',
    'roles' => array(
      'anonymous user' => 'anonymous user',
      'debtor' => 'debtor',
      'lender' => 'lender',
      'manager' => 'manager',
    ),
    'module' => 'node',
  );

  // Exported permission: 'access user profiles'.
  $permissions['access user profiles'] = array(
    'name' => 'access user profiles',
    'roles' => array(
      'manager' => 'manager',
    ),
    'module' => 'user',
  );

  // Exported permission: 'admin repayment'.
  $permissions['admin repayment'] = array(
    'name' => 'admin repayment',
    'roles' => array(
      'administrator' => 'administrator',
      'manager' => 'manager',
    ),
    'module' => 'cowpro_issuing',
  );

  // Exported permission: 'administer comments'.
  $permissions['administer comments'] = array(
    'name' => 'administer comments',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'comment',
  );

  // Exported permission: 'administer cowpro_customer_profile entities'.
  $permissions['administer cowpro_customer_profile entities'] = array(
    'name' => 'administer cowpro_customer_profile entities',
    'roles' => array(
      'administrator' => 'administrator',
      'manager' => 'manager',
    ),
    'module' => 'cowpro_customer',
  );

  // Exported permission: 'administer customer profile types'.
  $permissions['administer customer profile types'] = array(
    'name' => 'administer customer profile types',
    'roles' => array(
      'administrator' => 'administrator',
      'manager' => 'manager',
    ),
    'module' => 'cowpro_customer',
  );

  // Exported permission: 'administer users'.
  $permissions['administer users'] = array(
    'name' => 'administer users',
    'roles' => array(
      'manager' => 'manager',
    ),
    'module' => 'user',
  );

  // Exported permission: 'bid issuing'.
  $permissions['bid issuing'] = array(
    'name' => 'bid issuing',
    'roles' => array(
      'administrator' => 'administrator',
      'lender' => 'lender',
    ),
    'module' => 'cowpro_issuing',
  );

  // Exported permission: 'configure p2p'.
  $permissions['configure p2p'] = array(
    'name' => 'configure p2p',
    'roles' => array(
      'administrator' => 'administrator',
      'manager' => 'manager',
    ),
    'module' => 'cowpro',
  );

  // Exported permission: 'create article content'.
  $permissions['create article content'] = array(
    'name' => 'create article content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'create contract_credit_assignment content'.
  $permissions['create contract_credit_assignment content'] = array(
    'name' => 'create contract_credit_assignment content',
    'roles' => array(
      'manager' => 'manager',
    ),
    'module' => 'node',
  );

  // Exported permission: 'create contract_loan content'.
  $permissions['create contract_loan content'] = array(
    'name' => 'create contract_loan content',
    'roles' => array(
      'manager' => 'manager',
    ),
    'module' => 'node',
  );

  // Exported permission: 'create cowpro_customer_profile entities'.
  $permissions['create cowpro_customer_profile entities'] = array(
    'name' => 'create cowpro_customer_profile entities',
    'roles' => array(
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
      'debtor' => 'debtor',
      'lender' => 'lender',
      'manager' => 'manager',
    ),
    'module' => 'cowpro_customer',
  );

  // Exported permission: 'create cowpro_issuing content'.
  $permissions['create cowpro_issuing content'] = array(
    'name' => 'create cowpro_issuing content',
    'roles' => array(
      'debtor' => 'debtor',
      'manager' => 'manager',
    ),
    'module' => 'node',
  );

  // Exported permission: 'create page content'.
  $permissions['create page content'] = array(
    'name' => 'create page content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'delete any article content'.
  $permissions['delete any article content'] = array(
    'name' => 'delete any article content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'delete any contract_credit_assignment content'.
  $permissions['delete any contract_credit_assignment content'] = array(
    'name' => 'delete any contract_credit_assignment content',
    'roles' => array(
      'manager' => 'manager',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any contract_loan content'.
  $permissions['delete any contract_loan content'] = array(
    'name' => 'delete any contract_loan content',
    'roles' => array(
      'manager' => 'manager',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any cowpro_issuing content'.
  $permissions['delete any cowpro_issuing content'] = array(
    'name' => 'delete any cowpro_issuing content',
    'roles' => array(
      'manager' => 'manager',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any page content'.
  $permissions['delete any page content'] = array(
    'name' => 'delete any page content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'delete own article content'.
  $permissions['delete own article content'] = array(
    'name' => 'delete own article content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'delete own contract_credit_assignment content'.
  $permissions['delete own contract_credit_assignment content'] = array(
    'name' => 'delete own contract_credit_assignment content',
    'roles' => array(
      'manager' => 'manager',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own contract_loan content'.
  $permissions['delete own contract_loan content'] = array(
    'name' => 'delete own contract_loan content',
    'roles' => array(
      'manager' => 'manager',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own cowpro_issuing content'.
  $permissions['delete own cowpro_issuing content'] = array(
    'name' => 'delete own cowpro_issuing content',
    'roles' => array(
      'debtor' => 'debtor',
      'manager' => 'manager',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own page content'.
  $permissions['delete own page content'] = array(
    'name' => 'delete own page content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'edit any article content'.
  $permissions['edit any article content'] = array(
    'name' => 'edit any article content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'edit any contract_credit_assignment content'.
  $permissions['edit any contract_credit_assignment content'] = array(
    'name' => 'edit any contract_credit_assignment content',
    'roles' => array(
      'manager' => 'manager',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any contract_loan content'.
  $permissions['edit any contract_loan content'] = array(
    'name' => 'edit any contract_loan content',
    'roles' => array(
      'manager' => 'manager',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any cowpro_customer_profile entity'.
  $permissions['edit any cowpro_customer_profile entity'] = array(
    'name' => 'edit any cowpro_customer_profile entity',
    'roles' => array(
      'administrator' => 'administrator',
      'manager' => 'manager',
    ),
    'module' => 'cowpro_customer',
  );

  // Exported permission: 'edit any cowpro_issuing content'.
  $permissions['edit any cowpro_issuing content'] = array(
    'name' => 'edit any cowpro_issuing content',
    'roles' => array(
      'manager' => 'manager',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any page content'.
  $permissions['edit any page content'] = array(
    'name' => 'edit any page content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'edit own article content'.
  $permissions['edit own article content'] = array(
    'name' => 'edit own article content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'edit own comments'.
  $permissions['edit own comments'] = array(
    'name' => 'edit own comments',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'comment',
  );

  // Exported permission: 'edit own contract_credit_assignment content'.
  $permissions['edit own contract_credit_assignment content'] = array(
    'name' => 'edit own contract_credit_assignment content',
    'roles' => array(
      'manager' => 'manager',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own contract_loan content'.
  $permissions['edit own contract_loan content'] = array(
    'name' => 'edit own contract_loan content',
    'roles' => array(
      'manager' => 'manager',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own cowpro_customer_profile entities'.
  $permissions['edit own cowpro_customer_profile entities'] = array(
    'name' => 'edit own cowpro_customer_profile entities',
    'roles' => array(
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
      'debtor' => 'debtor',
      'lender' => 'lender',
      'manager' => 'manager',
    ),
    'module' => 'cowpro_customer',
  );

  // Exported permission: 'edit own cowpro_issuing content'.
  $permissions['edit own cowpro_issuing content'] = array(
    'name' => 'edit own cowpro_issuing content',
    'roles' => array(
      'debtor' => 'debtor',
      'manager' => 'manager',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own page content'.
  $permissions['edit own page content'] = array(
    'name' => 'edit own page content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'failing issuing'.
  $permissions['failing issuing'] = array(
    'name' => 'failing issuing',
    'roles' => array(
      'administrator' => 'administrator',
      'manager' => 'manager',
    ),
    'module' => 'cowpro_issuing',
  );

  // Exported permission: 'make loans to'.
  $permissions['make loans to'] = array(
    'name' => 'make loans to',
    'roles' => array(
      'administrator' => 'administrator',
      'manager' => 'manager',
    ),
    'module' => 'cowpro_issuing',
  );

  // Exported permission: 'post comments'.
  $permissions['post comments'] = array(
    'name' => 'post comments',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'comment',
  );

  // Exported permission: 'review issuing'.
  $permissions['review issuing'] = array(
    'name' => 'review issuing',
    'roles' => array(
      'administrator' => 'administrator',
      'manager' => 'manager',
    ),
    'module' => 'cowpro_issuing',
  );

  // Exported permission: 'skip comment approval'.
  $permissions['skip comment approval'] = array(
    'name' => 'skip comment approval',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'comment',
  );

  // Exported permission: 'temporary advance'.
  $permissions['temporary advance'] = array(
    'name' => 'temporary advance',
    'roles' => array(
      'administrator' => 'administrator',
      'manager' => 'manager',
    ),
    'module' => 'cowpro_issuing',
  );

  // Exported permission: 'view any cowpro_customer_profile entity'.
  $permissions['view any cowpro_customer_profile entity'] = array(
    'name' => 'view any cowpro_customer_profile entity',
    'roles' => array(
      'administrator' => 'administrator',
      'manager' => 'manager',
    ),
    'module' => 'cowpro_customer',
  );

  // Exported permission: 'view own cowpro_customer_profile entities'.
  $permissions['view own cowpro_customer_profile entities'] = array(
    'name' => 'view own cowpro_customer_profile entities',
    'roles' => array(
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
      'debtor' => 'debtor',
      'lender' => 'lender',
      'manager' => 'manager',
    ),
    'module' => 'cowpro_customer',
  );

  return $permissions;
}
