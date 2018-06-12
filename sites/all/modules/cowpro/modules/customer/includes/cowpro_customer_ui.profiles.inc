<?php

/**
 * @file
 * Page callbacks and form builder functions for administering customer profiles.
 */


/**
 * Menu callback: display a list of customer profile types that the user can create.
 */
function cowpro_customer_ui_customer_profile_add_page() {
  $item = menu_get_item();
  $content = system_admin_menu_block($item);

  // Bypass the admin/cowpro/customers/profiles/add listing if only one
  // customer profile available.
  if (count($content) == 1) {
    $item = array_shift($content);
    drupal_goto($item['href']);
  }

  return theme('customer_profile_add_list', array('content' => $content));
}

/**
 * Displays the list of available customer profile types for profile creation.
 *
 * @ingroup themeable
 */
function theme_customer_profile_add_list($variables) {
  $content = $variables['content'];
  $output = '';

  if ($content) {
    $output = '<dl class="cowpro-customer-profile-type-list">';
    foreach ($content as $item) {
      $output .= '<dt>' . l($item['title'], $item['href'], $item['localized_options']) . '</dt>';
      $output .= '<dd>' . filter_xss_admin($item['description']) . '</dd>';
    }
    $output .= '</dl>';
  }
  else {
    if (user_access('administer customer profile types')) {
      $output = '<p>' . t('You have not enabled modules defining any customer profile types yet.') . '</p>';
    }
    else {
      $output = '<p>' . t('No customer profile types have been enabled yet for you to use.') . '</p>';
    }
  }

  return $output;
}

/**
 * Form callback wrapper: create or edit a customer profile.
 *
 * @param $profile
 *   The customer profile object being edited by this form.
 *
 * @see cowpro_customer_customer_profile_form()
 */
function cowpro_customer_ui_customer_profile_form_wrapper($profile) {
  // Include the forms file from the Customer module.
  module_load_include('inc', 'cowpro_customer', 'includes/cowpro_customer_profile.forms');
  return drupal_get_form('cowpro_customer_ui_customer_profile_form', $profile);
}

/**
 * Form callback wrapper: confirmation form for deleting a customer profile.
 *
 * @param $profile
 *   The customer profile object being deleted by this form.
 *
 * @see cowpro_customer_customer_profile_delete_form()
 */
function cowpro_customer_ui_customer_profile_delete_form_wrapper($profile) {
  // Include the forms file from the Customer module.
  module_load_include('inc', 'cowpro_customer', 'includes/cowpro_customer_profile.forms');
  return drupal_get_form('cowpro_customer_ui_customer_profile_delete_form', $profile);
}

/**
 * Form callback wrapper: 注册用户编辑自己的用户资料.
 *
 * @param $type
 *   资料的类型名，也就是实现 hook_cowpro_customer_profile_type_info() 接口的函数返回的 profile_type 数组里的 ['type']
 *
 * @see cowpro_customer_customer_profile_form()
 */
function cowpro_customer_ui_customer_profile_edit_own_form_wrapper($user, $type) {
	if (cowpro_customer_profile_page_access($user, $type)) {
	  // Include the forms file from the Customer module.
	  module_load_include('inc', 'cowpro_customer', 'includes/cowpro_customer_profile.forms');
	  return drupal_get_form('cowpro_customer_ui_customer_profile_edit_own_form', $user->uid, $type);
	}
}

/**
 * Access callback: determine if the user can access the listing page of a
 * given profile type.
 */
function cowpro_customer_profile_page_access($account, $profile_type) {
	global $user;

	// Check if the user can access any page.
	if (user_access('administer cowpro_customer_profile entities')
			|| user_access('view any cowpro_customer_profile entity')
			|| user_access('view any cowpro_customer_profile entity of bundle ' . $profile_type)
			|| user_access('edit any cowpro_customer_profile entity')
			|| user_access('edit any cowpro_customer_profile entity of bundle ' . $profile_type)) {
				return TRUE;
			}

			// Check if the user can access his own page.
			if ($user->uid == $account->uid) {
				if (user_access('view own cowpro_customer_profile entities')
						|| user_access('create cowpro_customer_profile entities')
						|| user_access('create cowpro_customer_profile entities of bundle ' . $profile_type)
						|| user_access('view own cowpro_customer_profile entities of bundle ' . $profile_type)
						|| user_access('edit own cowpro_customer_profile entities')
						|| user_access('edit own cowpro_customer_profile entities of bundle ' . $profile_type)) {
							return TRUE;
						}
			}

			return FALSE;
}
