<?php
define('T01', 'T01'); // 投标
define('T02', 'T02'); // 取消投标
define('T03', 'T03'); // 放款
define('T04', 'T04'); // 还款
define('T05', 'T05'); // 出款
define('T10', 'T10'); // 营销
define('T12', 'T12'); // 其他费用收取
define('R01', 'R01'); // 客户代扣充值
define('R02', 'R02'); // 客户网银充值
define('W01', 'W01'); // 客户提现

function _jiupaipay_get_type_options() {
	$options = array();
	$options[T01] = '投标';
	$options[T02] = '取消投标';
	$options[T03] = '放款';
	$options[T04] = '还款';
	$options[T05] = '出款';
	$options[T10] = '营销';
	$options[T12] = '其他费用收取';
	$options[R01] = '客户代扣充值';
	$options[R02] = '客户网银充值';
	$options[W01] = '客户提现';
	return $options;
}