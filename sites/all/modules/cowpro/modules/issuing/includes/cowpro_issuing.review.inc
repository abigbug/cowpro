<?php
include_once 'cowpro_issuing_status.inc';

/**
 * callback.
 * 对贷款进行审核
 */
function _cowpro_issuing_review($node) {
	ctools_include ( 'modal' );
	ctools_include ( 'ajax' );

	$issuing = $node->field_issuing [LANGUAGE_NONE] [0];
	$form_state = array (
			'title' => $node->title,
			'deadline' => $issuing ['deadline'],
			'start_time' => $issuing ['start_time'],
			'status' => $issuing ['status'],
			'node' => $node,
			'ajax' => TRUE,
	);
	$commands = ctools_modal_form_wrapper ( '_cowpro_issuing_review_form', $form_state );

	//以AJAX方式驱动modal窗口的显示的时候，暂时没有找到更好的定义窗口维度的方法，所以暂时用js的方式来实现
	$js = <<<js
	<script type="text/javascript">
	var width = 800;
	var height = 300;
	var contentRight = 25;
    var contentBottom = 45;
	jQuery('div.ctools-modal-content').css({
		'width': width + 'px',
		'height': height + 'px'
	});
    jQuery('div.ctools-modal-content .modal-content').css({
        'width': (width - contentRight) + 'px',
        'height': (height - contentBottom) + 'px'
    });
	var styleProps = jQuery('#modalContent').css('top');
	modalContentResize();
	jQuery('#modalContent').css('top', styleProps);
	</script>
js;

	$commands[0]['output'] .= $js;
	print ajax_render($commands);
	exit ();
}
function _cowpro_issuing_review_form($form, &$form_state) {
	include_once 'cowpro_issuing.display.inc';
	$form = _cowpro_issuing_get_review_form ( $form_state );
	$form ['submit'] = array (
			'#type' => 'submit',
			'#value' => '审核',
			'#weight' => 100
	);
	$form ['cancel'] = array (
			'#type' => 'submit',
			'#value' => '取消',
			'#weight' => 200
	);
	return $form;
}

/**
 * Validation callback for _cowpro_issuing_review_form().
 */
function _cowpro_issuing_review_form_validate($form, &$form_state) {
	if ($form_state ['values'] ['op'] === $form_state ['values'] ['submit']) {
		if ($form_state ['values']['audited'] != 1) {
			form_set_error ( 'review', '请勾选“已审核”选项，再点“审核”按钮完成审核程序。' );
		}
	}
}

function _cowpro_issuing_review_form_submit(&$form, &$form_state) {
	if ($form_state ['values'] ['op'] === $form_state ['values'] ['submit']) {
		// 把"开始时间"的选项（由年、月、日三个下拉列表组成）转化成 unix timestamp 并保存在 $element['start_time'] 表单项里面
		$start = $form_state ['values']['start_time_element'];
		$format = 'Ymd';
		$date = DateTime::createFromFormat ( $format, $start ['year'] . sprintf('%02d', $start ['month']) . sprintf('%02d', $start ['day']) );
		//如果出现以下错误信息：
		//Fatal error: Call to a member function getTimestamp() on boolean in
		//说明 DateTime::createFromFormat 不成功，$date==FALSE
		$start_time = $date->getTimestamp ();

		$node = $form_state['node'];
		$node->field_issuing[LANGUAGE_NONE][0]['status'] = COWPRO_ISSUING_STATUS_AUDITED;
		$node->field_issuing[LANGUAGE_NONE][0]['deadline'] = $form_state['values']['deadline'];
		$node->field_issuing[LANGUAGE_NONE][0]['start_time'] = $start_time;
		node_save($node);
		drupal_set_message('审核完毕');
		$commands = array ();
		$commands [] = ctools_modal_command_dismiss ();
		$commands[] = ctools_ajax_command_reload();
		print ajax_render ( $commands );
		exit ();
	} else {
		$commands = array ();
		$commands [] = ctools_modal_command_dismiss ();
		print ajax_render ( $commands );
		exit ();
	}
}
