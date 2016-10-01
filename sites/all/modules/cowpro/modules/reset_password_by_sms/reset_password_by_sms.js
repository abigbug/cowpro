(function($) {
	Drupal.behaviors.mobile_verify = {};
	Drupal.behaviors.mobile_verify.attach = function(context, settings) {
		// http://stackoverflow.com/questions/2024389/jquery-click-event-is-firing-multiple-times-when-using-class-selector
		$(".send-verify-code").unbind('click').click(
				function(event) {
					event.preventDefault();
					var mobile_number = $(".mobile_number").val();
					var user_name = $(".user_name").val();

					if (!mobile_number_vailidate(mobile_number)) {
						$("#mobile_verify_help").text('请输入有效的手机号码');
					} else {
						$.ajax({
							type : "GET",
							url : Drupal.settings.basePath
									+ "/cowpro/reset-password-send-code",
							data : "mobile_number="
									+ encodeURIComponent(mobile_number)
									+ "&user_name="
									+ encodeURIComponent(user_name),
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

			$('#send_verify').val(minutes + ":" + seconds);

			if (--timer < 0) {
				stopTimer();
			}
		}, 1000);
	}
	;

	function stopTimer() {
		clearInterval(smsTimer);
		$('#send_verify').val("发送验证码");
		$('#send_verify').removeAttr('disabled');
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
