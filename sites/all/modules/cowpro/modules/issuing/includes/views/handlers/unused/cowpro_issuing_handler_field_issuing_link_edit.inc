<?php

/**
 * Field handler to present an issuing edit link.
 */
class cowpro_issuing_handler_field_issuing_link_edit extends cowpro_issuing_handler_field_issuing_link {
  function construct() {
    parent::construct();

    //$this->additional_fields['uid'] = 'uid';
  }

  function render($values) {
    // Ensure the user has access to delete this issuing.
    //$issuing = cowpro_issuing_new();
    $issuing_id = $this->get_value($values, 'entity_id');
    /*
    $issuing->uid = $this->get_value($values, 'uid');

    if (!cowpro_issuing_access('update', $issuing)) {
    	return;
    }*/

    $text = !empty($this->options['text']) ? $this->options['text'] : t('edit');

    return l($text, 'cowpro/issuing/' . $issuing_id . '/edit', array('query' => drupal_get_destination()));
  }
}
