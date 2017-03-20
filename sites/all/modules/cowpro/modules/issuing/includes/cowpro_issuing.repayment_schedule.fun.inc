<?php
/**
 * 还款方式
 * 一、等额本息。
 * 它是在还款期内，每月偿还同等数额的贷款(包括本金和利息)。
 * 每月还款额计算公式为：［贷款本金×月利率×（1＋月利率）＾还款月数］÷［（1＋月利率）＾还款月数－1］
 * 参考： http://baike.baidu.com/view/178589.htm
 * 二、等额本金。
 * 它是是在还款期内把贷款数总额等分，每月偿还同等数额的本金和剩余贷款在该月所产生的利息，
 * 这样由于每月的还款本金额固定，而利息越来越少，贷款人起初还款压力较大，
 * 但是随时间的推移每月还款数也越来越少。
 * 等额本金贷款计算公式为：每月还款金额 = （贷款本金 / 还款月数）+（本金 - 已归还本金累计额）×每月利率。
 * 参考： http://baike.baidu.com/view/1274152.htm
 * 三、净息还款法。（每月付息到期还本）
 * 按期付息到期还本法（飘浮式贷款Balloon Loan）
 * 它指贷款人在贷款期限内只付利息不用还本，本金可以在贷款到期后一次性偿还。
 * 按期付息到期还本方式系到期日前只付利息而不还本，到期时一次将本金偿还的方式。
 * 在贷款期间的支付压力最小，只需支付利息，但到期时，必须支付庞大的本金，因此，较适用于短期贷款，
 * 而不适用中长期的房屋贷款。可想而知，此种方式最后一次付款比以前历次额度高出甚多，且所缴的利息，
 * 将是所有方式中最高的。
 *
 * 中英文对照：
 * 等额本息还款法 average capital plus interest method
 * 等额本金还款法 average capital method
 * 净息还款法 balloon Loan
 *
 * 贷款年利率、月利率和日利率是如何转换的？
 * 贷款利率分为年利率、月利率和日利率。
 * 具体转换公式为：月利率=日利率×30；年利率=月利率×12。如月利率为5‰，则年利率为5‰×12=6%。
 */
function _cowpro_issuing_get_repayment_method_options() {
	$methods = array (
			'average_capital_plus_interest_method' => '等额本息',
			'average_capital_method' => '等额本金',
			'balloon_loan' => '每月付息到期还本',
	);
	return $methods;
}

/**
 * 将还款方式换为便于用户理解的文字表述
 * @param unknown $repayment_method
 */
function _cowpro_issuing_get_readable_repayment_method($repayment_method) {
	$options = _cowpro_issuing_get_repayment_method_options();
	if (array_key_exists($repayment_method, $options)) {
		return $options[$repayment_method];
	} else {
		return '未知';
	}
}

/**
 * 在根据还款方式生成还款计划表的函数中，
 * 所有大于等三十天贷款期限都是以月为单位
 * 也就是说大于三十天的贷款期限都必须是30的倍数
 * 只有小于三十在的短期贷款，我们在还款计划表中是将年利息换算为每日利息，
 * 大于等于三十天的贷款，我们是将年利息换算为月利息来生成还款计划表
 * @return string[]
 */
function _cowpro_issuing_get_loan_term_options() {
	$terms = array (
			7 => '七天',
			30 => '一个月',
			90 => '三个月',
			180 => '半年',
			360 => '一年',
	);
	return $terms;
}

function _cowpro_issuing_get_loan_term_options_2() {
	$terms = array (
			7 => '+1 week',
			30 => '+1 month',
			90 => '+3 month',
			180 => '+6 month',
			360 => '+1 year',
	);
	return $terms;
}

/**
 * 将贷款期限转换为便于用户理解的贷款期限的文字表述
 * @param unknown $loan_term
 */
function _cowpro_issuing_get_readable_loan_term($loan_term) {
	$terms = _cowpro_issuing_get_loan_term_options();
	if (array_key_exists($loan_term, $terms)) {
		return $terms[$loan_term];
	} else {
		return $loan_term;
	}
}

/**
 * 将贷款期限转换为便于用户理解的贷款期限的文字表述
 * @param unknown $loan_term
 */
function _cowpro_issuing_get_interest_period($start_time, $loan_term) {
	$terms = _cowpro_issuing_get_loan_term_options_2();
	if (array_key_exists($loan_term, $terms)) {
		return date("Y-m-d", strtotime($terms[$loan_term], $start_time));
	} else {
		return date("Y-m-d", $start_time + strtotime("+$loan_term days"));
	}
}

/**
 * 计算贷款总共分几期、以及每一期的还款日
 * (按月分期，如果不足一个月，例如‘七天’的标的，最后的还款日就在第七天)
 * @param 分期天数(参考_cowpro_issuing_get_loan_term_options) $term
 * @return 返回“分期表”，“分期表”是一个数组结构，
 * “分期表”中每一个元素代表一个分期，每一个分期元素也是一个数组结构，
 * 每一个分期元素中['interval_days']是一个整数值，代表天数，例如‘30’就表示一个月
 * ['deadline']是该期的最后还款时间，是一个 unix timestamp 类型
 */
function _cowpro_issuing_periods($term, $make_loans_time = null) {
	if ($make_loans_time) {
		$start_time = $make_loans_time;
	} else {
		$start_time = strtotime(date('Y-m-d 23:59:59'));
	}
	//$date = date('Y-m-d H:i:s', $time);
	//echo $date;

	$periods = array();
	$count = floor($term / 30);
	$i = 0;
	while($i<$count) {
		$periods[$i] = array();
		$periods[$i]['interval_days'] = 30;
		$periods[$i]['deadline'] = _cowpro_issuing_next_period($start_time, $i+1);
		$periods[$i]['term_no'] = $i + 1;//期次，对应表'cowpro_repayment_schedule'里面的字段'period'
		$i++;
	}
	$remainder = $term % 30;
	if ($remainder > 0) {
		//处理'七天'这一类不足一个月的短期借款
		if ($i > 0) {
			$base_time = $periods[$i-1];
		} else {
			$base_time = $start_time;
		}
		$periods[$i] = array();
		$periods[$i]['interval_days'] = $remainder;
		$periods[$i]['deadline'] = strtotime(date("Y-m-d H:i:s", $base_time) . " + $remainder days");
		$periods[$i]['term_no'] = $i + 1;//期次，对应表'cowpro_repayment_schedule'里面的字段'period'
	}
	return $periods;
}

function _cowpro_issuing_next_period($start_time, $month_span = 1) {
	$period = strtotime("+$month_span month", $start_time);
	$month_start = (int)date('n', $start_time);
	$month_period = (int)date('n', $period);
	if ($month_period > $month_start + $month_span) {
		//假设$start_time为2016年1月31日，
		//这时候通过strtotime("+1 month", $start_time)操作的结果将是2016年3月2日
		//我们要对这种情况进行处理，将结果置为前一个月（2月）的最后一天
		//echo $last_day_of_month.'ccc';
		//$period = strtotime('-1 month', strtotime($last_day_of_month));
		$period = strtotime('-1 month', $period);
		$last_day_of_month = date("Y-m-t H:i:s", $period);
		$period = strtotime($last_day_of_month);
	}
	return $period;
}

/**
 * 等额本息
 * 它是在还款期内，每月偿还同等数额的贷款(包括本金和利息)。
 * 每月还款额计算公式为：［贷款本金×月利率×（1＋月利率）＾还款月数］÷［（1＋月利率）＾还款月数－1］
 * 参考： http://baike.baidu.com/view/178589.htm
 *
 * 贷款期限$loan_term的有效值，请参考方法_cowpro_issuing_get_loan_term_options()的注释
 */
function _cowpro_issuing_average_capital_plus_interest_method($loan_amounts, $annual_rate, $loan_term, $periods) {
	if ($loan_term < 30) {
		//小于一个月的短期贷款
		$periods = _cowpro_issuing_short_term_loan($loan_amounts, $annual_rate, $loan_term, $periods);
	} else {
		$months = $loan_term / 30;//还款月数
		$month_rate = ($annual_rate / 100) / 12;//月利率
		$pow = pow(1 + $month_rate, $months);//（1＋月利率）＾还款月数
		$month_repayment = $loan_amounts * $month_rate * $pow / ($pow - 1);//［贷款本金×月利率×（1＋月利率）＾还款月数］÷［（1＋月利率）＾还款月数－1］
		$month_repayment = round($month_repayment, 2);
		for( $i= 0 ; $i < count($periods) ; $i++ ) {
			$periods[$i]['capital'] = $month_repayment;
			$periods[$i]['interest'] = 0;//"等额本息"这种还款方案是将本金与利息混合计算的，所以我们没有将利息单列出来
		}
	}
	return $periods;
}

/**
 * 等额本金
 * 它是是在还款期内把贷款数总额等分，每月偿还同等数额的本金和剩余贷款在该月所产生的利息，
 * 这样由于每月的还款本金额固定，而利息越来越少，贷款人起初还款压力较大，
 * 但是随时间的推移每月还款数也越来越少。
 * 等额本金贷款计算公式为：每月还款金额 = （贷款本金 / 还款月数）+（本金 - 已归还本金累计额）×每月利率。
 * 参考： http://baike.baidu.com/view/1274152.htm
 *
 * 贷款期限$loan_term的有效值，请参考方法_cowpro_issuing_get_loan_term_options()的注释
 */
function _cowpro_issuing_average_capital_method($loan_amounts, $annual_rate, $loan_term, $periods) {
	if ($loan_term < 30) {
		//小于一个月的短期贷款
		$periods = _cowpro_issuing_short_term_loan($loan_amounts, $annual_rate, $loan_term, $periods);
	} else {
		$months = $loan_term / 30;//总共分几期
		$month_rate = ($annual_rate / 100) / 12;//月利率
		$month_repayment_capital = $loan_amounts / 12;//每月应还本金
		$month_repayment_capital = round($month_repayment_capital, 2);
		$loan_remain = $loan_amounts;//剩余（未偿还）的本金
		for( $i= 0 ; $i < count($periods) ; $i++ ) {
			if ($i == count($periods)-1) {
				//最后一期
				$periods[$i]['capital'] = $loan_remain;
			} else {
				$periods[$i]['capital'] = $month_repayment_capital;
			}
			$interest = $loan_remain * $month_rate;
			$interest = round($interest, 2);
			$periods[$i]['interest'] = $interest;
			$loan_remain = $loan_remain - $month_repayment_capital;
		}
	}
	return $periods;
}

/**
 * 净息还款法。（每月付息到期还本）
 * 按期付息到期还本法（飘浮式贷款Balloon Loan）
 * 它指贷款人在贷款期限内只付利息不用还本，本金可以在贷款到期后一次性偿还。
 * 按期付息到期还本方式系到期日前只付利息而不还本，到期时一次将本金偿还的方式。
 * 在贷款期间的支付压力最小，只需支付利息，但到期时，必须支付庞大的本金，因此，较适用于短期贷款，
 * 而不适用中长期的房屋贷款。可想而知，此种方式最后一次付款比以前历次额度高出甚多，且所缴的利息，
 * 将是所有方式中最高的。
 *
 * 贷款期限$loan_term的有效值，请参考方法_cowpro_issuing_get_loan_term_options()的注释
 */
function _cowpro_issuing_balloon_loan($loan_amounts, $annual_rate, $loan_term, $periods) {
	if ($loan_term < 30) {
		//小于一个月的短期贷款
		$periods = _cowpro_issuing_short_term_loan($loan_amounts, $annual_rate, $loan_term, $periods);
	} else {
		$interest_total = ($loan_amounts * $annual_rate / 100) * ($loan_term / 360);
		$interest_total = round($interest_total, 2);
		$interest_sum = 0;
		for( $i= 0 ; $i < count($periods) ; $i++ ) {
			if ($i == count($periods)-1) {
				//最后一期
				$periods[$i]['capital'] = $loan_amounts;
				$periods[$i]['interest'] = $interest_total - $interest_sum;
			} else {
				$periods[$i]['capital'] = 0;
				$interest = 30 * $interest_total / $loan_term;
				$interest = round($interest, 2);
				$interest_sum = $interest_sum + $interest;
				$periods[$i]['interest'] = $interest;
			}
		}
	}
	return $periods;
}

/**
 * 短期的（小于一个月的），一次性付息还本的贷款
 * 这种贷款不论选用什么还款方式，结果都是一样的
 *
 * @param unknown $loan_amounts
 * @param unknown $annual_rate
 * @param unknown $loan_term
 * @param unknown $periods
 */
function _cowpro_issuing_short_term_loan($loan_amounts, $annual_rate, $loan_term, $periods) {
	$interest_total = ($loan_amounts / $annual_rate) * ($loan_term / 360);
	$interest_total = round($interest_total, 2);
	$periods[0]['capital'] = $loan_amounts;
	$periods[0]['interest'] = $interest_total;
	return $periods;
}

function _cowpro_issuing_build_repayment_schedule($loan_amounts, $annual_rate, $loan_term, $method_repayment, $make_loans_time=null) {
	//计算贷款总共分几期、以及每一期的还款日
	$periods = _cowpro_issuing_periods($loan_term, $make_loans_time);

	$args = array();
	$args[] = $loan_amounts;
	$args[] = $annual_rate;
	$args[] = $loan_term;
	$args[] = $periods;
	$function = '_cowpro_issuing_' . $method_repayment;
	$schedule = call_user_func_array($function, $args);

	return $schedule;
}

/**
 *
 * @param 贷款申请表的nid $nid
 * @param 贷款申请人的uid $applicant
 * @param 贷款申请表，数组结构 $issuing
 */
function _cowpro_issuing_save_repayment_schedule($nid, $applicant, $issuing) {
	//根据还款方式计算每一期的还款额
	$journal_list = cowpro_issuing_bid_list($nid);

	/*
	 * 向$journal_list里面增加一条记录，用于生成借款人每一期需要还款的金额，
	 * 该记录的收款人UID为-1
	 * 这样，可以方便我们输出各种还款报表，如果需要当期还款合计，也不必在输出的时候分组求和，只需要过滤UID=-1的记录就可以
	 */
	$amount = 0;
	foreach ($journal_list as $journal) {
		$amount = $amount + $journal->amount;
	}
	$payer_total = new stdClass();
	$payer_total->amount = $amount;
	$payer_total->created = REQUEST_TIME;
	$payer_total->uid = -1;
	$journal_list[] = $payer_total;

	$repayment_schedule = array();
	foreach ($journal_list as $journal) {
		//$journal->uid 出借人
		//$journal->amount 出借人的借款额
		$schedule_list = _cowpro_issuing_build_repayment_schedule($journal->amount, $issuing['annual_rate'], $issuing['loan_term'], $issuing['method_repayment'], $issuing['make_loans_time']);
		foreach ($schedule_list as $key => $value) {
			$value['payer_uid'] = $applicant['uid'];
			$value['receiver_uid'] = $journal->uid;
			$repayment_schedule[] = $value;
		}
	}

	//将“还款计划表”保存到数据库中
	$period_total = count($repayment_schedule) / count($journal_list);
	foreach($repayment_schedule as $schedule) {
		$entity_value = array(
				'issuing_id' => $nid,//对应的原始贷款申请表编号(nid)
				'period' => $schedule['term_no'],//期次
				'period_total' => $period_total,//还款计划共分X期
				'payer_uid' => $schedule['payer_uid'],//付款人uid
				'receiver_uid' => $schedule['receiver_uid'],//收款人uid
				'payable_amount' => $schedule['capital'] + $schedule['interest'],//应付款(包括贷款人应缴的各项费用，所以可能会与receivable_amount字段的值不同)
				'paid_amount' => 0,//已付款金额
				'receivable_amount' => $schedule['capital'] + $schedule['interest'],//应收款(包括债权人应缴的各项费用，所以可能会与payable_amount字段的值不同)
				'received_amount' => 0,//已收款金额
				'capital' => $schedule['capital'],//当期本金
				'interest' => $schedule['interest'],//当期利息
				'deadline' => $schedule['deadline'],//最后还款期限 The Unix timestamp
				'status' => 'WAITING_FOR',
		);
		$entity = entity_create('cowpro_repayment_schedule', $entity_value);
		$data = array();//借贷双方应向平台支付的各项费用，以及其它扩展的信息都可以记录在这里
		//$data['fee'] = 100;
		//$entity->data = serialize($data);
		$entity->data = $data;
		entity_get_controller('cowpro_repayment_schedule')->save($entity);
	}

}

function _cowpro_issuing_get_repayment_schedule_data_serial($schedule) {
	$data_array = $schedule->data;
	$max_serial = -1;
	foreach($data_array as $key => $value) {
		if ($max_serial < $value['serial']) {
			$max_serial = $value['serial'];
		}
	}
	return $max_serial + 1;
}