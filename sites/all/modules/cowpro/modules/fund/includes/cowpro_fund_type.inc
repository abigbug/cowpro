<?php
define('COWPRO_FUND_TYPE_TOPUP', 'TOPUP'); // 充值
define('COWPRO_FUND_TYPE_WITHDRAW', 'WITHDRAW'); // 提现
define('COWPRO_FUND_TYPE_BID', 'BID'); // 投标
define('COWPRO_FUND_TYPE_ISSUING_FAILING', 'ISSUING_FAILING'); // 流标退款
define('COWPRO_FUND_TYPE_MAKE_LOANS_TO', 'MAKE_LOANS_TO'); // 满标放款
define('COWPRO_FUND_TYPE_REPAYMENT_RECEIPTS', 'REPAYMENT_RECEIPTS'); // 按期还款，收款方
define('COWPRO_FUND_TYPE_REPAYMENT_PAYMENTS', 'REPAYMENT_PAYMENTS'); // 按期还款，付款方
define('COWPRO_FUND_TYPE_INTERNAL_TRANS', 'INTERNAL_TRANS'); // 内部转账

function _cowpro_fund_get_readable_status($status) {
	$result = '';
	switch ($status) {
		case COWPRO_FUND_TYPE_TOPUP :
			$result = '充值';
			break;
		case COWPRO_FUND_TYPE_WITHDRAW :
			$result = '提现';
			break;
		case COWPRO_FUND_TYPE_BID :
			$result = '投标';
			break;
		case COWPRO_FUND_TYPE_ISSUING_FAILING :
			$result = '流标退款';
			break;
		case COWPRO_FUND_TYPE_MAKE_LOANS_TO :
			$result = '满标放款';
			break;
		case COWPRO_FUND_TYPE_REPAYMENT_RECEIPTS :
			$result = '按期还款，收款方';
			break;
		case COWPRO_FUND_TYPE_REPAYMENT_PAYMENTS :
			$result = '按期还款，付款方';
			break;
		case COWPRO_FUND_TYPE_INTERNAL_TRANS :
			$result = '内部转账';
			break;
		default :
			throw new PDOException ( '无效的《资金明细账》状态: ' . $status );
	}

	return $result;
}

function _cowpro_fund_get_type_options() {
	$options = array();
	$options[COWPRO_FUND_TYPE_TOPUP] = '充值';
	$options[COWPRO_FUND_TYPE_WITHDRAW] = '提现';
	$options[COWPRO_FUND_TYPE_BID] = '投标';
	$options[COWPRO_FUND_TYPE_ISSUING_FAILING] = '流标退款';
	$options[COWPRO_FUND_TYPE_MAKE_LOANS_TO] = '满标放款';
	$options[COWPRO_FUND_TYPE_REPAYMENT_RECEIPTS] = '回款';
	$options[COWPRO_FUND_TYPE_REPAYMENT_PAYMENTS] = '还款';
	$options[COWPRO_FUND_TYPE_INTERNAL_TRANS] = '内部转账';
	return $options;
}