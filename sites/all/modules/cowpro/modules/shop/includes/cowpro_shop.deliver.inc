<?php
function _cowpro_shop_deliver_action(&$entities, $context = array(), $status) {
	foreach ($entities as $entity) {
		$deliver = entity_load_single('cowpro_shop_deliver', $entity->deliver_id);
		$deliver->status = $status;
		entity_get_controller('cowpro_shop_deliver')->save($deliver);
	}
}