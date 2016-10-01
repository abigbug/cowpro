<?php
define('COWPRO_REPAYMENT_SCHEDULE_STATUS_WAITING_FOR', 'WAITING_FOR'); // 等待还款
define('COWPRO_REPAYMENT_SCHEDULE_STATUS_COMPLETED', 'COMPLETED'); // 已还款
define('COWPRO_REPAYMENT_SCHEDULE_STATUS_IN_PROGRESS', 'IN_PROGRESS'); // 部分还款
define('COWPRO_REPAYMENT_SCHEDULE_STATUS_LOCKED', 'LOCKED'); // 锁定，在债权转让的时候，先设置该标志，这样来保证债权转让交易的原子性.
define('COWPRO_REPAYMENT_SCHEDULE_STATUS_ASSIGNABLE', 'ASSIGNABLE'); // 可转让
define('COWPRO_REPAYMENT_SCHEDULE_STATUS_ASSIGNED', 'ASSIGNED'); // 已转让

function _cowpro_repayment_schedule_get_readable_status($status) {
	$result = '';
	switch ($status) {
		case COWPRO_REPAYMENT_SCHEDULE_STATUS_WAITING_FOR :
			$result = '等待还款';
			break;
		case COWPRO_REPAYMENT_SCHEDULE_STATUS_COMPLETED :
			$result = '已还款';
			break;
		case COWPRO_REPAYMENT_SCHEDULE_STATUS_IN_PROGRESS :
			$result = '部分还款';
			break;
		case COWPRO_REPAYMENT_SCHEDULE_STATUS_LOCKED :
			$result = '锁定';
			break;
		case COWPRO_REPAYMENT_SCHEDULE_STATUS_ASSIGNABLE :
			$result = '可转让';
			break;
		case COWPRO_REPAYMENT_SCHEDULE_STATUS_ASSIGNED :
			$result = '已转让';
			break;
		default :
			throw new PDOException ( '无效的《还款计划表》状态: ' . $status );
	}

	return $result;
}

function _cowpro_repayment_schedule_get_status_options() {
	$options = array();
	$options[COWPRO_REPAYMENT_SCHEDULE_STATUS_WAITING_FOR] = '等待还款';
	$options[COWPRO_REPAYMENT_SCHEDULE_STATUS_COMPLETED] = '已还款';
	$options[COWPRO_REPAYMENT_SCHEDULE_STATUS_IN_PROGRESS] = '部分还款';
	$options[COWPRO_REPAYMENT_SCHEDULE_STATUS_LOCKED] = '锁定';
	$options[COWPRO_REPAYMENT_SCHEDULE_STATUS_ASSIGNABLE] = '可转让';
	$options[COWPRO_REPAYMENT_SCHEDULE_STATUS_ASSIGNED] = '已转让';
	return $options;
}