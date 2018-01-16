<?php

/**
 * @file
 * The controller for the bank card entity containing the CRUD operations.
 */

/**
 * The controller class for bank card contains methods for the bank card
 * CRUD operations. The load method is inherited from the default controller.
 */
class CowproShopDeliverEntityController extends DrupalCowProEntityController {

  /**
   * Create a default cowpro shop deliver record
   *
   * @param array $values
   *   An array of values to set, keyed by property name.
   *
   * @return
   *   A bank card object with all default fields initialized.
   */
  public function create(array $values = array()) {
    $values += array(
      'deliver_id' => NULL,
    	'txn_id' => 0,
    	'status' => 0,
      'created' => '',
      'changed' => '',
    );
    return parent::create($values);
  }

  /**
   */
  public function save($deliver, DatabaseTransaction $transaction = NULL) {
    if (!isset($transaction)) {
      $transaction = db_transaction();
      $started_transaction = TRUE;
    }

    try {
      global $user;

      // Determine if we will be inserting a new deliver.
      $deliver->is_new = empty($deliver->deliver_id);

      // Set the timestamp fields.
      if ($deliver->is_new && empty($deliver->created)) {
      	$deliver->created = REQUEST_TIME;
      }
      else {
        // Otherwise if the bank card is not new but comes from an entity_create()
        // or similar function call that initializes the created timestamp and
        // uid value to empty strings, unset them to prevent destroying existing
        // data in those properties on update.
        if ($deliver->created === '') {
          unset($deliver->created);
        }
      }

      $deliver->changed = REQUEST_TIME;

      return parent::save($deliver, $transaction);
    }
    catch (Exception $e) {
      if (!empty($started_transaction)) {
        $transaction->rollback();
        watchdog_exception($this->entityType, $e);
      }
      throw $e;
    }
  }

}
