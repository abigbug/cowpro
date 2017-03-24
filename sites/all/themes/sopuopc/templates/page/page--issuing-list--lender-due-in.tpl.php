<div class="sopuo-header-top clearfix">
  <div class="container">
    <div class="row">
      <?php if (!empty($page['header_top'])): ?>
      <?php print render($page['header_top']); ?>
      <?php endif; ?>
    </div>
  </div>
</div>
<header class="sopuo-header clearfix ">
  <div class="container">
    <div class="row">
      <div class="col-md-4 sopuo-logo"> <a class="logo navbar-btn" href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>"> <img src="<?php print $logo; ?>" alt="<?php print t('Home'); ?>" /> </a> </div>
      <div class="col-md-6 sopuo-mainnav"> <?php print render($page['navigation']); ?> </div>
      <div class="col-md-2 pull-right sopuo-header-right text-right">
        <?php

	global $user;
	//$username = $user->name;

if ( $user->uid ) :
	?>
        <a href="/user" class="btn-red btn-red-user"><?php echo t('我的金贝增'); ?></a> </div>
      <?php else :?>
      <a href="/user/register" class="btn-red">注册</a><a href="/user/login" class="btn-red btn-red01">登录</a> </div>
    <?php endif; ?>
  </div>
</header>
<?php if (!empty($page['banner'])): ?>
<div id="sopuo-banner" class="clearfix"><?php print render($page['banner']); ?></div>
<?php endif; ?>
<div class="sopuo-body-warp ">
  <div class="clearfix sopuo-title-bg">
    <?php print render($title_suffix); ?> </div>
  <section  class="container" id="sopuo-mainbody">
    <div class="row">
      <div class="col-md-2 " id="frame_left">

<?php
$block = block_load('system', 'navigation');
$output = @drupal_render(_block_get_renderable_array(_block_render_blocks(array($block))));
print $output;
?>
<?php
$block = block_load('block', '5');
$output = @drupal_render(_block_get_renderable_array(_block_render_blocks(array($block))));
print $output;
?>
      </div>
      <div class="col-md-10" id="frame_content"> <?php print $messages; ?>
        <?php if (!empty($page['help'])): ?>
        <?php print render($page['help']); ?>
        <?php endif; ?>
        <?php if (!empty($action_links)): ?>
        <ul class="action-links">
          <?php print render($action_links); ?>
        </ul>
        <?php endif; ?>
        <?php print render($page['content']); ?> </div>
    </div>
  </section>
</div>
<?php if (!empty($page['footer'])): ?>
<footer class="footer-top  bg-black bg-font-dark" id="sopuo-footer"> <?php print render($page['footer']); ?> </footer>
<?php endif; ?>
