<?php
/**
 * @file
 *   Generate relationships between site users for testing purposes.
 *
 */

/**
 * Implements hook_drush_command().
 */
function user_relationships_drush_command() {
  $items['generate-user-relationships'] = array(
    'description' => dt('Generates user relationships.'),
    'arguments' => array(
      'number_relations' => dt('The number of relationships to generate.'),
    ),
    'options' => array(
      'types' => 'A comma delimited list of relationship types to create.',
      'kill' => 'Delete all user relationships before generating new ones.',
      'invoke' => 'Invoke the hook_user_relationships_save with given param'
    ),
    'aliases' => array('genur'),
  );
  return $items;
}

/**
 * Sends message to drush log, if enabled.
 *
 * @param $message
 *   Text of message.
 */
function user_relationships_message($message) {
  if (function_exists('drush_log')) {
    drush_log($message, 'ok');
  }
  else {
    drupal_set_message($message);
  }
}

/**
 * Generate relationships.
 *
 * @param $number_relationships
 *   Number to generate of each relationship type.
 * @param $types
 *   Array of types to generate relations for.
 * @param $kill
 *   Whether to delete all existing relationships before creating new ones.
 *
 * @return
 *   Array of rids of the generated relations.
 */
function drush_user_relationships_generate_user_relationships($number_relationships = 10, $types = array(), $kill = FALSE) {
  if ($kill) {
    $num_deleted = db_delete('user_relationships')->execute();
    user_relationships_message('Deleted ' . $num_deleted . ' existing relationships.');
  }

  $action = drush_get_option('invoke');

  $number_users = $number_relationships * 2;
  if (empty($types)) {
    // If no types provided then load all types.
    $types = user_relationships_types_load();
  }
  if (empty($types)) {
    return drush_log('No types of relationship defined.', 'error');
  }

  foreach ($types as $type) {
    //Load all roles who have this permission
    $perm = 'can have ' . $type->name . ' relationships';
    $allowed_roles = user_roles(TRUE, $perm);
    $uids = array();

    // Authenticated is easiest if its an available role use it.
    if (in_array(DRUPAL_AUTHENTICATED_RID, array_keys($allowed_roles))) {
      $sql = "SELECT uid FROM users WHERE uid != 0 AND uid != 1";
      $result = db_query_range($sql, 0, $number_users);
      foreach ($result as $user) {
        $uids[$user->uid] = $user->uid;
      }
    }
    elseif (!empty($allowed_roles)) {
      $role_keys = array_keys($allowed_roles);
      $role_keys = implode(',', $role_keys);
      $sql = "SELECT uid FROM users_roles WHERE rid in (:roles)";
      $result = db_query($sql, array(':roles' => $role_keys));
      foreach ($result as $user) {
        $uids[$user->uid] = $user->uid;
      }
    }
    if (empty($uids)) {
      user_relationships_message('No suitable users to create relationships with. Please check your roles and permissions.');
      break;
    }
    $users = user_load_multiple($uids);
    $count = 0;
    while ($count < $number_relationships) {
      $requester = array_rand($users);
      $requestee = array_rand($users);
      if ($requestee != $requester) {
        $relationship = user_relationships_request_relationship($requester, $requestee, $type, TRUE);
        if ($action) {
          module_invoke_all('user_relationships_save', $relationship, $action);
        }
        $count++;
      }
    }
    user_relationships_message(t('Created !numrels relationships for !numusers users.', array('!numrels' => $count, '!numusers' => count($users))));
  }
}
