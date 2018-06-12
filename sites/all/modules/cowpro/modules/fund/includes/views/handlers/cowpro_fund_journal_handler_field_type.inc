<?php

/**
 * @file
 * Definition of cowpro_fund_journal_handler_field_type.
 */

/**
 * Field handler to output the name of journal type.
 *
 * @ingroup views_field_handlers
 */
class cowpro_fund_journal_handler_field_type extends views_handler_field {
  function render($values) {
		include_once drupal_get_path('module', 'cowpro_fund') . '/includes/cowpro_fund_type.inc';

		$options = _cowpro_fund_get_type_options();

    $value = $this->get_value($values);

    return $options[$value];
  }
}
