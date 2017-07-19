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

<article
	class="node node-tops node-product-type node-product-type-full node-tops-full node-published node-not-promoted node-not-sticky self-posted author-admin odd clearfix"
	id="node-tops-18">
	<div class="container-24 grid-14 prefix-1 clearfix">
		<div
			class="commerce-product-field commerce-product-field-field-images field-field-images node-18-product-field-images">
			<div class="cloud-zoom-container">
				<div id="wrap"
					style="top: 0px; z-index: 9999; position: relative; float: left;">

					<a
						href="<?php $img = reset($first_product['images']); print $img['url'];?>"
						class="cloud-zoom cloud-zoom-processed" id="cloud-zoom"
						rel="zoomWidth:'auto', zoomHeight:'auto', position:'inside', adjustX:0, adjustY:0, tint:'false', tintOpacity:'0.5', lensOpacity:'0.5', softFocus:false, smoothMove:'3', showTitle:false, titleOpacity:'0.5'"
						style="position: relative; display: block;"><img
						src="<?php $img = reset($first_product['images']); print $img['full_url'];?>"
						width="400" height="550" alt="" style="display: block;"></a>

					<div class="mousetrap"
						style="background-image: url(&quot;http://localhost/cms/commerce-kickstart/profiles/commerce_kickstart/libraries/cloud-zoom/blank.png&quot;); width: 400px; height: 550px; top: 0px; left: 0px; position: absolute; z-index: 9999; cursor: auto;"></div>
					<div class="mousetrap"
						style="background-image: url(&quot;http://localhost/cms/commerce-kickstart/profiles/commerce_kickstart/libraries/cloud-zoom/blank.png&quot;); width: 400px; height: 550px; top: 0px; left: 0px; position: absolute; z-index: 9999; cursor: auto;"></div>
					<div class="mousetrap"
						style="background-image: url(&quot;http://localhost/cms/commerce-kickstart/profiles/commerce_kickstart/libraries/cloud-zoom/blank.png&quot;); width: 400px; height: 550px; top: 0px; left: 0px; position: absolute; z-index: 9999; cursor: auto;"></div>
				</div>
				<div class="cloud-zoom-gallery-thumbs" style="float: left;">
				<?php foreach($first_product['images'] as $img) {?>
					<a
						href="<?php print $img['url']?>"
						class="cloud-zoom-gallery cloud-zoom-processed"
						rel="useZoom: 'cloud-zoom',smallImage: '<?php print $img['full_url']?>'"><img
						src="<?php print $img['thumbnail_url']?>"
						width="110" height="130" alt=""></a>
						<?php }?>
				</div>
			</div>
		</div>
	</div>
	<div class="container-24 grid-8 prefix-1">
		<div class="content clearfix">
			<header>
				<h2
					class="field field-name-title-field field-type-text field-label-hidden">
					<?php print $first_product['title']?></h2>
			</header>
			<div
				class="commerce-product-extra-field commerce-product-extra-field-sku node-18-product-sku">
				<div class="commerce-product-sku">
					<div class="commerce-product-sku-label">产品编号:</div>
					<?php print $first_product['sku']?>
				</div>

				<!-- END OUTPUT from 'profiles/commerce_kickstart/modules/contrib/commerce/modules/product/theme/commerce-product-sku.tpl.php' -->

			</div>
			<div
				class="field field-name-body field-type-text-with-summary field-label-hidden">
				<div class="field-items">
					<div class="field-item even">
						<p>
					<?php print $body?>
						</p>
					</div>
				</div>
			</div>

			<div
				class="field field-name-field-product field-type-commerce-product-reference field-label-hidden">
			<?php print '兑换积分：' . $first_product['price']?></li>
				<form method="get" action="<?php print $first_product['buy_link'];?>">
			兑换数量： <input name="qty" type="text" id="qty" value="1" size="4" onblur="changePrice()">
                <button type="submit">马上兑换</button>
				</form>
			</div>
		</div>
	</div>
</article>