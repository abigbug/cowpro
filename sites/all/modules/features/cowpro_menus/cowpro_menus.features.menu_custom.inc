<?php
/**
 * @file
 * cowpro_menus.features.menu_custom.inc
 */

/**
 * Implements hook_menu_default_menu_custom().
 */
function cowpro_menus_menu_default_menu_custom() {
  $menus = array();

  // Exported menu: main-menu.
  $menus['main-menu'] = array(
    'menu_name' => 'main-menu',
    'title' => '主菜单',
    'description' => '<em>主</em>菜单在多数站点用于显示站点的主要部分，往往位于顶部导航栏。',
  );
  // Exported menu: management.
  $menus['management'] = array(
    'menu_name' => 'management',
    'title' => 'Management',
    'description' => '<em>管理</em>菜单包含管理任务的链接。',
  );
  // Exported menu: navigation.
  $menus['navigation'] = array(
    'menu_name' => 'navigation',
    'title' => '导航',
    'description' => '<em>导航</em>菜单包含供站点访问者使用的链接。一些模块会自动向<em>导航</em>菜单添加链接。',
  );
  // Exported menu: user-menu.
  $menus['user-menu'] = array(
    'menu_name' => 'user-menu',
    'title' => 'User menu',
    'description' => '<em>用户</em>菜单包含与用户帐户有关的链接，以及“注销”链接。',
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('<em>主</em>菜单在多数站点用于显示站点的主要部分，往往位于顶部导航栏。');
  t('<em>导航</em>菜单包含供站点访问者使用的链接。一些模块会自动向<em>导航</em>菜单添加链接。');
  t('<em>用户</em>菜单包含与用户帐户有关的链接，以及“注销”链接。');
  t('<em>管理</em>菜单包含管理任务的链接。');
  t('Management');
  t('User menu');
  t('主菜单');
  t('导航');

  return $menus;
}
