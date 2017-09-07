/**
 * cowpro_p2p javascript core
 *
 * - Provides frequently used extensions to base javascript objects
 * - jQuery browser detection tweak
 * - Define functions used in events
 */

// Add String.trim() method
String.prototype.trim = function() {
	return this.replace(/\s+$/, '').replace(/^\s+/, '');
}

// Add Array.indexOf() method
if (!Array.prototype.indexOf) {
	Array.prototype.indexOf = function (obj, fromIndex) {
		if (fromIndex == null) {
			fromIndex = 0;
		} else if (fromIndex < 0) {
			fromIndex = Math.max(0, this.length + fromIndex);
		}

		for (var i = fromIndex, j = this.length; i < j; i++) {
			if (this[i] === obj) {
				return i;
			}
		}
		return -1;
	};
}


// jQuery Browser Detect Tweak For IE7
//jQuery.browser.version = jQuery.browser.msie && parseInt(jQuery.browser.version) == 6 && window["XMLHttpRequest"] ? "7.0" : jQuery.browser.version;

// Console.log wrapper to avoid errors when firebug is not present
// usage: log('inside coolFunc', this, arguments);
// paulirish.com/2009/log-a-lightweight-wrapper-for-consolelog/
window.log = function() {
	log.history = log.history || []; // store logs to an array for reference
	log.history.push(arguments);
	if (this.console) {
		console.log(Array.prototype.slice.call(arguments));
	}
};

// init object
var cowpro_p2p = cowpro_p2p || {};

/**
 * Image handling functions
 */
cowpro_p2p.image = { _cache : [] };

// preload images
cowpro_p2p.image.preload = function() {
	for (var i = arguments.length; i--;) {
		var cacheImage = document.createElement('img');
		cacheImage.src = arguments[i];
		cowpro_p2p.image._cache.push(cacheImage);
	}
}

jQuery(document).ready(function($){
    $(".boxflex li a").each(function(){
        $this = $(this);
        if($this[0].href==String(window.location)){  
            $(".boxflex li").removeClass("on");
            $this.parent().addClass("on");  
        }  
    });
        
    var msg = $("div.messages");
    if (msg.size() > 0) {
            alert(msg.text());
    }
   
});

    window.alert = function(str)  
    {  
     var shield = document.createElement("DIV");  
     shield.id = "shield";  
     shield.style.position = "absolute";  
     shield.style.left = "0px";  
     shield.style.top = "0px";  
     shield.style.width = "100%";  
     shield.style.height = document.body.scrollHeight+"px";  
     //弹出对话框时的背景颜色  
     shield.style.background = "#e4e4e4";  
     shield.style.textAlign = "center";  
     shield.style.zIndex = "9999999";
     
     //背景透明 IE有效  
     //shield.style.-moz-opacity = 0.8;  
     shield.style.opacity = .80;  
     shield.style.filter = "alpha(opacity=80)";  
     var alertFram = document.createElement("DIV");  
     alertFram.id="alertFram";  
     alertFram.style.position = "absolute";  
     alertFram.style.left = "10%";  
     alertFram.style.top = "20%";  
     alertFram.style.marginLeft = "0px";  
     alertFram.style.marginTop = "0px";  
     alertFram.style.width = "80%";  
     alertFram.style.height = "150px";  
     alertFram.style.background = "#ff0000";  
     alertFram.style.textAlign = "center";  
     alertFram.style.lineHeight = "150px";  
     alertFram.style.zIndex = "99999999";  
     strHtml = "<ul style=\"list-style:none;margin:0px;padding:0px;width:100%\">\n";  
     strHtml += " <li style=\"background:#FFB226;text-align:left;padding-left:20px;font-size:14px;font-weight:bold;height:25px;line-height:25px;border:1px solid #F9CADE;\">[提示]</li>\n";  
     strHtml += " <li style=\"background:#fff;text-align:center;font-size:12px;height:120px;line-height:20px;border-left:1px solid #FFB226;border-right:1px solid #F9CADE;\">"+str+"</li>\n";  
     strHtml += " <li style=\"background:#FFB226;text-align:center;font-weight:bold;height:25px;line-height:25px; border:1px solid #F9CADE;\"><input type=\"button\" value=\"确 定\" onclick=\"doOk()\" /></li>\n";  
     strHtml += "</ul>\n";  
     alertFram.innerHTML = strHtml;  
     document.body.appendChild(alertFram);  
     document.body.appendChild(shield);  
     //var ad = setInterval("doAlpha()",5);  
     this.doOk = function(){  
         alertFram.style.display = "none";  
         shield.style.display = "none";  
     }  
     alertFram.focus();  
     document.body.onselectstart = function(){return false;};  
    }
    
    function show(id,id2,obj){
       jQuery(".boxflex li").removeClass("on");
       obj.parent().addClass("on");
       if(document.getElementById(id).style.display=="block"){
         document.getElementById(id).style.display="none";
         document.getElementById(id2).style.display="none";
       }else{
         document.getElementById(id).style.display="block";
         document.getElementById(id2).style.display="block";
       }
    }
    
    function CloseDiv(show_div,bg_div)
    {
    document.getElementById(show_div).style.display='none';
    document.getElementById(bg_div).style.display='none';
    };

