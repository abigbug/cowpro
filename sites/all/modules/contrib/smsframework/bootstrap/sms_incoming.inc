<?php

/**
 * @file
 *  Include file to (ab)use the cache router to accept and queue SMS.
 *
 *  See smsframework/bootstrap/README.txt for use instructions.
 */

// Initial check of variable availability.
sms_bootstrap_check_vars();

// If it is route for incoming SMS, and bootstrap route is enabled, handle it
// here.
if (variable_get('sms_bootstrap_enabled', FALSE) && ($route = sms_bootstrap_load_route())) {
  // Yes it needs standard Drupal core dir structure.
  require_once DRUPAL_ROOT . '/modules/system/system.queue.inc';
  // Also if you move this file relative to the rest of sms framework.
  require dirname(__FILE__) . '/../sms.parser.inc';
  // Include the absolute path to the file including the SMS provider class.
  require $route['inc'];

  // Check access to the incoming parser.
  $access = $route['parser class']::checkAccess(ip_address(), $_REQUEST);
  if ($access !== TRUE) {
    watchdog('access denied', request_path(), NULL, WATCHDOG_WARNING);
    sms_bootstrap_response($access);
    exit;
  }

  // Parse request with class defined by the SMS provider for the route.
  $parser = new $route['parser class']($_REQUEST);
  $parser->parseRequest();

  $queue = sms_bootstrap_load_queue();

  // Add parsed item to the queue.
  if ($parser->getNumber() || $parser->getMessage()) {
    // @todo change so the full class can be serialized/deserialized.
    $item = array(
      'number' => $parser->getNumber(),
      'message' => $parser->getMessage(),
      'options' => $parser->getOptions(),
    );
    $queue->createItem($item);
  }

  sms_bootstrap_response($parser->getResponse);
  exit;
}

/**
 * Check to see if the request path is a route register to be handled.
 */
function sms_bootstrap_load_route() {
  if (! $routes = variable_get('sms_bootstrap_routes', '')) {
    // No routes defined. Allow core to continue.
    return FALSE;
  }

  if (isset($routes[request_path()])) {
    return $routes[request_path()];
  }

  return FALSE;
}

/**
 * Load and return the appropriate queue.
 *
 * If an alternate queue system is configured. Ensure a required include
 * file is loaded. Use Drupal variables 'queue_class' . $name, or
 * 'queue_default_class' to define the implementation of DrupalQueueInterface
 * to load.
 *
 * Set 'sms_bootstrap_queue' in settings.php if you don't rely on the db.
 */
function sms_bootstrap_load_queue() {
 $queue_info = variable_get('sms_bootstrap_queue', array());
  if (empty($queue_info['require db']) || $queue_info['required db']) {
    // The queue requires the db to be bootstraped, even if all the
    // variables have been supplied so far from settings.php.
    // Default DrupalSystemQueue requires DB. Set your $queue_info['require db']
    // to FALSE if you don't need it.
    drupal_bootstrap(DRUPAL_BOOTSTRAP_DATABASE, FALSE);
  }
  if (! empty($queue_info['inc'])) {
    require($queue_info['inc']);
  }
  $name = empty($queue_info['name']) ? 'sms_incoming' : $queue_info['name'];
  $reliable = empty($queue_info['reliable']) ? TRUE : $queue_info['reliable'];
  $queue = DrupalQueue::get($name, $reliable);
  $queue->createQueue();

  return $queue;
}

/**
 * If either of the required variables are not set load variables.
 *
 * Avoid this by setting both 'sms_bootstrap_routes' and 'sms_bootstrap_enabled'
 * in your settings.php file.
 */
function sms_bootstrap_check_vars() {
  if (variable_get('sms_bootstrap_routes', '') === '' || variable_get('sms_bootstrap_enabled', '') === '') {
    drupal_bootstrap(DRUPAL_BOOTSTRAP_VARIABLES, FALSE);
  }
}

/**
 * Send a HTTP response.
 *
 * @param array $response
 *   array('headers' => array('name' => 'value'), 'body' => 'text')
 */
function sms_bootstrap_response($response) {
  // Allow SMS provider to add content to response.
  foreach ($response['headers'] as $name => $value) {
    drupal_add_http_header($name, $value);
  }
  drupal_send_headers();
  print $response['body'];
}
