<?php
class cowpro_userpoints_txn_handler_filter_status_select extends views_handler_filter_in_operator {

	function get_value_options() {
		$this->value_title = '状态';
		$options = userpoints_txn_status();
		$this->value_options = $options;
		return $options;
	}
}