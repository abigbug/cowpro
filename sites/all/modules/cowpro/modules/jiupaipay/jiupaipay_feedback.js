(function($) {
    window.onload = function(){  
      check_feedback();
    };
    function check_feedback(){
      var journal_id = $("[name='journal_id']").val();
      $.ajax({
            type: "get",
            dataType: "JSON",
            async: false,
            url:"http://test.jinbeizeng.com/cowpro/jiupaipay/topup_feedback_ajax",//目标地址
            data:"journal_id="
                            + encodeURIComponent(journal_id),
            beforeSend:function(){
                $("#loading").show();
                $("#showdata").hide();
            },//发送数据之前
            success:function(response) {
              $("#showdata").text(response);     //加载数据，并写道页面
            },
            complete:function(){
                $("#loading").hide();
                $("#showdata").show();
            },//接收数据完毕
            error:function (response) {
              setTimout(check_feedback(),5000);
            }
      }); 
    }
})(jQuery);