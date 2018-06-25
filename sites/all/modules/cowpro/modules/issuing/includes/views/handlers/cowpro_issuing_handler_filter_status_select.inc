<?php
class cowpro_issuing_handler_filter_status_select extends views_handler_filter_in_operator {

	function get_value_options() {
		include_once drupal_get_path('module', 'cowpro_issuing') . '/includes/cowpro_issuing_status.inc';

		$this->value_title = '贷款状态';
		$options = _cowpro_issuing_get_status_options();
		$this->value_options = $options;
		return $options;
	}
}