<?php
/**
 * Field handler to output the name of files turnover.
 *
 * @ingroup views_field_handlers
 */
class jiupaipay_files_data_handler_field_turnover extends views_handler_field {
  function render($values) {
    $value = $this->get_value($values);
    $output = '￥' . number_format($value, 2);
    return $output;
  }
}
