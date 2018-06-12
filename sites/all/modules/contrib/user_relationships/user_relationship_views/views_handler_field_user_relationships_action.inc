<?php

/**
 * Field handler to present an 'approve' link for a given claim.
 *
 * @ingroup views_field_handlers
 */
class views_handler_field_user_relationships_action extends views_handler_field {
  function option_definition() {
    $options = parent::option_definition();
    $options['ur-type'] = array('default' => '', 'translatable' => FALSE);
    $options['ur-actions'] = array('default' => array(), 'translatable' => FALSE);
    return $options;
  }

  function options_form(&$form, &$form_state) {
    $options = array();
    foreach (user_relationships_types_load() as $rid => $relationship) {
      $options[$rid] = $relationship->name;
    }
    $form['ur-type'] = array(
      '#type' => 'radios',
      '#title' => t('User Relationship Type'),
      '#options' => $options,
      '#default_value' => $this->options['ur-type'],
    );
    $form['ur-actions'] = array(
      '#type' => 'checkboxes',
      '#title' => t('Actions'),
      '#options' => array(
        'add' => t('Add'),
        'remove' => t('Remove'),
        'requested' => t('Requested'),
        'received' => t('Received'),
      ),
      '#default_value' => $this->options['ur-actions'],
    );
    parent::options_form($form, $form_state);

    // The path is set by render_link function so don't allow to set it.
    $form['alter']['path'] = array('#access' => FALSE);
    $form['alter']['external'] = array('#access' => FALSE);
  }

  function render($values) {
    global $user;
    if ($row_uid = $this->get_value($values)) {
      $actions = user_relationships_ui_actions_between($user, user_load($row_uid), array_filter($this->options['ur-actions']), array($this->options['ur-type']));
      return implode($actions);
    }
  }
}