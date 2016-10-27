<?php

/**
 * @file
 * Provide better integration into the rules group
 */

/**
 * Implements hook_rules_action_info().
 */
function rewards_rules_action_info() {
  return array(
    'rewards_action_grant_points' => array(
      'label' => '向介绍人发放奖励',
      'named parameter' => TRUE,
      'parameter' => array(
        'user' => array(
          'type' => 'user',
          'label' => t('User'),
          'description' => '被介绍人，我们将找到该用户的介绍人并向其发放奖励',
        ),
        'points' => array(
          'type' => 'integer',
          'label' => t('!Points', userpoints_translation()),
          'description' => '奖励基数（实际奖励量是“奖励基数X百分比”然后取整的结果）',
        ),
        'percent' => array(
          'type' => 'integer',
          'label' => '奖励百分比%',
          'description' => '奖励百分比（实际奖励量是“奖励基数X百分比”然后取整的结果）',
        ),
      	'tid' => array(
          'label' => t('!Points category', userpoints_translation()),
          'type' => 'integer',
          'options list' => 'rewards_get_categories',
        ),
        'entity' => array(
          'label' => t('Entity'),
          'type' => 'entity',
          'description' => t('The entity to which this transaction refers.'),
          'optional' => TRUE,
         ),
        'description' => array(
          'label' => t('Description'),
          'type' => 'text',
          'description' => t('Can contain the reason why the points have been granted.'),
          'restriction' => 'input',
          'optional' => TRUE,
        ),
        'operation' => array(
          'label' => t('Operation'),
          'type' => 'text',
          'description' => t('Describes the operation (Insert/Remove/...).'),
          'restriction' => 'input',
        ),
        'reference' => array(
          'label' => t('Reference'),
          'type' => 'text',
          'description' => t('Can contain a reference for this transaction.'),
          'optional' => TRUE,
        ),
        'display' => array(
          'label' => t('Display'),
          'type' => 'boolean',
          'description' => t('Whether or not to show a message to the user when this !points transaction is added.', userpoints_translation()),
          'default value' => TRUE,
        ),
        'moderate' => array(
          'label' => t('Moderate'),
          'type' => 'text',
          'description' => t('Whether or not this !points transaction should be moderated.', userpoints_translation()),
          'options list' => 'rewards_moderate',
        ),
        'expirydate' => array(
          'label' => t('Expiration Date'),
          'type' => 'date',
          'description' => t('Define when the !points should expire.', userpoints_translation()),
          'optional' => TRUE,
        ),
      ),
      'group' => t('cowpro rewards'),
    ),
  );
}

/**
 * Wrapper function for userpoints_get_categories().
 *
 * Rules.module uses different arguments for option list callbacks than
 * userpoints_get_categories expects.
 */
function rewards_get_categories() {
  return userpoints_get_categories();
}

/**
 * Simple callback that lists the categories including an option for all.
 */
function rewards_get_all_categories() {
  return array('all' => t('All categories')) + userpoints_get_categories();
}

/**
 * Simple callback that lists the possible moderate values.
 */
function rewards_moderate() {
  return array(
    'default' => t('Use the site default'),
    'approved' => t('Automatically approved'),
    'moderated' => t('Added to moderation'),
  );
}

/**
 * Implements hook_rules_data_info().
 */
/*
function rewards_rules_data_info() {
  return array(
    'userpoints_transaction' => array(
      'label' => t('!Points transaction', userpoints_translation()),
      'wrap' => TRUE,
      'property info' => _userpoints_userpoints_transaction_properties(),
    ),
  );
}
*/

/**
 * Rules action - grant points to a user.
 */
function rewards_action_grant_points($params) {
  // Map $moderate value to the actual value used by the API.
  $moderate_mapping = array(
    'default' => NULL,
    'approved' => FALSE,
    'moderated' => TRUE,
  );
  $uid = is_object($params['user']->uid) ? $params['user']->getIdentifier() : $params['user']->uid;
  $relationship_type = user_relationships_type_load(array('name'=>'朋友'));
  $relationships = user_relationships_load(array(
  		'requester_id' => $uid,
  		'rtid'    => $relationship_type->rtid,
  ));

  $relationship = array_shift($relationships);
  if (! $relationship) {
  	return;
  }
  $uid_referree = $relationship->requestee_id;

  $percent = $params['percent'];
  $entity = $params['entity']->value();
  $interest = $entity->interest;
  $points = round($interest * $percent / 100);
  $params['points'] = $points;
  $user_name = $params['user']->name;
  $issuing_id = $entity->issuing_id;
  $period = $entity->period;
  $period_total = $entity->period_total;
  $description = "推荐人奖励，$user_name(id:$uid) 贷款申请表编号$issuing_id 第 $period 期/共 $period_total 期 还款，利息$interest";
  $params['description'] = $description;

  $params = array(
    // User id might be a int or a EntityValueWrapper.
    'uid' => $uid_referree,
    'entity_type' => 'cowpro_repayment_schedule',
    'entity_id' => $entity->schedule_id,
    'moderate' => $moderate_mapping[$params['moderate']],
    // Rules defaults to FALSE if the date format can not be parsed.
    // Use NULL instead since FALSE means no expiration.
    'expirydate' => $params['expirydate'] ? $params['expirydate'] : NULL,
  ) + $params;

  unset($params['state']);
  unset($params['user']);
  unset($params['entity']);
  unset($params['settings']);
  userpoints_userpointsapi($params);
}

function rewards_action_grant_points_form_alter(&$form, &$form_state) {
  // Empty value by default.
  $form['parameter']['expirydate']['settings']['expirydate']['#default_value'] = '';
  // Operation is a single line textfield.
  $form['parameter']['operation']['settings']['operation']['#type'] = 'textfield';
}
