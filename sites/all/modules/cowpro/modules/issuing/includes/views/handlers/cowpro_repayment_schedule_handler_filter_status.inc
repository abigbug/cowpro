<?php
class cowpro_repayment_schedule_handler_filter_status extends views_handler_filter_in_operator {

	function get_value_options() {
		include_once drupal_get_path('module', 'cowpro_issuing') . '/includes/cowpro_repayment_schedule_status.inc';

		$this->value_title = '还款状态';
		$options = _cowpro_repayment_schedule_get_status_options();
		$this->value_options = $options;
	}
}