<?php

/**
 * Area handler to display the empty text message for cowpro repayment schedule.
 */
class cowpro_repayment_schedule_handler_area_empty_text extends views_handler_area {

  function option_definition() {
    $options = parent::option_definition();

    return $options;
  }

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
  }

  public function render($empty = FALSE) {
    // If the View contains exposed filter input, the empty message indicates
    // no cowpro fund matched the search criteria.
    $exposed_input = $this->view->get_exposed_input();

    if (!empty($exposed_input)) {
      return t('No cowpro repayment schedule match your search criteria.');
    }

    // Otherwise display the empty text indicating no cowpro repayment schedule have
    // been created yet
    return t('No cowpro repayment schedule have been created yet.');
  }
}
