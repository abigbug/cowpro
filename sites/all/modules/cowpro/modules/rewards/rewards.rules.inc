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
  				'group' => t('cowpro'),
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
	  'cowpro_reward_repayment_finished' => array(
	  		'label' => '到期还款以后，发放奖励',
	  		'group' => t('cowpro'),
	  		'parameter' => array(
	  				'success' => array(
	  						'type' => 'boolean',
	  						'label' => t('Executing result'),
	  				),
	  				'cowpro_issuing' => array(
	  						'type' => 'cowpro_issuing',
	  						'label' => 'Cowpro issuing object',
	  				),
	  				'repayment_schedules' => array(
	  						'type' => 'list<cowpro_repayment_schedule>',
	  						'label' => 'array of repayment schedule',
	  				),
	  		),
	  		'base' => '_cowpro_reward_repayment_finished',
	  ),
  );
}

/**
 * The action function for 'cowpro_fund_make_loans_to_finished'.
 */
function _cowpro_reward_make_loans_to_finished($success, $node, $fund_journals) {
	_cowpro_reward_make_loans_to_finished_grant_points($success, $node, $fund_journals);
}

function _cowpro_reward_repayment_finished($success, $node, $repayment_schedules) {
	_cowpro_reward_repayment_finished_grant_points($success, $node, $repayment_schedules);
}

function _cowpro_reward_make_loans_to_finished_grant_points($success, $node, $fund_journals) {
	if ($success) {
		$loan_term = $node->field_issuing [LANGUAGE_NONE] [0]['loan_term'];
		foreach ($fund_journals as $journal) {
			$loan_amount = $journal->amount;
			$annualized_amount = ($loan_term / 360) * $loan_amount;//年化投资额
			$points = round($annualized_amount / 50);//年化投资额的五十分之一，做为投资者的奖励积分

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
						'tid' => 0,//积分
				);
				userpoints_userpointsapi($params);
			}
		}
	}
}
function _cowpro_reward_repayment_finished_grant_points($success, $node, $repayment_schedules) {
	if ($success) {
		$conditions = array();
		$conditions['internal_reference_id'] = 'ISSUING-' . $nid;
		$conditions['type'] = 'BID';
		$conditions['status'] = TRUE;
		$ids = FALSE;
		$reset = TRUE;
		$fund_journals = entity_load('cowpro_fund_journal', $ids, $conditions, $reset);

		$loan_term = $node->field_issuing [LANGUAGE_NONE] [0]['loan_term'];
		$schedule = array_shift($repayment_schedules);
		$period_total = $schedule->period_total;
		$period_remark = '第[' . $schedule->period . ']/[' . $schedule->period_total . ']期';
		$role = user_role_load_by_name('员工');

		foreach ($fund_journals as $journal) {
			$loan_amount = $journal->amount;
			$annualized_amount = ($loan_term / 360) * $loan_amount;//年化投资额
			$bonus1 = round(($annualized_amount / $period_total) * 3 / 1000);//年化投资额的千分之三，以现金的形式奖励投资人的推荐人
			$bonus2 = round(($annualized_amount / $period_total) * 2 / 1000);//年化投资额的千分之二，以现金的形式奖励投资人的推荐人的推荐人

			$term = current(taxonomy_get_term_by_name('奖金'));
			$uid_referree = -1;
			if ($bonus1 > 0) {
				//奖励投资人的推荐人
				$relationship_type = user_relationships_type_load(array('name'=>'朋友'));
				$relationships = user_relationships_load(array(
						'requester_id' => $uid,
						'rtid'    => $relationship_type->rtid,
				));

				$relationship = array_shift($relationships);
				if ($relationship) {
					$uid_referree = $relationship->requestee_id;
					if (!user_has_role($role->rid, $uid_referree)) {
						$params = array (
								'uid' => $uid_referree,
								'points' => $bonus1,
								'description' => '推荐他人投资奖励（一级）,用户：' . $user->name . ',贷款：' . $node->title . ',' . $period_remark,
								'display' => FALSE,
								'entity_type' => 'node',
								'entity_id' => $node->nid,
								'tid' => $term->tid,//奖金
						);
						userpoints_userpointsapi($params);
					}
				}
			}

			if (($bonus2 > 0) && ($uid_referree != -1)) {
				//奖励投资人的推荐人的推荐人
				$relationship_type = user_relationships_type_load(array('name'=>'朋友'));
				$relationships = user_relationships_load(array(
						'requester_id' => $uid_referree,
						'rtid'    => $relationship_type->rtid,
				));

				$relationship = array_shift($relationships);
				if ($relationship) {
					$uid_referree = $relationship->requestee_id;
					if (!user_has_role($role->rid, $uid_referree)) {
						$params = array (
							'uid' => $uid_referree,
							'points' => $bonus2,
							'description' => '推荐他人投资奖励（二级）,用户：' . $user->name . ',贷款：' . $node->title . ',' . $period_remark,
							'display' => FALSE,
							'entity_type' => 'node',
							'entity_id' => $node->nid,
							'tid' => $term->tid,//奖金
						);
						userpoints_userpointsapi($params);
					}
				}
			}

		}
	}
}
