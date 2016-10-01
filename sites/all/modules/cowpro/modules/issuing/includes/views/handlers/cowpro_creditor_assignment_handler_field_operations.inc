<?php
/**
 * Displays the creditor assignment operations in a ctools dropbutton.
 *
 * @ingroup views_field_handlers
 */
class cowpro_creditor_assignment_handler_field_operations extends views_handler_field_entity {

	function render($values) {
		$issuing_id = $this->get_value($values, 'nid');
		$uid = $values->users_cowpro_repayment_schedule_uid;

		$link1 = menu_contextual_links('cowpro_issuing', 'creditor_assignment', array($issuing_id, $uid, 'interrupt'));
		$link2 = menu_contextual_links('cowpro_issuing', 'creditor_assignment', array($issuing_id, $uid, 'buy'));
		$links = array_merge($link1, $link2);
		foreach ($links as $id => &$link) {
				$link['attributes']['class']=array('ctools-use-modal');
		}

		// Add the quick-link link which opens the megarow.
		$quick_link2['repayment-schedule'] = menu_get_item("issuing/$issuing_id/repayment_schedule");
		if ($quick_link2['repayment-schedule']['access']) {
			$quick_link2['repayment-schedule']['title'] = '还款详情';
			$quick_link2['repayment-schedule']['attributes']['class'] = array('views-megarow-open');
			$links = array_merge($quick_link2, $links);
		}
		$quick_link1['quick-view'] = menu_get_item("issuing/$issuing_id/brief");
		if ($quick_link1['quick-view']['access']) {
			$quick_link1['quick-view']['title'] = '贷款速览';
			$quick_link1['quick-view']['attributes']['class'] = array('views-megarow-open');
			$links = array_merge($quick_link1, $links);
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
