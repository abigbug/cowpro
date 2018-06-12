<?php

class cowpro_userpoints_txn_handler_field_operation extends views_handler_field {
  function render($values) {
  	return 'hello';
    $txn_id = $this->get_value($values);

    $query = db_select('userpoints_txn', 'p')
    ->fields('p')
    ->condition('p.txn_id', $txn_id)
    ->range(0, 1)
    ->execute();
    $transaction = $query->fetchObject();
    return userpoints_get_transaction_actions($transaction);
  }
}
