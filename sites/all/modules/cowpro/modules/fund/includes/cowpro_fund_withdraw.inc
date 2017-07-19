<?php
function cowpro_fund_withdraw($form, &$form_state) {
	$form = array ();

	$custodian_key = custodian_default_provider_key();
	$custodian_title = custodian_readable_provider_title($custodian_key);
	$interface = array($custodian_key => $custodian_title);
	$form ['withdraw_interface'] = array (
			'#type' => 'radios',
			'#title' => '提现渠道',
			'#default_value' => $custodian_key,
			'#options' => $interface,
			'#description' => ''
	);

	$form += cowpro_fund_bankcard_list ();

	ctools_include ( 'modal' );
	ctools_include ( 'ajax' );
	ctools_modal_add_js ();
	$form ['add-bankcard'] = array (
			'#markup' => ctools_modal_text_button ( '添加银行卡', 'cowpro/fund/bankcard/add', '添加银行卡' )
	);

	GLOBAL $user;
	$balance = custodian_get_balance($user);
	$withdraw = 0;
	if ($balance) {
		$withdraw = $balance ['withdraw'];
	}

	$form ['withdraw_balance'] = array (
			'#markup' => "<p>可提现余额(元)：$withdraw</p>",
	);
	$form ['amount'] = array (
			'#type' => 'numberfield',
			'#title' => '提现金额(元)',
			'#step' => 0.01,
			'#min' => 0,
			'#max' => 999999,
			'#default_value' => 0,
			'#input' => TRUE
	);

	$form ['withdraw'] = array (
			'#type' => 'submit',
			'#value' => '提现'
	);

	return $form;
}
function cowpro_fund_withdraw_validate($form, &$form_state) {
	if (is_null ( $form_state ['input'] ['bankcard_id'] )) {
		form_error ( $form ['bankcard'], "请指定银行卡" );
	}
	if (( float ) trim ( $form_state ['input'] ['amount'] ) <= 0) {
		form_error ( $form ['amount'], "请填写有效的提现金额" );
	}
}
function cowpro_fund_withdraw_submit($form, &$form_state) {
	$amount = $form_state ['input'] ['amount'];
	//$moudle = $form_state ['input'] ['withdraw_interface'];
	$bankcard_id = $form_state ['input'] ['bankcard_id'];
	$card = entity_load_single ( 'cowpro_fund_bankcard', $bankcard_id );

	$uid = $GLOBALS['user']->uid;
	$entity_value = array(
			'uid' => $uid,
			'status' => FALSE,
			'type' => 'WITHDRAW',
			'amount' => $amount,
	);
	$entity = entity_create('cowpro_fund_journal', $entity_value);
	$entity = entity_get_controller('cowpro_fund_journal')->save($entity);
	$journal_id = $entity->journal_id;

	$result = custodian_cowpro_fund_withdraw($uid, $amount,	$card, $journal_id);
}
function _cowpro_fund_get_bankcards($reset = FALSE) {
	// Get the bankcard data.
	$conditions = array (
			'uid' => $GLOBALS ['user']->uid
	);
	$cards = entity_load ( 'cowpro_fund_bankcard', array (), $conditions, $reset );
	return $cards;
}
function cowpro_fund_bankcard_list($reset = FALSE) {
	ctools_include ( 'modal' );
	ctools_include ( 'ajax' );
	$form = array ();
	$form ['bankcard'] = array (
			'#type' => 'fieldset',
			'#title' => '',
			'#prefix' => '<div id="bankcard-list">',
			'#suffix' => '</div>'
	);

	// Build the sortable table header.
	$header = array (
			'card_no' => '卡号',
			'bank_name' => '银行',
			'cardholder' => '持卡人',
			'operation' => '操作'
	);

	$cards = _cowpro_fund_get_bankcards($reset);

	// Build the rows.
	$options = array ();
	$default_value = NULL;
	foreach ( $cards as $card ) {
		$bankcard_id = $card->bankcard_id;
		if (is_null($default_value)) {
			$default_value = $bankcard_id;
		}
		$options [$bankcard_id] = array (
				'card_no' => $card->card_no,
				'bank_name' => $card->bank_name,
				'cardholder' => $card->cardholder,
				'operation' => ctools_ajax_text_button ( '删除', "cowpro/fund/bankcard/$bankcard_id/delete", '删除该银行卡信息' ),
				'#attributes' => array (
						'class' => array (
								'bankcard-row-' . $bankcard_id
						)
				)
		);
	}

	// Build the tableselect.
	$form ['bankcard'] ['bankcard_id'] = array (
			'#type' => 'tableselect',
			'#header' => $header,
			'#options' => $options,
			'#default_value' => $default_value,
			'#multiple' => FALSE,
			//'#empty' => ctools_modal_text_button ( '添加银行卡', 'cowpro/fund/bankcard/add', '添加银行卡' ),//'请添加银行卡',
			'#attributes' => array (
					'class' => array (
							'bankcard-table'
					)
			)
	);

	return $form;
}
function cowpro_fund_add_bankcard($form, &$form_state) {
	form_load_include ( $form_state, 'inc', 'cowpro_fund', 'includes/cowpro_fund_withdraw' );
	$uid = $GLOBALS ['user']->uid;
	$profile_real_name = cowpro_customer_profile_load_one_row_with_conditions ( $uid, 'real_name' );
	$cardholder = $profile_real_name->name;

	$form = array ();
	$form ['cardholder'] = array (
			'#type' => 'textfield',
			'#title' => '持卡人',
			'#default_value' => $cardholder,
			'#size' => 60,
			'#maxlength' => 128,
			'#required' => TRUE
	);

	$card_type = array (
			0 => '借记卡',
			1 => '信用卡'
	);
	$form ['card_type'] = array (
			'#type' => 'radios',
			'#title' => '帐户类型',
			'#default_value' => 0,
			'#options' => $card_type,
			'#description' => ''
	);

	$vocab = taxonomy_vocabulary_machine_name_load ( 'bank_list' );
	$banks = taxonomy_term_load_multiple ( array (), array (
			'vid' => $vocab->vid
	) );
	$options = array ();
	foreach ( $banks as $bank ) {
		$options [$bank->name] = $bank->name;
	}
	$form ['bank_list'] = array (
			'#type' => 'select',
			'#title' => '选择银行',
			'#options' => $options,
			'#description' => ''
	);

	$form ['bank_located'] = array (
			'#type' => 'fieldset',
			'#title' => '开户行所在地',
			'#id' => 'bank_located'
	);

	$provinces = china_address_api_get_province_list ( 'region_name_cn' );
	$default_province = '湖北';
	$default_city = '襄樊';
	$form ['bank_located'] ['province'] = array (
			'#type' => 'select',
			'#title' => '省',
			'#options' => $provinces,
			'#default_value' => $default_province,
			'#description' => '',
			'#ajax' => array (
					'callback' => 'cowpro_fund_refresh_city_list',
					'wrapper' => 'bank_located_city',
					'method' => 'replace',
					'event' => 'change'
			)
	);

	$form ['bank_located'] ['city'] = _cowpro_fund_build_city_select ( $default_province, $default_city );

	$form ['subbranch'] = array (
			'#type' => 'textfield',
			'#title' => '开户行网点',
			'#size' => 60,
			'#maxlength' => 128,
			'#required' => TRUE
	);
	$form ['card_no'] = array (
			'#type' => 'textfield',
			'#title' => '银行卡号',
			'#size' => 19,
			'#maxlength' => 19,
			'#required' => TRUE
	);
	$form ['card_no2'] = array (
			'#type' => 'textfield',
			'#title' => '确认卡号',
			'#size' => 19,
			'#maxlength' => 19,
			'#required' => TRUE
	);
	$form ['add'] = array (
			'#type' => 'submit',
			'#name' => 'add',
			'#value' => '确认添加',
			'#ajax' => array (
					'callback' => 'cowpro_fund_add_bankcard_done'
			)
	);
	$form ['cancel'] = array (
			'#markup' => l ( '取消', '#', array (
					'attributes' => array (
							'class' => 'ctools-close-modal'
					)
			) )
	);
	return $form;
}
function cowpro_fund_refresh_city_list($form, &$form_state) {
	$province = $form_state ['input'] ['province'];
	$element = _cowpro_fund_build_city_select ( $province );
	$element ['#id'] = 'edit-city';
	$element ['#name'] = 'city';
	return $element;
}
function _cowpro_fund_build_city_select($province = NULL, $city = NULL) {
	if (! is_null ( $province )) {
		$cities = china_address_api_get_city_list_by_name ( $province, 'region_name_cn' );
	} else {
		$cities = array ();
	}

	$values = array_values($cities);
	if (! is_null ( $province )) {
		$value = $city;
	} else {
		$value = array_shift($values);
	}
	$element = array (
			'#type' => 'select',
			'#title' => '市',
			'#options' => $cities,
			'#default_value' => $value,
			'#description' => '',
			'#prefix' => '<div id="bank_located_city">',
			'#suffix' => '</div>'
	);
	return $element;
}
function cowpro_fund_add_bankcard_done($form, &$form_state) {
	ctools_include ( 'modal' );
	ctools_include ( 'ajax' );
	if (trim ( $form_state ['input'] ['card_no'] ) != trim ( $form_state ['input'] ['card_no2'] )) {
		$error = '请确认两次输入的银行卡号是一致的！';
		ctools_ajax_render_error ( $error );
	} else {
		$card = entity_create ( 'cowpro_fund_bankcard', array () );
		$card->uid = $GLOBALS ['user']->uid;
		$card->type = $form_state ['input'] ['card_type'];
		$card->card_no = $form_state ['input'] ['card_no'];
		$card->cardholder = $form_state ['input'] ['cardholder'];
		$card->bank_name = $form_state ['input'] ['bank_list'];
		$card->bank_branch = $form_state ['input'] ['subbranch'];
		$card->province = $form_state ['input'] ['province'];
		$card->city = $form_state ['input'] ['city'];
		entity_get_controller ( 'cowpro_fund_bankcard' )->save ( $card );

		// 准备更新银行卡列表
		$element = cowpro_fund_bankcard_list ( TRUE );
		$form['bankcard-list'] =$element;

		// 补丁，这是为了在下面 drupal_render($element) 方法中能够正常地显示出银行卡列表
		//drupal_process_form ( 'bankcard-list', $element, $form_state );
		drupal_process_form ( 'bankcard-list', $form, $form_state );
		$element = $form['bankcard-list'];

		$commands = array ();
		$commands [] = ajax_command_replace ( '#bankcard-list', drupal_render ( $element ) );
		$commands [] = ctools_modal_command_dismiss ();
		print ajax_render ( $commands );
		exit ();
	}
}
function cowpro_fund_ctools_modal_dismiss() {
	ctools_include ( 'modal' );
	ctools_include ( 'ajax' );
	$commands = array ();
	$commands [] = ctools_modal_command_dismiss ();
	print ajax_render ( $commands );
	exit ();
}
function _cowpro_fund_withdraw_callback($success, $journal_id, $external_reference_id, $interface_module, $result) {
	if ($success) {
		$entity = entity_load_single('cowpro_fund_journal', $journal_id);
		$entity->status = TRUE;
		$entity->external_reference_id = $external_reference_id;
		$data = array();
		$data['interface_module'] = $interface_module;
		$data['result'] = $result;
		$entity->data = $data;
		entity_get_controller('cowpro_fund_journal')->save($entity);
	}

	$args = array();
	$args[] = $success;
	$args[] = $journal_id;
	$hook = 'cowpro_fund_withdraw_finished';
	foreach (module_implements($hook) as $module) {
		$function = $module . '_' . $hook;
		if (function_exists($function)) {
			call_user_func_array($function, $args);
		}
	}
}
