<?php

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
class cowpro_issuing_handler_field_title extends views_handler_field {
  function render($values) {
  	global $base_url;
    $output = '';
    $url = '';
    $node = node_load($this->get_value($values));
    $url .= $base_url . '/node/' . $this->get_value($values);
    $output .= l($node->title,$url);
    return $output;
  }
}
