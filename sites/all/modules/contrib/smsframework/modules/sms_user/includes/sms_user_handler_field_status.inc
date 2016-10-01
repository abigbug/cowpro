<?php

/**
 * @file
 * Views handler to display the sms number status.
 */

/**
 * Field handler to show the sms number status.
 *
 * @ingroup views_field_handlers
 */
class sms_user_handler_field_status extends views_handler_field {
  /**
   * {@inheritdoc}
   */
  function render($values) {
    $status = @$values->{$this->field_alias};
    switch ($status) {
      case SMS_USER_PENDING: return t('Pending');
      case SMS_USER_CONFIRMED: return t('Confirmed');
      default: return '';
    }
  }
}
