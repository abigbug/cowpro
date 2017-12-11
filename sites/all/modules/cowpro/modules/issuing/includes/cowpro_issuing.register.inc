<?php
/**
 * 将标的信息同步到第三方托管服务商
 */
function _cowpro_issuing_register($node) {
	ctools_include ( 'modal' );
	ctools_include ( 'ajax' );
	$form_state = array (
			'nid' => $node->nid,
			'ajax' => TRUE,
	);
	$output = ctools_modal_form_wrapper ( '_cowpro_issuing_register_form', $form_state );
	//print ajax_render ( $output );
	$commands[] = ctools_ajax_command_reload();
	print ajax_render ( $commands );
	exit ();
}

function _cowpro_issuing_register_form($form, &$form_state) {
	$nid = $form_state['nid'];
	$result = custodian_cowpro_fund_issuing_publish($nid);
	if ($result) {
		//如果该接口成功返回TRUE，我们就可以更新标的状态为 'COWPRO_ISSUING_STATUS_INVITE_BIDS_START 正在投标'
		$node = node_load($nid);
		$node->field_issuing[LANGUAGE_NONE][0]['status'] = COWPRO_ISSUING_STATUS_INVITE_BIDS_START;
		node_save($node);
		$message = '标的同步操作已成功！';
	} else {
		$message = '标的同步操作失败！';
	}
	$form['information'] = array(
			'#markup' => "<p>$message</p>",
	);
	drupal_set_message($message);
	return $form;
}
