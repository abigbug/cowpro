<?php
class cowpro_fund_journal_handler_filter_status extends views_handler_filter_in_operator {

	function get_value_options() {
		$options = array();
		$options[1] = '成功';
		$options[0] = '失败';
		$options[2] = '流标返款';
		$options[99] = '未知';

		$this->value_title = '结果';
		$this->value_options = $options;
	}
}