<?php

/**
 * @file
 * Token callbacks for the sms module.
 */

/**
 * Implements hook_token_info().
 */
function sms_token_info() {
  $info['types']['sms'] = array(
    'name' => t('SMS'),
    'needs-data' => 'sms',
    'description' => t("SMS"),
  );
  $info['tokens']['sms']['number'] = array(
    'name' => t('Number'),
    'description' => t("SMS Phone Number."),
  );
  $info['tokens']['sms']['message'] = array(
    'name' => t('Message'),
    'description' => t("SMS Mesage."),
  );
  return $info;
}

/**
 * Implements hook_tokens().
 */
function sms_tokens($type, $tokens, array $data = array(), array $options = array()) {
  $replacements = array();
  $sanitize = !empty($options['sanitize']);

  // Text format tokens.
  if ($type == 'sms' && !empty($data['sms'])) {
    $sms = $data['sms'];

    foreach ($tokens as $name => $original) {
      switch ($name) {
        case 'number':
          $replacements[$original] = check_plain($sms['number']);
          break;
        case 'message':
          $replacements[$original] = check_plain($sms['message']);
          break;
      }
    }
  }

  return $replacements;
}
