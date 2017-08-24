<?php

/*
 * Implementation of hook_token_info.
 */
function cowpro_issuing_token_info() {
	$issuing_type = array (
			'name' => 'Cowpro Issuing',
			'description' => 'Tokens related to individual Cowpro Issuing.',
			'needs-data' => 'cowpro_issuing'
	);
	$issuing ['title'] = array (
			'name' => '贷款标题',
			'description' => '贷款标题'
	);
	$issuing ['number'] = array (
			'name' => '合同编号',
			'description' => '合同编号'
	);
	$issuing ['applicant'] = array (
			'name' => '借款人',
			'description' => '借款人'
	);
	$issuing ['applicant_realname'] = array (
			'name' => '借款人姓名',
			'description' => '借款人真实姓名'
	);
	$issuing ['applicant_idno'] = array (
			'name' => '借款人',
			'description' => '借款人证件号码'
	);
	$issuing ['applicant_seal'] = array (
			'name' => '借款人印章',
			'description' => '借款人印章'
	);
	$issuing ['lender_detail_list'] = array (
			'name' => '出借人(借款明细)',
			'description' => '出借人(借款明细)'
	);
	$issuing ['lender_list'] = array (
			'name' => '出借人(姓名列表)',
			'description' => '出借人(姓名列表)'
	);
	$issuing ['loan_detail'] = array (
			'name' => '借款详情表',
			'description' => '借款详情表'
	);
	$issuing ['repayment_schedule'] = array (
			'name' => '还款计划表',
			'description' => '还款计划表'
	);
	$issuing ['sign_date'] = array (
			'name' => '签署日期',
			'description' => '签署日期',
			'type' => 'date',
	);
	/*
	 * $issuing[''] = array(
	 * 'name' => '',
	 * 'description' => '担保方',
	 * );
	 */

	$repayment_schedule_type = array (
			'name' => 'Cowpro Repayment Schedule',
			'description' => 'Tokens related to individual Cowpro Repayment Schedule.',
			'needs-data' => 'cowpro_repayment_schedule'
	);
	$repayment_schedule ['issuing_id'] = array (
			'name' => '贷款申请表',
			'description' => '贷款申请表',
			'type' => 'cowpro_issuing'
	);
	$repayment_schedule ['period'] = array (
			'name' => '第X期还款',
			'description' => '第X期还款'
	);
	$repayment_schedule ['period_total'] = array (
			'name' => '共X期',
			'description' => '共X期'
	);
	$repayment_schedule ['payer_uid'] = array (
			'name' => '付款人',
			'description' => '付款人',
			'type' => 'user'
	);
	$repayment_schedule ['receiver_uid'] = array (
			'name' => '收款人',
			'description' => '收款人',
			'type' => 'user'
	);
	$repayment_schedule ['payable_amount'] = array (
			'name' => '应付款',
			'description' => '应付款(包括贷款人应缴的各项费用，所以可能会与receivable_amount字段的值不同)',
			'type' => 'numeric'
	);
	$repayment_schedule ['payable_total_current_period'] = array (
			'name' => '本期应付款总额',
			'description' => '还款人在本期应还款的总额(对本期所有的应付款求和得到总额)',
			'type' => 'numeric'
	);
	$repayment_schedule ['paid_amount'] = array (
			'name' => '已付款金额',
			'description' => '已付款金额',
			'type' => 'numeric'
	);
	$repayment_schedule ['receivable_amount'] = array (
			'name' => '应收款',
			'description' => '应收款(包括债权人应缴的各项费用，所以可能会与payable_amount字段的值不同)',
			'type' => 'numeric'
	);
	$repayment_schedule ['received_amount'] = array (
			'name' => '已收款金额',
			'description' => '已收款金额',
			'type' => 'numeric'
	);
	$repayment_schedule ['deadline'] = array (
			'name' => '最后还款期限',
			'description' => '最后还款期限',
			'type' => 'date'
	);
	$repayment_schedule ['status'] = array (
			'name' => '还款状态',
			'description' => 'WAITING_FOR等待还款，COMPLETED已还款，IN_PROGRESS部分还款（债权转让的时候逻辑复杂，暂不支持），LOCKED锁定，在债权转让的时候，先设置该标志，这样来保证债权转让交易的原子性，ASSIGNABLE可转让，ASSIGNED已转让.'
	);
	$repayment_schedule ['created'] = array (
			'name' => 'created',
			'description' => 'The Unix timestamp when the record was created.',
			'type' => 'date'
	);
	$repayment_schedule ['changed'] = array (
			'name' => 'changed',
			'description' => 'The Unix timestamp when the record was most recently saved.',
			'type' => 'date'
	);

	return array (
			'types' => array (
					'cowpro_issuing' => $issuing_type,
					'cowpro_repayment_schedule' => $repayment_schedule_type
			),
			'tokens' => array (
					'cowpro_issuing' => $issuing,
					'cowpro_repayment_schedule' => $repayment_schedule
			)
	);
}

/*
 * Implementation of hook_tokens.
 */
function cowpro_issuing_tokens($type, $tokens, array $data = array(), array $options = array()) {
	$replacements = array ();
	if ($type == 'cowpro_issuing') {
		$replacements = _cowpro_issuing_tokens_issuing ( $type, $tokens, $data, $options );
	} else if ($type == 'cowpro_repayment_schedule') {
		$replacements = _cowpro_issuing_tokens_repayment ( $type, $tokens, $data, $options );
	}
	return $replacements;
}

function _cowpro_issuing_tokens_repayment($type, $tokens, array $data = array(), array $options = array()) {
  if (isset($options['language'])) {
    $language_code = $options['language']->language;
  }
  else {
    $language_code = LANGUAGE_NONE;
  }

  $replacements = array ();
	$sanitize = ! empty ( $options ['sanitize'] );

	// Cowpro repayment schedule tokens.
	if ($type == 'cowpro_repayment_schedule' && ! empty ( $data ['cowpro_repayment_schedule'] )) {
		$schedule = $data ['cowpro_repayment_schedule'];

		foreach ( $tokens as $name => $original ) {
			switch ($name) {
				case 'issuing_id' :
					$replacements [$original] = $schedule->issuing_id;
					break;
				case 'period' :
					$replacements [$original] = $schedule->period;
					break;
				case 'period_total' :
					$replacements [$original] = $schedule->period_total;
					break;
				case 'payer_uid' :
					$replacements [$original] = $schedule->payer_uid;
					break;
				case 'receiver_uid' :
					$replacements [$original] = $schedule->receiver_uid;
					break;
				case 'payable_amount' :
					$replacements [$original] = $schedule->payable_amount;
					break;
				case 'payable_total_current_period' :
					$query = new EntityFieldQuery ();
					$query->entityCondition ( 'entity_type', 'cowpro_repayment_schedule' )->propertyCondition ( 'issuing_id', $schedule->issuing_id )->propertyCondition ( 'period', $schedule->period )->propertyCondition ( 'receiver_uid', -1 );
					$result = $query->execute ();
					$ids = array_keys ( $result ['cowpro_repayment_schedule'] );
					$repayment_schedules = entity_load ( 'cowpro_repayment_schedule', $ids );
					$total = 0;
					foreach ($repayment_schedules as $repayment) {
						$total += $repayment->payable_amount;
					}
					$replacements [$original] = $total;
					break;
				case 'paid_amount' :
					$replacements [$original] = $schedule->paid_amount;
					break;
				case 'receivable_amount' :
					$replacements [$original] = $schedule->receivable_amount;
					break;
				case 'received_amount' :
					$replacements [$original] = $schedule->received_amount;
					break;
				case 'deadline' :
					$replacements [$original] = gmdate ( "Y年m月d日", $schedule->deadline );
					break;
				case 'status' :
					include_once 'includes/cowpro_repayment_schedule_status.inc';
					$content = _cowpro_repayment_schedule_get_readable_status ( $schedule->status );
					$replacements [$original] = $content;
					break;
				case 'created' :
					$replacements [$original] = gmdate ( "Y年m月d日", $schedule->created );
					break;
				case 'changed' :
					$replacements [$original] = gmdate ( "Y年m月d日", $schedule->changed );
					break;
			}
		}
	}

	return $replacements;
}
function _cowpro_issuing_tokens_issuing($type, $tokens, array $data = array(), array $options = array()) {
  if (isset($options['language'])) {
    $language_code = $options['language']->language;
  }
  else {
    $language_code = LANGUAGE_NONE;
  }

  $replacements = array ();
	$sanitize = ! empty ( $options ['sanitize'] );

	// Cowpro issing tokens.
	if ($type == 'cowpro_issuing' && ! empty ( $data ['cowpro_issuing'] )) {
		$issuing = $data ['cowpro_issuing'];

		foreach ( $tokens as $name => $original ) {
			switch ($name) {
				case 'title' :
					$replacements [$original] = $sanitize ? check_plain ( $issuing->title ) : $issuing->title;
					break;
				case 'number' :
					$replacements [$original] = sprintf ( "%'.06d", $issuing->nid );
					break;
				case 'amount' :
					$amount = $issuing->field_issuing[LANGUAGE_NONE][0]['loan_amounts'];
					$replacements [$original] = $amount;
					break;
				case 'applicant' :
					$applicant_uid = $issuing->field_applicant [LANGUAGE_NONE] [0] ['uid'];
					$u = user_load ( $applicant_uid );
					$replacements [$original] = $u->name;
					break;
				case 'applicant_realname' :
					$applicant_uid = $issuing->field_applicant [LANGUAGE_NONE] [0] ['uid'];
					$profile_real_name = cowpro_customer_profile_load_one_row_with_conditions ( $applicant_uid, 'real_name' );
					$replacements [$original] = $profile_real_name->name;
					break;
				case 'applicant_idno' :
					$applicant_uid = $issuing->field_applicant [LANGUAGE_NONE] [0] ['uid'];
					$profile_real_name = cowpro_customer_profile_load_one_row_with_conditions ( $applicant_uid, 'real_name' );
					$replacements [$original] = $profile_real_name->id_no;
					break;
				case 'applicant_seal' :
					$applicant_uid = $issuing->field_applicant [LANGUAGE_NONE] [0] ['uid'];
					$u = user_load ( $applicant_uid );
					$replacements [$original] = $u->seal; //TODO:获取seal的方式不对，还要改
					break;
				case 'lender_detail_list':
					include_once 'includes/cowpro_issuing.repayment_schedule.fun.inc';
					$journal_list = cowpro_issuing_bid_list ( $issuing->nid );
					$lender_detail = array ();
					$field_issuing = $issuing->field_issuing [LANGUAGE_NONE] [0];
					foreach ( $journal_list as $journal ) {
						// $journal->uid 出借人
						// $journal->amount 出借人的借款额
						$amount = 0;
						$schedule_list = _cowpro_issuing_build_repayment_schedule ( $journal->amount, $field_issuing ['annual_rate'], $field_issuing ['loan_term'], $field_issuing ['method_repayment'], $field_issuing['make_loans_time'] );
						foreach ( $schedule_list as $key => $value ) {
							$amount += $value['capital'] + $value['interest'];
						}
						$u = user_load ( $journal->uid );
						$profile_real_name = cowpro_customer_profile_load_one_row_with_conditions ( $journal->uid, 'real_name' );
						$l = array ();
						if (($GLOBALS['user']->uid == $journal->uid) || (in_array('administrator', $GLOBALS['user']->roles))) {
							$l ['name'] = $u->name;
							$l ['real_name'] = $profile_real_name->name;
							$l ['id_no'] = $profile_real_name->id_no;
						} else {
							$l ['name'] = _cowpro_issuing_tokens_utf_substr2($u->name);
							$l ['real_name'] = _cowpro_issuing_tokens_utf_substr2($profile_real_name->name);
							$l ['id_no'] = _cowpro_issuing_tokens_mask($profile_real_name->id_no, 4, strlen($profile_real_name->id_no)-8);
						}
						$l ['amount'] = $journal->amount;
						$l ['term'] = $field_issuing ['loan_term'];
						$l ['total'] = $amount;
						$lender_detail [] = $l;
					}
					$content = '';
					$content = <<<EOF
						<tr>
						<td>[site:name]用户名</td>
						<td>姓名</td>
						<td>证件号</td>
						<td>出借金额（元）</td>
						<td>借款期限</td>
						<td>全部应收（元）</td>
						</tr>
EOF;
					include_once 'includes/cowpro_issuing.repayment_schedule.fun.inc';
					$sum1 = 0;
					$sum2 = 0;
					foreach ( $lender_detail as $l ) {
						$content .= '<tr>';
						$content .= '<td>' . $l ['name'] . '</td>';
						$content .= '<td>' . $l ['real_name'] . '</td>';
						$content .= '<td>' . $l ['id_no'] . '</td>';
						$content .= '<td>' . $l ['amount'] . '</td>';
						$content .= '<td>' . _cowpro_issuing_get_readable_loan_term($l ['term']) . '</td>';
						$content .= '<td>' . $l ['total'] . '</td>';
						$content .= '</tr>';
						$sum1 = $sum1 + $l ['amount'];
						$sum2 = $sum2 + $l ['total'];
					}
					$content .= '<tr>';
					$content .= '<td>总计</td>';
					$content .= '<td></td>';
					$content .= '<td></td>';
					$content .= '<td>' . $sum1 . '</td>';
					$content .= '<td></td>';
					$content .= '<td>' . $sum2 . '</td>';
					$content .= '</tr>';
					$content = '<table border="1" style="margin: 0px auto; border-collapse: collapse; border: 1px solid rgb(0, 0, 0); width: 90%; ">' . $content . '</table>';
					$replacements [$original] = $content;
					break;
				case 'lender_list' :
					$journal_list = cowpro_issuing_bid_list ( $issuing->nid );
					$lender_list = array ();
					foreach ( $journal_list as $journal ) {
						//$u = user_load ( $journal->uid );
						$profile_real_name = cowpro_customer_profile_load_one_row_with_conditions ( $journal->uid, 'real_name' );
						if (($GLOBALS['user']->uid == $journal->uid) || (in_array('administrator', $GLOBALS['user']->roles))) {
							$lender_list [] = $profile_real_name->name;
						} else {
							$lender_list [] = _cowpro_issuing_tokens_utf_substr2($profile_real_name->name);
						}
					}
					$content = '<table border="0" style="margin: 0px auto; border-collapse: collapse; border: 0px solid rgb(0, 0, 0); width: 90%; ">';
					$i = 0;
					foreach ( $lender_list as $l ) {
						if ($i == 0) {
							$content .= '<tr>';

						}
						$content .= '<td>' . $l . '</td>';
						$i++;
						if ( $i == 5) {
							$i = 0;
							$content .= '<tr/>';
						}
					}
					if ($i != 0) {
						$content .= '<tr/>';
					}
					$content .= '</table>';
					$replacements [$original] = $content;
					break;
				case 'loan_detail':
					include_once 'includes/cowpro_issuing.repayment_schedule.fun.inc';
					$field_issuing = $issuing->field_issuing [LANGUAGE_NONE] [0];
					$content = '<table border="1" style="margin: 0px auto; border-collapse: collapse; border: 1px solid rgb(0, 0, 0); width: 90%; ">';
					$content .= '<tr>';
					$content .= '<td style="text-align:center;">借款详细用途</td>';
					$content .= '<td style="text-align:center;">' . $issuing->title . '</td>';
					$content .= '<td style="text-align:center;">借款年化利率</td>';
					$content .= '<td style="text-align:center;">' . $field_issuing ['annual_rate'] . '</td>';
					$content .= '</tr>';
					$content .= '<tr>';
					$content .= '<td style="text-align:center;">借款本金数额</td>';
					$content .= '<td style="text-align:center;">' . '人民币' . $field_issuing ['loan_amounts'] . '元' . '</td>';
					$content .= '<td style="text-align:center;">还款方式</td>';
					$content .= '<td style="text-align:center;">' . _cowpro_issuing_get_readable_repayment_method ( $field_issuing ['method_repayment'] ) . '</td>';
					$content .= '</tr>';
					$content .= '<tr>';
					$content .= '<td style="text-align:center;">月还本息数额</td>';
					$content .= '<td style="text-align:center;">详情见还款计划</td>';
					$content .= '<td style="text-align:center;">还款起止日期</td>';
					$content .= '<td style="text-align:center;">详情见还款计划</td>';
					$content .= '</tr>';
					$content .= '</table>';
					$replacements [$original] = $content;
					break;
				case 'repayment_schedule':
					include_once 'includes/cowpro_issuing.repayment_schedule.fun.inc';
					$content = '<table border="1" style="margin: 0px auto; border-collapse: collapse; border: 1px solid rgb(0, 0, 0); width: 90%; ">';
					$content .= '<tr>';
					$content .= '<td style="text-align:center;">还款日</td>';
					$content .= '<td style="text-align:center;">应还利息</td>';
					$content .= '<td style="text-align:center;">应还本金</td>';
					$content .= '</tr>';
					$field_issuing = $issuing->field_issuing [LANGUAGE_NONE] [0];
					$schedule_list = _cowpro_issuing_build_repayment_schedule ( $field_issuing ['loan_amounts'], $field_issuing ['annual_rate'], $field_issuing ['loan_term'], $field_issuing ['method_repayment'], $field_issuing['make_loans_time'] );
					foreach ( $schedule_list as $schedule ) {
						$content .= '<tr>';
						$content .= '<td style="text-align:center;">' . gmdate ( "Y年m月d日", $schedule ['deadline'] ) . '</td>';
						$content .= '<td style="text-align:center;">' . $schedule ['interest'] . '</td>';
						$content .= '<td style="text-align:center;">' . $schedule ['capital'] . '</td>';
						$content .= '</tr>';
					}
					$content .= '</table>';
					$replacements [$original] = $content;
					break;
				case 'sign_date' :
					$field_issuing = $issuing->field_issuing [LANGUAGE_NONE] [0];
					$replacements [$original] = gmdate ( "Y年m月d日", $field_issuing ['start_time'] );
					break;
			}
		}
	}

	return $replacements;
}

function _cowpro_issuing_tokens_mask ( $str, $start = 0, $length = null ) {
	$mask = preg_replace ( "/\S/", "*", $str );
	if( is_null ( $length )) {
		$mask = substr ( $mask, $start );
		$str = substr_replace ( $str, $mask, $start );
	}else{
		$mask = substr ( $mask, $start, $length );
		$str = substr_replace ( $str, $mask, $start, $length );
	}
	return $str;
}

function _cowpro_issuing_tokens_utf_substr2($str){
	$pa = "/[\x01-\x7f]|[\xc2-\xdf][\x80-\xbf]|\xe0[\xa0-\xbf][\x80-\xbf]|[\xe1-\xef][\x80-\xbf][\x80-\xbf]|\xf0[\x90-\xbf][\x80-\xbf][\x80-\xbf]|[\xf1-\xf7][\x80-\xbf][\x80-\xbf][\x80-\xbf]/";
	preg_match_all($pa, $str, $t_string);
	if (count($t_string[0])==1) {
		return $str;
	} else if(count($t_string[0])==2) {
		return _cowpro_issuing_tokens_cut_str($str, 1, 0).'****';
	} else {
		return _cowpro_issuing_tokens_cut_str($str, 1, 0).'****';//.cut_str($str, 1, -1);
	}
}

function _cowpro_issuing_tokens_cut_str($string, $sublen, $start = 0, $code = 'UTF-8')
{
	if($code == 'UTF-8')
	{
		$pa = "/[\x01-\x7f]|[\xc2-\xdf][\x80-\xbf]|\xe0[\xa0-\xbf][\x80-\xbf]|[\xe1-\xef][\x80-\xbf][\x80-\xbf]|\xf0[\x90-\xbf][\x80-\xbf][\x80-\xbf]|[\xf1-\xf7][\x80-\xbf][\x80-\xbf][\x80-\xbf]/";
		preg_match_all($pa, $string, $t_string);

		if(count($t_string[0]) - $start > $sublen) return join('', array_slice($t_string[0], $start, $sublen));
		return join('', array_slice($t_string[0], $start, $sublen));
	}
	else
	{
		$start = $start*2;
		$sublen = $sublen*2;
		$strlen = strlen($string);
		$tmpstr = '';

		for($i=0; $i< $strlen; $i++)
		{
			if($i>=$start && $i< ($start+$sublen))
			{
				if(ord(substr($string, $i, 1))>129)
				{
					$tmpstr.= substr($string, $i, 2);
				}
				else
				{
					$tmpstr.= substr($string, $i, 1);
				}
			}
			if(ord(substr($string, $i, 1))>129) $i++;
		}
		return $tmpstr;
	}
}
