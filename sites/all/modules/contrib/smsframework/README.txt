
Description
===========
Provides a pluggable API for Drupal to interact with SMS messages. 

* sms.module - the core API module
* sms_user.module - provides integration with Drupal users
* sms_blast.module - for sending a batch of messages
* sms_valid.module - provides extensible validation functionality
* sms_track.module - records sms inbound and outbound traffic for tracking purposes
* sms_sendtophone.module - input filter and node links for sending snippets of text via sms
* sms_actions.module - integrates sms with the actions module
* sms_devel.module - integrates sms with devel module

Also integrates well with the Messaging module (http://drupal.org/project/messaging).

More information is available from the groups homepage at: http://groups.drupal.org/sms-framework

Installation
============
1. Drop into your preferred modules directory
2. Enable the modules you want to use from admin/build/modules
3. Set and configure your default gateway at admin/smsframework/gateways
4. Check out the settings pages at admin/smsframework

Documentation
=============
Documentation for site builders and developers is available in the handbook
pages on Drupal.org at the following URL:

http://drupal.org/node/362258

Credits
=======
Will White of Development Seed (http://drupal.org/user/32237)
Tylor Sherman of Raincity Studios (http://drupal.org/user/143420)