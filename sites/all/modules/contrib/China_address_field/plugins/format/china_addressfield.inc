<?php

/**
 * @file
 * A specific handler for CH.
 */

$plugin = array(
  'title' => t('Address form (CN add-on from China Address Field Advanced)'),
  'format callback' => 'addressfield_format_address_cn_generate_advanced',
  'type' => 'address',
  'weight' => -80,
);

/**
 * Plugin for Address Field.
 */
function addressfield_format_address_cn_generate_advanced(&$format, $address, $context = array()) {
  if ($address['country'] == 'CN' && $context['mode'] == 'form') {
    global $language;
    //$langcode = !empty($address['data']) ? $address['data'] : $language->language;
    $langcode = $language->language;
    //dsm($langcode);

    $provinces = china_address_api_get_province_list($langcode);
    $province = !empty($address['administrative_area']) && in_array($address['administrative_area'], $provinces) ? $address['administrative_area'] : reset($provinces);

    $cities = china_address_api_get_city_list_by_name($province, $langcode);
    $city = !empty($address['locality']) && in_array($address['locality'], $cities) ? $address['locality'] : reset($cities);

    $counties = china_address_api_get_county_list_by_name($city, $langcode);
    $county = empty($address['thoroughfare']) && in_array($address['thoroughfare'], $counties) ? $address['thoroughfare'] : reset($counties);

    $format['locality_block'] = array(
      '#type' => 'addressfield_container',
      '#attributes' => array(
        'class' => array(
          'addressfield-container-inline',
          'locality-block',
          'country-' . $address['country'],
        ),
      ),
      '#weight' => 0,
    );
    $format['locality_block']['administrative_area'] = array(
      '#type' => 'select',
      '#title' => t('Province'),
      '#options' => $provinces,
      '#default_value' => 'Jiangsu',
      '#prefix' => '<div class="china-address province">',
      '#suffix' => '</div>',
      '#required' => TRUE,
      '#attached' => array(
        'css' => array(
          array(
            'data' => '.china-address .form-item {float:left;margin-right:10px;}',
            'type' => 'inline',
          ),
        ),
      ),
    );
    $format['locality_block']['locality'] = array(
      '#type' => 'select',
      '#title' => t('City'),
      '#default_value' => $city,
      '#options' => $cities,
      '#prefix' => '<div class="china-address city">',
      '#suffix' => '</div>',
    );
    unset($format['street_block']['thoroughfare']);
    $format['locality_block']['thoroughfare'] = array(
      '#type' => 'select',
      '#title' => t('County'),
      '#options' => $counties,
      '#default_value' => $county,
      '#prefix' => '<div class="china-address county">',
      '#suffix' => '</div>',
    );

    $format['street_block']['premise'] = array(
      '#type' => 'textfield',
      '#title' => t('Detail'),
      '#size' => 30,
      '#required' => TRUE,
    );

    unset($format['locality_block']['postal_code']);
    $format['street_block']['postal_code'] = array(
      '#type' => 'textfield',
      '#title' => t('Postal Code'),
      '#size' => 10,
    );
    $format['data'] = array(
      '#type' => 'value',
      '#value' => $language->language,
    );

    $format['locality_block']['administrative_area']['#wrapper_id'] = $format['#wrapper_id'];
    $format['locality_block']['administrative_area']['#process'][] = 'ajax_process_form';
    $format['locality_block']['administrative_area']['#process'][] = 'addressfield_format_address_cn_province_process1';
    $format['locality_block']['administrative_area']['#ajax'] = array(
      'callback' => 'addressfield_standard_widget_refresh',
      'wrapper' => $format['#wrapper_id'],
      'method' => 'replace',
    );

    $format['locality_block']['locality']['#wrapper_id'] = $format['#wrapper_id'];
    $format['locality_block']['locality']['#process'][] = 'ajax_process_form';
    $format['locality_block']['locality']['#process'][] = 'addressfield_format_address_cn_province_process1';
    $format['locality_block']['locality']['#ajax'] = array(
      'callback' => 'addressfield_standard_widget_refresh',
      'wrapper' => $format['#wrapper_id'],
      'method' => 'replace',
    );
  }
  else {
    if (isset($format['locality_block']['postal_code'])) {
      // Cancel the AJAX for forms we don't control.
      $format['locality_block']['postal_code']['#ajax'] = array();
    }
  }
}

/**
 * Something.
 */
function addressfield_format_address_cn_postal_code_process1($element) {
  $element['#limit_validation_errors'] = array($element['#parents']);

  return $element;
}

/**
 * Helper function.
 */
function addressfield_format_address_cn_province_process1($element) {
  $element['#limit_validation_errors'] = array($element['#parents']);

  return $element;
}

