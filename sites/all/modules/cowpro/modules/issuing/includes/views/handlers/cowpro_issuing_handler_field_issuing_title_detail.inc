<?php

/**
 * @file
 * Contains the basic issuing field handler.
 */

/**
 * Field handler to provide simple renderer that allows linking to an issuing.
 */
class cowpro_issuing_handler_field_issuing_title_detail extends views_handler_field {

  function render($values) {
  	//watchdog('cowpro_issuing_handler_field_issuing_title_detail', serialize($values));
  	$path = drupal_get_path ( 'module', 'cowpro_issuing' );
  	include_once $path . '/includes/cowpro_issuing.repayment_schedule.fun.inc';

    $nid = $this->get_value($values);
    $node = node_load($nid);
    $title = $node->title;
    $link = 'node/' . $nid;
    $str_title = l($this->sanitize_value($title), $link);

    $applicant_uid = $node->field_applicant[LANGUAGE_NONE] [0]['uid'];
    $profile_real_name = cowpro_customer_profile_load_one_row_with_conditions ( $applicant_uid, 'real_name' );
    if ($profile_real_name) {
    	$real_name = $profile_real_name->name;
    } else {
    	$real_name = '';
    }
    $user = user_load($applicant_uid);
    $userpath = 'user/' . $user->uid;
    $str_applicant = l($this->sanitize_value($user->name) . "($real_name)", $userpath);

    $issuing = $node->field_issuing [LANGUAGE_NONE] [0];
    $loan_term_readable = _cowpro_issuing_get_readable_loan_term($issuing ['loan_term']);
    $loan_amounts = $issuing ['loan_amounts'];
    $make_loans_time = gmdate("Y年m月d日", $issuing['make_loans_time']);

    $deadline = date("Y年m月d日", $values->cowpro_repayment_schedule_deadline);
    return "$str_title | $str_applicant | $loan_term_readable | $loan_amounts | $deadline";
  }
}
