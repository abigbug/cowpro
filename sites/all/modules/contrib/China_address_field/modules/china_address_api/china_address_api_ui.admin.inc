<?php

function china_address_api_config_form($form, $form_state) {
  $form['address']['#tree'] = TRUE;
  $form['button'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );

  $results = db_select('china_address_api','c')
              ->fields('c', array('region_id', 'region_name_cn', 'weight', 'status'))
              ->condition('region_type', 1)
              ->orderBy('weight', 'ASC')
              ->execute()
              ->fetchAll();
  foreach($results as $row) {
    $form['address'][$row->region_id] = array(
      'name' => array(
        '#markup' => check_plain($row->region_name_cn),
      ),
      'weight' => array(
        '#type' => 'weight',
        '#title' => t('Weight'),
        '#default_value' => $row->weight,
        '#title-display' => 'invisible',
        '#delta' => 30,
      ),
      'status' => array(
        '#type' => 'checkbox',
        '#title' => t('Enable'),
        '#default_value' => $row->status,
      ),
    );
  }
  return $form;
};

function theme_china_address_api_config_form($vars) {
  $form = $vars['form'];
  $rows = array();
  foreach (element_children($form['address']) as $id) {
    $form['address'][$id]['weight']['#attributes']['class'] = array('china-address-element-weight');
    $rows[] = array(
      'data' => array(
        'name' => drupal_render($form['address'][$id]['name']),
        'status' => drupal_render($form['address'][$id]['status']),
        'weight' => drupal_render($form['address'][$id]['weight']),
      ),
      'class' => array('draggable'),
    );
  }
  $table_id = 'china-address-api-sort-form';
  $header = array(t('Region Name'), t('Status'), t('Weight'));
  $output = theme('table', array(
                'header' => $header,
                'rows' => $rows,
                'attributes' => array('id' => $table_id),
              )
            );
  $output .= drupal_render_children($form);
  drupal_add_tabledrag($table_id, 'order', 'sibling', 'china-address-element-weight');
  return $output;
}

function china_address_api_config_form_submit($form, $form_state) {
  foreach ($form_state['values']['address'] as $id => $item) {
    db_update('china_address_api')
      ->fields(array(
        'weight' => $item['weight'],
        'status' => $item['status'],
        ))
      ->condition('region_id', $id)
      ->execute();
  }
  //include(__DIR__ . '/china_address_api.install');
  //china_address_api_install();
  cache_clear_all('china_address_api', 'cache', '*');
}

