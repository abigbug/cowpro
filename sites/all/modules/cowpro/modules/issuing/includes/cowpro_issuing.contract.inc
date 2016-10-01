<?php
include_once 'cowpro_issuing.repayment_schedule.fun.inc';

/**
 * callback.
 * 查看合同
 */
function _cowpro_issuing_contract_view($node) {
	ctools_include ( 'modal' );
	ctools_include ( 'ajax' );
	$content = _cowpro_issuing_contract_get_content ( $node );
	$output = array ();
	// $download = ctools_ajax_text_button('下载DOC文档', 'issuing/' . $node->nid . '/contract/download', '下载DOC文档');
	$link = 'issuing/' . $node->nid . '/contract/download';
	$download = "<a href=$link>下载DOC文档</a>";
	$output [] = ctools_modal_command_display ( $node->title, $download . $content );
	print ajax_render ( $output );
	exit ();
}

/**
 * callback.
 * 下载合同
 */
function _cowpro_issuing_contract_download($node) {
	include_once 'word.php';
	$content = _cowpro_issuing_contract_get_content ( $node );
	$word = new word ();
	$word->start ();
	$wordname = "借款协议.doc";
	echo $content;
	$word->save ( $wordname );
	drupal_exit ();
}

/**
 * 生成并返回贷款合同的文本
 *
 * @param unknown $node
 * @return Text
 */
function _cowpro_issuing_contract_get_content($node) {
	$contract_nid = $node->field_contract_loan [LANGUAGE_NONE] [0] ['nid'];
	$contract_node = node_load ( $contract_nid );
	$contract_content = $contract_node->body [LANGUAGE_NONE] [0] [value];
	$data = array ();
	$data ['cowpro_issuing'] = $node;
	$content = token_replace ( $contract_content, $data );
	return $content;
}