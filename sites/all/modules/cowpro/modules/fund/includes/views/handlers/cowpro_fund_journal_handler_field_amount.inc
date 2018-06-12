<?php

/**
 * @file
 * Definition of cowpro_fund_journal_handler_field_amount.
 */

/**
 * Field handler to output the name of journal status.
 *
 * @ingroup views_field_handlers
 */
class cowpro_fund_journal_handler_field_amount extends views_handler_field {
  function render($values) {

    $value = $this->get_value($values);
    $output = '￥' . number_format($value, 2);
    return $output;
  }
}
