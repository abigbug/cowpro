jQuery(document).ready(function($) {
    var state = $.cookie('themekey_redirect_state');
    if (state === null) {
        // Cookie not set => state 0.
        state = 0;
    }
    if (state == 0) {
        // Check if the user has to be redirected.
        $.ajax({
            // add the current path and query to the url for ThemeKey's rule matching
            url: Drupal.settings.basePath.replace(/\/$/, "") + '/index.php?q=themekey/redirect_callback' + window.location.pathname + window.location.search.replace(/^\?/, "&"),
            dataType: 'json',
            type: 'GET',
            success: function(target) {
                if (target) {
                    if (Drupal.settings.ThemeKeyRedirect.redirectOnce) {
                        // Set Domain A state to 2.
                        $.cookie('themekey_redirect_state', 2, { path: '/'});
                    }
                    window.location.href = target;
                    // If the targeted page runs ThemeKey Redirect it sets the
                    // state to 1 or 2.
                }
            }
        });
        if (Drupal.settings.ThemeKeyRedirect.checkOnce) {
            // Set Domain A state to 2.
            $.cookie('themekey_redirect_state', 2, { path: '/'});
        }
    }
    else if (state == 1) {
        // The user has been redirected but is optionally allowed once to switch
        // back manually.
        $('#block-themekey-redirect-domain-selector').show();
        // Set Domain B state to 2.
        $.cookie('themekey_redirect_state', 2, { path: '/'});
    }
    // State 2 indicates that the user has been redirected and no further redirects will happen.
});
