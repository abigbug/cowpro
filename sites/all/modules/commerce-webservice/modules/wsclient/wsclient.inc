<?php

/**
 * @file
 * Web service client - include file.
 */

/**
 * Class representing web service descriptions.
 */
class WSClientServiceDescription extends Entity {

  public $settings = array();
  public $operations = array();
  public $datatypes = array();
  public $global_parameters = array();
  public $name;
  public $label;
  public $url;
  public $type;

  protected $endpoint = NULL;

  function __construct($values = array(), $entity_type = 'wsclient_service') {
    parent::__construct($values, $entity_type);
  }

  /**
   * Magic method to catch service invocations.
   */
  public function __call($operation, $arguments) {
    return $this->invoke($operation, $arguments);
  }

  /**
   * Invoke a service via its endpoint.
   *
   * @param string $operation
   *   The name of the operation to execute.
   * @param array $arguments
   *   Arguments to pass to the service with this operation. If the array keys
   *   do not match the parameter information, the array values are assigned in
   *   sequential order according to the order of parameters.
   */
  public function invoke($operation, array $arguments) {
    if (!isset($this->operations[$operation])) {
      throw new WSClientException('Operation %operation does not exist for web service %service.', array('%operation' => $operation, '%service' => $this->name));
    }
    $named_arguments = array();
    if (isset($this->operations[$operation]['parameter'])) {
      $remaining_params = $this->operations[$operation]['parameter'];
      // Assign named arguments and hidden parameters.
      foreach ($this->operations[$operation]['parameter'] as $param => $info) {
        if (isset($arguments[$param])) {
          $named_arguments[$param] = $arguments[$param];
          unset($arguments[$param]);
          unset($remaining_params[$param]);
        }
        elseif ($info['type'] == 'hidden') {
          $named_arguments[$param] = $info['default value'];
          unset($remaining_params[$param]);
        }
      }
      // Assign the rest in sequential order.
      foreach ($remaining_params as $param => $info) {
        $named_arguments[$param] = array_shift($arguments);
      }
    }

    // Fill in global parameters.
    foreach ($this->global_parameters as $param => $info) {
      if (!isset($named_arguments[$param])) {
        $named_arguments[$param] = $info['default value'];
      }
    }

    return $this->endpoint()->call($operation, $named_arguments);
  }

  /**
   * Determines access to the web service.
   */
  public function access($account = NULL) {
    if (method_exists($this->endpoint(), 'access')) {
      return $this->endpoint()->access($account);
    }
    return user_access('interact with ' . $this->name, $account);
  }

  /**
   * Returns the associated web service endpoint object.
   *
   * @return WSClientEndpointInterface
   */
  public function endpoint() {
    if (!isset($this->endpoint)) {
      $types = wsclient_get_types();
      $this->endpoint = new $types[$this->type]['class']($this);
    }
    return $this->endpoint;
  }

  /**
   * Returns info about the data types of the web service.
   */
  public function dataTypes() {
    $types = $this->datatypes;
    foreach ($types as $type => $info) {
      // Add in the service name so that others know where this type comes from.
      $types[$type]['service'] = $this->name;
    }
    return $types;
  }

  /**
   * Returns info about the actions of the web service.
   */
  public function actions() {
    $actions = array();
    foreach ($this->operations as $name => $operation) {
      $actions[$name] = $operation += array(
        'base' => 'wsclient_service_action',
        'named parameter' => TRUE,
      );
      $actions[$name]['parameter'] = array();
      if (isset($operation['parameter'])) {
        // Prefix operation parameter names to avoid name clashes.
        foreach ((array) $operation['parameter'] as $param => $info) {
          $actions[$name]['parameter']['param_' . $param] = $info;
        }
      }
      $actions[$name]['parameter']['service'] = array(
        'type' => 'hidden',
        'default value' => $this->name,
      );
      $actions[$name]['parameter']['operation'] = array(
        'type' => 'hidden',
        'default value' => $name,
      );
      // Pass through the service result as provided variable.
      if (!empty($actions[$name]['result'])) {
        $actions[$name]['provides']['result'] = $actions[$name]['result'];
        unset($actions[$name]['result']);
      }
    }
    return $actions;
  }

  public function clearCache() {
    $this->endpoint()->clearCache();
  }
}

/**
 * Interface for remote endpoints. In case of any errors the implementing
 * classes should throw exceptions.
 */
interface WSClientEndpointInterface {

  public function __construct(WSClientServiceDescription $service);

  /**
   * Connect to the remote web service and call an operation.
   *
   * @param string $operation
   *   The name of the operation.
   * @param $arguments
   *   The arguments needed for the operation.
   *
   * @return
   *   The response of the web service call.
   */
  public function call($operation, $arguments);

  /**
   * An array of info about data types used by the provided events/actions
   * being not entities.
   */
  public function dataTypes();

  /**
   * Allows altering the configuration form of web service definitions, such
   * that the form can include endpoint type specific configuration settings.
   */
  public function formAlter(&$form, &$form_state);

  /**
   * Clear any caches the endpoint maintains.
   */
  public function clearCache();

}

/**
 * Default parent class for service endpoints.
 */
abstract class WSClientEndpoint implements WSClientEndpointInterface {

  /**
   * @var WSClientServiceDescription
   */
  protected $service;

  protected $url;

  protected $client;

  public function __construct(WSClientServiceDescription $service) {
    $this->service = $service;
    $this->url = $service->url;
  }

  public function call($operation, $arguments) {}

  public function dataTypes() {}

  public function formAlter(&$form, &$form_state) {}

  public function clearCache() {
    unset($this->client);
  }
}

/**
 * Custom exception class to enhance default PHP exceptions.
 */
class WSClientException extends Exception {

  /**
   * @param $msg
   *   The exception message containing placeholder as t().
   * @param $args
   *   Replacement arguments such as for t().
   */
  function __construct($msg, $args = array()) {
    $message = t($msg, $args);
    parent::__construct($message);
  }
}
