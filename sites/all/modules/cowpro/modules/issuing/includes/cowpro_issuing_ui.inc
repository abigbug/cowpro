<?php

/**
 * @file
 * Page callbacks and form builder functions for administering issuing.
 */

function cowpro_issuing_ui_issuing_list() {
return 'hello';
}

function cowpro_issuing_ui_issuing_add_new() {
	global $user;
	$uid = $user->uid;
	$issuing = cowpro_issuing_new($uid);
	return cowpro_issuing_ui_issuing_form_wrapper($issuing);
}

/**
 * Form callback wrapper: create or edit an issuing.
 *
 * @param $issuing
 *   The issuing object being edited by this form.
 *
 * @see cowpro_issuing_issuing_form()
 */
function cowpro_issuing_ui_issuing_form_wrapper($issuing) {
  // Include the forms file from the issuing module.
  module_load_include('inc', 'cowpro_issuing', 'includes/cowpro_issuing.forms');
  return drupal_get_form('cowpro_issuing_ui_issuing_form', $issuing);
}

/**
 * Form callback wrapper: confirmation form for deleting an issuing.
 *
 * @param $issuing
 *   The issuing object being deleted by this form.
 *
 * @see cowpro_issuing_issuing_delete_form()
 */
function cowpro_issuing_ui_issuing_delete_form_wrapper($issuing) {
  // Include the forms file from the issuing module.
  module_load_include('inc', 'cowpro_issuing', 'includes/cowpro_issuing.forms');
  return drupal_get_form('cowpro_issuing_ui_issuing_delete_form', $issuing);
}

/**
 * Form callback wrapper: 注册用户编辑自己的用户资料.
 *
 * @param $type
 *   资料的类型名，也就是实现 hook_cowpro_issuing_profile_type_info() 接口的函数返回的 profile_type 数组里的 ['type']
 *
 * @see cowpro_issuing_issuing_form()
 */
function cowpro_issuing_ui_issuing_edit_own_form_wrapper($type) {
  // Include the forms file from the Customer module.
  module_load_include('inc', 'cowpro_issuing', 'includes/cowpro_issuing.forms');
  return drupal_get_form('cowpro_issuing_ui_issuing_edit_own_form', $type);
}

/**
 * Access callback: determine if the user can access the listing page of a
 * given profile type.
 */
function cowpro_issuing_profile_page_access($account, $profile_type) {
	global $user;

	// Check if the user can access any page.
	if (user_access('administer cowpro_issuing_profile entities')
			|| user_access('view any cowpro_issuing_profile entity')
			|| user_access('view any cowpro_issuing_profile entity of bundle ' . $profile_type)
			|| user_access('edit any cowpro_issuing_profile entity')
			|| user_access('edit any cowpro_issuing_profile entity of bundle ' . $profile_type)) {
				return TRUE;
			}

			// Check if the user can access his own page.
			if ($user->uid == $account->uid) {
				if (user_access('view own cowpro_issuing_profile entities')
						|| user_access('create cowpro_issuing_profile entities')
						|| user_access('create cowpro_issuing_profile entities of bundle ' . $profile_type)
						|| user_access('view own cowpro_issuing_profile entities of bundle ' . $profile_type)
						|| user_access('edit own cowpro_issuing_profile entities')
						|| user_access('edit own cowpro_issuing_profile entities of bundle ' . $profile_type)) {
							return TRUE;
						}
			}

			return FALSE;
}
