
Web Service Client Module (wsclient)
------------------------------------
by Klaus Purer (klausi), klaus.purer@epiqo.com
and Wolfgang Ziegler (fago), wolfgang.ziegler@epiqo.com

WSClient provides an interface to consume external web services. It focuses on
integrating web service operations as Rules actions, but can also be used as data
provider for other modules. It also offers a convenient API for developers to
quickly invoke web services.

WSClient ships with two sub-modules that support SOAP and REST endpoints.


Installation
------------

 * WSClient depends on the Entity API module, download and install it from
   http://drupal.org/project/entity
 * The WSClient user interface depends on Rules, download and install it from
   http://drupal.org/project/rules
 * Copy the whole wsclient directory to your modules directory
   (e.g. DRUPAL_ROOT/sites/all/modules) and activate the Web service client and
   Web service client UI modules.
 * The administrative user interface can be found at
   admin/config/services/wsclient
 * If you want to use REST services you have to download and install the
   http_client module (http://drupal.org/project/http_client) and you need to
   activate the Web service client REST module.
 * If you want to use SOAP services you have to activate the Web service client
   SOAP module.


Web service decriptions
-----------------------

 * Before invoking a web service you need a description of it. Enable the Web
   service client examples module to get some examples.
 * The URL of a web service is the base URL for REST services and the link to a
   WSDL file for SOAP services.
 * Every web service has operations, each with parameters and a result.
 * A web service can have custom data types that describe complex parameters or
   results.


Usage with Rules
----------------

 * A web service operation can be executed as Rules action.
 * Go to the Rules UI at admin/config/workflow/rules
 * Add a new rule and choose an event (e.g. "After saving new content").
 * Add an action and choose one in the Web Services group (e.g. "Google Ajax
   APIs: Translate text").
 * Fill out the required operation parameters either directly or use the data
   selection to make use of other variables (e.g. "node:title").
 * Add other follow-up actions to process the result of the web service call.
 * If you need a complex operation parameter, create it beforehand in a "Create
   a data structure" action.


Usage for developers
--------------------

 * You can create web service descriptions in code, see for example
   wsclient_examples.module
 * You can easily invoke web services by loading the description and executing
   an operation (the operation name can be used a dynamic method name):

     $service = wsclient_service_load('google');
     $result = $service->translate('Hallo Welt', 'de|en');
