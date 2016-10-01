<?php

require_once 'cowpro_issuing.class.inc';

/**
 * @file
 * The controller for the issuing entity containing the CRUD operations.
 */

/**
 * The controller class for issuing contains methods for the
 * CRUD operations. The load method is inherited from the default controller.
 */
class CowProIssuingEntityController extends DrupalCowProEntityController {

  /**
   * Create a default issuing.
   *
   * @param array $values
   *   An array of values to set, keyed by property name.
   *
   * @return
   *   A issuing object with all default fields initialized.
   */
  public function create(array $values = array()) {
    $issuing = new Issuing($values);
  	foreach (module_implements('cpwpro_issuing_create') as $module) {
			$function = $module . '_cpwpro_issuing_create';
			$issuing = $function($issuing);
		}
    return $issuing;
  }

  /**
   * Saves an issuing.
   *
   * When saving an issuing without an ID, this function will create a new
   * issuing at that time.
   *
   * @param $issuing
   *   The full issuing object to save.
   * @param $transaction
   *   An optional transaction object.
   *
   * @return
   *   SAVED_NEW or SAVED_UPDATED depending on the operation performed.
   */
  public function save($issuing, DatabaseTransaction $transaction = NULL) {
    if (!isset($transaction)) {
      $transaction = db_transaction();
      $started_transaction = TRUE;
    }

    try {
      global $user;

      // Determine if we will be inserting a new issuing.
      $issuing->is_new = empty($issuing->issuing_id);

      // Set the timestamp fields.
      if ($issuing->is_new && empty($issuing->created)) {
        $issuing->created = REQUEST_TIME;
      }
      else {
        // Otherwise if the profile is not new but comes from an entity_create()
        // or similar function call that initializes the created timestamp and
        // uid value to empty strings, unset them to prevent destroying existing
        // data in those properties on update.
        if ($issuing->created === '') {
          unset($issuing->created);
        }
        if ($issuing->uid === '') {
          unset($issuing->uid);
        }
      }

      $issuing->changed = REQUEST_TIME;

      return parent::save($issuing, $transaction);
    }
    catch (Exception $e) {
      if (!empty($started_transaction)) {
        $transaction->rollback();
        watchdog_exception($this->entityType, $e);
      }
      throw $e;
    }
  }

  /**
   * Unserializes the data property of loaded issuing.
   */
  public function attachLoad(&$queried_issuings, $revision_id = FALSE) {
    foreach ($queried_issuings as $issuing_id => &$issuing) {
    	$issuing->data = unserialize($issuing->data);
    }

    // Call the default attachLoad() method. This will add fields and call
    // hook_cowpro_issuing_load().
    parent::attachLoad($queried_issuings, $revision_id);
  }

  /**
   * Deletes multiple issuing by ID.
   *
   * @param $issuing_ids
   *   An array of issuing IDs to delete.
   * @param $transaction
   *   An optional transaction object.
   * @param $entity_context
   *   An optional entity context array that specifies the entity throgh whose
   *   issuing reference field the given issuings are being deleted:
   *   - entity_type: the type of entity
   *   - entity_id: the unique ID of the entity
   *
   * @return
   *   TRUE on success, FALSE otherwise.
   */
  public function delete($issuing_ids, DatabaseTransaction $transaction = NULL, $entity_context = array()) {
    if (!empty($issuing_ids)) {
      $issuings = $this->load($issuing_ids, array());

      // Ensure the issuings can actually be deleted.
      foreach ((array) $issuings as $issuing_id => $issuing) {
        // If we received an entity context for this issuing, add it now.
        if (!empty($entity_context)) {
          $issuing->entity_context = $entity_context;
        }

        // If the issuing cannot be deleted, remove it from the issuings array.
        if (!cowpro_issuing_can_delete($issuing)) {
          unset($issuings[$issuing_id]);
        }
      }

      // If none of the specified issuings can be deleted, return FALSE.
      if (empty($issuings)) {
        return FALSE;
      }

      parent::delete($issuing_ids, $transaction);
      return TRUE;
    }
    else {
      return FALSE;
    }
  }
}
