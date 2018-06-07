(function($) {
	Drupal.behaviors.mobile_verify = {};
	Drupal.behaviors.mobile_verify.attach = function(context, settings) {
  $( document ).ready(function() {
    $("#edit-name").val('');
});


      // http://stackoverflow.com/questions/2024389/jquery-click-event-is-firing-multiple-times-when-using-class-selector
		$(".send-verify-code").unbind('click').click(
				function(event) {
					event.preventDefault();
					var mobile_number = $(".mobile_number").val();
					/*
					var number_object = $(".mobile_number");
					if (number_object.length == 0) {
						number_object = $("#edit-name");
					}
					var mobile_number = number_object.val();
					*/
					var captcha_response = $("[name='captcha_response']").val();
					var captcha_sid = $("[name='captcha_sid']").val();
					var captcha_token = $("[name='captcha_token']").val();
					var form_id = $("[name='form_id']").val();

					if (!mobile_number_vailidate(mobile_number)) {
						$("#mobile_verify_help").text('请输入有效的手机号码');
					} else {
						$.ajax({
							type : "GET",
							url : Drupal.settings.basePath
									+ "/cowpro/mobile-verify-send-code",
							data : "mobile_number="
									+ encodeURIComponent(mobile_number)
									+ "&captcha_response="
									+ encodeURIComponent(captcha_response)
									+ "&captcha_sid="
									+ encodeURIComponent(captcha_sid)
									+ "&captcha_token="
									+ encodeURIComponent(captcha_token)
									+ "&form_id="
									+ encodeURIComponent(form_id),
							dataType : 'json',
							success : function(response) {
								if (response.status == 200) {
									$("#mobile_verify_help").text('验证码已发送到您的手机，请查收');
									var seconds = 180;
									startTimer(seconds);
								} else {
									$('#send_verify').removeAttr('disabled');
									$("#mobile_verify_help").prepend(
											"<div class='mobile-verify-msg messages error'>"
													+ response.message
													+ "</div>");
								}
							}
						});
					}
				});
	};

	var smsTimer;
	function startTimer(duration) {
		$('#send_verify').attr('disabled', 'disabled');
		var timer = duration, minutes, seconds;
		smsTimer = setInterval(function() {
			minutes = parseInt(timer / 60, 10)
			seconds = parseInt(timer % 60, 10);

			minutes = minutes < 10 ? "0" + minutes : minutes;
			seconds = seconds < 10 ? "0" + seconds : seconds;

			//$('#send_verify').val(minutes + ":" + seconds);
			$("#mobile_verify_help_2").text(minutes + ":" + seconds + '之后可重新发送验证码');

			if (--timer < 0) {
				stopTimer();
			}
		}, 1000);
	}
	;

	function stopTimer() {
		clearInterval(smsTimer);
		//$('#send_verify').val("发送验证码");
		$('#send_verify').removeAttr('disabled');
		$("#mobile_verify_help_2").text('');
	}
	;

	function mobile_number_vailidate(mobile_number) {
		var _emp = /^\s*|\s*$/g;
		mobile_number = mobile_number.replace(_emp, "");
		var _d = /^1\d{10}$/g;
		if (_d.test(mobile_number)) {
			return true;
		} else {
			return false;
		}
	}
	;
})(jQuery);
