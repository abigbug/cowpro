jQuery(window).bind('load', function() {
	jQuery('.foreground').toggle('slow');
});

(function($) {
	jQuery(window).load(function($) {
		if (jQuery(".portfolio-grid").length) {
			function getNumColumns() {
				var $folioWrapper = jQuery('#isotope-container').data('cols');

				if ($folioWrapper == '1col') {
					var winWidth = jQuery("#isotope-container").width(),
						column = 1;
					return column;
				}

				else if ($folioWrapper == '2cols') {
					var winWidth = jQuery("#isotope-container").width(),
						column = 2;
					if (winWidth < 380) {
						column = 1;
					}
					return column;
				}

				else if ($folioWrapper == '3cols') {
					var winWidth = jQuery("#isotope-container").width(),
						column = 3;
					if (winWidth < 380) {
						column = 1;
					}
					else if ((winWidth >= 380) && (winWidth < 788)) {
						column = 2;
					}
					else if (winWidth >= 788) {
						column = 3;
					}
					return column;
				}

				else if ($folioWrapper == '4cols') {
					var winWidth = jQuery("#isotope-container").width(),
						column = 4;
					if (winWidth < 380) {
						column = 1;
					}
					else if ((winWidth >= 380) && (winWidth < 788)) {
						column = 2;
					}
					else if ((winWidth >= 788) && (winWidth < 940)) {
						column = 3;
					}
					else if (winWidth >= 940) {
						column = 4;
					}
					return column;
				}
			}

			function setColumnWidth() {
				var columns = getNumColumns(),
					containerWidth = jQuery("#isotope-container").width(),
					postWidth;

				if (columns == 1) {
					postWidth = containerWidth - 30;
				}
				if (columns == 2) {
					postWidth = (containerWidth - 60)/columns;
				}
				if (columns == 3) {
					postWidth = (containerWidth - 90)/columns;
				}
				if (columns == 4) {
					postWidth = (containerWidth - 120)/columns;
				}

				postWidth = Math.floor(postWidth);

				jQuery(".isotope-element").each(function(index) {
					jQuery(this).css({"width" : postWidth + "px"});
				});
			}
			
			var $container = jQuery('#isotope-container'),
				filters = {},
				items_count = jQuery(".isotope-element").size();

			setColumnWidth();
			$container.isotope({
				itemSelector		: '.isotope-element',
				layoutMode			: 'fitRows',
			});

			jQuery(window).on("debouncedresize", function(event) {
				setColumnWidth();
				$container.isotope()
			});
		};

		if (jQuery.cookie('the_cookie') == 0) {
			styleSwitch(0)
		}

		function styleSwitch(cookie) {
			if (cookie == 0) {
				jQuery('#style-mobile').remove();
				jQuery('#skeleton-mobile').remove();
				jQuery('.switcher').text("Responsive Version");
				jQuery.cookie('the_cookie', 0);
			} else {
				jQuery('head').append('<link rel="stylesheet" href="<?php echo base_path().path_to_theme() ?>/css/style-mobile.css" media="screen" id="style-mobile">');
				jQuery('head').append('<link rel="stylesheet" href="<?php echo base_path().path_to_theme() ?>/css/skeleton-mobile.css" media="screen" id="skeleton-mobile">');
				jQuery('.switcher').text("Desktop Version only");
				jQuery.cookie('the_cookie', 1);
			}
		}

		jQuery('.switcher').click(function() {
			styleSwitch(jQuery.cookie('the_cookie') == 0 ? 1 : 0);
			location.reload();
		});
	});
})(jQuery);

jQuery(document).ready(function () {
	jQuery("#isotope-options .option-set li a[data-option-value='.all']").addClass("selected");
	
	// Sticky menu
	if ((jQuery(window).width() > 995) && (jQuery('#header .stickup').length)) {
		jQuery('#header .stickup').tmStickUp({});
	}
	
	// Contact form validation
	var my_form_id = new tFormer('contact-site-form', {
		fields: {
			name: {
				rules: "*"
			},
			mail: {
				rules: "* @"
			},
			subject: {
				rules: "*"
			},
			message: {
				rules: "*"
			}
		}
	});
	
	// Contact form tooltips
	jQuery(".contact-form .form-item-name").append('<div class="error-message">This field is required!</div>');
	jQuery(".contact-form .form-item-mail").append('<div class="error-message">Please enter a valid email address!</div>');
	jQuery(".contact-form .form-item-subject").append('<div class="error-message">This field is required!</div>');
	jQuery(".contact-form .form-item-message .form-textarea-wrapper").append('<div class="error-message">This field is required!</div>');
	
	jQuery(".contact-form input[type='reset']").on("click", function($) {
		jQuery(this).parents(".contact-form").find(".error").removeClass("error");
	})
	
	/* Search (Toggle) */
	jQuery(".dd-search.block-search-form").append('<span class="search-button"><i class="fa fa-search"></i></span>');
	jQuery('span.search-button').click(function(){
		jQuery('.block-content').toggleClass('active');
	});
	jQuery(document).on('click', function  () {
		if (jQuery('#block-search-form .block-content').hasClass('active')) {
			jQuery(this).removeClass('active');
		}
	})
	jQuery('#block-search-form .block-content, span.search-button').on('click touchstart', function(e){
		e.stopPropagation();
	});
	
	jQuery(".views-field-nothing .expand-trigger").click(function(event) {
		event.preventDefault();
		jQuery(this).parent().find(".views-field-body").toggle(400);
		jQuery(this).toggleClass("active");
		jQuery(this).parent().toggleClass("expanded");
	});
});

// Back to Top Button
jQuery(window).load(function() {
	jQuery().UItoTop({
		easingType: 'easeOutQuart',
		containerID: 'backtotop'
	});
})

// Mobile menu
jQuery(window).load(function() {
	jQuery('#superfish-1').mobileMenu();
})