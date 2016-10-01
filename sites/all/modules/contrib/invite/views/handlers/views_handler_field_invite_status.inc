<?php

/**
 * @file
 * Definition of views_handler_field_invite_status.
 */

/**
 * Field handler to output the name of invite status.
 *
 * @ingroup views_field_handlers
 */
class views_handler_field_invite_status extends views_handler_field {
  function render($values) {
    $value = $this->get_value($values);

    $options = invite_get_status_options();
    return $options[$value];
  }
}
