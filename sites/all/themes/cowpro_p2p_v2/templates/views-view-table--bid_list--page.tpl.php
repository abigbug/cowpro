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
<div class="invest_view_content">
<?php foreach ($rows as $row_count => $row): ?>
  <div class="clearfix invest_list">
    <?php foreach ($row as $field => $content): ?>  
      <?php if ($field=='title'){?>
        <div class="invest_title">
          <?php print $content; ?>
        </div>
      <?php }?>
      <?php if ($field=='annual_rate'){?>
        <div class="col-md-2 the-nianhua">
          <span class="num-info"><?php print $content; ?></span>
          <p class="text-info">年化收益(%)</p>
        </div>
      <?php }?>
      <?php if ($field=='amount'){?>
        <div class="col-md-2 the-jine">
          <span class="num-info"><?php print $content; ?></span>
          <p class="text-info">投资金额(元)</p>
        </div>
      <?php }?>
      <?php if ($field=='term'){?>
        <div class="col-md-2 the-qixian">
          <span class="num-info"><?php print $content; ?></span>
          <p class="text-info">投资期限</p>
        </div>
      <?php }?>
      <?php if ($field=='make_loans_time'){?>
        <div class="col-md-222 invest_qt"><?php print $content;?>起投 -</div>
      <?php }?>
      <?php if ($field=='issuing_deadline'){?>
        <div class="col-md-222 invest_dq"><?php print $content;?>到期</div>
      <?php }?>
      <?php if ($field=='status'){?>
        <div class="col-md-222 invest_zt">状态：<?php print $content;?></div>
      <?php }?>
    <?php endforeach; ?>  
  </div>
<?php endforeach; ?>
</div>