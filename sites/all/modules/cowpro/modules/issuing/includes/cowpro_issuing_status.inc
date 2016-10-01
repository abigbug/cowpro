<?php
define('COWPRO_ISSUING_STATUS_UNAUDITED', 'UNAUDITED'); // 贷款人填写《贷款申请表》，末审核
define('COWPRO_ISSUING_STATUS_AUDITED', 'AUDITED'); // 审核通过
define('COWPRO_ISSUING_STATUS_INVITE_BIDS_START', 'INVITE_BIDS_START'); // 正在投标
define('COWPRO_ISSUING_STATUS_INVITE_BIDS_FAILED', 'INVITE_BIDS_FAILED'); // 流标
define('COWPRO_ISSUING_STATUS_INVITE_BIDS_SUCCEED', 'INVITE_BIDS_SUCCEED'); // 满标，等待放款
define('COWPRO_ISSUING_STATUS_REPAYMENT', 'REPAYMENT'); // 等待还款
define('COWPRO_ISSUING_STATUS_FINISHED', 'FINISHED'); // 还款完毕

function _cowpro_issuing_get_readable_status($status) {
	$result = '';
	switch ($status) {
		case COWPRO_ISSUING_STATUS_UNAUDITED :
			$result = '末审核';
			break;
		case COWPRO_ISSUING_STATUS_AUDITED :
			$result = '审核通过';
			break;
		case COWPRO_ISSUING_STATUS_INVITE_BIDS_START :
			$result = '正在投标';
			break;
		case COWPRO_ISSUING_STATUS_INVITE_BIDS_FAILED :
			$result = '流标';
			break;
		case COWPRO_ISSUING_STATUS_INVITE_BIDS_SUCCEED :
			$result = '满标，等待放款';
			break;
		case COWPRO_ISSUING_STATUS_REPAYMENT :
			$result = '等待还款';
			break;
		case COWPRO_ISSUING_STATUS_FINISHED :
			$result = '还款完毕';
			break;
		default :
			throw new PDOException ( '无效的《贷款申请表》状态: ' . $status );
	}

	return $result;
}

function _cowpro_issuing_get_status_options() {
	$options = array();
	$options[COWPRO_ISSUING_STATUS_UNAUDITED] = '末审核';
	$options[COWPRO_ISSUING_STATUS_AUDITED] = '审核通过';
	$options[COWPRO_ISSUING_STATUS_INVITE_BIDS_START] = '正在投标';
	$options[COWPRO_ISSUING_STATUS_INVITE_BIDS_FAILED] = '流标';
	$options[COWPRO_ISSUING_STATUS_INVITE_BIDS_SUCCEED] = '满标，等待放款';
	$options[COWPRO_ISSUING_STATUS_REPAYMENT] = '等待还款';
	$options[COWPRO_ISSUING_STATUS_FINISHED] = '还款完毕';
	return $options;
}