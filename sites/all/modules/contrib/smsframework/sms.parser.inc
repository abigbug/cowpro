<?php

/**
 * Interface and base class for SMS parser.
 *
 * SMS providers can implement this class to parse incoming SMS request.
 * Required if using the bootstrap method.
 */

/**
 * Incoming SMS parser.
 */
interface SmsParserInterface {
  /**
   * Checks access to parser for incoming SMS.
   *
   * Providers usually do this by checking against an allowed (range of) IP
   * addresses. It could also be with a request parameter.
   *
   * Remember when implementing if you use variables that these may not be
   * loaded from the database, and would have to be set in the settings.php
   * file, in the case of a configuration parsing and queuing without
   * bootstrapping the database.
   *
   * @param string $originator
   *   The originator of the SMS. Usually the IP address.
   * @param array $request
   *   $_REQUEST array, or replacement.
   *
   * @return bool|array
   *   TRUE to allow access.
   *   Response array if denied, @see this::response() for format.
   */
  static function checkAccess($originator, $request);

  /**
   * Starts a parser. Load URI information.
   *
   * @param array $request
   *   $_REQUEST array, or replacement.
   */
  public function __construct($request = array());

  /**
   * Sets the request.
   *
   * @param array $request
   *   $_REQUEST array, or replacement.
   */
  public function setRequest($request);

  /**
   * Retrieves SMS sender number.
   *
   * @return string
   *   Number or identifier supplied by SMS provider.
   */
  public function getNumber();

  /**
   * Retrieves SMS message content.
   *
   * @return string
   *   Decoded SMS message body.
   */
  public function getMessage();

  /**
   * Retrieves sms_incoming() options.
   *
   * @return array
   *   Options as defined by sms_incoming().
   */
  public function getOptions();

  /**
   * Retrieves the response if any.
   *
   * Some SMS provider modules offer a HTTP response content. Lacking an
   * HTTP response object this just provides simple options.
   *
   * @return array
   *   Array of header values keyed by header name and body. Example:
   *   @code
   *     array('headers' => array('name' => 'value), 'body' => 'text');
   *   @endcode
   */
  public function getResponse();

  /**
   * Parses the request.
   *
   * @todo Error or return handling. Does it make sense to notify of missing
   *   number, or message?
   */
  public function parseRequest();
}

/**
 * Base implementation of SmsParserInterface().
 */
abstract class SmsParserBase implements SmsParserInterface {
  /**
   * The request being parsed.
   *
   * @var array
   */
  protected $request;

  /**
   * The SMS sender number.
   *
   * @var string
   */
  protected $number;

  /**
   * The SMS body.
   *
   * @var string
   */
  protected $message;

  /**
   * The sms_incoming options.
   *
   * @var array
   */
  protected $options;

  /**
   * {@inheritdoc}
   */
  static function checkAccess($originator, $request) {
    return TRUE;
  }

  /**
   * {@inheritdoc}
   */
  public function __construct($request = array()) {
    $this->request = $request;
    $this->number = '';
    $this->message = '';
    $this->options = array();
  }

  /**
   * {@inheritdoc}
   */
  public function setRequest($request) {
    $this->request = $request;
  }

  /**
   * {@inheritdoc}
   */
  public function getNumber() {
    return $this->number;
  }

  /**
   * {@inheritdoc}
   */
  public function getMessage() {
    return $this->message;
  }

  /**
   * {@inheritdoc}
   */
  public function getOptions() {
    return $this->options;
  }

  /**
   * {@inheritdoc}
   */
  abstract public function parseRequest();

  /**
   * {@inheritdoc}
   */
  public function getResponse() {
    return array(
      'headers' => array(
        // Even though we should have a body entity to return.
        'Status' => '202 Accepted',
      ),
      'body' => '',
    );
  }
}
