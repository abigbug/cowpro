<?php

/**
 * @file
 * SMS Framework Message Tracking feature module: views
 *
 * @package sms
 * @subpackage sms_track
 */

/**
 * Implements hook_handler_field().
 */
class sms_track_handler_field_gateway extends views_handler_field {
  /**
   * {@inheritdoc}
   */
  function render($values) {
    $options_z = $values->{$this->field_alias};
    if (!empty($options_z)) {
      $options = unserialize($options_z);
      if (is_array($options) && array_key_exists('gateway', $options)) {
        return $options['gateway'];
      }
      else {
        return t('n/a');
      }
    }
  }
}
