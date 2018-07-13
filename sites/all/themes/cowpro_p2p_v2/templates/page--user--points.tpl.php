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
<style>
blockquote,body,button,dd,dl,dt,fieldset,form,h1,h2,h3,h4,h5,h6,input,li,ol,p,td,textarea,th,ul{padding:0;margin:0}
a{text-decoration:none;color:#323232}
ul{list-style:none}
h1,h2,h3,h4,h5,h6{font-weight:400}
table{border-collapse:collapse;border-spacing:0}
input[type=number],input[type=password],input[type=search],input[type=tel],input[type=text],textarea{border:none;outline:none;-webkit-appearance:none}
input[disabled]{background:transparent}input:-webkit-autofill{-webkit-box-shadow:0 0 0 1000px #fff inset}
img{border:none;vertical-align:middle;max-width:100%}
body,html{width:100%;font-size: 50px;}
body{background:#f5f5f5;color:#323232;font-size:.14rem;overflow-scrolling:touch;-webkit-user-select:none;-moz-user-select:none;-ms-user-select:none;user-select:none;-webkit-text-size-adjust:none;-ms-text-size-adjust:none;text-size-adjust:none;font-family:PingFang SC,Microsoft YaHei,Arial}
*{-webkit-tap-highlight-color:transparent;box-sizing:border-box}
input{vertical-align:middle;color:#323232}
.sr-only{position:absolute;width:1px;height:1px;margin:-1px;padding:0;overflow:hidden;clip:rect(0,0,0,0);border:0}.hide{display:none}strong{color:#ff7625;font-weight:400}
.sl-ld .sl-ld-ball:first-of-type{background:#629eff}.sl-ld .sl-ld-ball:nth-of-type(2){background:#238bcb}.scrollload-bottom .no-record{text-align:center;padding:1rem 0}
body{background:#f6f7f8;overflow:auto;-webkit-overflow-scrolling:touch}.flex{display:-webkit-box;display:-ms-flexbox;display:flex}
footer ul li p {
    font-size: 0.28rem;
}
</style>
  <section class="points_banner">
    <div class="all">
      <dl>
        <dt>
          <span class="title">当前积分</span>
          <a class="rule" onclick="javascript:OpenDiv();">积分规则</a>
        </dt>
        <dd>
          <?php 
            global $user;
            $points = userpoints_get_current_points ( $user->uid );
            print $points;
          ?>
        </dd>
      </dl>
    </div>
    <div class="flex links">
      <a class="lott" href="<?php global $base_url; print $base_url;?>/cowpro/raffle"><i></i><span>积分抽奖</span></a>
      <a class="coin" href="<?php global $base_url; print $base_url;?>/issuing-list"><i></i><span>去赚积分</span></a>
      <a class="shop" href="<?php global $base_url; print $base_url;?>/shop"><i></i><span>积分商城</span></a>
    </div>
  </section>
  <section class="recomend">
    <div class="reco-inner">
      <div class="title">推荐</div>
      <div class="cont">
        <div class="left">
          <p><strong><!-- react-text: 61 -->750<!-- /react-text --><!-- react-text: 62 -->积分<!-- /react-text --></strong></p>
          <p class="commodityName">50元现金券</p>
          <a class="btn" href="<?php global $base_url; print $base_url;?>/shop/detail/108">前往兑换</a>
        </div>
        <div class="rig" style="background-image: url(<?php echo $GLOBALS['base_url'] . '/' . drupal_get_path('theme', 'cowpro_p2p_v2') . '/images/1525691828648.png'; ?>);"></div>
      </div>
    </div>
  </section>
  <section class="list lock-scroll">
    <div>
      <?php print render($page['content']['system_main']); ?>
    </div>
  </section>
<div class="popBoxWraper" id="popBox2" style="display:none;"> <div class="popBoxBg"> <div class="popBoxContent"> <h1>规则说明</h1> <p></p><ul>
<li class="title"> 【什么是积分】</li>
<li>积分是金贝增平台给予投资用户的额外奖励，用户可以使用积分进行抽奖或兑换商城商品。</li>
<li class="title"> 【获取积分】</li>
<li>可通过投资获取积分。</li>
<li class="title"> 【积分使用】</li>
<li>可在积分抽奖栏目抽奖，每次抽奖消耗15积分。</li>
<li class="title"> 【积分有效期】</li>
<li>积分长期有效</li>
<li class="title"> 【作弊处理】</li>
<li>系统会对有作弊行为的用户做如下处理：</li>
<li>第1次发现作弊行为: 积分将回到原始点，用户列入重点监控名单；</li>
<li>第2次发现作弊行为: 将禁止用户继续领取积分，积分永远处于原始点的位置</li>
</ul><p></p> <div class="popBoxButtons"> <a class="popBoxCancel">取消</a> <a class="popBoxSure" href="javascript:CloseDiv();">我知道了</a> </div> </div> </div> </div>

<div id="page-wrapper" class="page-wrapper">
  <div id="page" class="page">

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
<script>
  function OpenDiv(){
    document.getElementById("popBox2").style.display="block";
  }
  function CloseDiv(){
    document.getElementById("popBox2").style.display="none";
  }
</script>