<?php
class cowpro_creditor_assignment_handler_field_amount extends views_handler_field {
	/**
	 * Get the value that's supposed to be rendered.
	 *
	 * This api exists so that other modules can easy set the values of the field
	 * without having the need to change the render method as well.
	 *
	 * @param $values An
	 *        	object containing all retrieved values.
	 * @param $field Optional
	 *        	name of the field where the value is stored.
	 */
	function get_value($values, $field = NULL) {
		// 此处与方法_cowpro_issuing_get_creditor_assignment_amount存在代码冗余
		// 需要找个方案解决冗余
		$data_array = unserialize ( $values->cowpro_repayment_schedule_data );
		$data = NULL;
		$serial = - 1;
		$result = 0;
		foreach ( $data_array as $key => $value ) {
			if ($value ['operate'] === 'creditor_assignment') {
				if ($serial < $value ['serial']) {
					$serial = $value ['serial'];
					$data = $value;
				}
			}
		}
		if ($data) {
			$result = $data ['amount'];
		}
		return $result;
	}
}
