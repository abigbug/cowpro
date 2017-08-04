<?php
/**
 * @file
 * Default theme implementation to display the basic html structure of a single
 * Drupal page.
 *
 * Variables:
 * - $css: An array of CSS files for the current page.
 * - $language: (object) The language the site is being displayed in.
 *   $language->language contains its textual representation.
 *   $language->dir contains the language direction. It will either be 'ltr' or 'rtl'.
 * - $rdf_namespaces: All the RDF namespace prefixes used in the HTML document.
 * - $grddl_profile: A GRDDL profile allowing agents to extract the RDF data.
 * - $head_title: A modified version of the page title, for use in the TITLE tag.
 * - $head: Markup for the HEAD section (including meta tags, keyword tags, and
 *   so on).
 * - $styles: Style tags necessary to import all CSS files for the page.
 * - $scripts: Script tags necessary to load the JavaScript files and settings
 *   for the page.
 * - $page_top: Initial markup from any modules that have altered the
 *   page. This variable should always be output first, before all other dynamic
 *   content.
 * - $page: The rendered page content.
 * - $page_bottom: Final closing markup from any modules that have altered the
 *   page. This variable should always be output last, after all other dynamic
 *   content.
 * - $classes String of classes that can be used to style contextually through
 *   CSS.
 *
 * @see template_preprocess()
 * @see template_preprocess_html()
 * @see template_process()
 */
$html_attributes = "lang=\"{$language->language}\" dir=\"{$language->dir}\" {$rdf_namespaces}";

 ?>

<!--[if IE 9 ]><html <?php print $html_attributes; ?> class="no-js ie ie9"><![endif]-->
<!--[if (gt IE 9)|!(IE)]><!--><html <?php print $html_attributes; ?> class="no-js"><!--<![endif]--><head<?php print $grddl_profile; ?>>
	<?php print $head; ?>

	<!--[if lte IE 8]>
		<div style=' text-align:center; clear: both; padding:0 0 0 15px; position: relative;'>
			<a href="//windows.microsoft.com/en-US/internet-explorer/products/ie/home?ocid=ie6_countdown_bannercode">
				<img src="//storage.ie6countdown.com/assets/100/images/banners/warning_bar_0000_us.jpg" border="0" height="42" width="820" alt="You are using an outdated browser. For a faster, safer browsing experience, upgrade for free today.">
			</a>
		</div>
	<![endif]-->

	<title><?php print $head_title; ?></title>

	<?php print $styles;
	print $scripts; ?>

	<!--[if IE 9]>
		<script src="<?php echo base_path().path_to_theme() ?>/js/jquery.placeholder.min.js"></script>
		<script>
			jQuery(document).ready(function() {
				jQuery('input, textarea').placeholder();
			})
		</script>
	<![endif]-->

	<script>
		if (jQuery.cookie('the_cookie') != 0) {
			document.write('<meta name="viewport" content="width=device-width, initial-scale=1, maximum-scale=1.0, user-scalable=no">')
		} else {
			document.write('<meta name="viewport" content="width=device-width">')
		}
	</script>

	<link rel="stylesheet" href="<?php echo base_path().path_to_theme() ?>/css/style-mobile.css" media="screen" id="style-mobile">
	<link rel="stylesheet" href="<?php echo base_path().path_to_theme() ?>/css/style-sopuopc.css" media="screen" id="style-sopuopc">
	<link rel="stylesheet" href="<?php echo base_path().path_to_theme() ?>/css/skeleton-mobile.css" media="screen" id="skeleton-mobile">
</head>
<body id="body" class="<?php print $classes; ?>" <?php print $attributes;?>>
	<?php print $page_top;
	print $page;
	print $page_bottom; ?>

</body>
</html>