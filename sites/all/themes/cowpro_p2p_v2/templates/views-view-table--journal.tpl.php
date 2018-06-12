<?php

/**
 * @file
 * Template to display a view as a table.
 *
 * - $title : The title of this group of rows.  May be empty.
 * - $header: An array of header labels keyed by field id.
 * - $caption: The caption for this table. May be empty.
 * - $header_classes: An array of header classes keyed by field id.
 * - $fields: An array of CSS IDs to use for each field id.
 * - $classes: A class or classes to apply to the table, based on settings.
 * - $row_classes: An array of classes to apply to each row, indexed by row
 *   number. This matches the index in $rows.
 * - $rows: An array of row items. Each row is an array of content.
 *   $rows are keyed by row number, fields within rows are keyed by field ID.
 * - $field_classes: An array of classes to apply to each field, indexed by
 *   field id, then row number. This matches the index in $rows.
 * @ingroup views_templates
 */
?>
<div class="journal_con">
  <?php foreach ($rows as $row_count => $row): ?>
  <ul class="list-text">
    <li>
    <?php foreach ($row as $field => $content): ?>
      <?php if ($field=='type'){?>
      <span><p><?php print $content; ?></p></span>
      <?php }?>
      <?php if ($field=='status'){?>
      <span><?php if ($content=="成功"){?><font color="#999999">状态：</font><?php print $content; ?><?php }else{ ?><p class="green"><font color="#999999">状态：</font><?php print $content; ?></p><?php }?></span>
      <?php }?>
      <?php if ($field=='amount'){?>
      <span><p class="day"><em><?php print $content; ?></em></p></span>
      <?php }?>
      <?php if ($field=='created'){?>
      <span><p class="ye"><?php print $content; ?></p></span>
      <?php }?>
      <?php if ($field=='internal_reference_id'){?>
      <span><p>备注：<?php if (empty($content)){?><?php print "-"; ?><?php }else{?><?php print $content; ?><?php }?></p></span>
      <?php }?>
    <?php endforeach; ?>  
    </li>
  </ul>
  <?php endforeach; ?>
</div>