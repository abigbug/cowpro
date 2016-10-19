<?php
/**
 * @file
 * Implementation to display a single Drupal page while offline.
 *
 * All the available variables are mirrored in page.tpl.php.
 *
 * @see template_preprocess()
 * @see template_preprocess_maintenance_page()
 * @see cowpro_p2p_process_maintenance_page()
 */
$html_attributes = "lang=\"{$language->language}\" dir=\"{$language->dir}\" {$rdf->version}{$rdf->namespaces}";

print $doctype; ?>

<!--[if IE 8 ]><html <?php print $html_attributes; ?> class="no-js ie ie8 lt-ie9"><![endif]-->
<!--[if IE 9 ]><html <?php print $html_attributes; ?> class="no-js ie ie9"><![endif]-->
<!--[if (gt IE 9)|!(IE)]><!--><html <?php print $html_attributes; ?> class="no-js"><!--<![endif]-->
<head<?php print $rdf->profile; ?>>
	<?php print $head; ?>

	<!--[if lte IE 7]>
		<div style=' text-align:center; clear: both; padding:0 0 0 15px; position: relative;'>
			<a href="//windows.microsoft.com/en-US/internet-explorer/products/ie/home?ocid=ie6_countdown_bannercode">
				<img src="//storage.ie6countdown.com/assets/100/images/banners/warning_bar_0000_us.jpg" border="0" height="42" width="820" alt="You are using an outdated browser. For a faster, safer browsing experience, upgrade for free today.">
			</a>
		</div>
	<![endif]-->

	<title><?php print $head_title; ?></title>

	<?php print $styles;
	print $scripts;?>

	<!--[if LT IE 9]>
		<script src="//html5shim.googlecode.com/svn/trunk/html5.js"></script>
	<![endif]-->

	<script>
		if (jQuery.cookie('the_cookie') != 0) {
			document.write('<meta name="viewport" content="width=device-width, initial-scale=1, maximum-scale=1.0, user-scalable=no">')
		} else {
			document.write('<meta name="viewport" content="width=device-width">')
		}
	</script>
</head>
<body class="<?php print $classes; ?>" <?php print $attributes;?>>
	<div id="skip-link">
		<a href="#main-content" class="element-invisible element-focusable"><?php print t( 'Skip to main content' ); ?></a>
	</div>

	<?php print $page_top; ?>

	<div id="page-wrapper">
		<div id="page">
			<!-- Header
			======================================================================================= -->
			<header id="header" role="banner">
				<div class="section clearfix">
					<!-- Logo -->
					<?php if ( $logo || $site_name || $site_slogan ) :?>
						<div id="logo" class="logo">
							<?php if ( $logo ) : // logo image ?>
								<a href="<?php print $front_page; ?>" title="<?php print t( 'Home' ); ?>" rel="home" id="img-logo" class="img-logo">
									<img src="<?php print $logo; ?>" alt="<?php print t( 'Home' ); ?>">
								</a>
							<?php endif;

							if ( $site_name ) : // site name ?>
								<h1 title="<?php print $site_name; ?>" id="site-name" class="site-name">
									<a href="<?php print $front_page; ?>" title="<?php print $site_name; ?>"><?php print $site_name; ?></a>
								</h1>
							<?php endif;

							if ( $site_slogan ) : // site slogan ?>
								<div title="<?php print $site_slogan; ?>" id="slogan" class="slogan">
									<?php print $site_slogan; ?>
								</div>
							<?php endif; ?>
						</div>
					<?php endif; ?>
				</div>
			</header>

			<!-- Content
			======================================================================================= -->
			<div id="main-wrapper">
				<div id="main" class="main clearfix">
					<div id="content" class="content page-content content-main column" role="main">
						<div class="section">
							<a id="main-content"></a>
							<!-- Page title -->
							<?php if ( $title ) : ?>
								<h1 class="title page-title" id="page-title"><?php print $title; ?></h1>
							<?php endif;?>

							<!-- Page content -->
							<div id="highlighted" class="highlighted">
								<?php print $content; ?>
							</div>

							<!-- System messages -->
							<?php if ( $messages ) : ?>
								<div id="messages">
									<div class="section clearfix">
										<?php print $messages; ?>
									</div>
								</div>
							<?php endif; ?>
						</div>
					</div>
				</div>
			</div>
		</div>
	</div>

	<?php print $page_bottom; ?>
</body>
</html>