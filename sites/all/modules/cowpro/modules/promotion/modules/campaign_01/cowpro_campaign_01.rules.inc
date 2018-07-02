<?php

/**
 * @file
 * Provide better integration into the rules group
 */

/**
 * Implements hook_rules_action_info().
 */
function cowpro_campaign_01_rules_action_info() {
  return array(
  		'cowpro_campaign_01_make_loans_to_finished' => array(
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
  				'base' => '_cowpro_campaign_01_make_loans_to_finished',
  		),
  );
}

/**
 * The action function for 'cowpro_fund_make_loans_to_finished'.
 */
function _cowpro_campaign_01_make_loans_to_finished($success, $node, $fund_journals) {
  _cowpro_campaign_01_make_loans_to_finished_grant_points($success, $node, $fund_journals);
}

function _cowpro_campaign_01_make_loans_to_finished_grant_points($success, $node, $fund_journals) {
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
				$desc = '投资奖励,' . '贷款：' . $node->title;
				$params = array (
						'uid' => $uid,
						'points' => $points,
						'description' => $desc,
						'display' => FALSE,
						'entity_type' => 'node',
						'entity_id' => $node->nid,
						'tid' => 0,//积分
				);
				userpoints_userpointsapi($params);
				watchdog('COWPRO_CAMPAIGN_01', "uid:$uid;$desc", NULL, WATCHDOG_DEBUG);
			}
		}
	}
}
