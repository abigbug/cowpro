<?php
/**
 * @file
 * cowpro_rules.rules_defaults.inc
 */

/**
 * Implements hook_default_rules_configuration().
 */
function cowpro_rules_default_rules_configuration() {
  $items = array();
  $items['cowpro_rules_assign_debtor_role_to_user'] = entity_import('rules_config', '{ "cowpro_rules_assign_debtor_role_to_user" : {
      "LABEL" : "assign debtor role to user",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "TAGS" : [
        "\\u5728\\u7528\\u6237\\u6ce8\\u518c\\u7684\\u65f6\\u5019\\u5206\\u914d\\u501f\\u6b3e\\u4eba(debtor)\\u89d2\\u8272"
      ],
      "REQUIRES" : [ "php", "rules" ],
      "ON" : { "user_insert" : [] },
      "IF" : [
        { "php_eval" : { "code" : "$path = isset($_GET[\\u0027q\\u0027]) ? $_GET[\\u0027q\\u0027] : \\u0027\\u003Cfront\\u003E\\u0027;\\r\\nreturn $path == \\u0027user\\/register\\/debtor\\u0027;" } }
      ],
      "DO" : [
        { "user_add_role" : { "account" : [ "account" ], "roles" : { "value" : { "5" : "5" } } } }
      ]
    }
  }');
  $items['rules_assign_default_role_to_user'] = entity_import('rules_config', '{ "rules_assign_default_role_to_user" : {
      "LABEL" : "assign lender role to user",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "TAGS" : [
        "\\u5728\\u7528\\u6237\\u6ce8\\u518c\\u7684\\u65f6\\u5019\\u5206\\u914d\\u51fa\\u501f\\u4eba(lender)\\u89d2\\u8272"
      ],
      "REQUIRES" : [ "php", "rules" ],
      "ON" : { "user_insert" : [] },
      "IF" : [
        { "php_eval" : { "code" : "$path = isset($_GET[\\u0027q\\u0027]) ? $_GET[\\u0027q\\u0027] : \\u0027\\u003Cfront\\u003E\\u0027;\\r\\nreturn $path == \\u0027user\\/register\\u0027;" } }
      ],
      "DO" : [
        { "user_add_role" : { "account" : [ "account" ], "roles" : { "value" : { "4" : "4" } } } }
      ]
    }
  }');
  $items['rules_cowpro_fund_bid_finished'] = entity_import('rules_config', '{ "rules_cowpro_fund_bid_finished" : {
      "LABEL" : "cowpro fund bid finished",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "TAGS" : [ "cowpro" ],
      "REQUIRES" : [ "cowpro_message" ],
      "ON" : { "cowpro_fund_bid_finished" : [] },
      "DO" : [ { "cowpro_fund_bid_finished" : [] } ]
    }
  }');
  $items['rules_cowpro_fund_buy_creditor_assignment_finished'] = entity_import('rules_config', '{ "rules_cowpro_fund_buy_creditor_assignment_finished" : {
      "LABEL" : "cowpro fund buy creditor assignment finished",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "TAGS" : [ "cowpro" ],
      "REQUIRES" : [ "cowpro_message" ],
      "ON" : { "cowpro_fund_buy_creditor_assignment_finished" : [] },
      "DO" : [ { "cowpro_fund_buy_creditor_assignment_finished" : [] } ]
    }
  }');
  $items['rules_cowpro_fund_make_loans_to_finished'] = entity_import('rules_config', '{ "rules_cowpro_fund_make_loans_to_finished" : {
      "LABEL" : "cowpro fund make loans to finished",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "TAGS" : [ "cowpro" ],
      "REQUIRES" : [ "cowpro_message" ],
      "ON" : { "cowpro_fund_make_loans_to_finished" : [] },
      "DO" : [ { "cowpro_fund_make_loans_to_finished" : [] } ]
    }
  }');
  $items['rules_cowpro_fund_repayment_finished'] = entity_import('rules_config', '{ "rules_cowpro_fund_repayment_finished" : {
      "LABEL" : "cowpro fund repayment finished",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "TAGS" : [ "cowpro" ],
      "REQUIRES" : [ "cowpro_message" ],
      "ON" : { "cowpro_fund_repayment_finished" : [] },
      "DO" : [ { "cowpro_fund_repayment_finished" : [] } ]
    }
  }');
  $items['rules_cowpro_fund_topup_finished'] = entity_import('rules_config', '{ "rules_cowpro_fund_topup_finished" : {
      "LABEL" : "cowpro fund topup finished",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "TAGS" : [ "cowpro" ],
      "REQUIRES" : [ "cowpro_message" ],
      "ON" : { "cowpro_fund_topup_finished" : [] },
      "DO" : [ { "cowpro_fund_topup_finished" : [] } ]
    }
  }');
  $items['rules_cowpro_fund_withdraw_finished'] = entity_import('rules_config', '{ "rules_cowpro_fund_withdraw_finished" : {
      "LABEL" : "cowpro fund withdraw finished",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "TAGS" : [ "cowpro" ],
      "REQUIRES" : [ "cowpro_message" ],
      "ON" : { "cowpro_fund_withdraw_finished" : [] },
      "DO" : [ { "cowpro_fund_withdraw_finished" : [] } ]
    }
  }');
  return $items;
}
