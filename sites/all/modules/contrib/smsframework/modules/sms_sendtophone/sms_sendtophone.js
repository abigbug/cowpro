(function ($) {

  Drupal.behaviors.smssendtophone = {
    /**
     * Adds javascript behavior to open sms-sendtophone form in a thickbox.
     *
     * @param context
     */
    attach: function (context) {
      $("a.sms-sendtophone").addClass('thickbox').each(function(i) {
        if ($(this).attr('href').search(/\?/) < 0) {
          $(this).attr('href', $(this).attr('href').concat('?'));
        }
        else {
          $(this).attr('href', $(this).attr('href').concat('&'));
        }
        $(this).attr('href', $(this).attr('href').concat('height=275&width=300&thickbox=1'));
      });
    }
  }
})(jQuery);
  