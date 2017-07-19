<?php

/**
 * Processes variables for cowpro-commerce-item.tpl.php.
 *
 * @see cowpro-commerce-item.tpl.php
 */
function template_preprocess_cowpro_commerce_item(&$variables) {
	global $base_url;

	$variables['title'] = $variables['item']['title'];
	$variables['status'] = $variables['item']['status'];
	$variables['promote'] = $variables['item']['promote'];
	$variables['nid'] = $variables['item']['nid'];
	$variables['type'] = $variables['item']['type'];
	$variables['body'] = $variables['item']['body']['und'][0]['value'];
	$variables['products'] = array();
	foreach ($variables['item']['products'] as $product) {
		$p = array();
		$p['sku'] = $product['sku'];
		$p['title'] = $product['title'];
		$p['product_id'] = $product['product_id'];
		$p['type'] = $product['type'];
		$p['price'] = intval(floor($product['commerce_price']['und'][0]['amount']/100));
		$p['buy_link'] = $base_url . '/shop/buy/' . $variables['nid'] . '/' . $p['product_id'];
		$images = array();
		foreach ($product['field_images']['und'] as $img) {
			$images[] = $img;
		}
		$p['images'] = $images;
		$variables['products'][] = $p;
	}
	$variables['first_product'] = reset($variables['products']);
}

/**
 * Processes variables for cowpro-commerce-list-item.tpl.php.
 *
 * @see cowpro-commerce-item.tpl.php
 */
function template_preprocess_cowpro_commerce_list_item(&$variables) {
}

function _cowpro_shop_theme_list_item($item) {
	$output = theme('cowpro_commerce_list_item', array('item' => $item));;
	return $output;
}

/**
 * Processes variables for cowpro-commerce-list.tpl.php.
 *
 * @see cowpro-commerce-list.tpl.php
 */
function template_preprocess_cowpro_commerce_list(&$vars) {
	$vars['rows'] = array();
	foreach ($vars['list'] as $item) {
		$vars['rows'][$item['nid']] = _cowpro_shop_theme_list_item($item);
	}

	$class = explode(' ', 'all-products');
	$class = array_map('views_clean_css_identifier', $class);

	$wrapper_class = explode(' ', 'item-list');
	$wrapper_class = array_map('views_clean_css_identifier', $wrapper_class);

	$vars['class'] = implode(' ', $class);
	$vars['wrapper_class'] = implode(' ', $wrapper_class);
	$vars['wrapper_prefix'] = '';
	$vars['wrapper_suffix'] = '';
	$vars['list_type_prefix'] = '<ul>';
	$vars['list_type_suffix'] = '</ul>';
	if ($vars['wrapper_class']) {
		$vars['wrapper_prefix'] = '<div class="' . $vars['wrapper_class'] . '">';
		$vars['wrapper_suffix'] = '</div>';
	}

	if ($vars['class']) {
		$vars['list_type_prefix'] = '<ul' . ' class="' . $vars['class'] . '">';
	}
	template_preprocess_cowpro_commerce_unformatted($vars);
}

/**
 * Display the simple view of rows one after another
 */
function template_preprocess_cowpro_commerce_unformatted(&$vars) {
	$rows = $vars['rows'];
	$vars['classes_array'] = array();
	$vars['classes'] = array();
	$default_row_class = TRUE;
	$row_class_special = TRUE;
	// Set up striping values.
	$count = 0;
	$max = count($rows);
	foreach ($rows as $id => $row) {
		$count++;
		if ($default_row_class) {
			$vars['classes'][$id][] = 'views-row';
			$vars['classes'][$id][] = 'views-row-' . $count;
		}
		if ($row_class_special) {
			$vars['classes'][$id][] = 'views-row-' . ($count % 2 ? 'odd' : 'even');
			if ($count == 1) {
				$vars['classes'][$id][] = 'views-row-first';
			}
			if ($count == $max) {
				$vars['classes'][$id][] = 'views-row-last';
			}
		}

		// Flatten the classes to a string for each row for the template file.
		$vars['classes_array'][$id] = isset($vars['classes'][$id]) ? implode(' ', $vars['classes'][$id]) : '';
	}
}
