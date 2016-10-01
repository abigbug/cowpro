<?php
function _install_theme() {
	variable_set('theme_default', 'cowpro_p2p');
	_install_theme_modules();
	_install_theme_views();
	_install_theme_blocks();
}

function _install_theme_blocks() {
	$default_theme = variable_get('theme_default', 'cowpro_p2p');
	$admin_theme = 'seven';
	$blocks = array(
			array(
					'module' => 'views',
					'delta' => 'slider-block',
					'theme' => $default_theme,
					'status' => 1,
					'weight' => -1,
					'region' => 'header',
					'visibility' => '1',
					'pages' => '<front>',
					'title' => '<none>',
					'cache' => -1,
					//'cache' => 8,调试完毕以后，改为全局缓存
			),
			array(
					'module' => 'superfish',
					'delta' => '1',
					'theme' => $default_theme,
					'status' => 1,
					'weight' => -1,
					'region' => 'menu',
					'visibility' => '0',
					'pages' => '',
					'title' => '<none>',
					'cache' => 2,
			),
	);
	$query = db_insert('block')->fields(array('module', 'delta', 'theme', 'status', 'weight', 'region', 'visibility', 'pages', 'title', 'cache'));
	foreach ($blocks as $block) {
		$query->values($block);
	}
	$query->execute();
}

function _install_theme_modules() {
	$modules = array(
			'libraries',
			'views_slideshow',
			'flexslider',
			'flexslider_fields',
			'flexslider_views_slideshow',
			'flexslider_views',
			'jquery_update',
			'superfish',
			'tm_font_awesome',
			'tm_font_flaticon',
	); // Array of module names
	$enable_dependencies = TRUE; // Whether or not to enable dependant modules
	module_enable($modules, $enable_dependencies);

	variable_set('jquery_update_jquery_version', '1.8');
	variable_set('jquery_update_jquery_admin_version', '1.8');
	variable_set('superfish_number', 1);
	variable_set('superfish_menu_1', 'user-menu:0');
	variable_set('superfish_name_1', '');
	variable_set('superfish_slide_1', 'easeOutCubic_vertical');

	$permissions = array(
			'create slide content',
			'edit any slide content',
			'delete any slide content',
	);
	$role = user_role_load_by_name('manager');
	//user_role_grant_permissions($role->rid, $permissions);

	module_enable(array('theme_slider'));
	features_revert_module('theme_slider');

}

function _install_theme_views() {
	$view = new view();
	$view->name = 'slider';
	$view->description = '';
	$view->tag = 'default';
	$view->base_table = 'node';
	$view->human_name = 'Slider';
	$view->core = 7;
	$view->api_version = '3.0';
	$view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

	/* Display: Master */
	$handler = $view->new_display('default', 'Master', 'default');
	$handler->display->display_options['use_more_always'] = FALSE;
	$handler->display->display_options['access']['type'] = 'perm';
	$handler->display->display_options['cache']['type'] = 'none';
	$handler->display->display_options['query']['type'] = 'views_query';
	$handler->display->display_options['exposed_form']['type'] = 'basic';
	$handler->display->display_options['pager']['type'] = 'some';
	$handler->display->display_options['pager']['options']['items_per_page'] = '3';
	$handler->display->display_options['pager']['options']['offset'] = '0';
	$handler->display->display_options['style_plugin'] = 'flexslider';
	$handler->display->display_options['style_options']['captionfield'] = 'nothing';
	$handler->display->display_options['row_plugin'] = 'fields';
	/* Field: Content: Slide image */
	$handler->display->display_options['fields']['field_slide_image']['id'] = 'field_slide_image';
	$handler->display->display_options['fields']['field_slide_image']['table'] = 'field_data_field_slide_image';
	$handler->display->display_options['fields']['field_slide_image']['field'] = 'field_slide_image';
	$handler->display->display_options['fields']['field_slide_image']['label'] = '';
	$handler->display->display_options['fields']['field_slide_image']['element_label_colon'] = FALSE;
	$handler->display->display_options['fields']['field_slide_image']['click_sort_column'] = 'fid';
	$handler->display->display_options['fields']['field_slide_image']['settings'] = array(
			'image_style' => 'flexslider_full',
			'image_link' => '',
	);
	/* Field: Content: Body */
	$handler->display->display_options['fields']['body']['id'] = 'body';
	$handler->display->display_options['fields']['body']['table'] = 'field_data_body';
	$handler->display->display_options['fields']['body']['field'] = 'body';
	$handler->display->display_options['fields']['body']['label'] = '';
	$handler->display->display_options['fields']['body']['exclude'] = TRUE;
	$handler->display->display_options['fields']['body']['alter']['max_length'] = '325';
	$handler->display->display_options['fields']['body']['alter']['ellipsis'] = FALSE;
	$handler->display->display_options['fields']['body']['alter']['strip_tags'] = TRUE;
	$handler->display->display_options['fields']['body']['element_label_colon'] = FALSE;
	$handler->display->display_options['fields']['body']['type'] = 'text_summary_or_trimmed';
	$handler->display->display_options['fields']['body']['settings'] = array(
			'trim_length' => '325',
	);
	/* Field: Content: Link */
	$handler->display->display_options['fields']['view_node']['id'] = 'view_node';
	$handler->display->display_options['fields']['view_node']['table'] = 'views_entity_node';
	$handler->display->display_options['fields']['view_node']['field'] = 'view_node';
	$handler->display->display_options['fields']['view_node']['label'] = '';
	$handler->display->display_options['fields']['view_node']['exclude'] = TRUE;
	$handler->display->display_options['fields']['view_node']['element_label_colon'] = FALSE;
	$handler->display->display_options['fields']['view_node']['text'] = 'Read more';
	/* Field: Content: Title */
	$handler->display->display_options['fields']['title']['id'] = 'title';
	$handler->display->display_options['fields']['title']['table'] = 'node';
	$handler->display->display_options['fields']['title']['field'] = 'title';
	$handler->display->display_options['fields']['title']['label'] = '';
	$handler->display->display_options['fields']['title']['exclude'] = TRUE;
	$handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
	/* Field: Global: Custom text */
	$handler->display->display_options['fields']['nothing']['id'] = 'nothing';
	$handler->display->display_options['fields']['nothing']['table'] = 'views';
	$handler->display->display_options['fields']['nothing']['field'] = 'nothing';
	$handler->display->display_options['fields']['nothing']['label'] = '';
	$handler->display->display_options['fields']['nothing']['exclude'] = TRUE;
	$handler->display->display_options['fields']['nothing']['alter']['text'] = '<div class="container-12">
<div class="grid-5">
<h2>[title]</h2>
[body]
<div class="link">[view_node]</div>
</div>
</div>';
	$handler->display->display_options['fields']['nothing']['element_type'] = '0';
	$handler->display->display_options['fields']['nothing']['element_label_colon'] = FALSE;
	/* Sort criterion: Content: Post date */
	$handler->display->display_options['sorts']['created']['id'] = 'created';
	$handler->display->display_options['sorts']['created']['table'] = 'node';
	$handler->display->display_options['sorts']['created']['field'] = 'created';
	$handler->display->display_options['sorts']['created']['order'] = 'DESC';
	/* Filter criterion: Content: Published */
	$handler->display->display_options['filters']['status']['id'] = 'status';
	$handler->display->display_options['filters']['status']['table'] = 'node';
	$handler->display->display_options['filters']['status']['field'] = 'status';
	$handler->display->display_options['filters']['status']['value'] = 1;
	$handler->display->display_options['filters']['status']['group'] = 1;
	$handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
	/* Filter criterion: Content: Type */
	$handler->display->display_options['filters']['type']['id'] = 'type';
	$handler->display->display_options['filters']['type']['table'] = 'node';
	$handler->display->display_options['filters']['type']['field'] = 'type';
	$handler->display->display_options['filters']['type']['value'] = array(
			'slide' => 'slide',
	);

	/* Display: Block */
	$handler = $view->new_display('block', 'Block', 'block');

	/* Display: Attachment */
	$handler = $view->new_display('attachment', 'Attachment', 'attachment_1');
	$handler->display->display_options['defaults']['css_class'] = FALSE;
	$handler->display->display_options['css_class'] = 'flexslider-controls';
	$handler->display->display_options['pager']['type'] = 'some';
	$handler->display->display_options['pager']['options']['items_per_page'] = '3';
	$handler->display->display_options['pager']['options']['offset'] = '0';
	$handler->display->display_options['defaults']['style_plugin'] = FALSE;
	$handler->display->display_options['style_plugin'] = 'list';
	$handler->display->display_options['defaults']['style_options'] = FALSE;
	$handler->display->display_options['defaults']['row_plugin'] = FALSE;
	$handler->display->display_options['row_plugin'] = 'fields';
	$handler->display->display_options['defaults']['row_options'] = FALSE;
	$handler->display->display_options['defaults']['fields'] = FALSE;
	/* Field: Content: Nid */
	$handler->display->display_options['fields']['nid']['id'] = 'nid';
	$handler->display->display_options['fields']['nid']['table'] = 'node';
	$handler->display->display_options['fields']['nid']['field'] = 'nid';
	$handler->display->display_options['fields']['nid']['label'] = '';
	$handler->display->display_options['fields']['nid']['exclude'] = TRUE;
	$handler->display->display_options['fields']['nid']['element_label_colon'] = FALSE;
	/* Field: Content: Slide icon */
	$handler->display->display_options['fields']['field_slide_icon']['id'] = 'field_slide_icon';
	$handler->display->display_options['fields']['field_slide_icon']['table'] = 'field_data_field_slide_icon';
	$handler->display->display_options['fields']['field_slide_icon']['field'] = 'field_slide_icon';
	$handler->display->display_options['fields']['field_slide_icon']['label'] = '';
	$handler->display->display_options['fields']['field_slide_icon']['alter']['alter_text'] = TRUE;
	$handler->display->display_options['fields']['field_slide_icon']['alter']['text'] = '<a href="?q=node/[nid]">[field_slide_icon]</a>';
	$handler->display->display_options['fields']['field_slide_icon']['element_label_colon'] = FALSE;
	$handler->display->display_options['displays'] = array(
			'block' => 'block',
			'default' => 0,
	);
	$handler->display->display_options['attachment_position'] = 'after';
	$view->save();
}