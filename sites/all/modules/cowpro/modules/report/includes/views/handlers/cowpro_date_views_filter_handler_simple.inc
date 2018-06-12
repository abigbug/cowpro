<?php
/**
 * @file
* A standard Views filter for a single date field,
* using Date API form selectors and sql handling.
*/

// @codingStandardsIgnoreStart
class cowpro_date_views_filter_handler_simple extends date_views_filter_handler_simple {

	/**
	 * Helper function to find a default value.
	 */
	function date_default_value($prefix, $options = NULL) {
		$default_date = '';
		if (empty($options)) {
			$options = $this->options;
		}
		// If this is a remembered value, use the value from the SESSION.
		if (!empty($this->options['expose']['remember'])) {
			$display_id = ($this->view->display_handler->is_defaulted('filters')) ? 'default' : $this->view->current_display;
			if (!empty($_SESSION['views'][$this->view->name][$display_id][$this->options['expose']['identifier']][$prefix])) {
				return $_SESSION['views'][$this->view->name][$display_id][$this->options['expose']['identifier']][$prefix];
			}
		}

		// This is a date that needs to be constructed from options like 'now' .
		$default_option = $prefix == 'max' ? 'today' : 'today';
		if (!empty($default_option)) {
			str_replace('now', 'today', $default_option);
			$date = date_create($default_option, date_default_timezone_object());
			//$date = $prefix == 'max' ? $date->modify('+1 day') : $date;
			$default_date = !empty($date) ? $date->format($this->format) : '';

			// The format for our filter is in ISO format, but the widget will need it in datetime format.
			$default_date = str_replace('T', ' ', $default_date);
		}
		// This a fixed date.
		else {
			$default_date = $options['value'][$prefix];
		}
		return $default_date;
	}

}
// @codingStandardsIgnoreEnd
