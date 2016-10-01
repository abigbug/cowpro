<?php
/**
 * @file
 * cowpro_features.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function cowpro_features_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "field_group" && $api == "field_group") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_node_info().
 */
function cowpro_features_node_info() {
  $items = array(
    'article' => array(
      'name' => t('文章'),
      'base' => 'node_content',
      'description' => t('使用<em>文章</em>发布有关时间的内容，如消息，新闻或日志。'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'contract_credit_assignment' => array(
      'name' => t('转让合同范本'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('转让合同范本'),
      'help' => '',
    ),
    'contract_loan' => array(
      'name' => t('借款合同范本'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('借款合同范本'),
      'help' => '',
    ),
    'cowpro_issuing' => array(
      'name' => t('贷款申请表'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('贷款名称'),
      'help' => '',
    ),
    'page' => array(
      'name' => t('基本页面'),
      'base' => 'node_content',
      'description' => t('对您的静态内容使用<em>基本页面</em>，比如“关于我们”页面。'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
