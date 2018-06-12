<?php
/**
 * @file
 * Example demonstrating a simple (i.e. 'sort' only) tabledrag form
 */

/**
 * Build the tabledrag_simple_example_form form.
 *
 * @return array
 *   A form array set for theming by theme_registration_wizard_admin_form()
 *
 * @ingroup tabledrag_example
 */
function registration_wizard_admin_form($form_state) {
  // Identify that the elements in 'profile_type_items' are a collection, to
  // prevent Form API from flattening the array when submitted.
  $form['profile_type_items']['#tree'] = TRUE;
  $form['profile_type_items'] = array_merge($form['profile_type_items'], _registration_wizard_get_sorted_profile_type_element());

  // Now we add our submit button, for submitting the form results.
  //
  // The 'actions' wrapper used here isn't strictly necessary for tabledrag,
  // but is included as a Form API recommended practice.
  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array('#type' => 'submit', '#value' => t('Save Changes'));
  return $form;
}

function _registration_wizard_get_sorted_profile_type_element() {
	$profile_type_wizard = variable_get('cowpro_registration_wizard', array());
	$profile_types = cowpro_customer_profile_types();

	$items = array();
	foreach ($profile_types as $key => $value) {
		$setup = array_key_exists($key, $profile_type_wizard)?$profile_type_wizard[$key]:NULL;

		// Create a form entry for this item.
		//
		// Each entry will be an array using the the unique id for that item as
		// the array key, and an array of table row data as the value.
		$items[$key] = array(
				//在下面的usort方法中，会丢失数组的key，所以在这里先记录一下
				'key' => $key,

				// We'll use a form element of type '#markup' to display the item name.
				'name' => array(
						'#markup' => check_plain($value['name']),
				),

				'included' => array(
						'#type' => 'checkbox',
						'#title' => t('includ in wizard'),
						'#title_display' => 'invisible',
						'#default_value' => isset($setup)?$setup['included']:TRUE,
				),

				// We'll use a form element of type '#textfield' to display the item
				// description, which will allow the value to be changed via the form.
				// We limit the input to 255 characters, which is the limit we set on
				// the database field.
				'description' => array(
						'#type' => 'textfield',
						'#default_value' => check_plain($value['description']),
						'#size' => 80,
						'#maxlength' => 255,
						'#disabled' => TRUE,
				),
				/*
				 'type' => array(
				 		'#type' => 'textfield',
				 		'#default_value' => $value['type'],
				 		'#size' => 80,
				 		'#maxlength' => 255,
				 		'#disabled' => TRUE,
				 		'#access' => FALSE,
				 ),
		*/
				// The 'weight' field will be manipulated as we move the items around in
				// the table using the tabledrag activity.  We use the 'weight' element
				// defined in Drupal's Form API.
				'weight' => array(
						'#type' => 'weight',
						'#title' => t('Weight'),
						'#default_value' => isset($setup)?$setup['weight']:$value['weight'],
						'#delta' => 10,
						'#title_display' => 'invisible',
				),
		);
	}

	//按['weight']的初始值进行排序
	usort($items, '_registration_wizard_profile_type_element_compare');

	//usort执行之后，$items的数组下标丢失，所以这里要将之前保存在$items中的$key恢复出来
	$result = array();
	foreach ($items as $item) {
		$key = $item['key'];
		unset($item['key']);
		$result[$key] = $item;
	}
	return $result;
}

function _registration_wizard_profile_type_element_compare($a, $b) {
	$a_val = (int) $a['weight']['#default_value'];
	$b_val = (int) $b['weight']['#default_value'];

	if($a_val > $b_val) return 1;
	if($a_val < $b_val) return -1;
	return 0;
}

/**
 * Theme callback for the registration_wizard_admin_form form.
 *
 * The theme callback will format the $form data structure into a table and
 * add our tabledrag functionality.  (Note that drupal_add_tabledrag should be
 * called from the theme layer, and not from a form declaration.  This helps
 * keep template files clean and readable, and prevents tabledrag.js from
 * being added twice accidently.
 *
 * @return array
 *   The rendered tabledrag form
 *
 * @ingroup tabledrag_example
 */
function theme_registration_wizard_admin_form($variables) {
  $form = $variables['form'];

  // Initialize the variable which will store our table rows.
  $rows = array();

  // Iterate over each element in our $form['profile_type_items'] array.
  foreach (element_children($form['profile_type_items']) as $id) {

    // Before we add our 'weight' column to the row, we need to give the
    // element a custom class so that it can be identified in the
    // drupal_add_tabledrag call.
    //
    // This could also have been done during the form declaration by adding
    // '#attributes' => array('class' => 'example-item-weight'),
    // directy to the 'weight' element in registration_wizard_admin_form().
    $form['profile_type_items'][$id]['weight']['#attributes']['class'] = array('profile-type-weight');

    // We are now ready to add each element of our $form data to the $rows
    // array, so that they end up as individual table cells when rendered
    // in the final table.  We run each element through the drupal_render()
    // function to generate the final html markup for that element.
    $rows[] = array(
      'data' => array(
        // Add our 'name' column.
        drupal_render($form['profile_type_items'][$id]['name']),
        // Add our 'included' column.
        drupal_render($form['profile_type_items'][$id]['included']),
      	// Add our 'description' column.
        drupal_render($form['profile_type_items'][$id]['description']),
        // Add our 'weight' column.
        drupal_render($form['profile_type_items'][$id]['weight']),
      ),
      // To support the tabledrag behaviour, we need to assign each row of the
      // table a class attribute of 'draggable'. This will add the 'draggable'
      // class to the <tr> element for that row when the final table is
      // rendered.
      'class' => array('draggable'),
    );
  }

  // We now define the table header values.  Ensure that the 'header' count
  // matches the final column count for your table.
  $header = array(t('Name'), t('Included'), t('Description'), t('Weight'));

  // We also need to pass the drupal_add_tabledrag() function an id which will
  // be used to identify the <table> element containing our tabledrag form.
  // Because an element's 'id' should be unique on a page, make sure the value
  // you select is NOT the same as the form ID used in your form declaration.
  $table_id = 'profile-types-table';

  // We can render our tabledrag table for output.
  $output = theme('table', array(
    'header' => $header,
    'rows' => $rows,
    'attributes' => array('id' => $table_id),
  ));

  // And then render any remaining form elements (such as our submit button).
  $output .= drupal_render_children($form);

  // We now call the drupal_add_tabledrag() function in order to add the
  // tabledrag.js goodness onto our page.
  //
  // For a basic sortable table, we need to pass it:
  // - the $table_id of our <table> element,
  // - the $action to be performed on our form items ('order'),
  // - a string describing where $action should be applied ('siblings'),
  // - and the class of the element containing our 'weight' element.
  drupal_add_tabledrag($table_id, 'order', 'sibling', 'profile-type-weight');

  return $output;
}

/**
 * Submit callback for the registration_wizard_admin_form form.
 *
 * Updates the 'weight' column for each element in our table, taking into
 * account that item's new order after the drag and drop actions have been
 * performed.
 *
 * @ingroup tabledrag_example
 */
function registration_wizard_admin_form_submit($form, &$form_state) {
  // Because the form elements were keyed with the item ids from the database,
  // we can simply iterate through the submitted values.
  $profile_type_wizard = $form_state['values']['profile_type_items'];
  variable_set('cowpro_registration_wizard', $profile_type_wizard);
}
