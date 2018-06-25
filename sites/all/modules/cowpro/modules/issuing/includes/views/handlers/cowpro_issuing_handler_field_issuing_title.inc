<?php

/**
 * @file
 * Contains the basic issuing field handler.
 */

/**
 * Field handler to provide simple renderer that allows linking to an issuing.
 */
class cowpro_issuing_handler_field_issuing_title extends views_handler_field {

  function render($values) {
    $nid = $this->get_value($values);
    $title = node_load($nid)->title;
    $link = 'node/' . $nid;
    return l($this->sanitize_value($title), $link);
  }
}
