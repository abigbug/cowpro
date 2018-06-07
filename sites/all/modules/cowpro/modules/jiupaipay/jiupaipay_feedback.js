(function($) {
  window.onload=function(){
    check_feedback();
    var feedback=setInterval(check_feedback,8000);
    function check_feedback(){
      //alert(123);
      var journal_id = $("[name='journal_id']").val();
      $.ajax({	    
            type : "GET",
            dataType: "JSON",
            async: false,
	        url : "/cowpro/jiupaipay/topup_feedback_ajax",
            data:"journal_id="+ encodeURIComponent(journal_id),
            beforeSend:function(){
                $("#loading").show();
                $("#showdata").hide();
            },//发送数据之前
            success:function(response) {
                clearInterval(feedback);
                $("#loading").hide();
                $("#showdata").show();
              $("#showdata").text(response);     //加载数据，并写道页面
            }
      }); 
    }
}
})(jQuery);