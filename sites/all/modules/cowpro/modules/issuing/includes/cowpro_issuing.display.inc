<?php
include_once 'cowpro_issuing_status.inc';
include_once 'cowpro_issuing.repayment_schedule.fun.inc';

function _cowpro_issuing_get_form_issuing($issuing) {
	$element = array ();
	$element ['issuing_general'] = array (
			'#type' => 'fieldset',
			'#title' => '贷款表',
			'#collapsible' => TRUE,
			'#collapsed' => FALSE,
			// '#group' => 'additional_settings',
			'#attributes' => array (
					'class' => array ()
			),
			'#weight' => - 800,
			'#tree' => TRUE
	);

	$element ['issuing_general'] ['method_repayment'] = array (
			'#type' => 'select',
			'#title' => '还款方式',
			'#options' => _cowpro_issuing_get_repayment_method_options (),
			'#default_value' => isset ( $issuing ['method_repayment'] ) ? $issuing ['method_repayment'] : 'balloon_loan',
			'#input' => TRUE,
			'#weight' => 800
	);

	$element ['issuing_general'] ['loan_term'] = array (
			'#type' => 'select',
			'#title' => '借款期限',
			'#options' => _cowpro_issuing_get_loan_term_options (),
			'#default_value' => isset ( $issuing ['loan_term'] ) ? $issuing ['loan_term'] : 90,
			'#input' => TRUE,
			'#weight' => 900
	);

	$element ['issuing_general'] ['loan_amounts'] = array (
			'#type' => 'numberfield',
			'#title' => '借款金额',
			'#min' => 100,
			'#max' => 99999999,
			'#default_value' => isset ( $issuing ['loan_amounts'] ) ? $issuing ['loan_amounts'] : 10000,
			'#input' => TRUE,
			'#weight' => 1200
	);

	$element ['issuing_general'] ['annual_rate'] = array (
			'#type' => 'numberfield',
			'#title' => '年利率(%)',
			'#step' => 0.01,
			'#min' => 0,
			'#max' => 19.99,
			'#default_value' => isset ( $issuing ['annual_rate'] ) ? $issuing ['annual_rate'] : 14,
			'#weight' => 1800
	);

	$element ['issuing_review'] = array (
			'#type' => 'fieldset',
			'#title' => '审核(发标时间)',
			'#collapsible' => TRUE,
			'#collapsed' => TRUE,
			'#group' => 'additional_settings',
			'#attached' => array (
					'js' => array (
							drupal_get_path ( 'module', 'cowpro_issuing' ) . '/review.js'
					)
			),
			'#attributes' => array (
					'class' => array (
							'cowpro-issuing-review-form'
					)
			),
			'#access' => user_access ( 'review issuing' ),
			'#weight' => - 500,
			'#tree' => TRUE
	);

	$element ['issuing_review'] = $element ['issuing_review'] + _cowpro_issuing_get_review_form ( $issuing );

	foreach ( module_implements ( 'cowpro_issuing_issuing_form' ) as $module ) {
		$function = $module . '_cowpro_issuing_issuing_form';
		$element = $function ( $element, $form_state, $issuing );
	}

	// $form = module_invoke_all('cowpro_issuing_issuing_form', $form, $form_state, $issuing);

	$element ['issuing_settings'] = array (
			'#type' => 'fieldset',
			'#title' => '费用设置',
			'#collapsible' => TRUE,
			'#collapsed' => TRUE,
			// '#group' => 'additional_settings',
			'#attributes' => array (
					'class' => array ()
			),
			'#access' => user_access ( 'configure p2p' ),
			'#weight' => - 700,
			'#tree' => TRUE
	);

	include_once 'cowpro_issuing.settings.inc';
	$element ['issuing_settings'] = $element ['issuing_settings'] + _cowpro_issuing_get_settings_element ( $issuing );

	return $element;
}
function _cowpro_issuing_get_review_form($issuing) {
	$element = array ();
	$element ['deadline'] = array (
			'#type' => 'numberfield',
			'#title' => '筹标期限(天)',
			'#description' => '最长为30天',
			'#min' => 1,
			'#max' => 30,
			'#default_value' => isset ( $issuing ['deadline'] ) ? $issuing ['deadline'] : 7,
			'#input' => TRUE,
			'#weight' => 10
	);

	$d = new DateTime ( 'NOW' );
	if (isset ( $issuing ['start_time'] )) {
		$d->setTimestamp ( $issuing ['start_time'] );
	}
	$v = array (
			'year' => ( int ) $d->format ( 'Y' ),
			'month' => ( int ) $d->format ( 'm' ),
			'day' => ( int ) $d->format ( 'd' )
	);
	$element ['start_time_element'] = array (
			'#title' => '开始时间',
			'#type' => 'date',
			'#default_value' => $v,
			'#pre_render' => array (
					'_cowpro_issuing_form_pre_render'
			),
			'#input' => TRUE,
			'#weight' => 20
	);

	$element ['start_time'] = array (
			'#title' => '开始时间',
			'#type' => 'hidden'
	);

	$element ['status'] = array (
			'#title' => '贷款进度状态',
			'#type' => 'hidden',
			'#default_value' => isset ( $issuing ['status'] ) ? $issuing ['status'] : COWPRO_ISSUING_STATUS_UNAUDITED
	);

	$element['make_loans_time'] = array(
			'#type' => 'hidden',
			'#value' => $issuing ['make_loans_time'],
	);

	$audited = FALSE;
	if (isset ( $issuing ['status'] ) && ($issuing ['status'] != COWPRO_ISSUING_STATUS_UNAUDITED)) {
		$audited = TRUE;
	}
	$element ['audited'] = array (
			'#title' => '已审核',
			'#type' => 'checkbox',
			'#default_value' => $audited,
			'#weight' => 30,
	);
	return $element;
}

function _cowpro_issuing_form_pre_render($element) {

	// '开始时间'的'年份'下拉框选项，只提供‘本年以及下一年’两个选项
	$currentYear = date ( "Y" );
	$nextYear = $currentYear + 1;
	$element ['year'] ['#options'] = array (
			$currentYear => $currentYear,
			$nextYear => $nextYear
	);

	$currentMonth = (int)date ( "m" );
	$element ['month'] ['#default_value'] = $currentMonth;
	$element ['month'] ['#value'] = $currentMonth;

	$currentDay = (int)date ( "d" );
	$element ['day'] ['#default_value'] = $currentDay;
	$element ['day'] ['#value'] = $currentDay;

	return $element;
}

/**
 * Validation callback for cowpro_issuing_issuing_form().
 */
/*
 * function cowpro_issuing_issuing_form_validate($form, &$form_state) {
 * $issuing = $form_state ['issuing'];
 * foreach ( module_implements ( 'cowpro_issuing_issuing_form_validate' ) as $module ) {
 * $function = $module . '_cowpro_issuing_issuing_form_validate';
 * $function ( $form, $form_state );
 * }
 * }
 */
/**
 * Submit callback for cowpro_issuing_issuing_form().
 */
/*
 * function cowpro_issuing_issuing_form_submit($form, &$form_state) {
 * global $user;
 *
 * $issuing = &$form_state ['issuing'];
 *
 * $issuing->caption = $form_state ['values'] ['caption'];
 * $issuing->caption_brief = $form_state ['values'] ['caption_brief'];
 * $issuing->method_repayment = $form_state ['values'] ['method_repayment'];
 *
 * foreach ( module_implements ( 'cowpro_issuing_issuing_form_submit' ) as $module ) {
 * $function = $module . '_cowpro_issuing_issuing_form_submit';
 * $issuing = $function ( $form, $form_state, $issuing );
 * }
 *
 * // Save the issuing.
 * cowpro_issuing_save ( $issuing );
 *
 * // Redirect based on the button clicked.
 * drupal_set_message ( '贷款申请表已保存.' );
 * }
 *
 * /**
 * Form callback: confirmation form for deleting an issuing.
 *
 * @param $issuing The
 * issuing object to be deleted.
 *
 * @see confirm_form()
 */
/*
 * function cowpro_issuing_issuing_delete_form($form, &$form_state, $issuing) {
 * $form_state ['issuing'] = $issuing;
 *
 * // Ensure this include file is loaded when the form is rebuilt from the cache.
 * $form_state ['build_info'] ['files'] ['form'] = drupal_get_path ( 'module', 'cowpro_customer' ) . '/includes/cowpro_issuing.display.inc';
 *
 * $form ['#submit'] [] = 'cowpro_customer_customer_profile_delete_form_submit';
 *
 * $form = confirm_form ( $form, t ( 'Are you sure you want to delete this issuing?' ), '', '<p>' . t ( 'Deleting this issuing cannot be undone.' ) . '</p>', t ( 'Delete' ), t ( 'Cancel' ), 'confirm' );
 *
 * return $form;
 * }
 */
/**
 * Submit callback for cowpro_issuing_issuing_delete_form().
 */
/*
 * function cowpro_issuing_issuing_delete_form_submit($form, &$form_state) {
 * $issuing = $form_state ['issuing'];
 *
 * if (cowpro_issuing_delete ( $issuing->issiung_id )) {
 * drupal_set_message ( t ( 'The issuing has been deleted.' ) );
 * watchdog ( 'cowpro_issuing', 'Deleted issuing @issuing_id.', array (
 * '@issuing_id' => $issuing->issuing_id
 * ), WATCHDOG_NOTICE );
 * } else {
 * drupal_set_message ( t ( 'The issuing could not be deleted.' ), 'error' );
 * }
 * }
 */
function _cowpro_issuing_get_render_issuing($issuing) {
	$element = array ();
	$element ['status'] = array (
			'#type' => 'html_tag',
			'#tag' => 'li',
			'#value' => _cowpro_issuing_get_readable_status ( $issuing ['status'] ),
			'#children' => ''
	);
	/*
	if ($issuing['status'] == COWPRO_ISSUING_STATUS_INVITE_BIDS_START) {
		$remain = $issuing ['start_time'] + $issuing['deadline']*24*60*60 - time();
		if ($remain <= 0) {
			$text = '已到期';
		} else {
			$date_a = new DateTime();
			$date_a->setTimestamp($issuing ['start_time'] + $issuing['deadline']*24*60*60);
			$date_b = new DateTime();
			$date_b->setTimestamp(time());
			$interval = date_diff($date_a, $date_b);
			$text = '投标截止时间还剩余：' . $interval->format('%d天 %h:%i:%s');
		}
		$element ['remain'] = array (
				'#type' => 'html_tag',
				'#tag' => 'li',
				'#value' => $text,
		);
	}
	*/
	$element ['method_repayment'] = array (
			'#type' => 'html_tag',
			'#tag' => 'li',
			'#value' => _cowpro_issuing_get_readable_repayment_method ( $issuing ['method_repayment'] ),
			'#children' => ''
	);
	$element ['loan_amounts'] = array (
			'#type' => 'html_tag',
			'#tag' => 'li',
			'#value' => $issuing ['loan_amounts'],
			'#children' => ''
	);
	$element ['loan_term'] = array (
			'#type' => 'html_tag',
			'#tag' => 'li',
			'#value' => _cowpro_issuing_get_readable_loan_term($issuing ['loan_term']),
			'#children' => ''
	);
	$element ['annual_rate'] = array (
			'#type' => 'html_tag',
			'#tag' => 'li',
			'#value' => $issuing ['annual_rate'],
			'#children' => ''
	);

	return $element;
}

function _cowpro_issuing_get_render_issuing_2($issuing) {
	$element = array ();
	$element ['status'] = array (
			'#type' => 'html_tag',
			'#tag' => 'span',
			'#value' => _cowpro_issuing_get_readable_status ( $issuing ['status'] ),
			'#children' => ''
	);
	if ($issuing['status'] == COWPRO_ISSUING_STATUS_INVITE_BIDS_START) {
		$remain = $issuing ['start_time'] + $issuing['deadline']*24*60*60 - time();
		if ($remain <= 0) {
			$text = '已到期';
		} else {
			$date_a = new DateTime();
			$date_a->setTimestamp($issuing ['start_time'] + $issuing['deadline']*24*60*60);
			$date_b = new DateTime();
			$date_b->setTimestamp(time());
			$interval = date_diff($date_a, $date_b);
			$text = '投标截止时间还剩余：' . $interval->format('%d天 %h:%i:%s');
		}
		$element ['remain'] = array (
				'#type' => 'html_tag',
				'#tag' => 'span',
				'#value' => $text,
		);
	}
	$element ['method_repayment'] = array (
			'#type' => 'html_tag',
			'#tag' => 'span',
			'#value' => _cowpro_issuing_get_readable_repayment_method ( $issuing ['method_repayment'] ),
			'#children' => ''
	);
	$element ['line1'] = array (
			'#type' => 'html_tag',
			'#tag' => 'br',
			'#value' => '',
			'#children' => ''
	);
	$element ['loan_amounts'] = array (
			'#type' => 'html_tag',
			'#tag' => 'span',
			'#value' => '贷款金额：' . $issuing ['loan_amounts'],
			'#children' => ''
	);
	$element ['line2'] = array (
			'#type' => 'html_tag',
			'#tag' => 'br',
			'#value' => '',
			'#children' => ''
	);
	$element ['loan_term'] = array (
			'#type' => 'html_tag',
			'#tag' => 'span',
			'#value' => _cowpro_issuing_get_readable_loan_term($issuing ['loan_term']) . '，',
			'#children' => ''
	);
	$element ['annual_rate'] = array (
			'#type' => 'html_tag',
			'#tag' => 'span',
			'#value' => '年利率：' . $issuing ['annual_rate'],
			'#children' => ''
	);

	return $element;
}
