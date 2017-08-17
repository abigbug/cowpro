<?php

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

class cowpro_issuing_handler_field_repayment_progress extends views_handler_field {
  function render($values) {
  	$issuing_id = $this->get_value($values);

  	$conditions = array (
  			'issuing_id' => $issuing_id,
  			//'period' => $period,
  			'receiver_uid' => -1,
  			//'status' => 'WAITING_FOR',
  	);
  	$reset = FALSE;
  	$schedules = entity_load ( 'cowpro_repayment_schedule', FALSE, $conditions, $reset );
  	$paid_amount = 0;
  	$payable_amount = 0;
  	foreach ($schedules as $schedule) {
  		$paid_amount = $paid_amount + $schedule->paid_amount;
  		$payable_amount = $payable_amount + $schedule->payable_amount;
  	}
  	if ($payable_amount != 0) {
    	$progress = (int)(($paid_amount / $payable_amount) * 100);
  	} else {
  		$progress = 0;
  	}

    return $progress;
  }
}
