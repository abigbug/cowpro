<?php
/**
 * A module-defined block content function.
 */
function _cowpro_fund_balance_contents() {
		$uid = $GLOBALS ['user']->uid;
		$msg = custodian_cowpro_fund_balance_contents($uid);
		$result = array(
				'#markup' => '<div>' . $msg . '</div>',
		);
		return $result;
}
