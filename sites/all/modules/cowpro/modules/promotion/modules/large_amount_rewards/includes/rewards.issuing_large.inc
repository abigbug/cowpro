<?php

function cowpro_large_amount_rewards_issuing_large_go_form($form, &$form_state) {
  $form['description'] = array(
    '#type' => 'markup',
    '#markup' => t('')
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => '本月大额奖励用户转账'
  );
  return $form;
}

function cowpro_large_amount_rewards_issuing_large_go_form_submit($form, &$form_state) {
  $function = 'cowpro_large_amount_rewards_issuing_large_go_batch';
  $batch = $function();
  batch_set($batch);
}

function cowpro_large_amount_rewards_issuing_large_go_batch() {
  $list = db_query("SELECT id,uid,rewards_amount as amount FROM {cowpro_rewards_issuing_large} WHERE rewards_date = DATE_FORMAT( CURDATE( ) , '%Y%m' ) AND status=0")->fetchAll();
  $operations = array();
  $i = 0;
  if ($list) {
    foreach ($list as $row) {
      $i++;
      $operations[] = array(
        'cowpro_large_amount_rewards_issuing_large_op_user',
        array(
          $row,
          t('(用户ID @operation)', array(
            '@operation' => $row->uid
          ))
        )
      );
    }
  }
  drupal_set_message(t('生成用户余额，共  @num 项', array(
    '@num' => $i
  )));
  $batch = array(
    'operations' => $operations,
    'finished' => 'cowpro_large_amount_rewards_issuing_large_finished',
    'file' => drupal_get_path('module', 'cowpro_large_amount_rewards') . '/includes/rewards.issuing_large.inc'
  );
  return $batch;
}

function cowpro_large_amount_rewards_issuing_large_op_user($obj, $operation_details, &$context) {
  sleep(1);
  $result = cowpro_fund_internal_trans_data($uid_from, $obj->uid, $obj->amount, "大额投标奖励");
  if ($result['success']) {
    db_update('cowpro_rewards_issuing_large')->fields(array(
      'status' => '1'
    ))->condition('id', $obj->id)->condition('uid', $obj->uid)->execute();
  }
}

function cowpro_large_amount_rewards_issuing_large_finished($success, $results, $operations) {
  if ($success) {
    global $base_url;
    drupal_set_message('批量转账成功');
    drupal_goto($base_url . "/cowpro_issuing_large");
  }
  else {
    $error_operation = reset($operations);
    drupal_set_message(t('An error occurred while processing @operation with arguments : @args', array(
      '@operation' => $error_operation[0],
      '@args' => print_r($error_operation[0], TRUE)
    )), 'error');
  }
}

