<?php

/**
 * @file
 * Forms for creating / editing and deleting customer profiles.
 */

/**
 * Form callback: create or edit a customer profile.
 *
 * @param $profile The
 *        	profile object to edit or for a create form an empty profile object
 *        	with only a profile type defined.
 *
 */
function cowpro_customer_customer_profile_form($form, &$form_state, $profile) {
	// Ensure this include file is loaded when the form is rebuilt from the cache.
	$form_state ['build_info'] ['files'] ['form'] = drupal_get_path ( 'module', 'cowpro_customer' ) . '/includes/cowpro_customer_profile.forms.inc';

	$form ['profile'] = array (
			'#type' => 'fieldset',
			'#title' => '资料',
			'#collapsible' => TRUE,
			'#collapsed' => TRUE,
			'#group' => 'additional_settings',
			'#attached' => array (
					'js' => array (
							drupal_get_path ( 'module', 'cowpro_customer' ) . '/cowpro_customer.js',
							array (
									'type' => 'setting',
									'data' => array (
											'anonymous' => variable_get ( 'anonymous', t ( 'Anonymous' ) )
									)
							)
					)
			),
			'#weight' => 10
	);

	$hook = 'cowpro_customer_profile_' . $profile->type . '_form';
	foreach ( module_implements ( $hook ) as $module ) {
		$function = $module . '_' . $hook;
		$form ['profile'] += $function ( $form ['profile'], $form_state, $profile );
	}

	// Ensure the owner name is accessible if the uid is set.
	if (! empty ( $profile->uid ) && $owner = user_load ( $profile->uid )) {
		$profile->name = $owner->name;
	}

	if (empty ( $profile->created )) {
		$profile->date = format_date ( REQUEST_TIME, 'custom', 'Y-m-d H:i:s O' );
	}

	// Add the field related form elements.
	$form_state ['customer_profile'] = $profile;
	field_attach_form ( 'cowpro_customer_profile', $profile, $form, $form_state );

	$form ['additional_settings'] = array (
			'#type' => 'vertical_tabs',
			'#weight' => 99
	);

	// Add the user account and e-mail fields.
	GLOBAL $user;
	if ($user->uid != $profile->uid) {
		$form ['user'] = array (
				'#type' => 'fieldset',
				'#title' => t ( 'User information' ),
				'#collapsible' => TRUE,
				'#collapsed' => TRUE,
				'#group' => 'additional_settings',
				'#attached' => array (
						'js' => array (
								drupal_get_path ( 'module', 'cowpro_customer' ) . '/cowpro_customer.js',
								array (
										'type' => 'setting',
										'data' => array (
												'anonymous' => variable_get ( 'anonymous', t ( 'Anonymous' ) )
										)
								)
						)
				),
				'#weight' => 20
		);
		$form ['user'] ['name'] = array (
				'#type' => 'textfield',
				'#title' => t ( 'Owned by' ),
				'#description' => t ( 'Leave blank for %anonymous.', array (
						'%anonymous' => variable_get ( 'anonymous', t ( 'Anonymous' ) )
				) ),
				'#maxlength' => 60,
				'#autocomplete_path' => 'user/autocomplete',
				'#default_value' => ! empty ( $profile->name ) ? $profile->name : '',
				'#disabled' => TRUE,
				'#weight' => - 1
		);
	}

	// Add the verified of the profile.
	$form ['profile_verified'] = array (
			'#type' => 'fieldset',
			'#title' => t ( 'Status' ),
			'#collapsible' => TRUE,
			'#collapsed' => TRUE,
			'#group' => 'additional_settings',
			'#attached' => array (
					'js' => array (
							drupal_get_path ( 'module', 'cowpro_customer' ) . '/cowpro_customer.js'
					)
			),
			'#weight' => 30
	);
	$form ['profile_verified'] ['verified'] = array (
			'#type' => 'radios',
			'#title' => t ( 'Status' ),
			// '#description' => t('Disabled profiles will not be visible to customers in options lists.'),
			'#options' => array (
					'1' => '已认证',
					'0' => '末认证'
			),
			'#default_value' => $profile->verified,
			'#required' => TRUE,
			'#disabled' => ! user_access ( 'administer cowpro_customer_profile entities' ),
			'#weight' => 35
	);

	// Disable the status field if the customer profile type has been disabled.
	if (! cowpro_customer_profile_type_load ( $profile->type )) {
		$form ['profile_status'] ['status'] ['#disabled'] = TRUE;
		$form ['profile_status'] ['status'] ['#description'] .= '<br />' . t ( 'This profile is of a type that is no longer available, so its status cannot be adjusted.' );
	}

	// We add the form's #submit array to this button along with the actual submit
	// handler to preserve any submit handlers added by a form callback_wrapper.
	$submit = array ();

	if (! empty ( $form ['#submit'] )) {
		$submit += $form ['#submit'];
	}

	$form ['actions'] = array (
			'#type' => 'actions'
	);
	$form ['actions'] ['submit'] = array (
			'#type' => 'submit',
			'#value' => t ( 'Save profile' ),
			'#submit' => array_merge ( $submit, array (
					'cowpro_customer_customer_profile_form_submit'
			) )
	);

	// We append the validate handler to #validate in case a form callback_wrapper
	// is used to add validate handlers earlier.
	$form ['#validate'] [] = 'cowpro_customer_customer_profile_form_validate';

	$hook = 'cowpro_customer_profile_' . $profile->type . '_form_alter';
	foreach ( module_implements ( $hook ) as $module ) {
		$function = $module . '_' . $hook;
		$form = $function ( $form, $form_state, $profile );
	}

	$hook = 'cowpro_customer_profile_form_alter';
	foreach ( module_implements ( $hook ) as $module ) {
		$function = $module . '_' . $hook;
		$form = $function ( $form, $form_state, $profile );
	}

	return $form;
}

/**
 * Form callback: 注册用户编辑自己的用户资料.
 *
 * @param $type 资料的类型名，也就是实现
 *        	hook_cowpro_customer_profile_type_info() 接口的函数返回的 profile_type 数组里的 ['type']
 */
function cowpro_customer_ui_customer_profile_edit_own_form($form, &$form_state, $uid, $type) {
	// global $user;
	$conditions = array (
			'uid' => $uid,
			'type' => $type
	);
	$profiles = cowpro_customer_profile_load_multiple ( array (), $conditions );
	if (empty ( $profiles )) {
		$profile = cowpro_customer_profile_new ( $type, $uid );
	} else {
		$profile = reset ( $profiles );
	}

	return cowpro_customer_customer_profile_form ( $form, $form_state, $profile );
}

/**
 * Validation callback for cowpro_customer_profile_form().
 */
function cowpro_customer_customer_profile_form_validate($form, &$form_state) {
	if (isset ( $form_state ['triggering_element'] ['#wizard type'] )) {
		// 如果是 ctools wizard form 按钮驱动的操作，不做处理
		// 这里是为了解决模块 registration_wizard 在点击向导按钮的时候
		// 用户有可能并没有填写当前的表单，所以我们这里不响应“向导按钮”驱动的操作
		// 在这里解决上述问题并不合适，有条件的时候需要对此进行重构
		return;
	}
	$profile = $form_state ['customer_profile'];

	$hook = 'cowpro_customer_profile_' . $profile->type . '_form_validate';
	foreach ( module_implements ( $hook ) as $module ) {
		$function = $module . '_' . $hook;
		$function ( $form, $form_state, $profile );
	}

	/*
	 * // Validate the "owned by" field.
	 * if (!empty($form_state['values']['name']) && !($account = user_load_by_name($form_state['values']['name']))) {
	 * // The use of empty() is mandatory in the context of usernames as the empty
	 * // string denotes an anonymous user.
	 * form_set_error('name', t('The username %name does not exist.', array('%name' => $form_state['values']['name'])));
	 * }
	 */

	// Notify field widgets to validate their data.
	field_attach_form_validate ( 'cowpro_customer_profile', $profile, $form, $form_state );
}

/**
 * Submit callback for cowpro_customer_profile_form().
 */
function cowpro_customer_customer_profile_form_submit($form, &$form_state) {
	if (isset ( $form_state ['triggering_element'] ['#wizard type'] )) {
		// 如果是 ctools wizard form 按钮驱动的操作，不做处理
		// 这里是为了解决模块 registration_wizard 在点击向导按钮的时候
		// 用户有可能并没有填写当前的表单，所以我们这里不响应“向导按钮”驱动的操作
		// 在这里解决上述问题并不合适，有条件的时候需要对此进行重构
		return;
	}
	global $user;

	$profile = &$form_state ['customer_profile'];

	$hook = 'cowpro_customer_profile_' . $profile->type . '_form_submit';
	foreach ( module_implements ( $hook ) as $module ) {
		$function = $module . '_' . $hook;
		$function ( $form, $form_state, $profile );
	}

	// 如果提交保存的用户没有管理权限，那么要把verified重置为“末认证”状态
	if (! user_access ( 'administer cowpro_customer_profile entities' )) {
		$profile->verified = FALSE;
	} else {
		$profile->verified = $form_state ['values'] ['verified'];
	}

	// Notify field widgets.
	field_attach_submit ( 'cowpro_customer_profile', $profile, $form, $form_state );

	// Save the profile.
	cowpro_customer_profile_save ( $profile );

	// Redirect based on the button clicked.
	drupal_set_message ( t ( 'Profile saved.' ) );
}

/**
 * Form callback: confirmation form for deleting a profile.
 *
 * @param $profile The
 *        	profile object to be deleted.
 *
 * @see confirm_form()
 */
function cowpro_customer_customer_profile_delete_form($form, &$form_state, $profile) {
	$form_state ['customer_profile'] = $profile;

	// Ensure this include file is loaded when the form is rebuilt from the cache.
	$form_state ['build_info'] ['files'] ['form'] = drupal_get_path ( 'module', 'cowpro_customer' ) . '/includes/cowpro_customer_profile.forms.inc';

	$form ['#submit'] [] = 'cowpro_customer_customer_profile_delete_form_submit';

	$form = confirm_form ( $form, t ( 'Are you sure you want to delete this profile?' ), '', '<p>' . t ( 'Deleting this profile cannot be undone.' ) . '</p>', t ( 'Delete' ), t ( 'Cancel' ), 'confirm' );

	return $form;
}

/**
 * Submit callback for cowpro_customer_profile_delete_form().
 */
function cowpro_customer_customer_profile_delete_form_submit($form, &$form_state) {
	$profile = $form_state ['customer_profile'];

	if (cowpro_customer_profile_delete ( $profile->profile_id )) {
		drupal_set_message ( t ( 'The profile has been deleted.' ) );
		watchdog ( 'cowpro_customer_profile', 'Deleted customer profile @profile_id.', array (
				'@profile_id' => $profile->profile_id
		), WATCHDOG_NOTICE );
	} else {
		drupal_set_message ( t ( 'The profile could not be deleted.' ), 'error' );
	}
}
function cowpro_customer_ui_customer_profile_edit_list_show_form($form, &$form_state, $uid, $type, $description) {
	// global $user;
	$conditions = array (
			'uid' => $uid,
			'type' => $type,
	);
	$profiles = cowpro_customer_profile_load_multiple ( array (), $conditions );
	if (empty ( $profiles )) {
		$profile = cowpro_customer_profile_new ( $type, $uid );
	} else {
		$profile = reset ( $profiles );
	}
	return cowpro_customer_customer_profile_show_form ( $form, $form_state, $profile, $description );
}

// 个人资料填写向导样式设置
function cowpro_customer_customer_profile_show_form($form, &$form_state, $profile, $description) {
	unset ( $form ['ctools_trail'] );
	unset ( $form ['buttons'] );
        $message="";
	$type = $profile->type;
	$uid = $profile->uid;
	$verified = $profile->verified;
	if ($verified) {
		$verified_class = 'verified';
		$markup = "已认证";
                if( $type == "survey" ) {
                    $link_type = "重新评测";
                }else{
                    $link_type = "修改设置";
                }
		
	} else {
		$verified_class = 'unverified';
		$markup = "未认证";
		$link_type = "立即设置";
	}

	$callback = $type . '_user_view_detail';
	if (function_exists ( $callback )) {
		$result = $callback($profile);
                $markup = $result['markup'];
                $verified = $result['verified'];
                $message= $result['message'];
	} else {
		if ($verified) {
			$markup = '已认证';
		} else {
			$markup = '未认证';
		}
	}

	$order_name = $form_state ['form_info'] ['order'] [$type];
	global $base_url;
	$form = array ();
        if( $type == 'survey' ) {
            $form ['show_list'] = array (
			'#markup' => '<div class="m_r"><div class="mr_t"><div class="phone2"> <p><span>' . $order_name . '</span><i>' . $description . '</i><b class="' . $verified_class . '">' . $markup . '</b><strong class="fundCustodian" style="cursor:pointer"><a href="' . $base_url . '/survey" title="">' . $link_type . '</a></strong></p></div></div></div>'
            );
        }else{
            $form ['show_list'] = array (
			'#markup' => '<div class="m_r"><div class="mr_t"><div class="phone2"> <p><span>' . $order_name . '</span><i>' . $description . '</i><b class="' . $verified_class . '">' . $markup . '</b><strong class="fundCustodian" style="cursor:pointer"><a href="' . $base_url . '/user/' . $uid . '/customer-profiles/' . $type . '" title="">' . $link_type . '</a></strong></p></div></div></div>'
            );
        }
	
        $form ['message'] = array (
			'#type' => 'hidden',
			'#default_value' => $message,
	);
	return $form;
}