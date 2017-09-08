Services Entity
===============

Services Entity allows you to use any entity type with Services, going beyond
the core entity types that Services supports.

Each entity type is defined as a new resource, with the usual services: create,
retrieve, update, delete, and index.

Entity types must declare an access callback (see entity_crud_hook_entity_info()
in Entity API's hook documentation, and also entity_access()).

Entity Processors
-----------------

Services Entity comes with two entity processors. These determine the way in
which the provided resources handle parameters:

* The Generic Entity Processor returns and expects an entity structure exactly
  as Drupal uses internally.
* The Clean Entity Processor uses a simplified version of the entity structure,
  with 'Drupalisms' such as deep field arrays removed. It also uses Entity API
  metadata property names instead of entity schema property names.

Resources
---------

An entity type 'foo' has a resource 'entity_foo' defined for it. On this the
following services are defined:

- create:
  - Send the object data in the body.
  - Returns newly created entity.

- update:
  - Send the object data in the body.
  - Returns 200 if successful.

- retrieve
  Has the following query string parameters:
  - 'fields': specify which fields to return.
    For example: endpoint/entity_node/1?fields=title,nid

- delete
  - Returns 200 if successful.

- index
  Has the following query string parameters:
  - 'fields': A comma separated list of fields to get.
  - 'parameters': Filter parameters array of entity properties, such as
    parameters[title]="test"
  - 'page': The zero-based index of the page to get, defaults to 0.
  - 'pagesize': Number of records to get per page. This has a maximum imposed on
    it to prevent excessive load to the server. By default this is 100, but this
    may be changed in the admin settings.
  - 'sort': Field or property to sort by.
  - 'direction': Direction of the sort. ASC or DESC.

  Custom Controllers
  ------------------
  You may provide your own controllers, either globally or for specific entities.
  These should implement the ServicesResourceControllerInterface.

  A global controller should be registered by implementing
  hook_services_entity_resource_info(). It may then be chosen in the UI, or by
  setting the 'services_entity_resource_class" system variable.

  An entity-specific controller should be registered by implementing
  hook_entity_info() or hook_entity_info_alter() and adding a
  'resource controller' key to the info array.  The specified class will then be
  used for that entity type.

  A custom controller must implement the resourceInfo() method to describe the
  operations, actions and relationships which it provides. For convenience, the
  ServicesResourceControllerAbstract class is provided to define basic CRUD/I
  operations. You may extend this to add additional arguments, actions or
  relationships. Note: this class provides definitions only; you must extend to
  provide implementations yourself.
