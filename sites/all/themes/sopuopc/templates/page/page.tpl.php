<?php if (!empty($page['banner'])): ?>
<div id="sopuo-banner" class="clearfix"><?php print render($page['banner']); ?></div>
<?php endif; ?>
<div class="sopuo-body-warp ">
  <div class="container">
    <div class="row">

      <aside class="col-sm-3 col-xs-12" id="sopuo-rightcontent">
<?php
$block = block_load('system', 'navigation');
$output = @drupal_render(_block_get_renderable_array(_block_render_blocks(array($block))));
print $output;
?>
</aside>

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
