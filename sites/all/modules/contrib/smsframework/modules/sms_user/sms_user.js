(function ($) {
  Drupal.behaviors.smsUser = {
    /**
     * Adds javascript behavior to display the number of characters typed in
     * sms_user actions form.
     *
     * @param $context
     */
    attach: function($context) {
      var $smstext = $('#edit-sms-text');
      var $keystrokes = $('#keystrokes span').eq(0).text('0 / ');
      $smstext.bind('keyup', function(e) {
        var chars = $smstext.val().length;
        $keystrokes.text(chars + ' / ');
      });
    }
  };
}(jQuery));