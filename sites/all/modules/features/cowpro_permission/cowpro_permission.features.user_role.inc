<?php
/**
 * @file
 * cowpro_permission.features.user_role.inc
 */

/**
 * Implements hook_user_default_roles().
 */
function cowpro_permission_user_default_roles() {
  $roles = array();

  // Exported role: administrator.
  $roles['administrator'] = array(
    'name' => 'administrator',
    'weight' => 2,
  );

  // Exported role: debtor.
  $roles['debtor'] = array(
    'name' => 'debtor',
    'weight' => 5,
  );

  // Exported role: lender.
  $roles['lender'] = array(
    'name' => 'lender',
    'weight' => 4,
  );

  // Exported role: manager.
  $roles['manager'] = array(
    'name' => 'manager',
    'weight' => 3,
  );

  return $roles;
}
