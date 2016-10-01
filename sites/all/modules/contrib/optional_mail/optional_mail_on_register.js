(function ($) {
  Drupal.behaviors.OptionalMailOnRegister = {
    attach: function(context) {
      if(jQuery("#edit-optionalmail-register").is(":checked")) {
        jQuery("#optionalmail-radios-options-1").css("display","block");
      }
      if(jQuery("#edit-optionalmail-edit").is(":checked")) {
        jQuery("#optionalmail-radios-options-2").css("display","block");
      }
      jQuery("#edit-optionalmail-register").click(function(){

        if(jQuery("#edit-optionalmail-register").is(":checked")) {
          jQuery("#optionalmail-radios-options-1").slideDown("normal");
        } else {
          jQuery("#optionalmail-radios-options-1").slideUp("normal");
        }
      })
      jQuery("#edit-optionalmail-edit").click(function(){
        if(jQuery("#edit-optionalmail-edit").is(":checked")) {
          jQuery("#optionalmail-radios-options-2").slideDown("normal");
        } else {
          jQuery("#optionalmail-radios-options-2").slideUp("normal");
        }
      })
    }
  };
})(jQuery);
