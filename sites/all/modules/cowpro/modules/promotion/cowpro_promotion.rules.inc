<?php

/**
 * @file
 * Provide better integration into the rules group
 */

/**
 * Implements hook_rules_condition_info() on behalf of the cowpro promotion module.
 */
function cowpro_promotion_rules_condition_info() {
  return array(
    'owpro_promotion_validity' => array(
      'label' => t('在有效期内'),
      'parameter' => array(
        'action_fired' => array(
          'type' => 'text',
          'label' => t('要验证的模块名'),
        ),
      ),
      'group' => t('cowpro promotion'),
      'base' => 'cowpro_promotion_rules_condition_validity',
    ),
  );
}

function cowpro_promotion_rules_condition_validity($action_fired) {
  $result = TRUE;
  $info = cowpro_promotion_info_list()[$action_fired];
  $begin = $info['duration_begin'];
  $end = $info['duration_end'];
  $format = 'Y-m-d H:i:s';
  $begin = DateTime::createFromFormat($format, $begin);
  $end = DateTime::createFromFormat($format, $end);
  
  $now = new DateTime("now");
  if ($begin !== FALSE) {
    $result = $result && ($now > $begin);
  }
  if ($end !== FALSE) {
    $result = $result && ($now < $end);
  }
  return $result;
}