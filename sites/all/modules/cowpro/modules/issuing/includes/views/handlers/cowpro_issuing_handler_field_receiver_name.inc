<?php

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

class cowpro_issuing_handler_field_receiver_name extends views_handler_field {
  function render($values) {
    $user=user_load($this->get_value($values));
    return $user->name;
  }
}
