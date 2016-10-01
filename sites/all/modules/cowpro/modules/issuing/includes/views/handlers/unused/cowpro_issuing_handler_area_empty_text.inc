<?php

/**
 * Area handler to display the empty text message for issuings.
 */
class cowpro_issuing_handler_area_empty_text extends views_handler_area {

  function option_definition() {
    $options = parent::option_definition();

    // Define an option to link to an issuing add form.
    $options['add_path'] = array('default' => '');

    return $options;
  }

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    $form['add_path'] = array(
      '#type' => 'textfield',
      '#title' => t('Path to an issuing add form'),
      '#description' => t('Provide the path to an issuing add form to link to in the empty message. If blank, no link will be included.'),
      '#default_value' => $this->options['add_path'],
    );
  }

  public function render($empty = FALSE) {
    // If the View contains exposed filter input, the empty message indicates
    // no customer profiles matched the search criteria.
    $exposed_input = $this->view->get_exposed_input();

    if (!empty($exposed_input)) {
      return '没有找到满足条件的贷款.';
    }

    // Otherwise display the empty text indicating no customer profiles have
    // been created yet and provide a link to the add form if configured.
    if (!empty($this->options['add_path'])) {
      return '还没有创建贷款申请表. <a href="' . url($this->options['add_path']) . '">我要贷款</a>.';
    }
    else {
      return '还没有创建贷款申请表.';
    }
  }
}
