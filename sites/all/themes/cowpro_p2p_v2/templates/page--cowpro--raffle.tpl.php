<?php

/**
 * @file
 * Default theme implementation to display a single Drupal page.
 *
 * Available variables:
 *
 * General utility variables:
 * - $base_path: The base URL path of the Drupal installation. At the very
 *	 least, this will always default to /.
 * - $directory: The directory the template is located in, e.g. modules/system
 *	 or themes/garland.
 * - $is_front: TRUE if the current page is the front page.
 * - $logged_in: TRUE if the user is registered and signed in.
 * - $is_admin: TRUE if the user has permission to access administration pages.
 *
 * Site identity:
 * - $front_page: The URL of the front page. Use this instead of $base_path,
 *	 when linking to the front page. This includes the language domain or
 *	 prefix.
 * - $logo: The path to the logo image, as defined in theme configuration.
 * - $site_name: The name of the site, empty when display has been disabled
 *	 in theme settings.
 * - $site_slogan: The slogan of the site, empty when display has been disabled
 *	 in theme settings.
 *
 * Navigation:
 * - $main_menu (array): An array containing the Main menu links for the
 *	 site, if they have been configured.
 * - $secondary_menu (array): An array containing the Secondary menu links for
 *	 the site, if they have been configured.
 * - $breadcrumb: The breadcrumb trail for the current page.
 *
 * Page content (in order of occurrence in the default page.tpl.php):
 * - $title_prefix (array): An array containing additional output populated by
 *	 modules, intended to be displayed in front of the main title tag that
 *	 appears in the template.
 * - $title: The page title, for use in the actual HTML content.
 * - $title_suffix (array): An array containing additional output populated by
 *	 modules, intended to be displayed after the main title tag that appears in
 *	 the template.
 * - $messages: HTML for status and error messages. Should be displayed
 *	 prominently.
 * - $tabs (array): Tabs linking to any sub-pages beneath the current page
 *	 (e.g., the view and edit tabs when displaying a node).
 * - $action_links (array): Actions local to the page, such as 'Add menu' on the
 *	 menu administration interface.
 * - $feed_icons: A string of all feed icons for the current page.
 * - $node: The node object, if there is an automatically-loaded node
 *	 associated with the page, and the node ID is the second argument
 *	 in the page's path (e.g. node/12345 and node/12345/revisions, but not
 *	 comment/reply/12345).
 *
 * Regions:
 * - $page['help']: Dynamic help text, mostly for admin pages.
 * - $page['highlighted']: Items for the highlighted content region.
 * - $page['content_top']: Items for the header region.
 * - $page['content']: The main content of the current page.
 * - $page['content_bottom']: Items for the header region.
 * - $page['sidebar_first']: Items for the first sidebar.
 * - $page['sidebar_second']: Items for the second sidebar.
 * - $page['header']: Items for the header region.
 * - $page['footer']: Items for the footer region.
 *
 * @see template_preprocess()
 * @see template_preprocess_page()
 * @see template_process()
 */
?>

<meta name="viewport" content="width=device-width, initial-scale=1, maximum-scale=1, user-scalable=no">
<style type="text/css">
#body{width:100%;margin:0 auto;position:relative;margin:0px;padding:0px;}
.wx-main-3{clear:both;width:100%;margin:0rem auto 0;height:24rem;background-color:#99ce5a;position:relative;}
.wx-main-3 #lottery{position:absolute;width:100%;margin:0rem auto 0;text-align:center;position:relative;z-index:80;background:url(<?php echo $GLOBALS['base_url'] . '/' . drupal_get_path('module', 'cowpro_raffle') . '/images/wx_bg.jpg'; ?>) no-repeat top center;background-size:100% 100%;height:95vw;padding-top:7vw}
.wx-main-3 #lottery table{width:84%;margin:0rem auto 0;}
tr,td{padding: 0em!important;}
.wx-main-3 #lottery table td {width:22%;text-align:center;vertical-align:middle;color:#333;font-index:-999}
.wx-main-3 #lottery table td img{ width:100%;}
.wx-main-3 #lottery table td a{width:40%;margin-top:6px;display:block;text-decoration:none;}
.wx-main-3 #lottery table td.active{background-color:#ea0000;}
.sep{display:none;}
.page-cowpro-zongzi #alertFram{top: 50%!important; }
</style>
<?php if ( !theme_get_setting( 'cowpro_p2p_breadcrumb_show' ) ) :
	$breadcrumb = NULL;
endif; ?>

<?php if ( $main_menu ) : ?>
	<a href="#main-menu" class="element-invisible element-focusable"><?php print t( 'Skip to navigation' ); ?></a>
<?php endif; ?>
<a href="#content" class="element-invisible element-focusable"><?php print t( 'Skip to main content' ); ?></a>


<div id="page-wrapper" class="page-wrapper">
	<div id="page" class="page">

		<!-- 顶部菜单
		======================================================================================= -->

		<div class="main-bar-wrapper">
			<div class="<?php if ( theme_get_setting( 'cowpro_p2p_sticky_menu' ) ) { echo 'stickup '; } ?>header-section-2"> <!-- Sticky menu wrapper -->
				<div class="container-12">

					<div class="grid-3">
						<a href="<?php echo base_path()?>"><img class="logo" src="<?php echo base_path() . path_to_theme(); ?>/logo.png"/></a>
					</div>

					<div class="grid-9">
						<!-- Region Menu -->
						<?php if ( $page['menu'] ) :
							print render( $page['menu'] );
						endif; ?>
					</div>
				</div>
			</div>
		</div>

		<!-- Header
		======================================================================================= -->
		<header id="header" class="header page-header clearfix" role="banner">
			<!-- Region Header Top -->
			<?php if ( $page['header_top'] ) : ?>
				<div class="container-12">
					<div class="grid-12">
						<?php print render( $page['header_top'] ); ?>
					</div>
				</div>
			<?php endif; ?>

			<!-- Region Header -->
			<?php if ( $page['header'] ) :
				cowpro_p2p_v2_region_preffix ( 'header' );
					print render( $page['header'] );
				cowpro_p2p_v2_region_suffix ( 'header' );
			endif; ?>

			<!-- Region Header bottom -->
			<?php if ( $page['header_bottom'] ) :
				cowpro_p2p_v2_region_preffix ( 'header_bottom' );
					print render( $page['header_bottom'] );
				cowpro_p2p_v2_region_suffix ( 'header_bottom' );
			endif; ?>
		</header>

		<!-- Content
		======================================================================================= -->
		<div id="main-wrapper" class="main-wrapper" role="main">
			<!-- Region content top -->
			<?php if ( $page['content_top'] ) :
				cowpro_p2p_v2_region_preffix ( 'content_top' );
					print render( $page['content_top'] );
				cowpro_p2p_v2_region_suffix ( 'content_top' );
			endif; ?>

			<div class="container-12">
				<div class="grid-12">
					<div id="main" class="main clearfix">
						<?php if ( $page['sidebar_first'] ) : ?>
							<!-- Left sidebar -->
							<aside id="sidebar-first" class="sidebar-first sidebar grid-2 alpha" role="complementary">
								<?php print render( $page['sidebar_first'] ); ?>
							</aside>
						<?php endif; ?>

						<!-- Page content -->
						<div id="content" class="content content-main <?php if ( ( $page['sidebar_first'] ) && ( $page['sidebar_second'] ) ) : print 'grid-2'; elseif ( $page['sidebar_first'] ) : print 'grid-10 omega'; elseif ( $page['sidebar_second'] ) : print 'grid-10 alpha'; endif; ?>">
							<?php if ( $page['highlighted'] || $breadcrumb || ( $title && !$is_front ) || $tabs['#primary'] || $action_links || $page['help'] || $messages ) : ?>
								<header id="content-header" class="content-header">
									<?php if ( $messages ) : ?>
										<!-- System messages -->
										<div id="messages" class="messages-wrapper clearfix">
											<?php print $messages; ?>
										</div>
									<?php endif; ?>

									<?php if ( $page['highlighted'] ) : ?>
										<!-- Highlighted -->
										<div id="highlighted" class="highlighted"><?php print render( $page['highlighted'] ); ?></div>
									<?php endif; ?>

									<?php if ( $breadcrumb ) : ?>
										<!-- Breadcrumbs -->
										<div id="breadcrumb" class="breadcrumb clearfix"><?php print $breadcrumb; ?></div>
									<?php endif; ?>

									<?php if ( $title && !$is_front ) :
										print render( $title_prefix ); ?>
											<!-- Page title -->
											<h2 id="page-title" class="title page-title" ><?php print $title; ?></h2>
										<?php print render( $title_suffix );
									endif; ?>

									<?php if ( $page['help'] ): ?>
										<!-- System help block -->
										<?php print render( $page['help'] );
									endif; ?>

									<?php if ( !empty( $tabs['#primary'] ) ) : ?>
										<!-- Tabs links -->
										<div class="tabs"><?php print render( $tabs ); ?></div>
									<?php endif; ?>

									<?php if ( $action_links ) : ?>
										<!-- Action links -->
										<ul class="action-links">
											<?php print render( $action_links ); ?>
										</ul>
									<?php endif; ?>
								</header>
							<?php endif; ?>

							<!-- Page content -->
    <div class="wx-main-3">
        <div id="lottery">
        <table border="0" cellpadding="0" cellspacing="0">
          <tr>
            <td class="lottery-unit lottery-unit-0"><img src="<?php echo $GLOBALS['base_url'] . '/' . drupal_get_path('module', 'cowpro_raffle') . '/images/1.png'; ?>"></td>
            <td class="lottery-unit lottery-unit-1"><img src="<?php echo $GLOBALS['base_url'] . '/' . drupal_get_path('module', 'cowpro_raffle') . '/images/2.png'; ?>"></td>
            <td class="lottery-unit lottery-unit-2"><img src="<?php echo $GLOBALS['base_url'] . '/' . drupal_get_path('module', 'cowpro_raffle') . '/images/8.png'; ?>"></td>
            <td class="lottery-unit lottery-unit-3"><img src="<?php echo $GLOBALS['base_url'] . '/' . drupal_get_path('module', 'cowpro_raffle') . '/images/3.png'; ?>"></td>
          </tr>
          <tr>
            <td class="lottery-unit lottery-unit-11"><img src="<?php echo $GLOBALS['base_url'] . '/' . drupal_get_path('module', 'cowpro_raffle') . '/images/8.png'; ?>"></td>
            <td colspan="2" rowspan="2" id="weixin_cj"><a href="javascript:void(0);"></a></td>
            <td class="lottery-unit lottery-unit-4"><img src="<?php echo $GLOBALS['base_url'] . '/' . drupal_get_path('module', 'cowpro_raffle') . '/images/4.png'; ?>"></td>
          </tr>
          <tr>
            <td class="lottery-unit lottery-unit-10"><img src="<?php echo $GLOBALS['base_url'] . '/' . drupal_get_path('module', 'cowpro_raffle') . '/images/4.png'; ?>"></td>
            <td class="lottery-unit lottery-unit-5"><img src="<?php echo $GLOBALS['base_url'] . '/' . drupal_get_path('module', 'cowpro_raffle') . '/images/8.png'; ?>"></td>
          </tr>
          <tr>
            <td class="lottery-unit lottery-unit-9"><img src="<?php echo $GLOBALS['base_url'] . '/' . drupal_get_path('module', 'cowpro_raffle') . '/images/7.png'; ?>"></td>
            <td class="lottery-unit lottery-unit-8"><img src="<?php echo $GLOBALS['base_url'] . '/' . drupal_get_path('module', 'cowpro_raffle') . '/images/8.png'; ?>"></td>
            <td class="lottery-unit lottery-unit-7"><img src="<?php echo $GLOBALS['base_url'] . '/' . drupal_get_path('module', 'cowpro_raffle') . '/images/6.png'; ?>"></td>
            <td class="lottery-unit lottery-unit-6"><img src="<?php echo $GLOBALS['base_url'] . '/' . drupal_get_path('module', 'cowpro_raffle') . '/images/5.png'; ?>"></td>
          </tr>
        </table>
        </div>
    </div>
						</div>

						<?php if ( $page['sidebar_second'] ) : ?>
							<!-- Right sidebar -->
							<aside id="sidebar-second" class="sidebar-second sidebar grid-2 omega" role="complementary">
								<div class="section">
									<?php print render( $page['sidebar_second'] ); ?>
								</div>
							</aside>
						<?php endif; ?>
					</div>
				</div>
			</div>

			<!-- Region Content bottom -->
			<?php if ( $page['content_bottom'] ) :
				cowpro_p2p_v2_region_preffix ( 'content_bottom' );
					print render( $page['content_bottom'] );
				cowpro_p2p_v2_region_suffix ( 'content_bottom' );
			endif; ?>

			<!-- Region Prefooter -->
			<?php if ( $page['prefooter'] ) :
				cowpro_p2p_v2_region_preffix ( 'prefooter' );
					print render( $page['prefooter'] );
				cowpro_p2p_v2_region_suffix ( 'prefooter' );
			endif; ?>
		</div>

		<!-- Footer
		======================================================================================= -->
		<footer id="footer" class="footer page-footer" role="contentinfo">
			<!-- Region Footer top -->
			<?php if ( $page['footer_top'] ) :
				cowpro_p2p_v2_region_preffix ( 'footer_top' );
					print render( $page['footer_top'] );
				cowpro_p2p_v2_region_suffix ( 'footer_top' );
			endif; ?>

			<div id="footer-wrapper" class="footer-wrapper">
				<div class="container-12">
					<div class="grid-12">
						<!-- Region Footer -->
						<?php if ( $page['footer'] ) :
							print render( $page['footer'] );
						endif; ?>

						<?php if ( $is_front ) : ?>
							Powered by 奶牛专家
						<?php endif; ?>
					</div>
				</div>
			</div>
			<!-- Region Footer bottom -->
			<?php if ( $page['footer_bottom'] ) :
				cowpro_p2p_v2_region_preffix ( 'footer_bottom' );
					print render( $page['footer_bottom'] );
				cowpro_p2p_v2_region_suffix ( 'footer_bottom' );
			endif; ?>
		</footer>
	</div>
</div>
  <script type="text/javascript">
    var lottery = {
      index: -1, //当前转动到哪个位置，起点位置
      count: 0, //总共有多少个位置
      timer: 0, //setTimeout的ID，用clearTimeout清除
      speed: 30, //初始转动速度
      times: 0, //转动次数
      cycle: 50, //转动基本次数：即至少需要转动多少次再进入抽奖环节
      prize: -1, //中奖位置
      init: function(id) {
        if (jQuery("#" + id).find(".lottery-unit").length > 0) {
          $lottery = jQuery("#" + id);
          $units = $lottery.find(".lottery-unit");
          this.obj = $lottery;
          this.count = $units.length;
          $lottery.find(".lottery-unit-" + this.index).addClass("active");
        }
      },
      roll: function() {
        var index = this.index;
        var count = this.count;
        var lottery = this.obj;        
        jQuery(lottery).find(".lottery-unit-" + index).removeClass("active");
        index += 1;
        if (index > count-1) {
          index = 0;
        }
        jQuery(lottery).find(".lottery-unit-" + index).addClass("active");
        this.index = index;
        return false;
        },
      stop: function(index) {
          this.prize = index;
          return false;
        }
      };
      function roll() {
        clearTimeout(lottery.timer);
        lottery.times += 1;
        lottery.roll();
        var prize_site = jQuery("#lottery").attr("prize_site");
        if (lottery.times > lottery.cycle + 10 && lottery.index == prize_site) {
          var prize_id = jQuery("#lottery").attr("prize_id");
          var prize_name = jQuery("#lottery").attr("prize_name");
          var points = jQuery("#lottery").attr("points");
          clearTimeout(lottery.timer);
          lottery.prize = 0;
          lottery.times = 0;
          click = false;
          setTimeout(function(){alert("\n抽奖结果："+prize_name)},lottery.timer);
        } else {
          if (lottery.times < lottery.cycle) {
            lottery.speed -= 10;
          } else if (lottery.times == lottery.cycle) {
            var index = Math.random() * (lottery.count) | 0;
            lottery.prize = index;
          } else {
            if (lottery.times > lottery.cycle + 10 && ((lottery.prize == 0 && lottery.index == 7) || lottery.prize == lottery.index + 1)) {
              lottery.speed += 110;
            } else {
              lottery.speed += 20;
            }
          }
          if (lottery.speed < 40) {
            lottery.speed = 40;
          }
          lottery.timer = setTimeout(roll, lottery.speed);
        }
        
        return false;
      }
      var click = false;
      
      jQuery(document).ready(function($) {
        lottery.init('lottery');
        jQuery("#weixin_cj").click(function() {
          if (click) {
            return false;
          } else {
            lottery.speed = 100;
            jQuery.post("/cowpro/raffle_ajax", {uid: 1}, function(data) { //获取奖品，也可以在这里判断是否登陆状态
                console.log(data);
              if( !data.err_msg ) {
                $("#lottery").attr("prize_site", data.prize_site);
                $("#lottery").attr("prize_id", data.prize_id);
                $("#lottery").attr("prize_name", data.prize_name);
                $("#lottery").attr("points", data.points);
                roll();
                click = true;
                return false;
              }else{
                alert(data.err_msg);
              }
            }, "json");
          }
        });
      })
    </script>