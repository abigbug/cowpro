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
  $view->name = '_wyth';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = '贷款信息';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = '贷款信息';
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
  $handler->display->display_options['pager']['options']['items_per_page'] = '30';
  $handler->display->display_options['pager']['options']['expose']['items_per_page_label'] = '每页条目数';
  $handler->display->display_options['pager']['options']['expose']['items_per_page_options_all_label'] = '- 全部 -';
  $handler->display->display_options['pager']['options']['expose']['offset_label'] = '偏移量';
  $handler->display->display_options['pager']['options']['tags']['first'] = '« 第一页';
  $handler->display->display_options['pager']['options']['tags']['previous'] = '‹ 前一页';
  $handler->display->display_options['pager']['options']['tags']['next'] = '下一页 ›';
  $handler->display->display_options['pager']['options']['tags']['last'] = '末页 »';
  $handler->display->display_options['style_plugin'] = 'table';
  /* 字段: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '标题';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* 排序标准: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* 过滤规则: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* 过滤规则: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'cowpro_issuing' => 'cowpro_issuing',
  );

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'issuing_search');
  $handler->display->display_options['path'] = 'issuing-search';
  $translatables['_wyth'] = array(
    t('Master'),
    t('贷款信息'),
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
    t('标题'),
    t('Page'),
  );
  $export['_wyth'] = $view;

  $view = new view();
  $view->name = '_ynvi';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = '投标记录';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = '投标记录';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['use_more_text'] = '更多';
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'access user profiles';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['submit_button'] = '应用';
  $handler->display->display_options['exposed_form']['options']['reset_button_label'] = '重置';
  $handler->display->display_options['exposed_form']['options']['exposed_sorts_label'] = '排序依据';
  $handler->display->display_options['exposed_form']['options']['sort_asc_label'] = '升序';
  $handler->display->display_options['exposed_form']['options']['sort_desc_label'] = '降序';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '30';
  $handler->display->display_options['pager']['options']['expose']['items_per_page_label'] = '每页条目数';
  $handler->display->display_options['pager']['options']['expose']['items_per_page_options_all_label'] = '- 全部 -';
  $handler->display->display_options['pager']['options']['expose']['offset_label'] = '偏移量';
  $handler->display->display_options['pager']['options']['tags']['first'] = '« 第一页';
  $handler->display->display_options['pager']['options']['tags']['previous'] = '‹ 前一页';
  $handler->display->display_options['pager']['options']['tags']['next'] = '下一页 ›';
  $handler->display->display_options['pager']['options']['tags']['last'] = '末页 »';
  $handler->display->display_options['style_plugin'] = 'table';
  /* 字段: 资金明细: 用户实名 */
  $handler->display->display_options['fields']['real_name_1']['id'] = 'real_name_1';
  $handler->display->display_options['fields']['real_name_1']['table'] = 'cowpro_fund_journal';
  $handler->display->display_options['fields']['real_name_1']['field'] = 'real_name';
  $handler->display->display_options['fields']['real_name_1']['label'] = '';
  $handler->display->display_options['fields']['real_name_1']['element_label_colon'] = FALSE;
  /* 字段: 资金明细: amount */
  $handler->display->display_options['fields']['amount']['id'] = 'amount';
  $handler->display->display_options['fields']['amount']['table'] = 'cowpro_fund_journal';
  $handler->display->display_options['fields']['amount']['field'] = 'amount';
  $handler->display->display_options['fields']['amount']['label'] = '金额';
  /* 字段: 资金明细: 内部参考凭证 */
  $handler->display->display_options['fields']['internal_reference_id']['id'] = 'internal_reference_id';
  $handler->display->display_options['fields']['internal_reference_id']['table'] = 'cowpro_fund_journal';
  $handler->display->display_options['fields']['internal_reference_id']['field'] = 'internal_reference_id';
  $handler->display->display_options['fields']['internal_reference_id']['label'] = '贷款标题';
  /* 字段: 资金明细: 时间 */
  $handler->display->display_options['fields']['created']['id'] = 'created';
  $handler->display->display_options['fields']['created']['table'] = 'cowpro_fund_journal';
  $handler->display->display_options['fields']['created']['field'] = 'created';
  $handler->display->display_options['fields']['created']['date_format'] = 'short';
  $handler->display->display_options['fields']['created']['custom_date_format'] = 'Y/m/d';
  $handler->display->display_options['fields']['created']['second_date_format'] = 'long';
  /* 排序标准: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* 过滤规则: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'cowpro_issuing' => 'cowpro_issuing',
  );
  /* 过滤规则: 资金明细: 业务类型 */
  $handler->display->display_options['filters']['type_1']['id'] = 'type_1';
  $handler->display->display_options['filters']['type_1']['table'] = 'cowpro_fund_journal';
  $handler->display->display_options['filters']['type_1']['field'] = 'type';
  $handler->display->display_options['filters']['type_1']['value'] = array(
    'BID' => 'BID',
  );
  /* 过滤规则: 资金明细: 结果 */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'cowpro_fund_journal';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = array(
    1 => '1',
  );
  /* 过滤规则: 贷款名称 */
  $handler->display->display_options['filters']['internal_reference_id']['id'] = 'internal_reference_id';
  $handler->display->display_options['filters']['internal_reference_id']['table'] = 'cowpro_fund_journal';
  $handler->display->display_options['filters']['internal_reference_id']['field'] = 'internal_reference_id';
  $handler->display->display_options['filters']['internal_reference_id']['ui_name'] = '贷款名称';
  $handler->display->display_options['filters']['internal_reference_id']['operator'] = 'contains';
  $handler->display->display_options['filters']['internal_reference_id']['exposed'] = TRUE;
  $handler->display->display_options['filters']['internal_reference_id']['expose']['operator_id'] = '';
  $handler->display->display_options['filters']['internal_reference_id']['expose']['label'] = '贷款标题';
  $handler->display->display_options['filters']['internal_reference_id']['expose']['operator'] = 'internal_reference_id_op';
  $handler->display->display_options['filters']['internal_reference_id']['expose']['identifier'] = 'internal_reference_id';
  $handler->display->display_options['filters']['internal_reference_id']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    6 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
  );
  /* 过滤规则: 资金明细: 用户实名 */
  $handler->display->display_options['filters']['real_name']['id'] = 'real_name';
  $handler->display->display_options['filters']['real_name']['table'] = 'cowpro_fund_journal';
  $handler->display->display_options['filters']['real_name']['field'] = 'real_name';
  $handler->display->display_options['filters']['real_name']['value'] = -1;
  $handler->display->display_options['filters']['real_name']['exposed'] = TRUE;
  $handler->display->display_options['filters']['real_name']['expose']['operator_id'] = '';
  $handler->display->display_options['filters']['real_name']['expose']['label'] = '用户实名';
  $handler->display->display_options['filters']['real_name']['expose']['operator'] = 'real_name_op';
  $handler->display->display_options['filters']['real_name']['expose']['identifier'] = 'real_name';
  $handler->display->display_options['filters']['real_name']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    6 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
  );

  /* Display: 投标记录 */
  $handler = $view->new_display('page', '投标记录', 'page');
  $handler->display->display_options['path'] = 'bid-search';
  $handler->display->display_options['menu']['title'] = '投标记录';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;

  /* Display: 投标记录，导出 */
  $handler = $view->new_display('views_data_export', '投标记录，导出', 'views_data_export_1');
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['style_plugin'] = 'views_data_export_xls';
  $handler->display->display_options['style_options']['provide_file'] = 0;
  $handler->display->display_options['style_options']['parent_sort'] = 0;
  $handler->display->display_options['path'] = 'bid-search.xls';
  $handler->display->display_options['displays'] = array(
    'page' => 'page',
    'default' => 0,
  );
  $translatables['_ynvi'] = array(
    t('Master'),
    t('投标记录'),
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
    t('金额'),
    t('贷款标题'),
    t('时间'),
    t('用户实名'),
    t('投标记录，导出'),
  );
  $export['_ynvi'] = $view;

  $view = new view();
  $view->name = 'all_issuing';
  $view->description = '';
  $view->tag = 'cowpro-issuing-list';
  $view->base_table = 'node';
  $view->human_name = '贷款管理';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = '贷款管理，导出';
  $handler->display->display_options['css_class'] = 'mobile-device-only';
  $handler->display->display_options['use_ajax'] = TRUE;
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['use_more_text'] = '更多';
  $handler->display->display_options['access']['type'] = 'role';
  $handler->display->display_options['access']['role'] = array(
    3 => '3',
  );
  $handler->display->display_options['cache']['type'] = 'time';
  $handler->display->display_options['cache']['results_lifespan'] = '3600';
  $handler->display->display_options['cache']['results_lifespan_custom'] = '0';
  $handler->display->display_options['cache']['output_lifespan'] = '3600';
  $handler->display->display_options['cache']['output_lifespan_custom'] = '0';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'better_exposed_filters';
  $handler->display->display_options['exposed_form']['options']['submit_button'] = '应用';
  $handler->display->display_options['exposed_form']['options']['reset_button_label'] = '重置';
  $handler->display->display_options['exposed_form']['options']['exposed_sorts_label'] = '排序依据';
  $handler->display->display_options['exposed_form']['options']['sort_asc_label'] = '升序';
  $handler->display->display_options['exposed_form']['options']['sort_desc_label'] = '降序';
  $handler->display->display_options['exposed_form']['options']['bef'] = array(
    'general' => array(
      'input_required' => 0,
      'text_input_required' => array(
        'text_input_required' => array(
          'value' => 'Select any filter and click on Apply to see results',
          'format' => 'filtered_html',
        ),
      ),
      'allow_secondary' => 0,
      'secondary_label' => '高级选项',
      'secondary_collapse_override' => '0',
    ),
    'field_issuing_status_1' => array(
      'bef_format' => 'default',
      'more_options' => array(
        'bef_select_all_none' => 0,
        'bef_collapsible' => 0,
        'autosubmit' => 0,
        'is_secondary' => 0,
        'any_label' => '',
        'bef_filter_description' => '',
        'tokens' => array(
          'available' => array(
            0 => 'global_types',
          ),
        ),
        'rewrite' => array(
          'filter_rewrite_values' => '',
        ),
      ),
    ),
  );
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['expose']['items_per_page_label'] = '每页条目数';
  $handler->display->display_options['pager']['options']['expose']['items_per_page_options_all_label'] = '- 全部 -';
  $handler->display->display_options['pager']['options']['expose']['offset_label'] = '偏移量';
  $handler->display->display_options['pager']['options']['tags']['first'] = '« 第一页';
  $handler->display->display_options['pager']['options']['tags']['previous'] = '‹ 前一页';
  $handler->display->display_options['pager']['options']['tags']['next'] = '下一页 ›';
  $handler->display->display_options['pager']['options']['tags']['last'] = '末页 »';
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
  /* 页眉: Global: Text area */
  $handler->display->display_options['header']['area']['id'] = 'area';
  $handler->display->display_options['header']['area']['table'] = 'views';
  $handler->display->display_options['header']['area']['field'] = 'area';
  $handler->display->display_options['header']['area']['content'] = '<div class="content_head container-fluid">
  <ul class="row">
    <li class="project col-md-8">投资项目<span class="inearnings">-</span></li>
    <li class="inmoney col-md-4 text-right"><a href="/issuing-list" style="color:#ec5245">更多项目</a></li>
  </ul>
</div>';
  $handler->display->display_options['header']['area']['format'] = 'full_html';
  /* 无任何结果时的行为: Global: Text area */
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['empty'] = TRUE;
  $handler->display->display_options['empty']['area']['content'] = '<h1>暂无内容，等待添加！</h1>';
  $handler->display->display_options['empty']['area']['format'] = 'full_html';
  /* 字段: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* 字段: 节点: 申请人 */
  $handler->display->display_options['fields']['field_applicant']['id'] = 'field_applicant';
  $handler->display->display_options['fields']['field_applicant']['table'] = 'field_data_field_applicant';
  $handler->display->display_options['fields']['field_applicant']['field'] = 'field_applicant';
  $handler->display->display_options['fields']['field_applicant']['settings'] = array(
    'user_reference_view_mode' => 'full',
  );
  /* 字段: 节点: 贷款表 */
  $handler->display->display_options['fields']['field_issuing']['id'] = 'field_issuing';
  $handler->display->display_options['fields']['field_issuing']['table'] = 'field_data_field_issuing';
  $handler->display->display_options['fields']['field_issuing']['field'] = 'field_issuing';
  $handler->display->display_options['fields']['field_issuing']['click_sort_column'] = 'status';
  /* 字段: Issuing: Operations */
  $handler->display->display_options['fields']['view_issuing']['id'] = 'view_issuing';
  $handler->display->display_options['fields']['view_issuing']['table'] = 'field_data_field_issuing';
  $handler->display->display_options['fields']['view_issuing']['field'] = 'view_issuing';
  $handler->display->display_options['fields']['view_issuing']['label'] = '操作';
  $handler->display->display_options['fields']['view_issuing']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['view_issuing']['add_destination'] = 1;
  /* 字段: Issuing: progress */
  $handler->display->display_options['fields']['progress']['id'] = 'progress';
  $handler->display->display_options['fields']['progress']['table'] = 'field_data_field_issuing';
  $handler->display->display_options['fields']['progress']['field'] = 'progress';
  $handler->display->display_options['fields']['progress']['label'] = '进度';
  /* 排序标准: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* 过滤规则: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'cowpro_issuing' => 'cowpro_issuing',
  );
  /* 过滤规则: 节点: 贷款表 (field_issuing:status) */
  $handler->display->display_options['filters']['field_issuing_status']['id'] = 'field_issuing_status';
  $handler->display->display_options['filters']['field_issuing_status']['table'] = 'field_data_field_issuing';
  $handler->display->display_options['filters']['field_issuing_status']['field'] = 'field_issuing_status';
  $handler->display->display_options['filters']['field_issuing_status']['operator'] = 'not in';
  $handler->display->display_options['filters']['field_issuing_status']['value'] = array(
    'INVITE_BIDS_FAILED' => 'INVITE_BIDS_FAILED',
  );
  $handler->display->display_options['filters']['field_issuing_status']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_issuing_status']['expose']['operator_id'] = 'field_issuing_status_op';
  $handler->display->display_options['filters']['field_issuing_status']['expose']['label'] = '贷款表 (field_issuing:status)';
  $handler->display->display_options['filters']['field_issuing_status']['expose']['operator'] = 'field_issuing_status_op';
  $handler->display->display_options['filters']['field_issuing_status']['expose']['identifier'] = 'field_issuing_status';

  /* Display: 贷款管理 */
  $handler = $view->new_display('page', '贷款管理', 'issuing_manage');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = '贷款管理';
  $handler->display->display_options['defaults']['access'] = FALSE;
  $handler->display->display_options['access']['type'] = 'role';
  $handler->display->display_options['access']['role'] = array(
    3 => '3',
  );
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
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
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* 字段: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  /* 字段: Issuing: 申请人 */
  $handler->display->display_options['fields']['applicant_uid']['id'] = 'applicant_uid';
  $handler->display->display_options['fields']['applicant_uid']['table'] = 'field_data_field_applicant';
  $handler->display->display_options['fields']['applicant_uid']['field'] = 'applicant_uid';
  /* 字段: Issuing: progress */
  $handler->display->display_options['fields']['progress']['id'] = 'progress';
  $handler->display->display_options['fields']['progress']['table'] = 'field_data_field_issuing';
  $handler->display->display_options['fields']['progress']['field'] = 'progress';
  $handler->display->display_options['fields']['progress']['label'] = '进度';
  /* 字段: Issuing: 贷款期限 */
  $handler->display->display_options['fields']['term']['id'] = 'term';
  $handler->display->display_options['fields']['term']['table'] = 'field_data_field_issuing';
  $handler->display->display_options['fields']['term']['field'] = 'term';
  /* 字段: Issuing: 年利率 */
  $handler->display->display_options['fields']['annual_rate']['id'] = 'annual_rate';
  $handler->display->display_options['fields']['annual_rate']['table'] = 'field_data_field_issuing';
  $handler->display->display_options['fields']['annual_rate']['field'] = 'annual_rate';
  /* 字段: Issuing: 贷款金额 */
  $handler->display->display_options['fields']['loan_amounts']['id'] = 'loan_amounts';
  $handler->display->display_options['fields']['loan_amounts']['table'] = 'field_data_field_issuing';
  $handler->display->display_options['fields']['loan_amounts']['field'] = 'loan_amounts';
  /* 字段: Issuing: 贷款状态 */
  $handler->display->display_options['fields']['status']['id'] = 'status';
  $handler->display->display_options['fields']['status']['table'] = 'field_data_field_issuing';
  $handler->display->display_options['fields']['status']['field'] = 'status';
  $handler->display->display_options['fields']['status']['label'] = '状态';
  /* 字段: Issuing: 满标放款时间 */
  $handler->display->display_options['fields']['make_loans_time']['id'] = 'make_loans_time';
  $handler->display->display_options['fields']['make_loans_time']['table'] = 'field_data_field_issuing';
  $handler->display->display_options['fields']['make_loans_time']['field'] = 'make_loans_time';
  $handler->display->display_options['fields']['make_loans_time']['label'] = '放款时间';
  /* 字段: Issuing: Operations */
  $handler->display->display_options['fields']['view_issuing']['id'] = 'view_issuing';
  $handler->display->display_options['fields']['view_issuing']['table'] = 'field_data_field_issuing';
  $handler->display->display_options['fields']['view_issuing']['field'] = 'view_issuing';
  $handler->display->display_options['fields']['view_issuing']['label'] = '操作';
  $handler->display->display_options['fields']['view_issuing']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['view_issuing']['add_destination'] = 1;
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* 过滤规则: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'cowpro_issuing' => 'cowpro_issuing',
  );
  /* 过滤规则: 节点: 贷款表 (field_issuing:status) */
  $handler->display->display_options['filters']['field_issuing_status']['id'] = 'field_issuing_status';
  $handler->display->display_options['filters']['field_issuing_status']['table'] = 'field_data_field_issuing';
  $handler->display->display_options['filters']['field_issuing_status']['field'] = 'field_issuing_status';
  $handler->display->display_options['filters']['field_issuing_status']['value'] = array(
    'UNAUDITED' => 'UNAUDITED',
    'AUDITED' => 'AUDITED',
    'INVITE_BIDS_START' => 'INVITE_BIDS_START',
    'INVITE_BIDS_FAILED' => 'INVITE_BIDS_FAILED',
    'INVITE_BIDS_SUCCEED' => 'INVITE_BIDS_SUCCEED',
    'REPAYMENT' => 'REPAYMENT',
    'FINISHED' => 'FINISHED',
  );
  $handler->display->display_options['filters']['field_issuing_status']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_issuing_status']['expose']['operator_id'] = 'field_issuing_status_op';
  $handler->display->display_options['filters']['field_issuing_status']['expose']['label'] = '贷款表状态';
  $handler->display->display_options['filters']['field_issuing_status']['expose']['operator'] = 'field_issuing_status_op';
  $handler->display->display_options['filters']['field_issuing_status']['expose']['identifier'] = 'field_issuing_status';
  $handler->display->display_options['filters']['field_issuing_status']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    6 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
    7 => 0,
  );
  $handler->display->display_options['filters']['field_issuing_status']['expose']['reduce'] = TRUE;
  $handler->display->display_options['filters']['field_issuing_status']['group_info']['label'] = '贷款表 (field_issuing:status)';
  $handler->display->display_options['filters']['field_issuing_status']['group_info']['identifier'] = 'field_issuing_status';
  $handler->display->display_options['filters']['field_issuing_status']['group_info']['widget'] = 'radios';
  $handler->display->display_options['filters']['field_issuing_status']['group_info']['group_items'] = array(
    1 => array(
      'title' => '末审核',
      'operator' => 'in',
      'value' => array(
        'UNAUDITED' => 'UNAUDITED',
        'all' => 0,
        'AUDITED' => 0,
        'INVITE_BIDS_START' => 0,
        'INVITE_BIDS_FAILED' => 0,
        'INVITE_BIDS_SUCCEED' => 0,
        'REPAYMENT' => 0,
        'FINISHED' => 0,
      ),
    ),
    2 => array(
      'title' => '正在投标',
      'operator' => 'in',
      'value' => array(
        'INVITE_BIDS_START' => 'INVITE_BIDS_START',
        'all' => 0,
        'UNAUDITED' => 0,
        'AUDITED' => 0,
        'INVITE_BIDS_FAILED' => 0,
        'INVITE_BIDS_SUCCEED' => 0,
        'REPAYMENT' => 0,
        'FINISHED' => 0,
      ),
    ),
    3 => array(
      'title' => '流标',
      'operator' => 'in',
      'value' => array(
        'INVITE_BIDS_FAILED' => 'INVITE_BIDS_FAILED',
        'all' => 0,
        'UNAUDITED' => 0,
        'AUDITED' => 0,
        'INVITE_BIDS_START' => 0,
        'INVITE_BIDS_SUCCEED' => 0,
        'REPAYMENT' => 0,
        'FINISHED' => 0,
      ),
    ),
    4 => array(
      'title' => '满标，等待放款',
      'operator' => 'in',
      'value' => array(
        'INVITE_BIDS_SUCCEED' => 'INVITE_BIDS_SUCCEED',
        'all' => 0,
        'UNAUDITED' => 0,
        'AUDITED' => 0,
        'INVITE_BIDS_START' => 0,
        'INVITE_BIDS_FAILED' => 0,
        'REPAYMENT' => 0,
        'FINISHED' => 0,
      ),
    ),
    5 => array(
      'title' => '等待还款',
      'operator' => 'in',
      'value' => array(
        'REPAYMENT' => 'REPAYMENT',
        'all' => 0,
        'UNAUDITED' => 0,
        'AUDITED' => 0,
        'INVITE_BIDS_START' => 0,
        'INVITE_BIDS_FAILED' => 0,
        'INVITE_BIDS_SUCCEED' => 0,
        'FINISHED' => 0,
      ),
    ),
    6 => array(
      'title' => '还款完毕',
      'operator' => 'in',
      'value' => array(
        'FINISHED' => 'FINISHED',
        'all' => 0,
        'UNAUDITED' => 0,
        'AUDITED' => 0,
        'INVITE_BIDS_START' => 0,
        'INVITE_BIDS_FAILED' => 0,
        'INVITE_BIDS_SUCCEED' => 0,
        'REPAYMENT' => 0,
      ),
    ),
  );
  /* 过滤规则: Content: Title */
  $handler->display->display_options['filters']['title']['id'] = 'title';
  $handler->display->display_options['filters']['title']['table'] = 'node';
  $handler->display->display_options['filters']['title']['field'] = 'title';
  $handler->display->display_options['filters']['title']['exposed'] = TRUE;
  $handler->display->display_options['filters']['title']['expose']['operator_id'] = '';
  $handler->display->display_options['filters']['title']['expose']['label'] = '贷款标题';
  $handler->display->display_options['filters']['title']['expose']['operator'] = 'title_op';
  $handler->display->display_options['filters']['title']['expose']['identifier'] = 'title';
  $handler->display->display_options['filters']['title']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    6 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
    7 => 0,
  );
  $handler->display->display_options['path'] = 'issuing-manage';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = '贷款管理';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;

  /* Display: 贷款管理，导出 */
  $handler = $view->new_display('views_data_export', '贷款管理，导出', 'views_data_export_1');
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'views_data_export_xls';
  $handler->display->display_options['style_options']['provide_file'] = 0;
  $handler->display->display_options['style_options']['parent_sort'] = 0;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* 字段: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* 字段: 节点: 申请人 */
  $handler->display->display_options['fields']['field_applicant']['id'] = 'field_applicant';
  $handler->display->display_options['fields']['field_applicant']['table'] = 'field_data_field_applicant';
  $handler->display->display_options['fields']['field_applicant']['field'] = 'field_applicant';
  $handler->display->display_options['fields']['field_applicant']['settings'] = array(
    'user_reference_view_mode' => 'full',
  );
  /* 字段: Issuing: progress */
  $handler->display->display_options['fields']['progress']['id'] = 'progress';
  $handler->display->display_options['fields']['progress']['table'] = 'field_data_field_issuing';
  $handler->display->display_options['fields']['progress']['field'] = 'progress';
  $handler->display->display_options['fields']['progress']['label'] = '进度';
  /* 字段: Issuing: 贷款期限 */
  $handler->display->display_options['fields']['term']['id'] = 'term';
  $handler->display->display_options['fields']['term']['table'] = 'field_data_field_issuing';
  $handler->display->display_options['fields']['term']['field'] = 'term';
  /* 字段: Issuing: 年利率 */
  $handler->display->display_options['fields']['annual_rate']['id'] = 'annual_rate';
  $handler->display->display_options['fields']['annual_rate']['table'] = 'field_data_field_issuing';
  $handler->display->display_options['fields']['annual_rate']['field'] = 'annual_rate';
  /* 字段: Issuing: 贷款金额 */
  $handler->display->display_options['fields']['loan_amounts']['id'] = 'loan_amounts';
  $handler->display->display_options['fields']['loan_amounts']['table'] = 'field_data_field_issuing';
  $handler->display->display_options['fields']['loan_amounts']['field'] = 'loan_amounts';
  /* 字段: Issuing: 贷款状态 */
  $handler->display->display_options['fields']['status']['id'] = 'status';
  $handler->display->display_options['fields']['status']['table'] = 'field_data_field_issuing';
  $handler->display->display_options['fields']['status']['field'] = 'status';
  /* 字段: Issuing: 满标放款时间 */
  $handler->display->display_options['fields']['make_loans_time']['id'] = 'make_loans_time';
  $handler->display->display_options['fields']['make_loans_time']['table'] = 'field_data_field_issuing';
  $handler->display->display_options['fields']['make_loans_time']['field'] = 'make_loans_time';
  $handler->display->display_options['fields']['make_loans_time']['label'] = '放款时间';
  $handler->display->display_options['path'] = 'issuing-manage.xls';
  $handler->display->display_options['displays'] = array(
    'issuing_manage' => 'issuing_manage',
    'default' => 0,
    'issuing_list_bidding' => 0,
    'issuing_list_debtor' => 0,
    'issuing_list_front' => 0,
    'block_1' => 0,
    'issuing_list' => 0,
  );
  $handler->display->display_options['use_batch'] = 'batch';
  $handler->display->display_options['segment_size'] = '100';

  /* Display: 正在投标的贷款(用户) */
  $handler = $view->new_display('page', '正在投标的贷款(用户)', 'issuing_list_bidding');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = '正在投标的贷款';
  $handler->display->display_options['defaults']['access'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* 过滤规则: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'cowpro_issuing' => 'cowpro_issuing',
  );
  /* 过滤规则: 节点: 贷款表 (field_issuing:status) */
  $handler->display->display_options['filters']['field_issuing_status']['id'] = 'field_issuing_status';
  $handler->display->display_options['filters']['field_issuing_status']['table'] = 'field_data_field_issuing';
  $handler->display->display_options['filters']['field_issuing_status']['field'] = 'field_issuing_status';
  $handler->display->display_options['filters']['field_issuing_status']['value'] = array(
    'INVITE_BIDS_START' => 'INVITE_BIDS_START',
  );
  $handler->display->display_options['path'] = 'issuing-list/bidding';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = '投标中';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;

  /* Display: 我的贷款 */
  $handler = $view->new_display('page', '我的贷款', 'issuing_list_debtor');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = '我的贷款';
  $handler->display->display_options['defaults']['access'] = FALSE;
  $handler->display->display_options['access']['type'] = 'role';
  $handler->display->display_options['access']['role'] = array(
    1 => '1',
  );
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '5';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'list';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['row_options']['default_field_elements'] = FALSE;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['header'] = FALSE;
  /* 页眉: Global: Text area */
  $handler->display->display_options['header']['area']['id'] = 'area';
  $handler->display->display_options['header']['area']['table'] = 'views';
  $handler->display->display_options['header']['area']['field'] = 'area';
  $handler->display->display_options['header']['area']['content'] = '<div class="content_head container-fluid">
  <ul class="row">
    <li class="project col-md-8">投资项目<span class="inearnings">为投资者创造<i>34,844,127</i>元收益</span></li>
    <li class="inmoney col-md-4 text-right"><a href="/issuing-list" style="color:#ec5245">更多项目</a></li>
  </ul>
</div>';
  $handler->display->display_options['header']['area']['format'] = 'full_html';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* 字段: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['exclude'] = TRUE;
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  /* 字段: 节点: 申请人 */
  $handler->display->display_options['fields']['field_applicant']['id'] = 'field_applicant';
  $handler->display->display_options['fields']['field_applicant']['table'] = 'field_data_field_applicant';
  $handler->display->display_options['fields']['field_applicant']['field'] = 'field_applicant';
  $handler->display->display_options['fields']['field_applicant']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_applicant']['settings'] = array(
    'user_reference_view_mode' => 'full',
  );
  /* 字段: 节点: 贷款表 */
  $handler->display->display_options['fields']['field_issuing']['id'] = 'field_issuing';
  $handler->display->display_options['fields']['field_issuing']['table'] = 'field_data_field_issuing';
  $handler->display->display_options['fields']['field_issuing']['field'] = 'field_issuing';
  $handler->display->display_options['fields']['field_issuing']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_issuing']['click_sort_column'] = 'status';
  /* 字段: Issuing: Operations */
  $handler->display->display_options['fields']['view_issuing']['id'] = 'view_issuing';
  $handler->display->display_options['fields']['view_issuing']['table'] = 'field_data_field_issuing';
  $handler->display->display_options['fields']['view_issuing']['field'] = 'view_issuing';
  $handler->display->display_options['fields']['view_issuing']['label'] = '操作';
  $handler->display->display_options['fields']['view_issuing']['exclude'] = TRUE;
  $handler->display->display_options['fields']['view_issuing']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['view_issuing']['add_destination'] = 1;
  /* 字段: Issuing: progress */
  $handler->display->display_options['fields']['progress']['id'] = 'progress';
  $handler->display->display_options['fields']['progress']['table'] = 'field_data_field_issuing';
  $handler->display->display_options['fields']['progress']['field'] = 'progress';
  $handler->display->display_options['fields']['progress']['label'] = '';
  $handler->display->display_options['fields']['progress']['exclude'] = TRUE;
  $handler->display->display_options['fields']['progress']['element_label_colon'] = FALSE;
  /* 字段: Global: PHP */
  $handler->display->display_options['fields']['php']['id'] = 'php';
  $handler->display->display_options['fields']['php']['table'] = 'views';
  $handler->display->display_options['fields']['php']['field'] = 'php';
  $handler->display->display_options['fields']['php']['label'] = '';
  $handler->display->display_options['fields']['php']['exclude'] = TRUE;
  $handler->display->display_options['fields']['php']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['php']['use_php_setup'] = 0;
  $handler->display->display_options['fields']['php']['php_output'] = '<?php
$node_id = $data->nid;
$node_url = drupal_get_path_alias(\'node/\' . $node_id) ; //url 转化
?>


<ul class="title1">
 <li> <a id="loanname" title="<?php print $data->node_title; ?>" href="<?php print $node_url; ?>"> <?php print $data->node_title; ?> </a> </li>
</ul>

';
  $handler->display->display_options['fields']['php']['use_php_click_sortable'] = '0';
  $handler->display->display_options['fields']['php']['php_click_sortable'] = '';
  /* 字段: Global: PHP */
  $handler->display->display_options['fields']['php_1']['id'] = 'php_1';
  $handler->display->display_options['fields']['php_1']['table'] = 'views';
  $handler->display->display_options['fields']['php_1']['field'] = 'php';
  $handler->display->display_options['fields']['php_1']['label'] = '';
  $handler->display->display_options['fields']['php_1']['exclude'] = TRUE;
  $handler->display->display_options['fields']['php_1']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['php_1']['use_php_setup'] = 0;
  $handler->display->display_options['fields']['php_1']['php_output'] = ' <?php
$uid = $data->_field_data[\'nid\'][\'entity\']->field_applicant[\'und\'][0][\'uid\'];
$user=user_load($uid);
$username=$user->name;

?>    

 <div class="col-md-2 the-nianhua">
      <span class="num-info"><?php print $data->_field_data[\'nid\'][\'entity\']->field_issuing[\'und\'][0][\'annual_rate\'] ; ?></span>
      <p class="text-info">预期年化收益率(%)</p>
      </div>
      <div class="col-md-2 the-qixian">
      <span class="num-info"><?php print $data->_field_data[\'nid\'][\'entity\']->field_issuing[\'und\'][0][\'loan_term\'] ; ?> </span>
      <p class="text-info">投资期限(天)</p>
      </div>
      <div class="col-md-2 the-jine">
      <span class="num-info"><?php print $data->_field_data[\'nid\'][\'entity\']->field_issuing[\'und\'][0][\'loan_amounts\'] ; ?></span>
      <p class="text-info">融资金额(元)</p>
      
      </div>
      <div class="col-md-2 the-huaik">  <span class="num-info"><?php print $username ; ?></span>
      <p class="text-info">第一还款源</p></div>';
  $handler->display->display_options['fields']['php_1']['use_php_click_sortable'] = '0';
  $handler->display->display_options['fields']['php_1']['php_click_sortable'] = '';
  /* 字段: Global: PHP */
  $handler->display->display_options['fields']['php_2']['id'] = 'php_2';
  $handler->display->display_options['fields']['php_2']['table'] = 'views';
  $handler->display->display_options['fields']['php_2']['field'] = 'php';
  $handler->display->display_options['fields']['php_2']['label'] = '';
  $handler->display->display_options['fields']['php_2']['exclude'] = TRUE;
  $handler->display->display_options['fields']['php_2']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['php_2']['use_php_setup'] = 0;
  $handler->display->display_options['fields']['php_2']['php_output'] = '<?php
$node_id = $data->nid;
$node_url = drupal_get_path_alias(\'node/\' . $node_id) ; //url 转化

?>
<a href="<?php print $node_url; ?>" target="_blank" title="立即投资" class="loan_bg_red">立即投资</a>';
  $handler->display->display_options['fields']['php_2']['use_php_click_sortable'] = '0';
  $handler->display->display_options['fields']['php_2']['php_click_sortable'] = '';
  /* 字段: Global: Custom text */
  $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['table'] = 'views';
  $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['label'] = '';
  $handler->display->display_options['fields']['nothing']['alter']['text'] = '<div class="content_foot foott"> [php]
  <div class="clearfix content_all container-fluid">
    <div class="row"> [php_1]
      <div class="col-md-2 the-baifen">
        <div class="jdt_ph">
          <div class="jqm-round-wrap">
            <div class="jqm-round-bg"></div>
            <canvas  class="jqm-round-sector" height="200" width="200"></canvas>
            <div class="jqm-round-circle">
              <p>[progress]%</p>
            </div>
          </div>
        </div>
      </div>
      <div class="col-md-2 the-xiangx">[view_issuing] </div>
    </div>
  </div>
</div>
';
  $handler->display->display_options['fields']['nothing']['element_label_colon'] = FALSE;
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* 上下文过滤器: 节点: 申请人 (field_applicant) */
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
  /* 过滤规则: Content: Type */
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

  /* Display: 全部贷款(首页) */
  $handler = $view->new_display('page', '全部贷款(首页)', 'issuing_list_front');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = '全部贷款';
  $handler->display->display_options['defaults']['access'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['defaults']['cache'] = FALSE;
  $handler->display->display_options['cache']['type'] = 'time';
  $handler->display->display_options['cache']['results_lifespan'] = '300';
  $handler->display->display_options['cache']['results_lifespan_custom'] = '0';
  $handler->display->display_options['cache']['output_lifespan'] = '300';
  $handler->display->display_options['cache']['output_lifespan_custom'] = '0';
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* 过滤规则: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'cowpro_issuing' => 'cowpro_issuing',
  );
  /* 过滤规则: 节点: 贷款表 (field_issuing:status) */
  $handler->display->display_options['filters']['field_issuing_status']['id'] = 'field_issuing_status';
  $handler->display->display_options['filters']['field_issuing_status']['table'] = 'field_data_field_issuing';
  $handler->display->display_options['filters']['field_issuing_status']['field'] = 'field_issuing_status';
  $handler->display->display_options['filters']['field_issuing_status']['operator'] = 'not in';
  $handler->display->display_options['filters']['field_issuing_status']['value'] = array(
    'UNAUDITED' => 'UNAUDITED',
  );
  $handler->display->display_options['path'] = 'issuing-list-front';
  $handler->display->display_options['menu']['title'] = '全部贷款';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;

  /* Display: 投资项目 */
  $handler = $view->new_display('block', '投资项目', 'block_1');
  $handler->display->display_options['defaults']['access'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['defaults']['cache'] = FALSE;
  $handler->display->display_options['cache']['type'] = 'time';
  $handler->display->display_options['cache']['results_lifespan'] = '300';
  $handler->display->display_options['cache']['results_lifespan_custom'] = '0';
  $handler->display->display_options['cache']['output_lifespan'] = '300';
  $handler->display->display_options['cache']['output_lifespan_custom'] = '0';
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '5';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'list';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['row_options']['default_field_elements'] = FALSE;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* 字段: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['exclude'] = TRUE;
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  /* 字段: 节点: 申请人 */
  $handler->display->display_options['fields']['field_applicant']['id'] = 'field_applicant';
  $handler->display->display_options['fields']['field_applicant']['table'] = 'field_data_field_applicant';
  $handler->display->display_options['fields']['field_applicant']['field'] = 'field_applicant';
  $handler->display->display_options['fields']['field_applicant']['label'] = '';
  $handler->display->display_options['fields']['field_applicant']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_applicant']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_applicant']['settings'] = array(
    'user_reference_view_mode' => 'full',
  );
  /* 字段: 节点: 贷款表 */
  $handler->display->display_options['fields']['field_issuing']['id'] = 'field_issuing';
  $handler->display->display_options['fields']['field_issuing']['table'] = 'field_data_field_issuing';
  $handler->display->display_options['fields']['field_issuing']['field'] = 'field_issuing';
  $handler->display->display_options['fields']['field_issuing']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_issuing']['click_sort_column'] = 'status';
  /* 字段: Issuing: Operations */
  $handler->display->display_options['fields']['view_issuing']['id'] = 'view_issuing';
  $handler->display->display_options['fields']['view_issuing']['table'] = 'field_data_field_issuing';
  $handler->display->display_options['fields']['view_issuing']['field'] = 'view_issuing';
  $handler->display->display_options['fields']['view_issuing']['label'] = '操作';
  $handler->display->display_options['fields']['view_issuing']['exclude'] = TRUE;
  $handler->display->display_options['fields']['view_issuing']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['view_issuing']['add_destination'] = 1;
  /* 字段: Issuing: progress */
  $handler->display->display_options['fields']['progress']['id'] = 'progress';
  $handler->display->display_options['fields']['progress']['table'] = 'field_data_field_issuing';
  $handler->display->display_options['fields']['progress']['field'] = 'progress';
  $handler->display->display_options['fields']['progress']['label'] = '';
  $handler->display->display_options['fields']['progress']['exclude'] = TRUE;
  $handler->display->display_options['fields']['progress']['element_label_colon'] = FALSE;
  /* 字段: Global: PHP */
  $handler->display->display_options['fields']['php']['id'] = 'php';
  $handler->display->display_options['fields']['php']['table'] = 'views';
  $handler->display->display_options['fields']['php']['field'] = 'php';
  $handler->display->display_options['fields']['php']['label'] = '';
  $handler->display->display_options['fields']['php']['exclude'] = TRUE;
  $handler->display->display_options['fields']['php']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['php']['use_php_setup'] = 0;
  $handler->display->display_options['fields']['php']['php_output'] = '<?php
$node_id = $data->nid;
$node_url = drupal_get_path_alias(\'node/\' . $node_id) ; //url 转化
?>


<ul class="title1">
 <li> <a id="loanname" title="<?php print $data->node_title; ?>" href="<?php print $node_url; ?>"> <?php print $data->node_title; ?> </a> </li>
</ul>

';
  $handler->display->display_options['fields']['php']['use_php_click_sortable'] = '0';
  $handler->display->display_options['fields']['php']['php_click_sortable'] = '';
  /* 字段: Global: PHP */
  $handler->display->display_options['fields']['php_1']['id'] = 'php_1';
  $handler->display->display_options['fields']['php_1']['table'] = 'views';
  $handler->display->display_options['fields']['php_1']['field'] = 'php';
  $handler->display->display_options['fields']['php_1']['label'] = '';
  $handler->display->display_options['fields']['php_1']['exclude'] = TRUE;
  $handler->display->display_options['fields']['php_1']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['php_1']['use_php_setup'] = 0;
  $handler->display->display_options['fields']['php_1']['php_output'] = ' <?php
	include_once drupal_get_path(\'module\', \'cowpro_issuing\') . \'/includes/cowpro_issuing.repayment_schedule.fun.inc\';
	$method_repayment_readable = _cowpro_issuing_get_readable_repayment_method($data->_field_data[\'nid\'][\'entity\']->field_issuing[\'und\'][0][\'method_repayment\']);

$uid = $data->_field_data[\'nid\'][\'entity\']->field_applicant[\'und\'][0][\'uid\'];
$u=user_load($uid);
$username=$u->name;
global $user;
if ($user->uid != $u->uid) {
    if (mb_strlen($username) < 11) {
               		$username = mb_substr($username, 0, 2) . \'***\';
               	} else {
               		$username = mb_substr($username, 0, 4) . \'****\' . mb_substr($username, -3, 3);
               	}
               }
?>    

 <div class="col-md-2 the-nianhua">
      <span class="num-info"><?php print $data->_field_data[\'nid\'][\'entity\']->field_issuing[\'und\'][0][\'annual_rate\'] ; ?></span>
      <p class="text-info">预期年化收益率(%)</p>
      </div>
      <div class="col-md-2 the-qixian">
      <span class="num-info"><?php include_once drupal_get_path(\'module\', \'cowpro_issuing\') . \'/includes/cowpro_issuing.repayment_schedule.fun.inc\'; print _cowpro_issuing_get_readable_loan_term($data->_field_data[\'nid\'][\'entity\']->field_issuing[\'und\'][0][\'loan_term\']) ; ?> </span>
      <p class="text-info">投资期限</p>
      </div>
      <div class="col-md-2 the-jine">
      <span class="num-info"><?php print $data->_field_data[\'nid\'][\'entity\']->field_issuing[\'und\'][0][\'loan_amounts\'] ; ?></span>
      <p class="text-info">融资金额(元)</p>
      
      </div>
      <div class="col-md-2 the-huankuan">  <span class="num-info"><?php print $method_repayment_readable; ?></span>
      <p class="text-info">还款方式</p></div>';
  $handler->display->display_options['fields']['php_1']['use_php_click_sortable'] = '0';
  $handler->display->display_options['fields']['php_1']['php_click_sortable'] = '';
  /* 字段: Global: PHP */
  $handler->display->display_options['fields']['php_2']['id'] = 'php_2';
  $handler->display->display_options['fields']['php_2']['table'] = 'views';
  $handler->display->display_options['fields']['php_2']['field'] = 'php';
  $handler->display->display_options['fields']['php_2']['label'] = '';
  $handler->display->display_options['fields']['php_2']['exclude'] = TRUE;
  $handler->display->display_options['fields']['php_2']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['php_2']['use_php_setup'] = 0;
  $handler->display->display_options['fields']['php_2']['php_output'] = '<?php
$node_id = $data->nid;
$node_url = drupal_get_path_alias(\'node/\' . $node_id) ; //url 转化

?>
';
  $handler->display->display_options['fields']['php_2']['use_php_click_sortable'] = '0';
  $handler->display->display_options['fields']['php_2']['php_click_sortable'] = '';
  /* 字段: Global: View result counter */
  $handler->display->display_options['fields']['counter']['id'] = 'counter';
  $handler->display->display_options['fields']['counter']['table'] = 'views';
  $handler->display->display_options['fields']['counter']['field'] = 'counter';
  $handler->display->display_options['fields']['counter']['label'] = '';
  $handler->display->display_options['fields']['counter']['exclude'] = TRUE;
  $handler->display->display_options['fields']['counter']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['counter']['counter_start'] = '1';
  $handler->display->display_options['fields']['counter']['reverse'] = 0;
  /* 字段: Global: Custom text */
  $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['table'] = 'views';
  $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['label'] = '';
  $handler->display->display_options['fields']['nothing']['alter']['text'] = '<div class="content_foot foott">
[php]
  <div class="clearfix content_all container-fluid">
    <div class="row">
[php_1] 
      <div class="col-md-2 the-baifen"><div class="jdt_ph">
  <div class="jqm-round-wrap">
    <div class="jqm-round-bg"></div>
    <canvas id="jqm-round-sector[counter]" class="jqm-round-sector" height="200" width="200"></canvas>
    <div class="jqm-round-circle">
      <p>[progress]%</p>
    </div>
  </div>
</div></div>
<div class="col-md-2 the-xiangx">[php_2] [view_issuing]  </div>      
    </div>
  </div>
</div>
';
  $handler->display->display_options['fields']['nothing']['element_label_colon'] = FALSE;
  $handler->display->display_options['defaults']['sorts'] = FALSE;
  /* 排序标准: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* 过滤规则: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'cowpro_issuing' => 'cowpro_issuing',
  );
  /* 过滤规则: 节点: 贷款表 (field_issuing:status) */
  $handler->display->display_options['filters']['field_issuing_status']['id'] = 'field_issuing_status';
  $handler->display->display_options['filters']['field_issuing_status']['table'] = 'field_data_field_issuing';
  $handler->display->display_options['filters']['field_issuing_status']['field'] = 'field_issuing_status';
  $handler->display->display_options['filters']['field_issuing_status']['operator'] = 'not in';
  $handler->display->display_options['filters']['field_issuing_status']['value'] = array(
    'INVITE_BIDS_FAILED' => 'INVITE_BIDS_FAILED',
  );

  /* Display: 全部贷款 */
  $handler = $view->new_display('page', '全部贷款', 'issuing_list');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = '全部贷款';
  $handler->display->display_options['defaults']['css_class'] = FALSE;
  $handler->display->display_options['css_class'] = 'mobile-device-only';
  $handler->display->display_options['defaults']['access'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['defaults']['exposed_form'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'better_exposed_filters';
  $handler->display->display_options['exposed_form']['options']['submit_button'] = '应用';
  $handler->display->display_options['exposed_form']['options']['reset_button_label'] = '重置';
  $handler->display->display_options['exposed_form']['options']['exposed_sorts_label'] = '排序依据';
  $handler->display->display_options['exposed_form']['options']['sort_asc_label'] = '升序';
  $handler->display->display_options['exposed_form']['options']['sort_desc_label'] = '降序';
  $handler->display->display_options['exposed_form']['options']['autosubmit'] = TRUE;
  $handler->display->display_options['exposed_form']['options']['bef'] = array(
    'general' => array(
      'input_required' => 0,
      'text_input_required' => array(
        'text_input_required' => array(
          'value' => 'Select any filter and click on Apply to see results',
          'format' => 'filtered_html',
        ),
      ),
      'allow_secondary' => 0,
      'secondary_label' => '高级选项',
      'secondary_collapse_override' => '0',
    ),
    'field_issuing_status_1' => array(
      'bef_format' => 'bef_links',
      'more_options' => array(
        'bef_select_all_none' => 1,
        'bef_collapsible' => 0,
        'autosubmit' => 0,
        'is_secondary' => 0,
        'any_label' => '全部',
        'bef_filter_description' => '',
        'tokens' => array(
          'available' => array(
            0 => 'global_types',
          ),
        ),
        'rewrite' => array(
          'filter_rewrite_values' => '',
        ),
      ),
    ),
    'field_issuing_loan_term' => array(
      'bef_format' => 'bef_links',
      'slider_options' => array(
        'bef_slider_min' => '0',
        'bef_slider_max' => '99999',
        'bef_slider_step' => '1',
        'bef_slider_animate' => '',
        'bef_slider_orientation' => 'horizontal',
      ),
      'more_options' => array(
        'bef_select_all_none' => FALSE,
        'bef_collapsible' => 0,
        'autosubmit' => 0,
        'is_secondary' => 0,
        'any_label' => '全部',
        'bef_filter_description' => '',
        'tokens' => array(
          'available' => array(
            0 => 'global_types',
          ),
        ),
        'rewrite' => array(
          'filter_rewrite_values' => '',
        ),
      ),
    ),
    'field_issuing_annual_rate' => array(
      'bef_format' => 'bef_links',
      'slider_options' => array(
        'bef_slider_min' => '0',
        'bef_slider_max' => '99999',
        'bef_slider_step' => '1',
        'bef_slider_animate' => '',
        'bef_slider_orientation' => 'horizontal',
      ),
      'more_options' => array(
        'bef_select_all_none' => FALSE,
        'bef_collapsible' => 0,
        'autosubmit' => 0,
        'is_secondary' => 0,
        'any_label' => '全部',
        'bef_filter_description' => '',
        'tokens' => array(
          'available' => array(
            0 => 'global_types',
          ),
        ),
        'rewrite' => array(
          'filter_rewrite_values' => '',
        ),
      ),
    ),
  );
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'load_more';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
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
  $handler->display->display_options['pager']['options']['waypoint']['infinite'] = 1;
  $handler->display->display_options['pager']['options']['more_button_text'] = '加载更多';
  $handler->display->display_options['pager']['options']['more_button_empty_text'] = '没有更多数据了';
  $handler->display->display_options['pager']['options']['advance']['content_class'] = '.view-content';
  $handler->display->display_options['pager']['options']['effects']['speed'] = 'slow';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'list';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['row_options']['default_field_elements'] = FALSE;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['exposed_block'] = TRUE;
  $handler->display->display_options['defaults']['header'] = FALSE;
  /* 页眉: Global: Text area */
  $handler->display->display_options['header']['area']['id'] = 'area';
  $handler->display->display_options['header']['area']['table'] = 'views';
  $handler->display->display_options['header']['area']['field'] = 'area';
  $handler->display->display_options['header']['area']['empty'] = TRUE;
  $handler->display->display_options['header']['area']['content'] = ' [block:views=-exp-all_issuing-issuing_list]';
  $handler->display->display_options['header']['area']['format'] = 'full_html';
  /* 页眉: Global: Result summary */
  $handler->display->display_options['header']['result']['id'] = 'result';
  $handler->display->display_options['header']['result']['table'] = 'views';
  $handler->display->display_options['header']['result']['field'] = 'result';
  $handler->display->display_options['header']['result']['empty'] = TRUE;
  $handler->display->display_options['header']['result']['content'] = '<p id="select_num">共为您找到<span id="total">@total</span>个标</p> ';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* 字段: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['exclude'] = TRUE;
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  /* 字段: 节点: 申请人 */
  $handler->display->display_options['fields']['field_applicant']['id'] = 'field_applicant';
  $handler->display->display_options['fields']['field_applicant']['table'] = 'field_data_field_applicant';
  $handler->display->display_options['fields']['field_applicant']['field'] = 'field_applicant';
  $handler->display->display_options['fields']['field_applicant']['label'] = '';
  $handler->display->display_options['fields']['field_applicant']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_applicant']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_applicant']['settings'] = array(
    'user_reference_view_mode' => 'full',
  );
  /* 字段: 节点: 贷款表 */
  $handler->display->display_options['fields']['field_issuing']['id'] = 'field_issuing';
  $handler->display->display_options['fields']['field_issuing']['table'] = 'field_data_field_issuing';
  $handler->display->display_options['fields']['field_issuing']['field'] = 'field_issuing';
  $handler->display->display_options['fields']['field_issuing']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_issuing']['click_sort_column'] = 'status';
  /* 字段: Issuing: Operations */
  $handler->display->display_options['fields']['view_issuing']['id'] = 'view_issuing';
  $handler->display->display_options['fields']['view_issuing']['table'] = 'field_data_field_issuing';
  $handler->display->display_options['fields']['view_issuing']['field'] = 'view_issuing';
  $handler->display->display_options['fields']['view_issuing']['label'] = '操作';
  $handler->display->display_options['fields']['view_issuing']['exclude'] = TRUE;
  $handler->display->display_options['fields']['view_issuing']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['view_issuing']['add_destination'] = 1;
  /* 字段: Issuing: progress */
  $handler->display->display_options['fields']['progress']['id'] = 'progress';
  $handler->display->display_options['fields']['progress']['table'] = 'field_data_field_issuing';
  $handler->display->display_options['fields']['progress']['field'] = 'progress';
  $handler->display->display_options['fields']['progress']['exclude'] = TRUE;
  /* 字段: Global: PHP */
  $handler->display->display_options['fields']['php']['id'] = 'php';
  $handler->display->display_options['fields']['php']['table'] = 'views';
  $handler->display->display_options['fields']['php']['field'] = 'php';
  $handler->display->display_options['fields']['php']['label'] = '';
  $handler->display->display_options['fields']['php']['exclude'] = TRUE;
  $handler->display->display_options['fields']['php']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['php']['use_php_setup'] = 0;
  $handler->display->display_options['fields']['php']['php_output'] = '<?php
$node_id = $data->nid;
$node_url = drupal_get_path_alias(\'node/\' . $node_id) ; //url 转化
?>


<ul class="title1">
 <li> <a id="loanname" title="<?php print $data->node_title; ?>" href="<?php print $node_url; ?>"> <?php print $data->node_title; ?> </a> </li>
</ul>

';
  $handler->display->display_options['fields']['php']['use_php_click_sortable'] = '0';
  $handler->display->display_options['fields']['php']['php_click_sortable'] = '';
  /* 字段: Global: PHP */
  $handler->display->display_options['fields']['php_1']['id'] = 'php_1';
  $handler->display->display_options['fields']['php_1']['table'] = 'views';
  $handler->display->display_options['fields']['php_1']['field'] = 'php';
  $handler->display->display_options['fields']['php_1']['label'] = '';
  $handler->display->display_options['fields']['php_1']['exclude'] = TRUE;
  $handler->display->display_options['fields']['php_1']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['php_1']['use_php_setup'] = 0;
  $handler->display->display_options['fields']['php_1']['php_output'] = ' <?php
$uid = $data->_field_data[\'nid\'][\'entity\']->field_applicant[\'und\'][0][\'uid\'];
$u=user_load($uid);
$username=$u->name;
global $user;
if ($user->uid != $u->uid) {
    if (mb_strlen($username) < 11) {
               		$username = mb_substr($username, 0, 2) . \'***\';
               	} else {
               		$username = mb_substr($username, 0, 4) . \'****\' . mb_substr($username, -3, 3);
               	}
               }
?>    

 <div class="col-md-2 the-nianhua">
      <span class="num-info"><?php print $data->_field_data[\'nid\'][\'entity\']->field_issuing[\'und\'][0][\'annual_rate\'] ; ?></span>
      <p class="text-info">预期年化收益率(%)</p>
      </div>
      <div class="col-md-2 the-qixian">
      <span class="num-info"><?php include_once drupal_get_path(\'module\', \'cowpro_issuing\') . \'/includes/cowpro_issuing.repayment_schedule.fun.inc\'; print _cowpro_issuing_get_readable_loan_term($data->_field_data[\'nid\'][\'entity\']->field_issuing[\'und\'][0][\'loan_term\']) ; ?> </span>
      <p class="text-info">投资期限</p>
      </div>
      <div class="col-md-2 the-jine">
      <span class="num-info"><?php print $data->_field_data[\'nid\'][\'entity\']->field_issuing[\'und\'][0][\'loan_amounts\'] ; ?></span>
      <p class="text-info">融资金额(元)</p>
      
      </div>
      <div class="col-md-2 the-huaik">  <span class="num-info"><?php /*print $username ; */?></span>
      <p class="text-info"><!-- 第一还款源--></p></div>';
  $handler->display->display_options['fields']['php_1']['use_php_click_sortable'] = '0';
  $handler->display->display_options['fields']['php_1']['php_click_sortable'] = '';
  /* 字段: Global: PHP */
  $handler->display->display_options['fields']['php_2']['id'] = 'php_2';
  $handler->display->display_options['fields']['php_2']['table'] = 'views';
  $handler->display->display_options['fields']['php_2']['field'] = 'php';
  $handler->display->display_options['fields']['php_2']['label'] = '';
  $handler->display->display_options['fields']['php_2']['exclude'] = TRUE;
  $handler->display->display_options['fields']['php_2']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['php_2']['use_php_setup'] = 0;
  $handler->display->display_options['fields']['php_2']['php_output'] = '<?php
$node_id = $data->nid;
$node_url = drupal_get_path_alias(\'node/\' . $node_id) ; //url 转化

?>
<a href="<?php print $node_url; ?>" target="_blank" title="立即投资" class="loan_bg_red">立即投资</a>';
  $handler->display->display_options['fields']['php_2']['use_php_click_sortable'] = '0';
  $handler->display->display_options['fields']['php_2']['php_click_sortable'] = '';
  /* 字段: Global: Custom text */
  $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['table'] = 'views';
  $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['label'] = '';
  $handler->display->display_options['fields']['nothing']['alter']['text'] = '<div class="content_foot foott"> [php]
  <div class="clearfix content_all container-fluid">
    <div class="row"> [php_1]
      <div class="col-md-2 the-baifen">
        <div class="jdt_ph">
          <div class="jqm-round-wrap">
            <div class="jqm-round-bg"></div>
            <canvas  class="jqm-round-sector" height="200" width="200"></canvas>
            <div class="jqm-round-circle">
              <p>[progress]%</p>
            </div>
          </div>
        </div>
      </div>
      <div class="col-md-2 the-xiangx">[view_issuing] </div>
    </div>
  </div>
</div>
';
  $handler->display->display_options['fields']['nothing']['element_label_colon'] = FALSE;
  $handler->display->display_options['defaults']['sorts'] = FALSE;
  /* 排序标准: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* 过滤规则: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'cowpro_issuing' => 'cowpro_issuing',
  );
  /* 过滤规则: 节点: 贷款表 (field_issuing:status) */
  $handler->display->display_options['filters']['field_issuing_status']['id'] = 'field_issuing_status';
  $handler->display->display_options['filters']['field_issuing_status']['table'] = 'field_data_field_issuing';
  $handler->display->display_options['filters']['field_issuing_status']['field'] = 'field_issuing_status';
  $handler->display->display_options['filters']['field_issuing_status']['operator'] = 'not in';
  $handler->display->display_options['filters']['field_issuing_status']['value'] = array(
    'UNAUDITED' => 'UNAUDITED',
  );
  /* 过滤规则: 节点: 贷款表 (field_issuing:status) */
  $handler->display->display_options['filters']['field_issuing_status_1']['id'] = 'field_issuing_status_1';
  $handler->display->display_options['filters']['field_issuing_status_1']['table'] = 'field_data_field_issuing';
  $handler->display->display_options['filters']['field_issuing_status_1']['field'] = 'field_issuing_status';
  $handler->display->display_options['filters']['field_issuing_status_1']['value'] = array(
    'INVITE_BIDS_START' => 'INVITE_BIDS_START',
    'INVITE_BIDS_SUCCEED' => 'INVITE_BIDS_SUCCEED',
    'REPAYMENT' => 'REPAYMENT',
    'FINISHED' => 'FINISHED',
  );
  $handler->display->display_options['filters']['field_issuing_status_1']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_issuing_status_1']['expose']['operator_id'] = 'field_issuing_status_1_op';
  $handler->display->display_options['filters']['field_issuing_status_1']['expose']['label'] = '项目状态：';
  $handler->display->display_options['filters']['field_issuing_status_1']['expose']['operator'] = 'field_issuing_status_1_op';
  $handler->display->display_options['filters']['field_issuing_status_1']['expose']['identifier'] = 'field_issuing_status_1';
  $handler->display->display_options['filters']['field_issuing_status_1']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    6 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
  );
  $handler->display->display_options['filters']['field_issuing_status_1']['expose']['reduce'] = TRUE;
  /* 过滤规则: 节点: 贷款表 (field_issuing:loan_term) */
  $handler->display->display_options['filters']['field_issuing_loan_term']['id'] = 'field_issuing_loan_term';
  $handler->display->display_options['filters']['field_issuing_loan_term']['table'] = 'field_data_field_issuing';
  $handler->display->display_options['filters']['field_issuing_loan_term']['field'] = 'field_issuing_loan_term';
  $handler->display->display_options['filters']['field_issuing_loan_term']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_issuing_loan_term']['expose']['operator_id'] = 'field_issuing_loan_term_op';
  $handler->display->display_options['filters']['field_issuing_loan_term']['expose']['label'] = '贷款表 (field_issuing:loan_term)';
  $handler->display->display_options['filters']['field_issuing_loan_term']['expose']['operator'] = 'field_issuing_loan_term_op';
  $handler->display->display_options['filters']['field_issuing_loan_term']['expose']['identifier'] = 'field_issuing_loan_term';
  $handler->display->display_options['filters']['field_issuing_loan_term']['is_grouped'] = TRUE;
  $handler->display->display_options['filters']['field_issuing_loan_term']['group_info']['label'] = '项目期限：';
  $handler->display->display_options['filters']['field_issuing_loan_term']['group_info']['identifier'] = 'field_issuing_loan_term';
  $handler->display->display_options['filters']['field_issuing_loan_term']['group_info']['group_items'] = array(
    1 => array(
      'title' => '30天以下',
      'operator' => '<=',
      'value' => array(
        'value' => '30',
        'min' => '',
        'max' => '',
      ),
    ),
    2 => array(
      'title' => '31-60天',
      'operator' => 'between',
      'value' => array(
        'value' => '',
        'min' => '31',
        'max' => '60',
      ),
    ),
    3 => array(
      'title' => '61-90天',
      'operator' => 'between',
      'value' => array(
        'value' => '',
        'min' => '61',
        'max' => '90',
      ),
    ),
    4 => array(
      'title' => '91-180天',
      'operator' => 'between',
      'value' => array(
        'value' => '',
        'min' => '91',
        'max' => '180',
      ),
    ),
  );
  /* 过滤规则: 节点: 贷款表 (field_issuing:annual_rate) */
  $handler->display->display_options['filters']['field_issuing_annual_rate']['id'] = 'field_issuing_annual_rate';
  $handler->display->display_options['filters']['field_issuing_annual_rate']['table'] = 'field_data_field_issuing';
  $handler->display->display_options['filters']['field_issuing_annual_rate']['field'] = 'field_issuing_annual_rate';
  $handler->display->display_options['filters']['field_issuing_annual_rate']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_issuing_annual_rate']['expose']['operator_id'] = 'field_issuing_annual_rate_op';
  $handler->display->display_options['filters']['field_issuing_annual_rate']['expose']['label'] = '贷款表 (field_issuing:annual_rate)';
  $handler->display->display_options['filters']['field_issuing_annual_rate']['expose']['operator'] = 'field_issuing_annual_rate_op';
  $handler->display->display_options['filters']['field_issuing_annual_rate']['expose']['identifier'] = 'field_issuing_annual_rate';
  $handler->display->display_options['filters']['field_issuing_annual_rate']['is_grouped'] = TRUE;
  $handler->display->display_options['filters']['field_issuing_annual_rate']['group_info']['label'] = '年化收益：';
  $handler->display->display_options['filters']['field_issuing_annual_rate']['group_info']['identifier'] = 'field_issuing_annual_rate';
  $handler->display->display_options['filters']['field_issuing_annual_rate']['group_info']['group_items'] = array(
    1 => array(
      'title' => '8%以下',
      'operator' => '<=',
      'value' => array(
        'value' => '8.00',
        'min' => '',
        'max' => '',
      ),
    ),
    2 => array(
      'title' => '8%-10%',
      'operator' => 'between',
      'value' => array(
        'value' => '',
        'min' => '8.01',
        'max' => '10.00',
      ),
    ),
    3 => array(
      'title' => '10%以上',
      'operator' => '>',
      'value' => array(
        'value' => '10',
        'min' => '10.01',
        'max' => '12.00',
      ),
    ),
  );
  /* 过滤规则: 节点: 贷款表 (field_issuing:status) */
  $handler->display->display_options['filters']['field_issuing_status_2']['id'] = 'field_issuing_status_2';
  $handler->display->display_options['filters']['field_issuing_status_2']['table'] = 'field_data_field_issuing';
  $handler->display->display_options['filters']['field_issuing_status_2']['field'] = 'field_issuing_status';
  $handler->display->display_options['filters']['field_issuing_status_2']['operator'] = 'not in';
  $handler->display->display_options['filters']['field_issuing_status_2']['value'] = array(
    'INVITE_BIDS_FAILED' => 'INVITE_BIDS_FAILED',
  );
  $handler->display->display_options['path'] = 'issuing-list';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = '全部贷款';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;
  $translatables['all_issuing'] = array(
    t('Master'),
    t('贷款管理，导出'),
    t('更多'),
    t('应用'),
    t('重置'),
    t('排序依据'),
    t('升序'),
    t('降序'),
    t('Select any filter and click on Apply to see results'),
    t('高级选项'),
    t('每页条目数'),
    t('- 全部 -'),
    t('偏移量'),
    t('« 第一页'),
    t('‹ 前一页'),
    t('下一页 ›'),
    t('末页 »'),
    t('<div class="content_head container-fluid">
  <ul class="row">
    <li class="project col-md-8">投资项目<span class="inearnings">-</span></li>
    <li class="inmoney col-md-4 text-right"><a href="/issuing-list" style="color:#ec5245">更多项目</a></li>
  </ul>
</div>'),
    t('<h1>暂无内容，等待添加！</h1>'),
    t('申请人'),
    t('贷款表'),
    t('操作'),
    t('进度'),
    t('贷款表 (field_issuing:status)'),
    t('贷款管理'),
    t('贷款期限'),
    t('年利率'),
    t('贷款金额'),
    t('状态'),
    t('放款时间'),
    t('贷款表状态'),
    t('贷款标题'),
    t('贷款状态'),
    t('正在投标的贷款(用户)'),
    t('正在投标的贷款'),
    t('我的贷款'),
    t('<div class="content_head container-fluid">
  <ul class="row">
    <li class="project col-md-8">投资项目<span class="inearnings">为投资者创造<i>34,844,127</i>元收益</span></li>
    <li class="inmoney col-md-4 text-right"><a href="/issuing-list" style="color:#ec5245">更多项目</a></li>
  </ul>
</div>'),
    t('<div class="content_foot foott"> [php]
  <div class="clearfix content_all container-fluid">
    <div class="row"> [php_1]
      <div class="col-md-2 the-baifen">
        <div class="jdt_ph">
          <div class="jqm-round-wrap">
            <div class="jqm-round-bg"></div>
            <canvas  class="jqm-round-sector" height="200" width="200"></canvas>
            <div class="jqm-round-circle">
              <p>[progress]%</p>
            </div>
          </div>
        </div>
      </div>
      <div class="col-md-2 the-xiangx">[view_issuing] </div>
    </div>
  </div>
</div>
'),
    t('全部'),
    t('全部贷款(首页)'),
    t('全部贷款'),
    t('投资项目'),
    t('<div class="content_foot foott">
[php]
  <div class="clearfix content_all container-fluid">
    <div class="row">
[php_1] 
      <div class="col-md-2 the-baifen"><div class="jdt_ph">
  <div class="jqm-round-wrap">
    <div class="jqm-round-bg"></div>
    <canvas id="jqm-round-sector[counter]" class="jqm-round-sector" height="200" width="200"></canvas>
    <div class="jqm-round-circle">
      <p>[progress]%</p>
    </div>
  </div>
</div></div>
<div class="col-md-2 the-xiangx">[php_2] [view_issuing]  </div>      
    </div>
  </div>
</div>
'),
    t('加载更多'),
    t('没有更多数据了'),
    t(' [block:views=-exp-all_issuing-issuing_list]'),
    t('<p id="select_num">共为您找到<span id="total">@total</span>个标</p> '),
    t('progress'),
    t('项目状态：'),
    t('贷款表 (field_issuing:loan_term)'),
    t('项目期限：'),
    t('贷款表 (field_issuing:annual_rate)'),
    t('年化收益：'),
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
  $handler->display->display_options['cache']['type'] = 'time';
  $handler->display->display_options['cache']['results_lifespan'] = '3600';
  $handler->display->display_options['cache']['results_lifespan_custom'] = '0';
  $handler->display->display_options['cache']['output_lifespan'] = '3600';
  $handler->display->display_options['cache']['output_lifespan_custom'] = '0';
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
  /* 字段: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* 字段: Issuing: Operations */
  $handler->display->display_options['fields']['view_node']['id'] = 'view_node';
  $handler->display->display_options['fields']['view_node']['table'] = 'field_data_field_issuing';
  $handler->display->display_options['fields']['view_node']['field'] = 'view_node';
  $handler->display->display_options['fields']['view_node']['label'] = '操作';
  $handler->display->display_options['fields']['view_node']['add_destination'] = 0;
  /* 排序标准: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* 过滤规则: Content: Type */
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
  $view->name = 'bankcard_search';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'cowpro_fund_bankcard';
  $view->human_name = '银行卡查询';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = '银行卡查询';
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
  $handler->display->display_options['pager']['options']['items_per_page'] = '30';
  $handler->display->display_options['pager']['options']['expose']['items_per_page_label'] = '每页条目数';
  $handler->display->display_options['pager']['options']['expose']['items_per_page_options_all_label'] = '- 全部 -';
  $handler->display->display_options['pager']['options']['expose']['offset_label'] = '偏移量';
  $handler->display->display_options['pager']['options']['tags']['first'] = '« 第一页';
  $handler->display->display_options['pager']['options']['tags']['previous'] = '‹ 前一页';
  $handler->display->display_options['pager']['options']['tags']['next'] = '下一页 ›';
  $handler->display->display_options['pager']['options']['tags']['last'] = '末页 »';
  $handler->display->display_options['style_plugin'] = 'table';
  /* 字段: 银行卡: 用户名 */
  $handler->display->display_options['fields']['uid']['id'] = 'uid';
  $handler->display->display_options['fields']['uid']['table'] = 'cowpro_fund_bankcard';
  $handler->display->display_options['fields']['uid']['field'] = 'uid';
  /* 字段: 银行卡: 银行卡号 */
  $handler->display->display_options['fields']['card_no']['id'] = 'card_no';
  $handler->display->display_options['fields']['card_no']['table'] = 'cowpro_fund_bankcard';
  $handler->display->display_options['fields']['card_no']['field'] = 'card_no';
  /* 字段: 银行卡: 持卡人姓名 */
  $handler->display->display_options['fields']['cardholder']['id'] = 'cardholder';
  $handler->display->display_options['fields']['cardholder']['table'] = 'cowpro_fund_bankcard';
  $handler->display->display_options['fields']['cardholder']['field'] = 'cardholder';
  /* 字段: 银行卡: 开户行 */
  $handler->display->display_options['fields']['bank_name']['id'] = 'bank_name';
  $handler->display->display_options['fields']['bank_name']['table'] = 'cowpro_fund_bankcard';
  $handler->display->display_options['fields']['bank_name']['field'] = 'bank_name';
  /* 字段: 银行卡: 开户行网点 */
  $handler->display->display_options['fields']['bank_branch']['id'] = 'bank_branch';
  $handler->display->display_options['fields']['bank_branch']['table'] = 'cowpro_fund_bankcard';
  $handler->display->display_options['fields']['bank_branch']['field'] = 'bank_branch';
  $handler->display->display_options['fields']['bank_branch']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['bank_branch']['hide_alter_empty'] = FALSE;
  /* 过滤规则: 银行卡: 用户ID */
  $handler->display->display_options['filters']['uid']['id'] = 'uid';
  $handler->display->display_options['filters']['uid']['table'] = 'cowpro_fund_bankcard';
  $handler->display->display_options['filters']['uid']['field'] = 'uid';
  $handler->display->display_options['filters']['uid']['exposed'] = TRUE;
  $handler->display->display_options['filters']['uid']['expose']['operator_id'] = '';
  $handler->display->display_options['filters']['uid']['expose']['label'] = '用户名';
  $handler->display->display_options['filters']['uid']['expose']['operator'] = 'uid_op';
  $handler->display->display_options['filters']['uid']['expose']['identifier'] = 'uid';
  $handler->display->display_options['filters']['uid']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    6 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
    7 => 0,
  );

  /* Display: 银行卡查询 */
  $handler = $view->new_display('page', '银行卡查询', 'page');
  $handler->display->display_options['path'] = 'bankcard-search';
  $translatables['bankcard_search'] = array(
    t('Master'),
    t('银行卡查询'),
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
    t('用户名'),
    t('银行卡号'),
    t('持卡人姓名'),
    t('开户行'),
    t('开户行网点'),
  );
  $export['bankcard_search'] = $view;

  $view = new view();
  $view->name = 'bid_list';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'cowpro_fund_journal';
  $view->human_name = '我的投资';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = '我的投资';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['use_more_text'] = '更多';
  $handler->display->display_options['access']['type'] = 'role';
  $handler->display->display_options['access']['role'] = array(
    4 => '4',
  );
  $handler->display->display_options['cache']['type'] = 'time';
  $handler->display->display_options['cache']['results_lifespan'] = '3600';
  $handler->display->display_options['cache']['results_lifespan_custom'] = '0';
  $handler->display->display_options['cache']['output_lifespan'] = '3600';
  $handler->display->display_options['cache']['output_lifespan_custom'] = '0';
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
  $handler->display->display_options['pager']['options']['tags']['first'] = '« 第一页';
  $handler->display->display_options['pager']['options']['tags']['previous'] = '‹ 前一页';
  $handler->display->display_options['pager']['options']['tags']['next'] = '下一页 ›';
  $handler->display->display_options['pager']['options']['tags']['last'] = '末页 »';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'journal_id' => 'journal_id',
    'title' => 'title',
    'field_issuing' => 'field_issuing',
    'amount' => 'amount',
    'created' => 'created',
    'view_issuing' => 'view_issuing',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'journal_id' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'title' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_issuing' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'amount' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'created' => array(
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
  /* 关联: 资金明细: issuing_id */
  $handler->display->display_options['relationships']['issuing_id']['id'] = 'issuing_id';
  $handler->display->display_options['relationships']['issuing_id']['table'] = 'cowpro_fund_journal';
  $handler->display->display_options['relationships']['issuing_id']['field'] = 'issuing_id';
  /* 字段: 资金明细: journal_id */
  $handler->display->display_options['fields']['journal_id']['id'] = 'journal_id';
  $handler->display->display_options['fields']['journal_id']['table'] = 'cowpro_fund_journal';
  $handler->display->display_options['fields']['journal_id']['field'] = 'journal_id';
  $handler->display->display_options['fields']['journal_id']['exclude'] = TRUE;
  /* 字段: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['relationship'] = 'issuing_id';
  $handler->display->display_options['fields']['title']['label'] = '标题';
  /* 字段: 节点: 贷款表 */
  $handler->display->display_options['fields']['field_issuing']['id'] = 'field_issuing';
  $handler->display->display_options['fields']['field_issuing']['table'] = 'field_data_field_issuing';
  $handler->display->display_options['fields']['field_issuing']['field'] = 'field_issuing';
  $handler->display->display_options['fields']['field_issuing']['relationship'] = 'issuing_id';
  $handler->display->display_options['fields']['field_issuing']['click_sort_column'] = 'status';
  /* 字段: 资金明细: amount */
  $handler->display->display_options['fields']['amount']['id'] = 'amount';
  $handler->display->display_options['fields']['amount']['table'] = 'cowpro_fund_journal';
  $handler->display->display_options['fields']['amount']['field'] = 'amount';
  $handler->display->display_options['fields']['amount']['label'] = '投资金额';
  /* 字段: 资金明细: 时间 */
  $handler->display->display_options['fields']['created']['id'] = 'created';
  $handler->display->display_options['fields']['created']['table'] = 'cowpro_fund_journal';
  $handler->display->display_options['fields']['created']['field'] = 'created';
  $handler->display->display_options['fields']['created']['label'] = '投资时间';
  $handler->display->display_options['fields']['created']['date_format'] = 'custom';
  $handler->display->display_options['fields']['created']['custom_date_format'] = 'Y/m/d';
  $handler->display->display_options['fields']['created']['second_date_format'] = 'long';
  /* 字段: Issuing: repayment progress */
  $handler->display->display_options['fields']['repayment_progress']['id'] = 'repayment_progress';
  $handler->display->display_options['fields']['repayment_progress']['table'] = 'field_data_field_issuing';
  $handler->display->display_options['fields']['repayment_progress']['field'] = 'repayment_progress';
  $handler->display->display_options['fields']['repayment_progress']['relationship'] = 'issuing_id';
  $handler->display->display_options['fields']['repayment_progress']['label'] = '还款进度%';
  /* 排序标准: 资金明细: 时间 */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'cowpro_fund_journal';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* 上下文过滤器: 资金明细: 用户 */
  $handler->display->display_options['arguments']['uid']['id'] = 'uid';
  $handler->display->display_options['arguments']['uid']['table'] = 'cowpro_fund_journal';
  $handler->display->display_options['arguments']['uid']['field'] = 'uid';
  $handler->display->display_options['arguments']['uid']['default_action'] = 'default';
  $handler->display->display_options['arguments']['uid']['exception']['title'] = '全部';
  $handler->display->display_options['arguments']['uid']['default_argument_type'] = 'current_user';
  $handler->display->display_options['arguments']['uid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['uid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['uid']['summary_options']['items_per_page'] = '25';
  /* 过滤规则: 资金明细: 业务类型 */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'cowpro_fund_journal';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'BID' => 'BID',
  );
  /* 过滤规则: 资金明细: 结果 */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'cowpro_fund_journal';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = array(
    1 => '1',
  );

  /* Display: 我的投资 */
  $handler = $view->new_display('page', '我的投资', 'page');
  $handler->display->display_options['path'] = 'issuing-list/bid';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = '我的投资';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;
  $translatables['bid_list'] = array(
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
    t('« 第一页'),
    t('‹ 前一页'),
    t('下一页 ›'),
    t('末页 »'),
    t('贷款申请表'),
    t('journal_id'),
    t('.'),
    t(','),
    t('标题'),
    t('贷款表'),
    t('投资金额'),
    t('投资时间'),
    t('还款进度%'),
    t('全部'),
  );
  $export['bid_list'] = $view;

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
  $handler->display->display_options['cache']['type'] = 'time';
  $handler->display->display_options['cache']['results_lifespan'] = '3600';
  $handler->display->display_options['cache']['results_lifespan_custom'] = '0';
  $handler->display->display_options['cache']['output_lifespan'] = '3600';
  $handler->display->display_options['cache']['output_lifespan_custom'] = '0';
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
  /* 字段: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* 字段: Issuing: Operations */
  $handler->display->display_options['fields']['view_node']['id'] = 'view_node';
  $handler->display->display_options['fields']['view_node']['table'] = 'field_data_field_issuing';
  $handler->display->display_options['fields']['view_node']['field'] = 'view_node';
  $handler->display->display_options['fields']['view_node']['label'] = '操作';
  $handler->display->display_options['fields']['view_node']['add_destination'] = 0;
  /* 排序标准: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* 过滤规则: Content: Type */
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
  $view->name = 'due_in_list';
  $view->description = '';
  $view->tag = 'cowpro';
  $view->base_table = 'cowpro_repayment_schedule';
  $view->human_name = '待还款清单';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = '待还款清单';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['use_more_text'] = '更多';
  $handler->display->display_options['access']['type'] = 'role';
  $handler->display->display_options['access']['role'] = array(
    3 => '3',
  );
  $handler->display->display_options['cache']['type'] = 'time';
  $handler->display->display_options['cache']['results_lifespan'] = '3600';
  $handler->display->display_options['cache']['results_lifespan_custom'] = '0';
  $handler->display->display_options['cache']['output_lifespan'] = '3600';
  $handler->display->display_options['cache']['output_lifespan_custom'] = '0';
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
  $handler->display->display_options['pager']['options']['tags']['first'] = '« 第一页';
  $handler->display->display_options['pager']['options']['tags']['previous'] = '‹ 前一页';
  $handler->display->display_options['pager']['options']['tags']['next'] = '下一页 ›';
  $handler->display->display_options['pager']['options']['tags']['last'] = '末页 »';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'issuing_id' => 'issuing_id',
    'payer_uid' => 'payer_uid',
    'deadline' => 'deadline',
    'payable_amount' => 'payable_amount',
    'status' => 'status',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'issuing_id' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'payer_uid' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'deadline' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'payable_amount' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'status' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  $handler->display->display_options['style_options']['empty_table'] = TRUE;
  /* 字段: 还款详情: 贷款名称 */
  $handler->display->display_options['fields']['issuing_id']['id'] = 'issuing_id';
  $handler->display->display_options['fields']['issuing_id']['table'] = 'cowpro_repayment_schedule';
  $handler->display->display_options['fields']['issuing_id']['field'] = 'issuing_id';
  /* 字段: 还款详情: period */
  $handler->display->display_options['fields']['period']['id'] = 'period';
  $handler->display->display_options['fields']['period']['table'] = 'cowpro_repayment_schedule';
  $handler->display->display_options['fields']['period']['field'] = 'period';
  $handler->display->display_options['fields']['period']['label'] = '期次';
  $handler->display->display_options['fields']['period']['separator'] = '';
  /* 字段: 还款详情: period_total */
  $handler->display->display_options['fields']['period_total']['id'] = 'period_total';
  $handler->display->display_options['fields']['period_total']['table'] = 'cowpro_repayment_schedule';
  $handler->display->display_options['fields']['period_total']['field'] = 'period_total';
  $handler->display->display_options['fields']['period_total']['label'] = '总期次';
  $handler->display->display_options['fields']['period_total']['separator'] = '';
  /* 字段: 还款详情: 最后还款日 */
  $handler->display->display_options['fields']['deadline']['id'] = 'deadline';
  $handler->display->display_options['fields']['deadline']['table'] = 'cowpro_repayment_schedule';
  $handler->display->display_options['fields']['deadline']['field'] = 'deadline';
  $handler->display->display_options['fields']['deadline']['date_format'] = 'custom';
  $handler->display->display_options['fields']['deadline']['custom_date_format'] = 'Y/m/d';
  $handler->display->display_options['fields']['deadline']['second_date_format'] = 'long';
  /* 字段: 还款详情: payable_amount */
  $handler->display->display_options['fields']['payable_amount']['id'] = 'payable_amount';
  $handler->display->display_options['fields']['payable_amount']['table'] = 'cowpro_repayment_schedule';
  $handler->display->display_options['fields']['payable_amount']['field'] = 'payable_amount';
  $handler->display->display_options['fields']['payable_amount']['label'] = '应还款金额';
  /* 字段: 还款详情: 状态 */
  $handler->display->display_options['fields']['status']['id'] = 'status';
  $handler->display->display_options['fields']['status']['table'] = 'cowpro_repayment_schedule';
  $handler->display->display_options['fields']['status']['field'] = 'status';
  /* 排序标准: 还款详情: 最后还款日 */
  $handler->display->display_options['sorts']['deadline']['id'] = 'deadline';
  $handler->display->display_options['sorts']['deadline']['table'] = 'cowpro_repayment_schedule';
  $handler->display->display_options['sorts']['deadline']['field'] = 'deadline';
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
  /* 过滤规则: 还款详情: 最后还款日 */
  $handler->display->display_options['filters']['deadline']['id'] = 'deadline';
  $handler->display->display_options['filters']['deadline']['table'] = 'cowpro_repayment_schedule';
  $handler->display->display_options['filters']['deadline']['field'] = 'deadline';
  $handler->display->display_options['filters']['deadline']['operator'] = '<=';
  $handler->display->display_options['filters']['deadline']['value']['value'] = '+31 day';
  $handler->display->display_options['filters']['deadline']['value']['type'] = 'offset';
  $handler->display->display_options['filters']['deadline']['exposed'] = TRUE;
  $handler->display->display_options['filters']['deadline']['expose']['operator_id'] = 'deadline_op';
  $handler->display->display_options['filters']['deadline']['expose']['label'] = '最后还款日';
  $handler->display->display_options['filters']['deadline']['expose']['operator'] = 'deadline_op';
  $handler->display->display_options['filters']['deadline']['expose']['identifier'] = 'deadline';
  /* 过滤规则: 还款详情: 状态 */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'cowpro_repayment_schedule';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = array(
    'WAITING_FOR' => 'WAITING_FOR',
  );
  $handler->display->display_options['filters']['status']['exposed'] = TRUE;
  $handler->display->display_options['filters']['status']['expose']['operator_id'] = 'status_op';
  $handler->display->display_options['filters']['status']['expose']['label'] = '状态';
  $handler->display->display_options['filters']['status']['expose']['operator'] = 'status_op';
  $handler->display->display_options['filters']['status']['expose']['identifier'] = 'status';
  /* 过滤规则: 还款详情: 收款方用户ID */
  $handler->display->display_options['filters']['receiver_uid']['id'] = 'receiver_uid';
  $handler->display->display_options['filters']['receiver_uid']['table'] = 'cowpro_repayment_schedule';
  $handler->display->display_options['filters']['receiver_uid']['field'] = 'receiver_uid';
  $handler->display->display_options['filters']['receiver_uid']['value']['value'] = '-1';

  /* Display: 待还款清单（管理员） */
  $handler = $view->new_display('page', '待还款清单（管理员）', 'due_in_list_manager');
  $handler->display->display_options['defaults']['access'] = FALSE;
  $handler->display->display_options['access']['type'] = 'role';
  $handler->display->display_options['access']['role'] = array(
    3 => '3',
  );
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* 字段: 还款详情: 贷款名称 */
  $handler->display->display_options['fields']['issuing_id']['id'] = 'issuing_id';
  $handler->display->display_options['fields']['issuing_id']['table'] = 'cowpro_repayment_schedule';
  $handler->display->display_options['fields']['issuing_id']['field'] = 'issuing_id';
  /* 字段: 还款详情: 付款方 */
  $handler->display->display_options['fields']['payer_uid']['id'] = 'payer_uid';
  $handler->display->display_options['fields']['payer_uid']['table'] = 'cowpro_repayment_schedule';
  $handler->display->display_options['fields']['payer_uid']['field'] = 'payer_uid';
  $handler->display->display_options['fields']['payer_uid']['element_label_colon'] = FALSE;
  /* 字段: 还款详情: period */
  $handler->display->display_options['fields']['period']['id'] = 'period';
  $handler->display->display_options['fields']['period']['table'] = 'cowpro_repayment_schedule';
  $handler->display->display_options['fields']['period']['field'] = 'period';
  $handler->display->display_options['fields']['period']['label'] = '期次';
  $handler->display->display_options['fields']['period']['separator'] = '';
  /* 字段: 还款详情: period_total */
  $handler->display->display_options['fields']['period_total']['id'] = 'period_total';
  $handler->display->display_options['fields']['period_total']['table'] = 'cowpro_repayment_schedule';
  $handler->display->display_options['fields']['period_total']['field'] = 'period_total';
  $handler->display->display_options['fields']['period_total']['label'] = '总期次';
  $handler->display->display_options['fields']['period_total']['separator'] = '';
  /* 字段: 还款详情: 最后还款日 */
  $handler->display->display_options['fields']['deadline']['id'] = 'deadline';
  $handler->display->display_options['fields']['deadline']['table'] = 'cowpro_repayment_schedule';
  $handler->display->display_options['fields']['deadline']['field'] = 'deadline';
  $handler->display->display_options['fields']['deadline']['date_format'] = 'custom';
  $handler->display->display_options['fields']['deadline']['custom_date_format'] = 'Y/m/d';
  $handler->display->display_options['fields']['deadline']['second_date_format'] = 'long';
  /* 字段: 还款详情: payable_amount */
  $handler->display->display_options['fields']['payable_amount']['id'] = 'payable_amount';
  $handler->display->display_options['fields']['payable_amount']['table'] = 'cowpro_repayment_schedule';
  $handler->display->display_options['fields']['payable_amount']['field'] = 'payable_amount';
  $handler->display->display_options['fields']['payable_amount']['label'] = '应还款金额';
  /* 字段: 还款详情: 状态 */
  $handler->display->display_options['fields']['status']['id'] = 'status';
  $handler->display->display_options['fields']['status']['table'] = 'cowpro_repayment_schedule';
  $handler->display->display_options['fields']['status']['field'] = 'status';
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* 过滤规则: 还款详情: 最后还款日 */
  $handler->display->display_options['filters']['deadline']['id'] = 'deadline';
  $handler->display->display_options['filters']['deadline']['table'] = 'cowpro_repayment_schedule';
  $handler->display->display_options['filters']['deadline']['field'] = 'deadline';
  $handler->display->display_options['filters']['deadline']['operator'] = 'between';
  $handler->display->display_options['filters']['deadline']['value']['value'] = '+31 day';
  $handler->display->display_options['filters']['deadline']['exposed'] = TRUE;
  $handler->display->display_options['filters']['deadline']['expose']['operator_id'] = 'deadline_op';
  $handler->display->display_options['filters']['deadline']['expose']['label'] = '最后还款日(格式：YYYY/MM/DD)';
  $handler->display->display_options['filters']['deadline']['expose']['operator'] = 'deadline_op';
  $handler->display->display_options['filters']['deadline']['expose']['identifier'] = 'deadline';
  $handler->display->display_options['filters']['deadline']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    6 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
    7 => 0,
  );
  /* 过滤规则: 还款详情: 状态 */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'cowpro_repayment_schedule';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = array(
    'WAITING_FOR' => 'WAITING_FOR',
    'COMPLETED' => 'COMPLETED',
  );
  $handler->display->display_options['filters']['status']['exposed'] = TRUE;
  $handler->display->display_options['filters']['status']['expose']['operator_id'] = 'status_op';
  $handler->display->display_options['filters']['status']['expose']['label'] = '状态';
  $handler->display->display_options['filters']['status']['expose']['operator'] = 'status_op';
  $handler->display->display_options['filters']['status']['expose']['identifier'] = 'status';
  $handler->display->display_options['filters']['status']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    6 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
    7 => 0,
  );
  $handler->display->display_options['filters']['status']['expose']['reduce'] = TRUE;
  /* 过滤规则: 还款详情: 收款方用户ID */
  $handler->display->display_options['filters']['receiver_uid']['id'] = 'receiver_uid';
  $handler->display->display_options['filters']['receiver_uid']['table'] = 'cowpro_repayment_schedule';
  $handler->display->display_options['filters']['receiver_uid']['field'] = 'receiver_uid';
  $handler->display->display_options['filters']['receiver_uid']['value']['value'] = '-1';
  /* 过滤规则: 还款详情: 付款方用户ID */
  $handler->display->display_options['filters']['payer_uid']['id'] = 'payer_uid';
  $handler->display->display_options['filters']['payer_uid']['table'] = 'cowpro_repayment_schedule';
  $handler->display->display_options['filters']['payer_uid']['field'] = 'payer_uid';
  $handler->display->display_options['filters']['payer_uid']['value'] = -1;
  $handler->display->display_options['filters']['payer_uid']['exposed'] = TRUE;
  $handler->display->display_options['filters']['payer_uid']['expose']['operator_id'] = '';
  $handler->display->display_options['filters']['payer_uid']['expose']['label'] = '付款方用户手机号码或者昵称 ';
  $handler->display->display_options['filters']['payer_uid']['expose']['operator'] = 'payer_uid_op';
  $handler->display->display_options['filters']['payer_uid']['expose']['identifier'] = 'payer_uid';
  $handler->display->display_options['filters']['payer_uid']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    6 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
    7 => 0,
  );
  /* 过滤规则: 还款详情: 贷款名称 */
  $handler->display->display_options['filters']['issuing_id']['id'] = 'issuing_id';
  $handler->display->display_options['filters']['issuing_id']['table'] = 'cowpro_repayment_schedule';
  $handler->display->display_options['filters']['issuing_id']['field'] = 'issuing_id';
  $handler->display->display_options['filters']['issuing_id']['exposed'] = TRUE;
  $handler->display->display_options['filters']['issuing_id']['expose']['operator_id'] = 'issuing_id_op';
  $handler->display->display_options['filters']['issuing_id']['expose']['label'] = '贷款名称';
  $handler->display->display_options['filters']['issuing_id']['expose']['operator'] = 'issuing_id_op';
  $handler->display->display_options['filters']['issuing_id']['expose']['identifier'] = 'issuing_id';
  $handler->display->display_options['filters']['issuing_id']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    6 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
    7 => 0,
  );
  $handler->display->display_options['path'] = 'issuing-manage/due-in';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = '待还款清单';
  $handler->display->display_options['menu']['description'] = '待还款清单';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;

  /* Display: 待还款清单（借款人） */
  $handler = $view->new_display('page', '待还款清单（借款人）', 'due_in_list_debtor');
  $handler->display->display_options['defaults']['access'] = FALSE;
  $handler->display->display_options['access']['type'] = 'role';
  $handler->display->display_options['access']['role'] = array(
    5 => '5',
  );
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* 上下文过滤器: 还款详情: 付款方 */
  $handler->display->display_options['arguments']['payer_uid']['id'] = 'payer_uid';
  $handler->display->display_options['arguments']['payer_uid']['table'] = 'cowpro_repayment_schedule';
  $handler->display->display_options['arguments']['payer_uid']['field'] = 'payer_uid';
  $handler->display->display_options['arguments']['payer_uid']['default_action'] = 'default';
  $handler->display->display_options['arguments']['payer_uid']['exception']['title'] = '全部';
  $handler->display->display_options['arguments']['payer_uid']['default_argument_type'] = 'current_user';
  $handler->display->display_options['arguments']['payer_uid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['payer_uid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['payer_uid']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* 过滤规则: 还款详情: 最后还款日 */
  $handler->display->display_options['filters']['deadline']['id'] = 'deadline';
  $handler->display->display_options['filters']['deadline']['table'] = 'cowpro_repayment_schedule';
  $handler->display->display_options['filters']['deadline']['field'] = 'deadline';
  $handler->display->display_options['filters']['deadline']['operator'] = '<=';
  $handler->display->display_options['filters']['deadline']['value']['value'] = '+31 day';
  $handler->display->display_options['filters']['deadline']['value']['type'] = 'offset';
  $handler->display->display_options['filters']['deadline']['expose']['operator_id'] = 'deadline_op';
  $handler->display->display_options['filters']['deadline']['expose']['label'] = '最后还款日';
  $handler->display->display_options['filters']['deadline']['expose']['operator'] = 'deadline_op';
  $handler->display->display_options['filters']['deadline']['expose']['identifier'] = 'deadline';
  $handler->display->display_options['filters']['deadline']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    6 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
  );
  /* 过滤规则: 还款详情: 状态 */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'cowpro_repayment_schedule';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = array(
    'WAITING_FOR' => 'WAITING_FOR',
  );
  /* 过滤规则: 还款详情: 收款方用户ID */
  $handler->display->display_options['filters']['receiver_uid']['id'] = 'receiver_uid';
  $handler->display->display_options['filters']['receiver_uid']['table'] = 'cowpro_repayment_schedule';
  $handler->display->display_options['filters']['receiver_uid']['field'] = 'receiver_uid';
  $handler->display->display_options['filters']['receiver_uid']['value']['value'] = '-1';
  $handler->display->display_options['path'] = 'issuing-list/debtor-due-in';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = '待还款清单';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;

  /* Display: 待收款清单（出借人） */
  $handler = $view->new_display('page', '待收款清单（出借人）', 'due_in_list_lender');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = '待收款清单';
  $handler->display->display_options['defaults']['access'] = FALSE;
  $handler->display->display_options['access']['type'] = 'role';
  $handler->display->display_options['access']['role'] = array(
    4 => '4',
  );
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* 字段: 还款详情: 贷款名称 */
  $handler->display->display_options['fields']['issuing_id']['id'] = 'issuing_id';
  $handler->display->display_options['fields']['issuing_id']['table'] = 'cowpro_repayment_schedule';
  $handler->display->display_options['fields']['issuing_id']['field'] = 'issuing_id';
  /* 字段: 还款详情: period */
  $handler->display->display_options['fields']['period']['id'] = 'period';
  $handler->display->display_options['fields']['period']['table'] = 'cowpro_repayment_schedule';
  $handler->display->display_options['fields']['period']['field'] = 'period';
  $handler->display->display_options['fields']['period']['label'] = '期次';
  $handler->display->display_options['fields']['period']['separator'] = '';
  /* 字段: 还款详情: period_total */
  $handler->display->display_options['fields']['period_total']['id'] = 'period_total';
  $handler->display->display_options['fields']['period_total']['table'] = 'cowpro_repayment_schedule';
  $handler->display->display_options['fields']['period_total']['field'] = 'period_total';
  $handler->display->display_options['fields']['period_total']['label'] = '总期次';
  $handler->display->display_options['fields']['period_total']['separator'] = '';
  /* 字段: 还款详情: 最后还款日 */
  $handler->display->display_options['fields']['deadline']['id'] = 'deadline';
  $handler->display->display_options['fields']['deadline']['table'] = 'cowpro_repayment_schedule';
  $handler->display->display_options['fields']['deadline']['field'] = 'deadline';
  $handler->display->display_options['fields']['deadline']['date_format'] = 'custom';
  $handler->display->display_options['fields']['deadline']['custom_date_format'] = 'Y/m/d';
  $handler->display->display_options['fields']['deadline']['second_date_format'] = 'long';
  /* 字段: 还款详情: payable_amount */
  $handler->display->display_options['fields']['payable_amount']['id'] = 'payable_amount';
  $handler->display->display_options['fields']['payable_amount']['table'] = 'cowpro_repayment_schedule';
  $handler->display->display_options['fields']['payable_amount']['field'] = 'payable_amount';
  $handler->display->display_options['fields']['payable_amount']['label'] = '应还款金额';
  /* 字段: 还款详情: 状态 */
  $handler->display->display_options['fields']['status']['id'] = 'status';
  $handler->display->display_options['fields']['status']['table'] = 'cowpro_repayment_schedule';
  $handler->display->display_options['fields']['status']['field'] = 'status';
  /* 字段: 还款详情: Operations */
  $handler->display->display_options['fields']['operations']['id'] = 'operations';
  $handler->display->display_options['fields']['operations']['table'] = 'cowpro_repayment_schedule';
  $handler->display->display_options['fields']['operations']['field'] = 'operations';
  $handler->display->display_options['fields']['operations']['label'] = '操作';
  /* 字段: 还款详情: 收款方 */
  $handler->display->display_options['fields']['receiver_uid']['id'] = 'receiver_uid';
  $handler->display->display_options['fields']['receiver_uid']['table'] = 'cowpro_repayment_schedule';
  $handler->display->display_options['fields']['receiver_uid']['field'] = 'receiver_uid';
  $handler->display->display_options['fields']['receiver_uid']['exclude'] = TRUE;
  /* 字段: 还款详情: 收款方 */
  $handler->display->display_options['fields']['receiver_uid_1']['id'] = 'receiver_uid_1';
  $handler->display->display_options['fields']['receiver_uid_1']['table'] = 'cowpro_repayment_schedule';
  $handler->display->display_options['fields']['receiver_uid_1']['field'] = 'receiver_uid';
  $handler->display->display_options['fields']['receiver_uid_1']['exclude'] = TRUE;
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* 过滤规则: 还款详情: 最后还款日 */
  $handler->display->display_options['filters']['deadline']['id'] = 'deadline';
  $handler->display->display_options['filters']['deadline']['table'] = 'cowpro_repayment_schedule';
  $handler->display->display_options['filters']['deadline']['field'] = 'deadline';
  $handler->display->display_options['filters']['deadline']['operator'] = '<=';
  $handler->display->display_options['filters']['deadline']['value']['value'] = '+31 day';
  $handler->display->display_options['filters']['deadline']['value']['type'] = 'offset';
  $handler->display->display_options['filters']['deadline']['expose']['operator_id'] = 'deadline_op';
  $handler->display->display_options['filters']['deadline']['expose']['label'] = '最后还款日';
  $handler->display->display_options['filters']['deadline']['expose']['operator'] = 'deadline_op';
  $handler->display->display_options['filters']['deadline']['expose']['identifier'] = 'deadline';
  /* 过滤规则: 还款详情: 状态 */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'cowpro_repayment_schedule';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = array(
    'WAITING_FOR' => 'WAITING_FOR',
  );
  $handler->display->display_options['path'] = 'issuing-list/lender-due-in';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = '待收款清单';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;

  /* Display: Data export */
  $handler = $view->new_display('views_data_export', 'Data export', 'views_data_export_1');
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'views_data_export_xls';
  $handler->display->display_options['style_options']['provide_file'] = 1;
  $handler->display->display_options['style_options']['parent_sort'] = 0;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* 字段: 还款详情: 贷款名称 */
  $handler->display->display_options['fields']['issuing_id']['id'] = 'issuing_id';
  $handler->display->display_options['fields']['issuing_id']['table'] = 'cowpro_repayment_schedule';
  $handler->display->display_options['fields']['issuing_id']['field'] = 'issuing_id';
  /* 字段: 还款详情: 付款方 */
  $handler->display->display_options['fields']['payer_uid']['id'] = 'payer_uid';
  $handler->display->display_options['fields']['payer_uid']['table'] = 'cowpro_repayment_schedule';
  $handler->display->display_options['fields']['payer_uid']['field'] = 'payer_uid';
  /* 字段: 还款详情: period */
  $handler->display->display_options['fields']['period']['id'] = 'period';
  $handler->display->display_options['fields']['period']['table'] = 'cowpro_repayment_schedule';
  $handler->display->display_options['fields']['period']['field'] = 'period';
  $handler->display->display_options['fields']['period']['label'] = '期次';
  $handler->display->display_options['fields']['period']['separator'] = '';
  /* 字段: 还款详情: period_total */
  $handler->display->display_options['fields']['period_total']['id'] = 'period_total';
  $handler->display->display_options['fields']['period_total']['table'] = 'cowpro_repayment_schedule';
  $handler->display->display_options['fields']['period_total']['field'] = 'period_total';
  $handler->display->display_options['fields']['period_total']['label'] = '总期次';
  $handler->display->display_options['fields']['period_total']['separator'] = '';
  /* 字段: 还款详情: 最后还款日 */
  $handler->display->display_options['fields']['deadline']['id'] = 'deadline';
  $handler->display->display_options['fields']['deadline']['table'] = 'cowpro_repayment_schedule';
  $handler->display->display_options['fields']['deadline']['field'] = 'deadline';
  $handler->display->display_options['fields']['deadline']['date_format'] = 'custom';
  $handler->display->display_options['fields']['deadline']['custom_date_format'] = 'Y/m/d';
  $handler->display->display_options['fields']['deadline']['second_date_format'] = 'long';
  /* 字段: 还款详情: payable_amount */
  $handler->display->display_options['fields']['payable_amount']['id'] = 'payable_amount';
  $handler->display->display_options['fields']['payable_amount']['table'] = 'cowpro_repayment_schedule';
  $handler->display->display_options['fields']['payable_amount']['field'] = 'payable_amount';
  $handler->display->display_options['fields']['payable_amount']['label'] = '应还款金额';
  /* 字段: 还款详情: 状态 */
  $handler->display->display_options['fields']['status']['id'] = 'status';
  $handler->display->display_options['fields']['status']['table'] = 'cowpro_repayment_schedule';
  $handler->display->display_options['fields']['status']['field'] = 'status';
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* 过滤规则: 还款详情: 最后还款日 */
  $handler->display->display_options['filters']['deadline']['id'] = 'deadline';
  $handler->display->display_options['filters']['deadline']['table'] = 'cowpro_repayment_schedule';
  $handler->display->display_options['filters']['deadline']['field'] = 'deadline';
  $handler->display->display_options['filters']['deadline']['operator'] = 'between';
  $handler->display->display_options['filters']['deadline']['value']['value'] = '+31 day';
  $handler->display->display_options['filters']['deadline']['exposed'] = TRUE;
  $handler->display->display_options['filters']['deadline']['expose']['operator_id'] = 'deadline_op';
  $handler->display->display_options['filters']['deadline']['expose']['label'] = '最后还款日';
  $handler->display->display_options['filters']['deadline']['expose']['operator'] = 'deadline_op';
  $handler->display->display_options['filters']['deadline']['expose']['identifier'] = 'deadline';
  $handler->display->display_options['filters']['deadline']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    6 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
    7 => 0,
  );
  /* 过滤规则: 还款详情: 状态 */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'cowpro_repayment_schedule';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = array(
    'WAITING_FOR' => 'WAITING_FOR',
  );
  $handler->display->display_options['filters']['status']['exposed'] = TRUE;
  $handler->display->display_options['filters']['status']['expose']['operator_id'] = 'status_op';
  $handler->display->display_options['filters']['status']['expose']['label'] = '状态';
  $handler->display->display_options['filters']['status']['expose']['operator'] = 'status_op';
  $handler->display->display_options['filters']['status']['expose']['identifier'] = 'status';
  /* 过滤规则: 还款详情: 收款方用户ID */
  $handler->display->display_options['filters']['receiver_uid']['id'] = 'receiver_uid';
  $handler->display->display_options['filters']['receiver_uid']['table'] = 'cowpro_repayment_schedule';
  $handler->display->display_options['filters']['receiver_uid']['field'] = 'receiver_uid';
  $handler->display->display_options['filters']['receiver_uid']['value']['value'] = '-1';
  /* 过滤规则: 还款详情: 付款方用户ID */
  $handler->display->display_options['filters']['payer_uid']['id'] = 'payer_uid';
  $handler->display->display_options['filters']['payer_uid']['table'] = 'cowpro_repayment_schedule';
  $handler->display->display_options['filters']['payer_uid']['field'] = 'payer_uid';
  $handler->display->display_options['filters']['payer_uid']['value'] = -1;
  $handler->display->display_options['filters']['payer_uid']['exposed'] = TRUE;
  $handler->display->display_options['filters']['payer_uid']['expose']['operator_id'] = '';
  $handler->display->display_options['filters']['payer_uid']['expose']['label'] = '付款方用户ID';
  $handler->display->display_options['filters']['payer_uid']['expose']['operator'] = 'payer_uid_op';
  $handler->display->display_options['filters']['payer_uid']['expose']['identifier'] = 'payer_uid';
  $handler->display->display_options['filters']['payer_uid']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    6 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
    7 => 0,
  );
  /* 过滤规则: 还款详情: 贷款名称 */
  $handler->display->display_options['filters']['issuing_id']['id'] = 'issuing_id';
  $handler->display->display_options['filters']['issuing_id']['table'] = 'cowpro_repayment_schedule';
  $handler->display->display_options['filters']['issuing_id']['field'] = 'issuing_id';
  $handler->display->display_options['filters']['issuing_id']['exposed'] = TRUE;
  $handler->display->display_options['filters']['issuing_id']['expose']['operator_id'] = 'issuing_id_op';
  $handler->display->display_options['filters']['issuing_id']['expose']['label'] = '贷款名称';
  $handler->display->display_options['filters']['issuing_id']['expose']['operator'] = 'issuing_id_op';
  $handler->display->display_options['filters']['issuing_id']['expose']['identifier'] = 'issuing_id';
  $handler->display->display_options['filters']['issuing_id']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    6 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
    7 => 0,
  );
  $handler->display->display_options['path'] = 'issuing-manage/due-in.xls';
  $handler->display->display_options['displays'] = array(
    'due_in_list_manager' => 'due_in_list_manager',
    'default' => 0,
    'due_in_list_debtor' => 0,
    'due_in_list_lender' => 0,
  );
  $translatables['due_in_list'] = array(
    t('Master'),
    t('待还款清单'),
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
    t('贷款名称'),
    t('期次'),
    t('.'),
    t('总期次'),
    t('最后还款日'),
    t('应还款金额'),
    t('状态'),
    t('全部'),
    t('待还款清单（管理员）'),
    t('付款方'),
    t('最后还款日(格式：YYYY/MM/DD)'),
    t('付款方用户手机号码或者昵称 '),
    t('待还款清单（借款人）'),
    t('待收款清单（出借人）'),
    t('待收款清单'),
    t('操作'),
    t('收款方'),
    t('Data export'),
    t('付款方用户ID'),
  );
  $export['due_in_list'] = $view;

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
  $handler->display->display_options['cache']['type'] = 'time';
  $handler->display->display_options['cache']['results_lifespan'] = '3600';
  $handler->display->display_options['cache']['results_lifespan_custom'] = '0';
  $handler->display->display_options['cache']['output_lifespan'] = '3600';
  $handler->display->display_options['cache']['output_lifespan_custom'] = '0';
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
  /* 字段: 节点: 贷款表 */
  $handler->display->display_options['fields']['field_issuing']['id'] = 'field_issuing';
  $handler->display->display_options['fields']['field_issuing']['table'] = 'field_data_field_issuing';
  $handler->display->display_options['fields']['field_issuing']['field'] = 'field_issuing';
  $handler->display->display_options['fields']['field_issuing']['label'] = '';
  $handler->display->display_options['fields']['field_issuing']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_issuing']['click_sort_column'] = 'status';
  /* 上下文过滤器: Content: Nid */
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
  $view->name = 'repayment_plan';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'cowpro_repayment_schedule';
  $view->human_name = '近期还款计划';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = '近期本金还款计划';
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
  $handler->display->display_options['pager']['options']['items_per_page'] = '30';
  $handler->display->display_options['pager']['options']['expose']['items_per_page_label'] = '每页条目数';
  $handler->display->display_options['pager']['options']['expose']['items_per_page_options_all_label'] = '- 全部 -';
  $handler->display->display_options['pager']['options']['expose']['offset_label'] = '偏移量';
  $handler->display->display_options['pager']['options']['tags']['first'] = '« 第一页';
  $handler->display->display_options['pager']['options']['tags']['previous'] = '‹ 前一页';
  $handler->display->display_options['pager']['options']['tags']['next'] = '下一页 ›';
  $handler->display->display_options['pager']['options']['tags']['last'] = '末页 »';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'issuing_id' => 'issuing_id',
    'receiver_uid' => 'receiver_uid',
    'deadline' => 'deadline',
    'status' => 'status',
    'capital' => 'capital',
    'interest' => 'interest',
    'referee' => 'referee',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'issuing_id' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'receiver_uid' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
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
    'capital' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'interest' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'referee' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  /* 字段: 还款详情: 贷款名称 */
  $handler->display->display_options['fields']['issuing_id']['id'] = 'issuing_id';
  $handler->display->display_options['fields']['issuing_id']['table'] = 'cowpro_repayment_schedule';
  $handler->display->display_options['fields']['issuing_id']['field'] = 'issuing_id';
  /* 字段: 还款详情: 收款方 */
  $handler->display->display_options['fields']['receiver_uid']['id'] = 'receiver_uid';
  $handler->display->display_options['fields']['receiver_uid']['table'] = 'cowpro_repayment_schedule';
  $handler->display->display_options['fields']['receiver_uid']['field'] = 'receiver_uid';
  /* 字段: 还款详情: 最后还款日 */
  $handler->display->display_options['fields']['deadline']['id'] = 'deadline';
  $handler->display->display_options['fields']['deadline']['table'] = 'cowpro_repayment_schedule';
  $handler->display->display_options['fields']['deadline']['field'] = 'deadline';
  $handler->display->display_options['fields']['deadline']['date_format'] = 'custom';
  $handler->display->display_options['fields']['deadline']['custom_date_format'] = 'Y/m/d';
  $handler->display->display_options['fields']['deadline']['second_date_format'] = 'long';
  /* 字段: 还款详情: 状态 */
  $handler->display->display_options['fields']['status']['id'] = 'status';
  $handler->display->display_options['fields']['status']['table'] = 'cowpro_repayment_schedule';
  $handler->display->display_options['fields']['status']['field'] = 'status';
  /* 字段: 还款详情: capital */
  $handler->display->display_options['fields']['capital']['id'] = 'capital';
  $handler->display->display_options['fields']['capital']['table'] = 'cowpro_repayment_schedule';
  $handler->display->display_options['fields']['capital']['field'] = 'capital';
  $handler->display->display_options['fields']['capital']['label'] = '本金';
  /* 字段: 还款详情: interest */
  $handler->display->display_options['fields']['interest']['id'] = 'interest';
  $handler->display->display_options['fields']['interest']['table'] = 'cowpro_repayment_schedule';
  $handler->display->display_options['fields']['interest']['field'] = 'interest';
  $handler->display->display_options['fields']['interest']['label'] = '利息';
  /* 字段: 损坏/缺失的处理器 */
  $handler->display->display_options['fields']['referee']['id'] = 'referee';
  $handler->display->display_options['fields']['referee']['table'] = 'cowpro_repayment_schedule';
  $handler->display->display_options['fields']['referee']['field'] = 'referee';
  $handler->display->display_options['fields']['referee']['label'] = '推荐人';
  /* 排序标准: 还款详情: 最后还款日 */
  $handler->display->display_options['sorts']['deadline']['id'] = 'deadline';
  $handler->display->display_options['sorts']['deadline']['table'] = 'cowpro_repayment_schedule';
  $handler->display->display_options['sorts']['deadline']['field'] = 'deadline';
  $handler->display->display_options['sorts']['deadline']['granularity'] = 'day';
  /* 排序标准: 还款详情: 贷款名称 */
  $handler->display->display_options['sorts']['issuing_id']['id'] = 'issuing_id';
  $handler->display->display_options['sorts']['issuing_id']['table'] = 'cowpro_repayment_schedule';
  $handler->display->display_options['sorts']['issuing_id']['field'] = 'issuing_id';
  /* 过滤规则: 还款详情: 最后还款日 */
  $handler->display->display_options['filters']['deadline']['id'] = 'deadline';
  $handler->display->display_options['filters']['deadline']['table'] = 'cowpro_repayment_schedule';
  $handler->display->display_options['filters']['deadline']['field'] = 'deadline';
  $handler->display->display_options['filters']['deadline']['operator'] = 'between';
  $handler->display->display_options['filters']['deadline']['exposed'] = TRUE;
  $handler->display->display_options['filters']['deadline']['expose']['operator_id'] = 'deadline_op';
  $handler->display->display_options['filters']['deadline']['expose']['label'] = '最后还款日（格式：yyyy/mm/dd）';
  $handler->display->display_options['filters']['deadline']['expose']['operator'] = 'deadline_op';
  $handler->display->display_options['filters']['deadline']['expose']['identifier'] = 'deadline';
  $handler->display->display_options['filters']['deadline']['expose']['remember'] = TRUE;
  $handler->display->display_options['filters']['deadline']['expose']['remember_roles'] = array(
    2 => 0,
    6 => '6',
    3 => '3',
    7 => '7',
    1 => 0,
    4 => 0,
    5 => 0,
  );
  /* 过滤规则: 还款详情: 状态 */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'cowpro_repayment_schedule';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = array(
    'WAITING_FOR' => 'WAITING_FOR',
  );
  $handler->display->display_options['filters']['status']['exposed'] = TRUE;
  $handler->display->display_options['filters']['status']['expose']['operator_id'] = 'status_op';
  $handler->display->display_options['filters']['status']['expose']['label'] = '状态';
  $handler->display->display_options['filters']['status']['expose']['operator'] = 'status_op';
  $handler->display->display_options['filters']['status']['expose']['identifier'] = 'status';
  $handler->display->display_options['filters']['status']['expose']['remember'] = TRUE;
  $handler->display->display_options['filters']['status']['expose']['remember_roles'] = array(
    2 => 0,
    6 => '6',
    3 => '3',
    7 => '7',
    1 => 0,
    4 => 0,
    5 => 0,
  );
  /* 过滤规则: 还款详情: 收款方用户ID */
  $handler->display->display_options['filters']['receiver_uid']['id'] = 'receiver_uid';
  $handler->display->display_options['filters']['receiver_uid']['table'] = 'cowpro_repayment_schedule';
  $handler->display->display_options['filters']['receiver_uid']['field'] = 'receiver_uid';
  $handler->display->display_options['filters']['receiver_uid']['operator'] = '!=';
  $handler->display->display_options['filters']['receiver_uid']['value']['value'] = '-1';
  /* 过滤规则: 还款详情: capital */
  $handler->display->display_options['filters']['capital']['id'] = 'capital';
  $handler->display->display_options['filters']['capital']['table'] = 'cowpro_repayment_schedule';
  $handler->display->display_options['filters']['capital']['field'] = 'capital';
  $handler->display->display_options['filters']['capital']['operator'] = '>';
  $handler->display->display_options['filters']['capital']['value']['value'] = '0';

  /* Display: 近期本金还款计划 */
  $handler = $view->new_display('page', '近期本金还款计划', 'page');
  $handler->display->display_options['path'] = 'repayment-plan';

  /* Display: 近期本金还款计划，导出 */
  $handler = $view->new_display('views_data_export', '近期本金还款计划，导出', 'views_data_export_1');
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'views_data_export_xls';
  $handler->display->display_options['style_options']['provide_file'] = 0;
  $handler->display->display_options['style_options']['parent_sort'] = 0;
  $handler->display->display_options['path'] = 'repayment-plan.xls';
  $handler->display->display_options['displays'] = array(
    'page' => 'page',
    'default' => 0,
    'page_1' => 0,
  );

  /* Display: 近期本金还款计划二 */
  $handler = $view->new_display('page', '近期本金还款计划二', 'page_1');
  $handler->display->display_options['defaults']['group_by'] = FALSE;
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['grouping'] = array(
    0 => array(
      'field' => 'title_detail',
      'rendered' => 1,
      'rendered_strip' => 0,
    ),
  );
  $handler->display->display_options['style_options']['columns'] = array(
    'title_detail' => 'title_detail',
    'receiver_uid' => 'receiver_uid',
    'deadline' => 'deadline',
    'status' => 'status',
    'capital' => 'capital',
    'interest' => 'interest',
    'referee' => 'referee',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'title_detail' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'receiver_uid' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
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
    'capital' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'interest' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'referee' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* 字段: 还款详情: 贷款名称明细 */
  $handler->display->display_options['fields']['title_detail']['id'] = 'title_detail';
  $handler->display->display_options['fields']['title_detail']['table'] = 'cowpro_repayment_schedule';
  $handler->display->display_options['fields']['title_detail']['field'] = 'title_detail';
  $handler->display->display_options['fields']['title_detail']['label'] = '贷款名称';
  $handler->display->display_options['fields']['title_detail']['exclude'] = TRUE;
  /* 字段: 还款详情: 收款方 */
  $handler->display->display_options['fields']['receiver_uid']['id'] = 'receiver_uid';
  $handler->display->display_options['fields']['receiver_uid']['table'] = 'cowpro_repayment_schedule';
  $handler->display->display_options['fields']['receiver_uid']['field'] = 'receiver_uid';
  /* 字段: 还款详情: 最后还款日 */
  $handler->display->display_options['fields']['deadline']['id'] = 'deadline';
  $handler->display->display_options['fields']['deadline']['table'] = 'cowpro_repayment_schedule';
  $handler->display->display_options['fields']['deadline']['field'] = 'deadline';
  $handler->display->display_options['fields']['deadline']['date_format'] = 'custom';
  $handler->display->display_options['fields']['deadline']['custom_date_format'] = 'Y/m/d';
  $handler->display->display_options['fields']['deadline']['second_date_format'] = 'long';
  /* 字段: 还款详情: 状态 */
  $handler->display->display_options['fields']['status']['id'] = 'status';
  $handler->display->display_options['fields']['status']['table'] = 'cowpro_repayment_schedule';
  $handler->display->display_options['fields']['status']['field'] = 'status';
  /* 字段: 还款详情: capital */
  $handler->display->display_options['fields']['capital']['id'] = 'capital';
  $handler->display->display_options['fields']['capital']['table'] = 'cowpro_repayment_schedule';
  $handler->display->display_options['fields']['capital']['field'] = 'capital';
  $handler->display->display_options['fields']['capital']['label'] = '本金';
  /* 字段: 还款详情: interest */
  $handler->display->display_options['fields']['interest']['id'] = 'interest';
  $handler->display->display_options['fields']['interest']['table'] = 'cowpro_repayment_schedule';
  $handler->display->display_options['fields']['interest']['field'] = 'interest';
  $handler->display->display_options['fields']['interest']['label'] = '利息';
  /* 字段: 损坏/缺失的处理器 */
  $handler->display->display_options['fields']['referee']['id'] = 'referee';
  $handler->display->display_options['fields']['referee']['table'] = 'cowpro_repayment_schedule';
  $handler->display->display_options['fields']['referee']['field'] = 'referee';
  $handler->display->display_options['fields']['referee']['label'] = '推荐人';
  $handler->display->display_options['path'] = 'repayment-plan2';

  /* Display: 近期本金还款计划二，导出 */
  $handler = $view->new_display('views_data_export', '近期本金还款计划二，导出', 'views_data_export_2');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = '近期本金还款计划二';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'views_data_export_xls';
  $handler->display->display_options['style_options']['provide_file'] = 0;
  $handler->display->display_options['style_options']['parent_sort'] = 0;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* 字段: 还款详情: 贷款名称明细 */
  $handler->display->display_options['fields']['title_detail']['id'] = 'title_detail';
  $handler->display->display_options['fields']['title_detail']['table'] = 'cowpro_repayment_schedule';
  $handler->display->display_options['fields']['title_detail']['field'] = 'title_detail';
  $handler->display->display_options['fields']['title_detail']['label'] = '贷款名称';
  /* 字段: 还款详情: 收款方 */
  $handler->display->display_options['fields']['receiver_uid']['id'] = 'receiver_uid';
  $handler->display->display_options['fields']['receiver_uid']['table'] = 'cowpro_repayment_schedule';
  $handler->display->display_options['fields']['receiver_uid']['field'] = 'receiver_uid';
  /* 字段: 还款详情: 最后还款日 */
  $handler->display->display_options['fields']['deadline']['id'] = 'deadline';
  $handler->display->display_options['fields']['deadline']['table'] = 'cowpro_repayment_schedule';
  $handler->display->display_options['fields']['deadline']['field'] = 'deadline';
  $handler->display->display_options['fields']['deadline']['date_format'] = 'custom';
  $handler->display->display_options['fields']['deadline']['custom_date_format'] = 'Y/m/d';
  $handler->display->display_options['fields']['deadline']['second_date_format'] = 'long';
  /* 字段: 还款详情: 状态 */
  $handler->display->display_options['fields']['status']['id'] = 'status';
  $handler->display->display_options['fields']['status']['table'] = 'cowpro_repayment_schedule';
  $handler->display->display_options['fields']['status']['field'] = 'status';
  /* 字段: 还款详情: capital */
  $handler->display->display_options['fields']['capital']['id'] = 'capital';
  $handler->display->display_options['fields']['capital']['table'] = 'cowpro_repayment_schedule';
  $handler->display->display_options['fields']['capital']['field'] = 'capital';
  $handler->display->display_options['fields']['capital']['label'] = '本金';
  /* 字段: 还款详情: interest */
  $handler->display->display_options['fields']['interest']['id'] = 'interest';
  $handler->display->display_options['fields']['interest']['table'] = 'cowpro_repayment_schedule';
  $handler->display->display_options['fields']['interest']['field'] = 'interest';
  $handler->display->display_options['fields']['interest']['label'] = '利息';
  /* 字段: 损坏/缺失的处理器 */
  $handler->display->display_options['fields']['referee']['id'] = 'referee';
  $handler->display->display_options['fields']['referee']['table'] = 'cowpro_repayment_schedule';
  $handler->display->display_options['fields']['referee']['field'] = 'referee';
  $handler->display->display_options['fields']['referee']['label'] = '推荐人';
  $handler->display->display_options['path'] = 'repayment-plan2.xls';
  $handler->display->display_options['displays'] = array(
    'page_1' => 'page_1',
    'default' => 0,
    'page' => 0,
  );
  $handler->display->display_options['sitename_title'] = 0;
  $translatables['repayment_plan'] = array(
    t('Master'),
    t('近期本金还款计划'),
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
    t('贷款名称'),
    t('收款方'),
    t('最后还款日'),
    t('状态'),
    t('本金'),
    t('利息'),
    t('推荐人'),
    t('最后还款日（格式：yyyy/mm/dd）'),
    t('近期本金还款计划，导出'),
    t('近期本金还款计划二'),
    t('近期本金还款计划二，导出'),
  );
  $export['repayment_plan'] = $view;

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
  $handler->display->display_options['cache']['type'] = 'time';
  $handler->display->display_options['cache']['results_lifespan'] = '3600';
  $handler->display->display_options['cache']['results_lifespan_custom'] = '0';
  $handler->display->display_options['cache']['output_lifespan'] = '3600';
  $handler->display->display_options['cache']['output_lifespan_custom'] = '0';
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
  /* 字段: User: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'users';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['relationship'] = 'payer_uid';
  $handler->display->display_options['fields']['name']['label'] = '付款用户';
  /* 字段: User: Name */
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
  /* 字段: 还款详情: paid_amount */
  $handler->display->display_options['fields']['paid_amount_1']['id'] = 'paid_amount_1';
  $handler->display->display_options['fields']['paid_amount_1']['table'] = 'cowpro_repayment_schedule';
  $handler->display->display_options['fields']['paid_amount_1']['field'] = 'paid_amount';
  $handler->display->display_options['fields']['paid_amount_1']['label'] = '已付款';
  /* 字段: 还款详情: receivable_amount */
  $handler->display->display_options['fields']['receivable_amount']['id'] = 'receivable_amount';
  $handler->display->display_options['fields']['receivable_amount']['table'] = 'cowpro_repayment_schedule';
  $handler->display->display_options['fields']['receivable_amount']['field'] = 'receivable_amount';
  $handler->display->display_options['fields']['receivable_amount']['label'] = '应收款';
  /* 字段: 还款详情: received_amount */
  $handler->display->display_options['fields']['received_amount']['id'] = 'received_amount';
  $handler->display->display_options['fields']['received_amount']['table'] = 'cowpro_repayment_schedule';
  $handler->display->display_options['fields']['received_amount']['field'] = 'received_amount';
  $handler->display->display_options['fields']['received_amount']['label'] = '已收款';
  /* 字段: 还款详情: 最后还款日 */
  $handler->display->display_options['fields']['deadline']['id'] = 'deadline';
  $handler->display->display_options['fields']['deadline']['table'] = 'cowpro_repayment_schedule';
  $handler->display->display_options['fields']['deadline']['field'] = 'deadline';
  $handler->display->display_options['fields']['deadline']['date_format'] = 'custom';
  $handler->display->display_options['fields']['deadline']['custom_date_format'] = 'Y/m/d';
  $handler->display->display_options['fields']['deadline']['second_date_format'] = 'short';
  /* 字段: 还款详情: 状态 */
  $handler->display->display_options['fields']['status']['id'] = 'status';
  $handler->display->display_options['fields']['status']['table'] = 'cowpro_repayment_schedule';
  $handler->display->display_options['fields']['status']['field'] = 'status';
  /* 上下文过滤器: Content: Nid */
  $handler->display->display_options['arguments']['nid']['id'] = 'nid';
  $handler->display->display_options['arguments']['nid']['table'] = 'node';
  $handler->display->display_options['arguments']['nid']['field'] = 'nid';
  $handler->display->display_options['arguments']['nid']['exception']['title'] = '全部';
  $handler->display->display_options['arguments']['nid']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['nid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['nid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['nid']['summary_options']['items_per_page'] = '25';
  /* 上下文过滤器: 还款详情: 收款方 */
  $handler->display->display_options['arguments']['receiver_uid']['id'] = 'receiver_uid';
  $handler->display->display_options['arguments']['receiver_uid']['table'] = 'cowpro_repayment_schedule';
  $handler->display->display_options['arguments']['receiver_uid']['field'] = 'receiver_uid';
  $handler->display->display_options['arguments']['receiver_uid']['default_action'] = 'empty';
  $handler->display->display_options['arguments']['receiver_uid']['exception']['title'] = '全部';
  $handler->display->display_options['arguments']['receiver_uid']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['receiver_uid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['receiver_uid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['receiver_uid']['summary_options']['items_per_page'] = '25';
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
  $handler->display->display_options['cache']['type'] = 'time';
  $handler->display->display_options['cache']['results_lifespan'] = '3600';
  $handler->display->display_options['cache']['results_lifespan_custom'] = '0';
  $handler->display->display_options['cache']['output_lifespan'] = '3600';
  $handler->display->display_options['cache']['output_lifespan_custom'] = '0';
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
  $handler->display->display_options['style_options']['columns'] = array(
    'period' => 'period',
    'name' => 'name',
    'payable_amount' => 'payable_amount',
    'paid_amount_1' => 'paid_amount_1',
    'deadline' => 'deadline',
    'status' => 'status',
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
  /* 字段: 还款详情: payable_amount */
  $handler->display->display_options['fields']['payable_amount']['id'] = 'payable_amount';
  $handler->display->display_options['fields']['payable_amount']['table'] = 'cowpro_repayment_schedule';
  $handler->display->display_options['fields']['payable_amount']['field'] = 'payable_amount';
  $handler->display->display_options['fields']['payable_amount']['label'] = '应付款';
  /* 字段: 还款详情: paid_amount */
  $handler->display->display_options['fields']['paid_amount_1']['id'] = 'paid_amount_1';
  $handler->display->display_options['fields']['paid_amount_1']['table'] = 'cowpro_repayment_schedule';
  $handler->display->display_options['fields']['paid_amount_1']['field'] = 'paid_amount';
  $handler->display->display_options['fields']['paid_amount_1']['label'] = '已付款';
  /* 字段: 还款详情: 最后还款日 */
  $handler->display->display_options['fields']['deadline']['id'] = 'deadline';
  $handler->display->display_options['fields']['deadline']['table'] = 'cowpro_repayment_schedule';
  $handler->display->display_options['fields']['deadline']['field'] = 'deadline';
  $handler->display->display_options['fields']['deadline']['date_format'] = 'custom';
  $handler->display->display_options['fields']['deadline']['custom_date_format'] = 'Y/m/d';
  $handler->display->display_options['fields']['deadline']['second_date_format'] = 'short';
  /* 字段: 还款详情: 状态 */
  $handler->display->display_options['fields']['status']['id'] = 'status';
  $handler->display->display_options['fields']['status']['table'] = 'cowpro_repayment_schedule';
  $handler->display->display_options['fields']['status']['field'] = 'status';
  /* 上下文过滤器: 还款详情: 贷款名称 */
  $handler->display->display_options['arguments']['issuing_id']['id'] = 'issuing_id';
  $handler->display->display_options['arguments']['issuing_id']['table'] = 'cowpro_repayment_schedule';
  $handler->display->display_options['arguments']['issuing_id']['field'] = 'issuing_id';
  $handler->display->display_options['arguments']['issuing_id']['exception']['title'] = '全部';
  $handler->display->display_options['arguments']['issuing_id']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['issuing_id']['summary']['format'] = 'default_summary';
  /* 过滤规则: 还款详情: 收款方用户ID */
  $handler->display->display_options['filters']['receiver_uid']['id'] = 'receiver_uid';
  $handler->display->display_options['filters']['receiver_uid']['table'] = 'cowpro_repayment_schedule';
  $handler->display->display_options['filters']['receiver_uid']['field'] = 'receiver_uid';
  $handler->display->display_options['filters']['receiver_uid']['value']['value'] = '-1';
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
    t('已付款'),
    t('最后还款日'),
    t('状态'),
    t('全部'),
  );
  $export['repayment_schedule_debtor'] = $view;

  $view = new view();
  $view->name = 'repayment_schedule_debtor_bulk_operation';
  $view->description = '';
  $view->tag = 'cowpro';
  $view->base_table = 'cowpro_repayment_schedule';
  $view->human_name = '还款详情(借款人还款操作)';
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
  $handler->display->display_options['style_plugin'] = 'table_megarows';
  $handler->display->display_options['style_options']['columns'] = array(
    'period' => 'period',
    'name' => 'name',
    'payable_amount' => 'payable_amount',
    'paid_amount_1' => 'paid_amount_1',
    'deadline' => 'deadline',
    'status' => 'status',
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
  );
  $handler->display->display_options['style_options']['scroll_padding'] = '120';
  $handler->display->display_options['row_plugin'] = 'fields';
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
  /* 字段: User: Name */
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
  /* 字段: 还款详情: paid_amount */
  $handler->display->display_options['fields']['paid_amount_1']['id'] = 'paid_amount_1';
  $handler->display->display_options['fields']['paid_amount_1']['table'] = 'cowpro_repayment_schedule';
  $handler->display->display_options['fields']['paid_amount_1']['field'] = 'paid_amount';
  $handler->display->display_options['fields']['paid_amount_1']['label'] = '已付款';
  /* 字段: 还款详情: 最后还款日 */
  $handler->display->display_options['fields']['deadline']['id'] = 'deadline';
  $handler->display->display_options['fields']['deadline']['table'] = 'cowpro_repayment_schedule';
  $handler->display->display_options['fields']['deadline']['field'] = 'deadline';
  $handler->display->display_options['fields']['deadline']['date_format'] = 'custom';
  $handler->display->display_options['fields']['deadline']['custom_date_format'] = 'Y/m/d';
  $handler->display->display_options['fields']['deadline']['second_date_format'] = 'short';
  /* 字段: 还款详情: 状态 */
  $handler->display->display_options['fields']['status']['id'] = 'status';
  $handler->display->display_options['fields']['status']['table'] = 'cowpro_repayment_schedule';
  $handler->display->display_options['fields']['status']['field'] = 'status';
  /* 字段: Bulk operations: 还款详情 */
  $handler->display->display_options['fields']['views_bulk_operations']['id'] = 'views_bulk_operations';
  $handler->display->display_options['fields']['views_bulk_operations']['table'] = 'views_entity_cowpro_repayment_schedule';
  $handler->display->display_options['fields']['views_bulk_operations']['field'] = 'views_bulk_operations';
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['display_type'] = '1';
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['enable_select_all_pages'] = 1;
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['row_clickable'] = 1;
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['force_single'] = 0;
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['entity_load_capacity'] = '10';
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_operations'] = array(
    'action::cowpro_issuing_repayment_action' => array(
      'selected' => 1,
      'skip_confirmation' => 0,
      'skip_permission_check' => 1,
      'override_label' => 0,
      'label' => '',
    ),
  );
  /* 上下文过滤器: 还款详情: 贷款名称 */
  $handler->display->display_options['arguments']['issuing_id']['id'] = 'issuing_id';
  $handler->display->display_options['arguments']['issuing_id']['table'] = 'cowpro_repayment_schedule';
  $handler->display->display_options['arguments']['issuing_id']['field'] = 'issuing_id';
  $handler->display->display_options['arguments']['issuing_id']['exception']['title'] = '全部';
  $handler->display->display_options['arguments']['issuing_id']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['issuing_id']['summary']['format'] = 'default_summary';
  /* 过滤规则: 还款详情: 收款方用户ID */
  $handler->display->display_options['filters']['receiver_uid']['id'] = 'receiver_uid';
  $handler->display->display_options['filters']['receiver_uid']['table'] = 'cowpro_repayment_schedule';
  $handler->display->display_options['filters']['receiver_uid']['field'] = 'receiver_uid';
  $handler->display->display_options['filters']['receiver_uid']['value']['value'] = '-1';
  $translatables['repayment_schedule_debtor_bulk_operation'] = array(
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
    t('已付款'),
    t('最后还款日'),
    t('状态'),
    t('还款详情'),
    t('- 选择一个操作 -'),
    t('全部'),
  );
  $export['repayment_schedule_debtor_bulk_operation'] = $view;

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
  $handler->display->display_options['cache']['type'] = 'time';
  $handler->display->display_options['cache']['results_lifespan'] = '3600';
  $handler->display->display_options['cache']['results_lifespan_custom'] = '0';
  $handler->display->display_options['cache']['output_lifespan'] = '3600';
  $handler->display->display_options['cache']['output_lifespan_custom'] = '0';
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
  /* 字段: User: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'users';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['relationship'] = 'payer_uid';
  $handler->display->display_options['fields']['name']['label'] = '付款用户';
  /* 字段: User: Name */
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
  /* 字段: 还款详情: received_amount */
  $handler->display->display_options['fields']['received_amount']['id'] = 'received_amount';
  $handler->display->display_options['fields']['received_amount']['table'] = 'cowpro_repayment_schedule';
  $handler->display->display_options['fields']['received_amount']['field'] = 'received_amount';
  $handler->display->display_options['fields']['received_amount']['label'] = '已收款';
  /* 字段: 还款详情: 最后还款日 */
  $handler->display->display_options['fields']['deadline']['id'] = 'deadline';
  $handler->display->display_options['fields']['deadline']['table'] = 'cowpro_repayment_schedule';
  $handler->display->display_options['fields']['deadline']['field'] = 'deadline';
  $handler->display->display_options['fields']['deadline']['date_format'] = 'custom';
  $handler->display->display_options['fields']['deadline']['custom_date_format'] = 'Y/m/d';
  $handler->display->display_options['fields']['deadline']['second_date_format'] = 'short';
  /* 字段: 还款详情: 状态 */
  $handler->display->display_options['fields']['status']['id'] = 'status';
  $handler->display->display_options['fields']['status']['table'] = 'cowpro_repayment_schedule';
  $handler->display->display_options['fields']['status']['field'] = 'status';
  /* 上下文过滤器: Content: Nid */
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
    t('已收款'),
    t('最后还款日'),
    t('状态'),
    t('全部'),
  );
  $export['repayment_schedule_lender'] = $view;

  $view = new view();
  $view->name = 'slider';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Slider';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['use_more_text'] = '更多';
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'time';
  $handler->display->display_options['cache']['results_lifespan'] = '21600';
  $handler->display->display_options['cache']['results_lifespan_custom'] = '0';
  $handler->display->display_options['cache']['output_lifespan'] = '21600';
  $handler->display->display_options['cache']['output_lifespan_custom'] = '0';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['submit_button'] = '应用';
  $handler->display->display_options['exposed_form']['options']['reset_button_label'] = '重置';
  $handler->display->display_options['exposed_form']['options']['exposed_sorts_label'] = '排序依据';
  $handler->display->display_options['exposed_form']['options']['sort_asc_label'] = '升序';
  $handler->display->display_options['exposed_form']['options']['sort_desc_label'] = '降序';
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '3';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'flexslider';
  $handler->display->display_options['style_options']['captionfield'] = 'nothing';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* 字段: 损坏/缺失的处理器 */
  $handler->display->display_options['fields']['field_slide_image']['id'] = 'field_slide_image';
  $handler->display->display_options['fields']['field_slide_image']['table'] = 'field_data_field_slide_image';
  $handler->display->display_options['fields']['field_slide_image']['field'] = 'field_slide_image';
  $handler->display->display_options['fields']['field_slide_image']['label'] = '';
  $handler->display->display_options['fields']['field_slide_image']['element_label_colon'] = FALSE;
  /* 字段: 节点: Body */
  $handler->display->display_options['fields']['body']['id'] = 'body';
  $handler->display->display_options['fields']['body']['table'] = 'field_data_body';
  $handler->display->display_options['fields']['body']['field'] = 'body';
  $handler->display->display_options['fields']['body']['label'] = '';
  $handler->display->display_options['fields']['body']['exclude'] = TRUE;
  $handler->display->display_options['fields']['body']['alter']['max_length'] = '325';
  $handler->display->display_options['fields']['body']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['body']['alter']['strip_tags'] = TRUE;
  $handler->display->display_options['fields']['body']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['body']['type'] = 'text_summary_or_trimmed';
  $handler->display->display_options['fields']['body']['settings'] = array(
    'trim_length' => '325',
  );
  /* 字段: Content: Link */
  $handler->display->display_options['fields']['view_node']['id'] = 'view_node';
  $handler->display->display_options['fields']['view_node']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['view_node']['field'] = 'view_node';
  $handler->display->display_options['fields']['view_node']['label'] = '';
  $handler->display->display_options['fields']['view_node']['exclude'] = TRUE;
  $handler->display->display_options['fields']['view_node']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['view_node']['text'] = 'Read more';
  /* 字段: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['exclude'] = TRUE;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  /* 字段: Global: Custom text */
  $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['table'] = 'views';
  $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['label'] = '';
  $handler->display->display_options['fields']['nothing']['exclude'] = TRUE;
  $handler->display->display_options['fields']['nothing']['alter']['text'] = '<div class="container-12">
<div class="grid-5">
<h2>[title]</h2>
[body]
<div class="link">[view_node]</div>
</div>
</div>';
  $handler->display->display_options['fields']['nothing']['element_type'] = '0';
  $handler->display->display_options['fields']['nothing']['element_label_colon'] = FALSE;
  /* 排序标准: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* 过滤规则: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* 过滤规则: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'slide' => 'slide',
  );

  /* Display: Block */
  $handler = $view->new_display('block', 'Block', 'block');

  /* Display: Attachment */
  $handler = $view->new_display('attachment', 'Attachment', 'attachment_1');
  $handler->display->display_options['defaults']['css_class'] = FALSE;
  $handler->display->display_options['css_class'] = 'flexslider-controls';
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '3';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'list';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* 字段: Content: Nid */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['label'] = '';
  $handler->display->display_options['fields']['nid']['exclude'] = TRUE;
  $handler->display->display_options['fields']['nid']['element_label_colon'] = FALSE;
  /* 字段: 损坏/缺失的处理器 */
  $handler->display->display_options['fields']['field_slide_icon']['id'] = 'field_slide_icon';
  $handler->display->display_options['fields']['field_slide_icon']['table'] = 'field_data_field_slide_icon';
  $handler->display->display_options['fields']['field_slide_icon']['field'] = 'field_slide_icon';
  $handler->display->display_options['fields']['field_slide_icon']['label'] = '';
  $handler->display->display_options['fields']['field_slide_icon']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_slide_icon']['alter']['text'] = '<a href="?q=node/[nid]">[field_slide_icon]</a>';
  $handler->display->display_options['fields']['field_slide_icon']['element_label_colon'] = FALSE;
  $handler->display->display_options['displays'] = array(
    'block' => 'block',
    'default' => 0,
  );
  $handler->display->display_options['attachment_position'] = 'after';
  $translatables['slider'] = array(
    t('Master'),
    t('更多'),
    t('应用'),
    t('重置'),
    t('排序依据'),
    t('升序'),
    t('降序'),
    t('Read more'),
    t('<div class="container-12">
<div class="grid-5">
<h2>[title]</h2>
[body]
<div class="link">[view_node]</div>
</div>
</div>'),
    t('Block'),
    t('Attachment'),
    t('<a href="?q=node/[nid]">[field_slide_icon]</a>'),
  );
  $export['slider'] = $view;

  $view = new view();
  $view->name = 'sopuo_solder';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'sopuo solder';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'sopuo solder';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['use_more_text'] = '更多';
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'time';
  $handler->display->display_options['cache']['results_lifespan'] = '21600';
  $handler->display->display_options['cache']['results_lifespan_custom'] = '0';
  $handler->display->display_options['cache']['output_lifespan'] = '21600';
  $handler->display->display_options['cache']['output_lifespan_custom'] = '0';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['submit_button'] = '应用';
  $handler->display->display_options['exposed_form']['options']['reset_button_label'] = '重置';
  $handler->display->display_options['exposed_form']['options']['exposed_sorts_label'] = '排序依据';
  $handler->display->display_options['exposed_form']['options']['sort_asc_label'] = '升序';
  $handler->display->display_options['exposed_form']['options']['sort_desc_label'] = '降序';
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '6';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'views_bootstrap_carousel_plugin_style';
  $handler->display->display_options['style_options']['interval'] = '5000';
  $handler->display->display_options['style_options']['navigation'] = 1;
  $handler->display->display_options['style_options']['indicators'] = 1;
  $handler->display->display_options['style_options']['pause'] = 1;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['row_options']['default_field_elements'] = FALSE;
  /* 字段: 节点: Silder Links */
  $handler->display->display_options['fields']['field_silder_links']['id'] = 'field_silder_links';
  $handler->display->display_options['fields']['field_silder_links']['table'] = 'field_data_field_silder_links';
  $handler->display->display_options['fields']['field_silder_links']['field'] = 'field_silder_links';
  $handler->display->display_options['fields']['field_silder_links']['label'] = '';
  $handler->display->display_options['fields']['field_silder_links']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_silder_links']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_silder_links']['type'] = 'text_plain';
  /* 字段: 节点: Silder images */
  $handler->display->display_options['fields']['field_silder_images']['id'] = 'field_silder_images';
  $handler->display->display_options['fields']['field_silder_images']['table'] = 'field_data_field_silder_images';
  $handler->display->display_options['fields']['field_silder_images']['field'] = 'field_silder_images';
  $handler->display->display_options['fields']['field_silder_images']['label'] = '';
  $handler->display->display_options['fields']['field_silder_images']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_silder_images']['alter']['text'] = '<a href="[field_silder_links]" target="_blank" >[field_silder_images] </a>';
  $handler->display->display_options['fields']['field_silder_images']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_silder_images']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_silder_images']['settings'] = array(
    'image_style' => '',
    'image_link' => '',
  );
  /* 排序标准: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  /* 过滤规则: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* 过滤规则: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'sopuo_slider' => 'sopuo_slider',
  );

  /* Display: Block */
  $handler = $view->new_display('block', 'Block', 'block');
  $translatables['sopuo_solder'] = array(
    t('Master'),
    t('sopuo solder'),
    t('更多'),
    t('应用'),
    t('重置'),
    t('排序依据'),
    t('升序'),
    t('降序'),
    t('<a href="[field_silder_links]" target="_blank" >[field_silder_images] </a>'),
    t('Block'),
  );
  $export['sopuo_solder'] = $view;

  $view = new view();
  $view->name = 'touzi2017';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = ' 投资项目';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = ' 投资项目';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['use_more_text'] = '更多';
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'time';
  $handler->display->display_options['cache']['results_lifespan'] = '3600';
  $handler->display->display_options['cache']['results_lifespan_custom'] = '0';
  $handler->display->display_options['cache']['output_lifespan'] = '3600';
  $handler->display->display_options['cache']['output_lifespan_custom'] = '0';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['submit_button'] = '应用';
  $handler->display->display_options['exposed_form']['options']['reset_button_label'] = '重置';
  $handler->display->display_options['exposed_form']['options']['exposed_sorts_label'] = '排序依据';
  $handler->display->display_options['exposed_form']['options']['sort_asc_label'] = '升序';
  $handler->display->display_options['exposed_form']['options']['sort_desc_label'] = '降序';
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* 字段: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* 排序标准: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* 过滤规则: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* 过滤规则: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'cowpro_issuing' => 'cowpro_issuing',
  );

  /* Display: Block */
  $handler = $view->new_display('block', 'Block', 'block');
  $translatables['touzi2017'] = array(
    t('Master'),
    t(' 投资项目'),
    t('更多'),
    t('应用'),
    t('重置'),
    t('排序依据'),
    t('升序'),
    t('降序'),
    t('Block'),
  );
  $export['touzi2017'] = $view;

  $view = new view();
  $view->name = 'user_sopuo';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'users';
  $view->human_name = '用户查询';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = '用户查询';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['use_more_text'] = '更多';
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'access user profiles';
  $handler->display->display_options['cache']['type'] = 'time';
  $handler->display->display_options['cache']['results_lifespan'] = '3600';
  $handler->display->display_options['cache']['results_lifespan_custom'] = '0';
  $handler->display->display_options['cache']['output_lifespan'] = '3600';
  $handler->display->display_options['cache']['output_lifespan_custom'] = '0';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'better_exposed_filters';
  $handler->display->display_options['exposed_form']['options']['submit_button'] = '应用';
  $handler->display->display_options['exposed_form']['options']['reset_button_label'] = '重置';
  $handler->display->display_options['exposed_form']['options']['exposed_sorts_label'] = '排序依据';
  $handler->display->display_options['exposed_form']['options']['sort_asc_label'] = '升序';
  $handler->display->display_options['exposed_form']['options']['sort_desc_label'] = '降序';
  $handler->display->display_options['exposed_form']['options']['bef'] = array(
    'general' => array(
      'input_required' => 0,
      'text_input_required' => array(
        'text_input_required' => array(
          'value' => 'Select any filter and click on Apply to see results',
          'format' => 'full_html',
        ),
      ),
      'allow_secondary' => 0,
      'secondary_label' => '高级选项',
      'secondary_collapse_override' => '0',
    ),
  );
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['pager']['options']['expose']['items_per_page_label'] = '每页条目数';
  $handler->display->display_options['pager']['options']['expose']['items_per_page_options_all_label'] = '- 全部 -';
  $handler->display->display_options['pager']['options']['expose']['offset_label'] = '偏移量';
  $handler->display->display_options['pager']['options']['tags']['first'] = '« 第一页';
  $handler->display->display_options['pager']['options']['tags']['previous'] = '‹ 前一页';
  $handler->display->display_options['pager']['options']['tags']['next'] = '下一页 ›';
  $handler->display->display_options['pager']['options']['tags']['last'] = '末页 »';
  $handler->display->display_options['style_plugin'] = 'table_megarows';
  $handler->display->display_options['style_options']['columns'] = array(
    'name' => 'name',
    'mmm' => 'mmm',
    'created' => 'created',
    'real_name' => 'real_name',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'name' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'mmm' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'created' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'real_name' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  $handler->display->display_options['style_options']['scroll_padding'] = '120';
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['row_options']['default_field_elements'] = FALSE;
  /* 字段: User: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'users';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['label'] = '';
  $handler->display->display_options['fields']['name']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['name']['alter']['ellipsis'] = FALSE;
  /* 字段: User: Created date */
  $handler->display->display_options['fields']['created']['id'] = 'created';
  $handler->display->display_options['fields']['created']['table'] = 'users';
  $handler->display->display_options['fields']['created']['field'] = 'created';
  $handler->display->display_options['fields']['created']['label'] = '创建日期';
  $handler->display->display_options['fields']['created']['date_format'] = 'custom';
  $handler->display->display_options['fields']['created']['custom_date_format'] = 'Y/m/d';
  $handler->display->display_options['fields']['created']['second_date_format'] = 'long';
  /* 字段: User: 乾多多注册 */
  $handler->display->display_options['fields']['mmm']['id'] = 'mmm';
  $handler->display->display_options['fields']['mmm']['table'] = 'users';
  $handler->display->display_options['fields']['mmm']['field'] = 'mmm';
  /* 字段: User: 实名认证 */
  $handler->display->display_options['fields']['real_name']['id'] = 'real_name';
  $handler->display->display_options['fields']['real_name']['table'] = 'users';
  $handler->display->display_options['fields']['real_name']['field'] = 'real_name';
  /* 字段: User: 手机验证 */
  $handler->display->display_options['fields']['mobile_certification']['id'] = 'mobile_certification';
  $handler->display->display_options['fields']['mobile_certification']['table'] = 'users';
  $handler->display->display_options['fields']['mobile_certification']['field'] = 'mobile_certification';
  /* 字段: User: 投标密码 */
  $handler->display->display_options['fields']['payment_password']['id'] = 'payment_password';
  $handler->display->display_options['fields']['payment_password']['table'] = 'users';
  $handler->display->display_options['fields']['payment_password']['field'] = 'payment_password';
  /* 字段: User: 推荐人 */
  $handler->display->display_options['fields']['referee']['id'] = 'referee';
  $handler->display->display_options['fields']['referee']['table'] = 'users';
  $handler->display->display_options['fields']['referee']['field'] = 'referee';
  /* 排序标准: User: Created date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'users';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* 过滤规则: User: Created date */
  $handler->display->display_options['filters']['created_2']['id'] = 'created_2';
  $handler->display->display_options['filters']['created_2']['table'] = 'users';
  $handler->display->display_options['filters']['created_2']['field'] = 'created';
  $handler->display->display_options['filters']['created_2']['exposed'] = TRUE;
  $handler->display->display_options['filters']['created_2']['expose']['operator_id'] = 'created_2_op';
  $handler->display->display_options['filters']['created_2']['expose']['label'] = '创建日期(格式：YYYY/MM/DD) ';
  $handler->display->display_options['filters']['created_2']['expose']['use_operator'] = TRUE;
  $handler->display->display_options['filters']['created_2']['expose']['operator'] = 'created_2_op';
  $handler->display->display_options['filters']['created_2']['expose']['identifier'] = 'created_2';
  $handler->display->display_options['filters']['created_2']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    6 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
    7 => 0,
  );
  /* 过滤规则: User: 手机验证 */
  $handler->display->display_options['filters']['mobile_certification_2']['id'] = 'mobile_certification_2';
  $handler->display->display_options['filters']['mobile_certification_2']['table'] = 'users';
  $handler->display->display_options['filters']['mobile_certification_2']['field'] = 'mobile_certification';
  $handler->display->display_options['filters']['mobile_certification_2']['value'] = -1;
  $handler->display->display_options['filters']['mobile_certification_2']['exposed'] = TRUE;
  $handler->display->display_options['filters']['mobile_certification_2']['expose']['operator_id'] = '';
  $handler->display->display_options['filters']['mobile_certification_2']['expose']['label'] = '用户的手机号码或者昵称';
  $handler->display->display_options['filters']['mobile_certification_2']['expose']['operator'] = 'mobile_certification_2_op';
  $handler->display->display_options['filters']['mobile_certification_2']['expose']['identifier'] = 'mobile_certification_2';
  $handler->display->display_options['filters']['mobile_certification_2']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    6 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
  );
  /* 过滤规则: User: 推荐人 */
  $handler->display->display_options['filters']['referee_2']['id'] = 'referee_2';
  $handler->display->display_options['filters']['referee_2']['table'] = 'users';
  $handler->display->display_options['filters']['referee_2']['field'] = 'referee';
  $handler->display->display_options['filters']['referee_2']['value'] = -1;
  $handler->display->display_options['filters']['referee_2']['exposed'] = TRUE;
  $handler->display->display_options['filters']['referee_2']['expose']['operator_id'] = '';
  $handler->display->display_options['filters']['referee_2']['expose']['label'] = '推荐人的手机号码或者昵称 ';
  $handler->display->display_options['filters']['referee_2']['expose']['operator'] = 'referee_2_op';
  $handler->display->display_options['filters']['referee_2']['expose']['identifier'] = 'referee_2';
  $handler->display->display_options['filters']['referee_2']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    6 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
  );

  /* Display: 用户查询 */
  $handler = $view->new_display('page', '用户查询', 'page');
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '30';
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
  $handler->display->display_options['exposed_block'] = TRUE;
  $handler->display->display_options['path'] = 'user-search';

  /* Display: 用户查询，导出 */
  $handler = $view->new_display('views_data_export', '用户查询，导出', 'views_data_export_1');
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'views_data_export_xls';
  $handler->display->display_options['style_options']['provide_file'] = 0;
  $handler->display->display_options['style_options']['parent_sort'] = 0;
  $handler->display->display_options['path'] = 'user-search.xls';
  $handler->display->display_options['displays'] = array(
    'page' => 'page',
    'default' => 0,
  );
  $handler->display->display_options['use_batch'] = 'batch';
  $handler->display->display_options['segment_size'] = '200';
  $translatables['user_sopuo'] = array(
    t('Master'),
    t('用户查询'),
    t('更多'),
    t('应用'),
    t('重置'),
    t('排序依据'),
    t('升序'),
    t('降序'),
    t('Select any filter and click on Apply to see results'),
    t('高级选项'),
    t('每页条目数'),
    t('- 全部 -'),
    t('偏移量'),
    t('« 第一页'),
    t('‹ 前一页'),
    t('下一页 ›'),
    t('末页 »'),
    t('创建日期'),
    t('乾多多注册'),
    t('实名认证'),
    t('手机验证'),
    t('投标密码'),
    t('推荐人'),
    t('创建日期(格式：YYYY/MM/DD) '),
    t('用户的手机号码或者昵称'),
    t('推荐人的手机号码或者昵称 '),
    t('用户查询，导出'),
  );
  $export['user_sopuo'] = $view;

  $view = new view();
  $view->name = 'userpoints_search';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'userpoints_txn';
  $view->human_name = '积分与奖金';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = '积分与奖金';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['use_more_text'] = '更多';
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'access user profiles';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['submit_button'] = '应用';
  $handler->display->display_options['exposed_form']['options']['reset_button_label'] = '重置';
  $handler->display->display_options['exposed_form']['options']['exposed_sorts_label'] = '排序依据';
  $handler->display->display_options['exposed_form']['options']['sort_asc_label'] = '升序';
  $handler->display->display_options['exposed_form']['options']['sort_desc_label'] = '降序';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '30';
  $handler->display->display_options['pager']['options']['expose']['items_per_page_label'] = '每页条目数';
  $handler->display->display_options['pager']['options']['expose']['items_per_page_options_all_label'] = '- 全部 -';
  $handler->display->display_options['pager']['options']['expose']['offset_label'] = '偏移量';
  $handler->display->display_options['pager']['options']['tags']['first'] = '« 第一页';
  $handler->display->display_options['pager']['options']['tags']['previous'] = '‹ 前一页';
  $handler->display->display_options['pager']['options']['tags']['next'] = '下一页 ›';
  $handler->display->display_options['pager']['options']['tags']['last'] = '末页 »';
  $handler->display->display_options['style_plugin'] = 'table';
  /* 关联: Userpoints Transactions: User */
  $handler->display->display_options['relationships']['uid']['id'] = 'uid';
  $handler->display->display_options['relationships']['uid']['table'] = 'userpoints_txn';
  $handler->display->display_options['relationships']['uid']['field'] = 'uid';
  $handler->display->display_options['relationships']['uid']['label'] = '用户';
  /* 字段: User: 用户昵称与实名 */
  $handler->display->display_options['fields']['name_detail']['id'] = 'name_detail';
  $handler->display->display_options['fields']['name_detail']['table'] = 'users';
  $handler->display->display_options['fields']['name_detail']['field'] = 'name_detail';
  $handler->display->display_options['fields']['name_detail']['relationship'] = 'uid';
  $handler->display->display_options['fields']['name_detail']['label'] = '用户';

  /* Display: 积分与奖金 */
  $handler = $view->new_display('page', '积分与奖金', 'page');
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* 字段: User: 用户昵称与实名 */
  $handler->display->display_options['fields']['name_detail']['id'] = 'name_detail';
  $handler->display->display_options['fields']['name_detail']['table'] = 'users';
  $handler->display->display_options['fields']['name_detail']['field'] = 'name_detail';
  $handler->display->display_options['fields']['name_detail']['relationship'] = 'uid';
  $handler->display->display_options['fields']['name_detail']['label'] = '用户';
  /* 字段: Userpoints Transactions: Category */
  $handler->display->display_options['fields']['tid']['id'] = 'tid';
  $handler->display->display_options['fields']['tid']['table'] = 'userpoints_txn';
  $handler->display->display_options['fields']['tid']['field'] = 'tid';
  $handler->display->display_options['fields']['tid']['label'] = '分类';
  /* 字段: Userpoints Transactions: Points */
  $handler->display->display_options['fields']['points']['id'] = 'points';
  $handler->display->display_options['fields']['points']['table'] = 'userpoints_txn';
  $handler->display->display_options['fields']['points']['field'] = 'points';
  $handler->display->display_options['fields']['points']['label'] = '点';
  /* 字段: Userpoints Transactions: Reference */
  $handler->display->display_options['fields']['reference']['id'] = 'reference';
  $handler->display->display_options['fields']['reference']['table'] = 'userpoints_txn';
  $handler->display->display_options['fields']['reference']['field'] = 'reference';
  $handler->display->display_options['fields']['reference']['label'] = '参考';
  /* 字段: Userpoints Transactions: Description */
  $handler->display->display_options['fields']['description']['id'] = 'description';
  $handler->display->display_options['fields']['description']['table'] = 'userpoints_txn';
  $handler->display->display_options['fields']['description']['field'] = 'description';
  $handler->display->display_options['fields']['description']['label'] = '描述';
  /* 字段: Userpoints Transactions: Timestamp */
  $handler->display->display_options['fields']['time_stamp']['id'] = 'time_stamp';
  $handler->display->display_options['fields']['time_stamp']['table'] = 'userpoints_txn';
  $handler->display->display_options['fields']['time_stamp']['field'] = 'time_stamp';
  $handler->display->display_options['fields']['time_stamp']['label'] = '时间';
  $handler->display->display_options['fields']['time_stamp']['date_format'] = 'custom';
  $handler->display->display_options['fields']['time_stamp']['custom_date_format'] = 'Y/m/d';
  $handler->display->display_options['fields']['time_stamp']['second_date_format'] = 'long';
  /* 字段: Userpoints Transactions: 操作、动作 */
  $handler->display->display_options['fields']['cowpro_operation']['id'] = 'cowpro_operation';
  $handler->display->display_options['fields']['cowpro_operation']['table'] = 'userpoints_txn';
  $handler->display->display_options['fields']['cowpro_operation']['field'] = 'cowpro_operation';
  $handler->display->display_options['fields']['cowpro_operation']['label'] = '操作';
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* 过滤规则: Userpoints Transactions: Category */
  $handler->display->display_options['filters']['tid']['id'] = 'tid';
  $handler->display->display_options['filters']['tid']['table'] = 'userpoints_txn';
  $handler->display->display_options['filters']['tid']['field'] = 'tid';
  $handler->display->display_options['filters']['tid']['exposed'] = TRUE;
  $handler->display->display_options['filters']['tid']['expose']['operator_id'] = 'tid_op';
  $handler->display->display_options['filters']['tid']['expose']['label'] = '分类';
  $handler->display->display_options['filters']['tid']['expose']['operator'] = 'tid_op';
  $handler->display->display_options['filters']['tid']['expose']['identifier'] = 'tid';
  $handler->display->display_options['filters']['tid']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    6 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
    7 => 0,
  );
  /* 过滤规则: Userpoints Transactions: Timestamp */
  $handler->display->display_options['filters']['time_stamp']['id'] = 'time_stamp';
  $handler->display->display_options['filters']['time_stamp']['table'] = 'userpoints_txn';
  $handler->display->display_options['filters']['time_stamp']['field'] = 'time_stamp';
  $handler->display->display_options['filters']['time_stamp']['operator'] = 'between';
  $handler->display->display_options['filters']['time_stamp']['exposed'] = TRUE;
  $handler->display->display_options['filters']['time_stamp']['expose']['operator_id'] = 'time_stamp_op';
  $handler->display->display_options['filters']['time_stamp']['expose']['label'] = '时间(格式：YYYY/MM/DD) ';
  $handler->display->display_options['filters']['time_stamp']['expose']['operator'] = 'time_stamp_op';
  $handler->display->display_options['filters']['time_stamp']['expose']['identifier'] = 'time_stamp';
  $handler->display->display_options['filters']['time_stamp']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    6 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
    7 => 0,
  );
  $handler->display->display_options['path'] = 'userpoints-search';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = '积分与奖金';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;

  /* Display: 商城购物 */
  $handler = $view->new_display('page', '商城购物', 'page_1');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = '商城购物';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* 字段: User: 用户昵称与实名 */
  $handler->display->display_options['fields']['name_detail']['id'] = 'name_detail';
  $handler->display->display_options['fields']['name_detail']['table'] = 'users';
  $handler->display->display_options['fields']['name_detail']['field'] = 'name_detail';
  $handler->display->display_options['fields']['name_detail']['relationship'] = 'uid';
  $handler->display->display_options['fields']['name_detail']['label'] = '用户';
  /* 字段: Userpoints Transactions: Points */
  $handler->display->display_options['fields']['points']['id'] = 'points';
  $handler->display->display_options['fields']['points']['table'] = 'userpoints_txn';
  $handler->display->display_options['fields']['points']['field'] = 'points';
  $handler->display->display_options['fields']['points']['label'] = '点';
  /* 字段: Userpoints Transactions: Description */
  $handler->display->display_options['fields']['description']['id'] = 'description';
  $handler->display->display_options['fields']['description']['table'] = 'userpoints_txn';
  $handler->display->display_options['fields']['description']['field'] = 'description';
  $handler->display->display_options['fields']['description']['label'] = '描述';
  /* 字段: Userpoints Transactions: Timestamp */
  $handler->display->display_options['fields']['time_stamp']['id'] = 'time_stamp';
  $handler->display->display_options['fields']['time_stamp']['table'] = 'userpoints_txn';
  $handler->display->display_options['fields']['time_stamp']['field'] = 'time_stamp';
  $handler->display->display_options['fields']['time_stamp']['label'] = '时间';
  $handler->display->display_options['fields']['time_stamp']['date_format'] = 'custom';
  $handler->display->display_options['fields']['time_stamp']['custom_date_format'] = 'Y/m/d';
  $handler->display->display_options['fields']['time_stamp']['second_date_format'] = 'long';
  /* 字段: User: 手机验证 */
  $handler->display->display_options['fields']['mobile_certification']['id'] = 'mobile_certification';
  $handler->display->display_options['fields']['mobile_certification']['table'] = 'users';
  $handler->display->display_options['fields']['mobile_certification']['field'] = 'mobile_certification';
  $handler->display->display_options['fields']['mobile_certification']['relationship'] = 'uid';
  $handler->display->display_options['fields']['mobile_certification']['label'] = '手机';
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* 过滤规则: Userpoints Transactions: Category */
  $handler->display->display_options['filters']['tid']['id'] = 'tid';
  $handler->display->display_options['filters']['tid']['table'] = 'userpoints_txn';
  $handler->display->display_options['filters']['tid']['field'] = 'tid';
  $handler->display->display_options['filters']['tid']['value'] = array(
    0 => '0',
  );
  $handler->display->display_options['filters']['tid']['group'] = 1;
  $handler->display->display_options['filters']['tid']['expose']['operator_id'] = 'tid_op';
  $handler->display->display_options['filters']['tid']['expose']['label'] = '分类';
  $handler->display->display_options['filters']['tid']['expose']['operator'] = 'tid_op';
  $handler->display->display_options['filters']['tid']['expose']['identifier'] = 'tid';
  $handler->display->display_options['filters']['tid']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    6 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
    7 => 0,
  );
  /* 过滤规则: Userpoints Transactions: Reference */
  $handler->display->display_options['filters']['reference']['id'] = 'reference';
  $handler->display->display_options['filters']['reference']['table'] = 'userpoints_txn';
  $handler->display->display_options['filters']['reference']['field'] = 'reference';
  $handler->display->display_options['filters']['reference']['value'] = 'shop';
  $handler->display->display_options['filters']['reference']['group'] = 1;
  /* 过滤规则: Userpoints Transactions: Timestamp */
  $handler->display->display_options['filters']['time_stamp']['id'] = 'time_stamp';
  $handler->display->display_options['filters']['time_stamp']['table'] = 'userpoints_txn';
  $handler->display->display_options['filters']['time_stamp']['field'] = 'time_stamp';
  $handler->display->display_options['filters']['time_stamp']['operator'] = 'between';
  $handler->display->display_options['filters']['time_stamp']['group'] = 1;
  $handler->display->display_options['filters']['time_stamp']['exposed'] = TRUE;
  $handler->display->display_options['filters']['time_stamp']['expose']['operator_id'] = 'time_stamp_op';
  $handler->display->display_options['filters']['time_stamp']['expose']['label'] = '时间(格式：YYYY/MM/DD) ';
  $handler->display->display_options['filters']['time_stamp']['expose']['operator'] = 'time_stamp_op';
  $handler->display->display_options['filters']['time_stamp']['expose']['identifier'] = 'time_stamp';
  $handler->display->display_options['filters']['time_stamp']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    6 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
    7 => 0,
  );
  $handler->display->display_options['path'] = 'userpoints-shop';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = '商城购物';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;

  /* Display: 商城购物，导出 */
  $handler = $view->new_display('views_data_export', '商城购物，导出', 'views_data_export_1');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = '商城购物，导出';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'views_data_export_xls';
  $handler->display->display_options['style_options']['provide_file'] = 0;
  $handler->display->display_options['style_options']['parent_sort'] = 0;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* 字段: User: 用户昵称与实名 */
  $handler->display->display_options['fields']['name_detail']['id'] = 'name_detail';
  $handler->display->display_options['fields']['name_detail']['table'] = 'users';
  $handler->display->display_options['fields']['name_detail']['field'] = 'name_detail';
  $handler->display->display_options['fields']['name_detail']['relationship'] = 'uid';
  $handler->display->display_options['fields']['name_detail']['label'] = '用户';
  /* 字段: Userpoints Transactions: Points */
  $handler->display->display_options['fields']['points']['id'] = 'points';
  $handler->display->display_options['fields']['points']['table'] = 'userpoints_txn';
  $handler->display->display_options['fields']['points']['field'] = 'points';
  $handler->display->display_options['fields']['points']['label'] = '点';
  /* 字段: Userpoints Transactions: Description */
  $handler->display->display_options['fields']['description']['id'] = 'description';
  $handler->display->display_options['fields']['description']['table'] = 'userpoints_txn';
  $handler->display->display_options['fields']['description']['field'] = 'description';
  $handler->display->display_options['fields']['description']['label'] = '描述';
  /* 字段: Userpoints Transactions: Timestamp */
  $handler->display->display_options['fields']['time_stamp']['id'] = 'time_stamp';
  $handler->display->display_options['fields']['time_stamp']['table'] = 'userpoints_txn';
  $handler->display->display_options['fields']['time_stamp']['field'] = 'time_stamp';
  $handler->display->display_options['fields']['time_stamp']['label'] = '时间';
  $handler->display->display_options['fields']['time_stamp']['date_format'] = 'custom';
  $handler->display->display_options['fields']['time_stamp']['custom_date_format'] = 'Y/m/d';
  $handler->display->display_options['fields']['time_stamp']['second_date_format'] = 'long';
  /* 字段: User: 手机验证 */
  $handler->display->display_options['fields']['mobile_certification']['id'] = 'mobile_certification';
  $handler->display->display_options['fields']['mobile_certification']['table'] = 'users';
  $handler->display->display_options['fields']['mobile_certification']['field'] = 'mobile_certification';
  $handler->display->display_options['fields']['mobile_certification']['relationship'] = 'uid';
  $handler->display->display_options['fields']['mobile_certification']['label'] = '手机';
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* 过滤规则: Userpoints Transactions: Category */
  $handler->display->display_options['filters']['tid']['id'] = 'tid';
  $handler->display->display_options['filters']['tid']['table'] = 'userpoints_txn';
  $handler->display->display_options['filters']['tid']['field'] = 'tid';
  $handler->display->display_options['filters']['tid']['value'] = array(
    0 => '0',
  );
  $handler->display->display_options['filters']['tid']['group'] = 1;
  /* 过滤规则: Userpoints Transactions: Reference */
  $handler->display->display_options['filters']['reference']['id'] = 'reference';
  $handler->display->display_options['filters']['reference']['table'] = 'userpoints_txn';
  $handler->display->display_options['filters']['reference']['field'] = 'reference';
  $handler->display->display_options['filters']['reference']['value'] = 'shop';
  $handler->display->display_options['filters']['reference']['group'] = 1;
  /* 过滤规则: Userpoints Transactions: Timestamp */
  $handler->display->display_options['filters']['time_stamp']['id'] = 'time_stamp';
  $handler->display->display_options['filters']['time_stamp']['table'] = 'userpoints_txn';
  $handler->display->display_options['filters']['time_stamp']['field'] = 'time_stamp';
  $handler->display->display_options['filters']['time_stamp']['operator'] = 'between';
  $handler->display->display_options['filters']['time_stamp']['group'] = 1;
  $handler->display->display_options['filters']['time_stamp']['exposed'] = TRUE;
  $handler->display->display_options['filters']['time_stamp']['expose']['operator_id'] = 'time_stamp_op';
  $handler->display->display_options['filters']['time_stamp']['expose']['label'] = '时间(格式：YYYY/MM/DD) ';
  $handler->display->display_options['filters']['time_stamp']['expose']['operator'] = 'time_stamp_op';
  $handler->display->display_options['filters']['time_stamp']['expose']['identifier'] = 'time_stamp';
  $handler->display->display_options['filters']['time_stamp']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    6 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
    7 => 0,
  );
  $handler->display->display_options['path'] = 'userpoints-shop.xls';
  $handler->display->display_options['displays'] = array(
    'page_1' => 'page_1',
    'default' => 0,
    'page' => 0,
  );
  $handler->display->display_options['sitename_title'] = 0;
  $translatables['userpoints_search'] = array(
    t('Master'),
    t('积分与奖金'),
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
    t('用户'),
    t('分类'),
    t('点'),
    t('.'),
    t(','),
    t('参考'),
    t('描述'),
    t('时间'),
    t('操作'),
    t('时间(格式：YYYY/MM/DD) '),
    t('商城购物'),
    t('手机'),
    t('商城购物，导出'),
  );
  $export['userpoints_search'] = $view;

  $view = new view();
  $view->name = 'userpoints_sum';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'userpoints';
  $view->human_name = '全部积分';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = '全部积分';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['use_more_text'] = '更多';
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'access user profiles';
  $handler->display->display_options['cache']['type'] = 'time';
  $handler->display->display_options['cache']['results_lifespan'] = '3600';
  $handler->display->display_options['cache']['results_lifespan_custom'] = '0';
  $handler->display->display_options['cache']['output_lifespan'] = '3600';
  $handler->display->display_options['cache']['output_lifespan_custom'] = '0';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['submit_button'] = '应用';
  $handler->display->display_options['exposed_form']['options']['reset_button_label'] = '重置';
  $handler->display->display_options['exposed_form']['options']['exposed_sorts_label'] = '排序依据';
  $handler->display->display_options['exposed_form']['options']['sort_asc_label'] = '升序';
  $handler->display->display_options['exposed_form']['options']['sort_desc_label'] = '降序';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '30';
  $handler->display->display_options['pager']['options']['expose']['items_per_page_label'] = '每页条目数';
  $handler->display->display_options['pager']['options']['expose']['items_per_page_options_all_label'] = '- 全部 -';
  $handler->display->display_options['pager']['options']['expose']['offset_label'] = '偏移量';
  $handler->display->display_options['pager']['options']['tags']['first'] = '« 第一页';
  $handler->display->display_options['pager']['options']['tags']['previous'] = '‹ 前一页';
  $handler->display->display_options['pager']['options']['tags']['next'] = '下一页 ›';
  $handler->display->display_options['pager']['options']['tags']['last'] = '末页 »';
  $handler->display->display_options['style_plugin'] = 'table';
  /* 关联: Userpoints: User */
  $handler->display->display_options['relationships']['uid']['id'] = 'uid';
  $handler->display->display_options['relationships']['uid']['table'] = 'userpoints';
  $handler->display->display_options['relationships']['uid']['field'] = 'uid';
  $handler->display->display_options['relationships']['uid']['label'] = '用户';
  /* 字段: User: 用户昵称与实名 */
  $handler->display->display_options['fields']['name_detail']['id'] = 'name_detail';
  $handler->display->display_options['fields']['name_detail']['table'] = 'users';
  $handler->display->display_options['fields']['name_detail']['field'] = 'name_detail';
  $handler->display->display_options['fields']['name_detail']['relationship'] = 'uid';
  /* 字段: User: 手机验证 */
  $handler->display->display_options['fields']['mobile_certification']['id'] = 'mobile_certification';
  $handler->display->display_options['fields']['mobile_certification']['table'] = 'users';
  $handler->display->display_options['fields']['mobile_certification']['field'] = 'mobile_certification';
  $handler->display->display_options['fields']['mobile_certification']['relationship'] = 'uid';
  /* 字段: Userpoints: Current 积分 in category */
  $handler->display->display_options['fields']['points']['id'] = 'points';
  $handler->display->display_options['fields']['points']['table'] = 'userpoints';
  $handler->display->display_options['fields']['points']['field'] = 'points';
  $handler->display->display_options['fields']['points']['label'] = '分值';
  /* 字段: Userpoints: Points category */
  $handler->display->display_options['fields']['tid']['id'] = 'tid';
  $handler->display->display_options['fields']['tid']['table'] = 'userpoints';
  $handler->display->display_options['fields']['tid']['field'] = 'tid';
  $handler->display->display_options['fields']['tid']['label'] = '分类';
  /* 字段: Userpoints: 操作、动作 */
  $handler->display->display_options['fields']['cowpro_operation']['id'] = 'cowpro_operation';
  $handler->display->display_options['fields']['cowpro_operation']['table'] = 'userpoints';
  $handler->display->display_options['fields']['cowpro_operation']['field'] = 'cowpro_operation';
  $handler->display->display_options['fields']['cowpro_operation']['label'] = '操作';
  /* 排序标准: Userpoints: Current 积分 in category */
  $handler->display->display_options['sorts']['points']['id'] = 'points';
  $handler->display->display_options['sorts']['points']['table'] = 'userpoints';
  $handler->display->display_options['sorts']['points']['field'] = 'points';
  $handler->display->display_options['sorts']['points']['order'] = 'DESC';
  /* 过滤规则: Userpoints: Points category */
  $handler->display->display_options['filters']['tid']['id'] = 'tid';
  $handler->display->display_options['filters']['tid']['table'] = 'userpoints';
  $handler->display->display_options['filters']['tid']['field'] = 'tid';
  $handler->display->display_options['filters']['tid']['group'] = 1;
  $handler->display->display_options['filters']['tid']['exposed'] = TRUE;
  $handler->display->display_options['filters']['tid']['expose']['operator_id'] = 'tid_op';
  $handler->display->display_options['filters']['tid']['expose']['label'] = '分类';
  $handler->display->display_options['filters']['tid']['expose']['operator'] = 'tid_op';
  $handler->display->display_options['filters']['tid']['expose']['identifier'] = 'tid';
  $handler->display->display_options['filters']['tid']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    6 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
    7 => 0,
    8 => 0,
  );
  /* 过滤规则: Userpoints: Current 积分 in category */
  $handler->display->display_options['filters']['points']['id'] = 'points';
  $handler->display->display_options['filters']['points']['table'] = 'userpoints';
  $handler->display->display_options['filters']['points']['field'] = 'points';
  $handler->display->display_options['filters']['points']['operator'] = '>';
  $handler->display->display_options['filters']['points']['group'] = 1;
  $handler->display->display_options['filters']['points']['exposed'] = TRUE;
  $handler->display->display_options['filters']['points']['expose']['operator_id'] = 'points_op';
  $handler->display->display_options['filters']['points']['expose']['label'] = '分值大于';
  $handler->display->display_options['filters']['points']['expose']['operator'] = 'points_op';
  $handler->display->display_options['filters']['points']['expose']['identifier'] = 'points';
  $handler->display->display_options['filters']['points']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    6 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
    7 => 0,
    8 => 0,
  );

  /* Display: 全部积分 */
  $handler = $view->new_display('page', '全部积分', 'page');
  $handler->display->display_options['path'] = 'userpoints-sum';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = '全部积分';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;

  /* Display: 全部积分，导出 */
  $handler = $view->new_display('views_data_export', '全部积分，导出', 'views_data_export_1');
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'views_data_export_xls';
  $handler->display->display_options['style_options']['provide_file'] = 0;
  $handler->display->display_options['style_options']['parent_sort'] = 0;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* 字段: User: 用户昵称与实名 */
  $handler->display->display_options['fields']['name_detail']['id'] = 'name_detail';
  $handler->display->display_options['fields']['name_detail']['table'] = 'users';
  $handler->display->display_options['fields']['name_detail']['field'] = 'name_detail';
  $handler->display->display_options['fields']['name_detail']['relationship'] = 'uid';
  /* 字段: User: 手机验证 */
  $handler->display->display_options['fields']['mobile_certification']['id'] = 'mobile_certification';
  $handler->display->display_options['fields']['mobile_certification']['table'] = 'users';
  $handler->display->display_options['fields']['mobile_certification']['field'] = 'mobile_certification';
  $handler->display->display_options['fields']['mobile_certification']['relationship'] = 'uid';
  /* 字段: Userpoints: Current 积分 in category */
  $handler->display->display_options['fields']['points']['id'] = 'points';
  $handler->display->display_options['fields']['points']['table'] = 'userpoints';
  $handler->display->display_options['fields']['points']['field'] = 'points';
  $handler->display->display_options['fields']['points']['label'] = '分值';
  /* 字段: Userpoints: Points category */
  $handler->display->display_options['fields']['tid']['id'] = 'tid';
  $handler->display->display_options['fields']['tid']['table'] = 'userpoints';
  $handler->display->display_options['fields']['tid']['field'] = 'tid';
  $handler->display->display_options['fields']['tid']['label'] = '分类';
  $handler->display->display_options['path'] = 'userpoints-sum.xls';
  $handler->display->display_options['displays'] = array(
    'page' => 'page',
    'default' => 0,
  );
  $handler->display->display_options['use_batch'] = 'batch';
  $handler->display->display_options['segment_size'] = '100';
  $translatables['userpoints_sum'] = array(
    t('Master'),
    t('全部积分'),
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
    t('用户'),
    t('用户昵称与实名'),
    t('手机验证'),
    t('分值'),
    t('.'),
    t(','),
    t('分类'),
    t('操作'),
    t('分值大于'),
    t('全部积分，导出'),
  );
  $export['userpoints_sum'] = $view;

  return $export;
}
