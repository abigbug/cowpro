<?php

/**
 *
 * @file
 * Provide better integration into the rules group
 */

/**
 * Implementation of hook_rules_event_info().
 */
function cowpro_check_in_rules_event_info() {
  return array(
    'cowpro_promotion_user_check_in' => array(
      'label' => '用户签到',
      'group' => t('cowpro promotion'),
      'variables' => array(
        'account' => array(
          'type' => 'user',
          'label' => t('registered user')
        )
      )
    )
  );
}

/**
 * Implements hook_rules_action_info().
 */
function cowpro_check_in_rules_action_info() {
  return array(
    'cowpro_check_in_grant_points' => array(
      'label' => '用户签到之后，奖励一个积分',
      'group' => t('cowpro promotion'),
      'parameter' => array(
        'account' => array(
          'type' => 'user',
          'label' => t('registered user')
        )
      ),
      'base' => '_cowpro_check_in_grant_points'
    )
  );
}

/**
 * The action function for 'cowpro_check_in_grant_points'.
 */
function _cowpro_check_in_grant_points($account) {
  $uid = $account->uid;
  $points = 1;
  $params = array(
    'uid' => $uid,
    'points' => $points,
    'description' => '签到奖励',
    'display' => FALSE,
    'tid' => 0 // 积分
  );
  userpoints_userpointsapi($params);
  $block = block_load("cowpro_fund", "cowpro_fund_user");
  $cache_id = _block_get_cache_id($block);
  
  cache_clear_all($cache_id, "cache_block");
  drupal_set_message('签到奖励积分1个！');
}
