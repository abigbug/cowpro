(function ($) {

Drupal.behaviors.issuingReviewFieldsetSummaries = {
  attach: function (context) {
    $('fieldset.cowpro-issuing-review-form', context).drupalSetSummary(function (context) {
      if ($('.form-item-field-issuing-und-0-issuing-review-audited input', context).is(':checked')) {
        return '已审核';
      }
      else {
        return '未审核';
      }
    });
  }
}; 

})(jQuery);
