<?php

/**
 * @file
 * The controller for the bank card entity containing the CRUD operations.
 */

/**
 * The controller class for bank card contains methods for the bank card
 * CRUD operations. The load method is inherited from the default controller.
 */
class CowProFundBankCardEntityController extends DrupalCowProEntityController {

  /**
   * Create a default bank card
   *
   * @param array $values
   *   An array of values to set, keyed by property name.
   *
   * @return
   *   A bank card object with all default fields initialized.
   */
  public function create(array $values = array()) {
    $values += array(
      'bankcard_id' => NULL,
    	'uid' => '',
    	'type' => 0,
    	'card_no' => '',
    	'cardholder' => '',
    	'bank_name' => '',
    	'bank_branch' => '',
    	'province' => '',
    	'city' => '',
      'created' => '',
      'changed' => '',
    );
    return parent::create($values);
  }

  /**
   * Saves a bank card.
   *
   * When saving a bank card without an ID, this function will create a new
   * bank card at that time.
   *
   * @param $bankcard
   *   The full bank card object to save.
   * @param $transaction
   *   An optional transaction object.
   *
   * @return
   *   SAVED_NEW or SAVED_UPDATED depending on the operation performed.
   */
  public function save($bankcard, DatabaseTransaction $transaction = NULL) {
    if (!isset($transaction)) {
      $transaction = db_transaction();
      $started_transaction = TRUE;
    }

    try {
      global $user;

      // Determine if we will be inserting a new journal.
      $bankcard->is_new = empty($bankcard->bankcard_id);

      // Set the timestamp fields.
      if ($bankcard->is_new && empty($bankcard->created)) {
        $bankcard->created = REQUEST_TIME;
      }
      else {
        // Otherwise if the bank card is not new but comes from an entity_create()
        // or similar function call that initializes the created timestamp and
        // uid value to empty strings, unset them to prevent destroying existing
        // data in those properties on update.
        if ($bankcard->created === '') {
          unset($bankcard->created);
        }
        if ($bankcard->uid === '') {
          unset($bankcard->uid);
        }
      }

      $bankcard->changed = REQUEST_TIME;

      return parent::save($bankcard, $transaction);
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
   * Unserializes the data property of loaded bank card.
   */
  public function attachLoad(&$queried_cards, $revision_id = FALSE) {
    foreach ($queried_cards as $bankcard_id => &$bankcard) {
    	$bankcard->data = unserialize($bankcard->data);
    }

    parent::attachLoad($queried_cards, $revision_id = FALSE);
  }

  /**
   * Deletes multiple bank cards by ID.
   *
   * @param $bankcard_ids
   *   An array of bank card IDs to delete.
   * @param $transaction
   *   An optional transaction object.
   * @param $entity_context
   *   An optional entity context array that specifies the entity throgh whose
   *   bank card reference field the given profiles are being deleted:
   *   - entity_type: the type of entity
   *   - entity_id: the unique ID of the entity
   *
   * @return
   *   TRUE on success, FALSE otherwise.
   */
  public function delete($bankcard_ids, DatabaseTransaction $transaction = NULL, $entity_context = array()) {
    if (!empty($bankcard_ids)) {
      $bankcards = $this->load($bankcard_ids, array());

      // Ensure the bank cards can actually be deleted.
      foreach ((array) $bankcards as $bankcard_id => $bankcard) {
        // If we received an entity context for this bank card, add it now.
        if (!empty($entity_context)) {
          $bankcard->entity_context = $entity_context;
        }

        // If the bank card cannot be deleted, remove it from the bankcards array.
        if (!cowpro_fund_bankcard_can_delete($bankcard)) {
          unset($bankcards[$bankcard_id]);
        }
      }

      // If none of the specified journals can be deleted, return FALSE.
      if (empty($bankcards)) {
        return FALSE;
      }

      parent::delete($bankcard_ids, $transaction);
      return TRUE;
    }
    else {
      return FALSE;
    }
  }
}
