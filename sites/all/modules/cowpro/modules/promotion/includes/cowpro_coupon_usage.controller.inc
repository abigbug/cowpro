<?php

/**
 * @file
 * Coupon Usage controller class.
 */

/**
 * Cowpro Coupon Usage controller class.
 */
class CowproCouponUsageEntityController extends DrupalCowProEntityController {

  /**
   * Create a coupon usage record.
   *
   * @param array $values
   *   An array of values to set, keyed by property name.
   *
   * @return object
   *   A coupon usage object with all default fields initialized.
   */
  public function create(array $values = array()) {
    $values += array(
      'txn_id' => 0,
      'created' => '',
      'search_field' => '',
      'module' => '',
    );

    return parent::create($values);
  }

  /**
   * Saves a coupon usage record.
   *
   * @param object $coupon_usage
   *   The full coupon usage object to save.
   * @param \DatabaseTransaction $transaction
   *   An optional transaction object.
   *
   * @return bool|int
   *   SAVED_NEW or SAVED_UPDATED depending on the operation performed.
   */
  public function save($coupon_usage, DatabaseTransaction $transaction = NULL) {
    if (empty($coupon_usage->{$this->idKey}) || !empty($coupon_usage->is_new)) {
      // Set the creation timestamp if not set, for new entities.
      if (empty($coupon_usage->created)) {
        $coupon_usage->created = REQUEST_TIME;
      }
    }
    return parent::save($coupon_usage);
  }

  /**
   * Unserialize the data property of loaded coupon usages.
   */
  public function attachLoad(&$queried_coupon_usages, $revision_id = FALSE) {
    foreach ($queried_coupon_usages as $id => &$cowpro_coupon_usage) {
      $cowpro_coupon_usage->data = unserialize($cowpro_coupon_usage->data);
    }

    // Call the default attachLoad().
    parent::attachLoad($queried_coupon_usages, $revision_id);
  }

}
