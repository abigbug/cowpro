<?php

/**
 * @file
 * This file contains no working PHP code; it exists to provide additional
 * documentation for doxygen as well as to document web service descriptions
 * in the standard Drupal manner.
 */

/**
 * @addtogroup wsclient_hooks
 * @{
 */

/**
 * Define a remote endpoint type.
 *
 * This hook may be used to define a remote endpoint type, which users may
 * use for configuring web services.
 *
 * @return
 *   An array of endpoint type definitions with the endpoint type names as keys.
 *   Each definition is represented by another array with the following keys:
 *   - label: The label of the endpoint type. Start capitalized. Required.
 *   - class: The actual implementation class for the endpoint type. This class
 *     has to implement the WSClientEndpointInterface. Required.
 *
 * @see hook_wsclient_endpoint_types_alter()
 * @see WSClientEndpointInterface
 */
function hook_wsclient_endpoint_types() {
  return array(
    'rules_web_hook' => array(
      'label' => t('Rules Web Hooks'),
      'class' => 'WSClientServiceDescriptionEndpointWebHooks',
    ),
  );
}

/**
 * Alter remote endpoint type definitions.
 *
 * @param $types
 *   The remote endpoint type definitions as returned from
 *   hook_wsclient_endpoint_types().
 *
 * @see hook_wsclient_endpoint_types()
 */
function hook_wsclient_endpoint_types_alter(&$types) {
  $types['rules_web_hook']['label'] = t('New fancy Rules Web Hooks');
}

/**
 * Act on web service descriptions being loaded from the database.
 *
 * This hook is invoked during web service description loading, which is
 * handled by entity_load(), via the EntityCRUDController.
 *
 * @param $services
 *   An array of web service descriptions being loaded, keyed by id.
 */
function hook_wsclient_service_load($services) {
  $result = db_query('SELECT id, foo FROM {mytable} WHERE id IN(:ids)', array(':ids' => array_keys($services)));
  foreach ($result as $record) {
    $services[$record->id]->foo = $record->foo;
  }
}

/**
 * Respond to creation of a new web service description.
 *
 * This hook is invoked after the description is inserted into the database.
 *
 * @param  $service
 *   The web service description that is being created.
 */
function hook_wsclient_service_insert($service) {
  db_insert('mytable')
    ->fields(array(
      'id' => $service->id,
      'my_field' => $service->myField,
    ))
    ->execute();
}

/**
 * Act on a web service description being inserted or updated.
 *
 * This hook is invoked before the web service description is saved to the
 * database.
 *
 * @param WSClientServiceDescription $service
 *   The web service description that is being inserted or updated.
 */
function hook_wsclient_service_presave($service) {
  $service->myField = 'foo';
}

/**
 * Respond to updates to a web service description.
 *
 * This hook is invoked after the web service description has been updated in
 * the database.
 *
 * @param WSClientServiceDescription $service
 *   The web service description that is being updated.
 */
function hook_wsclient_service_update($service) {
  db_update('mytable')
    ->fields(array('my_field' => $service->myField))
    ->condition('id', $service->id)
    ->execute();
}

/**
 * Respond to a web service description deletion.
 *
 * This hook is invoked after the web service description has been removed from
 * the database.
 *
 * @param WSClientServiceDescription $service
 *   The web service description that is being deleted.
 */
function hook_wsclient_service_delete($service) {
  db_delete('mytable')
    ->condition('id', $service->id)
    ->execute();
}

/**
 * Define default web service descriptions.
 *
 * This hook is invoked when web service descriptions are loaded.
 *
 * @return
 *   An array of web service descriptions with the web service names as keys.
 *
 * @see hook_default_wsclient_service_alter()
 */
function hook_default_wsclient_service() {
  $service = new WSClientServiceDescription();
  $service->name = 'master';
  $service->label = 'The master site.';
  $service->url = 'http://master.example.com';
  $service->type = 'rest';
  $services[$service->name] = $service;
  return $services;
}

/**
 * Alter default web service descriptions.
 *
 * @param $services
 *   The default web service descriptions of all modules as returned from
 *   hook_default_wsclient_service().
 *
 * @see hook_default_wsclient_service()
 */
function hook_default_wsclient_service_alter(&$services) {
  $services['master']->label = 'New fancy mster site.';
}

/**
 * @}
 */
