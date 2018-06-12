(function ($) {
  Drupal.behaviors.imageCaptchaRefresh = {
    attach: function (context) {
      $('.reload-captcha', context).not('.processed').bind('click', function () {
        $(this).addClass('processed');
        var $form = $(this).parents('form');
        // Send post query for getting new captcha data.
        var date = new Date();
        var url = this.href + '?' + date.getTime();
        $.get(
          url,
          {},
          function (response) {
            if(response.status == 1) {
              $('.captcha', $form).find('img').attr('src', response.data.url);
              $('input[name=captcha_sid]', $form).val(response.data.sid);
              $('input[name=captcha_token]', $form).val(response.data.token);
            }
            else {
              alert(response.message);
            }
          },
          'json'
          );
        return false;
      });
    }
  };
})(jQuery);
