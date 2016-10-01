<?php
/**
 * @file
 * cowpro_menus.features.menu_links.inc
 */

/**
 * Implements hook_menu_default_menu_links().
 */
function cowpro_menus_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: main-menu_:<front>.
  $menu_links['main-menu_:<front>'] = array(
    'menu_name' => 'main-menu',
    'link_path' => '<front>',
    'router_path' => '',
    'link_title' => '首页',
    'options' => array(
      'identifier' => 'main-menu_:<front>',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 1,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -50,
    'customized' => 1,
  );
  // Exported menu link: main-menu_:issuing-list.
  $menu_links['main-menu_:issuing-list'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'issuing-list',
    'router_path' => 'issuing-list',
    'link_title' => '我要投资',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'main-menu_:issuing-list',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -49,
    'customized' => 1,
  );
  // Exported menu link: main-menu_:node/1.
  $menu_links['main-menu_:node/1'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'node/1',
    'router_path' => 'node/%',
    'link_title' => '关于我们',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'main-menu_:node/1',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -47,
    'customized' => 1,
  );
  // Exported menu link: main-menu_:node/add/cowpro-issuing.
  $menu_links['main-menu_:node/add/cowpro-issuing'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'node/add/cowpro-issuing',
    'router_path' => 'node/add/cowpro-issuing',
    'link_title' => '我要贷款',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'main-menu_:node/add/cowpro-issuing',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -48,
    'customized' => 1,
  );
  // Exported menu link: management_-name:admin/cowpro/customer-profiles/add/employment.
  $menu_links['management_-name:admin/cowpro/customer-profiles/add/employment'] = array(
    'menu_name' => 'management',
    'link_path' => 'admin/cowpro/customer-profiles/add/employment',
    'router_path' => 'admin/cowpro/customer-profiles/add/employment',
    'link_title' => '新增 @name',
    'options' => array(
      'attributes' => array(
        'title' => '您的工作状况是评估您信用状况的主要依据。请您填写真实可靠的工作信息。',
      ),
      'identifier' => 'management_-name:admin/cowpro/customer-profiles/add/employment',
    ),
    'module' => 'system',
    'hidden' => 1,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 1,
    'parent_identifier' => 'management_:admin/cowpro/customer-profiles/add',
  );
  // Exported menu link: management_-name:admin/cowpro/customer-profiles/add/mobile.
  $menu_links['management_-name:admin/cowpro/customer-profiles/add/mobile'] = array(
    'menu_name' => 'management',
    'link_path' => 'admin/cowpro/customer-profiles/add/mobile',
    'router_path' => 'admin/cowpro/customer-profiles/add/mobile',
    'link_title' => '新增 @name',
    'options' => array(
      'attributes' => array(
        'title' => '通过手机短信验证码的形式，对用户提供的手机号进行认证。',
      ),
      'identifier' => 'management_-name:admin/cowpro/customer-profiles/add/mobile',
    ),
    'module' => 'system',
    'hidden' => 1,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 1,
    'parent_identifier' => 'management_:admin/cowpro/customer-profiles/add',
  );
  // Exported menu link: management_-name:admin/cowpro/customer-profiles/add/moneymoremore.
  $menu_links['management_-name:admin/cowpro/customer-profiles/add/moneymoremore'] = array(
    'menu_name' => 'management',
    'link_path' => 'admin/cowpro/customer-profiles/add/moneymoremore',
    'router_path' => 'admin/cowpro/customer-profiles/add/moneymoremore',
    'link_title' => '新增 @name',
    'options' => array(
      'attributes' => array(
        'title' => '在乾多多网站上开通第三方托管账户，并与我们P2P平台上的用户进行关联。',
      ),
      'identifier' => 'management_-name:admin/cowpro/customer-profiles/add/moneymoremore',
    ),
    'module' => 'system',
    'hidden' => 1,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 1,
    'parent_identifier' => 'management_:admin/cowpro/customer-profiles/add',
  );
  // Exported menu link: management_-name:admin/cowpro/customer-profiles/add/real-name.
  $menu_links['management_-name:admin/cowpro/customer-profiles/add/real-name'] = array(
    'menu_name' => 'management',
    'link_path' => 'admin/cowpro/customer-profiles/add/real-name',
    'router_path' => 'admin/cowpro/customer-profiles/add/real-name',
    'link_title' => '新增 @name',
    'options' => array(
      'attributes' => array(
        'title' => '此项为必要信用认证，上传齐全后将开始审核。必要认证缺失的用户，无法得到贷款。',
      ),
      'identifier' => 'management_-name:admin/cowpro/customer-profiles/add/real-name',
    ),
    'module' => 'system',
    'hidden' => 1,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 1,
    'parent_identifier' => 'management_:admin/cowpro/customer-profiles/add',
  );
  // Exported menu link: management_:admin/cowpro/config_custodian.
  $menu_links['management_:admin/cowpro/config_custodian'] = array(
    'menu_name' => 'management',
    'link_path' => 'admin/cowpro/config_custodian',
    'router_path' => 'admin/cowpro/config_custodian',
    'link_title' => '选择第三方托管服务商',
    'options' => array(
      'attributes' => array(
        'title' => '指定第三方资金托管服务商',
      ),
      'identifier' => 'management_:admin/cowpro/config_custodian',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 0,
    'parent_identifier' => 'management_p2p:admin/cowpro',
  );
  // Exported menu link: management_:admin/cowpro/config_general.
  $menu_links['management_:admin/cowpro/config_general'] = array(
    'menu_name' => 'management',
    'link_path' => 'admin/cowpro/config_general',
    'router_path' => 'admin/cowpro/config_general',
    'link_title' => '常规',
    'options' => array(
      'attributes' => array(
        'title' => '与平台相关的一些参数项，可以在这里设置',
      ),
      'identifier' => 'management_:admin/cowpro/config_general',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -48,
    'customized' => 1,
    'parent_identifier' => 'management_p2p:admin/cowpro',
  );
  // Exported menu link: management_:admin/cowpro/config_issuing.
  $menu_links['management_:admin/cowpro/config_issuing'] = array(
    'menu_name' => 'management',
    'link_path' => 'admin/cowpro/config_issuing',
    'router_path' => 'admin/cowpro/config_issuing',
    'link_title' => '贷款申请表参数',
    'options' => array(
      'attributes' => array(
        'title' => '配置与《贷款申请表》有关的参数',
      ),
      'identifier' => 'management_:admin/cowpro/config_issuing',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -47,
    'customized' => 1,
    'parent_identifier' => 'management_p2p:admin/cowpro',
  );
  // Exported menu link: management_:admin/cowpro/config_mobile_certification.
  $menu_links['management_:admin/cowpro/config_mobile_certification'] = array(
    'menu_name' => 'management',
    'link_path' => 'admin/cowpro/config_mobile_certification',
    'router_path' => 'admin/cowpro/config_mobile_certification',
    'link_title' => '手机认证短信模板',
    'options' => array(
      'attributes' => array(
        'title' => '设置手机认证短信的内容',
      ),
      'identifier' => 'management_:admin/cowpro/config_mobile_certification',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -43,
    'customized' => 1,
    'parent_identifier' => 'management_p2p:admin/cowpro',
  );
  // Exported menu link: management_:admin/cowpro/config_real_name_certification.
  $menu_links['management_:admin/cowpro/config_real_name_certification'] = array(
    'menu_name' => 'management',
    'link_path' => 'admin/cowpro/config_real_name_certification',
    'router_path' => 'admin/cowpro/config_real_name_certification',
    'link_title' => '实名认证设置',
    'options' => array(
      'attributes' => array(
        'title' => '设置实名认证所需要的材料',
      ),
      'identifier' => 'management_:admin/cowpro/config_real_name_certification',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 0,
    'parent_identifier' => 'management_p2p:admin/cowpro',
  );
  // Exported menu link: management_:admin/cowpro/config_registration_wizard.
  $menu_links['management_:admin/cowpro/config_registration_wizard'] = array(
    'menu_name' => 'management',
    'link_path' => 'admin/cowpro/config_registration_wizard',
    'router_path' => 'admin/cowpro/config_registration_wizard',
    'link_title' => '注册向导设置',
    'options' => array(
      'attributes' => array(
        'title' => '设置用户注册时需要填写的信息及步骤',
      ),
      'identifier' => 'management_:admin/cowpro/config_registration_wizard',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 0,
    'parent_identifier' => 'management_p2p:admin/cowpro',
  );
  // Exported menu link: management_:admin/cowpro/config_sms_message.
  $menu_links['management_:admin/cowpro/config_sms_message'] = array(
    'menu_name' => 'management',
    'link_path' => 'admin/cowpro/config_sms_message',
    'router_path' => 'admin/cowpro/config_sms_message',
    'link_title' => '贷款业务短信模板',
    'options' => array(
      'attributes' => array(
        'title' => '设置贷款业务提醒短信的内容',
      ),
      'identifier' => 'management_:admin/cowpro/config_sms_message',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -42,
    'customized' => 1,
    'parent_identifier' => 'management_p2p:admin/cowpro',
  );
  // Exported menu link: management_:admin/cowpro/config_sms_ylxf.
  $menu_links['management_:admin/cowpro/config_sms_ylxf'] = array(
    'menu_name' => 'management',
    'link_path' => 'admin/cowpro/config_sms_ylxf',
    'router_path' => 'admin/cowpro/config_sms_ylxf',
    'link_title' => '屹立雄风接口设置',
    'options' => array(
      'attributes' => array(
        'title' => '设置屹立雄风短信接口的参数',
      ),
      'identifier' => 'management_:admin/cowpro/config_sms_ylxf',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -45,
    'customized' => 1,
    'parent_identifier' => 'management_p2p:admin/cowpro',
  );
  // Exported menu link: management_:admin/cowpro/config_sms_ylxf_test.
  $menu_links['management_:admin/cowpro/config_sms_ylxf_test'] = array(
    'menu_name' => 'management',
    'link_path' => 'admin/cowpro/config_sms_ylxf_test',
    'router_path' => 'admin/cowpro/config_sms_ylxf_test',
    'link_title' => '屹立雄风接口测试',
    'options' => array(
      'attributes' => array(
        'title' => '向手机发送测试短信以便检查短信接口的参数设置是否正确',
      ),
      'identifier' => 'management_:admin/cowpro/config_sms_ylxf_test',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -44,
    'customized' => 1,
    'parent_identifier' => 'management_p2p:admin/cowpro',
  );
  // Exported menu link: management_:admin/cowpro/customer-profiles/add.
  $menu_links['management_:admin/cowpro/customer-profiles/add'] = array(
    'menu_name' => 'management',
    'link_path' => 'admin/cowpro/customer-profiles/add',
    'router_path' => 'admin/cowpro/customer-profiles/add',
    'link_title' => '添加用户资料',
    'options' => array(
      'attributes' => array(
        'title' => 'Add a new customer profile.',
      ),
      'identifier' => 'management_:admin/cowpro/customer-profiles/add',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -49,
    'customized' => 1,
    'parent_identifier' => 'management_p2p:admin/cowpro',
  );
  // Exported menu link: management_:admin/cowpro/customer-profiles/list.
  $menu_links['management_:admin/cowpro/customer-profiles/list'] = array(
    'menu_name' => 'management',
    'link_path' => 'admin/cowpro/customer-profiles/list',
    'router_path' => 'admin/cowpro/customer-profiles/list',
    'link_title' => '浏览用户资料',
    'options' => array(
      'identifier' => 'management_:admin/cowpro/customer-profiles/list',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -50,
    'customized' => 1,
    'parent_identifier' => 'management_p2p:admin/cowpro',
  );
  // Exported menu link: management_:admin/structure/menu/manage/main-menu.
  $menu_links['management_:admin/structure/menu/manage/main-menu'] = array(
    'menu_name' => 'management',
    'link_path' => 'admin/structure/menu/manage/main-menu',
    'router_path' => 'admin/structure/menu/manage/%',
    'link_title' => '主菜单',
    'options' => array(
      'identifier' => 'management_:admin/structure/menu/manage/main-menu',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 0,
    'parent_identifier' => 'management_:admin/structure/menu',
  );
  // Exported menu link: management_:admin/structure/menu/manage/navigation.
  $menu_links['management_:admin/structure/menu/manage/navigation'] = array(
    'menu_name' => 'management',
    'link_path' => 'admin/structure/menu/manage/navigation',
    'router_path' => 'admin/structure/menu/manage/%',
    'link_title' => '导航',
    'options' => array(
      'identifier' => 'management_:admin/structure/menu/manage/navigation',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 0,
    'parent_identifier' => 'management_:admin/structure/menu',
  );
  // Exported menu link: management_appearance:admin/appearance.
  $menu_links['management_appearance:admin/appearance'] = array(
    'menu_name' => 'management',
    'link_path' => 'admin/appearance',
    'router_path' => 'admin/appearance',
    'link_title' => 'Appearance',
    'options' => array(
      'attributes' => array(
        'title' => 'Select and configure your themes.',
      ),
      'identifier' => 'management_appearance:admin/appearance',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -45,
    'customized' => 1,
    'parent_identifier' => 'management_:admin',
  );
  // Exported menu link: management_configuration:admin/config.
  $menu_links['management_configuration:admin/config'] = array(
    'menu_name' => 'management',
    'link_path' => 'admin/config',
    'router_path' => 'admin/config',
    'link_title' => 'Configuration',
    'options' => array(
      'attributes' => array(
        'title' => 'Administer settings.',
      ),
      'identifier' => 'management_configuration:admin/config',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 0,
    'weight' => -41,
    'customized' => 1,
    'parent_identifier' => 'management_:admin',
  );
  // Exported menu link: management_content:admin/content.
  $menu_links['management_content:admin/content'] = array(
    'menu_name' => 'management',
    'link_path' => 'admin/content',
    'router_path' => 'admin/content',
    'link_title' => 'Content',
    'options' => array(
      'attributes' => array(
        'title' => 'Administer content and comments.',
      ),
      'identifier' => 'management_content:admin/content',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 0,
    'weight' => -48,
    'customized' => 1,
    'parent_identifier' => 'management_:admin',
  );
  // Exported menu link: management_dashboard:admin/dashboard.
  $menu_links['management_dashboard:admin/dashboard'] = array(
    'menu_name' => 'management',
    'link_path' => 'admin/dashboard',
    'router_path' => 'admin/dashboard',
    'link_title' => 'Dashboard',
    'options' => array(
      'attributes' => array(
        'title' => 'View and customize your dashboard.',
      ),
      'identifier' => 'management_dashboard:admin/dashboard',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -49,
    'customized' => 1,
    'parent_identifier' => 'management_:admin',
  );
  // Exported menu link: management_help:admin/help.
  $menu_links['management_help:admin/help'] = array(
    'menu_name' => 'management',
    'link_path' => 'admin/help',
    'router_path' => 'admin/help',
    'link_title' => 'Help',
    'options' => array(
      'attributes' => array(
        'title' => 'Reference for usage, configuration, and modules.',
      ),
      'identifier' => 'management_help:admin/help',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -39,
    'customized' => 1,
    'parent_identifier' => 'management_:admin',
  );
  // Exported menu link: management_management:admin/structure/menu/manage/management.
  $menu_links['management_management:admin/structure/menu/manage/management'] = array(
    'menu_name' => 'management',
    'link_path' => 'admin/structure/menu/manage/management',
    'router_path' => 'admin/structure/menu/manage/%',
    'link_title' => 'Management',
    'options' => array(
      'identifier' => 'management_management:admin/structure/menu/manage/management',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 0,
    'parent_identifier' => 'management_:admin/structure/menu',
  );
  // Exported menu link: management_modules:admin/modules.
  $menu_links['management_modules:admin/modules'] = array(
    'menu_name' => 'management',
    'link_path' => 'admin/modules',
    'router_path' => 'admin/modules',
    'link_title' => 'Modules',
    'options' => array(
      'attributes' => array(
        'title' => 'Extend site functionality.',
      ),
      'identifier' => 'management_modules:admin/modules',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -43,
    'customized' => 1,
    'parent_identifier' => 'management_:admin',
  );
  // Exported menu link: management_p2p:admin/cowpro.
  $menu_links['management_p2p:admin/cowpro'] = array(
    'menu_name' => 'management',
    'link_path' => 'admin/cowpro',
    'router_path' => 'admin/cowpro',
    'link_title' => 'P2P平台管理',
    'options' => array(
      'attributes' => array(
        'title' => 'P2P网贷平台管理',
      ),
      'identifier' => 'management_p2p:admin/cowpro',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 0,
    'weight' => -50,
    'customized' => 1,
    'parent_identifier' => 'management_:admin',
  );
  // Exported menu link: management_people:admin/people.
  $menu_links['management_people:admin/people'] = array(
    'menu_name' => 'management',
    'link_path' => 'admin/people',
    'router_path' => 'admin/people',
    'link_title' => 'People',
    'options' => array(
      'attributes' => array(
        'title' => 'Manage user accounts, roles, and permissions.',
      ),
      'identifier' => 'management_people:admin/people',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -44,
    'customized' => 1,
    'parent_identifier' => 'management_:admin',
  );
  // Exported menu link: management_reports:admin/reports.
  $menu_links['management_reports:admin/reports'] = array(
    'menu_name' => 'management',
    'link_path' => 'admin/reports',
    'router_path' => 'admin/reports',
    'link_title' => 'Reports',
    'options' => array(
      'attributes' => array(
        'title' => 'View reports, updates, and errors.',
      ),
      'identifier' => 'management_reports:admin/reports',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 0,
    'weight' => -40,
    'customized' => 1,
    'parent_identifier' => 'management_:admin',
  );
  // Exported menu link: management_status-report:admin/reports/status.
  $menu_links['management_status-report:admin/reports/status'] = array(
    'menu_name' => 'management',
    'link_path' => 'admin/reports/status',
    'router_path' => 'admin/reports/status',
    'link_title' => 'Status report',
    'options' => array(
      'attributes' => array(
        'title' => 'Get a status report about your site\'s operation and any detected problems.',
      ),
      'identifier' => 'management_status-report:admin/reports/status',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -50,
    'customized' => 1,
    'parent_identifier' => 'management_:admin/reports',
  );
  // Exported menu link: management_structure:admin/structure.
  $menu_links['management_structure:admin/structure'] = array(
    'menu_name' => 'management',
    'link_path' => 'admin/structure',
    'router_path' => 'admin/structure',
    'link_title' => 'Structure',
    'options' => array(
      'attributes' => array(
        'title' => 'Administer blocks, content types, menus, etc.',
      ),
      'identifier' => 'management_structure:admin/structure',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 0,
    'weight' => -46,
    'customized' => 1,
    'parent_identifier' => 'management_:admin',
  );
  // Exported menu link: management_user-menu:admin/structure/menu/manage/user-menu.
  $menu_links['management_user-menu:admin/structure/menu/manage/user-menu'] = array(
    'menu_name' => 'management',
    'link_path' => 'admin/structure/menu/manage/user-menu',
    'router_path' => 'admin/structure/menu/manage/%',
    'link_title' => 'User menu',
    'options' => array(
      'identifier' => 'management_user-menu:admin/structure/menu/manage/user-menu',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 0,
    'parent_identifier' => 'management_:admin/structure/menu',
  );
  // Exported menu link: management_views-megarow-configuration:admin/config/user-interface/views_megarow.
  $menu_links['management_views-megarow-configuration:admin/config/user-interface/views_megarow'] = array(
    'menu_name' => 'management',
    'link_path' => 'admin/config/user-interface/views_megarow',
    'router_path' => 'admin/config/user-interface/views_megarow',
    'link_title' => 'Views Megarow configuration',
    'options' => array(
      'attributes' => array(
        'title' => 'Options for Views Megarow settings',
      ),
      'identifier' => 'management_views-megarow-configuration:admin/config/user-interface/views_megarow',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 0,
    'parent_identifier' => 'management_:admin/config/user-interface',
  );
  // Exported menu link: navigation_:admin/people.
  $menu_links['navigation_:admin/people'] = array(
    'menu_name' => 'navigation',
    'link_path' => 'admin/people',
    'router_path' => 'admin/people',
    'link_title' => '用户管理',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'navigation_:admin/people',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -44,
    'customized' => 1,
  );
  // Exported menu link: navigation_:article-list.
  $menu_links['navigation_:article-list'] = array(
    'menu_name' => 'navigation',
    'link_path' => 'article-list',
    'router_path' => 'article-list',
    'link_title' => '内容管理',
    'options' => array(
      'identifier' => 'navigation_:article-list',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 0,
    'weight' => -46,
    'customized' => 1,
  );
  // Exported menu link: navigation_:contract-list.
  $menu_links['navigation_:contract-list'] = array(
    'menu_name' => 'navigation',
    'link_path' => 'contract-list',
    'router_path' => 'contract-list',
    'link_title' => '合同管理',
    'options' => array(
      'identifier' => 'navigation_:contract-list',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 0,
    'weight' => -45,
    'customized' => 1,
  );
  // Exported menu link: navigation_:creditor-assignment.
  $menu_links['navigation_:creditor-assignment'] = array(
    'menu_name' => 'navigation',
    'link_path' => 'creditor-assignment',
    'router_path' => 'creditor-assignment',
    'link_title' => '债权转让',
    'options' => array(
      'identifier' => 'navigation_:creditor-assignment',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -47,
    'customized' => 1,
  );
  // Exported menu link: navigation_:issuing-list.
  $menu_links['navigation_:issuing-list'] = array(
    'menu_name' => 'navigation',
    'link_path' => 'issuing-list',
    'router_path' => 'issuing-list',
    'link_title' => '全部贷款',
    'options' => array(
      'identifier' => 'navigation_:issuing-list',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 0,
    'weight' => -49,
    'customized' => 1,
  );
  // Exported menu link: navigation_:issuing-list/debtor.
  $menu_links['navigation_:issuing-list/debtor'] = array(
    'menu_name' => 'navigation',
    'link_path' => 'issuing-list/debtor',
    'router_path' => 'issuing-list/debtor',
    'link_title' => '我的贷款',
    'options' => array(
      'identifier' => 'navigation_:issuing-list/debtor',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 0,
    'parent_identifier' => 'navigation_:issuing-list',
  );
  // Exported menu link: navigation_:issuing-list/lender.
  $menu_links['navigation_:issuing-list/lender'] = array(
    'menu_name' => 'navigation',
    'link_path' => 'issuing-list/lender',
    'router_path' => 'issuing-list/lender',
    'link_title' => '我的投资',
    'options' => array(
      'identifier' => 'navigation_:issuing-list/lender',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 0,
    'parent_identifier' => 'navigation_:issuing-list',
  );
  // Exported menu link: navigation_:issuing-manage.
  $menu_links['navigation_:issuing-manage'] = array(
    'menu_name' => 'navigation',
    'link_path' => 'issuing-manage',
    'router_path' => 'issuing-manage',
    'link_title' => '贷款管理',
    'options' => array(
      'identifier' => 'navigation_:issuing-manage',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 0,
    'weight' => -48,
    'customized' => 1,
  );
  // Exported menu link: navigation_:issuing-manage/unaudited.
  $menu_links['navigation_:issuing-manage/unaudited'] = array(
    'menu_name' => 'navigation',
    'link_path' => 'issuing-manage/unaudited',
    'router_path' => 'issuing-manage/unaudited',
    'link_title' => '待审核',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'navigation_:issuing-manage/unaudited',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -50,
    'customized' => 1,
    'parent_identifier' => 'navigation_:issuing-manage',
  );
  // Exported menu link: navigation_:node/add/article.
  $menu_links['navigation_:node/add/article'] = array(
    'menu_name' => 'navigation',
    'link_path' => 'node/add/article',
    'router_path' => 'node/add/article',
    'link_title' => '文章',
    'options' => array(
      'attributes' => array(
        'title' => '使用<em>文章</em>发布有关时间的内容，如消息，新闻或日志。',
      ),
      'identifier' => 'navigation_:node/add/article',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -50,
    'customized' => 1,
    'parent_identifier' => 'navigation_:article-list',
  );
  // Exported menu link: navigation_:node/add/contract-credit-assignment.
  $menu_links['navigation_:node/add/contract-credit-assignment'] = array(
    'menu_name' => 'navigation',
    'link_path' => 'node/add/contract-credit-assignment',
    'router_path' => 'node/add/contract-credit-assignment',
    'link_title' => '转让合同范本',
    'options' => array(
      'identifier' => 'navigation_:node/add/contract-credit-assignment',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -49,
    'customized' => 1,
    'parent_identifier' => 'navigation_:contract-list',
  );
  // Exported menu link: navigation_:node/add/contract-loan.
  $menu_links['navigation_:node/add/contract-loan'] = array(
    'menu_name' => 'navigation',
    'link_path' => 'node/add/contract-loan',
    'router_path' => 'node/add/contract-loan',
    'link_title' => '借款合同范本',
    'options' => array(
      'identifier' => 'navigation_:node/add/contract-loan',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -50,
    'customized' => 1,
    'parent_identifier' => 'navigation_:contract-list',
  );
  // Exported menu link: navigation_:node/add/cowpro-issuing.
  $menu_links['navigation_:node/add/cowpro-issuing'] = array(
    'menu_name' => 'navigation',
    'link_path' => 'node/add/cowpro-issuing',
    'router_path' => 'node/add/cowpro-issuing',
    'link_title' => '我要贷款',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'navigation_:node/add/cowpro-issuing',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -50,
    'customized' => 1,
  );
  // Exported menu link: navigation_:node/add/page.
  $menu_links['navigation_:node/add/page'] = array(
    'menu_name' => 'navigation',
    'link_path' => 'node/add/page',
    'router_path' => 'node/add/page',
    'link_title' => '基本页面',
    'options' => array(
      'attributes' => array(
        'title' => '对您的静态内容使用<em>基本页面</em>，比如“关于我们”页面。',
      ),
      'identifier' => 'navigation_:node/add/page',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -49,
    'customized' => 1,
    'parent_identifier' => 'navigation_:article-list',
  );
  // Exported menu link: navigation_:registration_wizard.
  $menu_links['navigation_:registration_wizard'] = array(
    'menu_name' => 'navigation',
    'link_path' => 'registration_wizard',
    'router_path' => 'registration_wizard',
    'link_title' => '个人资料填写向导',
    'options' => array(
      'identifier' => 'navigation_:registration_wizard',
    ),
    'module' => 'system',
    'hidden' => 1,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -40,
    'customized' => 1,
  );
  // Exported menu link: navigation_add-content:node/add.
  $menu_links['navigation_add-content:node/add'] = array(
    'menu_name' => 'navigation',
    'link_path' => 'node/add',
    'router_path' => 'node/add',
    'link_title' => 'Add content',
    'options' => array(
      'identifier' => 'navigation_add-content:node/add',
    ),
    'module' => 'system',
    'hidden' => 1,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -41,
    'customized' => 1,
  );
  // Exported menu link: navigation_compose-tips:filter/tips.
  $menu_links['navigation_compose-tips:filter/tips'] = array(
    'menu_name' => 'navigation',
    'link_path' => 'filter/tips',
    'router_path' => 'filter/tips',
    'link_title' => 'Compose tips',
    'options' => array(
      'identifier' => 'navigation_compose-tips:filter/tips',
    ),
    'module' => 'system',
    'hidden' => 1,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 0,
    'weight' => -42,
    'customized' => 1,
  );
  // Exported menu link: navigation_search:search.
  $menu_links['navigation_search:search'] = array(
    'menu_name' => 'navigation',
    'link_path' => 'search',
    'router_path' => 'search',
    'link_title' => 'Search',
    'options' => array(
      'identifier' => 'navigation_search:search',
    ),
    'module' => 'system',
    'hidden' => 1,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -43,
    'customized' => 1,
  );
  // Exported menu link: user-menu_:registration_wizard.
  $menu_links['user-menu_:registration_wizard'] = array(
    'menu_name' => 'user-menu',
    'link_path' => 'registration_wizard',
    'router_path' => 'registration_wizard',
    'link_title' => '个人资料填写向导',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'user-menu_:registration_wizard',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 1,
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Add content');
  t('Appearance');
  t('Compose tips');
  t('Configuration');
  t('Content');
  t('Dashboard');
  t('Help');
  t('Management');
  t('Modules');
  t('P2P平台管理');
  t('People');
  t('Reports');
  t('Search');
  t('Status report');
  t('Structure');
  t('User menu');
  t('Views Megarow configuration');
  t('个人资料填写向导');
  t('主菜单');
  t('借款合同范本');
  t('债权转让');
  t('全部贷款');
  t('关于我们');
  t('内容管理');
  t('合同管理');
  t('基本页面');
  t('实名认证设置');
  t('导航');
  t('屹立雄风接口测试');
  t('屹立雄风接口设置');
  t('常规');
  t('待审核');
  t('我的投资');
  t('我的贷款');
  t('我要投资');
  t('我要贷款');
  t('手机认证短信模板');
  t('文章');
  t('新增 @name');
  t('注册向导设置');
  t('浏览用户资料');
  t('添加用户资料');
  t('用户管理');
  t('贷款业务短信模板');
  t('贷款申请表参数');
  t('贷款管理');
  t('转让合同范本');
  t('选择第三方托管服务商');
  t('首页');

  return $menu_links;
}
