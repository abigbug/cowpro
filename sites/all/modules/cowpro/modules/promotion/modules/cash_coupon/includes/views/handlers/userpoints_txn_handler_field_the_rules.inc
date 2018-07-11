<?php
class userpoints_txn_handler_field_the_rules extends views_handler_field {
    function render($values) {
        $txn_points = $values->userpoints_txn_points;
        $txn_reference = $values->userpoints_txn_reference;    //活动场景，区分活动

        //调用代金券使用规则判断
        $the_rules=cowpro_cash_coupon_the_rules_show($txn_points,$txn_reference);
        return $the_rules;
    }
}
