<?php

/**
 * Area handler to display the empty text message for cowpro fund.
 */
class cowpro_fund_journal_handler_area_empty_text extends views_handler_area {

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
      return '无满足条件的数据';
    }

    // Otherwise display the empty text indicating no cowpro fund have
    // been created yet
    return '无数据';
  }
}
