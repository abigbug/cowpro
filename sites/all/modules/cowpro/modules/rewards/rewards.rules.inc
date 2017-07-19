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
  		'cowpro_reward_make_loans_to_finished' => array(
  				'label' => '满标放款以后，发放积分奖励',
  				'group' => t('Cowpro'),
  				'parameter' => array(
  						'success' => array(
  								'type' => 'boolean',
  								'label' => t('Executing result'),
  						),
  						'node' => array(
  								'type' => 'node',
  								'label' => 'node object',
  						),
  						'fund_journals' => array(
  								'type' => 'unknown',
  								'label' => 'array of fund journal',
  						),
  				),
  				'base' => '_cowpro_reward_make_loans_to_finished',
  		),
  );
}

/**
 * The action function for 'cowpro_fund_make_loans_to_finished'.
 */
function _cowpro_reward_make_loans_to_finished($success, $node, $fund_journals) {
	_cowpro_reward_make_loans_to_finished_grant_points($success, $node, $fund_journals);
}

function _cowpro_reward_make_loans_to_finished_grant_points($success, $node, $fund_journals) {
	if ($success) {
		$loan_term = $node->field_issuing [LANGUAGE_NONE] [0]['loan_term'];
		foreach ($fund_journals as $journal) {
			$loan_amount = $journal->amount;
			$annualized_amount = ($loan_term / 360) * $loan_amount;
			$points = round($annualized_amount / 50);

			if ($points > 0) {
				//奖励投资人
				$user = user_load($journal->uid);
				$uid = $user->uid;
				$params = array (
						'uid' => $uid,
						'points' => $points,
						'description' => '投资奖励,' . '贷款：' . $node->title,
						'display' => FALSE,
						'entity_type' => 'node',
						'entity_id' => $node->nid,
						'tid' => 0,
				);
				userpoints_userpointsapi($params);

				//奖励投资人的推荐人
				$relationship_type = user_relationships_type_load(array('name'=>'朋友'));
				$relationships = user_relationships_load(array(
						'requester_id' => $uid,
						'rtid'    => $relationship_type->rtid,
				));

				$relationship = array_shift($relationships);
				if ($relationship) {
					$uid_referree = $relationship->requestee_id;
					$params = array (
							'uid' => $uid,
							'points' => $points,
							'description' => '推荐他人投资奖励,用户：' . $user->name . ',贷款：' . $node->title,
							'display' => FALSE,
							'entity_type' => 'node',
							'entity_id' => $node->nid,
							'tid' => 1,
					);
					userpoints_userpointsapi($params);
				}
			}

		}
	}
}
