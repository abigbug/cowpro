<?php
/**
 * @file
 * cowpro_bank_list.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function cowpro_bank_list_taxonomy_default_vocabularies() {
  return array(
    'bank_list' => array(
      'name' => '银行列表',
      'machine_name' => 'bank_list',
      'description' => '用户提现的时候可选择的银行',
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
