<?php print format_plural(count($links_rendered), 'You can manually switch back to this page:', 'You can manually switch back to one of these pages:'); ?>
<ul>
<?php foreach ($links_rendered as $link) { ?>
  <li><?php print $link;?></li>
<?php } ?>
</ul>