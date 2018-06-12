<?php

/**
 * @file
 * User Relationships admin settings and config forms
 */

/**
 * Main settings
 */
function user_relationships_admin_settings() {
  $form['settings'] = array(
    '#type' => 'vertical_tabs',
  );

  $form['general'] = array(
    '#type'   => 'fieldset',
    '#title'  => t('General'),
    '#weight' => -10,
    '#group' => 'settings',
  );
  $form['general']['user_relationships_allow_multiple'] = array(
    '#type'           => 'checkbox',
    '#title'          => t('Allow multiple relationships'),
    '#description'    => t('If checked, a user may create multiple relationships (each relationship of a different type) with another user.'),
    '#default_value'  => variable_get('user_relationships_allow_multiple', 1),
  );
  $form['general']['user_relationships_show_direct_links'] = array(
    '#type'           => 'checkbox',
    '#title'          => t('Show a separate link per relationship type'),
    '#description'    => t("On a user's page, show a separate link for each available relationship type (instead of the generic 'Create a relationship' link)."),
    '#default_value'  => variable_get('user_relationships_show_direct_links', 1),
  );
  $form['general']['user_relationships_show_user_pictures'] = array(
    '#type'           => 'checkbox',
    '#title'          => t("Show user pictures on relationship pages"),
    '#description'    => t("Show a picture next to each user's name on 'My relationships' pages."),
    '#default_value'  => variable_get('user_relationships_show_user_pictures', 0),
  );
  $form['general']['user_relationships_allow_auto_approve'] = array(
    '#type'           => 'checkbox',
    '#title'          => t('Allow users to auto approve'),
    '#description'    => t('Provide users with an option to automatically approve all requested relationships.'),
    '#default_value'  => variable_get('user_relationships_allow_auto_approve', 0),
  );
  $form['general']['user_relationships_relationships_per_page'] = array(
    '#type'           => 'textfield',
    '#title'          => t('Relationships per page'),
    '#size'           => 4,
    '#description'    => t('Number of relationships to show per page. If set to 0 all will be shown.'),
    '#default_value'  => variable_get('user_relationships_relationships_per_page', 16),
    '#validate'       => array('user_relationships_setting_validation' => array(array(
      'is_numeric' => array('msg' => t('The relationships per page setting is not an integer'))
    )))
  );
  $form['positioning'] = array(
    '#type'   => 'fieldset',
    '#title'  => t('AJAX Popup Positioning'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#description' => t('Some themes may require repositioning of AJAX confirmation dialogs. You may use these controls to set where the popup appears on the page or in relation to the mouse cursor.'),
    '#group' => 'settings',
  );
  $form['positioning']['user_relationships_enable_ajax_popups'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show AJAX confirmation popups'),
    '#default_value' => variable_get('user_relationships_enable_ajax_popups', 0),
    '#description' => t('Other popup settings below will only take effect if popups are enabled.')
  );
  $form['positioning']['user_relationships_position'] = array(
    '#type' => 'select',
    '#title' => t("Elaboration form's css position"),
    '#default_value' => variable_get('user_relationships_position', 'absolute'),
    '#options' => array(
      'absolute' => t('Mouse cursor'),
      'fixed' => t('Fixed'),
    ),
    '#description' => t('Sets the css <em>position</em> property of AJAX confirmation popups.'),
  );
  $form['positioning']['user_relationships_left'] = array(
    '#type' => 'textfield',
    '#title' => t("Elaboration form's css left value"),
    '#default_value' => variable_get('user_relationships_left', '0'),
    '#size' => 4,
    '#description' => t("Sets the css <em>left</em> property of AJAX confirmation popups. Try the value of 0 for 'Mouse cursor', or 0.5 for 'Fixed'. You may enter a distance in pixels, or as a % using a value 1 or less. Relative positioning requires a fixed position."),
  );
  $form['positioning']['user_relationships_top'] = array(
    '#type' => 'textfield',
    '#title' => t("Elaboration form's css top value"),
    '#default_value'  => variable_get('user_relationships_top', '0'),
    '#size' => 4,
    '#description' => t("Sets the css <em>top</em> property of AJAX confirmation popups. Try the value of 0 for 'Mouse cursor', or 0.4 for 'Fixed'. You may enter a distance in pixels, or as a % using a value 1 or less. Relative positioning requires a fixed position."),
  );

  $form['messages'] = array(
    '#type'         => 'fieldset',
    '#title'        => t('Custom Screen Messages'),
    '#weight'       => 0,
    '#description'  => t('Customize the confirmation messages displayed to users when specific relationship events occur.'),
    '#group' => 'settings',
  );

  $form['messages']['user_relationships_requests_link'] = array(
    '#type' => 'textfield',
    '#title' => t('Path to relationship requests'),
    '#default_value'  => variable_get('user_relationships_requests_link', 'relationships/received'),
    '#description' => t("Only change this setting if a user's pending relationship requests have a different location than the default path (relationships/received)"),
  );

  $form['messages']['messages_settings'] = array(
    '#type' => 'vertical_tabs',
  );

  $default_messages = _user_relationships_default_messages(array());
  _user_relationships_message_settings_form($form['messages'], $default_messages);

  //options for author pane integration
  if (function_exists('author_pane_api') && author_pane_api() == '2') {
    $rtypes = user_relationships_types_load();
    $form['author_pane'] = array(
      '#type'   => 'fieldset',
      '#title'  => t('Author Pane'),
      '#collapsible' => TRUE,
      '#group' => 'settings',
    );
    $form['author_pane']['user_relationships_enable_author_pane'] = array(
      '#type'           => 'checkbox',
      '#title'          => t('Show links in Author Pane'),
      '#description'    => t('Check if you wish to show add/remove relationship links in Author Pane.'),
      '#default_value'  => variable_get('user_relationships_enable_author_pane', 0),
    );
    // Since AP supports only one link per module, need to pick one relationship type
    if (count($rtypes)) {
      $options = array();
      foreach ($rtypes as $rtype) {
        $options[$rtype->rtid] = $rtype->name;
      }
      $form['author_pane']['user_relationships_author_pane_rtids'] = array(
        '#type' => 'select',
        '#multiple' => TRUE,
        '#title' => t('Relationship types to use'),
        '#default_value' => variable_get('user_relationships_author_pane_rtids', 'absolute'),
        '#options' => $options,
        '#description' => t('The chosen relationship types will be used for add/remove links.'),
      );
    }
  }
  return system_settings_form($form);
}


/**
 * Relationship type edit page.
 */
function user_relationships_admin_type_edit($form, &$form_state, $relationship_type = NULL) {
  if (!$relationship_type) {
    drupal_set_title(t('Add relationship type'));
  }
  else {
    drupal_set_title(t('Edit @name relationship type', array('@name' => $relationship_type->name)));
  }

  $form['tabs'] = array(
    '#type' => 'vertical_tabs',
  );

  $form['name'] = array(
    '#type'           => 'textfield',
    '#title'          => t('Name'),
    '#maxlength'      => 255,
    '#default_value'  => isset($relationship_type) ? $relationship_type->name : NULL,
    '#description'    => t("Example: buddy, friend, coworker, spouse."),
    '#required'       => TRUE,
    '#weight'         => -10,
  );
  $form['machine_name'] = array(
    '#type' => 'machine_name',
    '#default_value' => isset($relationship_type) ? $relationship_type->machine_name : NULL,
    '#maxlength' => 255,
    '#machine_name' => array(
      'exists' => 'user_relationships_type_machine_name_load',
    ),
    '#weight' => -9,
  );
  $form['requires_approval'] = array(
    '#type'           => 'checkbox',
    '#title'          => t('Requires Approval'),
    '#default_value'  => (isset($relationship_type->requires_approval) ? $relationship_type->requires_approval : 1),
    '#description'    => t('Check this if the requestee must approve the relationship'),
    '#weight'         => -8,
  );
  $form['expires_val'] = array(
    '#title'          => t('Request expires in'),
    '#field_suffix'   => t('days'),
    '#type'           => 'textfield',
    '#size'           => 4,
    '#default_value'  => isset($relationship_type->expires_val) ? $relationship_type->expires_val : 0,
    '#description'    => t('After how many days should a request of this type be removed? (0 for never)'),
    '#weight'         => -7,
    '#states'         => array(
      'visible'         => array(
        ':input[name=requires_approval]' => array('checked' => TRUE),
      ),
    ),
  );
  $form['is_oneway'] = array(
    '#type'           => 'checkbox',
    '#title'          => t('This is a one-way relationship'),
    '#default_value'  => isset($relationship_type) ? $relationship_type->is_oneway : NULL,
    '#description'    => t('This relationship should only go one direction. This might be a manager or teacher.'),
    '#weight'         => -6,
  );
  $form['is_reciprocal'] = array(
    '#type'           => 'checkbox',
    '#title'          => t('This one-way relationship can be reciprocated'),
    '#default_value'  => isset($relationship_type) ? $relationship_type->is_reciprocal : NULL,
    '#description'    => t('The user who receives this request can create an additional one-way relationship back to the requester. This might be a follower or subscriber.'),
    '#weight'         => -5,
    '#states'         => array(
      'visible'         => array(
        ':input[name=is_oneway]' => array('checked' => TRUE),
      ),
    ),
  );

  $form['branding'] = array(
    '#type' => 'fieldset',
    '#title' => t('Branding'),
    '#group' => 'tabs',
  );

  $form['branding']['plural_name'] = array(
    '#type'           => 'textfield',
    '#title'          => t('Plural name'),
    '#maxlength'      => 255,
    '#default_value'  => isset($relationship_type->plural_name) ? $relationship_type->plural_name : NULL,
    '#description'    => t("Example: buddies, friends, coworkers, spouses."),
    '#weight'         => 2,
  );

  $form['branding']['name_capitalized'] = array(
    '#type'           => 'textfield',
    '#title'          => t('Capitalized name'),
    '#maxlength'      => 255,
    '#default_value'  => isset($relationship_type) ? $relationship_type->name_capitalized : NULL,
    '#description'    => t("Example: buddies, friends, coworkers, spouses."),
    '#weight'         => 6,
  );

  $form['branding']['plural_name_capitalized'] = array(
    '#type'           => 'textfield',
    '#title'          => t('Capitalized plural name'),
    '#maxlength'      => 255,
    '#default_value'  => isset($relationship_type) ? $relationship_type->plural_name_capitalized : NULL,
    '#description'    => t("Example: buddies, friends, coworkers, spouses."),
    '#weight'         => 10,
  );

  // #states doesn't work on a vertical tab fieldset, hide each input element
  // separately.
  $form['reverse_branding'] = array(
    '#type' => 'fieldset',
    '#title' => t('One-way reverse branding'),
    '#group' => 'tabs',
    '#description' => t('One-way reversed branding is only used when this relationship type only goes one way. Then, these names are used when displaying relationships initiated by other users.'),
    // Doesn't work properly yet.
    '#states'         => array(
      'visible'         => array(
        ':input[name=is_oneway]' => array('checked' => TRUE),
      ),
    ),
  );

  $form['reverse_branding']['reverse_name'] = array(
    '#type'           => 'textfield',
    '#title'          => t('Name'),
    '#maxlength'      => 255,
    '#default_value'  => isset($relationship_type) ? $relationship_type->reverse_name : NULL,
    '#description'    => t("Example: buddies, friends, coworkers, spouses."),
    '#weight'         => 0,
  );

  $form['reverse_branding']['reverse_plural_name'] = array(
    '#type'           => 'textfield',
    '#title'          => t('Plural name'),
    '#maxlength'      => 255,
    '#default_value'  => isset($relationship_type) ? $relationship_type->reverse_plural_name : NULL,
    '#description'    => t("Example: buddies, friends, coworkers, spouses."),
    '#weight'         => 4,
  );

  $form['reverse_branding']['reverse_name_capitalized'] = array(
    '#type'           => 'textfield',
    '#title'          => t('Capitalized name'),
    '#maxlength'      => 255,
    '#default_value'  => isset($relationship_type) ? $relationship_type->reverse_name_capitalized : NULL,
    '#description'    => t("Example: buddies, friends, coworkers, spouses."),
    '#weight'         => 8,
  );

  $form['reverse_branding']['reverse_plural_name_capitalized'] = array(
    '#type'           => 'textfield',
    '#title'          => t('Capitalized plural name'),
    '#maxlength'      => 255,
    '#default_value'  => isset($relationship_type) ? $relationship_type->reverse_plural_name_capitalized : NULL,
    '#description'    => t("Example: buddies, friends, coworkers, spouses."),
    '#weight'         => 12,
  );


  $form['rtid'] = array(
    '#type'   => 'value',
    '#value'  => isset($relationship_type->rtid) ? (int) $relationship_type->rtid : NULL,
  );
  $form['action'] = array(
    '#type'   => 'value',
    '#value'  => (isset($relationship_type->rtid) ? 'edit' : 'add'),
  );

  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array(
    '#type'   => 'submit',
    '#value'  => (isset($relationship_type->rtid) ? t('Save relationship type') : t('Add relationship type')),
    '#weight' => 0,
  );
  if (module_exists('i18n_string')) {
    $form['actions']['translate'] = array(
      '#type'   => 'submit',
      '#name'   => 'save_translate',
      '#value'  => (isset($relationship_type->rtid) ? t('Save and translate') : t('Add and translate')),
      '#weight' => 5,
    );
  }


  return $form;
}


/**
 * Relationship type delete page.
 */
function user_relationships_admin_type_delete($form, &$form_state, $relationship_type = NULL) {
  if ($relationship_type) {
    $form['rtid'] = array(
      '#type'   => 'value',
      '#value'  => (int) $relationship_type->rtid,
    );

    return confirm_form(
      $form,
      t('Are you sure you want to delete @rel_name?', user_relationships_type_translations($relationship_type)),
      'admin/config/people/relationships',
      t('This action cannot be undone.'),
      t('Delete'), t('Cancel')
    );
  }
  else {
    drupal_set_message(user_relationships_get_message('non_existent_type'));
    drupal_goto('admin/config/people/relationships');
  }
}

/**
 * Validate the submitted relationship type
 */
function user_relationships_admin_type_edit_validate($form, &$form_state) {
  $select = db_select('user_relationship_types', 'urt')
    ->fields('urt', array('name'))
    ->where("LOWER(name) = LOWER(:name)", array(':name' => $form_state['values']['name']));
  if (isset($form_state['values']['rtid'])) {
    $select->condition('rtid', $form_state['values']['rtid'], '<>');
  }
  if ($select->execute()->fetchField()) {
    form_set_error('name', t('%name has already been used.', array('%name' => $form_state['values']['name'])));
  }

  $expire = $form_state['values']['expires_val'];
  if (!is_numeric($expire) || (int) $expire < 0) {
    form_set_error('expires_val', t('Expiration period must be an integer greater than or equal to 0.'));
  }
}

/**
 * Process the relationship edit page form submission.
 */
function user_relationships_admin_type_edit_submit($form, &$form_state) {
  $relationship_type = (object) $form_state['values'];

  user_relationships_type_save($relationship_type);

  if ($form_state['values']['action'] == 'add') {
    drupal_set_message(t('Relationship @rel_name has been added.', user_relationships_type_translations($relationship_type)));
    watchdog(
      'u_relationship',
      'User Relationships form: relationship @rel_name added.', user_relationships_type_translations($relationship_type),
      WATCHDOG_NOTICE,
      l(t('view'), 'admin/user/user_relationship/types/' . $relationship_type->rtid . '/edit')
    );
  }
  else {
    drupal_set_message(t('Relationship @rel_name has been updated.', user_relationships_type_translations($relationship_type)));
    watchdog(
      'u_relationship',
      'User Relationships form: relationship @rel_name updated.', user_relationships_type_translations($relationship_type),
      WATCHDOG_NOTICE,
      l(t('view'), 'admin/config/people/relationships/' . $relationship_type->rtid . '/edit')
    );
  }

  $form_state['redirect'] = 'admin/config/people/relationships';
  if (module_exists('i18n_string') && $form_state['triggering_element']['#name'] == 'save_translate') {
    $form_state['redirect'] = 'admin/config/people/relationships/' . $relationship_type->rtid . '/translate';
  }
}


/**
 * Process relationship delete form submission.
 */
function user_relationships_admin_type_delete_submit($form, &$form_state) {
  $relationship_type = user_relationships_type_load($form_state['values']['rtid']);

  user_relationships_type_delete($form_state['values']['rtid']);

  // #371311 force menu rebuild
  drupal_static_reset('user_relationships_types_load');
  menu_rebuild();

  drupal_set_message(t('Relationship @rel_name has been deleted.', user_relationships_type_translations($relationship_type)));
  watchdog(
    'u_relationship',
    'User Relationships form: relationship @rel_name deleted.', user_relationships_type_translations($relationship_type),
    WATCHDOG_NOTICE
  );

  $form_state['redirect'] = 'admin/config/people/relationships';
}

/**
 * Relationship Types List
 */
function user_relationships_admin_types_list_page() {
  $relationship_types = user_relationships_types_load();

  $headers = array(t('Name'), t('Type'), t('Requires Approval'), t('Operations'));
  $rows = array();

  foreach ($relationship_types as $relationship) {

    $approval = t('No');
    if ($relationship->requires_approval) {
      if ($relationship->expires_val) {
        $approval = format_plural($relationship->expires_val, 'Yes (within 1 day)', 'Yes (within @count days)');
      }
      else {
        $approval = t('Yes');
      }
    }

    $rows[$relationship->rtid] = array(
      check_plain(user_relationships_type_get_name($relationship)),
      ($relationship->is_oneway ? ($relationship->is_reciprocal ? t('Reciprocal') : t('One-way')) : t('Mutual')),
      $approval,
      l(t('edit'),     "admin/config/people/relationships/{$relationship->rtid}/edit") . ' | ' .
      l(t('delete'),   "admin/config/people/relationships/{$relationship->rtid}/delete")
    );
  }

  $page['relationships'] = array(
    '#type'   => 'fieldset',
    '#title'  => t('Relationship Types'),
    '#weight' => 0,
  );
  $page['relationships']['list'] = array(
    '#theme' => 'table',
    '#header' => $headers,
    '#rows' => $rows,
    '#empty' => t('No relationships available.'),
  );

  drupal_alter('user_relationships_types_list', $page);

  return $page;
}


/**
 * Helper function to build the settings form for the notification messages
 */
function _user_relationships_message_settings_form(&$form, $defaults = array()) {

  $replaceables = array(
    '!requester',
    '!requestee',
    '%relationship_name',
    '%relationship_plural_name',
    '!pending_relationship_requests',
  );

  $translations = _user_relationships_default_message_key_translations();
  foreach ($defaults as $key => $value) {
    if (is_array($value)) {
      $form[$key] = array(
        '#type'         => 'fieldset',
        '#title'        => isset($translations[$key]) ? $translations[$key] : t(drupal_ucfirst(str_replace('_', ' ', $key))),
        '#collapsible'  => TRUE,
        '#collapsed'    => TRUE,
        '#description'  => t('The following tokens are available for use in your custom messages: @replaceables.', array('@replaceables' => implode($replaceables, ', '))),
        '#group'        => 'messages_settings',
      );
      _user_relationships_message_settings_form($form[$key], $value);
    }
    else {
      $form["user_relationships_msg_{$key}"] = array(
        '#type'           => 'textfield',
        '#title'          => isset($translations[$key]) ? $translations[$key] : t(drupal_ucfirst(str_replace('_', ' ', $key))),
        '#default_value'  => variable_get("user_relationships_msg_{$key}", $value)
      );
    }
  }
}
