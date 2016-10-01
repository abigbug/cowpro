<?php

/*
 * Implementation of hook_token_info.
 */
function cowpro_fund_token_info() {
	$type = array (
			'name' => 'Cowpro Fund Journal',
			'description' => 'Tokens related to individual Cowpro Fund Journal.',
			'needs-data' => 'cowpro_fund_journal'
	);

	$fund ['journal_id'] = array (
			'name' => '日记账序号',
			'description' => '日记账序号.'
	);
	$fund ['type'] = array (
			'name' => '交易类型',
			'description' => '交易类型，包括TOPUP(充值)、WITHDRAW(提现)、BID(投标)、ISSUING_FAILING(流标退款)、MAKE_LOANS_TO(满标放款)、REPAYMENT_RECEIPTS(按期还款，收款方)、REPAYMENT_PAYMENTS(按期还款，付款方)等等，其它模块也可以对此进行扩展，定义新的交易类型.'
	);
	$fund ['internal_reference_id'] = array (
			'name' => '内部索引号',
			'description' => '与交易相关的业务记录的索引号，可能为NULL.'
	);
	$fund ['external_reference_id'] = array (
			'name' => '外部索引号',
			'description' => '外部（资金托管方）对应的索引号，可能为NULL.'
	);
	$fund ['uid'] = array (
			'name' => 'uid',
			'description' => '与交易相关的用户的uid.',
			'type' => 'user'
	);
	$fund ['amount'] = array (
			'name' => '金额',
			'description' => '金额',
			'type' => 'numeric'
	);
	$fund ['status'] = array (
			'name' => '交易状态',
			'description' => '1:表示交易成功; 2:表示交易失败; 针对type=BID这钟类型，还有status=2这种情况，表示"投标"以后"流标返款"成功的用例'
	);
	$fund ['created'] = array (
			'name' => 'created',
			'description' => 'The Unix timestamp when the record was created.',
			'type' => 'date'
	);
	$fund ['changed'] = array (
			'name' => 'changed',
			'description' => 'The Unix timestamp when the record was most recently saved.',
			'type' => 'date'
	);

	return array (
			'types' => array (
					'cowpro_fund_journal' => $type,
			),
			'tokens' => array (
					'cowpro_fund_journal' => $fund,
			)
	);
}

/*
 * Implementation of hook_tokens.
 */
function cowpro_fund_tokens($type, $tokens, array $data = array(), array $options = array()) {
  if (isset($options['language'])) {
    $language_code = $options['language']->language;
  }
  else {
    $language_code = LANGUAGE_NONE;
  }

  $replacements = array ();
	$sanitize = ! empty ( $options ['sanitize'] );

	// Cowpro fund journal tokens.
	if ($type == 'cowpro_fund_journal' && ! empty ( $data ['cowpro_fund_journal'] )) {
		$journal = $data ['cowpro_fund_journal'];

		foreach ( $tokens as $name => $original ) {
			switch ($name) {
				case 'journal_id' :
					$replacements [$original] = $journal->journal_id;
					break;
				case 'type' :
					include_once 'includes/cowpro_fund_type.inc';
					$content = _cowpro_fund_get_readable_status($journal->type);
					$replacements [$original] = $content;
					break;
				case 'internal_reference_id' :
					$replacements [$original] = $journal->internal_reference_id;
					break;
				case 'external_reference_id' :
					$replacements [$original] = $journal->external_reference_id;
					break;
				case 'uid' :
					$replacements [$original] = $journal->uid;
					break;
				case 'amount' :
					$replacements [$original] = $journal->amount;
					break;
				case 'status' :
					$content = '未知';
					if ($journal->status == 1) {
						$content = '成功';
					} else if ($journal->status == 2) {
						$content = '失败';
					}
					$replacements [$original] = $content;
					break;
				case 'created' :
					$replacements[$original] = format_date($journal->created, 'medium', '', NULL, $language_code);
					break;
				case 'changed' :
					$replacements[$original] = format_date($journal->created, 'medium', '', NULL, $language_code);
					break;
			}
		}
	}

	return $replacements;
}
