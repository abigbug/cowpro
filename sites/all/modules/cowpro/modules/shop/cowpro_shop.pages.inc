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
}

/**
 * Processes variables for cowpro-commerce-list.tpl.php.
 *
 * @see cowpro-commerce-list.tpl.php
 */
function template_preprocess_cowpro_commerce_list(&$variables) {
	$a=$variables;
}