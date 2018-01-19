<?php
/**
 * Field handler to output the name of files type.
 *
 * @ingroup views_field_handlers
 */
class jiupaipay_files_data_handler_field_business_type extends views_handler_field {
  function render($values) {
    include_once drupal_get_path('module', 'jiupaipay') . '/includes/jiupaipay.business.type.inc';
    $options = _jiupaipay_get_type_options();
    $value = $this->get_value($values);
    return $options[$value];
  }
}