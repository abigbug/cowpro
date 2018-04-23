<?php
include_once 'jiupaipay.const.inc';
include_once ("libs/RSA.php");
include_once 'jiupaipay.fun.inc';
include_once ("libs/AES.php");
include_once ("libs/Common.php");

/**
 * 标的信息同步
 *
 * @param int $nid
 *        	标的ID
 *
 * $projectStatus 标的状态:
 * 01:发布
 * 02:投资中
 * 03:放款
 * 04:流标
 * 05:撤标
 * 06:还款中
 * 07:结束
 *
 * $busiTradeType 业务操作类型
 * P01：标的发布
 * P02：标的流标
 * P03：标的撤标
 * P04：标的修改
 */
function jiupaipay_issuing_publish($nid, $busiTradeType = "P01", $projectStatus = "01") {
	// 请求报文头
	$header = jiupaipay_header ( "O00001" );

	$node = node_load ( $nid );
	$aes = new AES ( JPP_AES_KEY, JPP_AES_IV );
	$post_data = array ();
	$post_data ['busiTradeType'] = $busiTradeType;
	$post_data ['businessSeqNo'] = "jbz_" . date ( "Ymd", time () ) . time () . "@" . $busiTradeType . "@" . $projectStatus;
	$post_data ['objectId'] = $nid;
	$post_data ['objectName'] = $node->title;
	$post_data ['totalAmount'] = $node->field_issuing [LANGUAGE_NONE] [0] ['loan_amounts'];
	$post_data ['interestRate'] = $node->field_issuing [LANGUAGE_NONE] [0] ['annual_rate'];
	$post_data ['returnType'] = "01";
	$loan_term = $node->field_issuing [LANGUAGE_NONE] [0] ['loan_term'] / 30;
	$returnInfoList = array (
			"oderNo" => "11",
			"returnNo" => intval ( $loan_term ),
			"returnDate" => "20171225",
	);
	$post_data ['returnInfoList'] [] = $returnInfoList;
	$post_data ['customerId'] = $node->field_applicant ['und'] [0] ['uid'];
	$post_data ['projectStatus'] = $projectStatus;
	$post_data ['nature'] = "";
	$post_data ['note'] = "";

	$post_data_tmp = $post_data;

	$oderNo = $post_data_tmp ["returnInfoList"] [0] ['oderNo'];
	unset ( $post_data_tmp ["returnInfoList"] [0] ['oderNo'] );
	foreach ( $post_data_tmp ['returnInfoList'] [0] as $key => $value ) {
		$post_data_tmp [$key . $oderNo] = $value;
	}

	unset ( $post_data_tmp ['returnInfoList'] );
	ksort ( $post_data_tmp );
	$signInfo = $header ['signTime'];
	foreach ( $post_data_tmp as $value ) {
		$signInfo .= "|" . $value;
	}

	$post_data ['customerId'] = $aes->encrypt ( $post_data ['customerId'] );
	$post_data ['objectName'] = $aes->encrypt ( $post_data ['objectName'] );
	$post_data ['objectId'] = $aes->encrypt ( $post_data ['objectId'] );

	$rsa_private_key = variable_get ( PRIVATE_KEY_ON_JIUPAIPAY );
	$rsa_public_key = variable_get ( PUBLIC_KEY_ON_JIUPAIPAY );
	$rsa = new RSA ( $rsa_private_key, $rsa_public_key );
	$signData = $rsa->sign ( $signInfo );

	$header ['signature'] = $signData;
	$curl_post_data ['reqHeader'] = $header;
	$curl_post_data ['inBody'] = $post_data;

	$result = jiupaipay_curl_api ( $curl_post_data );
	$result = json_decode ( $result, true );

	$result_jpp = array ();
	$result_jpp ['success'] = false;
	$result ['outBody'] ['objectaccNo'] = $aes->decrypt ( $result ['outBody'] ['objectaccNo'] );

	if ($result ['respHeader'] ['respCode'] == 'P2P0000' && _jiupaipay_verify_api ( $result ['outBody'], $result ['respHeader'] ['signature'], $result ['respHeader'] ['signTime'] )) {
		if ($busiTradeType == "P01") {
			$acc_no = $result ['outBody'] ['objectaccNo'];
			$sql_data ['issuing_object_accno'] = $acc_no;
			$sql_data ['nid'] = $nid;
			db_insert ( 'jiupaipay_issuing_accno' )->fields ( array (
					'issuing_object_accno' => $sql_data ['issuing_object_accno'],
					'nid' => $sql_data ['nid']
			) )->execute ();
		}
		$result_jpp ['success'] = true;
	}

	$result_jpp ['result_code'] = $result ['respHeader'] ['respCode'];
	$result_jpp ['message'] = $result ['respHeader'] ['respMsg'];
	return $result_jpp;
}

?>