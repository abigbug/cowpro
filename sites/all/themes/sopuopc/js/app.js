jQuery(document).ready(function($) { 
    // 收益计算器
    (function(){
        var btn = $('.cndns-right .jisuanqi');
        var jisuanqiEl = $('#jisuanqi');
        var jisuanBtn = jisuanqiEl.find('.jisuanqi-btn');
        var nhll = 0.066; // 默认年化利率
        var qixian = 1; // 默认期限

        // console.log(btn.length);
        if(btn.length > 0 && jisuanqiEl.length > 0){
            // 打开计算器
            btn.on('click',function(){
                layer.open({
                  type: 1,
                  shade: false,
                  title: false,
                  area: ['420px','auto'],
                  content: jisuanqiEl
                });
                // 指定焦点
                jisuanqiEl.find('input[name="jisuanqi-money"]').focus();
            });
        }
        // 预计年化利率
        jisuanqiEl.find('select[name="jisuanqi-qixian"]').change(function(){
            var sec = $(this).val();
            switch (sec) {                
                case '1':
                    qixian = 1;
                    nhll = 0.066;
                    break;
                case '3':
                    qixian = 3;
                    nhll = 0.090;
                    break;
                case '6':
                    qixian = 6;
                    nhll = 0.096;
                    break;
                case '12':
                    qixian = 12;
                    nhll = 0.108;
                    break;
                default:
                    // ...
                    break;
            }
            var lltxt = nhll*100;
            jisuanqiEl.find('.shouyilv').html(lltxt.toFixed(2)+'%');
        });
        // 计算收益
        if(jisuanBtn.length > 0){
            jisuanBtn.on('click',function(){
                var money = jisuanqiEl.find('input[name="jisuanqi-money"]').val();
                var reg = new RegExp("^[0-9]+$");
                if(!reg.test(money)){
                    layer.msg("请输入正确的投资金额！");
                    // 指定焦点
                    jisuanqiEl.find('input[name="jisuanqi-money"]').focus();
                    return false;
                }
                money = parseInt(money);
                var shouyi = money * nhll * qixian / 12; // 计算收益
                shouyi = parseInt((shouyi*100)) / 100; // 保留两位小数
                jisuanqiEl.find('.shouyi').html(shouyi);
            });
        }
        
        $('#top-back').hide()
        $(window).scroll(function(){
                 if($(this).scrollTop() > 350){
                        $("#top-back").fadeIn();
                 }
                 else{
                        $("#top-back").fadeOut();
                 }
          })	
    })();
});



// 限制只能输入数字
function onlyNum() {
    if(!(event.keyCode==46)&&!(event.keyCode==8)&&!(event.keyCode==37)&&!(event.keyCode==39))
    if(!((event.keyCode>=48&&event.keyCode<=57)||(event.keyCode>=96&&event.keyCode<=105)))
    event.returnValue=false;
}

//置顶事件
function topBack(){
  jQuery('body,html').animate({scrollTop:0},300);
}