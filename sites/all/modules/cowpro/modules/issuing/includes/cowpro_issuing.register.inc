<?php
/**
 * 将标的信息同步到第三方托管服务商
 */
function _cowpro_issuing_register($node) {
	$result = custodian_cowpro_fund_issuing_publish($node->nid);

	if ($result['success'] === TRUE) {
		//如果该接口成功返回TRUE，我们就可以更新标的状态为 'COWPRO_ISSUING_STATUS_INVITE_BIDS_START 正在投标'
		$node->field_issuing[LANGUAGE_NONE][0]['status'] = COWPRO_ISSUING_STATUS_INVITE_BIDS_START;
		node_save($node);
		drupal_set_message('标的同步操作已成功！');
	} else {
		drupal_set_message($result['message']."-".$result['result_code']);
	}

	ctools_include ( 'modal' );
	ctools_include ( 'ajax' );
	$commands = array ();
	$commands[] = ctools_ajax_command_reload();
	print ajax_render ( $commands );
	exit ();
}
