<?php

/**
 * @file
 * Definition of entityqueue_handler_argument_subqueue_id.
 */

/**
 * Argument handler to accept a user id.
 *
 * @ingroup views_argument_handlers
 */
class entityqueue_handler_argument_subqueue_id extends views_handler_argument_numeric {
  /**
   * Override the behavior of title(). Get the name of the user.
   *
   * @return array
   *    A list of usernames.
   */
  function title_query() {
    $this->ensure_my_table();
    $titles = array();

    $result = db_query("SELECT esq.label FROM {entityqueue_subqueue} esq WHERE esq.subqueue_id IN (:sqids)", array(':sqids' => $this->value));
    foreach ($result as $term) {
      $titles[] = check_plain($term->label);
    }
    return $titles;
  }
}
