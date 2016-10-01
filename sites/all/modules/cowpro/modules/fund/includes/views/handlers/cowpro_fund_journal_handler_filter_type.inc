<?php
class cowpro_fund_journal_handler_filter_type extends views_handler_filter_in_operator {

	function get_value_options() {
		include_once drupal_get_path('module', 'cowpro_fund') . '/includes/cowpro_fund_type.inc';

		$this->value_title = '业务类型';
		$options = _cowpro_fund_get_type_options();
		$this->value_options = $options;
	}
}