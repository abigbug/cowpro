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
          <a href="<?php global $base_url; print $base_url;?>/user" class="btn-red btn-red-user" ><?php echo t('我的金贝增'); ?></a> </div>
        <?php else :?>
        <a href="<?php global $base_url; print $base_url;?>/user/register" class="btn-red">注册</a><a href="<?php global $base_url; print $base_url;?>/user/login" class="btn-red btn-red01">登录</a> </div>

        <?php endif; ?>

  </div>
</header>
 <?php if (!empty($page['banner'])): ?>
  <div id="sopuo-banner" class="clearfix"><?php print render($page['banner']); ?></div>
 <?php endif; ?>
<div class="sopuo-body-warp">
  <div class="container">
    <div class="row">
      <div class="sopuo-contentall-front">


        <a id="main-content"></a>
		<?php print render($title_prefix); ?>
         <?php print render($title_suffix); ?>
		 <?php print $messages; ?>
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

<div class="rt-content js-0 dspn" style="display: block;">
            <div class="rt-content-title">投资流程</div>
            <div class="rt-content-process rel">
                <div class="rt-process-line"></div>
                <ul class="rel">
                    <li>
                        <a href="javascript:;" class="rt-process-logo rt-ral">
                            <span></span>
                            <p>注册</p>
                        </a>
                    </li>
                    <li><span class="rt-arrow"></span></li>
                    <li>
                        <a href="javascript:;" class="rt-process-logo rt-deposit">
                            <span></span>
                            <p>安全设置</p>
                        </a>
                    </li>
                    <li><span class="rt-arrow"></span></li>
                    <li>
                        <a href="javascript:;" class="rt-process-logo rt-choose">
                            <span></span>
                            <p>充值</p>
                        </a>
                    </li>
                    <li><span class="rt-arrow"></span></li>
                    <li>
                        <a href="javascript:;" class="rt-process-logo rt-certify">
                            <span></span>
                            <p>浏览可投项目</p>
                        </a>
                    </li>
                    <li><span class="rt-arrow"></span></li>
                    <li>
                        <a href="javascript:;" class="rt-process-logo rt-invest">
                            <span></span>
                            <p>投资</p>
                        </a>
                    </li>
                    <li><span class="rt-arrow"></span></li>
                    <li>
                        <a href="javascript:;" class="rt-process-logo rt-earn">
                            <span></span>
                            <p>坐收利息</p>
                        </a>
                    </li>
                </ul>
            </div>
            <div class="rt-content-title">常见自助服务</div>
            <div class="rt-content-service">
                <ul>
                    <li>
                        <a target="_blank" href="/index.php?ctl=user&amp;act=getpassword" class="rt-service-logo rt-findLoginPwd">
                            <span></span>
                            <p>找回登录密码</p>
                        </a>
                    </li>
                    <li>
                        <a target="_blank" href="/member.php?ctl=uc_account&amp;act=security" class="rt-service-logo rt-findPayPwd">
                            <span></span>
                            <p>找回支付密码</p>
                        </a>
                    </li>
                    <li>
                        <a target="_blank" href="/member.php?ctl=uc_account&amp;act=security" class="rt-service-logo rt-modifyMail">
                            <span></span>
                            <p>修改邮箱</p>
                        </a>
                    </li>
                    <li>
                        <a target="_blank" href="/member.php?ctl=uc_account&amp;act=security" class="rt-service-logo rt-modifyTel">
                            <span></span>
                            <p>修改手机</p>
                        </a>
                    </li>
                    <li>
                        <a target="_blank" href="/member.php?ctl=uc_account&amp;act=security" class="rt-service-logo rt-modifyLoginPwd">
                            <span></span>
                            <p>修改登录密码</p>
                        </a>
                    </li>
                    <li>
                        <a target="_blank" href="/member.php?ctl=uc_account&amp;act=security" class="rt-service-logo rt-modifyPayPwd">
                            <span></span>
                            <p>修改支付密码</p>
                        </a>
                    </li>
                </ul>
            </div>
        </div>

          <?php print render($page['content']); ?> </div>
    </div>
  </div>
</div>

      <?php print render($page['footer_top']); ?>

<?php if (!empty($page['footer'])): ?>
<footer class="footer-top  bg-black bg-font-dark" id="sopuo-footer">
<?php print render($page['footer']); ?>
</footer>
<?php endif; ?>