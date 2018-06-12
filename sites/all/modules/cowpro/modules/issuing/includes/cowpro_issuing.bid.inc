<?php
/**
 * callback.
 * 我要投资
 */
function _cowpro_issuing_bid($node) {
	ctools_include ( 'modal' );
	ctools_include ( 'ajax' );
	$issuing = $node->field_issuing [LANGUAGE_NONE] [0];
	$form_state = array (
			'title' => $node->title,
			'nid' => $node->nid,
			'loan_amounts' => $issuing['loan_amounts'],
			'bid_amount' => 0,
			'node' => $node,
			'ajax' => TRUE,
	);
	$commands = ctools_modal_form_wrapper ( '_cowpro_issuing_bid_form', $form_state );

	//以AJAX方式驱动modal窗口的显示的时候，暂时没有找到更好的定义窗口维度的方法，所以暂时用js的方式来实现
	$js = <<<js
	<script type="text/javascript">
	var width = 800;
	var height = 400;
	var contentRight = 25;
    var contentBottom = 45;
	jQuery('div.ctools-modal-content').css({
		'width': width + 'px',
		'height': height + 'px'
	});
    jQuery('div.ctools-modal-content .modal-content').css({
        'width': (width - contentRight) + 'px',
        'height': (height - contentBottom) + 'px'
    });
	var styleProps = jQuery('#modalContent').css('top');
	modalContentResize();
	jQuery('#modalContent').css('top', styleProps);
	</script>
js;

	$commands[0]['output'] .= $js;
	print ajax_render ( $commands );
	exit ();
}

function _cowpro_issuing_bid_form($form, &$form_state) {
	$bid_avail = _cowpro_issuing_bid_avail ( $form_state['nid'], $form_state['loan_amounts'] );
	GLOBAL $user;
	$balance = custodian_get_balance($user);
	$balance_available = 0;
	if ($balance) {
		$balance_available = $balance ['balance'];
	}

	$form ['balance_available'] = array (
			'#markup' => "<p>可用余额(元)：$balance_available</p>",
	);

	$form ['amount'] = array (
			'#type' => 'numberfield',
			'#title' => '投资金额(元)',
			'#description' => '',
			'#min' => 1,
			'#max' => $bid_avail,
			'#input' => TRUE,
			'#weight' => 10,
	);
	$form['information'] = array(
			'#markup' => "<p>当前最大可投资金额为 $bid_avail 元。</p>",
	);

	$hook = 'cowpro_issuing_bid_form';
	foreach (module_implements($hook) as $module) {
		$form = array_merge($form, module_invoke($module, $hook, $form, $form_state));
	}

	$form ['submit'] = array (
			'#type' => 'submit',
			'#value' => '投标',
			'#weight' => 100,
	);
	$form ['cancel'] = array (
			'#type' => 'submit',
			'#value' => '取消',
			'#weight' => 200,
	);
	return $form;
}

function _cowpro_issuing_bid_avail($nid, $loan_amounts) {
	$query = db_select('cowpro_fund_journal', 'j');
	$query->addExpression('SUM(amount)', 'total');
  $query->condition('j.internal_reference_id', 'ISSUING-' . $nid, '=');
  $query->condition('j.type', 'BID', '=');
  $query->condition('j.status', TRUE, '=');
  $result = $query->execute()->fetchAll();
  $bid_avail = $loan_amounts - $result[0]->total;
	return $bid_avail;
}

function _cowpro_issuing_bid_list($nid) {
	$query = db_select('cowpro_fund_journal', 'j');
	$query->addField('j', 'uid');
	$query->addField('j', 'amount');
	$query->addField('j', 'created');
	$query->condition('j.internal_reference_id', 'ISSUING-' . $nid, '=');
  $query->condition('j.type', 'BID', '=');
  $query->condition('j.status', TRUE, '=');
  $result = $query->execute()->fetchAll();
	return $result;
}

/**
 * Validation callback for _cowpro_issuing_bid_form().
 */
function _cowpro_issuing_bid_form_validate($form, &$form_state) {
	if ($form_state ['values'] ['op'] === $form_state ['values'] ['submit']) {
		$bid_avail = _cowpro_issuing_bid_avail($form_state['nid'], $form_state['loan_amounts']);
		if ($form_state ['values']['amount'] > $bid_avail) {
			form_set_error ( 'bid', "请注意，当前最大可投资金额为 $bid_avail 元" );
		}
		if ($form_state ['values']['amount'] <= 0) {
			form_set_error ( 'bid', '请填写有效的投资金额(大于零)' );
		}
		if ($form_state ['values']['amount'] % 1 != 0) {
			form_set_error ( 'bid', '投资金额的最小单位是“元”' );
		}
		if ($form_state ['values']['amount'] < 100) {
			if ($bid_avail >= 100) {
				//在可投标余额大于100的时候，投资金额必需大于等于100元
				form_set_error ( 'bid', '投资金额必需大于等于100元' );
			} else if ($form_state ['values']['amount'] != $bid_avail) {
				//如果可投标余额小于100，就没有这个限制
				form_set_error ( 'bid', "投资金额必需是 $bid_avail 元" );
			}
		}
		if ($form_state ['values']['amount'] > 200000) {
			form_set_error ( 'bid', '当投资金额大于二十万元的时候，请拆分成多笔资金分别投资' );
		}
		global $user;
		$balance = cowpro_fund_get_balance($user->uid);
		$availableAmount = 0;
		if ($balance ['success']) {
		    $availableAmount = $balance['balance'];
		}
		if ($form_state ['values']['amount'] > $availableAmount) {
		    form_set_error ( 'bid', '账户余额不足' );
		}
		
		module_invoke_all ( 'cowpro_issuing_bid_form_validate', $form, $form_state );
	}
}

function _cowpro_issuing_bid_form_submit(&$form, &$form_state) {
	if ($form_state ['values'] ['op'] === $form_state ['values'] ['submit']) {
		$hook = 'cowpro_issuing_bid_form_submit';
		$result = TRUE;
		foreach (module_implements($hook) as $module) {
			$result = $result && module_invoke($module, $hook, $form, $form_state);
		}

		if ($result) {
			$amount = $form_state['input']['amount'];
			$nid = $form_state['nid'];
			$uid = $GLOBALS['user']->uid;
			$entity_value = array(
					'uid' => $uid,
					'status' => FALSE,
					'type' => 'BID',
					'amount' => $amount,
					'issuing_id' => $nid,
					'internal_reference_id' => 'ISSUING-' . $nid,
			);
			$entity = entity_create('cowpro_fund_journal', $entity_value);
			entity_get_controller('cowpro_fund_journal')->save($entity);
			$journal_id = $entity->journal_id;

			$result = custodian_cowpro_fund_bid($uid, $amount, $nid, $journal_id);

			$entity = entity_load_single('cowpro_fund_journal', $journal_id);
			if ($result['success']) {
				$status = TRUE;
			} else {
				$status = FALSE;
			}
			$entity->status = $status;
			$entity->external_reference_id =$result['external_reference_id'];
			$entity->data = $result['data'];
			entity_get_controller('cowpro_fund_journal')->save($entity);

			_cowpro_issuing_bid_finished($result['success'], $nid, $journal_id);
			module_invoke_all ( 'cowpro_issuing_bid_finished', $result['success'], $nid, $journal_id );
			if ($result['success']) {
				$message = '投标成功';
				drupal_set_message($message);
			} else {
				$message = '投标失败:' . $result['message'] . '<br/>(代码：' . $result['result_code'] . ')';
				drupal_set_message($message, 'error');
			}
		}

		ctools_include ( 'modal' );
		ctools_include ( 'ajax' );
		$commands = array ();
		$commands[] = ctools_ajax_command_reload();
		print ajax_render ( $commands );
		drupal_exit ();
	} else {
		$commands = array ();
		$commands [] = ctools_modal_command_dismiss ();
		print ajax_render ( $commands );
		drupal_exit ();
	}
}

/**
 * 检查issuing的投标总额，如果投标总额等于贷款申请额，就将status标记为INVITE_BIDS_SUCCEED状态
 * @param 贷款申请表的编号 $nid
 */
function _cowpro_issuing_bid_finished($success, $nid, $journal_id) {
	if ($success) {
		$loan_amounts = db_query("SELECT i.field_issuing_loan_amounts FROM {field_data_field_issuing} i WHERE i.entity_id = $nid")->fetchField();
		//watchdog('issuing debug', "_cowpro_issuing_bid_finished: nid=$nid; loan_amounts=$loan_amounts", NULL, WATCHDOG_DEBUG);
		if (_cowpro_issuing_bid_avail($nid, $loan_amounts) == 0) {
			//watchdog('issuing debug', "_cowpro_issuing_bid_finished: _cowpro_issuing_bid_avail==0", NULL, WATCHDOG_DEBUG);
			db_query("UPDATE {field_data_field_issuing} SET field_issuing_status = '" . COWPRO_ISSUING_STATUS_INVITE_BIDS_SUCCEED . "' WHERE entity_id = $nid");
			//参考 http://stackoverflow.com/questions/9870608/how-to-clear-node-custom-field-cache-in-drupal-7
			//how to clear node custom field cache in drupal 7
			cache_clear_all("field:node:$nid", 'cache_field');
			entity_get_controller('node')->resetCache(array($nid));
		}
	}
	$args = array();
	$args[] = $success;
	$args[] = $nid;
	$args[] = $journal_id;
	$hook = 'cowpro_fund_bid_finished';
	foreach (module_implements($hook) as $module) {
		$function = $module . '_' . $hook;
		if (function_exists($function)) {
			call_user_func_array($function, $args);
		}
	}
}