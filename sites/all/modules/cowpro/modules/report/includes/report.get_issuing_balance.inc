<?php

function cowpro_report_issuing_balance_query_form($form, &$form_state) {
  $form['description'] = array(
    '#type' => 'markup',
    '#markup' => t('')
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => '查询标的台账账号'
  );
  return $form;
}

function cowpro_report_issuing_balance_query_form_submit($form, &$form_state) {
  $function = 'cowpro_report_issuing_balance_query_batch';
  $batch = $function();
  batch_set($batch);
}

function cowpro_report_issuing_balance_query_batch() {
  $list = db_query("SELECT issuing_object_accno FROM {jiupaipay_issuing_accno}")->fetchAll();
  $operations = array();
  $i = 0;
  if ($list) {
    foreach ($list as $row) {
      $i++;
      $operations[] = array(
        'cowpro_report_issuing_balance_query_do',
        array(
          $row->issuing_object_accno,
          t('(用户ID @operation)', array(
            '@operation' => $row->issuing_object_accno
          ))
        )
      );
    }
  }
  drupal_set_message(t('生成台账账号，共  @num 项', array(
    '@num' => $i
  )));
  $batch = array(
    'operations' => $operations,
    'finished' => 'cowpro_report_issuing_balance_query_finished',
    'file' => drupal_get_path('module', 'cowpro_report') . '/includes/report.get_issuing_balance.inc'
  );
  return $batch;
}

function cowpro_report_issuing_balance_query_do($obj, $operation_details, &$context) {
  $module_path = drupal_get_path('module', 'jiupaipay');
  include $module_path . '/includes/jiupaipay.ledger_account.inc';
  sleep(1);
  $result = jiupaipay_ledger_account($obj);
  file_put_contents("issuing_account_amount.text", $obj . "=>" . $result . "\r\n", FILE_APPEND);
}

function cowpro_report_issuing_balance_query_finished($success, $results, $operations) {
  if ($success) {
    global $base_url;
    drupal_set_message('标的台账查询完毕');
  }
  else {
    $error_operation = reset($operations);
    drupal_set_message(t('An error occurred while processing @operation with arguments : @args', array(
      '@operation' => $error_operation[0],
      '@args' => print_r($error_operation[0], TRUE)
    )), 'error');
  }
}

