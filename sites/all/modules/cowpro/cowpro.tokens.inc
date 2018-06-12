<?php
include_once 'cowpro.const.inc';

/*
 * Implementation of hook_token_info.
 */
function cowpro_token_info() {
	$cowpro_type = array (
			'name' => 'Cowpro',
			'description' => '与平台及公司相关的诸如公司名称、地址、公章等等。',
	);
	$cowpro['company_name'] = array (
			'name' => '公司名称',
			'description' => '公司名称'
	);
	$cowpro ['company_address'] = array (
			'name' => '公司营业地址',
			'description' => '公司营业地址'
	);
	$cowpro ['company_organization_code'] = array (
			'name' => '公司组织机构代码',
			'description' => '公司组织机构代码'
	);
	$cowpro ['company_seal_url'] = array (
			'name' => '公司印章图片URL',
			'description' => '公司印章图片URL'
	);

	return array (
			'types' => array (
					'cowpro' => $cowpro_type,
			),
			'tokens' => array (
					'cowpro' => $cowpro,
			)
	);
}

/*
 * Implementation of hook_tokens.
 */
function cowpro_tokens($type, $tokens, array $data = array(), array $options = array()) {
	$replacements = array ();
	if ($type == 'cowpro') {
		$replacements = _cowpro_tokens_replacement ( $type, $tokens, $data, $options );
	}
	return $replacements;
}

function _cowpro_tokens_replacement($type, $tokens, array $data = array(), array $options = array()) {
	if (isset($options['language'])) {
		$language_code = $options['language']->language;
	}
	else {
		$language_code = LANGUAGE_NONE;
	}

	$replacements = array ();
	$sanitize = ! empty ( $options ['sanitize'] );

	// Cowpro tokens.
	if ($type == 'cowpro') {
		foreach ( $tokens as $name => $original ) {
			switch ($name) {
				case 'company_name' :
					$replacements [$original] = variable_get('cowpro_company_name', COWPRO_COMPANY_NAME);
					break;
				case 'company_address' :
					$replacements [$original] = variable_get('cowpro_company_address', COWPRO_COMPANY_ADDRESS);
					break;
				case 'company_organization_code' :
					$replacements [$original] = variable_get('cowpro_company_organization_code', COWPRO_COMPANY_ORGANIZATION_CODE);
					break;
				case 'company_seal_url' :
					$url = '';
					$seal = variable_get('cowpro_company_seal', '');
					if ($seal != '') {
						$file = file_load($seal);
						$url = file_create_url($file->uri);
					}
					$replacements [$original] = $url;
					break;
			}
		}
	}

	return $replacements;
}
