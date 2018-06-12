<?php

/**
 * @file
 * The controller for the repayment schedule entity containing the CRUD operations.
 */

/**
 * The controller class for 还款计划表 contains methods for the 还款计划表
 * CRUD operations. The load method is inherited from the default controller.
 */
class CowProRepaymentScheduleEntityController extends DrupalCowProEntityController {

  /**
   * 创建“还款计划表”
   *
   * @param array $values
   *   An array of values to set, keyed by property name.
   *
   * @return
   *   A cowpro repayment schedule object with all default fields initialized.
   */
  public function create(array $values = array()) {
    $values += array(
      'schedule_id' => NULL,
    	'payer_uid' => -1,
    	'receiver_uid' => -1,
    	'paid_amount' => 0,
    	'received_amount' => 0,
      'status' => 'WAITING_FOR',
      'created' => '',
      'changed' => '',
    	'data' => array(),
    );
    $hook = 'cowpro_repayment_schedule_create';
    foreach (module_implements($hook) as $module) {
    	$values = module_invoke($module, $hook, $values);
    }

    return parent::create($values);
  }

  /**
   * 保存“还款计划表”
   *
   * When saving a cowpro repayment schedule without an ID, this function will create a new
   * repayment schedule at that time.
   *
   * @param $journal
   *   The full repayment schedule object to save.
   * @param $transaction
   *   An optional transaction object.
   *
   * @return
   *   SAVED_NEW or SAVED_UPDATED depending on the operation performed.
   */
  public function save($repayment, DatabaseTransaction $transaction = NULL) {
    if (!isset($transaction)) {
      $transaction = db_transaction();
      $started_transaction = TRUE;
    }

    try {
      // Determine if we will be inserting a new repayment.
      $repayment->is_new = empty($repayment->schedule_id);

      // Set the timestamp fields.
      if ($repayment->is_new && empty($repayment->created)) {
        $repayment->created = REQUEST_TIME;
      }
      else {
        // Otherwise if the repayment is not new but comes from an entity_create()
        // or similar function call that initializes the created timestamp and
        // uid value to empty strings, unset them to prevent destroying existing
        // data in those properties on update.
        if ($repayment->created === '') {
          unset($repayment->created);
        }
      }

      $repayment->changed = REQUEST_TIME;

      $hook = 'cowpro_repayment_schedule_save';
      foreach (module_implements($hook) as $module) {
      	$repayment = module_invoke($module, $hook, $repayment);
      }

      return parent::save($repayment, $transaction);
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
   * Unserializes the data property of loaded repayment schedule.
   */
  public function attachLoad(&$queried_repayments, $revision_id = FALSE) {
    foreach ($queried_repayments as $journal_id => &$repayment) {
    	$repayment->data = unserialize($repayment->data);

      $hook = 'cowpro_repayment_schedule_load';
      foreach (module_implements($hook) as $module) {
      	$repayment = module_invoke($module, $hook, $repayment);
      }
    }

    // Call the default attachLoad() method. This will add fields and call
    // hook_cowpro_repayment_schedule_load().
    parent::attachLoad($queried_repayments, $revision_id);
  }

  /**
   * Deletes multiple repayment schedules by ID.
   *
   * @param $repayment_ids
   *   An array of repayment schedule IDs to delete.
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
  public function delete($repayment_ids, DatabaseTransaction $transaction = NULL, $entity_context = array()) {
    if (!empty($repayment_ids)) {
      $repayments = $this->load($repayment_ids, array());

      // Ensure the repayment schedules can actually be deleted.
      foreach ((array) $repayments as $repayment_id => $repayment) {
        // If we received an entity context for this repayment, add it now.
        if (!empty($entity_context)) {
          $repayment->entity_context = $entity_context;
        }

        // If the repayment cannot be deleted, remove it from the repayment schedules array.
        if (!cowpro_repayment_schedule_can_delete($repayment)) {
          unset($repayments[$repayment_id]);
        }
      }

      // If none of the specified repayment schedules can be deleted, return FALSE.
      if (empty($repayments)) {
        return FALSE;
      }

      parent::delete($repayment_ids, $transaction);
      return TRUE;
    }
    else {
      return FALSE;
    }
  }
}
