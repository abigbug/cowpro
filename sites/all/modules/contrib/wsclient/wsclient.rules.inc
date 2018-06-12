<?php

/**
 * @file
 * Web service client - Rules integration.
 */

/**
 * Implements hook_rules_data_info().
 */
function wsclient_rules_data_info() {
  $types = array();
  // Collect all data types of all services.
  $all_types = array();
  foreach (entity_load_multiple_by_name('wsclient_service', FALSE) as $name => $service) {
    foreach ($service->dataTypes() as $type => $type_info) {
      // Prefix the label with the service label.
      $type_info['label'] = $service->label . ': ' . $type_info['label'];
      $all_types['wsclient_' . $name . '_' . $type] = $type_info;
    }
  }
  // Prepare data type info for Rules.
  foreach ($all_types as $type => $type_info) {
    wsclient_type_info_populate($type_info, $type_info['service'], $all_types);
    $type_info = array_intersect_key($type_info, array_flip(array('label', 'property info'))) + array(
      'wrap' => TRUE,
      'creation callback' => 'rules_action_data_create_array',
    );
    $types[$type] = $type_info;
  }
  return $types;
}

/**
 * Helper function to recursively populate property information in a data type
 * information array. Also adds a default label from the machine name.
 *
 * @param $type_info
 *   Type information array that describes the type.
 * @param $service_name
 *   The name of the web service description where the type information belongs
 *   to.
 * @param $all_types
 *   Array of all data types of all web service descriptions.
 * @param unknown_type $recursion_stop
 *   Array of data type names that have already been used to populate property
 *   information. Used to prevent endless recursion.
 */
function wsclient_type_info_populate(array &$type_info, $service_name, array $all_types, $recursion_stop = array()) {
  if (isset($type_info['property info'])) {
    foreach ($type_info['property info'] as $name => &$info) {
      if (!isset($info['label']) || $info['label'] == '') {
        $info['label'] = $name;
      }
      // Get the global type name.
      $type = wsclient_global_type_name($info['type'], $service_name, $all_types);
      // Date values are converted from ISO strings to timestamp, if needed.
      if($type == 'date') {
        $info['getter callback'] = 'entity_property_verbatim_date_get';
      }
      // Copy recursion information for this property.
      $new_recursion_stop = $recursion_stop;
      if (!isset($info['property info']) && isset($all_types[$type]) && !isset($recursion_stop[$type])) {
        $info['type'] = strpos($info['type'], 'list<') === 0 ? 'list<' . $type . '>' : $type;
        // Copy over the property information.
        $info['property info'] = $all_types[$type]['property info'];
        // Mark this type as finished.
        $new_recursion_stop[$type] = TRUE;
      }
      // Also populate nested property info arrays (recursion).
      wsclient_type_info_populate($info, $service_name, $all_types, $new_recursion_stop);
    }
  }
}

/**
 * Map a service specific type name to the global type name.
 */
function wsclient_global_type_name($type, $service_name, $all_types) {
  if (isset($all_types['wsclient_' . $service_name . '_' . $type])) {
    return 'wsclient_' . $service_name . '_' . $type;
  }
  if (strpos($type, 'list<') === 0 && isset($all_types['wsclient_' . $service_name . '_' . substr($type, 5, -1)])) {
    return 'wsclient_' . $service_name . '_' . substr($type, 5, -1);
  }
  return $type;
}

/**
 * Implements hook_rules_action_info().
 */
function wsclient_rules_action_info() {
  $return = array();
  foreach (entity_load_multiple_by_name('wsclient_service', FALSE) as $name => $service) {
    $service_types = $service->dataTypes();
    foreach ($service->actions() as $item_name => $info) {
      $info += array(
        'parameter' => array(),
        'provides' => array(),
        'group' => t('Web services'),
      );
      // Map the types.
      foreach ($info['parameter'] as $param => &$param_info) {
        $param_info['type'] = wsclient_map_type($name, $service_types, $param_info['type']);
        if (!isset($param_info['label'])) {
          // Create a label from parameter machine name, remove prefix 'param_'.
          $param_info['label'] = substr($param, 6);
        }
      }
      foreach ($info['provides'] as $var_name => &$var_info) {
        $var_info['type'] = wsclient_map_type($name, $service_types, $var_info['type']);
      }
      // Prefix the action label with the service label.
      $info['label'] = $service->label . ': ' . $info['label'];
      $return['wsclient_' . $name . '_' . $item_name] = $info;
    }
  }
  return $return;
}

/**
 * Action callback: invoke a web service.
 */
function wsclient_service_action($arguments, RulesPlugin $element) {
  if ($service = wsclient_service_load($arguments['service'])) {
    $args = array();
    foreach ($arguments as $name => $data) {
      if (strpos($name, 'param_') === 0) {
        // Remove the parameter name prefix 'param_'.
        $args[substr($name, 6)] = $data;
      }
    }
    try {
      $return = $service->invoke($arguments['operation'], $args);
    }
    catch (Exception $e) {
      throw new RulesEvaluationException($e->getMessage(), array(), $element, RulesLog::ERROR);
    }
    return array('result' => $return);
  }
  else {
    throw new WSClientException('The web service %name cannot be found.', array('%name' => $arguments['service']));
  }
}

