----------------------------
An option for receiving SMS
----------------------------

To receive, parse and queue SMS for processing at a low bootstrap level.

The include file (ab)uses the option to include a file at the cache level of
bootstrap. 
It provides a very basic routing system, which allows SMS provider modules
to claim paths and allocate a parser class for the incoming request.
The parsed SMS is then queued for later processing. By default the core
database Drupal Queue will be used. To use an alternate queue and avoid 
bootstrapping the database see the configuration under.

------------------
Using Drupal Queue
------------------

At its simplest add to your settings.php file the line:

  // Path to the smsframework/bootstrap/sms_incoming.inc file to include.
  $conf['cache_backends'][] = 'sites/all/module/smsframework/bootstrap/sms_incoming.inc';

And set the variable 'sms_bootstrap_enabled' to TRUE. This can also be fixed in the
settings.php file:

  $conf['sms_bootstrap_enabled'] = TRUE;

You will need a SMS provider module that implements the SmsParserInterface and offers this
in 'sms_bootstrap_routes' variable.
To avoid loading the variables you can also set this in the settings.php file. For example:

  $conf['sms_bootstrap_routes'] = array(
    'path/to/receive/sms' => array(
      // Path to include the SmsParser class file.
      'inc' => 'sites/all/modules/sms_provider/sms_provider.parser.inc',

      // Parser class name.
      'parser class' => 'SmsProviderParserClass',
    ),
  );

------------------------
Using an Alternate Queue
------------------------

If you are using a queue implementation of DrupalQueue that does not use the 
database, you first must set all the variables above in you settings.php file.
All variables required need to be in the settings.php to prevent the DB being
loaded.

Identify your queue with DrupalQueue by setting the appropriate variable. One
of:

  // If the queue is being used as the default.
  $conf['queue_default_class'] = 'YourQueueClass';

  // If you want to use the default queue name.
  $conf['queue_class_sms_incoming'] = 'YourQueueClass';

  // If you use another queue. Then also set 'name' => 'your_name' below.
  $conf['queue_class_your_name'] = 'YourQueueClass';

Then to identify you queue with any of these that maybe required:-

  $conf['sms_bootstrap_queue'] = array(
    // The path to include YourQueueClass. This is probably the only
    // value that is absolutely required.
    'inc' => 'path/to/required/queue.inc',

    // To announce that the queue does not require the database.
    // If other cache_backends are enabled, depending on order, and the
    // 'page_cache_without_database' setting, the database may be loaded
    // anyway. See documentation of your cache backend.
    'require db' => FALSE,

    // If not specified the default queue name is 'sms_incoming'.
    'name' => 'queue_name',

    // Default is a reliable queue.
    'reliable' => TRUE,
  );

---------------
Developer notes
---------------

If you are writing an SMS provider to support queueing, you will need to
implement a parser class, preferably in a seperate include file. See:
smsframework/sms.parser.inc for SmsParserInterface and the base
SmsParserBase class.

Automagically adding your route to the 'sms_bootstrap_routes' array, see
example above, will aid users not setting the path and class in their
settings.php $conf variables. Remember you have to include the absolute
inc path (__DIR__, dirname(__FILE__) etc.)
