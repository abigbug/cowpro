<?php

/**
 * Implements hook_rules_action_info().
 */
function cowpro_message_rules_action_info() {
  $actions = array(
  		'cowpro_fund_topup_finished' => array(
  				'label' => 'cowpro_fund_topup_finished',
  				'group' => t('cowpro'),
  				'parameter' => array(
  						'success' => array(
  								'type' => 'boolean',
  								'label' => t('Executing result'),
  						),
  						'journal' => array(
  								'type' => 'fund_journal',
  								'label' => 'fund journal object',
  						),
  				),
  				'base' => '_cowpro_message_cowpro_fund_topup_finished',
  		),
  		'cowpro_fund_withdraw_finished' => array(
  				'label' => 'cowpro_fund_withdraw_finished',
  				'group' => t('cowpro'),
  				'parameter' => array(
  						'success' => array(
  								'type' => 'boolean',
  								'label' => t('Executing result'),
  						),
  						'journal' => array(
  								'type' => 'fund_journal',
  								'label' => 'fund journal object',
  						),
  				),
  				'base' => '_cowpro_message_cowpro_fund_withdraw_finished',
  		),
    'cowpro_fund_bid_finished' => array(
      'label' => 'cowpro_fund_bid_finished',
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
        'journal' => array(
          'type' => 'fund_journal',
          'label' => 'fund journal object',
        ),
      ),
    	'base' => '_cowpro_message_cowpro_fund_bid_finished',
    ),
  	'cowpro_fund_buy_creditor_assignment_finished' => array(
      'label' => 'cowpro_fund_buy_creditor_assignment_finished',
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
        'buyer_uid' => array(
          'type' => 'integer',
          'label' => 'buyer_uid',
        ),
        'seller_uid' => array(
          'type' => 'integer',
          'label' => 'seller_uid',
        ),
        'amount' => array(
          'type' => 'decimal',
          'label' => 'amount',
        ),
      ),
    	'base' => '_cowpro_message_cowpro_fund_buy_creditor_assignment_finished',
    ),
    'cowpro_fund_make_loans_to_finished' => array(
      'label' => 'cowpro_fund_make_loans_to_finished',
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
    	'base' => '_cowpro_message_cowpro_fund_make_loans_to_finished',
    ),
  	'cowpro_fund_repayment_finished' => array(
      'label' => 'cowpro_fund_repayment_finished',
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
    	'base' => '_cowpro_message_cowpro_fund_repayment_finished',
    ),
  );

  return $actions;
}

/**
 * Implements hook_rules_data_info().
 */
function cowpro_message_rules_data_info() {
	return array(
			'cowpro_issuing' => array(
					'label' => t('Cowpro issuing object'),
					'wrap' => TRUE,
					'property info' => _cowpro_message_rules_cowpro_issuing_info(),
			),
			'cowpro_repayment_schedule' => array(
					'label' => t('Cowpro repayment schedule'),
					'wrap' => TRUE,
					'property info' => _cowpro_message_rules_cowpro_repayment_schedule_info(),
			),
	);
}

/**
 * Defines property info for cowpro issuing.
 */
function _cowpro_message_rules_cowpro_issuing_info() {
	return array(
    'applicant' => array(
      'label' => t('申请人'),
      'description' => '贷款的申请人',
      'type' => 'user',
      'getter callback' => '_cowpro_message_rules_applicant_get',
    ),
    'loan_amounts_decimal' => array(
      'label' => t('贷款总额'),
      'description' => '贷款总金额',
      'type' => 'decimal',
      'getter callback' => '_cowpro_message_rules_loan_amounts_decimal_get',
    ),
    'loan_amounts_integer' => array(
      'label' => t('贷款总额(整数)'),
      'description' => '贷款总金额(整数)',
      'type' => 'integer',
      'getter callback' => '_cowpro_message_rules_loan_amounts_integer_get',
    ),
	);
}

/**
 * Property getter callback returing the applicant (as an user).
 */
function _cowpro_message_rules_applicant_get($data, array $options, $name, $type, $info) {
	return user_load($data->field_applicant[LANGUAGE_NONE][0]['uid']);
}

/**
 * Property getter callback returing the loan amount (as a decimal).
 */
function _cowpro_message_rules_loan_amounts_decimal_get($data, array $options, $name, $type, $info) {
	return $data->field_issuing[LANGUAGE_NONE][0]['loan_amounts'];
}

/**
 * Property getter callback returing the loan amount (as a integer).
 */
function _cowpro_message_rules_loan_amounts_integer_get($data, array $options, $name, $type, $info) {
	return intval($data->field_issuing[LANGUAGE_NONE][0]['loan_amounts']);
}

/**
 * Defines property info for cowpro repayment schedule.
 */
function _cowpro_message_rules_cowpro_repayment_schedule_info() {
	return array(
    'payer_user' => array(
      'label' => t('付款人'),
      'description' => '付款人',
      'type' => 'user',
      'getter callback' => '_cowpro_message_rules_payer_user_get',
    ),
    'receiver_user' => array(
      'label' => t('收款人'),
      'description' => '收款人',
      'type' => 'user',
      'getter callback' => '_cowpro_message_rules_receiver_user_get',
    ),
	'capital_integer' => array(
      'label' => t('当期本金(整数)'),
      'description' => '当期本金(整数)',
      'type' => 'integer',
      'getter callback' => '_cowpro_message_rules_capital_integer_get',
    ),
    'interest_integer' => array(
      'label' => t('当期利息(整数)'),
      'description' => '当期利息(整数)',
      'type' => 'integer',
      'getter callback' => '_cowpro_message_rules_interest_integer_get',
    ),
	);
}

function _cowpro_message_rules_payer_user_get($data, array $options, $name, $type, $info) {
	return user_load($data->payer_uid);
}

function _cowpro_message_rules_receiver_user_get($data, array $options, $name, $type, $info) {
	return user_load($data->receiver_uid);
}

function _cowpro_message_rules_capital_integer_get($data, array $options, $name, $type, $info) {
	return intval($data->capital);
}

function _cowpro_message_rules_interest_integer_get($data, array $options, $name, $type, $info) {
	return intval($data->interest);
}

/**
 * Implements hook_rules_event_info().
 */
function cowpro_message_rules_event_info() {
	$events = array(
    'cowpro_fund_topup_finished' => array(
    		'label' => 'cowpro_fund_topup_finished',
    		'group' => t('cowpro'),
    		'variables' => array(
    				'success' => array(
    						'type' => 'boolean',
    						'label' => t('Executing result'),
    				),
    				'journal' => array(
    						'type' => 'fund_journal',
    						'label' => 'fund journal object',
    				),
    		),
    ),
    'cowpro_fund_withdraw_finished' => array(
    		'label' => 'cowpro_fund_withdraw_finished',
    		'group' => t('cowpro'),
    		'variables' => array(
    				'success' => array(
    						'type' => 'boolean',
    						'label' => t('Executing result'),
    				),
    				'journal' => array(
    						'type' => 'fund_journal',
    						'label' => 'fund journal object',
    				),
    		),
    ),
    'cowpro_fund_bid_finished' => array(
    		'label' => 'cowpro_fund_bid_finished',
    		'group' => t('cowpro'),
    		'variables' => array(
    				'success' => array(
    						'type' => 'boolean',
    						'label' => t('Executing result'),
    				),
    				'node' => array(
    						'type' => 'node',
    						'label' => 'node object',
    				),
    				'journal' => array(
    						'type' => 'fund_journal',
    						'label' => 'fund journal object',
    				),
    		),
    ),
    'cowpro_fund_buy_creditor_assignment_finished' => array(
    		'label' => 'cowpro_fund_buy_creditor_assignment_finished',
    		'group' => t('cowpro'),
    		'variables' => array(
   				'success' => array(
					'type' => 'boolean',
					'label' => t('Executing result'),
   				),
   				'node' => array(
					'type' => 'node',
					'label' => 'node object',
   				),
   				'buyer_uid' => array(
					'type' => 'integer',
					'label' => 'buyer_uid',
   				),
  				'seller_uid' => array(
					'type' => 'integer',
					'label' => 'seller_uid',
   				),
   				'amount' => array(
					'type' => 'decimal',
					'label' => 'amount',
  				),
    		),
    ),
    'cowpro_fund_make_loans_to_finished' => array(
    		'label' => 'cowpro_fund_make_loans_to_finished',
    		'group' => t('cowpro'),
    		'variables' => array(
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
    ),
    'cowpro_fund_repayment_finished' => array(
    		'label' => 'cowpro_fund_repayment_finished',
    		'group' => t('cowpro'),
    		'variables' => array(
   				'success' => array(
					'type' => 'boolean',
					'label' => t('Executing result'),
   				),
		        'cowpro_issuing' => array(
		          'type' => 'cowpro_issuing',
		          'label' => 'cowpro_issuing object',
		        ),
		        'repayment_schedules' => array(
		          'type' => 'list<cowpro_repayment_schedule>',
		          'label' => 'array of repayment schedule',
		        ),
    		),
    ),
  );
  return $events;
}

/**
 * The action function for 'cowpro_fund_topup_finished'.
 */
function _cowpro_message_cowpro_fund_topup_finished($success, $journal) {
	//const COWPRO_SMS_FUND_TOPUP_MESSAGE = '尊敬的用户[user:name]，您刚才充值[cowpro_fund_journal:amount]已成功，特此通知。';
	if ($success) {
		$user = user_load($journal->uid);
		$uid = $user->uid;
		$profile_mobile = cowpro_customer_profile_load_one_row_with_conditions($uid, 'mobile');
		$phone_number = $profile_mobile->mobile_number;

		$data = array();
		$data['cowpro_fund_journal'] = $journal;
		$data['user'] = $user;
		$content = token_replace(variable_get ( 'cowpro_sms_fund_topup_message', COWPRO_SMS_FUND_TOPUP_MESSAGE ), $data);
		cowpro_message_send($phone_number, $content);
	}
}

/**
 * The action function for 'cowpro_fund_withdraw_finished'.
 */
function _cowpro_message_cowpro_fund_withdraw_finished($success, $journal) {
	//const COWPRO_SMS_FUND_WITHDRAW_MESSAGE = '尊敬的用户[user:name]，您刚才的提现申请[cowpro_fund_journal:amount]已提交，特此通知。';
	if ($success) {
		$user = user_load($journal->uid);
		$uid = $user->uid;
		$profile_mobile = cowpro_customer_profile_load_one_row_with_conditions($uid, 'mobile');
		$phone_number = $profile_mobile->mobile_number;

		$data = array();
		$data['cowpro_fund_journal'] = $journal;
		$data['user'] = $user;
		$content = token_replace(variable_get ( 'cowpro_sms_fund_withdraw_message', COWPRO_SMS_FUND_WITHDRAW_MESSAGE ), $data);
		cowpro_message_send($phone_number, $content);
	}
}

/**
 * The action function for 'cowpro_fund_bid_finished'.
 */
function _cowpro_message_cowpro_fund_bid_finished($success, $node, $journal) {
	//const COWPRO_SMS_BID_LENDER_MESSAGE = '尊敬的用户[user:name]，您于[cowpro_fund_journal:created]投标了贷款“[cowpro_issuing:title]”，冻结资金[cowpro_fund_journal:amount]。';
	//const COWPRO_SMS_BID_BORROWER_MESSAGE = '尊敬的用户[cowpro_issuing:applicant]，用户[user:name]于[cowpro_fund_journal:created]投标了贷款“[cowpro_issuing:title]”，冻结资金[cowpro_fund_journal:amount]。';
	if ($success) {
		$user = user_load($journal->uid);
		$uid = $user->uid;
		$profile_mobile = cowpro_customer_profile_load_one_row_with_conditions($uid, 'mobile');
		$phone_number = $profile_mobile->mobile_number;

		$data = array();
		$data['node'] = $node;
		$data['cowpro_issuing'] = $node;//->field_issuing [LANGUAGE_NONE] [0];
		$data['cowpro_fund_journal'] = $journal;
		$data['user'] = $user;
		$content = token_replace(variable_get ( 'cowpro_sms_bid_lender_message', COWPRO_SMS_BID_LENDER_MESSAGE ), $data);
		cowpro_message_send($phone_number, $content);

		/*
		$applicant_user = user_load($node->field_applicant [LANGUAGE_NONE] [0]['uid']);
		$uid = $applicant_user->uid;
		$profile_mobile = cowpro_customer_profile_load_one_row_with_conditions($uid, 'mobile');
		$phone_number = $profile_mobile->mobile_number;

		$data = array();
		$data['node'] = $node;
		$data['cowpro_issuing'] = $node;//->field_issuing [LANGUAGE_NONE] [0];
		$data['cowpro_fund_journal'] = $journal;
		$data['user'] = $user;
		$content = token_replace(variable_get ( 'cowpro_sms_bid_borrower_message', COWPRO_SMS_BID_BORROWER_MESSAGE ), $data);
		cowpro_message_send($phone_number, $content);
		*/
	}
}

/**
 * The action function for 'cowpro_fund_buy_creditor_assignment_finished'.
 */
function _cowpro_message_cowpro_fund_buy_creditor_assignment_finished($success, $node, $buyer_uid, $seller_uid, $amount) {
	//const COWPRO_SMS_CREDITOR_ASSIGNMENT_BUYER_MESSAGE = '尊敬的用户[user:name]，很高兴的通知您，您已成功购买了债权“[cowpro_issuing:title]”，编号：“[cowpro_issuing:number]”。';
	//const COWPRO_SMS_CREDITOR_ASSIGNMENT_SELLER_MESSAGE = '尊敬的用户[user:name]，很高兴的通知您，您转让的债权“[cowpro_issuing:title]”，编号：“[cowpro_issuing:number]”已成功转让。';
	if ($success) {
		$user = user_load($buyer_uid);
		$uid = $user->uid;
		$profile_mobile = cowpro_customer_profile_load_one_row_with_conditions($uid, 'mobile');
		$phone_number = $profile_mobile->mobile_number;

		$data = array();
		$data['node'] = $node;
		$data['cowpro_issuing'] = $node;//->field_issuing [LANGUAGE_NONE] [0];
		$data['cowpro_fund_journal'] = $journal;
		$data['user'] = $user;
		$content = token_replace(variable_get ( 'cowpro_sms_creditor_assignment_buyer_message', COWPRO_SMS_CREDITOR_ASSIGNMENT_BUYER_MESSAGE ), $data);
		cowpro_message_send($phone_number, $content);

		$user = user_load($seller_uid);
		$uid = $user->uid;
		$profile_mobile = cowpro_customer_profile_load_one_row_with_conditions($uid, 'mobile');
		$phone_number = $profile_mobile->mobile_number;

		$data = array();
		$data['node'] = $node;
		$data['cowpro_issuing'] = $node;//->field_issuing [LANGUAGE_NONE] [0];
		$data['cowpro_fund_journal'] = $journal;
		$data['user'] = $user;
		$content = token_replace(variable_get ( 'cowpro_sms_creditor_assignment_seller_message', COWPRO_SMS_CREDITOR_ASSIGNMENT_SELLER_MESSAGE ), $data);
		cowpro_message_send($phone_number, $content);
	}
}

/**
 * The action function for 'cowpro_fund_make_loans_to_finished'.
 */
function _cowpro_message_cowpro_fund_make_loans_to_finished($success, $node, $fund_journals) {
	_cowpro_message_cowpro_fund_make_loans_to_finished_message_send($success, $node, $fund_journals);
}

function _cowpro_message_cowpro_fund_make_loans_to_finished_message_send($success, $node, $fund_journals) {
	//const COWPRO_SMS_MAKE_LOANS_TO_LENDER_MESSAGE = '尊敬的用户[user:name]，您投标的贷款“[cowpro_issuing:title]”已于[cowpro_issuing:sign_date]满标，资金已划拨给贷款人。';
	//const COWPRO_SMS_MAKE_LOANS_TO_BORROWER_MESSAGE = '尊敬的用户[user:name]，您的贷款“[cowpro_issuing:title]”已于[cowpro_issuing:sign_date]满标，资金已划拨到您指定的账户，请注意查收。';
	if ($success) {
		foreach ($fund_journals as $journal) {
			$user = user_load($journal->uid);
			$uid = $user->uid;
			$profile_mobile = cowpro_customer_profile_load_one_row_with_conditions($uid, 'mobile');
			$phone_number = $profile_mobile->mobile_number;

			$data = array();
			$data['node'] = $node;
			$data['cowpro_issuing'] = $node;//->field_issuing [LANGUAGE_NONE] [0];
			$data['user'] = $user;
			$data['cowpro_fund_journal'] = $journal;
			$content = token_replace(variable_get ( 'cowpro_sms_make_loans_to_lender_message', COWPRO_SMS_MAKE_LOANS_TO_LENDER_MESSAGE ), $data);
			cowpro_message_send($phone_number, $content);
		}

		/*
		$user = user_load($node->field_applicant [LANGUAGE_NONE] [0]['uid']);
		$uid = $user->uid;
		$profile_mobile = cowpro_customer_profile_load_one_row_with_conditions($uid, 'mobile');
		$phone_number = $profile_mobile->mobile_number;

		$data = array();
		$data['node'] = $node;
		$data['cowpro_issuing'] = $node;//->field_issuing [LANGUAGE_NONE] [0];
		$data['user'] = $user;
		$content = token_replace(variable_get ( 'cowpro_sms_make_loans_to_borrower_message', COWPRO_SMS_MAKE_LOANS_TO_BORROWER_MESSAGE ), $data);
		cowpro_message_send($phone_number, $content);
		*/
	}
}

/**
 * The action function for 'cowpro_fund_repayment_finished'.
 */
function _cowpro_message_cowpro_fund_repayment_finished($success, $node, $repayment_schedules) {
	//const COWPRO_SMS_REPAYMENT_PAYER_MESSAGE = '尊敬的用户[user:name]，您的贷款“[cowpro_issuing:title]”第[cowpro_repayment_schedule:period]/[cowpro_repayment_schedule:period_total]期还款已完成，本期还款总金额[cowpro_repayment_schedule:payable_total_current_period]。';
	//const COWPRO_SMS_REPAYMENT_RECEIVER_MESSAGE = '尊敬的用户[user:name]，您的投资“[cowpro_issuing:title]”第[cowpro_repayment_schedule:period]/[cowpro_repayment_schedule:period_total]期还款已完成，还款金额[cowpro_repayment_schedule:payable_amount]已划拨到您指定的账户，请注意查收。';

	if ($success) {
		foreach ($repayment_schedules as $repayment) {
			$user = user_load($repayment->receiver_uid);
			$uid = $user->uid;
			$profile_mobile = cowpro_customer_profile_load_one_row_with_conditions($uid, 'mobile');
			$phone_number = $profile_mobile->mobile_number;

			$data = array();
			$data['node'] = $node;
			$data['cowpro_issuing'] = $node;//->field_issuing [LANGUAGE_NONE] [0];
			$data['user'] = $user;
			$data['cowpro_repayment_schedule'] = $repayment;
			$content = token_replace(variable_get ( 'cowpro_sms_repayment_receiver_message', COWPRO_SMS_REPAYMENT_RECEIVER_MESSAGE ), $data);
			cowpro_message_send($phone_number, $content);
		}

		/*
		$values = array_values ( $repayment_schedules );
		$repayment = array_shift($values);
		$user = user_load($node->field_applicant [LANGUAGE_NONE] [0]['uid']);
		$uid = $user->uid;
		$profile_mobile = cowpro_customer_profile_load_one_row_with_conditions($uid, 'mobile');
		$phone_number = $profile_mobile->mobile_number;

		$data = array();
		$data['node'] = $node;
		$data['cowpro_issuing'] = $node;//->field_issuing [LANGUAGE_NONE] [0];
		$data['user'] = $user;
		$data['cowpro_repayment_schedule'] = $repayment;
		$content = token_replace(variable_get ( 'cowpro_sms_repayment_payer_message', COWPRO_SMS_REPAYMENT_PAYER_MESSAGE ), $data);
		cowpro_message_send($phone_number, $content);
		*/
	}
}
