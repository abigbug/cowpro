<?php

/**
 * @file
 * The controller for the customer profile entity containing the CRUD operations.
 */

/**
 * The controller class for fund contains methods for the fund
 * CRUD operations. The load method is inherited from the default controller.
 */
class CowProFundJournalEntityController extends DrupalCowProEntityController {

  /**
   * Create a default fund journal
   *
   * @param array $values
   *   An array of values to set, keyed by property name.
   *
   * @return
   *   A fund journal object with all default fields initialized.
   */
  public function create(array $values = array()) {
    $values += array(
      'journal_id' => NULL,
      'type' => '',
    	'internal_reference_id' => '',
    	'external_reference_id' => '',
    	'uid' => '',
    	'amount' => 0,
      'status' => 1,
      'created' => '',
      'changed' => '',
    );
    $hook = 'cowpro_fund_journal_create';
    foreach (module_implements($hook) as $module) {
    	$values = module_invoke($module, $hook, $values);
    }

    return parent::create($values);
  }

  /**
   * Saves a fund journal.
   *
   * When saving a fund journal without an ID, this function will create a new
   * fund journal at that time.
   *
   * @param $journal
   *   The full fund journal object to save.
   * @param $transaction
   *   An optional transaction object.
   *
   * @return
   *   SAVED_NEW or SAVED_UPDATED depending on the operation performed.
   */
  public function save($journal, DatabaseTransaction $transaction = NULL) {
    if (!isset($transaction)) {
      $transaction = db_transaction();
      $started_transaction = TRUE;
    }

    try {
      global $user;

      // Determine if we will be inserting a new journal.
      $journal->is_new = empty($journal->journal_id);

      // Set the timestamp fields.
      if ($journal->is_new && empty($journal->created)) {
        $journal->created = REQUEST_TIME;
      }
      else {
        // Otherwise if the profile is not new but comes from an entity_create()
        // or similar function call that initializes the created timestamp and
        // uid value to empty strings, unset them to prevent destroying existing
        // data in those properties on update.
        if ($journal->created === '') {
          unset($journal->created);
        }
        if ($journal->uid === '') {
          unset($journal->uid);
        }
      }

      $journal->changed = REQUEST_TIME;

      $hook = 'cowpro_fund_journal_save';
      foreach (module_implements($hook) as $module) {
      	$journal = module_invoke($module, $hook, $journal);
      }

      return parent::save($journal, $transaction);
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
   * Unserializes the data property of loaded journal.
   */
  public function attachLoad(&$queried_journals, $revision_id = FALSE) {
    foreach ($queried_journals as $journal_id => &$journal) {
    	$journal->data = unserialize($journal->data);

      $hook = 'cowpro_fund_journal_load';
      foreach (module_implements($hook) as $module) {
      	$journal = module_invoke($module, $hook, $fund);
      }
    }

    // Call the default attachLoad() method. This will add fields and call
    // hook_cowpro_fund_journal_load().
    parent::attachLoad($queried_journals, $revision_id = FALSE);
  }

  /**
   * Deletes multiple fund journals by ID.
   *
   * @param $journal_ids
   *   An array of fund journal IDs to delete.
   * @param $transaction
   *   An optional transaction object.
   * @param $entity_context
   *   An optional entity context array that specifies the entity throgh whose
   *   customer profile reference field the given profiles are being deleted:
   *   - entity_type: the type of entity
   *   - entity_id: the unique ID of the entity
   *
   * @return
   *   TRUE on success, FALSE otherwise.
   */
  public function delete($journal_ids, DatabaseTransaction $transaction = NULL, $entity_context = array()) {
    if (!empty($journal_ids)) {
      $journals = $this->load($journal_ids, array());

      // Ensure the customer profiles can actually be deleted.
      foreach ((array) $journals as $journal_id => $journal) {
        // If we received an entity context for this journal, add it now.
        if (!empty($entity_context)) {
          $journal->entity_context = $entity_context;
        }

        // If the journal cannot be deleted, remove it from the journals array.
        if (!cowpro_fund_journal_can_delete($journal)) {
          unset($journals[$journal_id]);
        }
      }

      // If none of the specified journals can be deleted, return FALSE.
      if (empty($journals)) {
        return FALSE;
      }

      parent::delete($journal_ids, $transaction);
      return TRUE;
    }
    else {
      return FALSE;
    }
  }
}
