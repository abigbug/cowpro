<?php

/**
 * Field handler to translate a customer profile type into its readable form.
 */
class cowpro_customer_handler_field_customer_profile_type extends cowpro_customer_handler_field_customer_profile {
  function render($values) {
    $type = $this->get_value($values);
    $value = cowpro_customer_profile_type_get_name($type);

    if (empty($value)) {
      $value = t('Unknown');
    }

    return $this->render_link($this->sanitize_value($value), $values);
  }
}
