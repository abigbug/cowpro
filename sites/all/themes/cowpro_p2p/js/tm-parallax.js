jQuery(document).ready(function($) {
	parallax_box = $('.parallax-box');

	if (parallax_box.length > 0) {
		ParallaxBox();
	}
	
	function ParallaxBox() {
		var windowSelector = $(window),
			documentSelector = $(document),
			documentWidth = documentSelector.width(),
			windowHeight = windowSelector.height(),
			liteMode = false,
			ieVersion = getInternetExplorerVersion(),
			ds = document.documentElement;
			
		if (!device.mobile() && !device.tablet()) {
			liteMode = false;
			
			if (ieVersion !=-1 && ieVersion < 9) {
				liteMode = true;
			}
		} else {
			liteMode = true;
		}
		
		parallax_box.each(function() {
			parallaxBox($(this));
		});
		
		function parallaxBox(obj) {
			var obj_bg = obj.find('.parallax-bg'),
				type = obj_bg.data('parallax-type'),
				obj_bg_inner,
				img,
				originalWidth = 0,
				originalHeight = 0,
				img_url = obj_bg.data('img-url'),
				bufferRatio = obj_bg.data('speed'),
				parallaxInvert = obj_bg.data('invert'),
				parallaxType = 'parallax_normal',
				objHeight = obj.height(),
				objOffsetTop = obj.offset().top,
				baseHeight = 0,
				parallax = true;
			
			switch (type) {
				case 'image':
					loadImg(); 
					break
				case 'video':
					obj_bg_inner = $('.parallax_media', obj_bg);
					
					if (liteMode) {
						obj_bg_inner.remove();
						loadImg();   
					} else {
						loadVideo();
					}
					break
			}
			
			function loadImg() {
				if (img_url) {
					img = new Image();
					img.src = img_url;
					
					img.onload = function () {
						originalWidth = img.width;
						originalHeight = img.height;
						
						imgBlocksStructure = !liteMode ? "<div class='parallax-img parallax-bg-inner'></div>" : "<img class='parallax-img parallax-bg-inner' src='' alt=''/>";
						obj_bg.append(imgBlocksStructure);
						obj_bg_inner = $('.parallax-img', obj_bg);
						
						if (!liteMode) {
							obj_bg_inner.css('background-image', 'url(' + (img_url) + ')');
						} else { 
							obj_bg_inner.attr('src', img_url);
							bufferRatio = 'none';
						}
						
						initParallax();
					}
				}
			}

			function loadVideo() {
				var videoElement = obj_bg_inner.get(0);

				videoElement.load();
				videoElement.play();
				
				originalWidth = videoElement.videoWidth;
				originalHeight = videoElement.videoHeight;
					
				if (img_url) {
					img = new Image();
					img.src = img_url;
					
					img.onload = function () {
						originalWidth = originalWidth == 0 ? img.width : originalWidth;
						originalHeight = originalHeight == 0 ? img.height : originalHeight;
						objectResize(obj_bg_inner, documentWidth, baseHeight, originalWidth, originalHeight);
					}
				}
				
				videoElement.onloadeddata = function() {
					originalWidth = videoElement.videoWidth;
					originalHeight = videoElement.videoHeight;
					objectResize(obj_bg_inner, documentWidth, baseHeight, originalWidth, originalHeight);
				}
				
				initParallax();
			}
			
			function initParallax() {
				if (!parallaxInvert) {
					parallaxType = 'parallax_normal';
				} else {
					parallaxType = 'parallax_invert';
				}
				
				switch (bufferRatio) {
					case 'low':
						bufferRatio = 3;
						break
					case 'normal':
						bufferRatio = 2.25;
						break
					case 'hight':
						bufferRatio = 1.5;
						break
					case 'fixed':
						if (ieVersion != -1) {
							if (type != 'video') {
								parallax = false;
								obj_bg_inner.css({backgroundAttachment:'fixed'});
							} else {
								console.log('ie');
								parallaxType = 'parallax_normal';
								bufferRatio = 2.25;
							}
						} else {
							parallaxType = 'parallax_fixes';
							bufferRatio = 1;
						}
						break
					case 'none':
						parallax = false;
						parallaxType = 'parallax_none';
						break
					default:
						bufferRatio = 2.25;
						
						if (bufferRatio > 5) {
							bufferRatio = 5; 
						}
						if (bufferRatio <= 1) {
							if ($.browser.msie) {
								parallax = false;
								obj_bg_inner.css({backgroundAttachment:'fixed'});
							} else {
								parallaxType = 'parallax_fixes';
								bufferRatio = 1;
							}
						}
						break
				}

				windowSelector.resize(parallaxObjResize);
				parallaxObjResize();
				
				if (!liteMode) {
					windowSelector.scroll(parallaxMove);
				}
			}
			
			function parallaxObjResize() {
				documentWidth = documentSelector.width();
				windowHeight = windowSelector.height();

				objHeight = obj.height();

				obj_bg.width(documentWidth);
				obj_bg.css({'width' : documentWidth, 'margin-left' : Math.floor(documentWidth*-0.5), 'left' : '50%'});
				
				baseHeight = getBaseHeight(parallaxType, objHeight, bufferRatio);
				objectResize(obj_bg_inner, documentWidth, baseHeight, originalWidth, originalHeight);
				
				if (!liteMode) {
					parallaxMove();
				}
			}

			function parallaxMove() {
				if (parallax && !liteMode) {
					var documentScrollTop,
						startScrollTop,
						endScrollTop;

					objOffsetTop = obj.offset().top;
					documentScrollTop = documentSelector.scrollTop();

					startScrollTop = documentScrollTop + windowHeight;
					endScrollTop = documentScrollTop - objHeight;

					if ((startScrollTop > objOffsetTop) && (endScrollTop < objOffsetTop)) {
						y = documentScrollTop - objOffsetTop;
						
						if (!parallaxInvert) {
							newPositionTop =  parseInt(y / bufferRatio);
						} else {
							newPositionTop = -parseInt(y / bufferRatio) - parseInt(windowHeight / bufferRatio)
						}

						obj_bg_inner.css({top: newPositionTop + 'px'});
					}
				}
			}
		}
		
		function objectResize(obj, baseWidth, baseHeight, originalWidth, originalHeight ) {
			var imageRatio,
				originalWidth,
				originalHeight,
				newImgWidth,
				newImgHeight,
				newImgTop,
				newImgLeft;

			imageRatio = originalHeight/originalWidth;
			containerRatio = baseHeight/baseWidth;
	
			if (containerRatio > imageRatio) {
				newImgHeight = baseHeight;
				newImgWidth = Math.round((newImgHeight*originalWidth) / originalHeight);
			} else {
				newImgWidth = baseWidth;
				newImgHeight = Math.round((newImgWidth*originalHeight) / originalWidth);
			}
	
			newImgLeft =- (newImgWidth-baseWidth) * .5;
			newImgTop =- (newImgHeight-baseHeight) * .5;
			
			obj.css({width: newImgWidth, height: newImgHeight, marginTop: newImgTop, marginLeft: newImgLeft});
		}
		
		function getBaseHeight(parallaxType, objHeight, bufferRatio) {
			var newBaseHeight = 0;

			switch (parallaxType) {
				case 'parallax_normal':
					newBaseHeight = objHeight + parseInt((windowHeight - objHeight)/bufferRatio);
					break
				case 'parallax_invert':
					newBaseHeight = objHeight + parseInt((windowHeight + objHeight)/bufferRatio);
					break
				case 'parallax_fixes':
					newBaseHeight = windowHeight;
					break
				case 'parallax_none':
					newBaseHeight = objHeight;
					break
			}

			return newBaseHeight;
		}
		
		function getInternetExplorerVersion() {
			var rv = -1;
			if (navigator.appName == 'Microsoft Internet Explorer') {
				var ua = navigator.userAgent,
					re  = new RegExp("MSIE ([0-9]{1,}[\.0-9]{0,})");

				if (re.exec(ua) != null) {
					rv = parseFloat(RegExp.$1);
				}
			} else if (navigator.appName == 'Netscape') {
				var ua = navigator.userAgent,
					re  = new RegExp("Trident/.*rv:([0-9]{1,}[\.0-9]{0,})");

				if (re.exec(ua) != null) {
					rv = parseFloat(RegExp.$1);
				}
			}

			return rv;
		}
	}
});