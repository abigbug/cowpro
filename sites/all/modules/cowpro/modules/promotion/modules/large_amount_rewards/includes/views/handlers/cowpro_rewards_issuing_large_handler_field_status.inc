<?php

class cowpro_rewards_issuing_large_handler_field_status extends views_handler_field {
	function render($values) {
		$status = $this->get_value($values);
                $string = "未发放";
		if ($status == 1) {
			$string = "<font style='color:#006600'>已发放</font>";
		}
		return $string;
	}
}
