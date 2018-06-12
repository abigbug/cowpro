<?php

/**
 * @file
 * WSClient UI - implements service description management and configuration
 * screens.
 */

/**
 * Controller class for customizing the default Entity UI.
 */
class WSClientUIController extends EntityDefaultUIController {

  /**
   * Customizes menu items.
   *
   * @see EntityDefaultUIController::hook_menu()
   */
  function hook_menu() {
    $items = parent::hook_menu();

    // Add additionally need menu items to manage web service operations.
    $id_count = count(explode('/', $this->path)) + 1;
    $items[$this->path . '/manage/%wsclient_service/add/operation'] = array(
      'title' => 'Add operation',
      'page callback' => 'drupal_get_form',
      'page arguments' => array('wsclient_ui_operation', $id_count, NULL, 'add'),
      'access arguments' => array('administer web services'),
      'file' => 'wsclient_ui.inc',
      'file path' => drupal_get_path('module', 'wsclient_ui'),
    );
    $op_count = $id_count + 2;
    $items[$this->path . '/manage/%wsclient_service/operation/%wsclient_ui_operation'] = array(
      'title' => 'Edit operation',
      'page callback' => 'drupal_get_form',
      'page arguments' => array('wsclient_ui_operation', $id_count, $op_count, 'edit'),
      'load arguments' => array($id_count),
      'access arguments' => array('administer web services'),
      'file' => 'wsclient_ui.inc',
      'file path' => drupal_get_path('module', 'wsclient_ui'),
    );
    $items[$this->path . '/manage/%wsclient_service/operation/%wsclient_ui_operation/delete'] = array(
      'title' => 'Delete operation',
      'page callback' => 'drupal_get_form',
      'page arguments' => array('wsclient_ui_operation_delete', $id_count, $op_count),
      'load arguments' => array($id_count),
      'access arguments' => array('administer web services'),
      'file' => 'wsclient_ui.inc',
      'file path' => drupal_get_path('module', 'wsclient_ui'),
    );
    // Menu items to manage data types.
    $items[$this->path . '/manage/%wsclient_service/add/type'] = array(
      'title' => 'Add data type',
      'page callback' => 'drupal_get_form',
      'page arguments' => array('wsclient_ui_type', $id_count, NULL, 'add'),
      'access arguments' => array('administer web services'),
      'file' => 'wsclient_ui.inc',
      'file path' => drupal_get_path('module', 'wsclient_ui'),
    );
    $items[$this->path . '/manage/%wsclient_service/type/%wsclient_ui_type'] = array(
      'title' => 'Edit data type',
      'page callback' => 'drupal_get_form',
      'page arguments' => array('wsclient_ui_type', $id_count, $op_count, 'edit'),
      'load arguments' => array($id_count),
      'access arguments' => array('administer web services'),
      'file' => 'wsclient_ui.inc',
      'file path' => drupal_get_path('module', 'wsclient_ui'),
    );
    $items[$this->path . '/manage/%wsclient_service/type/%wsclient_ui_type/delete'] = array(
      'title' => 'Delete data type',
      'page callback' => 'drupal_get_form',
      'page arguments' => array('wsclient_ui_type_delete', $id_count, $op_count),
      'load arguments' => array($id_count),
      'access arguments' => array('administer web services'),
      'file' => 'wsclient_ui.inc',
      'file path' => drupal_get_path('module', 'wsclient_ui'),
    );

    // Overrides the default description of the top level menu item.
    $items[$this->path]['description'] = 'Manage Web Service Descriptions for Web service client.';
    return $items;
  }
}

/**
 * Provides a form to add, edit and clone web service descriptions.
 */
function wsclient_service_form($form, &$form_state, $service, $op = 'edit') {
  if ($op == 'clone') {
    $service->label .= ' (cloned)';
    $service->name .= '_clone';
  }
  $type_info = wsclient_get_types();
  if (empty($type_info)) {
    drupal_set_message(t('No service types were found, please enable a module that provides a service type.'), 'warning');
  }
  $types = array();
  foreach ($type_info as $type => $info) {
    $types[$type] = $info['label'];
  }

  $form['label'] = array(
    '#type' => 'textfield',
    '#title' => 'Label',
    '#default_value' => $service->label,
    '#required' => TRUE,
    '#description' => t('The human-readable name.'),
  );
  $form['name'] = array(
    '#type' => 'machine_name',
    '#default_value' => isset($service->name) ? $service->name : '',
    '#maxlength' => 32,
    '#machine_name' => array(
      'exists' => 'wsclient_service_load',
      'source' => array('label'),
    ),
    '#required' => TRUE,
    '#description' => t('The machine-readable name of this service is used internally to identify the service. This name must contain only lowercase letters, numbers, and underscores and must be unique.'),
    '#element_validate' => array('form_validate_machine_name', 'entity_ui_validate_machine_name'),
  );
  $form['url'] = array(
    '#type' => 'textfield',
    '#title' => 'URL',
    '#default_value' => $service->url,
    '#required' => TRUE,
    '#description' => t('The URL of the web service.'),
    '#element_validate' => array('wsclient_ui_element_url_validate'),
  );
  $form['type'] = array(
    '#type' => 'select',
    '#title' => 'Type',
    '#default_value' => $service->type,
    '#options' => $types,
    '#required' => TRUE,
    '#description' => t('The type of the web service.'),
  );
  if ($op == 'edit') {
    // Operations of the web service in a table
    $rows = array();
    $operations = wsclient_ui_label_sort($service->operations);
    foreach ($operations as $name => $operation) {
      $row = array();
      $row[] = array('data' => array(
        '#theme' => 'entity_ui_overview_item',
        '#label' => $operation['label'],
        '#name' => $name,
        '#url' => array(
          'path' => WSCLIENT_UI_PATH . '/manage/' . $service->name . '/operation/' . $name,
          'options' => array(),
        ),
      ));
      $row[] = l(t('Edit'), WSCLIENT_UI_PATH . '/manage/' . $service->name . '/operation/' . $name);
      $row[] = l(t('Delete'), WSCLIENT_UI_PATH . '/manage/' . $service->name . '/operation/' . $name . '/delete');
      $rows[] = $row;
    }
    $header = array(t('Label'), array('data' => t('Operations'), 'colspan' => 3));
    $add_operation = array(
      '#theme' => 'links__wsclient',
      '#links' => array(
        'add_op' => array(
          'title' => t('Add operation'),
          'href' => WSCLIENT_UI_PATH . '/manage/' . $service->name . '/add/operation',
        ),
      ),
    );
    $add_operation['#attributes']['class'][] = 'rules-operations-add';
    $add_operation['#attributes']['class'][] = 'action-links';
    $row = array();
    $row[] = array('data' => $add_operation, 'colspan' => 3);
    $rows[] = array('data' => $row, 'class' => array('rules-elements-add'));
    // @todo description help text for operations, data types
    $form['operations'] = array(
      '#access' => TRUE,
      '#tree' => TRUE,
      '#theme' => 'table',
      '#empty' => t('None'),
      '#caption' => t('Operations'),
      '#rows' => $rows,
      '#header' => $header,
    );
    // Add some table styling from Rules.
    $form['operations']['#attributes']['class'][] = 'rules-elements-table';
    $form['operations']['#attached']['css'][] = drupal_get_path('module', 'rules') . '/ui/rules.ui.css';

    // Data types of the web service in a table
    $rows = array();
    $datatypes = wsclient_ui_label_sort($service->datatypes);
    foreach ($datatypes as $name => $datatype) {
      $row = array();
      $row[] = array('data' => array(
        '#theme' => 'entity_ui_overview_item',
        '#label' => $datatype['label'],
        '#name' => $name,
        '#url' => array(
          'path' => WSCLIENT_UI_PATH . '/manage/' . $service->name . '/type/' . $name,
          'options' => array(),
        ),
      ));
      $row[] = l(t('Edit'), WSCLIENT_UI_PATH . '/manage/' . $service->name . '/type/' . $name);
      $row[] = l(t('Delete'), WSCLIENT_UI_PATH . '/manage/' . $service->name . '/type/' . $name . '/delete');
      $rows[] = $row;
    }
    $header = array(t('Label'), array('data' => t('Operations'), 'colspan' => 3));
    $add_type = array(
      '#theme' => 'links__wsclient',
      '#links' => array(
        'add_op' => array(
          'title' => t('Add data type'),
          'href' => WSCLIENT_UI_PATH . '/manage/' . $service->name . '/add/type',
        ),
      ),
    );
    $add_type['#attributes']['class'][] = 'rules-operations-add';
    $add_type['#attributes']['class'][] = 'action-links';
    $row = array();
    $row[] = array('data' => $add_type, 'colspan' => 3);
    $rows[] = array('data' => $row, 'class' => array('rules-elements-add'));
    $form['datatypes'] = array(
      '#access' => TRUE,
      '#tree' => TRUE,
      '#theme' => 'table',
      '#empty' => t('None'),
      '#caption' => t('Data types'),
      '#rows' => $rows,
      '#header' => $header,
    );

    // Input for global service parameters.
    $form['global_parameters'] = array(
      '#tree' => TRUE,
      '#element_validate' => array('wsclient_ui_validate_global_parameters'),
      '#theme' => 'wsclient_ui_global_parameter_form',
      '#title' => t('Input for global service parameters'),
      '#description' => t('Specify the global parameters for the service. Global parameters will be used if the value of an operation parameter with the same name is empty.'),
    );

    $weight = 0;
    foreach ($service->global_parameters as $name => $info) {
      $form['global_parameters']['items'][$name] = _wsclient_ui_global_parameter_row($service, $datatypes, $name, $info);
      $form['global_parameters']['items'][$name]['weight']['#default_value'] = $weight++;
    }

    // Always add three empty lines for global parameters input.
    $form_state['more'] = isset($form_state['more']) ? $form_state['more'] : 3;
    for ($i = 0; $i < $form_state['more']; $i++) {
      if (!isset($form['global_parameters']['items'][$i])) {
        $form['global_parameters']['items'][$i] = _wsclient_ui_global_parameter_row($service, $datatypes);
      }
    }
    $form['global_parameters']['more'] = array(
      '#type' => 'submit',
      '#value' => t('Add more'),
      '#limit_validation_errors' => array(array('properties')),
      '#submit' => array('wsclient_ui_more_submit'),
    );

    // Add some table styling from Rules.
    $form['datatypes']['#attributes']['class'][] = 'rules-elements-table';
    $form['datatypes']['#attached']['css'][] = drupal_get_path('module', 'rules') . '/ui/rules.ui.css';
  }
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );

  // Allow the endpoint to make alterations to the form.
  $form_state['form'] = 'main';
  if ($service->type) {
    $service->endpoint()->formAlter($form, $form_state);
  }

  $form['#submit'][] = 'wsclient_service_form_submit';

  return $form;
}

/**
 * Submit callback of the web service description form.
 */
function wsclient_service_form_submit($form, &$form_state) {
  $service = entity_ui_form_submit_build_entity($form, $form_state);

  // Save global paramters.
  if (isset($form_state['values']['global_parameters'])) {
    $service->global_parameters = array();
    foreach ($form_state['values']['global_parameters']['items'] as $key => $item) {
      if (!empty($item['name'])) {
        $service->global_parameters[$item['name']] = array(
          'default value' => $item['default_value']
        );
      }
    }
  }

  $service->save();
  drupal_set_message(t('Web service description %service has been saved.', array('%service' => $service->label)));
  if ($form_state['op'] == 'add') {
    $form_state['redirect'] = WSCLIENT_UI_PATH . '/manage/' . $service->name;
  }
  else {
    $form_state['redirect'] = WSCLIENT_UI_PATH;
  }
}

/**
 * FAPI callback to validate a URL.
 */
function wsclient_ui_element_url_validate($element, &$form_state) {
  if (!valid_url($element['#value'], TRUE)) {
    form_error($element, t('Please enter a valid URL.'));
  }
}

/**
 * Operation form.
 */
function wsclient_ui_operation($form, &$form_state, $service, $operation, $op = 'edit') {
  $form['label'] = array(
    '#type' => 'textfield',
    '#title' => t('Label'),
    '#default_value' => isset($operation['label']) ? $operation['label'] : '',
    '#required' => TRUE,
    '#description' => t('The human-readable name of the operation.'),
    '#weight' => -10,
  );
  $form['name'] = array(
    '#type' => 'textfield',
    '#title' => t('Name'),
    '#default_value' => isset($operation['name']) ? $operation['name'] : '',
    '#required' => TRUE,
    '#description' => t('The machine-readable name of this operation is used internally to identify the operation.'),
    '#element_validate' => array('wsclient_ui_operation_name_validate'),
    '#weight' => -10,
  );
  $form['parameters'] = array(
    '#tree' => TRUE,
    '#element_validate' => array('wsclient_ui_validate_parameters'),
    '#theme' => 'wsclient_ui_parameter_form',
    '#title' => t('Parameters'),
    '#description' => t('Specify the parameters for the operation. For each parameter you have to specify a certain data type and a unique name containing only alphanumeric characters and underscores. You can also specify a default value for the parameter and if it is required.'),
  );
  $weight = 0;
  $types = wsclient_ui_types(TRUE);
  if (isset($operation['parameter'])) {
    foreach ($operation['parameter'] as $name => $info) {
      $form['parameters']['items'][$name] = _wsclient_ui_parameter_row($service, $types, $name, $info);
      $form['parameters']['items'][$name]['weight']['#default_value'] = $weight++;
    }
  }
  // Always add three empty lines.
  $form_state['more'] = isset($form_state['more']) ? $form_state['more'] : 3;
  for ($i = 0; $i < $form_state['more']; $i++) {
    if (!isset($form['parameters']['items'][$i])) {
      $form['parameters']['items'][$i] = _wsclient_ui_parameter_row($service, $types);
      $form['parameters']['items'][$i]['weight']['#default_value'] = $weight++;
    }
  }
  $form['parameters']['more'] = array(
    '#type' => 'submit',
    '#value' => t('Add more'),
    '#limit_validation_errors' => array(array('parameters')),
    '#submit' => array('wsclient_ui_more_submit'),
  );
  // Exclude the hidden data type for result types.
  unset($types['hidden']);

  $result_type = 0;
  $multiple = FALSE;
  if (isset($operation['result']['type'])) {
    $result_type = wsclient_map_type($service->name, $service->dataTypes(), $operation['result']['type']);
    if (strpos($result_type, 'list<') === 0) {
      $multiple = TRUE;
      // Cut off the 'list<>' indicator.
      $result_type = substr($result_type, 5, -1);
    }
  }
  $form['result_type'] = array(
    '#type' => 'select',
    '#title' => t('Result type'),
    '#options' => array(0 => '--') + $types,
    '#default_value' => $result_type,
    '#description' => t('The result data type returned by the service'),
  );
  $form['result_multiple'] = array(
    '#type' => 'checkbox',
    '#title' => t('Multiple result'),
    '#default_value' => $multiple,
    '#description' => t('If checked, the result variable is a list containing multiple elements of the result type.'),
  );
  $form['result_label'] = array(
    '#type' => 'textfield',
    '#title' => t('Result label'),
    '#default_value' => isset($operation['result']['label']) ? $operation['result']['label'] : '',
    '#description' => t('The human-readable name of the result variable returned by the service.'),
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );
  $form_state['service'] = $service;
  $form_state['operation'] = $operation;

  // Allow the endpoint to make alterations to the form.
  $form_state['form'] = 'operation';
  $service->endpoint()->formAlter($form, $form_state);

  $form['#submit'][] = 'wsclient_ui_operation_submit';
  return $form;
}

/**
 * Generates a row in the global parameter table.
 */
function _wsclient_ui_global_parameter_row($service, $types, $name = '', $info = array()) {
  $param_type = 0;
  $multiple = FALSE;
  $parameter['name'] = array(
    '#type' => 'textfield',
    '#size' => 40,
    '#default_value' => $name,
    '#element_validate' => array('wsclient_ui_name_validate'),
  );
  $parameter['default_value'] = array(
    '#type' => 'textfield',
    '#size' => 30,
    '#default_value' => isset($info['default value']) ? $info['default value'] : '',
  );
  return $parameter;
}

/**
 * Generates a row in the parameter table.
 */
function _wsclient_ui_parameter_row($service, $types, $name = '', $info = array()) {
  $param_type = 0;
  $multiple = FALSE;
  if (isset($info['type'])) {
    $param_type = wsclient_map_type($service->name, $service->dataTypes(), $info['type']);
    if (strpos($param_type, 'list<') === 0) {
      $multiple = TRUE;
      // Cut off the 'list<>' indicator.
      $param_type = substr($param_type, 5, -1);
    }
  }
  $parameter['type'] = array(
    '#type' => 'select',
    '#options' => array(0 => '--') + $types,
    '#default_value' => $param_type,
  );
  $parameter['multiple'] = array(
    '#type' => 'checkbox',
    '#default_value' => $multiple,
  );
  $parameter['name'] = array(
    '#type' => 'textfield',
    '#size' => 40,
    '#default_value' => $name,
    '#element_validate' => array('wsclient_ui_name_validate'),
  );
  $parameter['default_value'] = array(
    '#type' => 'textfield',
    '#size' => 30,
    '#default_value' => isset($info['default value']) ? $info['default value'] : '',
  );
  $parameter['required'] = array(
    '#type' => 'checkbox',
    '#default_value' => isset($info['optional']) ? !$info['optional'] : TRUE,
  );
  $parameter['weight'] = array(
    '#type' => 'weight',
  );
  return $parameter;
}

/**
 * Validation callback for machine names of parameters or properties.
 */
function wsclient_ui_name_validate($element, &$form_state) {
  if ($element['#value'] && !preg_match('!^[A-Za-z0-9_]+$!', $element['#value'])) {
    form_error($element, t('Machine names must contain only letters, numbers, and underscores.'));
  }
}

/**
 * Submit callback for adding more parameter rows.
 */
function wsclient_ui_more_submit($form, &$form_state) {
  $form_state['more']++;
  $form_state['rebuild'] = TRUE;
}

/**
 * Submit callback of operation form.
 */
function wsclient_ui_operation_submit($form, &$form_state) {
  $service = $form_state['service'];
  $operation = $form_state['operation'];

  $operation['label'] = $form_state['values']['label'];
  $operation['parameter'] = array();
  foreach ($form_state['values']['parameters']['items'] as $key => $item) {
    if (!empty($item['name'])) {
      // Unmap the data type if it is local to this service.
      $unmapped_type = _wsclient_ui_unmap_type($item['type'], $service);
      if ($item['multiple']) {
        $operation['parameter'][$item['name']] = array('type' => 'list<' . $unmapped_type . '>');
      }
      else {
        $operation['parameter'][$item['name']] = array('type' => $unmapped_type);
      }
      if ($item['default_value'] !== '') {
        $operation['parameter'][$item['name']]['default value'] = $item['default_value'];
      }
      if (!$item['required']) {
        $operation['parameter'][$item['name']]['optional'] = TRUE;
      }
    }
  }
  if (!empty($form_state['values']['result_type'])) {
    $unmapped_type = _wsclient_ui_unmap_type($form_state['values']['result_type'], $service);
    $operation['result'] = array(
      'type' => $unmapped_type,
      'label' => isset($form_state['values']['result_label']) ? $form_state['values']['result_label'] : 'result',
    );
    if ($form_state['values']['result_multiple']) {
      $operation['result']['type'] = 'list<' . $unmapped_type . '>';
    }
  }
  unset($service->operations[$form_state['operation']['name']]);
  $service->operations[$form_state['values']['name']] = $operation;
  $service->save();
  drupal_set_message(t('Operation %operation has been saved.', array('%operation' => $operation['label'])));
  $form_state['redirect'] = WSCLIENT_UI_PATH . '/manage/' . $service->name;
  rules_clear_cache();
}

/**
 * Validation callback for operation names.
 */
function wsclient_ui_operation_name_validate($element, &$form_state) {
  if ($element['#value'] && !preg_match('!^[A-Za-z0-9_]+$!', $element['#value'])) {
    form_error($element, t('Operation names must contain only letters, numbers, and underscores.'));
  }
  if ($element['#value'] != $form_state['operation']['name'] && isset($form_state['service']->operations[$element['#value']])) {
    form_error($element, t('An operation with that name already exists'));
  }
}

/**
 * Themes the operation form for editing the used parameters.
 *
 * @ingroup themeable
 */
function theme_wsclient_ui_parameter_form($variables) {
  $elements = $variables['element'];

  $table['#theme'] = 'table';
  $table['#header'] = array(t('Data type'), t('Multiple'), t('Name'), t('Default value'), t('Required'), array('data' => t('Weight'), 'class' => array('tabledrag-hide')));
  $table['#attributes']['id'] = 'rules-' . drupal_html_id($elements['#title']) . '-id';

  foreach (element_children($elements['items']) as $key) {
    $element = &$elements['items'][$key];
    // Add special classes to be used for tabledrag.js.
    $element['weight']['#attributes']['class'] = array('rules-element-weight');

    $row = array();
    $row[] = array('data' => $element['type']);
    $row[] = array('data' => $element['multiple']);
    $row[] = array('data' => $element['name']);
    $row[] = array('data' => $element['default_value']);
    $row[] = array('data' => $element['required']);
    $row[] = array('data' => $element['weight']);
    $row = array('data' => $row) + $element['#attributes'];
    $row['class'][] = 'draggable';
    $table['#rows'][] = $row;
  }
  $elements['items']['#printed'] = TRUE;
  if (!empty($table['#rows'])) {
    drupal_add_tabledrag($table['#attributes']['id'], 'order', 'sibling', 'rules-element-weight');
  }

  // Theme it like a form item, but with the description above the content.
  $attributes['class'][] = 'form-item';
  $attributes['class'][] = 'rules-variables-form';

  $output = '<div' . drupal_attributes($attributes) . '>' . "\n";
  $output .= theme('form_element_label', $variables);
  if (!empty($elements['#description'])) {
    $output .= ' <div class="description">' . $elements['#description'] . "</div>\n";
  }
  $output .= ' ' . drupal_render($table) . "\n";
  // Add in any further children elements.
  foreach (element_children($elements, TRUE) as $key) {
    $output .= drupal_render($elements[$key]);
  }
  $output .= "</div>\n";
  return $output;
}

/**
 * Themes the global parameters form for editing the used parameters.
 *
 * @ingroup themeable
 */
function theme_wsclient_ui_global_parameter_form($variables) {
  $elements = $variables['element'];

  $table['#theme'] = 'table';
  $table['#header'] = array(t('Name'), t('Default value'));
  $table['#attributes']['id'] = 'rules-' . drupal_html_id($elements['#title']) . '-id';

  foreach (element_children($elements['items']) as $key) {
    $element = &$elements['items'][$key];
    // Add special classes to be used for tabledrag.js.
    $element['weight']['#attributes']['class'] = array('rules-element-weight');

    $row = array();
    $row[] = array('data' => $element['name']);
    $row[] = array('data' => $element['default_value']);
    $row = array('data' => $row) + $element['#attributes'];
    $row['class'][] = 'draggable';
    $table['#rows'][] = $row;
  }
  $elements['items']['#printed'] = TRUE;

  // Theme it like a form item, but with the description above the content.
  $attributes['class'][] = 'form-item';
  $attributes['class'][] = 'rules-variables-form';

  $output = '<div' . drupal_attributes($attributes) . '>' . "\n";
  $output .= theme('form_element_label', $variables);
  if (!empty($elements['#description'])) {
    $output .= ' <div class="description">' . $elements['#description'] . "</div>\n";
  }
  $output .= ' ' . drupal_render($table) . "\n";
  // Add in any further children elements.
  foreach (element_children($elements, TRUE) as $key) {
    $output .= drupal_render($elements[$key]);
  }
  $output .= "</div>\n";
  return $output;
}

/**
 * Returns a list of available data types for service parameters, return
 * values or data type properties. Entities are excluded.
 *
 * @param $hidden
 * 	 Flag to indicate whether the special 'hidden' data type should be added to
 *   the list as well.
 */
function wsclient_ui_types($hidden = FALSE) {
  $cache = rules_get_cache();
  $data_info = $cache['data_info'];
  $entity_info = entity_get_info();
  // Remove entities.
  $data_info = array_diff_key($data_info, $entity_info);
  unset($data_info['entity']);
  // Remove the generic list type.
  unset($data_info['list']);
  $options = array();
  foreach ($data_info as $type => $properties) {
    // Do not add lists as this handled by the "multiple" checkbox.
    if (strpos($type, 'list<') !== 0) {
      $options[$type] = $properties['label'];
    }
  }
  if ($hidden) {
    // Add special 'hidden' data type
    $options['hidden'] = t('hidden');
  }
  natcasesort($options);
  return $options;
}

/**
 * FAPI callback to validate the form for editing parameter info.
 */
function wsclient_ui_validate_parameters($elements, &$form_state) {
  $names = array();
  foreach (element_children($elements['items']) as $item_key) {
    $element = &$elements['items'][$item_key];
    if ($element['name']['#value'] || $element['type']['#value']) {
      foreach (array('name' => t('Name'), 'type' => t('Data type')) as $key => $title) {
        if (!$element[$key]['#value']) {
          form_error($element[$key], t('!name field is required.', array('!name' => $title)));
        }
      }
      if (isset($names[$element['name']['#value']])) {
        form_error($element['name'], t('The name %name is already taken.', array('%name' => $element['name']['#value'])));
      }
      $names[$element['name']['#value']] = TRUE;
    }
    if ($element['type']['#value'] == 'hidden' && $element['default_value']['#value'] === '') {
      form_error($element['default_value'], t('The "hidden" data type requires a default value.'));
    }
  }
}

/**
 * FAPI callback to validate the form for editing global parameter info.
 */
function wsclient_ui_validate_global_parameters($elements, &$form_state) {
  $names = array();
  foreach (element_children($elements['items']) as $item_key) {
    $element = &$elements['items'][$item_key];
    if ($element['name']['#value']) {
      if (isset($names[$element['name']['#value']])) {
        form_error($element['name'], t('The name %name is already taken.', array('%name' => $element['name']['#value'])));
      }
      $names[$element['name']['#value']] = TRUE;
    }
  }
}

/**
 * Operation delete confirmation form.
 */
function wsclient_ui_operation_delete($form, &$form_state, $service, $operation) {
  $confirm_question = t('Are you sure you want to delete the operation %operation?', array('%operation' => $operation['label']));
  $form_state['service'] = $service;
  $form_state['operation'] = $operation;
  return confirm_form($form, $confirm_question, WSCLIENT_UI_PATH . '/manage/' . $service->name);
}

/**
 * Submit callback of operation delete form.
 */
function wsclient_ui_operation_delete_submit($form, &$form_state) {
  $service = $form_state['service'];
  $operation = $form_state['operation'];
  unset($service->operations[$operation['name']]);
  $service->save();
  drupal_set_message(t('Deleted operation %operation.', array('%operation' => $operation['label'])));
  $form_state['redirect'] = WSCLIENT_UI_PATH . '/manage/' . $service->name;
}

/**
 * Data type form.
 */
function wsclient_ui_type($form, &$form_state, $service, $type, $op = 'edit') {
  $form['label'] = array(
    '#type' => 'textfield',
    '#title' => t('Label'),
    '#default_value' => isset($type['label']) ? $type['label'] : '',
    '#required' => TRUE,
    '#description' => t('The human-readable name of the data type.'),
  );
  $form['name'] = array(
    '#type' => 'textfield',
    '#title' => t('Name'),
    '#default_value' => isset($type['name']) ? $type['name'] : '',
    '#required' => TRUE,
    '#description' => t('The machine-readable name of this data type is used internally to identify the data type.'),
    '#element_validate' => array('wsclient_ui_type_name_validate'),
  );
  $form['properties'] = array(
    '#tree' => TRUE,
    '#element_validate' => array('wsclient_ui_validate_parameters'),
    '#theme' => 'wsclient_ui_property_form',
    '#title' => t('Properties'),
    '#description' => t('Specify the properties for the data type. For each property you have to specify a certain data type and a unique name containing only alphanumeric characters and underscores.'),
  );
  $types = wsclient_ui_types();
  if (isset($type['property info'])) {
    foreach ($type['property info'] as $name => $info) {
      $form['properties']['items'][$name] = _wsclient_ui_property_row($service, $types, $name, $info);
    }
  }
  // Always add three empty lines.
  $form_state['more'] = isset($form_state['more']) ? $form_state['more'] : 3;
  for ($i = 0; $i < $form_state['more']; $i++) {
    if (!isset($form['properties']['items'][$i])) {
      $form['properties']['items'][$i] = _wsclient_ui_property_row($service, $types);
    }
  }
  $form['properties']['more'] = array(
    '#type' => 'submit',
    '#value' => t('Add more'),
    '#limit_validation_errors' => array(array('properties')),
    '#submit' => array('wsclient_ui_more_submit'),
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );
  $form_state['service'] = $service;
  $form_state['type'] = $type;

  // Allow the endpoint to make alterations to the form.
  $form_state['form'] = 'type';
  $service->endpoint()->formAlter($form, $form_state);

  $form['#submit'][] = 'wsclient_ui_type_submit';

  return $form;
}

/**
 * Submit callback of data type form.
 */
function wsclient_ui_type_submit($form, &$form_state) {
  $service = $form_state['service'];
  $type = $form_state['type'];
  $type['label'] = $form_state['values']['label'];

  $type['property info'] = array();
  foreach ($form_state['values']['properties']['items'] as $key => $item) {
    if (!empty($item['name'])) {
      $unmapped_type = _wsclient_ui_unmap_type($item['type'], $service);
      $type['property info'][$item['name']] = array(
        'type' => $unmapped_type,
        'label' => $item['label'],
      );
      if ($item['multiple']) {
        $type['property info'][$item['name']] = array('type' => 'list<' . $unmapped_type . '>');
      }
    }
  }
  unset($service->datatypes[$form_state['type']['name']]);
  $service->datatypes[$form_state['values']['name']] = $type;
  $service->save();
  drupal_set_message(t('Data type %type has been saved.', array('%type' => $type['label'])));
  $form_state['redirect'] = WSCLIENT_UI_PATH . '/manage/' . $service->name;
  // Clear caches so that the new type is made available immediately.
  rules_clear_cache();
  $service->clearCache();
}

/**
 * Validation callback for data type names.
 */
function wsclient_ui_type_name_validate($element, &$form_state) {
  if ($element['#value'] && !preg_match('!^[A-Za-z0-9_]+$!', $element['#value'])) {
    form_error($element, t('Data type names must contain only letters, numbers, and underscores.'));
  }
  if ($element['#value'] != $form_state['type']['name'] && isset($form_state['service']->datatypes) && in_array($element['#value'], array_keys($form_state['service']->datatypes))) {
    form_error($element, t('A data type with that name already exists'));
  }
}

/**
 * Helper function to sort a nested data information array based on the label
 * of the items.
 */
function wsclient_ui_label_sort($data_info, $label_key = 'label') {
  $sort_info = array();
  foreach ($data_info as $key => $info) {
    $sort_info[$key] = $info[$label_key];
  }
  natcasesort($sort_info);
  foreach ($sort_info as $key => $label) {
    $sort_info[$key] = $data_info[$key];
  }
  return $sort_info;
}

/**
 * Data type delete confirmation form.
 */
function wsclient_ui_type_delete($form, &$form_state, $service, $type) {
  $confirm_question = t('Are you sure you want to delete the data type %type?', array('%type' => $type['label']));
  $form_state['service'] = $service;
  $form_state['type'] = $type;
  return confirm_form($form, $confirm_question, WSCLIENT_UI_PATH . '/manage/' . $service->name);
}

/**
 * Submit callback of data type delete form.
 */
function wsclient_ui_type_delete_submit($form, &$form_state) {
  $service = $form_state['service'];
  $type = $form_state['type'];
  unset($service->datatypes[$type['name']]);
  $service->save();
  drupal_set_message(t('Deleted data type %type.', array('%type' => $type['label'])));
  $form_state['redirect'] = WSCLIENT_UI_PATH . '/manage/' . $service->name;
}

/**
 * Generates a row in the properties table.
 */
function _wsclient_ui_property_row($service, $types, $name = '', $info = array()) {
  $property_type = 0;
  $multiple = FALSE;
  if (isset($info['type'])) {
    $property_type = wsclient_map_type($service->name, $service->dataTypes(), $info['type']);
    if (strpos($property_type, 'list<') === 0) {
      $multiple = TRUE;
      // Cut off the 'list<>' indicator.
      $property_type = substr($property_type, 5, -1);
    }
  }
  $property['type'] = array(
    '#type' => 'select',
    '#options' => array(0 => '--') + $types,
    '#default_value' => $property_type,
  );
  $property['multiple'] = array(
    '#type' => 'checkbox',
    '#default_value' => $multiple,
  );
  $property['name'] = array(
    '#type' => 'textfield',
    '#size' => 40,
    '#default_value' => $name,
    '#element_validate' => array('wsclient_ui_name_validate'),
  );
  $property['label'] = array(
    '#type' => 'textfield',
    '#size' => 40,
    '#default_value' => isset($info['label']) ? $info['label'] : '',
  );
  return $property;
}

/**
 * Themes the data type form for editing the properties.
 *
 * @ingroup themeable
 */
function theme_wsclient_ui_property_form($variables) {
  $elements = $variables['element'];

  $table['#theme'] = 'table';
  $table['#header'] = array(t('Data type'), t('Multiple'), t('Name'), t('Label'));
  $table['#attributes']['id'] = 'rules-' . drupal_html_id($elements['#title']) . '-id';

  foreach (element_children($elements['items']) as $key) {
    $element = &$elements['items'][$key];

    $row = array();
    $row[] = array('data' => $element['type']);
    $row[] = array('data' => $element['multiple']);
    $row[] = array('data' => $element['name']);
    $row[] = array('data' => $element['label']);
    $row = array('data' => $row) + $element['#attributes'];
    $table['#rows'][] = $row;
  }
  $elements['items']['#printed'] = TRUE;

  // Theme it like a form item, but with the description above the content.
  $attributes['class'][] = 'form-item';
  $attributes['class'][] = 'rules-variables-form';

  $output = '<div' . drupal_attributes($attributes) . '>' . "\n";
  $output .= theme('form_element_label', $variables);
  if (!empty($elements['#description'])) {
    $output .= ' <div class="description">' . $elements['#description'] . "</div>\n";
  }
  $output .= ' ' . drupal_render($table) . "\n";
  // Add in any further children elements.
  foreach (element_children($elements, TRUE) as $key) {
    $output .= drupal_render($elements[$key]);
  }
  $output .= "</div>\n";
  return $output;
}

/**
 * Maps the global name of a data type back to the local name in the service,
 * if the type actually stems from the service.
 */
function _wsclient_ui_unmap_type($type, $service) {
  if (strpos($type, 'wsclient_' . $service->name . '_') === 0) {
    $unmaped_type = substr($type, strlen('wsclient_' . $service->name . '_'));
    if (array_key_exists($unmaped_type, $service->dataTypes())) {
      return $unmaped_type;
    }
  }
  return $type;
}
