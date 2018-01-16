<?php
class cowpro_shop_deliver_handler_filter_status extends views_handler_filter_in_operator {

	function get_value_options() {
		$options = array();
		$options[0] = '未处理';
		$options[1] = '已处理';

		$this->value_title = '结果';
		$this->value_options = $options;
	}
}