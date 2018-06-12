=========================
Web Service Client Tester
=========================

Provides a User Interface for testing services known to the 
<a href="http://drupal.org/project/wsclient">Web service client</a>.

Usage
-----
 
Use this to see what is happening under the hood when you use wsclient to talk 
to a remote service.

* First set up a web service using a WSDL or manual entry.
* Visiting the web service client management page
  (/admin/config/services/wsclient/{service})
  you will find a 'Test' button added to the available 'Operations'.
* Using that will present a webform exposing fields derived from the WSDL and 
somewhat emulating the data structure that is expected to make up a service 
request.

Executing that request will then display the request that is being made 
(in raw form with headers and payload) and the response that came back, 
also displaying the response headers and response data or message if any.

If you have devel.module enabled, a rendered dump of the data structure 
(PHP objects constructed by the wsclient) will also be displayed.

Info
----

Validation is not done by this UI, so it's up to you to enter the correct basic 
data types (e.g., date in a date field, int in an integer field)

It was designed to handle advanced, nested complex types as data structures 
that can be both submitted and retrieved. If wsclient can manage the data, we 
should be able to expose it.

History
-------

dman saw <a href="http://drupal.org/node/1812504">A request for a standalone 
form</a> to test web services before digging into rules, and agreed it was 
going to be needed. 

On completion, it was soon absorbed from a sandbok project into wsclient 
project proper.


Related
-------
Other tools in this space (non-Drupal) include 
<a href="https://chrome.google.com/webstore/detail/advanced-rest-client">
Advanced REST Client, a browser plugin for Chrome</a> 
and the "Web Services Explorer" plugin for Eclipse. 
But if you want to know what your PHP Drupal site is really doing, you need to 
expose the workings of the real transactions.