<?php
/**
 * @file
 *
 * @see template_preprocess()
 * @see template_preprocess_cowpro_commerce_list_item()
 *
 * - $title : The title of this group of rows.  May be empty.
 * - $options['type'] will either be ul or ol.
 * @ingroup views_templates
 *
 * 参考 views-view-list.tpl.php
 */
?>
  <div class="jfgoods-img"><img width="257" height="221" src=<?php $first_item = reset($item['products']); print $first_item['field_images']['und'][0]['url']?>></div>
  <div class="jfgoods-xinxi">
    <h4 class="jfgoods-name"><a href=<?php global $base_url; print $base_url . '/shop/detail/' . $item['nid']?>><?php print $item['title']?></a></h4>
    <div class="jfgoods-p">
      <h6 class="jfgoods-w1">
        <p>所需积分</p>
        <p class="jfgoods-pcol1">
          <?php
            $product = reset($item['products']);
            $price = intval(floor($product['commerce_price']['und'][0]['amount']/100));
            print $price;
          ?>
        </p>
      </h6>
      <h6 class="jfgoods-w3"><a href=<?php global $base_url; print $base_url . '/shop/detail/' . $item['nid']?> target="_blank" class="jfgoods-btn border-radius5">立即兑换</a></h6>
    </div>
  </div>