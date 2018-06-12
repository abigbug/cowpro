<?php

/**
 * @file
 * Contains views_handler_filter_user_relationships_type_machine_name
 */

class views_handler_filter_user_relationships_type_machine_name extends views_handler_filter_in_operator {
  function get_value_options() {
    if (!isset($this->value_options)) {
      $this->value_title = t('Relationship types');
      $types = user_relationships_types_load();
      $options = array();
      foreach ($types as $type => $info) {
        $options[$info->machine_name] = t($info->name);
      }
      asort($options);
      $this->value_options = $options;
    }
  }
}
