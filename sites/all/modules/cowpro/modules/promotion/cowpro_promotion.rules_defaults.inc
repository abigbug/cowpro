<?php
/**
 * @file
 * cowpro_promotion.rules_defaults.inc
 */

/**
 * Implements hook_default_rules_configuration().
 */
function cowpro_promotion_default_rules_configuration() {
  $promotion_info_list = cowpro_promotion_info_list();
  
  $configs = array();
  foreach ($promotion_info_list as $key => $promotion) {
    $configs[$key] = _cowpro_promotion_build_rule($key, $promotion);
  }
  return $configs;
}

function _cowpro_promotion_build_rule($key, $promotion) {
  $rule = rules_reaction_rule();
  $rule->label = $promotion['title'];
  $rule->active = TRUE;
  $rule->event($promotion['event'])
  ->condition(rules_condition('cowpro_promotion_validity', array('action_fired' => $key)))
  ->action($promotion['action'], array());
  return $rule;
}
