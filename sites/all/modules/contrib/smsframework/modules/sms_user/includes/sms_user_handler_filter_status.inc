<?php

/**
 * @file
 * Views handler to filter sms number status.
 */

/**
 * Filter by phone validation status
 *
 * @ingroup views_field_handlers
 */
class sms_user_handler_filter_status extends views_handler_filter_in_operator {
  /**
   * {@inheritdoc}
   */
  function get_value_options() {
    if (!isset($this->value_options)) {
      $this->value_title = t('Status');
      $this->value_options = array(
        SMS_USER_PENDING => t('Pending'),
        SMS_USER_CONFIRMED => t('Confirmed'),
      );
    }
  }

  /**
   * {@inheritdoc}
   */
  function value_form(&$form, &$form_state) {
    parent::value_form($form, $form_state);
    $form['value']['#type'] = 'select';
  }
}