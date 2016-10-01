<?php

/**
 * @file
 * Theme settings for the cowpro_p2p
 */
function cowpro_p2p_form_system_theme_settings_alter( &$form, &$form_state ) {
	if ( !isset( $form['cowpro_p2p_settings'] ) ) {
		/**
		 * Vertical tabs layout borrowed from Sasson.
		 *
		 * @link http://drupal.org/project/sasson
		 */
		drupal_add_css( drupal_get_path( 'theme', 'cowpro_p2p' ) . '/css/options/theme-settings.css', array(
			'group'				=> CSS_THEME,
			'every_page'		=> TRUE,
			'weight'			=> 99
		) );

		// Enable/disable options wich are depends on modules
		$background_types = array(
			'none' => 'None',
		);
		$note = '';

		if ( module_exists ( 'media' ) ) {
			$background_types['image'] = 'Image';
		} else {
			$note .= t( '<p style="color: #f00">You should enable Media Module to use all of these proporties!</p>' );
		}

		if ( module_exists ( 'tm_block_bg' ) ) {
			$background_types['video'] = 'Video';
		} else {
			$note .= t( '<p style="color: #f00">You should enable TM Block Background Module to use all of these proporties!</p>' );
		}

		/* Submit function */
		$form['#submit'][] = 'cowpro_p2p_form_system_theme_settings_submit';

		/* Add reset button */
		$form['actions']['reset'] = array(
			'#submit' => array( 'cowpro_p2p_form_system_theme_settings_reset' ),
			'#type' => 'submit',
			'#value' => t( 'Reset to defaults' ),
		);

		/* Settings */
		$form['cowpro_p2p_settings'] = array(
			'#type'				=> 'vertical_tabs',
			'#weight'			=> -10,
		);

		/**
		 * General settings.
		 */
		$form['cowpro_p2p_settings']['cowpro_p2p_general'] = array(
			'#title'			=> t( 'General Settings' ),
			'#type'				=> 'fieldset',
		);

		$form['cowpro_p2p_settings']['cowpro_p2p_general']['theme_settings'] = $form['theme_settings'];
		unset( $form['theme_settings'] );

		$form['cowpro_p2p_settings']['cowpro_p2p_general']['logo'] = $form['logo'];
		unset( $form['logo'] );

		$form['cowpro_p2p_settings']['cowpro_p2p_general']['favicon'] = $form['favicon'];
		unset( $form['favicon'] );

		$form['cowpro_p2p_settings']['cowpro_p2p_general']['cowpro_p2p_sticky_menu'] = array(
			'#default_value'	=> theme_get_setting( 'cowpro_p2p_sticky_menu' ),
			'#title'			=> t( 'Stick up menu.' ),
			'#type'				=> 'checkbox',
		);

		/**
		 * Breadcrumb settings.
		 */
		$form['cowpro_p2p_settings']['cowpro_p2p_breadcrumb'] = array(
			'#title'			=> t( 'Breadcrumb Settings' ),
			'#type'				=> 'fieldset',
		);

		$form['cowpro_p2p_settings']['cowpro_p2p_breadcrumb']['cowpro_p2p_breadcrumb_show'] = array(
			'#default_value'	=> theme_get_setting( 'cowpro_p2p_breadcrumb_show' ),
			'#title'			=> t( 'Show the breadcrumb.' ),
			'#type'				=> 'checkbox',
		);

		$form['cowpro_p2p_settings']['cowpro_p2p_breadcrumb']['cowpro_p2p_breadcrumb_container'] = array(
			'#states'			=> array(
				'invisible'		=> array(
					'input[name="cowpro_p2p_breadcrumb_show"]' => array(
						'checked'	=> FALSE
					),
				),
			),
			'#type'				=> 'container',
		);

		$form['cowpro_p2p_settings']['cowpro_p2p_breadcrumb']['cowpro_p2p_breadcrumb_container']['cowpro_p2p_breadcrumb_hideonlyfront'] = array(
			'#default_value'	=> theme_get_setting( 'cowpro_p2p_breadcrumb_hideonlyfront' ),
			'#title'			=> t( 'Hide the breadcrumb if the breadcrumb only contains a link to the front page.' ),
			'#type'				=> 'checkbox',
		);

		$form['cowpro_p2p_settings']['cowpro_p2p_breadcrumb']['cowpro_p2p_breadcrumb_container']['cowpro_p2p_breadcrumb_showtitle'] = array(
			'#default_value'	=> theme_get_setting( 'cowpro_p2p_breadcrumb_showtitle' ),
			'#description'		=> t( "Check this option to add the current page's title to the breadcrumb trail." ),
			'#title'			=> t( 'Show page title on breadcrumb.' ),
			'#type'				=> 'checkbox',
		);

		$form['cowpro_p2p_settings']['cowpro_p2p_breadcrumb']['cowpro_p2p_breadcrumb_container']['cowpro_p2p_breadcrumb_separator'] = array(
			'#default_value'	=> theme_get_setting( 'cowpro_p2p_breadcrumb_separator' ),
			'#description'		=> t( 'Text only. Dont forget to include spaces.' ),
			'#size'				=> 8,
			'#title'			=> t( 'Breadcrumb separator' ),
			'#type'				=> 'textfield',
		);

		/**
		 * Regions Settings
		 */
		$form['cowpro_p2p_settings']['cowpro_p2p_regions'] = array(
			'#description'		=> $note,
			'#title'			=> t( 'Regions Settings' ),
			'#type'				=> 'fieldset',
		);

		// Header
		$form['cowpro_p2p_settings']['cowpro_p2p_regions']['cowpro_p2p_header_opt'] = array(
			'#title'			=> t( 'Header' ),
			'#type'				=> 'fieldset',
		);
		$form['cowpro_p2p_settings']['cowpro_p2p_regions']['cowpro_p2p_header_opt']['cowpro_p2p_header_bg_type'] = array(
			'#default_value' => theme_get_setting( 'cowpro_p2p_header_bg_type' ),
			'#options' => $background_types,
			'#title' => t( 'Background type:' ),
			'#type' => 'select',
		);
		$form['cowpro_p2p_settings']['cowpro_p2p_regions']['cowpro_p2p_header_opt']['cowpro_p2p_header_bg_img'] = array(
			'#default_value'	=> theme_get_setting( 'cowpro_p2p_header_bg_img' ),
			'#description'		=> t( 'Choose block background image.' ),
			'#media_options' => array(
				'global' => array(
					'types' => array(
						'image' => 'image',
					),
					'schemes' => array(
						'public' => 'public',
					),
					'file_extensions' => 'png gif jpg jpeg',
					'max_filesize' => '1 MB',
					'uri_scheme' => 'public',
				),
			),
			'#states'			=> array(
				'visible'		=> array(
					'select[name="cowpro_p2p_header_bg_type"]' => array(
						'value'	=> 'image'
					),
				),
			),
			'#title'			=> t( 'Background image URL' ),
			'#tree'				=> TRUE,
			'#type'				=> 'media',
		);
		$form['cowpro_p2p_settings']['cowpro_p2p_regions']['cowpro_p2p_header_opt']['cowpro_p2p_header_bg_parallax'] = array(
			'#default_value' =>  theme_get_setting( 'cowpro_p2p_header_bg_parallax' ),
			'#states'			=> array(
				'visible'		=> array(
					'select[name="cowpro_p2p_header_bg_type"]' => array(
						'value'	=> 'image'
					),
				),
			),
			'#title' => t( 'Use parallax' ),
			'#type' => 'checkbox',
		);
		$form['cowpro_p2p_settings']['cowpro_p2p_regions']['cowpro_p2p_header_opt']['cowpro_p2p_header_bg_video'] = array(
			'#default_value'	=> theme_get_setting( 'cowpro_p2p_header_bg_video' ),
			'#description'		=> t( 'Enter video URL. Supports youtube video. ' ),
			'#size'				=> 60,
			'#states'			=> array(
				'visible'		=> array(
					'select[name="cowpro_p2p_header_bg_type"]' => array(
						'value'	=> 'video'
					),
				),
			),
			'#title'			=> t( 'Background Video URL' ),
			'#type'				=> 'textfield',
		);
		$form['cowpro_p2p_settings']['cowpro_p2p_regions']['cowpro_p2p_header_opt']['cowpro_p2p_header_bg_video_start'] = array(
			'#default_value'	=> theme_get_setting( 'cowpro_p2p_header_bg_video_start' ),
			'#description'		=> t( 'Enter time in seconds. ' ),
			'#size'				=> 8,
			'#states'			=> array(
				'visible'		=> array(
					'select[name="cowpro_p2p_header_bg_type"]' => array(
						'value'	=> 'video'
					),
				),
			),
			'#title'			=> t( 'Start video at' ),
			'#type'				=> 'textfield',
		);
		$form['cowpro_p2p_settings']['cowpro_p2p_regions']['cowpro_p2p_header_opt']['cowpro_p2p_header_fullwidth'] = array(
			'#default_value'	=> theme_get_setting( 'cowpro_p2p_header_fullwidth' ),
			'#description'		=> t( "Check this option to make this region fullwidth (e.g. remove grids)." ),
			'#title'			=> t( 'Fullwidth' ),
			'#type'				=> 'checkbox',
		);

		// Header bottom
		$form['cowpro_p2p_settings']['cowpro_p2p_regions']['cowpro_p2p_header_bottom_opt'] = array(
			'#title'			=> t( 'Header bottom' ),
			'#type'				=> 'fieldset',
		);
		$form['cowpro_p2p_settings']['cowpro_p2p_regions']['cowpro_p2p_header_bottom_opt']['cowpro_p2p_header_bottom_bg_type'] = array(
			'#default_value' => theme_get_setting( 'cowpro_p2p_header_bottom_bg_type' ),
			'#options' => $background_types,
			'#title' => t( 'Background type:' ),
			'#type' => 'select',
		);
		$form['cowpro_p2p_settings']['cowpro_p2p_regions']['cowpro_p2p_header_bottom_opt']['cowpro_p2p_header_bottom_bg_img'] = array(
			'#default_value'	=> theme_get_setting( 'cowpro_p2p_header_bottom_bg_img' ),
			'#description'		=> t( 'Choose block background image.' ),
			'#media_options' => array(
				'global' => array(
					'types' => array(
						'image' => 'image',
					),
					'schemes' => array(
						'public' => 'public',
					),
					'file_extensions' => 'png gif jpg jpeg',
					'max_filesize' => '1 MB',
					'uri_scheme' => 'public',
				),
			),
			'#states'			=> array(
				'visible'		=> array(
					'select[name="cowpro_p2p_header_bottom_bg_type"]' => array(
						'value'	=> 'image'
					),
				),
			),
			'#title'			=> t( 'Background image URL' ),
			'#tree'				=> TRUE,
			'#type'				=> 'media',
		);
		$form['cowpro_p2p_settings']['cowpro_p2p_regions']['cowpro_p2p_header_bottom_opt']['cowpro_p2p_header_bottom_bg_parallax'] = array(
			'#default_value' =>  theme_get_setting( 'cowpro_p2p_header_bottom_bg_parallax' ),
			'#states'			=> array(
				'visible'		=> array(
					'select[name="cowpro_p2p_header_bottom_bg_type"]' => array(
						'value'	=> 'image'
					),
				),
			),
			'#title' => t( 'Use parallax' ),
			'#type' => 'checkbox',
		);
		$form['cowpro_p2p_settings']['cowpro_p2p_regions']['cowpro_p2p_header_bottom_opt']['cowpro_p2p_header_bottom_bg_video'] = array(
			'#default_value'	=> theme_get_setting( 'cowpro_p2p_header_bottom_bg_video' ),
			'#description'		=> t( 'Enter video URL. Supports youtube video. ' ),
			'#size'				=> 60,
			'#states'			=> array(
				'visible'		=> array(
					'select[name="cowpro_p2p_header_bottom_bg_type"]' => array(
						'value'	=> 'video'
					),
				),
			),
			'#title'			=> t( 'Background Video URL' ),
			'#type'				=> 'textfield',
		);
		$form['cowpro_p2p_settings']['cowpro_p2p_regions']['cowpro_p2p_header_bottom_opt']['cowpro_p2p_header_bottom_bg_video_start'] = array(
			'#default_value'	=> theme_get_setting( 'cowpro_p2p_header_bottom_bg_video_start' ),
			'#description'		=> t( 'Enter time in seconds. ' ),
			'#size'				=> 8,
			'#states'			=> array(
				'visible'		=> array(
					'select[name="cowpro_p2p_header_bottom_bg_type"]' => array(
						'value'	=> 'video'
					),
				),
			),
			'#title'			=> t( 'Start video at' ),
			'#type'				=> 'textfield',
		);
		$form['cowpro_p2p_settings']['cowpro_p2p_regions']['cowpro_p2p_header_bottom_opt']['cowpro_p2p_header_bottom_fullwidth'] = array(
			'#default_value'	=> theme_get_setting( 'cowpro_p2p_header_bottom_fullwidth' ),
			'#description'		=> t( "Check this option to make this region fullwidth (e.g. remove grids)." ),
			'#title'			=> t( 'Fullwidth' ),
			'#type'				=> 'checkbox',
		);

		// Content top
		$form['cowpro_p2p_settings']['cowpro_p2p_regions']['cowpro_p2p_content_top_opt'] = array(
			'#title'			=> t( 'Content top' ),
			'#type'				=> 'fieldset',
		);
		$form['cowpro_p2p_settings']['cowpro_p2p_regions']['cowpro_p2p_content_top_opt']['cowpro_p2p_content_top_bg_type'] = array(
			'#default_value' => theme_get_setting( 'cowpro_p2p_content_top_bg_type' ),
			'#options' => $background_types,
			'#title' => t( 'Background type:' ),
			'#type' => 'select',
		);
		$form['cowpro_p2p_settings']['cowpro_p2p_regions']['cowpro_p2p_content_top_opt']['cowpro_p2p_content_top_bg_img'] = array(
			'#default_value'	=> theme_get_setting( 'cowpro_p2p_content_top_bg_img' ),
			'#description'		=> t( 'Choose block background image.' ),
			'#media_options' => array(
				'global' => array(
					'types' => array(
						'image' => 'image',
					),
					'schemes' => array(
						'public' => 'public',
					),
					'file_extensions' => 'png gif jpg jpeg',
					'max_filesize' => '1 MB',
					'uri_scheme' => 'public',
				),
			),
			'#states'			=> array(
				'visible'		=> array(
					'select[name="cowpro_p2p_content_top_bg_type"]' => array(
						'value'	=> 'image'
					),
				),
			),
			'#title'			=> t( 'Background image URL' ),
			'#tree'				=> TRUE,
			'#type'				=> 'media',
		);
		$form['cowpro_p2p_settings']['cowpro_p2p_regions']['cowpro_p2p_content_top_opt']['cowpro_p2p_content_top_bg_parallax'] = array(
			'#default_value' =>  theme_get_setting( 'cowpro_p2p_content_top_bg_parallax' ),
			'#states'			=> array(
				'visible'		=> array(
					'select[name="cowpro_p2p_content_top_bg_type"]' => array(
						'value'	=> 'image'
					),
				),
			),
			'#title' => t( 'Use parallax' ),
			'#type' => 'checkbox',
		);
		$form['cowpro_p2p_settings']['cowpro_p2p_regions']['cowpro_p2p_content_top_opt']['cowpro_p2p_content_top_bg_video'] = array(
			'#default_value'	=> theme_get_setting( 'cowpro_p2p_content_top_bg_video' ),
			'#description'		=> t( 'Enter video URL. Supports youtube video. ' ),
			'#size'				=> 60,
			'#states'			=> array(
				'visible'		=> array(
					'select[name="cowpro_p2p_content_top_bg_type"]' => array(
						'value'	=> 'video'
					),
				),
			),
			'#title'			=> t( 'Background Video URL' ),
			'#type'				=> 'textfield',
		);
		$form['cowpro_p2p_settings']['cowpro_p2p_regions']['cowpro_p2p_content_top_opt']['cowpro_p2p_content_top_bg_video_start'] = array(
			'#default_value'	=> theme_get_setting( 'cowpro_p2p_content_top_bg_video_start' ),
			'#description'		=> t( 'Enter time in seconds. ' ),
			'#size'				=> 8,
			'#states'			=> array(
				'visible'		=> array(
					'select[name="cowpro_p2p_content_top_bg_type"]' => array(
						'value'	=> 'video'
					),
				),
			),
			'#title'			=> t( 'Start video at' ),
			'#type'				=> 'textfield',
		);
		$form['cowpro_p2p_settings']['cowpro_p2p_regions']['cowpro_p2p_content_top_opt']['cowpro_p2p_content_top_fullwidth'] = array(
			'#default_value'	=> theme_get_setting( 'cowpro_p2p_content_top_fullwidth' ),
			'#description'		=> t( "Check this option to make this region fullwidth (e.g. remove grids)." ),
			'#title'			=> t( 'Fullwidth' ),
			'#type'				=> 'checkbox',
		);

		// Content bottom
		$form['cowpro_p2p_settings']['cowpro_p2p_regions']['cowpro_p2p_content_bottom_opt'] = array(
			'#title'			=> t( 'Content bottom' ),
			'#type'				=> 'fieldset',
		);
		$form['cowpro_p2p_settings']['cowpro_p2p_regions']['cowpro_p2p_content_bottom_opt']['cowpro_p2p_content_bottom_bg_type'] = array(
			'#default_value' => theme_get_setting( 'cowpro_p2p_content_bottom_bg_type' ),
			'#options' => $background_types,
			'#title' => t( 'Background type:' ),
			'#type' => 'select',
		);
		$form['cowpro_p2p_settings']['cowpro_p2p_regions']['cowpro_p2p_content_bottom_opt']['cowpro_p2p_content_bottom_bg_img'] = array(
			'#default_value'	=> theme_get_setting( 'cowpro_p2p_content_bottom_bg_img' ),
			'#description'		=> t( 'Choose block background image.' ),
			'#media_options' => array(
				'global' => array(
					'types' => array(
						'image' => 'image',
					),
					'schemes' => array(
						'public' => 'public',
					),
					'file_extensions' => 'png gif jpg jpeg',
					'max_filesize' => '1 MB',
					'uri_scheme' => 'public',
				),
			),
			'#states'			=> array(
				'visible'		=> array(
					'select[name="cowpro_p2p_content_bottom_bg_type"]' => array(
						'value'	=> 'image'
					),
				),
			),
			'#title'			=> t( 'Background image URL' ),
			'#tree'				=> TRUE,
			'#type'				=> 'media',
		);
		$form['cowpro_p2p_settings']['cowpro_p2p_regions']['cowpro_p2p_content_bottom_opt']['cowpro_p2p_content_bottom_bg_parallax'] = array(
			'#default_value' =>  theme_get_setting( 'cowpro_p2p_content_bottom_bg_parallax' ),
			'#states'			=> array(
				'visible'		=> array(
					'select[name="cowpro_p2p_content_bottom_bg_type"]' => array(
						'value'	=> 'image'
					),
				),
			),
			'#title' => t( 'Use parallax' ),
			'#type' => 'checkbox',
		);
		$form['cowpro_p2p_settings']['cowpro_p2p_regions']['cowpro_p2p_content_bottom_opt']['cowpro_p2p_content_bottom_bg_video'] = array(
			'#default_value'	=> theme_get_setting( 'cowpro_p2p_content_bottom_bg_video' ),
			'#description'		=> t( 'Enter video URL. Supports youtube video. ' ),
			'#size'				=> 60,
			'#states'			=> array(
				'visible'		=> array(
					'select[name="cowpro_p2p_content_bottom_bg_type"]' => array(
						'value'	=> 'video'
					),
				),
			),
			'#title'			=> t( 'Background Video URL' ),
			'#type'				=> 'textfield',
		);
		$form['cowpro_p2p_settings']['cowpro_p2p_regions']['cowpro_p2p_content_bottom_opt']['cowpro_p2p_content_bottom_bg_video_start'] = array(
			'#default_value'	=> theme_get_setting( 'cowpro_p2p_content_bottom_bg_video_start' ),
			'#description'		=> t( 'Enter time in seconds. ' ),
			'#size'				=> 8,
			'#states'			=> array(
				'visible'		=> array(
					'select[name="cowpro_p2p_content_bottom_bg_type"]' => array(
						'value'	=> 'video'
					),
				),
			),
			'#title'			=> t( 'Start video at' ),
			'#type'				=> 'textfield',
		);
		$form['cowpro_p2p_settings']['cowpro_p2p_regions']['cowpro_p2p_content_bottom_opt']['cowpro_p2p_content_bottom_fullwidth'] = array(
			'#default_value'	=> theme_get_setting( 'cowpro_p2p_content_bottom_fullwidth' ),
			'#description'		=> t( "Check this option to make this region fullwidth (e.g. remove grids)." ),
			'#title'			=> t( 'Fullwidth' ),
			'#type'				=> 'checkbox',
		);

		// Prefooter
		$form['cowpro_p2p_settings']['cowpro_p2p_regions']['cowpro_p2p_prefooter_opt'] = array(
			'#title'			=> t( 'Prefooter' ),
			'#type'				=> 'fieldset',
		);
		$form['cowpro_p2p_settings']['cowpro_p2p_regions']['cowpro_p2p_prefooter_opt']['cowpro_p2p_prefooter_bg_type'] = array(
			'#default_value' => theme_get_setting( 'cowpro_p2p_prefooter_bg_type' ),
			'#options' => $background_types,
			'#title' => t( 'Background type:' ),
			'#type' => 'select',
		);
		$form['cowpro_p2p_settings']['cowpro_p2p_regions']['cowpro_p2p_prefooter_opt']['cowpro_p2p_prefooter_bg_img'] = array(
			'#default_value'	=> theme_get_setting( 'cowpro_p2p_prefooter_bg_img' ),
			'#description'		=> t( 'Choose block background image.' ),
			'#media_options' => array(
				'global' => array(
					'types' => array(
						'image' => 'image',
					),
					'schemes' => array(
						'public' => 'public',
					),
					'file_extensions' => 'png gif jpg jpeg',
					'max_filesize' => '1 MB',
					'uri_scheme' => 'public',
				),
			),
			'#states'			=> array(
				'visible'		=> array(
					'select[name="cowpro_p2p_prefooter_bg_type"]' => array(
						'value'	=> 'image'
					),
				),
			),
			'#title'			=> t( 'Background image URL' ),
			'#tree'				=> TRUE,
			'#type'				=> 'media',
		);
		$form['cowpro_p2p_settings']['cowpro_p2p_regions']['cowpro_p2p_prefooter_opt']['cowpro_p2p_prefooter_bg_parallax'] = array(
			'#default_value' =>  theme_get_setting( 'cowpro_p2p_prefooter_bg_parallax' ),
			'#states'			=> array(
				'visible'		=> array(
					'select[name="cowpro_p2p_prefooter_bg_type"]' => array(
						'value'	=> 'image'
					),
				),
			),
			'#title' => t( 'Use parallax' ),
			'#type' => 'checkbox',
		);
		$form['cowpro_p2p_settings']['cowpro_p2p_regions']['cowpro_p2p_prefooter_opt']['cowpro_p2p_prefooter_bg_video'] = array(
			'#default_value'	=> theme_get_setting( 'cowpro_p2p_prefooter_bg_video' ),
			'#description'		=> t( 'Enter video URL. Supports youtube video. ' ),
			'#size'				=> 60,
			'#states'			=> array(
				'visible'		=> array(
					'select[name="cowpro_p2p_prefooter_bg_type"]' => array(
						'value'	=> 'video'
					),
				),
			),
			'#title'			=> t( 'Background Video URL' ),
			'#type'				=> 'textfield',
		);
		$form['cowpro_p2p_settings']['cowpro_p2p_regions']['cowpro_p2p_prefooter_opt']['cowpro_p2p_prefooter_bg_video_start'] = array(
			'#default_value'	=> theme_get_setting( 'cowpro_p2p_prefooter_bg_video_start' ),
			'#description'		=> t( 'Enter time in seconds. ' ),
			'#size'				=> 8,
			'#states'			=> array(
				'visible'		=> array(
					'select[name="cowpro_p2p_prefooter_bg_type"]' => array(
						'value'	=> 'video'
					),
				),
			),
			'#title'			=> t( 'Start video at' ),
			'#type'				=> 'textfield',
		);
		$form['cowpro_p2p_settings']['cowpro_p2p_regions']['cowpro_p2p_prefooter_opt']['cowpro_p2p_prefooter_fullwidth'] = array(
			'#default_value'	=> theme_get_setting( 'cowpro_p2p_prefooter_fullwidth' ),
			'#description'		=> t( "Check this option to make this region fullwidth (e.g. remove grids)." ),
			'#title'			=> t( 'Fullwidth' ),
			'#type'				=> 'checkbox',
		);

		// Footer top
		$form['cowpro_p2p_settings']['cowpro_p2p_regions']['cowpro_p2p_footer_top_opt'] = array(
			'#title'			=> t( 'Footer top' ),
			'#type'				=> 'fieldset',
		);
		$form['cowpro_p2p_settings']['cowpro_p2p_regions']['cowpro_p2p_footer_top_opt']['cowpro_p2p_footer_top_bg_type'] = array(
			'#default_value' => theme_get_setting( 'cowpro_p2p_footer_top_bg_type' ),
			'#options' => $background_types,
			'#title' => t( 'Background type:' ),
			'#type' => 'select',
		);
		$form['cowpro_p2p_settings']['cowpro_p2p_regions']['cowpro_p2p_footer_top_opt']['cowpro_p2p_footer_top_bg_img'] = array(
			'#default_value'	=> theme_get_setting( 'cowpro_p2p_footer_top_bg_img' ),
			'#description'		=> t( 'Choose block background image.' ),
			'#media_options' => array(
				'global' => array(
					'types' => array(
						'image' => 'image',
					),
					'schemes' => array(
						'public' => 'public',
					),
					'file_extensions' => 'png gif jpg jpeg',
					'max_filesize' => '1 MB',
					'uri_scheme' => 'public',
				),
			),
			'#states'			=> array(
				'visible'		=> array(
					'select[name="cowpro_p2p_footer_top_bg_type"]' => array(
						'value'	=> 'image'
					),
				),
			),
			'#title'			=> t( 'Background image URL' ),
			'#tree'				=> TRUE,
			'#type'				=> 'media',
		);
		$form['cowpro_p2p_settings']['cowpro_p2p_regions']['cowpro_p2p_footer_top_opt']['cowpro_p2p_footer_top_bg_parallax'] = array(
			'#default_value' =>  theme_get_setting( 'cowpro_p2p_footer_top_bg_parallax' ),
			'#states'			=> array(
				'visible'		=> array(
					'select[name="cowpro_p2p_footer_top_bg_type"]' => array(
						'value'	=> 'image'
					),
				),
			),
			'#title' => t( 'Use parallax' ),
			'#type' => 'checkbox',
		);
		$form['cowpro_p2p_settings']['cowpro_p2p_regions']['cowpro_p2p_footer_top_opt']['cowpro_p2p_footer_top_bg_video'] = array(
			'#default_value'	=> theme_get_setting( 'cowpro_p2p_footer_top_bg_video' ),
			'#description'		=> t( 'Enter video URL. Supports youtube video. ' ),
			'#size'				=> 60,
			'#states'			=> array(
				'visible'		=> array(
					'select[name="cowpro_p2p_footer_top_bg_type"]' => array(
						'value'	=> 'video'
					),
				),
			),
			'#title'			=> t( 'Background Video URL' ),
			'#type'				=> 'textfield',
		);
		$form['cowpro_p2p_settings']['cowpro_p2p_regions']['cowpro_p2p_footer_top_opt']['cowpro_p2p_footer_top_bg_video_start'] = array(
			'#default_value'	=> theme_get_setting( 'cowpro_p2p_footer_top_bg_video_start' ),
			'#description'		=> t( 'Enter time in seconds. ' ),
			'#size'				=> 8,
			'#states'			=> array(
				'visible'		=> array(
					'select[name="cowpro_p2p_footer_top_bg_type"]' => array(
						'value'	=> 'video'
					),
				),
			),
			'#title'			=> t( 'Start video at' ),
			'#type'				=> 'textfield',
		);
		$form['cowpro_p2p_settings']['cowpro_p2p_regions']['cowpro_p2p_footer_top_opt']['cowpro_p2p_footer_top_fullwidth'] = array(
			'#default_value'	=> theme_get_setting( 'cowpro_p2p_footer_top_fullwidth' ),
			'#description'		=> t( "Check this option to make this region fullwidth (e.g. remove grids)." ),
			'#title'			=> t( 'Fullwidth' ),
			'#type'				=> 'checkbox',
		);

		// Footer bottom
		$form['cowpro_p2p_settings']['cowpro_p2p_regions']['cowpro_p2p_footer_bottom_opt'] = array(
			'#title'			=> t( 'Footer bottom' ),
			'#type'				=> 'fieldset',
		);
		$form['cowpro_p2p_settings']['cowpro_p2p_regions']['cowpro_p2p_footer_bottom_opt']['cowpro_p2p_footer_bottom_bg_type'] = array(
			'#default_value' => theme_get_setting( 'cowpro_p2p_footer_bottom_bg_type' ),
			'#options' => $background_types,
			'#title' => t( 'Background type:' ),
			'#type' => 'select',
		);
		$form['cowpro_p2p_settings']['cowpro_p2p_regions']['cowpro_p2p_footer_bottom_opt']['cowpro_p2p_footer_bottom_bg_img'] = array(
			'#default_value'	=> theme_get_setting( 'cowpro_p2p_footer_bottom_bg_img' ),
			'#description'		=> t( 'Choose block background image.' ),
			'#media_options' => array(
				'global' => array(
					'types' => array(
						'image' => 'image',
					),
					'schemes' => array(
						'public' => 'public',
					),
					'file_extensions' => 'png gif jpg jpeg',
					'max_filesize' => '1 MB',
					'uri_scheme' => 'public',
				),
			),
			'#states'			=> array(
				'visible'		=> array(
					'select[name="cowpro_p2p_footer_bottom_bg_type"]' => array(
						'value'	=> 'image'
					),
				),
			),
			'#title'			=> t( 'Background image URL' ),
			'#tree'				=> TRUE,
			'#type'				=> 'media',
		);
		$form['cowpro_p2p_settings']['cowpro_p2p_regions']['cowpro_p2p_footer_bottom_opt']['cowpro_p2p_footer_bottom_bg_parallax'] = array(
			'#default_value' =>  theme_get_setting( 'cowpro_p2p_footer_bottom_bg_parallax' ),
			'#states'			=> array(
				'visible'		=> array(
					'select[name="cowpro_p2p_footer_bottom_bg_type"]' => array(
						'value'	=> 'image'
					),
				),
			),
			'#title' => t( 'Use parallax' ),
			'#type' => 'checkbox',
		);
		$form['cowpro_p2p_settings']['cowpro_p2p_regions']['cowpro_p2p_footer_bottom_opt']['cowpro_p2p_footer_bottom_bg_video'] = array(
			'#default_value'	=> theme_get_setting( 'cowpro_p2p_footer_bottom_bg_video' ),
			'#description'		=> t( 'Enter video URL. Supports youtube video. ' ),
			'#size'				=> 60,
			'#states'			=> array(
				'visible'		=> array(
					'select[name="cowpro_p2p_footer_bottom_bg_type"]' => array(
						'value'	=> 'video'
					),
				),
			),
			'#title'			=> t( 'Background Video URL' ),
			'#type'				=> 'textfield',
		);
		$form['cowpro_p2p_settings']['cowpro_p2p_regions']['cowpro_p2p_footer_bottom_opt']['cowpro_p2p_footer_bottom_bg_video_start'] = array(
			'#default_value'	=> theme_get_setting( 'cowpro_p2p_footer_bottom_bg_video_start' ),
			'#description'		=> t( 'Enter time in seconds. ' ),
			'#size'				=> 8,
			'#states'			=> array(
				'visible'		=> array(
					'select[name="cowpro_p2p_footer_bottom_bg_type"]' => array(
						'value'	=> 'video'
					),
				),
			),
			'#title'			=> t( 'Start video at' ),
			'#type'				=> 'textfield',
		);
		$form['cowpro_p2p_settings']['cowpro_p2p_regions']['cowpro_p2p_footer_bottom_opt']['cowpro_p2p_footer_bottom_fullwidth'] = array(
			'#default_value'	=> theme_get_setting( 'cowpro_p2p_footer_bottom_fullwidth' ),
			'#description'		=> t( "Check this option to make this region fullwidth (e.g. remove grids)." ),
			'#title'			=> t( 'Fullwidth' ),
			'#type'				=> 'checkbox',
		);

		/**
		 * Blog settings
		 */
		$form['cowpro_p2p_settings']['cowpro_p2p_blog'] = array(
			'#title'			=> t( 'Blog Settings' ),
			'#type'				=> 'fieldset',
		);

		$form['cowpro_p2p_settings']['cowpro_p2p_blog']['cowpro_p2p_blog_title'] = array(
			'#default_value'	=> theme_get_setting( 'cowpro_p2p_blog_title' ),
			'#description'		=> t( 'Text only. Leave empty to set Blog title the same as Blog menu link' ),
			'#size'				=> 60,
			'#title'			=> t( 'Blog title' ),
			'#type'				=> 'textfield',
		);

		/**
		 * Custom CSS
		 */
		$form['cowpro_p2p_settings']['cowpro_p2p_css'] = array(
			'#title'			=> t( 'Custom CSS' ),
			'#type'				=> 'fieldset',
		);

		$form['cowpro_p2p_settings']['cowpro_p2p_css']['cowpro_p2p_custom_css'] = array(
			'#default_value'	=> theme_get_setting( 'cowpro_p2p_custom_css' ),
			'#description'		=> t( 'Insert your CSS code here.' ),
			'#title'			=> t( 'Custom CSS' ),
			'#type'				=> 'textarea',
		);
	}
}


/* Custom CSS */
function cowpro_p2p_form_system_theme_settings_submit( $form, &$form_state ) {
	$fp = fopen( drupal_get_path( 'theme', 'cowpro_p2p' ) . '/css/custom.css', 'a' );
	ftruncate( $fp, 0 );
	fwrite( $fp, $form_state['values']['cowpro_p2p_custom_css'] );
	fclose( $fp );
}

/* Reset options */
function cowpro_p2p_form_system_theme_settings_reset( $form, &$form_state ) {
	form_state_values_clean( $form_state );

	variable_del( 'theme_cowpro_p2p_settings' );

	$fp = fopen( drupal_get_path( 'theme', 'cowpro_p2p' ) . '/css/custom.css', 'a' );
	ftruncate( $fp, 0 );
	fclose( $fp );

	drupal_set_message( t( 'The configuration options have been reset to their default values.' ) );
}