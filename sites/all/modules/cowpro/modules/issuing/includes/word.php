<?php
class word {
	function start() {
		ob_start ();
		echo '<html xmlns:o="urn:schemas-microsoft-com:office:office"
		xmlns:w="urn:schemas-microsoft-com:office:word"
		xmlns="http://www.w3.org/TR/REC-html40">';
	}
	function save($path) {
		echo "</html>";
		$data = ob_get_contents ();
		ob_end_clean ();
		$this->wirtefile ( $path, $data );
	}
	function wirtefile($fn, $data) {
		// $fp=fopen($fn,"wb");
		// fwrite($fp,$data);
		// fclose($fp);
		$ua = $_SERVER ["HTTP_USER_AGENT"];
		$encoded_filename = urlencode ( $fn );
		$encoded_filename = str_replace ( "+", "%20", $encoded_filename );
		header ( 'Content-Type: application/octet-stream' );
		// if (preg_match("/MSIE/", $ua)) {
		if (preg_match ( "/MSIE/", $ua ) || preg_match ( "/Trident\/7.0/", $ua )) {
			header ( 'Content-Disposition: attachment; filename="' . $encoded_filename . '"' );
		} else if (preg_match ( "/Firefox/", $ua )) {
			header ( 'Content-Disposition: attachment; filename*="utf8\'\'' . $fn . '"' );
		} else {
			header ( 'Content-Disposition: attachment; filename="' . $fn . '"' );
		}
		echo $data;
		ob_flush (); // 每次执行前刷新缓存
		flush ();
	}
	function file_transfer($uri, $headers) {
		if (ob_get_level()) {
			ob_end_clean();
		}

		foreach ($headers as $name => $value) {
			drupal_add_http_header($name, $value);
		}
		drupal_send_headers();
		$scheme = file_uri_scheme($uri);
		// Transfer file in 1024 byte chunks to save memory usage.
		if ($scheme && file_stream_wrapper_valid_scheme($scheme) && $fd = fopen($uri, 'rb')) {
			while (!feof($fd)) {
				print fread($fd, 1024);
			}
			fclose($fd);
		}
		else {
			drupal_not_found();
		}
		drupal_exit();
	}
}