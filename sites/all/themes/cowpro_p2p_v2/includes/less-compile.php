<?php
/*
 * Style files
 *
 */
$themeDir = 'sites/all/themes/cowpro_p2p_v2';

$styleInput = $themeDir . '/less/style.less';
$styleOutput = $themeDir . '/css/style.css';

$styleMobileInput = $themeDir . '/less/style-mobile.less';
$styleMobileOutput = $themeDir . '/css/style-mobile.css';

/*
 * Auto Compiling LESS files (cache)
 *
 */
function auto_less_compile( $inputFile, $outputFile ) {
	// load the cache
	$cacheFile = $inputFile . ".cache";

	if ( file_exists( $cacheFile ) ) {
		$cache = unserialize( file_get_contents( $cacheFile ) );
	} else {
		$cache = $inputFile;
	}

	// custom formatter
	$formatter = new lessc_formatter_classic;
	$formatter->indentChar = "\t";

	$less = new lessc;
	$less->setFormatter( $formatter );


	try {
		// create a new cache object, and compile
		$newCache = $less->cachedCompile( $cache );

		// the next time we run, write only if it has updated
		if ( !is_array( $cache ) || $newCache["updated"] > $cache["updated"] ) {
			file_put_contents( $cacheFile, serialize( $newCache ) );
			file_put_contents( $outputFile, $newCache['compiled'] );
		}
	} catch ( Exception $ex ) {
		echo "lessphp fatal error: " . $ex->getMessage();
	}
}
auto_less_compile( $styleInput, $styleOutput );
auto_less_compile( $styleMobileInput, $styleMobileOutput ); ?>