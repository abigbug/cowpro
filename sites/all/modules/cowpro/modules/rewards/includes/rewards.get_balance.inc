<?php
function cowpro_rewards_get_balance_amount_go_form($form, &$form_state){
    $form ['description'] = array (
			'#type' => 'markup',
			'#markup' => t ( '' )
	);
	$form ['submit'] = array (
			'#type' => 'submit',
			'#value' => '查询最新借款人余额'
	);
	return $form;
}

function cowpro_rewards_get_balance_amount_go_form_submit($form, &$form_state) {
	$function = 'cowpro_rewards_get_balance_amount_go_batch';
	$batch = $function ();
	batch_set ( $batch );
}
function cowpro_rewards_get_balance_amount_go_batch() {
        $debtor_uids = cowpro_rewords_get_role_uids('debtor');
        //清空数据表
        db_query("truncate user_balance");
        $i = 0;
        $operations = array();
        
        if ($debtor_uids) {
          foreach ($debtor_uids as $row) {
                $uid = $row;
                $i ++;
		$operations[] = array (
				'cowpro_rewards_get_balance_op_user',
				array (
					$uid,
					t( '(用户ID @operation)', array (
					'@operation' => $uid,
					))
				)
		); 
	  }
        }
	drupal_set_message ( t ( '生成用户余额，共  @num 项', array (
			'@num' => $i,
	) ) );
	$batch = array (
		'operations' => $operations,
		'finished' => 'cowpro_rewards_get_balance_finished',
                'file' => drupal_get_path('module', 'cowpro_rewards') . '/includes/rewards.get_balance.inc',
	);
	return $batch;
}

function cowpro_rewards_get_balance_op_user($uid, $operation_details, &$context){
     $balance = cowpro_fund_get_balance($uid);
     $profile_real_name = cowpro_customer_profile_load_one_row_with_conditions ( $uid, 'real_name' );
     $nickname = db_query("SELECT name FROM {users} WHERE uid = $uid")->fetchField();
     db_insert('user_balance')
          ->fields(array(
            'uid' => $uid,
            'balance' => $balance['balance'],
             'name' => $profile_real_name->name,
             'nickname' => $nickname,
             'created' => time(),
             'updated' => time(),
            ))
          ->execute();
}

function cowpro_rewards_get_balance_finished($success, $results, $operations) {
	if ($success) {
                global $base_url;
		drupal_set_message('生成成功');
                drupal_goto ( $base_url . "/cowpro/rewards/report" );
	} else {
		$error_operation = reset ( $operations );
		drupal_set_message ( t ( 'An error occurred while processing @operation with arguments : @args', array (
				'@operation' => $error_operation [0],
				'@args' => print_r ( $error_operation [0], TRUE )
		) ), 'error' );
	}
}

