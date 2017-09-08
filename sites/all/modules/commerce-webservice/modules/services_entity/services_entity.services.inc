<?php

/**
 * Contains Services hooks.
 */

/**
 * Implements of hook_services_resources().
 */
function services_entity_services_resources() {
  $resources = array();

  foreach (entity_get_info() as $entity_type => $info) {
    $controller = _services_entity_get_controller($entity_type);
    $resources["entity_$entity_type"] = $controller->resourceInfo($entity_type);
  }

  return $resources;
}
