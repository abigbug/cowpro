<?php

/**
 * @file
 * Handler to filter for entities that are not/in the entityqueue.
 */
class entityqueue_handler_filter_in_queue extends views_handler_filter_boolean_operator {
  function query() {
    $this->ensure_my_table();
    $field_table = $this->definition['field table'];
    $field_field = $this->definition['field field'];

    $field_table_alias = FALSE;
    $tables = $this->query->table_queue;

    foreach ($tables as $info) {
      if ($info['table'] == $field_table) {
        $field_table_alias = $info['alias'];
        break;
      }
    }
    // Add the field.
    if ($field_table_alias) {
      $operator  = $this->value ? 'IS NOT NULL' : 'IS NULL';
      $condition = "$field_table_alias.$field_field $operator";

      $this->query->add_where_expression($this->options['group'], $condition);
    }
    else {
      drupal_set_message(t('In order to filter by the "in queue" property, you need to add the Entityqueue: Queue relationship.'), 'error');
    }
  }
}

