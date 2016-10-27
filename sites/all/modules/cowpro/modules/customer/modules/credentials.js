(function($) {
Drupal.behaviors.credentials = {
    attach: function (context, settings) {
    	var beforeSerialize = Drupal.ajax.prototype.beforeSerialize;
    	
    	Drupal.ajax.prototype.beforeSerialize = function (element, options) {
    		options['data']['applicant'] = $('#edit-field-applicant-und-0-uid')[0].value;
    		beforeSerialize.call(this, element, options);
        };

        /*
        if (Drupal.ajax['credentials_select']) {
    	Drupal.ajax['credentials_select'].options.beforeSend = function (xmlhttprequest, options) {
    		alert('beforeSend');
    	}

        // Overwrite beforeSubmit
        Drupal.ajax['credentials_select'].options.beforeSubmit = function (form_values, element, options) {
            // ... Some staff added to form_values
        	alert('beforeSubmit');
            return false; // to prevent AJAX call if needed.
        };
        //Or you can overwrite beforeSubmit
    	Drupal.ajax['credentials_select'].options.beforeSerialize = function (element, options) {

        	alert('beforeSerialize');
            // ... Some staff added to options.data
            // Also call parent function
            Drupal.ajax.prototype.beforeSerialize(element, options);
        };
        }
        */
	}
};
})(jQuery);
