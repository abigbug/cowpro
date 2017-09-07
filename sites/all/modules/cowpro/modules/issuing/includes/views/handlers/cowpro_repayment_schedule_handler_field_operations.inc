<?php
/**
 * Displays the issuing operations in a ctools dropbutton.
 *
 * @ingroup views_field_handlers
 */
class cowpro_repayment_schedule_handler_field_operations extends views_handler_field_entity {
	function render($values) {
		$issuing_id = $this->get_value($values, 'issuing_id');
		$uid = $values->cowpro_repayment_schedule_receiver_uid;

		$links = array();

		// Add the quick-link link which opens the megarow.
		$quick_link['repayment-schedule'] = menu_get_item("issuing/$issuing_id/$uid/repayment_schedule");
		if ($quick_link['repayment-schedule']['access']) {
			$quick_link['repayment-schedule']['title'] = '还款详情';
			$quick_link['repayment-schedule']['attributes']['class'] = array('ctools-use-modal');
			$links = array_merge($quick_link, $links);
		}

		ctools_include('modal');
		ctools_include('ajax');
		ctools_modal_add_js();

		$element = array(
				'#markup' => theme('links__ctools_dropbutton', array('links' => $links, 'attributes' => array('class' => array('links', 'inline')))),
		);

		return $element;
	}
}
