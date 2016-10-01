<?php

/**
 * Filter by issuing status.
 */
class cowpro_issuing_handler_filter_issuing extends views_handler_filter_in_operator {
  function get_value_options() {
    if (!isset($this->value_options)) {
      $this->value_title = '贷款进度状态';
      $status_array = array(
      		0 => '贷款人发标，末审核',
      		1 => '审核通过',
      		2 => '流标',
      		3 => '满标，等待放款',
      		4 => '等待还款',
      		5 => '还款完毕',
      );
      foreach ($status_array as $status => $info) {
        $options[$status] = $info;
      }
      $this->value_options = $options;
    }
  }
}
