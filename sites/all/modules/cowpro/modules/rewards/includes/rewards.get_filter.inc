<?php
function cowpro_rewards_get_filter_form($form, &$form_state){
               $form["search_date"]["deadline"] = array(
                '#type' => 'date', 
                '#title' => "日期搜索", 
                '#size' => 20,
                '#default_value' => array(
                    'month' => format_date(time(), 'custom', 'n'),
                    'day' => format_date(time(), 'custom', 'j'),
                    'year' => format_date(time(), 'custom', 'Y'),
                ),
               '#pre_render' => array (
                                '_cowpro_report_form_pre_render'
                ),
              );
           $form['submit'] = array(
                '#type' => 'submit',
                '#value' => '提交',
            );
	return $form;
}

function cowpro_rewards_get_filter_form_submit($form, &$form_state) {
   
    $year = intval($form_state ['values']['deadline']['year']);
    $month = intval($form_state ['values']['deadline']['month']);
    $day = intval($form_state ['values']['deadline']['day']);
    global $base_url;
    $_SESSION['search_report_date'] = $year."-".$month."-".$day;
    drupal_goto($base_url."/cowpro/rewards/report/");
}

function _cowpro_report_form_pre_render($element) {

	// '开始时间'的'年份'下拉框选项，只提供‘本年以及下一年’两个选项
	$currentYear = date ( "Y" );
	$element ['year'] ['#options'] = array (
			$currentYear => $currentYear,
			$currentYear - 1 => $currentYear - 1,
			$currentYear - 2 => $currentYear - 2,
			$currentYear - 3 => $currentYear - 3,
	);

	$currentMonth = (int)date ( "m" );
	$element ['month'] ['#default_value'] = $currentMonth;
	$element ['month'] ['#value'] = $currentMonth;

	$currentDay = (int)date ( "d" );
	$element ['day'] ['#default_value'] = $currentDay;
	$element ['day'] ['#value'] = $currentDay;
        //var_dump($element);die();
	return $element;
}

