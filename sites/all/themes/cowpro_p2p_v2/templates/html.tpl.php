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
	<link rel="stylesheet" href="<?php echo base_path().path_to_theme() ?>/css/skeleton-mobile.css" media="screen" id="skeleton-mobile">
</head>
<body id="body" class="<?php print $classes; ?>" <?php print $attributes;?>>
	<?php print $page_top;
	print $page;
	print $page_bottom; ?>
	<!-- 在线客服begin -->
<div id="online_qq_layer">
  <div id="online_qq_tab">
    <div class="online_icon"> <a href="javascript:void(0);"></a> </div>
  </div>
  <div id="onlineService">
    <div class="online_windows overz">
      <div class="online_w_top"> </div>
      <!--online_w_top end-->
      <div class="online_w_c overz">
        <div class="online_bar collapse" id="onlineSort1">
          <h2> <a href="javascript:;">在线客服</a> </h2>
          <div class="online_content overz" id="onlineType1" style="display: block;">
            <ul class="overz">
              <li><a target="_blank" href="http://wpa.qq.com/msgrd?v=3&uin=2871381708&site=qq&menu=yes"><img border="0" src="http://wpa.qq.com/pa?p=2:2871381708:51" alt="点击这里给我发消息" title="点击这里给我发消息"/></a></li>
              <li><a target="_blank" href="http://wpa.qq.com/msgrd?v=3&uin=1130578102&site=qq&menu=yes"><img border="0" src="http://wpa.qq.com/pa?p=2:1130578102:41" alt="点击这里给我发消息" title="点击这里给我发消息"/></a></li>
              <li><a target="_blank" href="http://wpa.qq.com/msgrd?v=3&uin=3319119499&site=qq&menu=yes"><img border="0" src="http://wpa.qq.com/pa?p=2:3319119499:41" alt="点击这里给我发消息" title="点击这里给我发消息"/></a></li>
              <li>电话:400-961-0710</li>
            </ul>
          </div>
          <!--online_content end-->
        </div>
        <!--online_bar end
        <div class="online_bar collapse" id="onlineSort2">
          <h2> <a href="javascript:;">加盟合作咨询</a> </h2>
          <div class="online_content overz" id="onlineType2" style="display: block;">
            <ul class="overz">
              <li><a target="_blank" href="http://wpa.qq.com/msgrd?v=3&uin=0000000000&site=qq&menu=yes"><img border="0" src="http://wpa.qq.com/pa?p=2:12345678:51" /></a> </li>
              <li>电话：13600000000</li>
            </ul>
          </div>
        </div>
        online_bar end-->
        <div class="online_bar collapse" id="onlineSort3">
          <h2> <a href="javascript:;">扫一扫，关注微信</a> </h2>
          <div class="online_content overz" id="onlineType3" style="display: block;"> <img src="<?php echo base_path().path_to_theme() ?>/images/wx.jpg" style="display: block;margin: 0 auto 5px;width: 90px"> </div>
        </div>
        <!--online_bar end-->
      </div>
      <!--online_w_c end-->
      <div class="online_w_bottom"> </div>
      <!--online_w_bottom end-->
    </div>
    <!--online_windows end-->
  </div>
</div>
<script type="text/javascript">
jQuery(function(){
	jQuery('#online_qq_layer').hover(function(){
		jQuery(this).stop().animate({right:'0'});
	},function(){
		jQuery(this).stop().animate({right:'-140px'});
	});
});
</script>
<!-- 在线客服end -->

</body>
</html>