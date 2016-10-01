<?php
function _cowpro_issuing_get_assigning_schedules($issuing_id, $uid) {
	$query = new EntityFieldQuery ();
	$query->entityCondition ( 'entity_type', 'cowpro_repayment_schedule' )->propertyCondition ( 'issuing_id', $issuing_id )->propertyCondition ( 'receiver_uid', $uid )->propertyCondition ( 'status', 'ASSIGNABLE' )->propertyOrderBy ( 'deadline', 'ASC' );
	$result = $query->execute ();
	$ids = array_keys ( $result ['cowpro_repayment_schedule'] );
	$repayment_schedules = entity_load ( 'cowpro_repayment_schedule', $ids );
	return $repayment_schedules;
}

function _cowpro_issuing_get_creditor_assignment_amount($repayment) {
	$data = NULL;
	$serial = -1;
	$result = 0;
	foreach ($repayment->data as $key => $value) {
		if ($value['operate'] === 'creditor_assignment') {
			if ($serial < $value['serial']) {
				$serial = $value['serial'];
				$data = $value;
			}
		}
	}
	if ($data) {
		$result = $data['amount'];
	}
	return $result;
}

