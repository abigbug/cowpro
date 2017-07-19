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
<article
	class="node node-tops contextual-links-region node-product-type node-tops node-product-type-product-list node-tops-product-list node-published node-not-promoted node-not-sticky self-posted author-admin odd clearfix"
	id="node-tops-18">
	<div class="content clearfix">
		<div
			class="commerce-product-field commerce-product-field-field-images field-field-images node-18-product-field-images">
			<figure
				class="field field-name-field-images field-type-image field-label-hidden">
						<a
			href=<?php global $base_url; print $base_url . '/shop/detail/' . $item['nid']?>>
<img
				src=<?php $first_item = reset($item['products']); print $first_item['field_images']['und'][0]['url']?>
					width="230" height="260" alt=""></a>
			</figure>
		</div>
		<header>
			<h2
				class="field field-name-title-field field-type-text field-label-hidden">
						<a
			href=<?php global $base_url; print $base_url . '/shop/detail/' . $item['nid']?>>
			<?php print $item['title']?>
			</a>
			</h2>
		</header>
	</div>
</article>
