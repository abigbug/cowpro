<?php
/**
 * @file
 * cowpro_features.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function cowpro_features_taxonomy_default_vocabularies() {
  return array(
    'tags' => array(
      'name' => '标签',
      'machine_name' => 'tags',
      'description' => '用标签将相似的文章分门别类。',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 0,
      'rdf_mapping' => array(
        'rdftype' => array(
          0 => 'skos:ConceptScheme',
        ),
        'name' => array(
          'predicates' => array(
            0 => 'dc:title',
          ),
        ),
        'description' => array(
          'predicates' => array(
            0 => 'rdfs:comment',
          ),
        ),
      ),
    ),
  );
}
