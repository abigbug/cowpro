<?php

/**
 * Field handler to present a link to delete an issuing.
 */
class cowpro_issuing_handler_field_issuing_link_delete extends cowpro_issuing_handler_field_issuing_link {
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

    if (!cowpro_issuing_access('delete', $issuing)) {
      return;
    }*/

    $text = !empty($this->options['text']) ? $this->options['text'] : t('delete');

    return l($text, 'cowpro/issuing/' . $issuing_id . '/delete', array('query' => drupal_get_destination()));
  }
}
