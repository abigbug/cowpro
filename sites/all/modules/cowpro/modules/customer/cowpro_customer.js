(function($) {

Drupal.behaviors.customerFieldsetSummaries = {
  attach: function (context, settings) {
	  /*
    $('fieldset#edit-user', context).drupalSetSummary(function (context) {
      var name = $('#edit-name').val() || Drupal.settings.anonymous;

      return Drupal.t('Owned by @name', { '@name': name });
    });
    $('fieldset#edit-profile-verified', context).drupalSetSummary(function (context) {
      return ($('input[@name=verified]:checked').val() == 0) ?
        '末认证' :
        '已认证';
    });
    */
  }
};

})(jQuery);
