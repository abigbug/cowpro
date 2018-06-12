<?php
class jiupaipay_files_data_handler_filter_business_type extends views_handler_filter_in_operator {
	function get_value_options() {
		include_once drupal_get_path('module', 'jiupaipay') . '/includes/jiupaipay.business.type.inc';
		$this->value_title = '业务类型';
		$options = _jiupaipay_get_type_options();
		$this->value_options = $options;
	}
}