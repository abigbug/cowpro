<?php

/**
 * @file
 * Contains the basic issuing field handler.
 */

/**
 * Field handler to provide simple renderer that allows linking to an issuing.
 */
class cowpro_issuing_handler_field_issuing extends views_handler_field {
  function init(&$view, &$options) {
    parent::init($view, $options);

    if (!empty($this->options['link_to_issuing'])) {
      $this->additional_fields['issuing_id'] = 'issuing_id';
    }
  }

  function option_definition() {
    $options = parent::option_definition();

    $options['link_to_issuing'] = array('default' => FALSE);

    return $options;
  }

  /**
   * Provide the link to issuing option.
   */
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    $form['link_to_issuing'] = array(
      '#title' => t("Link this field to the issuing's administrative view page"),
      '#description' => t('This will override any other link you have set.'),
      '#type' => 'checkbox',
      '#default_value' => !empty($this->options['link_to_issuing']),
    );
  }

  /**
   * Render whatever the data is as a link to the issuing.
   *
   * Data should be made XSS safe prior to calling this function.
   */
  function render_link($data, $values) {
    if (!empty($this->options['link_to_issuing']) && $data !== NULL && $data !== '') {
      $issuing_id = $this->get_value($values, 'entity_id');
      $this->options['alter']['make_link'] = TRUE;
      $this->options['alter']['path'] = 'cowpro/issuing/' . $issuing_id;
    }

    return $data;
  }

  function render($values) {
    $value = $this->get_value($values);
    return $this->render_link($this->sanitize_value($value), $values);
  }
}
