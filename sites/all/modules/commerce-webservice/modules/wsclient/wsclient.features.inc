<?php

/**
 * @file
 * Provides Features integration for web service descriptions.
 */

/**
 * Custom Features controller to add service data type dependencies and
 * endpoint module dependencies to the export.
 */
class WSClientFeaturesController extends EntityDefaultFeaturesController {

  /**
   * Generates the result for hook_features_export().
   */
  public function export($data, &$export, $module_name = '') {
    $pipe = parent::export($data, $export, $module_name);
    $wsclient_types = wsclient_data_type_info();
    $endpoints = wsclient_get_types();
    // Keep track of services that are a dependency.
    $dependencies = array();
    foreach ($data as $identifier) {
      $service = wsclient_service_load($identifier);
      // Add the module that provides the endpoint for the service as
      // dependency.
      $module = $endpoints[$service->type]['module'];
      $export['dependencies'][$module] = $module;

      // Add other services when data types stem from them.
      foreach ($service->dataTypes() as $type_name => $info) {
        if (isset($info['property info'])) {
          foreach ($info['property info'] as $property => $property_info) {
            if (isset($wsclient_types[$property_info['type']])) {
              $type_info = $wsclient_types[$property_info['type']];
              $dependencies[$type_info['service']] = $type_info['service'];
            }
          }
        }
      }
      foreach ($service->operations as $operation => $info) {
        if (isset($info['parameter'])) {
          foreach ($info['parameter'] as $param => $param_info) {
            if (isset($wsclient_types[$param_info['type']])) {
              $type_info = $wsclient_types[$param_info['type']];
              $dependencies[$type_info['service']] = $type_info['service'];
            }
          }
        }
        if (isset($wsclient_types[$info['result']['type']])) {
          $type_info = $wsclient_types[$info['result']['type']];
          $dependencies[$type_info['service']] = $type_info['service'];
        }
      }
    }
    // Remove wsclient_services from the dependency list if they are already
    // listed in the export array. This is necessary to prevent an infinite loop.
    $dependencies = array_diff_key($dependencies, $export['features']['wsclient_service']);
    foreach ($dependencies as $dependency) {
      $pipe['wsclient_service'][] = $dependency;
    }
    return $pipe;
  }
}
