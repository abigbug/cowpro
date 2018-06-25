<?php

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

class cowpro_issuing_handler_field_issuing_deadline extends views_handler_field {
  function render($values) {
    $issuing_id = $this->get_value($values);
    $deadline = db_query("SELECT DISTINCT(deadline) FROM {cowpro_repayment_schedule} WHERE issuing_id=$issuing_id AND period=period_total")->fetchField();
    if( $deadline ) {
        return date("Y/m/d", $deadline);
    }else{
        return "-";
    }
    

  }
}
