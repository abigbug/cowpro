<?php

/**
 * @file
 * ThemeKey's variant of class EntityFieldQuery.
 *
 * @author Markus Kalkbrenner | mkalkbrenner
 *   @see http://drupal.org/user/124705
 */

/**
 * Class ThemeKeyEntityFieldQuery
 *
 * Adds all field values of fields added by fieldCondition() to the
 * EntityFieldQuery::$orderedResult
 */
class ThemeKeyEntityFieldQuery extends EntityFieldQuery {

  /**
   * Finishes the query.
   *
   * Adds tags, metaData, range and returns the requested list or count.
   *
   * @param SelectQuery $select_query
   * A SelectQuery which has entity_type, entity_id, revision_id and bundle
   * fields added.
   * @param $id_key
   * Which field's values to use as the returned array keys.
   *
   * @return
   * See EntityFieldQuery::execute().
   */
  function finishQuery($select_query, $id_key = 'entity_id') {
    foreach ($this->tags as $tag) {
      $select_query->addTag($tag);
    }
    foreach ($this->metaData as $key => $object) {
      $select_query->addMetaData($key, $object);
    }
    $select_query->addMetaData('entity_field_query', $this);
    if ($this->range) {
      $select_query->range($this->range['start'], $this->range['length']);
    }
    if ($this->count) {
      return $select_query->countQuery()->execute()->fetchField();
    }
    $return = array();

    foreach ($this->fields as $key => $field) {
      if ('field_sql_storage' == $field['storage']['type']) {
        foreach ($select_query->conditions() as $condition) {
          if (is_array($condition)
            && array_key_exists('field', $condition)
            && strpos($condition['field'], 'field_data_' . $field['field_name'] . $key . '.') === 0
          ) {
            list($table_alias, $column) = explode('.', $condition['field']);
            $select_query->addField($table_alias, $column, $field['field_name']);
            break;
          }
        }
      }
    }

    $this->orderedResults =array();
    foreach ($select_query->execute() as $partial_entity) {
      $bundle = isset($partial_entity->bundle) ? $partial_entity->bundle : NULL;
      $entity = entity_create_stub_entity($partial_entity->entity_type, array($partial_entity->entity_id, $partial_entity->revision_id, $bundle));
      $return[$partial_entity->entity_type][$partial_entity->$id_key] = $entity;
      $this->orderedResults[] = $partial_entity;
    }
    return $return;
  }
}
