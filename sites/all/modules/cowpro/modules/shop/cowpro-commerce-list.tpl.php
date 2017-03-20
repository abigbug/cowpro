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
<div id="product_info">
	<ul>
		<li><?php print $title?></li>
		<li><?php print $body?></li>
		<?php foreach ($products as $product) {?>
			<li><?php print $product['product_id']?></li>
			<li><img src=<?php print $product['images'][0]['url']?>></li>
			<li><?php print '兑换积分：' . $product['price']?></li>
				<form method="get" action="<?php print $product['buy_link'];?>">
			兑换数量： <input name="qty" type="text" id="qty" value="1" size="4" onblur="changePrice()">
                <button type="submit">马上兑换</button>
				</form>
		<?php }?>
	</ul>
</div>
