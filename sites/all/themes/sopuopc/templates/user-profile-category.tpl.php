<?php

/**
 * @file
 * Default theme implementation to present profile categories (groups of
 * profile items).
 *
 * Categories are defined when configuring user profile fields for the site.
 * It can also be defined by modules. All profile items for a category will be
 * output through the $profile_items variable.
 *
 * @see user-profile-item.tpl.php
 *      where each profile item is rendered. It is implemented as a definition
 *      list by default.
 * @see user-profile.tpl.php
 *      where all items and categories are collected and printed out.
 *
 * Available variables:
 * - $title: Category title for the group of items.
 * - $profile_items: All the items for the group rendered through
 *   user-profile-item.tpl.php.
 * - $attributes: HTML attributes. Usually renders classes.
 *
 * @see template_preprocess_user_profile_category()
 */
?>
<?php
$class_info = mb_substr($title,0,2,'utf-8');
$class_info1 = str_replace(' ', '-',transliteration_get("$class_info", '?', language_default('language')));

?>

<div class="clearfix <?php echo $class_info1?>content right-block">
  <div class="clearfix <?php echo $class_info1?>title">
    <?php if ($title): ?>
    <h3><?php print $title; ?></h3>
    <?php endif; ?>
  </div>
  <div class="clearfix <?php echo $class_info1?>list">
    <dl<?php print $attributes; ?> class=" <?php echo $class_info1?>-info">
      <?php print $profile_items; ?>
    </dl>
  </div>
</div>
