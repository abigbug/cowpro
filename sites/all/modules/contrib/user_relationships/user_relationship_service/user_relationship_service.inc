<?php
/**
 * @file
 * Link general user relationship functionalities to services module.
 *
 * @author Drupal 7 and Services 3.x port by Ed Zenisek <http://drupal.org/user/2410988>
 * @author Adapted to Services 3.x by MD3 http://drupal.org/user/1714848
 * @author Drupal 6 port by Darren Ferguson <http://drupal.org/user/70179>
 * @author Written by scottgifford http://drupal.org/user/245699
 */

/**
 * Get all relationship types.
 *
 * @return
 *   An array of relationship objects.
 *
 * @see user_relationships_types_load()
 */
function user_relationship_service_types() {
  return user_relationships_types_load();
}

/**
 * Get all relationship types for the logged in user.
 *
 * @return
 *   An array of relationship objects for the logged in user.
 *
 * @see user_relationships_load()
 */
function user_relationship_service_mine() {
  try {
    global $user;
    $param = array('user' => $user->uid);
    $rels = user_relationships_load($param);
    if (!$rels || !is_array($rels)) {
      throw new Exception("User relationship load failed");
    }
    return array_values($rels);
  } catch (Exception $ex) {
    return services_error(t('Error getting user relationships: @msg', array('@msg' => $ex->getMessage())));
  }
}

/**
 * Get all relationship types for the requested user.
 *
 * @param $uid
 *   The uid of the user to look up relationships for.
 *
 * @return
 *   An array of relationship objects for the requested user.
 *
 * @see user_relationships_load()
 */
function user_relationship_service_user($uid) {
  try {
    $param = array('user' => $uid);
    $rels = user_relationships_load($param);
    if (!$rels || !is_array($rels)) {
      throw new Exception("User relationship load failed");
    }
    return array_values($rels);
  } catch (Exception $ex) {
    return services_error(t('Error getting user relationships: @msg', array('@msg' => $ex->getMessage())));
  }
}

/**
 * Approve a relationship.
 *
 * @param $data
 *   An object containing the relationship items. The $data object
 *   should contain:
 *     -rid (relationship id to approve.
 *     [GET] {endpoint}/relationships/ or @see user_relationships_load())
 *
 * @return
 *   The relationship object of the newly created relationship.
 *
 * @see user_relationships_save_relationship()
 */
function user_relationship_service_approve($data) {
  if (!$data['rid']) {
    return services_error(t('Missing required field "rid".'), 404);
  }
  // Maintain compability with original code.
  $rid=$data['rid'];
  // Start of Darren Ferguson's code.
  try {
    global $user;
    $rels = user_relationships_load(array('rid' => $rid , 'requestee_id' => $user->uid, 'approved' => 0));
    if (!$rels || !is_array($rels) || count($rels) != 1) {
      throw new Exception("User relationship load failed");
    }
    $rel = array_shift($rels);
    if ($rel->requestee_id != $user->uid) {
      throw new Exception("Access denied");
    }
    user_relationships_save_relationship($rel, 'approve');
    return $rel;
  } catch (Exception $ex) {
    return services_error(t('Error approving relationship: @msg', array('@msg' => $ex->getMessage())));
  }
}

/**
 * Delete or cancel an relationship.
 *
 * @param $data
 *   An object containing the relationship items. The $data object should contain:
 *     -rid (relationship id to delete or cancel.
 *     [GET] {endpoint}/relationships/ or @see user_relationships_load())
 *     -reason (for deleting friendship. possible values: cancel,
 *     disapprove, remove)
 *
 * @return
 *   The relationship object of the newly created relationship.
 *
 * @see user_relationships_delete_relationship()
 */
function user_relationship_service_delete($data) {
  if (!$data['rid']) {
    return services_error(t('Missing required field "rid".'), 404);
  }
  if (!$data['reason']) {
    return services_error(t('Missing required field "reason".'), 404);
  }
  // Maintain compability with original code.
  $rid=$data['rid'];
  $reason=$data['reason'];
  // Start of Darren Ferguson's code.
  try {
    global $user;
    $rels = user_relationships_load(array('rid' => $rid , 'user' => $user->uid));
    if (!$rels || !is_array($rels) || count($rels) != 1) {
      throw new Exception("User relationship load failed");
    }
    $rel = array_shift($rels);
    if ($rel->requestee_id != $user->uid && $rel->requester_id != $user->uid) {
      throw new Exception("Access denied");
    }
    user_relationships_delete_relationship($rel, $user, $reason);
    return $rel;
  } catch (Exception $ex) {
    return services_error(t('Error removing relationship: @msg', array('@msg' => $ex->getMessage())));
  }
}

/**
 * Request a relationship.
 *
 * @param $uid
 *   User id of person to request relationship with
 * @param $type_name
 *   Name of type of relationship to request.
 *   See user_relationships_types_load() or [GET] {endpoint}/relationships/types
 *
 * @return
 *   The relationship object of the newly created relationship.
 *
 * @see user_relationships_request_relationship()
 */
function user_relationship_service_request($uid, $type_name) {
  try {
    $type = user_relationships_type_load(array('name' => $type_name));
    if (!$type) {
      throw new Exception(t('No such relationship type'));
    }

    global $user;
    $existing_relationship = user_relationships_load(array('rtid' => $type->rtid, 'between' => array($user->uid, $uid)));
    // If there is already an existing relationship, return it.
    if (!empty($existing_relationship)) {
      return current($existing_relationship);
    }
    $ret = user_relationships_request_relationship($user, $uid, $type);
    if (!$ret) {
      throw new Exception(t('Unknown failure or permission denied'));
    }
    elseif (!is_object($ret)) {
      throw new Exception($ret);
    }
    return $ret;
  } catch (Exception $ex) {
    return services_error(t('Error requesting relationship: @msg', array('@msg' => $ex->getMessage())), 406);
  }
}
