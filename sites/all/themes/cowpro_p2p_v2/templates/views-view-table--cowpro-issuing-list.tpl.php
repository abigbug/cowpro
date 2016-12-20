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
<div <?php if ($classes) { print 'class="'. $classes . '" '; } ?><?php print $attributes; ?>>
    <?php foreach ($rows as $row_count => $row): ?>
    <div class="views-view-content-cowpro">
      <div <?php if ($row_classes[$row_count]) { print 'class="' . implode(' ', $row_classes[$row_count]) .'"';  } ?>>

		<table <?php if ($classes) { print 'class="'. $classes . '" '; } ?><?php print $attributes; ?>>
  <tbody>
      <tr <?php if ($row_classes[$row_count]) { print 'class="' . implode(' ', $row_classes[$row_count]) .'"';  } ?>>
          <td <?php if ($field_classes['view_issuing'][$row_count]) { print 'class="'. $field_classes['view_issuing'][$row_count] . '" '; } ?><?php if ($field_attributes['view_issuing'][$row_count]) { print drupal_attributes($field_attributes['view_issuing'][$row_count]);} ?>>

		<ul class="title1">
          <li <?php if ($field_classes['title'][$row_count]) { print 'class="'. $field_classes['title'][$row_count] . '" '; } ?><?php if ($field_attributes['view_issuing'][$row_count]) { print drupal_attributes($field_attributes['title'][$row_count]);} ?>>
            <?php print $row['title'];  unset($row['title']);?>
          </li>
          <li <?php if ($field_classes['field_applicant'][$row_count]) { print 'class="'. $field_classes['field_applicant'][$row_count] . '" '; } ?><?php if ($field_attributes['view_issuing'][$row_count]) { print drupal_attributes($field_attributes['field_applicant'][$row_count]);} ?>>
            <?php
            //print $row['field_applicant'];
            unset($row['field_applicant']);
            ?>
          </li>
		</ul>
          </td>
          <td class="separate"></td>

          <td <?php if ($field_classes['view_issuing'][$row_count]) { print 'class="'. $field_classes['view_issuing'][$row_count] . '" '; } ?><?php if ($field_attributes['view_issuing'][$row_count]) { print drupal_attributes($field_attributes['view_issuing'][$row_count]);} ?>>
            <?php print $row['view_issuing'];  unset($row['view_issuing']);?>
          </td>
		</tr>
  </tbody>
		</table>

		<div class="title">
			<ul class="title2">
				<?php print $row['field_issuing']; unset($row['field_issuing']);?>
			</ul>
			<ul class="title3">
				<li>状态</li>
				<li>计息方式</li>
				<li>融资金额(元)</li>
				<li>投资期限(天)</li>
				<li>预期年化收益率(%)</li>
			</ul>
		</div>

        <?php foreach ($row as $field => $content): ?>
          <span <?php if ($field_classes[$field][$row_count]) { print 'class="'. $field_classes[$field][$row_count] . '" '; } ?><?php print drupal_attributes($field_attributes[$field][$row_count]); ?>>
            <?php print $content; ?>
            (<?php print $field; ?>)
          </span>
        <?php endforeach; ?>

      </div>
    </div>
    <div class="clear"></div>
    <?php endforeach; ?>
</div>
