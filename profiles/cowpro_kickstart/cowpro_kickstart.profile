<?php
/**
 * Implements hook_form_FORM_ID_alter().
 *
 * Allows the profile to alter the site configuration form.
 */
function cowpro_kickstart_form_install_configure_form_alter(&$form, $form_state) {
	$form ['site_information'] ['site_name'] ['#default_value'] = '奶牛专家';
	$form ['server_settings'] ['site_default_country'] ['#default_value'] = 'CN';
	// 以下是 install profile 测试阶段的缺省值，在发行版本中，要屏蔽
	$form ['site_information'] ['site_mail'] ['#default_value'] = '15893969@qq.com';
	$form ['admin_account'] ['account'] ['name'] ['#default_value'] = 'admin';
	$form ['admin_account'] ['account'] ['mail'] ['#default_value'] = '15893969@qq.com';
}

/**
 * Implements hook_form_alter().
 *
 * Select the current install profile by default.
 */
function cowpro_kickstart_form_install_select_profile_form_alter(&$form, $form_state) {
	foreach ( $form ['profile'] as $key => $element ) {
		$form ['profile'] [$key] ['#value'] = 'cowpro_kickstart';
	}
}

/**
 * Implement hook_install_tasks_alter().
 */
function cowpro_kickstart_install_tasks_alter(&$tasks, $install_state) {
	global $install_state;
	$install_state ['parameters'] ['locale'] = 'zh-hans';
	// Hide 'Choose language' installation task.
	// $tasks ['install_select_locale'] ['display'] = FALSE;
	$tasks ['install_select_locale'] ['run'] = INSTALL_TASK_SKIP;
}

/**
 * Implements hook_install_tasks().
 */
function cowpro_kickstart_install_tasks($install_state) {
	if (isset($install_state['parameters']['theme'])) {
		$theme_id = $install_state['parameters']['theme'];
	}

	$tasks ['cowpro_kickstart_install_select_theme'] = array (
			'display_name' => st ( '选择主题（网站界面）' ),
			'type' => 'form',
			'function' => 'cowpro_kickstart_theme_select_form',
	);
	/*
	$task['cowpro_kickstart_install_select_theme_sumbit'] = array(
	  'display_name' => '开始安装网站主题',
	  'type' => 'batch',
		'run' => INSTALL_TASK_RUN_IF_NOT_COMPLETED,
	  'function' => 'cowpro_kickstart_install_select_theme_sumbit',
	);
	*/
	$tasks ['cowpro_kickstart_import_translations'] = array (
			'display_name' => st ( '导入汉化文件' ),
			'type' => 'batch',
	);
	$tasks ['cowpro_kickstart_grant_default_permissions'] = array (
			'display_name' => st ( '设置权限' ),
			'type' => 'batch',
	);
	$tasks ['cowpro_kickstart_customer_setup'] = array (
			'display_name' => st ( '初始化站点' ),
			'type' => 'batch',
	);

	return $tasks;
}

function cowpro_kickstart_install_select_theme_submit($form, &$form_state) {
	require_once 'cowpro_kickstart.theme.inc';

	$theme_id = $form_state['values']['theme'];
	if ($theme_id == 'cowpro_p2p_v1') {
		_install_theme_v1();
	} else if ($theme_id == 'cowpro_p2p_v2') {
		_install_theme_v2();
	}
}

function cowpro_kickstart_theme_select_form($form, &$form_state) {
	$theme_options = array(
			'cowpro_p2p_v1' => 'cowpro_p2p_v1',
			'cowpro_p2p_v2' => 'cowpro_p2p_v2',
	);
	$themes = system_rebuild_theme_data();
	$theme_v1 = $themes['cowpro_p2p'];
	$theme_v2 = $themes['cowpro_p2p_v2'];
	$form['screenshot_v1'] = array(
			'#markup' => '<p>' . $theme_v1->info['name'] . ' ' . $theme_v1->info['description'] . '</p><br/><img src=' . $theme_v1->info['screenshot'] . ' /><br/>',
	);
	$form['screenshot_v2'] = array(
			'#markup' => '<p>' . $theme_v2->info['name'] . ' ' . $theme_v2->info['description'] . '</p><br/><img src=' . $theme_v2->info['screenshot'] . ' /><br/>',
	);
	$form['theme'] = array(
			'#type' => 'radios',
			'#title' => '选择网站外观',
			'#default_value' => 'cowpro_p2p_v2',
			'#options' => $theme_options,
			'#description' => '请选择网站外观',
	);
	$form['actions'] = array('#type' => 'actions');
	$form['actions']['submit'] =  array(
			'#type' => 'submit',
			'#value' => st('Save and continue'),
	);
	$form['#submit'][] = 'cowpro_kickstart_install_select_theme_submit';
	return $form;
}

/**
 * Installation task callback: creates batch process to enable additional
 * languages and download relevant interface translations.
 */
function cowpro_kickstart_import_translations() {
	include_once DRUPAL_ROOT . '/includes/locale.inc';
	module_load_include ( 'drush.inc', 'l10n_update' );
	module_load_include ( 'fetch.inc', 'l10n_update' );
	module_load_include ( 'batch.inc', 'l10n_update' );

	variable_set ( 'l10n_update_check_mode', 2 ); // L10N_UPDATE_USE_SOURCE_LOCAL 'Local files only'
	variable_set ( 'l10n_update_download_store', 'sites/all/translations' );
	variable_set ( 'l10n_update_import_mode', 0 ); // LOCALE_IMPORT_OVERWRITE 'Overwrite existing translations'

	$updates = array ();
	$languages = array (
			'cn'
	);
	$status = l10n_update_get_status ();

	if (isset($status['drupal'])) {
		//不需要重复安装 druapl core 的翻译文件，这样可以加快安装进度
		unset($status['drupal']);
	}

	// Prepare information about projects which have available translation
	// updates.
	if ($languages && $status) {
		foreach ( $status as $project ) {
			foreach ( $project as $langcode => $project_info ) {
				// Translation update found for this project-language combination.
				if ($project_info->type && ($project_info->type == L10N_UPDATE_LOCAL || $project_info->type == L10N_UPDATE_REMOTE)) {
					$updates ['projects'] [$project_info->name] = $project_info;
					$updates ['languages'] [$langcode] = $project_info;
				}
			}
		}
	}

	$options = _l10n_update_default_update_options ();
	$options ['overwrite_options'] = array (
			'not_customized' => TRUE,
			'customized' => TRUE
	);
	$languages = array (
			'zh-hans'
	);
	$projects = array_keys($status);

	$batch = l10n_update_batch_update_build ( $projects, $languages, $options );
	$batch ['title'] = '导入汉化文件';

	return $batch;
}

/**
 * 有些动态的权限，比如根据不同的 customer type 而生成的权限，不方便使用 features 来加载
 * 这些动态的权限调用 cowpro_grant_default_permissions() 进行加载
 */
function cowpro_kickstart_grant_default_permissions() {
	cowpro_grant_default_permissions ();
}

/**
 *
 */
function cowpro_kickstart_customer_setup() {
	$languages = language_list ();
	variable_set ( 'language_default', $languages ['zh-hans'] );
	// variable_set('language_default', (object) array('language' => 'en', 'name' => 'English', 'native' => 'English', 'direction' => 0, 'enabled' => 1, 'plurals' => 0, 'formula' => '', 'domain' => '', 'prefix' => '', 'weight' => 0, 'javascript' => ''));

	// 禁用英语，只保留中文简体
	// 这样，在 user/%user/edit 驱动的用户编辑功能下，不会出现“语言设置”选项
	// 去除繁琐的输入项，提供精简的界面有利于提高产品的易用性
	db_update ( 'languages' )->fields ( array (
			'enabled' => 0
	) )->condition ( 'language', 'en' )->execute ();
	variable_set ( 'language_count', 1 );

	// 关闭“本地化设置”界面
	// 在“用户编辑与注册”表单中，不显示“选择时区”的界面
	variable_set ( 'configurable_timezones', 0 );

	variable_set ( 'user_register', USER_REGISTER_VISITORS );

	// optional_mail_on_register模块
	variable_set ( 'optionalmail_register', 1 );
	variable_set ( 'user_email_verification', FALSE );
	if (module_exists ( 'contact' )) {
		// 参考方法 optional_mail_on_register_optionalmail_settings_submit
		variable_set ( 'contact_default_status', FALSE );
	}
	variable_set ( 'optionalmail_edit', 1 );
	variable_set ( 'optionalmail_alterfield_register', 'field visible' );
	variable_set ( 'optionalmail_alterfield_edit', 'field visible' );

	//与point模块有关的汉化设置
	variable_set(USERPOINTS_TRANS_UCPOINTS, '积分');
	variable_set(USERPOINTS_TRANS_LCPOINTS, '积分');
	variable_set(USERPOINTS_TRANS_UCPOINT, '积分');
	variable_set(USERPOINTS_TRANS_LCPOINT, '积分');
	variable_set(USERPOINTS_TRANS_UNCAT, '普通积分');
	_import_customized_translation();

	_import_example_data ();
	_import_seal();

	// Update the menu router information.
	module_enable(array('cowpro_menu'));
	features_revert_module('cowpro_menu');
	menu_rebuild ();
	// ignore any rebuild messages
	node_access_needs_rebuild ( FALSE );
	// ignore any other install messages
	drupal_get_messages ();
}

/**
 * 对系统以及第三方模块的汉化文件中的瑕疵进行优化
 */
function _import_customized_translation() {
	$langcode = 'zh-hans';
	$writer = new PoDatabaseWriter();
	$writer->setLangcode($langcode);
	$writer->setOptions(array(
			'overwrite_options' => array(
					'not_customized' => TRUE,
					'customized' => TRUE,
			),
	));

	$non_customized_translations = array(
			'!Points' => '积分',
			'All points' => '全部积分',
			'Invite' => '邀请',
			'Invitation' => '邀请',
			'Send Invitation' => '发送邀请',
			'Invitation has been sent.' => '邀请已发出',
			'Relationship Type' => '好友关系',
			'User Relationship Type' => '好友关系',
			'Request new password' => '用邮箱重置密码',
			'SMS Framework' => 'SMS通道设置',
			'Carrier configuration' => '运营商设置',
			'Gateway configuration' => '网关设置',
			'Profile saved.' => '资料已保存。',
	);

	foreach ($non_customized_translations as $source => $translation) {
		$poItem = new PoItem();
		$poItem->setFromArray(array(
				'source' => $source,
				'translation' => $translation,
		));
		$writer->writeItem($poItem);
	}

	//对 invite 模块中未汉化的内容进行汉化
	$view = views_get_view('invite');
	$view->human_name = '邀请';
	$view->display['default']->display_options['title'] = '邀请';
	$view->display['default']->display_options['empty']['area']['content'] = '无数据';
	$view->display['page']->display_options['tab_options']['title'] = '邀请';
	$view->save();

}

/**
 * 导入演示用的用户资料以及贷款申请表、合同范本
 */
function _import_example_data() {

	$default_users = array ();
	$default_users [] = array (
			'manager',
			'宋江'
	);
	$default_users [] = array (
			'debtor',
			'吴用'
	);
	$default_users [] = array (
			'debtor',
			'林冲'
	);
	$default_users [] = array (
			'lender',
			'武松'
	);
	$default_users [] = array (
			'lender',
			'杨志'
	);
	$default_users [] = array (
			'lender',
			'史进'
	);
	$default_users [] = array (
			'lender',
			'时迁'
	);

	foreach ( $default_users as $default_user ) {
		$role = user_role_load_by_name ( $default_user [0] );
		$name = $default_user [1];
		$password = 'hello';
		$fields = array (
				'name' => $name,
				'mail' => '',
				'pass' => $password,
				'status' => 1,
				'init' => 'email address',
				'roles' => array (
						$role->rid => $role->name,
				)
		);

		// the first parameter is left blank so a new user is created
		$account = user_save ( '', $fields );
	}

	//按照features_revert_module()的文档说明：This module must be a features module and enabled
	//所以我们在调用features_revert_module()之前，先调用module_enable()
	module_enable(array('cowpro_demo'));
	features_revert_module('cowpro_demo');

	//强制调用cron，驱动defaultcontent_cron()，把node写入表中
	//以便于下面更新node.created
	drupal_cron_run();

	//更新node的create，
	//我们在测试的过程中，会多次反复向乾多多提交对同一个贷款申请表的投标操作
	//乾多多是以BatchNo这个参数为主键来处理贷款申请表
	//这样，在重新安装之后，针对同一个贷款申请表的新的投标测试可能会被乾多多认为可投标的金额不足而返回错误信息
	//所以我们在这里更新created字段，并且在提交乾多多服务器的时候，会把created的值做为贷款申请表orderno的一部分
	$count = db_update('node')
	->fields(array('created' => time(), 'changed' => time()))
	->execute();
	watchdog('cowpro_demo', '更新node记录，共 %count 条', array('%count' => $count), WATCHDOG_NOTICE);

	//cowpro_demo导入到数据库表 node 中的记录，编号从1开始，
	//编号1-4是四个合同模板，下面要处理的贷款申请表编号是从5开始
	/*
	 * 不知是什么原因，在前面 features_revert_module('cowpro_demo') 之后
	 * 正面的代码 node_load 并不能加载到指定的 issuing
	 * features_revert_module('cowpro_demo') 的效果一直到安装结束，才能在数据库中表现出来
	 * 所以这里暂时先不做操作
	$debtor = user_load_by_name ( '吴用' );
	for($nid = 5; $nid <= 7; $nid ++) {
		$node = node_load ( $nid, NULL, TRUE);
		$node->field_applicant ['und'] [0] ['applicant_uid'] = $debtor->uid;
		$node->field_issuing ['und'] [0] ['issuing_start_time'] = time ();
		node_save ( $node );
	}
	$debtor = user_load_by_name ( '林冲' );
	for($nid = 8; $nid <= 11; $nid ++) {
		$node = node_load ( $nid, NULL, TRUE );
		$node->field_applicant ['und'] [0] ['applicant_uid'] = $debtor->uid;
		$node->field_issuing ['und'] [0] ['issuing_start_time'] = time ();
		node_save ( $node );
	}
	*/
}

/**
 * 导入公司的公章
 * 缺省的公章是不个示例，生产环境中，管理员需要另外制作并上传公章的PNG文件
 * 安装好的环境中，管理员可以在 admin/cowpro/config_general 菜单下面上传公章
 * 示例用的公章的图片取自 http://free.clipartof.com/details/49-Free-Cartoon-Cow-Clip-Art
 */
function _import_seal() {
	global $user;
	$uri = 'public://seal/cow.png';
	$filename = 'cow.png';

	$file = new stdClass;
	$file->uid = $user->uid;
	$file->filename = $filename;
	$file->uri = $uri;
	$file->filemime = 'image/png';
	$file->filesize = filesize($uri);
	$file->status = 1;

	file_save($file);
	file_usage_add($file, 'cowpro', 'seal', $user->uid);
}