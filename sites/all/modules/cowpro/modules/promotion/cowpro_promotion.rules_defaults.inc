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
    $configs[$key] = _cowpro_promotion_build_rule($promotion);
  }
  return $configs;
}

function _cowpro_promotion_build_rule($promotion) {
  $rule = rules_reaction_rule();
  $rule->label = $promotion['title'];
  $rule->active = TRUE;
  $rule->event($promotion['event'])
  ->condition(rules_condition('owpro_promotion_validity', array('action_fired' => $promotion['module'])))
  ->action($promotion['action'], array());
  return $rule;
}
