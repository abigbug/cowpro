<?php
/**
 * @file
 * The primary PHP file for this theme.
 */
function sopuopc_process_page(&$variables) {

    // Page template suggestions based off of content types
   if (isset($variables['node'])) {

                $variables['theme_hook_suggestions'][] = 'page__type__'. $variables['node']->type;
                $variables['theme_hook_suggestions'][] = "page__node__" . $variables['node']->nid;
				$variables['theme_hook_suggestions'][] = 'page__node__' . str_replace('_', '--', $variables['node']->type);

				  				//use page path
				$alias = drupal_get_path_alias($_GET['q']);
    if ($alias != $_GET['q']) {
        $template_filename = 'page';

        //Break it down for each piece of the alias path
        foreach (explode('/', $alias) as $path_part) {
            $template_filename = $template_filename . '__' . $path_part;
            $variables['theme_hook_suggestions'][] = $template_filename;
            }

        }
   }
    if (arg(0) == 'taxonomy' && arg(1) == 'term' && is_numeric(arg(2))) {
    $tid = arg(2);
    $vid = db_query("SELECT vid FROM {taxonomy_term_data} WHERE tid = :tid", array(':tid' => $tid))->fetchField();

    $variables['theme_hook_suggestions'][] = 'page__vocabulary__'.$vid;
  }
  // Always print the site name and slogan, but if they are toggled off, we'll

}




function sopuopc_preprocess_node (&$variables) {
$variables['theme_hook_suggestions'][] = 'node__' . $variables['type'] . '__' . $variables['view_mode'];
$variables['theme_hook_suggestions'][] = "node__" . $variables['node']->nid . '__' . $variables['view_mode'];
}
function sopuopc_date_display_range($variables) {
  $date1 = $variables['date1'];
  $date2 = $variables['date2'];
  $timezone = $variables['timezone'];
  $attributes_start = $variables['attributes_start'];
  $attributes_end = $variables['attributes_end'];

  $start_date = '<span class="date-display-start"' . drupal_attributes($attributes_start) . '>' . $date1 . '</span>';
  $end_date = '<span class="date-display-end"' . drupal_attributes($attributes_end) . '>' . $date2 . $timezone . '</span>';

  // If microdata attributes for the start date property have been passed in,
  // add the microdata in meta tags.
  if (!empty($variables['add_microdata'])) {
    $start_date .= '<meta' . drupal_attributes($variables['microdata']['value']['#attributes']) . '/>';
    $end_date .= '<meta' . drupal_attributes($variables['microdata']['value2']['#attributes']) . '/>';
  }

  // Wrap the result with the attributes.
  return t('!start-date - !end-date', array(
    '!start-date' => $start_date,
    '!end-date' => $end_date,
  ));
}

/**
 * Implements hook_menu_link().
 */
function sopuopc_menu_link($variables) {
  $element = &$variables['element'];

  // If there is a image uploaded to the menu item, replace the title with the
  // image.
  if (isset($element['#localized_options']['content']['image'])) {
    $image = file_load($element['#localized_options']['content']['image']);
    $image_info = image_get_info($image->uri);

    $image_markup = theme_image(array(
        'path' => $image->uri,
        'width' => $image_info['width'],
        'height' => $image_info['height'],
        'attributes' => array(),
      )
    );

    $element['#localized_options']['html'] = true;
    $element['#title'] = $image_markup;
  }

  return theme_menu_link($variables);
}

function sopuopc_preprocess_menu_tree__navigation(&$variables) {
	//print_r($variables);
}

function sopuopc_preprocess_menu__navigation(&$variables) {
	//print_r($variables);
}

