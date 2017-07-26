<?php
/**
 * Displays the issuing operations in a ctools dropbutton.
 *
 * @ingroup views_field_handlers
 */
class cowpro_issuing_handler_field_issuing_operations extends views_handler_field_entity {

	function option_definition() {
		$options = parent::option_definition();
		$options['add_quick_edit'] = TRUE;
		$options['add_destination'] = TRUE;

		return $options;
	}

	function options_form(&$form, &$form_state) {
		parent::options_form($form, $form_state);

		/*
		$form['add_quick_edit'] = array(
				'#type' => 'checkbox',
				'#title' => t('Add the quick edit link for product displays.'),
				'#default_value' => $this->options['add_quick_edit'],
		);
		*/
		$form['add_destination'] = array(
				'#type' => 'checkbox',
				'#title' => t('Add a destination parameter to operations links so users return to this View on form submission.'),
				'#default_value' => $this->options['add_destination'],
		);
	}

	function render($values) {
		$issuing_id = $this->get_value($values, 'nid');

		$links1 = menu_contextual_links('node', 'node', array($issuing_id));
		$links2 = menu_contextual_links('cowpro_issuing', 'issuing', array($issuing_id));
		foreach ($links2 as $id => &$link) {
				$link['attributes']['class']=array('ctools-use-modal');
		}
		$links = array_merge($links1, $links2);

		// Add the destination to the links if specified.
		if ($this->options['add_destination']) {
			foreach ($links as $id => &$link) {
				$link['query'] = drupal_get_destination();
			}
		}

		// Add the quick-link link which opens the megarow.
		$quick_link2['repayment-schedule'] = menu_get_item("issuing/$issuing_id/repayment_schedule");
		if ($quick_link2['repayment-schedule']['access']) {
			$quick_link2['repayment-schedule']['title'] = '还款详情';
			$quick_link2['repayment-schedule']['attributes']['class'] = array('ctools-use-modal');
			$links = array_merge($quick_link2, $links);
		}

		/*
		$quick_link1['quick-view'] = menu_get_item("issuing/$issuing_id/brief");
		if ($quick_link1['quick-view']['access']) {
			$quick_link1['quick-view']['title'] = '贷款详情';
			$quick_link1['quick-view']['attributes']['class'] = array('views-megarow-open');
			$links = array_merge($quick_link1, $links);
		}
		*/

		$quick_link1['quick-view'] = menu_get_item("issuing/$issuing_id");
		if ($quick_link1['quick-view']['access']) {
			$quick_link1['quick-view']['title'] = '贷款详情';
			$links = array_merge($quick_link1, $links);
		}

		ctools_include('modal');
		ctools_include('ajax');
		ctools_modal_add_js();

		$node = node_load($issuing_id);
		include_once drupal_get_path('module', 'cowpro_issuing') . '/includes/cowpro_issuing_status.inc';
		switch ($node->field_issuing[LANGUAGE_NONE][0]['status']) {
		case COWPRO_ISSUING_STATUS_UNAUDITED :
			$status_class = 'default';
			break;
		case COWPRO_ISSUING_STATUS_AUDITED :
			$status_class = 'default';
			break;
		case COWPRO_ISSUING_STATUS_INVITE_BIDS_START :
			$status_class = 'default';
			break;
		case COWPRO_ISSUING_STATUS_INVITE_BIDS_FAILED :
			$status_class = 'default';
			break;
		case COWPRO_ISSUING_STATUS_INVITE_BIDS_SUCCEED :
			$status_class = 'yellow';
			break;
		case COWPRO_ISSUING_STATUS_REPAYMENT :
			$status_class = 'green';
			break;
		case COWPRO_ISSUING_STATUS_FINISHED :
			$status_class = 'default';
		}


		$element = array(
				'#markup' => theme('links__ctools_dropbutton', array('links' => $links, 'attributes' => array('class' => array('links', 'inline', $status_class)))),
		);

		return $element;
	}
}
