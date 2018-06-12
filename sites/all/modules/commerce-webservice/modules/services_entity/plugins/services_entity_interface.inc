<?php

/**
 * @file
 * Services Entity module integration for entities.
 */

/**
 * Specifies CRUD and access methods for resources.
 */
interface ServicesResourceControllerInterface {

  /**
   * Specify services resource informatino for an entity type.
   *
   * @param string $entity_type
   *   The entity type whose info should be specified.
   *
   * @return
   *   An info array as would be returned by hook_services_resources().
   *
   * @see hooK_services_resources().
   */
  public function resourceInfo($entity_type);

  /**
   * Determines access for a given operation and resource.
   *
   * @param string $op
   *   Either 'create', 'view' (= read), 'update' or 'delete'.
   * @param $args
   *   The arguments passed to the operation.
   *
   * @see entity_access()
   */
  public function access($op, $args);

  /**
   * Create a new resource.
   *
   * @param string $entity_type
   *   The type of the resource that should be created.
   * @param array $values
   *   Array of values for properties of the resource, keyed by property
   *   name. At least for all required properties values have to be given.
   *
   * @return int|string
   *   The id of the newly created resource.
   */
  public function create($entity_type, array $values);

  /**
   * Returns an existing resource.
   *
   * @param string $entity_type
   *   The type of the resource that should be returned.
   * @param int|string $entity_id
   *   The id of the resource that should be returned.
   * @param array $fields (optional)
   *   The fields for the resource that should be returned.
   * @param int $revision (optional)
   *   The revision of the resource that should be returned.  If omitted,
   *   the current revision will be returned.
   *
   * @return
   *   The internal representation of the resource.
   */
  public function retrieve($entity_type, $entity_id, $fields, $revision);

  /**
   * Update an existing resource.
   *
   * @param string $entity_type
   *   The type of the resource that should be updated.
   * @param int|string $entity_id
   *   The id of the resource that should be updated.
   * @param array $values
   *   An array of values for the properties to be updated, keyed by property
   *   name.
   */
  public function update($entity_type, $entity_id, array $values);

  /**
   * Delete an existing resource.
   *
   * @param string $entity_type
   *   The type of the resource that should be deleted.
   * @param int|string $entity_id
   *   The id of the resource that should be deleted.
   */
  public function delete($entity_type, $entity_id);

  /**
   *
   * @param string $entity_type
   *   The type of the resource that should be deleted.
   * @param array $filters
   *   field comparison operators to filter the results.
   * @param int $page
   *   The page of resources to be returned
   * @param int $limit
   *   The number of items on that pages to be returned.
   */
  public function index($entity_type, $fields, $parameters, $page, $pagesize, $sort, $direction);

  /**
   * Get the value of a single field.
   *
   * @param $entity_type
   *  The entity type.
   * @param $entity_id
   *  The id of the entity on which the field values are present.
   * @param $field_name
   *  The name of the field to retrieve the value of.
   * @param $fields
   *  A comma-separated list of the fields to return on the returned entities, or
   *  '*' to return all fields.
   * @param $raw
   *  (optional) Whether to return the raw value of the field, or the processed
   *  value. Defaults to FALSE.
   *
   * @return
   *  Entity data for the field.
   */
  public function field($entity_type, $entity_id, $field_name, $fields = '*', $raw = FALSE);
}

