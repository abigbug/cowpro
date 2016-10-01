(function ($) {

Drupal.behaviors.fileLibrarySummary = {
  attach: function (context) {
    $('fieldset.file-form-library', context).drupalSetSummary(function (context) {
      var library = $('.form-item-library input', context).attr('checked');
      return Drupal.t('Included in library: @library', { '@library': (library ? 'Yes' : 'No') });
    });

  }
};

})(jQuery);
