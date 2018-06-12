<?php

/**
 * Contains Services resources callbacks.
 */

/**
 * Services access callback.
 *
 * Invokes the 'access' method of the appropriate controller.
 *
 * @param $access_op
 *   The $op value to pass as the first parameter to the controller's
 *   access() method.
 * @param array $args
 *   An array of arguments that will be passed to the resource callback. This
 *   is due to our setting of 'access arguments append' in the resource info.
 *
 * @return boolean
 *   TRUE to grant access, FALSE otherwise.
 */
function _services_entity_access_callback($access_op, $args) {
  // Remove the first of the arguments, which is the resource method name.
  array_shift($args);

  $entity_type = reset($args);
  $controller = _services_entity_get_controller($entity_type);

  return call_user_func_array(array($controller, 'access'), array($access_op, $args));
}

/**
 * Services resource callback.
 *
 * Invokes the specified method of the appropriate controller.
 *
 * @param string $method
 *   The method to invoke.
 * @param string $entity_type
 *   The entity type.
 * @param ...
 *   Additional arguments to pass to the method.
 *
 * @return mixed
 *   The response payload for the service, ready for formatting.
 */
function _services_entity_resource_callback($method, $entity_type) {
  $args = func_get_args();
  $method = array_shift($args);
  $entity_type = reset($args);
  $controller = _services_entity_get_controller($entity_type);
  return call_user_func_array(array($controller, $method), $args);
}
