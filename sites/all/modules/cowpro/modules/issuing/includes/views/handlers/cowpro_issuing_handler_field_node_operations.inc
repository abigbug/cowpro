<?php
/**
 * Displays the node operations in a ctools dropbutton.
 * 提供对 node 操作的上下文菜单
 * 本项目中，在视图"合同管理"与"内容管理"中，使用了该字段
 * cowpro_issuing_handler_field_node_operations 与 cowpro_issuing_handler_field_issuing_operations
 * 在功能上有很多重叠的地方
 * 有条件的时候可以考虑重构
 * @ingroup views_field_handlers
 */
class cowpro_issuing_handler_field_node_operations extends views_handler_field_entity {

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

		$links = menu_contextual_links('node', 'node', array($issuing_id));

		// Add the destination to the links if specified.
		if ($this->options['add_destination']) {
			foreach ($links as $id => &$link) {
				$link['query'] = drupal_get_destination();
			}
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
