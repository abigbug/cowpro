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
        <a href="<?php global $base_url; print $base_url;?>/user" class="btn-red btn-red-user"><?php echo t('我的金贝增'); ?></a> </div>
      <?php else :?>
      <a href="<?php global $base_url; print $base_url;?>/user/register" class="btn-red">注册</a><a href="<?php global $base_url; print $base_url;?>/user/login" class="btn-red btn-red01">登录</a> </div>
    <?php endif; ?>
  </div>
</header>
<?php if (!empty($page['banner'])): ?>
<div id="sopuo-banner" class="clearfix"><?php print render($page['banner']); ?></div>
<?php endif; ?>
<div class="sopuo-body-warp ">
  <div class="container">
    <div class="row">
      <section  class="col-sm-9 col-xs-12" id="sopuo-mainbody">
        <?php if (!empty($title)): ?>
        <h1 class="page-header text-center"><?php print $title; ?></h1>
        <?php endif; ?>
        <?php print render($title_suffix); ?> <?php print $messages; ?>
        <?php if (!empty($tabs)): ?>
        <?php print render($tabs); ?>
        <?php endif; ?>
        <?php if (!empty($page['help'])): ?>
        <?php print render($page['help']); ?>
        <?php endif; ?>
        <?php if (!empty($action_links)): ?>
        <ul class="action-links">
          <?php print render($action_links); ?>
        </ul>
        <?php endif; ?>
        <?php print render($page['content']); ?> </section>
    </div>
  </div>
</div>
<?php if (!empty($page['footer'])): ?>
<footer class="footer-top  bg-black bg-font-dark" id="sopuo-footer"> <?php print render($page['footer']); ?> </footer>
<?php endif; ?>
