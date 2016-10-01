<?php
/**
 * @file
 * cowpro_views.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function cowpro_views_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'all_issuing';
  $view->description = '';
  $view->tag = 'cowpro';
  $view->base_table = 'node';
  $view->human_name = '贷款管理';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = '我的投资';
  $handler->display->display_options['use_ajax'] = TRUE;
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['use_more_text'] = '更多';
  $handler->display->display_options['access']['type'] = 'role';
  $handler->display->display_options['access']['role'] = array(
    3 => '3',
  );
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['submit_button'] = '应用';
  $handler->display->display_options['exposed_form']['options']['reset_button_label'] = '重置';
  $handler->display->display_options['exposed_form']['options']['exposed_sorts_label'] = '排序依据';
  $handler->display->display_options['exposed_form']['options']['sort_asc_label'] = '升序';
  $handler->display->display_options['exposed_form']['options']['sort_desc_label'] = '降序';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '20';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['quantity'] = '9';
  $handler->display->display_options['pager']['options']['expose']['items_per_page_label'] = '每页条目数';
  $handler->display->display_options['pager']['options']['expose']['items_per_page_options_all_label'] = '- 全部 -';
  $handler->display->display_options['pager']['options']['expose']['offset_label'] = '偏移量';
  $handler->display->display_options['pager']['options']['tags']['first'] = '|< 第一页';
  $handler->display->display_options['pager']['options']['tags']['previous'] = '< 前一页';
  $handler->display->display_options['pager']['options']['tags']['next'] = '下一页 >';
  $handler->display->display_options['pager']['options']['tags']['last'] = '末页 >|';
  $handler->display->display_options['style_plugin'] = 'table_megarows';
  $handler->display->display_options['style_options']['columns'] = array(
    'title' => 'title',
    'field_applicant' => 'field_applicant',
    'view_issuing' => 'view_issuing',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'title' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_applicant' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'view_issuing' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  $handler->display->display_options['style_options']['scroll_padding'] = '120';
  $handler->display->display_options['style_options']['loading_text'] = '正在加载...';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* 字段: 内容: 标题 */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* 字段: 内容: 申请人 */
  $handler->display->display_options['fields']['field_applicant']['id'] = 'field_applicant';
  $handler->display->display_options['fields']['field_applicant']['table'] = 'field_data_field_applicant';
  $handler->display->display_options['fields']['field_applicant']['field'] = 'field_applicant';
  $handler->display->display_options['fields']['field_applicant']['settings'] = array(
    'user_reference_view_mode' => 'full',
  );
  /* 字段: Issuing: 操作 */
  $handler->display->display_options['fields']['view_issuing']['id'] = 'view_issuing';
  $handler->display->display_options['fields']['view_issuing']['table'] = 'field_data_field_issuing';
  $handler->display->display_options['fields']['view_issuing']['field'] = 'view_issuing';
  $handler->display->display_options['fields']['view_issuing']['add_destination'] = 1;
  /* 排序标准: 内容: 发布日期 */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* 过滤规则: 内容: 类型 */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'cowpro_issuing' => 'cowpro_issuing',
  );
  /* 过滤规则: 内容: 贷款表 (field_issuing:status) */
  $handler->display->display_options['filters']['field_issuing_status']['id'] = 'field_issuing_status';
  $handler->display->display_options['filters']['field_issuing_status']['table'] = 'field_data_field_issuing';
  $handler->display->display_options['filters']['field_issuing_status']['field'] = 'field_issuing_status';
  $handler->display->display_options['filters']['field_issuing_status']['value'] = array(
    'INVITE_BIDS_START' => 'INVITE_BIDS_START',
  );

  /* Display: 贷款管理 */
  $handler = $view->new_display('page', '贷款管理', 'page');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = '贷款管理';
  $handler->display->display_options['defaults']['access'] = FALSE;
  $handler->display->display_options['access']['type'] = 'role';
  $handler->display->display_options['access']['role'] = array(
    3 => '3',
  );
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* 过滤规则: 内容: 类型 */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'cowpro_issuing' => 'cowpro_issuing',
  );
  $handler->display->display_options['path'] = 'issuing-manage';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = '贷款管理';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;

  /* Display: 正在投标的贷款 */
  $handler = $view->new_display('page', '正在投标的贷款', 'page_9');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = '正在投标的贷款';
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* 过滤规则: 内容: 类型 */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'cowpro_issuing' => 'cowpro_issuing',
  );
  /* 过滤规则: 内容: 贷款表 (field_issuing:status) */
  $handler->display->display_options['filters']['field_issuing_status']['id'] = 'field_issuing_status';
  $handler->display->display_options['filters']['field_issuing_status']['table'] = 'field_data_field_issuing';
  $handler->display->display_options['filters']['field_issuing_status']['field'] = 'field_issuing_status';
  $handler->display->display_options['filters']['field_issuing_status']['value'] = array(
    'INVITE_BIDS_START' => 'INVITE_BIDS_START',
  );
  $handler->display->display_options['path'] = 'issuing-manage/bidding';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = '投标中';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;

  /* Display: 待审核的贷款 */
  $handler = $view->new_display('page', '待审核的贷款', 'page_1');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = '待审核';
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* 过滤规则: 内容: 类型 */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'cowpro_issuing' => 'cowpro_issuing',
  );
  /* 过滤规则: 内容: 贷款表 (field_issuing:status) */
  $handler->display->display_options['filters']['field_issuing_status']['id'] = 'field_issuing_status';
  $handler->display->display_options['filters']['field_issuing_status']['table'] = 'field_data_field_issuing';
  $handler->display->display_options['filters']['field_issuing_status']['field'] = 'field_issuing_status';
  $handler->display->display_options['filters']['field_issuing_status']['value'] = array(
    'UNAUDITED' => 'UNAUDITED',
  );
  $handler->display->display_options['path'] = 'issuing-manage/unaudited';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = '待审核';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;

  /* Display: 已满标等待放款的贷款 */
  $handler = $view->new_display('page', '已满标等待放款的贷款', 'page_7');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = '已满标等待放款的贷款';
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* 过滤规则: 内容: 类型 */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'cowpro_issuing' => 'cowpro_issuing',
  );
  /* 过滤规则: 内容: 贷款表 (field_issuing:status) */
  $handler->display->display_options['filters']['field_issuing_status']['id'] = 'field_issuing_status';
  $handler->display->display_options['filters']['field_issuing_status']['table'] = 'field_data_field_issuing';
  $handler->display->display_options['filters']['field_issuing_status']['field'] = 'field_issuing_status';
  $handler->display->display_options['filters']['field_issuing_status']['value'] = array(
    'INVITE_BIDS_SUCCEED' => 'INVITE_BIDS_SUCCEED',
  );
  $handler->display->display_options['path'] = 'issuing-manage/succeed';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = '待放款';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;

  /* Display: 正在还款的贷款 */
  $handler = $view->new_display('page', '正在还款的贷款', 'page_8');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = '还款中';
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* 过滤规则: 内容: 类型 */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'cowpro_issuing' => 'cowpro_issuing',
  );
  /* 过滤规则: 内容: 贷款表 (field_issuing:status) */
  $handler->display->display_options['filters']['field_issuing_status']['id'] = 'field_issuing_status';
  $handler->display->display_options['filters']['field_issuing_status']['table'] = 'field_data_field_issuing';
  $handler->display->display_options['filters']['field_issuing_status']['field'] = 'field_issuing_status';
  $handler->display->display_options['filters']['field_issuing_status']['value'] = array(
    'REPAYMENT' => 'REPAYMENT',
  );
  $handler->display->display_options['path'] = 'issuing-manage/repayment';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = '还款中';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;

  /* Display: 已流标的贷款 */
  $handler = $view->new_display('page', '已流标的贷款', 'page_6');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = '已流标';
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* 过滤规则: 内容: 类型 */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'cowpro_issuing' => 'cowpro_issuing',
  );
  /* 过滤规则: 内容: 贷款表 (field_issuing:status) */
  $handler->display->display_options['filters']['field_issuing_status']['id'] = 'field_issuing_status';
  $handler->display->display_options['filters']['field_issuing_status']['table'] = 'field_data_field_issuing';
  $handler->display->display_options['filters']['field_issuing_status']['field'] = 'field_issuing_status';
  $handler->display->display_options['filters']['field_issuing_status']['value'] = array(
    'INVITE_BIDS_FAILED' => 'INVITE_BIDS_FAILED',
  );
  $handler->display->display_options['path'] = 'issuing-manage/failed';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = '已流标';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;

  /* Display: 全部贷款 */
  $handler = $view->new_display('page', '全部贷款', 'page_2');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = '全部贷款';
  $handler->display->display_options['defaults']['access'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* 过滤规则: 内容: 类型 */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'cowpro_issuing' => 'cowpro_issuing',
  );
  /* 过滤规则: 内容: 贷款表 (field_issuing:status) */
  $handler->display->display_options['filters']['field_issuing_status']['id'] = 'field_issuing_status';
  $handler->display->display_options['filters']['field_issuing_status']['table'] = 'field_data_field_issuing';
  $handler->display->display_options['filters']['field_issuing_status']['field'] = 'field_issuing_status';
  $handler->display->display_options['filters']['field_issuing_status']['operator'] = 'not in';
  $handler->display->display_options['filters']['field_issuing_status']['value'] = array(
    'UNAUDITED' => 'UNAUDITED',
  );
  $handler->display->display_options['path'] = 'issuing-list';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = '全部贷款';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;

  /* Display: 正在投标的贷款 */
  $handler = $view->new_display('page', '正在投标的贷款', 'page_5');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = '正在投标的贷款';
  $handler->display->display_options['defaults']['access'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['path'] = 'issuing-list/bidding';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = '投标中';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;

  /* Display: 我的贷款 */
  $handler = $view->new_display('page', '我的贷款', 'page_3');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = '我的贷款';
  $handler->display->display_options['defaults']['access'] = FALSE;
  $handler->display->display_options['access']['type'] = 'role';
  $handler->display->display_options['access']['role'] = array(
    5 => '5',
  );
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* 上下文过滤器: 内容: 申请人 (field_applicant)申请人 (field_applicant) */
  $handler->display->display_options['arguments']['field_applicant_uid']['id'] = 'field_applicant_uid';
  $handler->display->display_options['arguments']['field_applicant_uid']['table'] = 'field_data_field_applicant';
  $handler->display->display_options['arguments']['field_applicant_uid']['field'] = 'field_applicant_uid';
  $handler->display->display_options['arguments']['field_applicant_uid']['default_action'] = 'default';
  $handler->display->display_options['arguments']['field_applicant_uid']['exception']['title'] = '全部';
  $handler->display->display_options['arguments']['field_applicant_uid']['default_argument_type'] = 'current_user';
  $handler->display->display_options['arguments']['field_applicant_uid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['field_applicant_uid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['field_applicant_uid']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* 过滤规则: 内容: 类型 */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'cowpro_issuing' => 'cowpro_issuing',
  );
  $handler->display->display_options['path'] = 'issuing-list/debtor';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = '我的贷款';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;

  /* Display: 我的投资 */
  $handler = $view->new_display('page', '我的投资', 'page_4');
  $handler->display->display_options['defaults']['group_by'] = FALSE;
  $handler->display->display_options['group_by'] = TRUE;
  $handler->display->display_options['defaults']['access'] = FALSE;
  $handler->display->display_options['access']['type'] = 'role';
  $handler->display->display_options['access']['role'] = array(
    4 => '4',
  );
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* 上下文过滤器: 还款详情: 收款方 */
  $handler->display->display_options['arguments']['receiver_uid']['id'] = 'receiver_uid';
  $handler->display->display_options['arguments']['receiver_uid']['table'] = 'cowpro_repayment_schedule';
  $handler->display->display_options['arguments']['receiver_uid']['field'] = 'receiver_uid';
  $handler->display->display_options['arguments']['receiver_uid']['default_action'] = 'default';
  $handler->display->display_options['arguments']['receiver_uid']['exception']['title'] = '全部';
  $handler->display->display_options['arguments']['receiver_uid']['default_argument_type'] = 'current_user';
  $handler->display->display_options['arguments']['receiver_uid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['receiver_uid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['receiver_uid']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* 过滤规则: 内容: 类型 */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'cowpro_issuing' => 'cowpro_issuing',
  );
  $handler->display->display_options['path'] = 'issuing-list/lender';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = '我的投资';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;
  $translatables['all_issuing'] = array(
    t('Master'),
    t('我的投资'),
    t('更多'),
    t('应用'),
    t('重置'),
    t('排序依据'),
    t('升序'),
    t('降序'),
    t('每页条目数'),
    t('- 全部 -'),
    t('偏移量'),
    t('|< 第一页'),
    t('< 前一页'),
    t('下一页 >'),
    t('末页 >|'),
    t('申请人'),
    t('操作'),
    t('贷款管理'),
    t('正在投标的贷款'),
    t('待审核的贷款'),
    t('待审核'),
    t('已满标等待放款的贷款'),
    t('正在还款的贷款'),
    t('还款中'),
    t('已流标的贷款'),
    t('已流标'),
    t('全部贷款'),
    t('我的贷款'),
    t('全部'),
  );
  $export['all_issuing'] = $view;

  $view = new view();
  $view->name = 'article_list';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = '内容管理';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = '内容管理';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['use_more_text'] = '更多';
  $handler->display->display_options['access']['type'] = 'role';
  $handler->display->display_options['access']['role'] = array(
    3 => '3',
  );
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['submit_button'] = '应用';
  $handler->display->display_options['exposed_form']['options']['reset_button_label'] = '重置';
  $handler->display->display_options['exposed_form']['options']['exposed_sorts_label'] = '排序依据';
  $handler->display->display_options['exposed_form']['options']['sort_asc_label'] = '升序';
  $handler->display->display_options['exposed_form']['options']['sort_desc_label'] = '降序';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '20';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['quantity'] = '9';
  $handler->display->display_options['pager']['options']['expose']['items_per_page_label'] = '每页条目数';
  $handler->display->display_options['pager']['options']['expose']['items_per_page_options_all_label'] = '- 全部 -';
  $handler->display->display_options['pager']['options']['expose']['offset_label'] = '偏移量';
  $handler->display->display_options['pager']['options']['tags']['first'] = '|< 第一页';
  $handler->display->display_options['pager']['options']['tags']['previous'] = '< 前一页';
  $handler->display->display_options['pager']['options']['tags']['next'] = '下一页 >';
  $handler->display->display_options['pager']['options']['tags']['last'] = '末页 >|';
  $handler->display->display_options['style_plugin'] = 'table_megarows';
  $handler->display->display_options['style_options']['columns'] = array(
    'title' => 'title',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'title' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  $handler->display->display_options['style_options']['scroll_padding'] = '120';
  $handler->display->display_options['style_options']['loading_text'] = '正在加载...';
  $handler->display->display_options['row_plugin'] = 'node';
  /* 字段: 内容: 标题 */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* 字段: Issuing: 操作 */
  $handler->display->display_options['fields']['view_node']['id'] = 'view_node';
  $handler->display->display_options['fields']['view_node']['table'] = 'field_data_field_issuing';
  $handler->display->display_options['fields']['view_node']['field'] = 'view_node';
  $handler->display->display_options['fields']['view_node']['add_destination'] = 0;
  /* 排序标准: 内容: 发布日期 */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* 过滤规则: 内容: 类型 */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'page' => 'page',
    'article' => 'article',
  );

  /* Display: 内容管理 */
  $handler = $view->new_display('page', '内容管理', 'page');
  $handler->display->display_options['path'] = 'article-list';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = '内容管理';
  $translatables['article_list'] = array(
    t('Master'),
    t('内容管理'),
    t('更多'),
    t('应用'),
    t('重置'),
    t('排序依据'),
    t('升序'),
    t('降序'),
    t('每页条目数'),
    t('- 全部 -'),
    t('偏移量'),
    t('|< 第一页'),
    t('< 前一页'),
    t('下一页 >'),
    t('末页 >|'),
    t('操作'),
  );
  $export['article_list'] = $view;

  $view = new view();
  $view->name = 'contract_list';
  $view->description = '';
  $view->tag = 'cowpro';
  $view->base_table = 'node';
  $view->human_name = '合同管理';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = '合同管理';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['use_more_text'] = '更多';
  $handler->display->display_options['access']['type'] = 'role';
  $handler->display->display_options['access']['role'] = array(
    3 => '3',
  );
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['submit_button'] = '应用';
  $handler->display->display_options['exposed_form']['options']['reset_button_label'] = '重置';
  $handler->display->display_options['exposed_form']['options']['exposed_sorts_label'] = '排序依据';
  $handler->display->display_options['exposed_form']['options']['sort_asc_label'] = '升序';
  $handler->display->display_options['exposed_form']['options']['sort_desc_label'] = '降序';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '20';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['quantity'] = '9';
  $handler->display->display_options['pager']['options']['expose']['items_per_page_label'] = '每页条目数';
  $handler->display->display_options['pager']['options']['expose']['items_per_page_options_all_label'] = '- 全部 -';
  $handler->display->display_options['pager']['options']['expose']['offset_label'] = '偏移量';
  $handler->display->display_options['pager']['options']['tags']['first'] = '|< 第一页';
  $handler->display->display_options['pager']['options']['tags']['previous'] = '< 前一页';
  $handler->display->display_options['pager']['options']['tags']['next'] = '下一页 >';
  $handler->display->display_options['pager']['options']['tags']['last'] = '末页 >|';
  $handler->display->display_options['style_plugin'] = 'table_megarows';
  $handler->display->display_options['style_options']['columns'] = array(
    'title' => 'title',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'title' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  $handler->display->display_options['style_options']['scroll_padding'] = '120';
  $handler->display->display_options['style_options']['loading_text'] = '正在加载...';
  $handler->display->display_options['row_plugin'] = 'node';
  /* 字段: 内容: 标题 */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* 字段: Issuing: 操作 */
  $handler->display->display_options['fields']['view_node']['id'] = 'view_node';
  $handler->display->display_options['fields']['view_node']['table'] = 'field_data_field_issuing';
  $handler->display->display_options['fields']['view_node']['field'] = 'view_node';
  $handler->display->display_options['fields']['view_node']['add_destination'] = 0;
  /* 排序标准: 内容: 发布日期 */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* 过滤规则: 内容: 类型 */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'contract_loan' => 'contract_loan',
    'contract_credit_assignment' => 'contract_credit_assignment',
  );

  /* Display: 合同管理 */
  $handler = $view->new_display('page', '合同管理', 'page');
  $handler->display->display_options['path'] = 'contract-list';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = '合同管理';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;
  $translatables['contract_list'] = array(
    t('Master'),
    t('合同管理'),
    t('更多'),
    t('应用'),
    t('重置'),
    t('排序依据'),
    t('升序'),
    t('降序'),
    t('每页条目数'),
    t('- 全部 -'),
    t('偏移量'),
    t('|< 第一页'),
    t('< 前一页'),
    t('下一页 >'),
    t('末页 >|'),
    t('操作'),
  );
  $export['contract_list'] = $view;

  $view = new view();
  $view->name = 'issuing_brief';
  $view->description = '';
  $view->tag = 'cowpro';
  $view->base_table = 'node';
  $view->human_name = '贷款速览';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['use_ajax'] = TRUE;
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['use_more_text'] = '更多';
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['submit_button'] = '应用';
  $handler->display->display_options['exposed_form']['options']['reset_button_label'] = '重置';
  $handler->display->display_options['exposed_form']['options']['exposed_sorts_label'] = '排序依据';
  $handler->display->display_options['exposed_form']['options']['sort_asc_label'] = '升序';
  $handler->display->display_options['exposed_form']['options']['sort_desc_label'] = '降序';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '20';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['quantity'] = '9';
  $handler->display->display_options['pager']['options']['expose']['items_per_page_label'] = '每页条目数';
  $handler->display->display_options['pager']['options']['expose']['items_per_page_options_all_label'] = '- 全部 -';
  $handler->display->display_options['pager']['options']['expose']['offset_label'] = '偏移量';
  $handler->display->display_options['pager']['options']['tags']['first'] = '|< 第一页';
  $handler->display->display_options['pager']['options']['tags']['previous'] = '< 前一页';
  $handler->display->display_options['pager']['options']['tags']['next'] = '下一页 >';
  $handler->display->display_options['pager']['options']['tags']['last'] = '末页 >|';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'title' => 'title',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'title' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  /* 字段: 内容: 贷款表 */
  $handler->display->display_options['fields']['field_issuing']['id'] = 'field_issuing';
  $handler->display->display_options['fields']['field_issuing']['table'] = 'field_data_field_issuing';
  $handler->display->display_options['fields']['field_issuing']['field'] = 'field_issuing';
  $handler->display->display_options['fields']['field_issuing']['label'] = '';
  $handler->display->display_options['fields']['field_issuing']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_issuing']['click_sort_column'] = 'status';
  /* 上下文过滤器: 内容: Nid */
  $handler->display->display_options['arguments']['nid']['id'] = 'nid';
  $handler->display->display_options['arguments']['nid']['table'] = 'node';
  $handler->display->display_options['arguments']['nid']['field'] = 'nid';
  $handler->display->display_options['arguments']['nid']['exception']['title'] = '全部';
  $handler->display->display_options['arguments']['nid']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['nid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['nid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['nid']['summary_options']['items_per_page'] = '25';
  $translatables['issuing_brief'] = array(
    t('Master'),
    t('更多'),
    t('应用'),
    t('重置'),
    t('排序依据'),
    t('升序'),
    t('降序'),
    t('每页条目数'),
    t('- 全部 -'),
    t('偏移量'),
    t('|< 第一页'),
    t('< 前一页'),
    t('下一页 >'),
    t('末页 >|'),
    t('全部'),
  );
  $export['issuing_brief'] = $view;

  $view = new view();
  $view->name = 'repayment_schedule';
  $view->description = '';
  $view->tag = 'cowpro';
  $view->base_table = 'node';
  $view->human_name = '还款详情';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['use_ajax'] = TRUE;
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['use_more_text'] = '更多';
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['submit_button'] = '应用';
  $handler->display->display_options['exposed_form']['options']['reset_button_label'] = '重置';
  $handler->display->display_options['exposed_form']['options']['exposed_sorts_label'] = '排序依据';
  $handler->display->display_options['exposed_form']['options']['sort_asc_label'] = '升序';
  $handler->display->display_options['exposed_form']['options']['sort_desc_label'] = '降序';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '20';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['quantity'] = '9';
  $handler->display->display_options['pager']['options']['expose']['items_per_page_label'] = '每页条目数';
  $handler->display->display_options['pager']['options']['expose']['items_per_page_options_all_label'] = '- 全部 -';
  $handler->display->display_options['pager']['options']['expose']['offset_label'] = '偏移量';
  $handler->display->display_options['pager']['options']['tags']['first'] = '|< 第一页';
  $handler->display->display_options['pager']['options']['tags']['previous'] = '< 前一页';
  $handler->display->display_options['pager']['options']['tags']['next'] = '下一页 >';
  $handler->display->display_options['pager']['options']['tags']['last'] = '末页 >|';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'title' => 'title',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'title' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  /* 关联: 还款详情: 付款方用户ID */
  $handler->display->display_options['relationships']['payer_uid']['id'] = 'payer_uid';
  $handler->display->display_options['relationships']['payer_uid']['table'] = 'cowpro_repayment_schedule';
  $handler->display->display_options['relationships']['payer_uid']['field'] = 'payer_uid';
  $handler->display->display_options['relationships']['payer_uid']['label'] = '付款用户';
  $handler->display->display_options['relationships']['payer_uid']['required'] = TRUE;
  /* 关联: 还款详情: 收款方用户ID */
  $handler->display->display_options['relationships']['receiver_uid']['id'] = 'receiver_uid';
  $handler->display->display_options['relationships']['receiver_uid']['table'] = 'cowpro_repayment_schedule';
  $handler->display->display_options['relationships']['receiver_uid']['field'] = 'receiver_uid';
  $handler->display->display_options['relationships']['receiver_uid']['label'] = '收款用户';
  $handler->display->display_options['relationships']['receiver_uid']['required'] = TRUE;
  /* 字段: 还款详情: period */
  $handler->display->display_options['fields']['period']['id'] = 'period';
  $handler->display->display_options['fields']['period']['table'] = 'cowpro_repayment_schedule';
  $handler->display->display_options['fields']['period']['field'] = 'period';
  $handler->display->display_options['fields']['period']['label'] = '期次';
  $handler->display->display_options['fields']['period']['separator'] = '';
  /* 字段: 用户: 名称 */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'users';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['relationship'] = 'payer_uid';
  $handler->display->display_options['fields']['name']['label'] = '付款用户';
  /* 字段: 用户: 名称 */
  $handler->display->display_options['fields']['name_1']['id'] = 'name_1';
  $handler->display->display_options['fields']['name_1']['table'] = 'users';
  $handler->display->display_options['fields']['name_1']['field'] = 'name';
  $handler->display->display_options['fields']['name_1']['relationship'] = 'receiver_uid';
  $handler->display->display_options['fields']['name_1']['label'] = '收款用户';
  /* 字段: 还款详情: payable_amount */
  $handler->display->display_options['fields']['payable_amount']['id'] = 'payable_amount';
  $handler->display->display_options['fields']['payable_amount']['table'] = 'cowpro_repayment_schedule';
  $handler->display->display_options['fields']['payable_amount']['field'] = 'payable_amount';
  $handler->display->display_options['fields']['payable_amount']['label'] = '应付款';
  $handler->display->display_options['fields']['payable_amount']['set_precision'] = TRUE;
  $handler->display->display_options['fields']['payable_amount']['precision'] = '2';
  /* 字段: 还款详情: paid_amount */
  $handler->display->display_options['fields']['paid_amount_1']['id'] = 'paid_amount_1';
  $handler->display->display_options['fields']['paid_amount_1']['table'] = 'cowpro_repayment_schedule';
  $handler->display->display_options['fields']['paid_amount_1']['field'] = 'paid_amount';
  $handler->display->display_options['fields']['paid_amount_1']['label'] = '已付款';
  $handler->display->display_options['fields']['paid_amount_1']['set_precision'] = TRUE;
  $handler->display->display_options['fields']['paid_amount_1']['precision'] = '2';
  /* 字段: 还款详情: receivable_amount */
  $handler->display->display_options['fields']['receivable_amount']['id'] = 'receivable_amount';
  $handler->display->display_options['fields']['receivable_amount']['table'] = 'cowpro_repayment_schedule';
  $handler->display->display_options['fields']['receivable_amount']['field'] = 'receivable_amount';
  $handler->display->display_options['fields']['receivable_amount']['label'] = '应收款';
  $handler->display->display_options['fields']['receivable_amount']['set_precision'] = TRUE;
  $handler->display->display_options['fields']['receivable_amount']['precision'] = '2';
  /* 字段: 还款详情: received_amount */
  $handler->display->display_options['fields']['received_amount']['id'] = 'received_amount';
  $handler->display->display_options['fields']['received_amount']['table'] = 'cowpro_repayment_schedule';
  $handler->display->display_options['fields']['received_amount']['field'] = 'received_amount';
  $handler->display->display_options['fields']['received_amount']['label'] = '已收款';
  $handler->display->display_options['fields']['received_amount']['set_precision'] = TRUE;
  $handler->display->display_options['fields']['received_amount']['precision'] = '2';
  /* 字段: 还款详情: 最后还款日 */
  $handler->display->display_options['fields']['deadline']['id'] = 'deadline';
  $handler->display->display_options['fields']['deadline']['table'] = 'cowpro_repayment_schedule';
  $handler->display->display_options['fields']['deadline']['field'] = 'deadline';
  $handler->display->display_options['fields']['deadline']['date_format'] = 'short';
  $handler->display->display_options['fields']['deadline']['second_date_format'] = 'short';
  /* 字段: 还款详情: 状态 */
  $handler->display->display_options['fields']['status']['id'] = 'status';
  $handler->display->display_options['fields']['status']['table'] = 'cowpro_repayment_schedule';
  $handler->display->display_options['fields']['status']['field'] = 'status';
  /* 上下文过滤器: 内容: Nid */
  $handler->display->display_options['arguments']['nid']['id'] = 'nid';
  $handler->display->display_options['arguments']['nid']['table'] = 'node';
  $handler->display->display_options['arguments']['nid']['field'] = 'nid';
  $handler->display->display_options['arguments']['nid']['exception']['title'] = '全部';
  $handler->display->display_options['arguments']['nid']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['nid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['nid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['nid']['summary_options']['items_per_page'] = '25';
  $translatables['repayment_schedule'] = array(
    t('Master'),
    t('更多'),
    t('应用'),
    t('重置'),
    t('排序依据'),
    t('升序'),
    t('降序'),
    t('每页条目数'),
    t('- 全部 -'),
    t('偏移量'),
    t('|< 第一页'),
    t('< 前一页'),
    t('下一页 >'),
    t('末页 >|'),
    t('付款用户'),
    t('收款用户'),
    t('期次'),
    t('.'),
    t('应付款'),
    t(','),
    t('已付款'),
    t('应收款'),
    t('已收款'),
    t('最后还款日'),
    t('状态'),
    t('全部'),
  );
  $export['repayment_schedule'] = $view;

  $view = new view();
  $view->name = 'repayment_schedule_debtor';
  $view->description = '';
  $view->tag = 'cowpro';
  $view->base_table = 'cowpro_repayment_schedule';
  $view->human_name = '还款详情(借款人)';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['use_ajax'] = TRUE;
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['use_more_text'] = '更多';
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['submit_button'] = '应用';
  $handler->display->display_options['exposed_form']['options']['reset_button_label'] = '重置';
  $handler->display->display_options['exposed_form']['options']['exposed_sorts_label'] = '排序依据';
  $handler->display->display_options['exposed_form']['options']['sort_asc_label'] = '升序';
  $handler->display->display_options['exposed_form']['options']['sort_desc_label'] = '降序';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '0';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['quantity'] = '9';
  $handler->display->display_options['pager']['options']['expose']['items_per_page_label'] = '每页条目数';
  $handler->display->display_options['pager']['options']['expose']['items_per_page_options_all_label'] = '- 全部 -';
  $handler->display->display_options['pager']['options']['expose']['offset_label'] = '偏移量';
  $handler->display->display_options['pager']['options']['tags']['first'] = '« 第一页';
  $handler->display->display_options['pager']['options']['tags']['previous'] = '‹ 前一页';
  $handler->display->display_options['pager']['options']['tags']['next'] = '下一页 ›';
  $handler->display->display_options['pager']['options']['tags']['last'] = '末页 »';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['grouping'] = array(
    0 => array(
      'field' => 'period',
      'rendered' => 1,
      'rendered_strip' => 0,
    ),
  );
  $handler->display->display_options['style_options']['columns'] = array(
    'period' => 'period',
    'name' => 'name',
    'payable_amount' => 'payable_amount',
    'paid_amount_1' => 'paid_amount_1',
    'deadline' => 'deadline',
    'status' => 'status',
    'views_bulk_operations' => 'views_bulk_operations',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'period' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'name' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'payable_amount' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'paid_amount_1' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'deadline' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'status' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'views_bulk_operations' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  /* 关联: 还款详情: 付款方用户ID */
  $handler->display->display_options['relationships']['payer_uid']['id'] = 'payer_uid';
  $handler->display->display_options['relationships']['payer_uid']['table'] = 'cowpro_repayment_schedule';
  $handler->display->display_options['relationships']['payer_uid']['field'] = 'payer_uid';
  $handler->display->display_options['relationships']['payer_uid']['label'] = '付款用户';
  $handler->display->display_options['relationships']['payer_uid']['required'] = TRUE;
  /* 字段: 还款详情: period */
  $handler->display->display_options['fields']['period']['id'] = 'period';
  $handler->display->display_options['fields']['period']['table'] = 'cowpro_repayment_schedule';
  $handler->display->display_options['fields']['period']['field'] = 'period';
  $handler->display->display_options['fields']['period']['label'] = '期次';
  $handler->display->display_options['fields']['period']['separator'] = '';
  /* 字段: 用户: 名称 */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'users';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['relationship'] = 'payer_uid';
  $handler->display->display_options['fields']['name']['label'] = '付款用户';
  /* 字段: 还款详情: payable_amount */
  $handler->display->display_options['fields']['payable_amount']['id'] = 'payable_amount';
  $handler->display->display_options['fields']['payable_amount']['table'] = 'cowpro_repayment_schedule';
  $handler->display->display_options['fields']['payable_amount']['field'] = 'payable_amount';
  $handler->display->display_options['fields']['payable_amount']['label'] = '应付款';
  $handler->display->display_options['fields']['payable_amount']['set_precision'] = TRUE;
  $handler->display->display_options['fields']['payable_amount']['precision'] = '2';
  /* 字段: 还款详情: paid_amount */
  $handler->display->display_options['fields']['paid_amount_1']['id'] = 'paid_amount_1';
  $handler->display->display_options['fields']['paid_amount_1']['table'] = 'cowpro_repayment_schedule';
  $handler->display->display_options['fields']['paid_amount_1']['field'] = 'paid_amount';
  $handler->display->display_options['fields']['paid_amount_1']['label'] = '已付款';
  $handler->display->display_options['fields']['paid_amount_1']['set_precision'] = TRUE;
  $handler->display->display_options['fields']['paid_amount_1']['precision'] = '2';
  /* 字段: 还款详情: 最后还款日 */
  $handler->display->display_options['fields']['deadline']['id'] = 'deadline';
  $handler->display->display_options['fields']['deadline']['table'] = 'cowpro_repayment_schedule';
  $handler->display->display_options['fields']['deadline']['field'] = 'deadline';
  $handler->display->display_options['fields']['deadline']['date_format'] = 'short';
  $handler->display->display_options['fields']['deadline']['second_date_format'] = 'short';
  /* 字段: 还款详情: 状态 */
  $handler->display->display_options['fields']['status']['id'] = 'status';
  $handler->display->display_options['fields']['status']['table'] = 'cowpro_repayment_schedule';
  $handler->display->display_options['fields']['status']['field'] = 'status';
  /* 字段: 批量操作: 还款详情 */
  $handler->display->display_options['fields']['views_bulk_operations']['id'] = 'views_bulk_operations';
  $handler->display->display_options['fields']['views_bulk_operations']['table'] = 'cowpro_repayment_schedule';
  $handler->display->display_options['fields']['views_bulk_operations']['field'] = 'views_bulk_operations';
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['display_type'] = '1';
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['enable_select_all_pages'] = 0;
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['row_clickable'] = 1;
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['force_single'] = 0;
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['entity_load_capacity'] = '10';
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['skip_batching'] = 1;
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_operations'] = array(
    'action::cowpro_issuing_repayment_action' => array(
      'selected' => 1,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
  );
  /* 上下文过滤器: 还款详情: 贷款申请表 */
  $handler->display->display_options['arguments']['issuing_id']['id'] = 'issuing_id';
  $handler->display->display_options['arguments']['issuing_id']['table'] = 'cowpro_repayment_schedule';
  $handler->display->display_options['arguments']['issuing_id']['field'] = 'issuing_id';
  $handler->display->display_options['arguments']['issuing_id']['exception']['title'] = '全部';
  $handler->display->display_options['arguments']['issuing_id']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['issuing_id']['summary']['format'] = 'default_summary';
  $translatables['repayment_schedule_debtor'] = array(
    t('Master'),
    t('更多'),
    t('应用'),
    t('重置'),
    t('排序依据'),
    t('升序'),
    t('降序'),
    t('每页条目数'),
    t('- 全部 -'),
    t('偏移量'),
    t('« 第一页'),
    t('‹ 前一页'),
    t('下一页 ›'),
    t('末页 »'),
    t('付款用户'),
    t('期次'),
    t('.'),
    t('应付款'),
    t(','),
    t('已付款'),
    t('最后还款日'),
    t('状态'),
    t('还款详情'),
    t('- 选择一个操作 -'),
    t('全部'),
  );
  $export['repayment_schedule_debtor'] = $view;

  $view = new view();
  $view->name = 'repayment_schedule_lender';
  $view->description = '';
  $view->tag = 'cowpro';
  $view->base_table = 'node';
  $view->human_name = '还款详情(出借人)';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['use_ajax'] = TRUE;
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['use_more_text'] = '更多';
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['submit_button'] = '应用';
  $handler->display->display_options['exposed_form']['options']['reset_button_label'] = '重置';
  $handler->display->display_options['exposed_form']['options']['exposed_sorts_label'] = '排序依据';
  $handler->display->display_options['exposed_form']['options']['sort_asc_label'] = '升序';
  $handler->display->display_options['exposed_form']['options']['sort_desc_label'] = '降序';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '20';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['quantity'] = '9';
  $handler->display->display_options['pager']['options']['expose']['items_per_page_label'] = '每页条目数';
  $handler->display->display_options['pager']['options']['expose']['items_per_page_options_all_label'] = '- 全部 -';
  $handler->display->display_options['pager']['options']['expose']['offset_label'] = '偏移量';
  $handler->display->display_options['pager']['options']['tags']['first'] = '|< 第一页';
  $handler->display->display_options['pager']['options']['tags']['previous'] = '< 前一页';
  $handler->display->display_options['pager']['options']['tags']['next'] = '下一页 >';
  $handler->display->display_options['pager']['options']['tags']['last'] = '末页 >|';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'title' => 'title',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'title' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  /* 关联: 还款详情: 付款方用户ID */
  $handler->display->display_options['relationships']['payer_uid']['id'] = 'payer_uid';
  $handler->display->display_options['relationships']['payer_uid']['table'] = 'cowpro_repayment_schedule';
  $handler->display->display_options['relationships']['payer_uid']['field'] = 'payer_uid';
  $handler->display->display_options['relationships']['payer_uid']['label'] = '付款用户';
  $handler->display->display_options['relationships']['payer_uid']['required'] = TRUE;
  /* 关联: 还款详情: 收款方用户ID */
  $handler->display->display_options['relationships']['receiver_uid']['id'] = 'receiver_uid';
  $handler->display->display_options['relationships']['receiver_uid']['table'] = 'cowpro_repayment_schedule';
  $handler->display->display_options['relationships']['receiver_uid']['field'] = 'receiver_uid';
  $handler->display->display_options['relationships']['receiver_uid']['label'] = '收款用户';
  $handler->display->display_options['relationships']['receiver_uid']['required'] = TRUE;
  /* 字段: 还款详情: period */
  $handler->display->display_options['fields']['period']['id'] = 'period';
  $handler->display->display_options['fields']['period']['table'] = 'cowpro_repayment_schedule';
  $handler->display->display_options['fields']['period']['field'] = 'period';
  $handler->display->display_options['fields']['period']['label'] = '期次';
  $handler->display->display_options['fields']['period']['separator'] = '';
  /* 字段: 用户: 名称 */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'users';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['relationship'] = 'payer_uid';
  $handler->display->display_options['fields']['name']['label'] = '付款用户';
  /* 字段: 用户: 名称 */
  $handler->display->display_options['fields']['name_1']['id'] = 'name_1';
  $handler->display->display_options['fields']['name_1']['table'] = 'users';
  $handler->display->display_options['fields']['name_1']['field'] = 'name';
  $handler->display->display_options['fields']['name_1']['relationship'] = 'receiver_uid';
  $handler->display->display_options['fields']['name_1']['label'] = '收款用户';
  /* 字段: 还款详情: receivable_amount */
  $handler->display->display_options['fields']['receivable_amount']['id'] = 'receivable_amount';
  $handler->display->display_options['fields']['receivable_amount']['table'] = 'cowpro_repayment_schedule';
  $handler->display->display_options['fields']['receivable_amount']['field'] = 'receivable_amount';
  $handler->display->display_options['fields']['receivable_amount']['label'] = '应收款';
  $handler->display->display_options['fields']['receivable_amount']['set_precision'] = TRUE;
  $handler->display->display_options['fields']['receivable_amount']['precision'] = '2';
  /* 字段: 还款详情: received_amount */
  $handler->display->display_options['fields']['received_amount']['id'] = 'received_amount';
  $handler->display->display_options['fields']['received_amount']['table'] = 'cowpro_repayment_schedule';
  $handler->display->display_options['fields']['received_amount']['field'] = 'received_amount';
  $handler->display->display_options['fields']['received_amount']['label'] = '已收款';
  $handler->display->display_options['fields']['received_amount']['set_precision'] = TRUE;
  $handler->display->display_options['fields']['received_amount']['precision'] = '2';
  /* 字段: 还款详情: 最后还款日 */
  $handler->display->display_options['fields']['deadline']['id'] = 'deadline';
  $handler->display->display_options['fields']['deadline']['table'] = 'cowpro_repayment_schedule';
  $handler->display->display_options['fields']['deadline']['field'] = 'deadline';
  $handler->display->display_options['fields']['deadline']['date_format'] = 'short';
  $handler->display->display_options['fields']['deadline']['second_date_format'] = 'short';
  /* 字段: 还款详情: 状态 */
  $handler->display->display_options['fields']['status']['id'] = 'status';
  $handler->display->display_options['fields']['status']['table'] = 'cowpro_repayment_schedule';
  $handler->display->display_options['fields']['status']['field'] = 'status';
  /* 上下文过滤器: 内容: Nid */
  $handler->display->display_options['arguments']['nid']['id'] = 'nid';
  $handler->display->display_options['arguments']['nid']['table'] = 'node';
  $handler->display->display_options['arguments']['nid']['field'] = 'nid';
  $handler->display->display_options['arguments']['nid']['exception']['title'] = '全部';
  $handler->display->display_options['arguments']['nid']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['nid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['nid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['nid']['summary_options']['items_per_page'] = '25';
  $translatables['repayment_schedule_lender'] = array(
    t('Master'),
    t('更多'),
    t('应用'),
    t('重置'),
    t('排序依据'),
    t('升序'),
    t('降序'),
    t('每页条目数'),
    t('- 全部 -'),
    t('偏移量'),
    t('|< 第一页'),
    t('< 前一页'),
    t('下一页 >'),
    t('末页 >|'),
    t('付款用户'),
    t('收款用户'),
    t('期次'),
    t('.'),
    t('应收款'),
    t(','),
    t('已收款'),
    t('最后还款日'),
    t('状态'),
    t('全部'),
  );
  $export['repayment_schedule_lender'] = $view;

  return $export;
}
