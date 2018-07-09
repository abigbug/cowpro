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
<div class="due_in_con">
  <?php foreach ($rows as $row_count => $row): ?>
  <ul class="list-text">
    <li>
    <?php foreach ($row as $field => $content): ?>
      <?php if ($field=='issuing_id'){?>
      <span><p><?php print $content; ?></p></span>
      <?php }?>
      <?php if ($field=='period'){?>
      <span><p>第<font color="#fe7743"><?php print $content; ?></font></p></span>
      <?php }?>
      <?php if ($field=='period_total'){?>
      <span><p><font color="#fe7743">/<?php print $content; ?></font>期还款</p></span>
      <?php }?>
      <?php if ($field=='deadline'){?>
      <span><p>最后还款日：<?php print $content; ?></p></span>      
      <?php }?>
      <?php if ($field=='payable_amount'){?>
      <span><p>应还款金额：<font color="#fe7743"><?php print $content; ?></font></p></span>
      <?php }?>
      <?php if ($field=='status'){?>
      <span><p>状态：<?php print $content; ?></p></span>
      <?php }?>
      <?php if ($field=='operations'){?>
      <span><p><?php print $content; ?></p></span>
      <?php }?>
    <?php endforeach; ?>  
    </li>
  </ul>
  <?php endforeach; ?>
</div>