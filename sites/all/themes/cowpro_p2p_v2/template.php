<?php

/**
 * @file
 * Contains theme override functions and process & preprocess functions for cowpro_p2p_v2
 */

// Auto-rebuild the theme registry during theme development.
if ( theme_get_setting( 'cowpro_p2p_v2_clear_registry' ) ) {
	// Rebuild .info data.
	system_rebuild_theme_data();
	// Rebuild theme registry.
	drupal_theme_rebuild();
}

/**
 * Implements template_html_head_alter();
 *
 * Changes the default meta content-type tag to the shorter HTML5 version
 */
function cowpro_p2p_v2_html_head_alter( &$head_elements ) {
	$head_elements['system_meta_content_type']['#attributes'] = array(
		'charset'	=> 'utf-8'
	);
}

/**
 * Implements template_proprocess_search_block_form().
 *
 * Changes the search form to use the HTML5 "search" input attribute
 */
function cowpro_p2p_v2_preprocess_search_block_form( &$vars ) {
	$vars['search_form'] = str_replace( 'type="text"', 'type="search"', $vars['search_form'] );
}

/**
 * Implements template_preprocess().
 */
function cowpro_p2p_v2_preprocess( &$vars, $hook ) {
	$vars['cowpro_p2p_v2_path'] = base_path() . path_to_theme();

	$count[ $hook ] = isset( $count[ $hook ] ) && is_int( $count[ $hook ] ) ? $count[ $hook ] : 1;
	$vars['zebra_hook'][ $hook ] = ( $count[ $hook ] % 2) ? 'odd' : 'even';
	$vars['id_hook'][ $hook ] = $count[ $hook ]++;
}

/**
 * Implements template_preprocess_html().
 */
function cowpro_p2p_v2_preprocess_html( &$vars ) {
	$vars['doctype'] = _cowpro_p2p_v2_doctype();
	$vars['rdf'] = _cowpro_p2p_v2_rdf( $vars );

	// Since menu is rendered in preprocess_page we need to detect it here to add body classes
	$has_main_menu = theme_get_setting( 'toggle_main_menu' );
	$has_secondary_menu = theme_get_setting( 'toggle_secondary_menu' );

	/* Add extra classes to body for more flexible theming */

	if ( $has_main_menu or $has_secondary_menu ) {
		$vars['classes_array'][] = 'with-navigation';
	}

	if ( $has_secondary_menu ) {
		$vars['classes_array'][] = 'with-subnav';
	}

	if ( !empty( $vars['page']['featured'] ) ) {
		$vars['classes_array'][] = 'featured';
	}

	if ( !empty( $vars['page']['triptych_first'] )
		|| !empty( $vars['page']['triptych_middle'] )
		|| !empty( $vars['page']['triptych_last'] ) ) {
		$vars['classes_array'][] = 'triptych';
	}

	if ( !empty( $vars['page']['footer_firstcolumn'] )
		|| !empty( $vars['page']['footer_secondcolumn'] )
		|| !empty( $vars['page']['footer_thirdcolumn'] )
		|| !empty( $vars['page']['footer_fourthcolumn'] ) ) {
		$vars['classes_array'][] = 'footer-columns';
	}

	if ( $vars['is_admin'] ) {
		$vars['classes_array'][] = 'admin';
	}

	if ( !$vars['is_front'] ) {
		// Add unique classes for each page and website section
		$path = drupal_get_path_alias( $_GET['q'] );
		$temp = explode( '/', $path, 2 );
		$section = array_shift( $temp );
		$page_name = array_shift( $temp );

		if ( isset( $page_name ) ) {
			$vars['classes_array'][] = cowpro_p2p_v2_id_safe( 'page-' . $page_name );
		}

		$vars['classes_array'][] = cowpro_p2p_v2_id_safe( 'section-' . $section );

		// add template suggestions
		$vars['theme_hook_suggestions'][] = "page__section__" . $section;
		$vars['theme_hook_suggestions'][] = "page__" . $page_name;

		if ( arg(0 ) == 'node' ) {
			if ( arg(1) == 'add' ) {
				if ( $section == 'node' ) {
					array_pop( $vars['classes_array'] ); // Remove 'section-node'
				}
				$body_classes[] = 'section-node-add'; // Add 'section-node-add'
			} elseif ( is_numeric( arg(1) ) && ( arg(2) == 'edit' || arg(2) == 'delete' ) ) {
				if ( $section == 'node' ) {
					array_pop( $vars['classes_array'] ); // Remove 'section-node'
				}
				$body_classes[] = 'section-node-' . arg(2); // Add 'section-node-edit' or 'section-node-delete'
			}
		}
	}

	// Blog title
	$d = drupal_get_destination();
	if ( ( $d['destination'] == 'blog' ) && ( theme_get_setting( 'cowpro_p2p_v2_blog_title' ) != "" ) ) {
		$vars['title'] = theme_get_setting( 'cowpro_p2p_v2_blog_title' );
		$vars['head_title'] = theme_get_setting( 'cowpro_p2p_v2_blog_title' );
	}
}

/**
 * Implements template_preprocess_page().
 */
function cowpro_p2p_v2_preprocess_page( &$vars ) {
	if ( isset( $vars['node_title'] ) ) {
		$vars['title'] = $vars['node_title'];
	}

	// Adding classes wether #navigation is here or not
	if ( !empty( $vars['main_menu'] ) or !empty( $vars['sub_menu'] ) ) {
		$vars['classes_array'][] = 'with-navigation';
	}

	if ( !empty( $vars['secondary_menu'] ) ) {
		$vars['classes_array'][] = 'with-subnav';
	}

	// Since the title and the shortcut link are both block level elements,
	// positioning them next to each other is much simpler with a wrapper div.
	if ( !empty( $vars['title_suffix']['add_or_remove_shortcut'] ) && $vars['title'] ) {
		// Add a wrapper div using the title_prefix and title_suffix render elements.
		$vars['title_prefix']['shortcut_wrapper'] = array(
			'#markup' => '<div class="shortcut-wrapper clearfix">',
			'#weight' => 100,
		);
		$vars['title_suffix']['shortcut_wrapper'] = array(
			'#markup' => '</div>',
			'#weight' => -99,
		);
		// Make sure the shortcut link is the first item in title_suffix.
		$vars['title_suffix']['add_or_remove_shortcut']['#weight'] = -100;
	}

	// Remove message from front page
	if( drupal_is_front_page() ) {
		unset( $vars['page']['content']['system_main']['default_message'] );
	}

	// Blog title
	$d = drupal_get_destination();
	if ( ( $d['destination'] == 'blog' ) && ( theme_get_setting( 'cowpro_p2p_v2_blog_title' ) != "" ) ) {
		$vars['title'] = theme_get_setting( 'cowpro_p2p_v2_blog_title' );
		$vars['head_title'] = theme_get_setting( 'cowpro_p2p_v2_blog_title' );
	}
}

/**
 * Implements template_preprocess_maintenance_page().
 */
function cowpro_p2p_v2_preprocess_maintenance_page( &$vars ) {
	// Manually include these as they're not available outside template_preprocess_page().
	$vars['rdf_namespaces'] = drupal_get_rdf_namespaces();
	$vars['grddl_profile'] = '//www.w3.org/1999/xhtml/vocab';

	$vars['doctype'] = _cowpro_p2p_v2_doctype();
	$vars['rdf'] = _cowpro_p2p_v2_rdf( $vars );

	if ( !$vars['db_is_active'] ) {
		unset( $vars['site_name'] );
	}

	drupal_add_css( drupal_get_path( 'theme', 'cowpro_p2p_v2' ) . '/css/maintenance-page.css' );
}

/**
 * Implements template_preprocess_node().
 *
 * Adds extra classes to node container for advanced theming
 */
function cowpro_p2p_v2_preprocess_node( &$vars ) {
	// Striping class
	$vars['classes_array'][] = 'node-' . $vars['zebra'];

	// Node is published
	$vars['classes_array'][] = ( $vars['status'] ) ? 'published' : 'unpublished';

	// Node has comments?
	$vars['classes_array'][] = ( $vars['comment'] ) ? 'with-comments' : 'no-comments';

	if ( $vars['sticky'] ) {
		$vars['classes_array'][] = 'sticky'; // Node is sticky
	}

	if ( $vars['promote'] ) {
		$vars['classes_array'][] = 'promote'; // Node is promoted to front page
	}

	if ( $vars['teaser'] ) {
		$vars['classes_array'][] = 'node-teaser'; // Node is displayed as teaser.
	}

	if ( $vars['uid'] && $vars['uid'] === $GLOBALS['user']->uid ) {
		$classes[] = 'node-mine'; // Node is authored by current user.
	}

	$vars['submitted'] = t( '!username', array( '!username' => $vars['name'] ) );
	$vars['submitted_date'] = t( '!datetime', array( '!datetime' => $vars['date'] ) );
	$vars['submitted_pubdate'] = format_date( $vars['created'], 'custom', 'Y-m-d\TH:i:s' );

	if ( $vars['view_mode'] == 'full' && node_is_page( $vars['node'] ) ) {
		$vars['classes_array'][] = 'node-full';
	}
}

/**
 * Implements template_preprocess_block().
 */
function cowpro_p2p_v2_preprocess_block( &$vars, $hook ) {
	// Add a striping class.
	$vars['classes_array'][] = 'block-' . $vars['zebra'];

	// In the header region visually hide block titles.
 /*if ( $vars['block']->region == 'header' ) {
		$vars['title_attributes_array']['class'][] = 'element-invisible';
	}*/
}

/**
 * Implements theme_menu_tree().
 */
function cowpro_p2p_v2_menu_tree( $vars ) {
	return '<ul class="menu clearfix">' . $vars['tree'] . '</ul>';
}

/**
 * Implements theme_field__field_type().
 */
function cowpro_p2p_v2_field__taxonomy_term_reference( $vars ) {
	$output = '';

	// Render the label, if it's not hidden.
	if ( !$vars['label_hidden'] ) {
		$output .= '<h3 class="field-label">' . $vars['label'] . ': </h3>';
	}

	// Render the items.
	$output .= ( $vars['element']['#label_display'] == 'inline' ) ? '<ul class="links inline">' : '<ul class="links">';
	foreach ( $vars['items'] as $delta => $item ) {
		$output .= '<li class="taxonomy-term-reference-' . $delta . '"' . $vars['item_attributes'][ $delta ] . '>' . drupal_render( $item ) . '</li>';
	}
	$output .= '</ul>';

	// Render the top-level DIV.
	$output = '<div class="' . $vars['classes'] . ( !in_array( 'clearfix', $vars['classes_array'] ) ? ' clearfix' : '' ) . '">' . $output . '</div>';

	return $output;
}

/**
 *	Return a themed breadcrumb trail
 */
function cowpro_p2p_v2_breadcrumb( $vars ) {
	$breadcrumb = isset( $vars['breadcrumb'] ) ? $vars['breadcrumb'] : array();

	$condition = theme_get_setting( 'cowpro_p2p_v2_breadcrumb_hideonlyfront' ) ? count( $breadcrumb ) > 1
			: !empty( $breadcrumb );
	$separator = theme_get_setting( 'cowpro_p2p_v2_breadcrumb_separator' );

	if ( theme_get_setting( 'cowpro_p2p_v2_breadcrumb_showtitle' ) ) {
		$title = drupal_get_title();
		if ( !empty( $title ) ) {
			$condition = true;
			$breadcrumb[] = $title;
		}
	}

	if ( $condition ) {
		// Provide a navigational heading to give context for breadcrumb links to screen-reader users.
		// Make the heading invisible with .element-invisible.
		$output = '<h2 class="element-invisible">' . t( 'You are here' ) . '</h2>';
		$output .= implode( $separator, $breadcrumb );
		return $output;
	}
}


/**
 * Determine whether to show floating tabs
 *
 * @return bool
 */
function cowpro_p2p_v2_tabs_float() {
	$float = (bool) theme_get_setting( 'cowpro_p2p_v2_tabs_float' );
	$float_node = (bool) theme_get_setting( 'cowpro_p2p_v2_tabs_node' );
	$is_node = ( arg(0) === 'node' && is_numeric( arg(1) ) );

	if ( $float ) {
		return ( $float_node ) ? $is_node : TRUE;
	}

	return FALSE;
}

/*
 * 	Converts a string to a suitable html ID attribute.
 *	Taken from "basic"
 *
 * 	 http://www.w3.org/TR/html4/struct/global.html#h-7.5.2 specifies what makes a
 * 	 valid ID attribute in HTML. This function:
 *
 * 	- Ensure an ID starts with an alpha character by optionally adding an 'n'.
 * 	- Replaces any character except A-Z, numbers, and underscores with dashes.
 * 	- Converts entire string to lowercase.
 *
 * 	@param $string
 * 		The string
 * 	@return
 * 		The converted string
 */

function cowpro_p2p_v2_id_safe( $string ) {
	// Strip accents
	$accents = '/&([A-Za-z]{1,2})(tilde|grave|acute|circ|cedil|uml|lig);/';
	$string = preg_replace( $accents, '$1', htmlentities( utf8_decode( $string ) ) );
	// Replace with dashes anything that isn't A-Z, numbers, dashes, or underscores.
	$string = strtolower( preg_replace( '/[^a-zA-Z0-9_-]+/', '-', $string ) );
	// If the first character is not a-z, add 'n' in front.
	if ( !ctype_lower( $string{0} ) ) { // Don't use ctype_alpha since its locale aware.
		$string = 'id' . $string;
	}
	return $string;
}

/**
 * Generate doctype for templates
 */
function _cowpro_p2p_v2_doctype() {
	return ( module_exists( 'rdf' ) ) ? '<!DOCTYPE html PUBLIC "-//W3C//DTD HTML+RDFa 1.1//EN"' . "\n" . '"//www.w3.org/MarkUp/DTD/xhtml-rdfa-1.dtd">' : '<!DOCTYPE html>' . "\n";
}

/**
 * Generate RDF object for templates
 *
 * Uses RDFa attributes if the RDF module is enabled
 * Lifted from Adaptivetheme for D7, full credit to Jeff Burnz
 * ref: http://drupal.org/node/887600
 *
 * @param array $vars
 */
function _cowpro_p2p_v2_rdf( $vars ) {
	$rdf = new stdClass();

	if ( module_exists( 'rdf' ) ) {
		$rdf->version = 'version="HTML+RDFa 1.1"';
		$rdf->namespaces = $vars['rdf_namespaces'];
		$rdf->profile = ' profile="' . $vars['grddl_profile'] . '"';
	} else {
		$rdf->version = '';
		$rdf->namespaces = '';
		$rdf->profile = '';
	}

	return $rdf;
}

/**
 * Generate the HTML output for a menu link and submenu.
 *
 * @param $vars
 *	 An associative array containing:
 *	 - element: Structured array data for a menu link.
 *
 * @return
 *	 A themed HTML string.
 *
 * @ingroup themeable
 */
function cowpro_p2p_v2_menu_link( array $vars ) {
	$element = $vars['element'];
	$sub_menu = '';

	if ( $element['#below'] ) {
		$sub_menu = drupal_render( $element['#below'] );
	}

	$output = l( $element['#title'], $element['#href'], $element['#localized_options'] );
	// Adding a class depending on the TITLE of the link (not constant)
	$element['#attributes']['class'][] = cowpro_p2p_v2_id_safe( $element['#title'] );
	// Adding a class depending on the ID of the link (constant)
	$element['#attributes']['class'][] = 'mid-' . $element['#original_link']['mlid'];

	return '<li' . drupal_attributes( $element['#attributes'] ) . '>' . $output . $sub_menu . "</li>\n";
}

/**
 * Override or insert variables into theme_menu_local_task().
 */
function cowpro_p2p_v2_preprocess_menu_local_task( &$vars ) {
	$link = & $vars['element']['#link'];

	// If the link does not contain HTML already, check_plain() it now.
	// After we set 'html'=TRUE the link will not be sanitized by l().
	if ( empty( $link['localized_options']['html'] ) ) {
		$link['title'] = check_plain( $link['title'] );
	}

	$link['localized_options']['html'] = TRUE;
	$link['title'] = '<span class="tab">' . $link['title'] . '</span>';
}

/**
 *	Duplicate of theme_menu_local_tasks() but adds clearfix to tabs.
 */
function cowpro_p2p_v2_menu_local_tasks( &$vars ) {
	$output = '';

	if ( !empty( $vars['primary'] ) ) {
		$vars['primary']['#prefix'] = '<h2 class="element-invisible">' . t( 'Primary tabs' ) . '</h2>';
		$vars['primary']['#prefix'] .= '<div class="tabs"><ul class="tabs primary clearfix">';
		$vars['primary']['#suffix'] = '</ul></div>';
		$output .= drupal_render( $vars['primary'] );
	}

	if ( !empty( $vars['secondary'] ) ) {
		$vars['secondary']['#prefix'] = '<h2 class="element-invisible">' . t( 'Secondary tabs' ) . '</h2>';
		$vars['secondary']['#prefix'] .= '<ul class="tabs secondary clearfix">';
		$vars['secondary']['#suffix'] = '</ul>';
		$output .= drupal_render( $vars['secondary'] );
	}

	return $output;
}

/**
 * Implements template_preprocess_comment().
 * Preprocess variables for comment.tpl.php.
 * Borrowed from Responsive HTML5 Boilerplate.
 * @link http://drupal.org/project/html5_boilerplate
 */
function cowpro_p2p_v2_preprocess_comment( &$variables ) {
	$uri = entity_uri( 'comment', $variables['comment'] );
	$uri['options'] += array( 'attributes' => array( 'rel' => 'bookmark' ) );
	$variables['title'] = l( $variables['comment']->subject, $uri['path'], $uri['options'] );
	$variables['permalink'] = l( t( 'Permalink' ), $uri['path'], $uri['options'] );
	$variables['created'] = '<span class="date-time permalink">' . l( $variables['created'], $uri['path'], $uri['options'] ) . '</span>';
	$variables['datetime'] = format_date( $variables['comment']->created, 'custom', 'c' );
	$variables['unpublished'] = '';

	if ( $variables['status'] === 'comment-unpublished' ) {
		$variables['unpublished'] = '<div class="unpublished">' . t( 'Unpublished' ) . '</div>';
	}

	// Add class to comment title.
	if ( !isset( $variables['title_attributes_array']['class'] ) ) {
		$variables['title_attributes_array']['class'] = array();
	}
	$variables['title_attributes_array']['class'][] = 'comment-title';

	// Add class to comment content.
	if ( !isset( $variables['content_attributes_array']['class'] ) ) {
		$variables['content_attributes_array']['class'] = array();
	}
	$variables['content_attributes_array']['class'][] = 'comment-content';
	$variables['content_attributes_array']['class'][] = 'content';
}

/* Less compiler */
include( 'includes/lessc.inc.php' );
include( 'includes/less-compile.php' );

/* Region options */
function cowpro_p2p_v2_region_preffix ( $reg ) {
	$block_bg_type = theme_get_setting( 'cowpro_p2p_v2_' . $reg . '_bg_type' );
	$block_bg_img = theme_get_setting( 'cowpro_p2p_v2_' . $reg . '_bg_img' );
	$block_bg_parallax = theme_get_setting( 'cowpro_p2p_v2_' . $reg . '_bg_parallax' );
	$bg_video = theme_get_setting( 'cowpro_p2p_v2_' . $reg . '_bg_video' );
	$bg_video_start = theme_get_setting( 'cowpro_p2p_v2_' . $reg . '_bg_video_start' );
	$fullwidth = theme_get_setting( 'cowpro_p2p_v2_' . $reg . '_fullwidth' );

	$classes = ' class="' . $reg . '_wrapper';
	$styles = '';
	$attributes = '';
	$content = "\n";

	if ( isset( $block_bg_img['fid'] ) && $block_bg_img['fid'] && ( $block_bg_type == 'image' ) ) {
		$file = file_load( $block_bg_img['fid'] );
		$url = file_create_url( $file->uri );
		if ( !$block_bg_parallax ) {
			$styles .= ' style="background-image: url(' . $url . '); background-position: center top;"';
		}
		$classes .= ' img-bg';

		if ( $block_bg_parallax ) {
			$classes .= ' parallax-box image-parallax-box';
		}
	}

	if ( isset( $bg_video ) && $bg_video && ( $block_bg_type == 'video' ) ) {
		if ( $bg_video_start == null ) {
			$bg_video_start = 0;
		}
		$classes .= ' video-bg';
		$bg_video_start = (int) $bg_video_start;
		$content .= '<a class="tm_video_bg" data-property="{videoURL:\'' . $bg_video . '\', containment:\'#' . $reg . '_wrapper\',autoPlay:true, showControls:false, mute:true, startAt:' . $bg_video_start . ', opacity:1}">youtube</a>';
	}

	if ( $fullwidth ) {
		$classes .= ' region-fullwidth';
	}

	$classes .= '"';

	$output_preffix = '<div id="' . $reg . '_wrapper"' . $classes . $styles . $attributes . '>' . $content;
		if ( !$fullwidth ) {
			$output_preffix .= '<div class="container-12">';
				$output_preffix .= '<div class="grid-12">';
		}

	print $output_preffix;
}
function cowpro_p2p_v2_region_suffix ( $reg ) {
	$fullwidth = theme_get_setting( 'cowpro_p2p_v2_' . $reg . '_fullwidth' );
	$block_bg_parallax = theme_get_setting( 'cowpro_p2p_v2_' . $reg . '_bg_parallax' );
	$block_bg_img = theme_get_setting( 'cowpro_p2p_v2_' . $reg . '_bg_img' );

	$output_suffix = '';
		if ( !$fullwidth ) {
				$output_suffix .= '</div>';
			$output_suffix .= '</div>';
		}
	if ( $block_bg_parallax ) {
		$file = file_load( $block_bg_img['fid'] );
		$url = file_create_url( $file->uri );
		$output_suffix .= '<div class="parallax-bg" data-parallax-type="image" data-img-url="' . $url . '" data-speed="0.5" data-invert="false"></div>';
	}
	$output_suffix .= '</div>';

	print $output_suffix;
}


function cowpro_p2p_v2_form_contact_site_form_alter( &$form, &$form_state, $form_id ) {
	$form['name']['#attributes']['placeholder'] = t( "Name" );
	$form['name']['#title_display'] = 'invisible';

	$form['mail']['#attributes']['placeholder'] = t( "E-mail" );
	$form['mail']['#title_display'] = 'invisible';

	$form['subject']['#attributes']['placeholder'] = t( "Subject" );
	$form['subject']['#title_display'] = 'invisible';

	$form['message']['#attributes']['placeholder'] = t( "Message" );
	$form['message']['#title_display'] = 'invisible';

	$form['reset'] = array(
		'#type' => 'markup',
		'#markup' => '<input class="form-button" type="reset" value="' . t( "Clear" ) . '">',
		'#weight' => 1,
	);
}

/**
 * Themable display of the 'breadcrumb' trail to show the order of the forms.
 */
function cowpro_p2p_v2_ctools_wizard_trail__registration_wizard($vars) {
	//<span class="wizard-trail-current"><a href="/cms/cowpro/registration_wizard/payment_password" data-thmr="thmr_1">支付密码</a></span>
	//<span class="wizard-trail-next"><a href="/cms/cowpro/registration_wizard/moneymoremore" data-thmr="thmr_2">关联乾多多账户</a></span>
	//<span class="wizard-trail-next"><a href="/cms/cowpro/registration_wizard/mobile" data-thmr="thmr_3">手机认证</a></span>
	//<span class="wizard-trail-next"><a href="/cms/cowpro/registration_wizard/credentials" data-thmr="thmr_4">证明文件</a></span>
	if (!empty($vars['trail'])) {
		$profile_types = registration_wizard_get_available_profile_types();
		foreach ($profile_types as $value) {
			if ($value['included']) {
				foreach($vars['trail'] as $id => $trail) {
					if (strpos($trail, $value['type']) !== false) {
						$class = $value['type'] . ' ';
						$uid = $GLOBALS ['user']->uid;
						$profile = cowpro_customer_profile_load_one_row_with_conditions($uid, $value['type']);
						if (!is_null($profile)) {
							$class .= 'audited';
						} else {
							$class .= 'unaudited';
						}
						$vars['trail'][$id] = '<span class="' . $class . '">' . $vars['trail'][$id] . '</span>';
					}
				}
			}
		}
		return '<div class="wizard-trail">' . implode('', $vars['trail']) . '</div>';
	}
}

function cowpro_p2p_v2_username($variables) {
	$userpath = 'user/' . $variables['uid'];
	$output = l($variables['name'] . $variables['extra'], $userpath, $variables['link_options']);
	return $output;
}
