<?php

/**
 * @file
 * Default theme implementation to format an individual feed item for display
 * on the aggregator page.
 *
 * Available variables:
 * - $feed_url: URL to the originating feed item.
 * - $feed_title: Title of the feed item.
 * - $source_url: Link to the local source section.
 * - $source_title: Title of the remote source.
 * - $source_date: Date the feed was posted on the remote source.
 * - $content: Feed item content.
 * - $categories: Linked categories assigned to the feed.
 *
 * @see template_preprocess()
 * @see template_preprocess_aggregator_item()
 */
?>
<div class="feed-item">
	<header class="feed-item-header">
		<h2 class="title feed-item-title">
			<a href="<?php print $feed_url; ?>"><?php print $feed_title; ?></a>
		</h2>
		<div class="submitted feed-item-submitted">
			<?php if ( $source_url ) : ?>
				<a href="<?php print $source_url; ?>" class="feed-item_src"><?php print $source_title; ?></a> -
			<?php endif; ?>
			<time class="feed-item-time" datetime="<?php print $datetime; ?>"><?php print $source_date; ?></time>
		</div>
	</header>

	<?php if ( $content ) : ?>
		<div class="content feed-item-content">
			<?php print $content; ?>
		</div>
	<?php endif; ?>

	<?php if ( $categories ) : ?>
		<footer class="feed-item-footer">
			<div class="categories feed-item-categories"><strong><?php print t( 'Categories' ); ?></strong>: <?php print implode( ', ', $categories ); ?></div>
		</footer>
	<?php endif; ?>
</div><!-- /.feed-item -->