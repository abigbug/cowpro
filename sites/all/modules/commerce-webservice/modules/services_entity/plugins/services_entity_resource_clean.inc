<?php
/**
 * This class is designed to create a very clean API that integrates with
 * the services and entity modules. We want to strip all "drupalisms" out
 * of the API. For example, there should be no [LANGUAGE_NONE][0][value] or
 * field_ in the API.
 *
 * It should be possible to create an API that is easily replicated on another
 * system.
 *
 * Much of this code is borrowed from restws module.
 */
class ServicesEntityResourceControllerClean extends ServicesEntityResourceController {
  /**
   * @see ServicesEntityResourceController::access()
   */
  public function access($op, $args) {
    if ($op == 'create') {
      list($entity_type, $data) = $args;
      // Workaround for bug in Entity API node access.
      // @todo remove once https://drupal.org/node/1780646 lands.
      if ($entity_type == 'node') {
        return isset($data['type']) ? node_access('create', $data['type']) : FALSE;
      }
      // Create a wrapper from the entity so we can call its access() method.
      $wrapper = $this->createWrapperFromValues($entity_type, $data);
      return $wrapper->entityAccess('create');
    }
    else {
      return parent::access($op, $args);
    }
  }

  public function create($entity_type, array $values) {
    $wrapper = $this->createWrapperFromValues($entity_type, $values);

    // Check write access on each property.
    foreach (array_keys($values) as $name) {
      if (!$this->propertyAccess($wrapper, $name, 'create')) {
        services_error(t("Not authorized to set property '@p'", array('@p' => $name)), 403);
      }
    }

    // Make sure that bundle information is present on entities that have
    // bundles. We have to do this after creating the wrapper, because the
    // name of the bundle key may differ from that of the corresponding
    // metadata property (e.g. for taxonomy terms, the bundle key is
    // 'vocabulary_machine_name', while the property is 'vocabulary').
    if ($bundle_key = $wrapper->entityKey('bundle')) {
      $entity = $wrapper->value();
      if (empty($entity->{$bundle_key})) {
        $entity_info = $wrapper->entityInfo();
        if (isset($entity_info['bundles']) && count($entity_info['bundles']) === 1) {
          // If the entity supports only a single bundle, then use that as a
          // default. This allows creation of such entities if (as with ECK)
          // they still use a bundle key.
          $entity->{$bundle_key} = reset($entity_info['bundles']);
        }
        else {
          services_error('Missing bundle: ' . $bundle_key, 406);
        }
      }
    }

    $properties = $wrapper->getPropertyInfo();
    $diff = array_diff_key($values, $properties);
    if (!empty($diff)) {
      services_error('Unknown data properties: ' . implode(' ', array_keys($diff)) . '.', 406);
    }
    $wrapper->save();
    return $this->get_data($wrapper, '*');
  }

  public function retrieve($entity_type, $entity_id, $fields, $revision) {
    $entity = parent::retrieve($entity_type, $entity_id, '*', $revision);
    return $this->get_data(entity_metadata_wrapper($entity_type, $entity), $fields);
  }

  public function update($entity_type, $entity_id, array $values) {
    $property_info = entity_get_all_property_info($entity_type);
    $values = $this->transform_values($entity_type, $property_info, $values);
    try {
      $wrapper = entity_metadata_wrapper($entity_type, $entity_id);
      foreach ($values as $name => $value) {
        // Only attempt to set properties when the new value differs from that
        // on the existing entity; otherwise, requests will fail for read-only
        // and unauthorized properties, even if they are not being changed. This
        // allows us to UPDATE a previously retrieved entity without removing
        // such properties from the payload, as long as they are unchanged.
        if (!$this->propertyHasValue($wrapper, $name, $value)) {
          // We set the property before checking access so the new value
          // will be passed to the access callback. This is necesssary in
          // some cases (e.g. text-format fields) where access permissions
          // depend on the value that is being set.
          $wrapper->{$name}->set($value);
          if (!$this->propertyAccess($wrapper, $name, 'update')) {
            services_error(t("Not authorized to set property '@property-name'.", array('@property-name' => $name)), 403);
          }
        }
      }
    }
    catch (EntityMetadataWrapperException $e) {
      services_error($e->getMessage(), 406);
    }
    $wrapper->save();
    return $this->get_data($wrapper, '*');
  }

  public function index($entity_type, $fields, $parameters, $page, $pagesize, $sort, $direction) {
    $property_info = entity_get_all_property_info($entity_type);
    $parameters = $this->transform_values($entity_type, $property_info, $parameters);
    $sort = (isset($property_info['field_' . $sort]))?'field_' . $sort:$sort;

    // Call the parent method, which takes care of access control.
    $entities = parent::index($entity_type, '*', $parameters, $page, $pagesize, $sort, $direction);
    foreach($entities as $entity) {
      $return[] = $this->get_data(entity_metadata_wrapper($entity_type, $entity), $fields);
    }
    return $return;
  }

  /**
   * Implements ServicesResourceControllerInterface::field().
   */
  public function field($entity_type, $entity_id, $field_name, $fields = '*', $raw = FALSE) {
    $entity = entity_load_single($entity_type, $entity_id);
    if (!$entity) {
      services_error('Entity not found', 404);
    }

    $field_name = preg_replace('/^field_/', '', $field_name);

    // The metadata wrapper checks entity_access() on each entity in the field.
    $return = $this->get_data(entity_metadata_wrapper($entity_type, $entity), $field_name);
    return $return;
  }

  /**
   * Return the data structure for an entity stripped of all "drupalisms" such as
   * field_ and complex data arrays.
   *
   * @param type $wrapper
   * @return type
   */
  protected function get_data($wrapper, $fields = '*') {
    if ($fields != '*') {
      $fields_array = explode(',', $fields);
    }
    $data = array();
    $filtered = $this->property_access_filter($wrapper);
    foreach ($filtered as $name => $property) {
      // We don't want 'field_' at the beginning of fields. This is a drupalism and shouldn't be in the api.
      $name = preg_replace('/^field_/', '', $name);
      // If fields is set and it isn't one of them, go to the next.
      if ($fields != '*' && !in_array($name, $fields_array)) {
        continue;
      }
      try {
        if ($property instanceof EntityDrupalWrapper) {
          // For referenced entities only return the URI.
          if ($id = $property->getIdentifier()) {
            $data[$name] = $this->get_resource_reference($property->type(), $id);
          }
        }
        elseif ($property instanceof EntityValueWrapper) {
          $data[$name] = $property->value();
        }
        elseif ($property instanceof EntityListWrapper || $property instanceof EntityStructureWrapper) {
          $data[$name] = $this->get_data($property);
        }
      }
      catch (EntityMetadataWrapperException $e) {
        // A property causes problems - ignore that.
      }
    }
    // If bundle = entity_type, don't send it.
    if (method_exists($wrapper, 'entityInfo')) {
      $entity_info = $wrapper->entityInfo();
      if (isset($entity_info['bundle keys'])) {
        foreach ($entity_info['bundle keys'] as $bundle_key) {
          if (array_key_exists($bundle_key, $data) && $data[$bundle_key] == $wrapper->type()) {
            unset($data[$bundle_key]);
          }
        }
      }
    }
    return $data;
  }

  /**
   * Return a resource reference array.
   *
   * @param type $resource
   * @param type $id
   * @return type
   */
  protected function get_resource_reference($resource, $id) {
    $return = array(
      'uri' => services_resource_uri(array('entity_' . $resource, $id)),
      'id' => $id,
      'resource' => $resource,
    );
    if (module_exists('uuid') && entity_get_info($resource)) {
      $ids = entity_get_uuid_by_id($resource, array($id));
      if ($id = reset($ids)) {
        $return['uuid'] = $id;
      }
    }
    return $return;
  }

  /**
   * Filters out properties where view access is not allowed for the current user.
   *
   * @param EntityMetadataWrapper $wrapper
   *   EntityMetadataWrapper that should be checked.
   *
   * @return
   *   An array of properties where access is allowed, keyed by their property
   *   name.
   */
  protected function property_access_filter($wrapper) {
    $filtered = array();
    foreach ($wrapper as $name => $property) {
      try {
        if ($property->access('view')) {
          $filtered[$name] = $property;
        }
      }
      catch (EntityMetaDataWrapperException $e) {
        // Log the exception and ignore the property. This is known to happen
        // when attempting to access the 'book' property of a non-book node.
        // In such cases Entity API erroneously throws an exception.
        // @see https://drupal.org/node/2051087 and linked issues.
        watchdog('services_entity', 'Exception testing access to property @p: @e', array('@p' => $name, '@e' => $e->getMessage()), WATCHDOG_WARNING);
      }
    }
    return $filtered;
  }

  /**
   * Checks for field_ prefix for each field and adds it if necessary.
   *
   * @param type $values
   * @return type
   */
  protected function transform_values($entity_type, $property_info, $values) {
    foreach($values as $key => $value) {
      // Handle Resource references so we can pass pack the object.
      if (is_array($value) && isset($value['id'])) {
        $values[$key] = $value['id'];
      }
      // Check if this is actually a field_ value
      if (isset($property_info['field_' . $key])) {
        $values['field_' . $key] = $values[$key];
        unset($values[$key]);
      }
    }
    return $values;
  }

  /**
   * Overridden to translate metadata property name to schema field.
   *
   * @see ServicesEntityResourceController::propertyQueryOperation()
   */
  protected function propertyQueryOperation($entity_type, EntityFieldQuery $query, $operation, $property, $value) {
    $info = entity_get_all_property_info($entity_type);
    $field = isset($info[$property]['schema field']) ? $info[$property]['schema field'] : $property;
    try {
      parent::propertyQueryOperation($entity_type, $query, $operation, $field, $value);
    }
    catch (ServicesException $e) {
      // Intercept a services exception and correct the property name.
      services_error(t('Parameter @prop does not exist', array('@p' => $property)), 406);
    }
  }

  /**
   * Helper function to create a wrapped entity from provided data values.
   *
   * @param $entity_type
   *   The type of entity to be created.
   * @param $values
   *   Array of data property values.
   * @return EntityDrupalWrapper
   *   The wrapped entity.
   * @todo the created wrapper should probably be statically cached, so we
   * don't have to build it twice (first on access() and again on create()).
   */
  protected function createWrapperFromValues($entity_type, array &$values) {
    $property_info = entity_get_all_property_info($entity_type);
    $values = $this->transform_values($entity_type, $property_info, $values);
    try {
      $wrapper = entity_property_values_create_entity($entity_type, $values);
    }
    catch (EntityMetadataWrapperException $e) {
      services_error($e->getMessage(), 406);
    }
    return $wrapper;
  }

  /**
   * Determine whether a wrapper property has a specified value.
   *
   * @param \EntityMetadataWrapper $wrapper
   *   The wrapper whose property is to be checked.
   * @param $name
   *   The name of the property to check.
   * @param mixed $value
   *   The value to compare it to. May be a wrapper, identifier or raw value.
   *
   * @return boolean
   *   TRUE if the property's current value is equal to the given value. FALSE
   *   if they are different.
   */
  protected function propertyHasValue(EntityMetadataWrapper $wrapper, $name, $value) {
    $property = $wrapper->{$name};
    if ($property instanceof EntityDrupalWrapper) {
      if ($value instanceof EntityDrupalWrapper) {
        return $value->getIdentifier() == $property->getIdentifier();
      }
      elseif (is_numeric($value)) {
        return $value == $property->getIdentifier();
      }
    }
    return $value == $property->value();
  }
  
  /**
   * Check access on an entity metadata property.
   *
   * This is a wrapper around EntityMetadataWrapper::access() because that
   * makes no distinction between 'create' and 'update' operations.
   *
   * @param EntityDrupalWrapper $wrapper
   *   The wrapped entity for which the property access is to be checked.
   * @param string $name
   *   The wrapper name of the property whose access is to be checked.
   * @param string $op
   *   One of 'create', 'update' or 'view'.
   *
   * @return bool
   *   TRUE if the current user has access to set the property, FALSE otherwise.
   */
  protected function propertyAccess($wrapper, $name, $op) {
    $property = $wrapper->{$name};
    $info = $property->info();
    switch ($op) {
      case 'create':
        // Don't check access on bundle for new entities. Otherwise,
        // property access checks will fail for, e.g., node type, which
        // requires the 'administer nodes' permission to set.
        // @see entity_metadata_node_entity_property_info().
        if (isset($info['schema field']) && $info['schema field'] == $wrapper->entityKey('bundle')) {
          return TRUE;
        }
  
        // Don't check access on node author if set to the current user.
        if ($wrapper->type() == 'node' && $name == 'author' && $wrapper->value()->uid == $GLOBALS['user']->uid) {
          return TRUE;
        }
  
        // No break: no special cases apply, so contine as for 'update'.
  
      case 'update':
        // This is a hack to check format access for text fields.
        // @todo remove once this is handled properly by core or Entity API.
        // @see https://drupal.org/node/2065021
        if ($property->type() == 'text_formatted' && $property->format->value()) {
          $format = (object) array('format' => $property->format->value());
          if (!filter_access($format)) {
            return FALSE;
          }
        }
  
        // Entity API create access is currently broken for nodes.
        // @todo remove this check once https://drupal.org/node/1780646 is fixed.
        // @see also https://drupal.org/node/1865102
        if ($op == 'create' && $wrapper->type() == 'node') {
          return TRUE;
        }
  
        // Finally, use the property access.
        return $property->access('edit');
  
      case 'view':
        return $property->access('view');
    }
  }
}
