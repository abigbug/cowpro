<?php

/**
 * @file
 * Services Entity module integration for entities.
 */

/**
 * An abstract controller providing basic CRUD resource info for entities.
 *
 * Note that this controller only provides the resource definition. There are
 * no implementations of any of the CRUD methods. You should extend this class
 * to provide your own implementations.
 *
 * @see ServicesEntityResourceController
 */
abstract class ServicesResourceControllerAbstract implements ServicesResourceControllerInterface {

  /**
   * Helper function to return basic information about a resource operation.
   *
   * Invoke this method to build the basic info array, and then override
   * elements as needed for your specific entity/operation.
   *
   * @param string $entity_type
   *   The entity type.
   * @param string $controller_method
   *   The name of the method the service should invoke on the controller. This
   *   must be defined in the controller class.
   * @param $access_op
   *   If set, the $op value to pass to the access method for this operation.
   *   Defaults to the method name. This is useful when the operation
   *   expected by entity_access() differs from the method name (e.g. 'view'
   *   rather than 'retrieve'), or when you want to use the same access rules
   *   for more than one method (for example, a relationship might want to
   *   simply use the entity's default 'view' access).
   * @param boolean $id_arg
   *   If set, add an argument representing the entity_id. This will be taken from
   *   path index 0.
   * @param boolean $values_arg
   *   If set, add an argument representing the entity values. This will be taken from
   *   the POST data.
   *
   * @return
   *   An info array which can be used as a basis for building a services resource
   *   definition.
   *
   * @see ServicesResourceControllerAbstract::resourceInfo()
   * @see hook_services_resources()
   */
  protected function getInfoElement($entity_type, $controller_method, $access_op = NULL, $id_arg = FALSE, $values_arg = FALSE) {
    $element = array(
      'callback' => '_services_entity_resource_callback',
      'file' => array(
        'type' => 'inc',
        'module' => 'services_entity',
        'name' => 'services_entity.resources',
      ),
      'help' => "Executes the $controller_method operation on entities of type $entity_type",
      'args' => array(
        // This pseudo-argument is how we will pass the specific method name to
        // our generic callback.
        array(
          'name' => 'method',
          'optional' => TRUE,  // Otherwise throws an error
          'default value' => $controller_method,
          'type' => 'string',
          'description' => 'Internal use only: the method to invoke.',
        ),
        // This pseudo-argument is how we will pass the specific entity type to
        // our generic callback.
        array(
          'name' => 'entity_type',
          'optional' => TRUE,  // Otherwise throws an error
          'default value' => $entity_type,
          'type' => 'string',
          'description' => 'Internal use only: the type of entity.',
        ),
      ),
      'access callback' => '_services_entity_access_callback',
      // Specify what will be passed as the $op argument to the access method
      // of the controller; this defaults to the method name.
      'access arguments' => array($access_op ? $access_op : $controller_method),
      'access arguments append' => TRUE,
    );

    // If specified, add an argument representing the entity_id.
    // This will be taken from index 0 of the path.
    if ($id_arg) {
      $element['args'][] = array(
        'name' => $entity_type . '_id',
        'optional' => FALSE,
        'source' => array('path' => 0),
        'type' => 'int',
        'description' => "The $entity_type id.",
      );
    }

    // If specified, add an argument representing the entity data.
    // This will be taken from the post data.
    if ($values_arg) {
      $element['args'][] = array(
        'name' => 'values',
        'optional' => FALSE,
        'source' => 'data',
        'description' => "A representation of the $entity_type",
        'type' => 'struct',
      );
    }

    return $element;
  }

  /**
   * Implemented to define basic CRUD/I operations.
   *
   * May be extended to add arguments to these operations, or to
   * add additional actions or relationships.
   *
   * @see ServicesResourceControllerInterface::resourceInfo()
   */
  public function resourceInfo($entity_type) {
    $info = array();

    $entity_info = entity_get_info($entity_type);
    $replacements = array(
      '@type' => $entity_info['label'],
    );

    // Create.
    if (entity_type_supports($entity_type, 'create')) {
      $info['create'] = $this->getInfoElement($entity_type, 'create', 'create', FALSE, TRUE);
      $info['create']['help'] = t("Creates an entity of type @type.", $replacements);
    }

    // Retrieve.
    $info['retrieve'] = $this->getInfoElement($entity_type, 'retrieve', 'view', TRUE, FALSE);
    $info['retrieve']['help'] = t("Retrieves an entity of type @type.", $replacements);
    $info['retrieve']['args'][] = array(
      'name' => 'fields',
      'optional' => TRUE,
      'type' => 'string',
      'description' => 'A comma separated list of fields to get.',
      'default value' => '*',
      'source' => array('param' => 'fields'),
    );
    $info['retrieve']['args'][] = array(
      'name' => 'revision',
      'optional' => TRUE,
      'type' => 'int',
      'description' => 'The specific revision to retrieve.',
      'default value' => NULL,
      'source' => array('param' => 'revision'),
    );

    // Update.
    if (entity_type_supports($entity_type, 'save')) {
      $info['update'] = $this->getInfoElement($entity_type, 'update', 'update', TRUE, TRUE);
      $info['update']['help'] = t("Updates an entity of type @type.", $replacements);
    }

    // Delete.
    if (entity_type_supports($entity_type, 'delete')) {
      $info['delete'] = $this->getInfoElement($entity_type, 'delete', 'delete', TRUE, FALSE);
      $info['delete']['help'] =  t("Deletes an entity of type @type.", $replacements);
    }

    // Index.
    $info['index'] = $this->getInfoElement($entity_type, 'index', 'index', FALSE, FALSE);
    $info['index']['help'] =  t("Retrieves a list of entities of type @type.", $replacements);
    /**
     * Fields to return.
     *
     * These should be specified in a comma separated list like ?fields=title,created,uid
     */
    $info['index']['args'][] = array(
      'name' => 'fields',
      'optional' => TRUE,
      'type' => 'string',
      'description' => 'A comma separated list of fields to get.',
      'default value' => '*',
      'source' => array('param' => 'fields'),
    );
    /**
     * Filter parameters.
     *
     * These should be specified by ?parameters[title]=My Title&param[created]=4403305
     */
    $info['index']['args'][] = array(
      'name' => 'parameters',
      'optional' => TRUE,
      'type' => 'array',
      'description' => 'Filter parameters array such as parameters[title]="test"',
      'default value' => array(),
      'source' => array('param' => 'parameters'),
    );
    /**
     * Page number.
     *
     * A zero based page number like ?page=3 (returns the fourth page)
     */
    $info['index']['args'][] = array(
      'name' => 'page',
      'optional' => TRUE,
      'type' => 'int',
      'description' => 'The zero-based index of the page to get, defaults to 0.',
      'default value' => 0,
      'source' => array('param' => 'page'),
    );
    /**
     * Page Size.
     *
     * How many records per page to return. ?pagesize=20
     */
    $info['index']['args'][] = array(
      'name' => 'pagesize',
      'optional' => TRUE,
      'type' => 'int',
      'description' => 'Number of records to get per page.',
      'default value' => variable_get('services_entity_' . $entity_type . '_index_page_size', 20),
      'source' => array('param' => 'pagesize'),
    );
    /**
     * Sort field.
     *
     * Which field to sort on. ?sort=created
     */
    $info['index']['args'][] = array(
      'name' => 'sort',
      'optional' => TRUE,
      'type' => 'string',
      'description' => 'Field to sort by.',
      'default value' => '',
      'source' => array('param' => 'sort'),
    );
    /**
     * Sort Direction.
     *
     * Which direction to sort. Possible Values = "ASC|DESC" ?direction=DESC
     */
    $info['index']['args'][] = array(
      'name' => 'direction',
      'optional' => TRUE,
      'type' => 'string',
      'description' => 'Direction of the sort. ASC or DESC.',
      'default value' => 'ASC',
      'source' => array('param' => 'direction'),
    );
    return $info;
  }

}
