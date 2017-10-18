<?php

/**
 * @file
*
* Available variables:
* 	$title
*  $status
*  $promote
*  $nid
*  $type
*  $body
*  $products = array();
*  $products['sku']
*  $products['title']
*  $products['product_id']
*  $products['type']
*  $products['price']
*  $products['images'] = $images;
*
* @see template_preprocess()
* @see template_preprocess_cowpro_commerce_item()
*
* @ingroup themeable
*/
?>
<article class="sopuo-shop-view">
  <div class="Xcontent">
    <ul class="Xcontent01">
      <div class="Xcontent06"><img src="<?php $img = reset($first_product['images']); print $img['url'];?>" id="imgshow"></div>
      <div class="Xcontent08">
        <?php  foreach($first_product['images'] as $img) {?>
	<div class="Xcontent10"><img src="<?php print $img['url']?>" onclick="showimg('<?php print $img['url']?>');" ></div>
        <?php }?>
      </div>
      <div class="Xcontent13">
        <div class="Xcontent14"><p><?php print $first_product['title']?></a></div>
	<div class="Xcontent17">
	  <div class="Xcontent20">
	    <p class="Xcontent21">产品编号：</p>
	    <p class="Xcontent22"><?php print $first_product['sku']?></p>
	  </div>
          <div class="Xcontent20" style="clear: both;">
	    <p class="Xcontent21">兑换积分：</p>
            <p class="Xcontent22"><b><?php print $first_product['price']?></b></p>
          </div>
	</div>
	<div class="Xcontent30">
	  <form method="get" action="<?php print $first_product['buy_link'];?>">
	  <p class="Xcontent31">兑换数量：</p><input name="qty" type="text" id="qty" value="1" size="4"class="input" onblur="changePrice()">
          <?php if ($item['show_bill_input'] == 1) {?>
          <p class="Xcontent31">手机：</p><input name="mbl" type="text" id="mbl" value="<?php print $item['user_mobile']?>" size="10"class="input" style="width:120px">
          <?php }?>
          <div class="Xmsdh"><button type="submit">马上兑换</button></div>
	  </form>
        </div>
      </div>
    </ul>
    <div class="field field-name-body field-type-text-with-summary field-label-hidden">
      <div class="field-items">
	<div class="field-item even">
	  <p><?php print $body?></p>
	</div>
      </div>
    </div>
  </div>
</article>