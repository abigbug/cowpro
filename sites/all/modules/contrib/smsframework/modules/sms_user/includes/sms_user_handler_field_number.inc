<?php

/**
 * @file
 * A handler to provide displays for users' mobile phone
 *
 * @ingroup views_field_handlers
 */
class sms_user_handler_field_number extends views_handler_field {

  /**
   * {@inheritdoc}
   */
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
  }

  /**
   * {@inheritdoc}
   */
  function render($values) {
    return $values->{$this->field_alias};
  }
}