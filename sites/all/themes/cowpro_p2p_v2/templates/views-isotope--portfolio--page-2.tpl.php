<?php
/**
 * @file views-isotope.tpl.php
 * Default simple view template to display a list of rows.
 *
 * @ingroup views_templates
 */
?>
<div id="isotope-container" class="isotope-container" data-cols="2cols">
	<?php $count = 0;
	foreach ( $rows as $id => $row ) :
		// added for easy multi-color display
		if ( $count == 5 ) :
			$count = 0;
		endif;

		$classlist = '';
		$bgstyle = '';

		// pull out isotope-filter class if it exists
		if ( strstr( $row, '<div class="isotope-filter">' ) ) :
			$rowparts = explode( '<div class="isotope-filter">', $row );
			$filterclass = explode( '</div>', $rowparts[1] );

			// check for commas and treat as an array for list of taxonomy terms
			if ( strstr( $filterclass[0], ',' ) ) :
				$classes = explode( ', ', $filterclass[0] );
				foreach ( $classes as $class ) :
					$class = trim( strip_tags( strtolower( $class ) ) );
					$class = str_replace( ' ', '-', $class );
					$class = str_replace( '/', '-', $class );
					$class = str_replace( '&amp;', '', $class );
					$classlist .= ' ' . $class;
				endforeach;
			else :
				//strip divs and normalize naming for just once
				$classlist = trim( strip_tags( strtolower( $filterclass[0] ) ) );
				$classlist = str_replace( ' ', '-', $classlist );
				$classlist = str_replace('/', '-', $classlist );
				$classlist = str_replace( '&amp;', '', $classlist );
			endif;
			$row = $rowparts[0] . '</div>';
		endif; ?>

		<div class="isotope-element isotope-element-<?php print $count; ?> <?php print $classlist; ?>" data-category="<?php print $classlist; ?>" <?php print $bgstyle ?>>
			<?php print $row; ?>
		</div>

		<?php // reset
		$rowparts = NULL;
		$filterclass = NULL;
		$count++;
	endforeach; ?>
</div>