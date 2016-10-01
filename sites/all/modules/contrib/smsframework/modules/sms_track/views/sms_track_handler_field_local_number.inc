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
class sms_track_handler_field_local_number extends views_handler_field {
  /**
   * {@inheritdoc}
   */
  function render($values) {
    $options_z = $values->{$this->field_alias};
    if (!empty($options_z)) {
      $options = unserialize($options_z);
      if (is_array($options)) {
        if (array_key_exists('receiver', $options)) {
          return $options['receiver'];
        }
        elseif (array_key_exists('sender', $options)) {
          return $options['sender'];
        }
      }
      return t('n/a');
    }
  }
}
