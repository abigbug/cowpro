<?php

/**
 * @file
 * Definition of cowpro_fund_journal_handler_field_status.
 */

/**
 * Field handler to output the name of journal status.
 *
 * @ingroup views_field_handlers
 */
class cowpro_repayment_schedule_handler_field_status extends views_handler_field {
  function render($values) {
    include_once drupal_get_path('module', 'cowpro_issuing') . '/includes/cowpro_repayment_schedule_status.inc';
    $value = $this->get_value($values);
    $result = _cowpro_repayment_schedule_get_readable_status ( $value );

    return $result;
  }
}
