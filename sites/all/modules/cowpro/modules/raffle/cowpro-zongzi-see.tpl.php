  <style type="text/css">
.dw_main{width: 100%; min-width: 1420px; overflow: hidden;}
.main-0{ background: url("/sites/all/modules/cowpro/modules/raffle/images_zongzi/pic_01.jpg") no-repeat center; width: 100%; min-width: 1420px; height: 692px; overflow: hidden;}
.main-1{ background: url("/sites/all/modules/cowpro/modules/raffle/images_zongzi/pic_02.jpg") no-repeat center; width: 100%; min-width: 1420px; height: 362px; overflow: hidden;}
.main-1 dl{ width: 1000px;margin: 0 auto;}
.main-1 dl dd{ margin-left:450px; width:50px; text-align:center;font-size: 26px; font-weight:bold; color: #ea6612; line-height: 40px; margin-top: 299px;}

.main-2{ background: url("/sites/all/modules/cowpro/modules/raffle/images_zongzi/pic_03.jpg") no-repeat center; width: 100%; min-width: 1420px; height: 821px; overflow: hidden;} 
.main-2 dl{width: 900px;margin: 0 auto;}
.main-2 dl dd{width:92%;font-size: 16px;color:#23C011; line-height: 28px; margin-top: 150px;}
.main-2 dl dd span{font-size:18px;font-weight:bold;}

.main-3{ background: url("/sites/all/modules/cowpro/modules/raffle/images_zongzi/pic_04.jpg") no-repeat center; width: 100%; min-width: 1420px; height: 166px; overflow: hidden;} 

.main-4{ background: url("/sites/all/modules/cowpro/modules/raffle/images_zongzi/pic_05.jpg") center;background-repeat: repeat-y;  width: 100%; min-width: 1420px; height: 730px; overflow: hidden;} 
.main-4 dl{ width: 1000px;margin: 0 auto;}
.main-4 dl dd{width:684px;margin: 0 auto;}

.main-5{ background: url("/sites/all/modules/cowpro/modules/raffle/images_zongzi/pic_06.jpg") no-repeat center; width: 100%; min-width: 1420px; height: 915px; overflow: hidden;} 
.main-5 dl{width: 900px;margin: 0 auto;}
.main-5 dl dd{width:92%;font-size: 16px;color: #23C011; line-height: 28px; margin-top: 300px;}
.main-5 dl dd span{font-size:18px;font-weight:bold;}

.main-6{ background: url("/sites/all/modules/cowpro/modules/raffle/images_zongzi/pic_07.jpg") no-repeat center; width: 100%; min-width: 1420px; height: 622px; overflow: hidden;} 

#lottery{width:684px;height:684px;margin:20px auto;background:url(/sites/all/modules/cowpro/modules/raffle/images_zongzi/bg.jpg) no-repeat;padding:50px 55px;}
#lottery table td{width:142px;height:142px;text-align:center;vertical-align:middle;font-size:24px;color:#333;font-index:-999}
#lottery table td a{width:284px;height:284px;line-height:150px;display:block;text-decoration:none;}
#lottery table td.active{background-color:#ea0000;}

.wx-main-0{ background: url("/sites/all/modules/cowpro/modules/raffle/images_zongzi/wx_pic_01.jpg") no-repeat center; width: 100%; min-width: 1420px; height: 746px; overflow: hidden;}
.wx-main-0 dl{ width: 1000px;margin: 0 auto;}
.wx-main-0 dl dd{ margin-left:446px; width:50px; text-align:center;font-size: 36px; font-weight:bold; color: #ea6612; line-height: 40px; margin-top: 686px;}

.wx-main-1{ background: url("/sites/all/modules/cowpro/modules/raffle/images_zongzi/wx_pic_02.jpg") no-repeat center; width: 100%; min-width: 1420px; height: 950px; overflow: hidden;} 
.wx-main-1 dl{width: 1100px;margin: 0 auto;}
.wx-main-1 dl dd{width:92%;font-size:26px;color:#23C011; line-height: 34px; margin-top: 130px;}
.wx-main-1 dl dd span{line-height:32px;font-weight:bold;}
  </style>
<div class="clearfix"></div>
<div class="dw_main">
  <div class="main-0">
    <dl>
      <dd>&nbsp;</dd>
    </dl>
  </div>
  <div class="main-1">
    <dl>
      <dd><?php $term = current(taxonomy_get_term_by_name('粽子'));
                $points = userpoints_get_current_points($user->uid,$term->tid);
                echo round($points / 100,2);
          ?></dd>
    </dl>
  </div>
  <div class="main-2">
    <dl>
      <dd>
         <span>活动时间：</span><br>
         6月8日17：30——6月18日23：59<br><br>
    
        <span>“粽子”获得：</span><br>
         累计投资1万年化可以在平台上兑换一个“粽子”；<br><br>
        
         <span>参与流程：</span><br>
         参与投资并达到要求后，在平台上兑换“粽子”，一个“粽子”参与一次大转盘抽奖，每次转盘后减少相对应的“粽子”数量，未参与转盘抽奖视为放弃（逾期不候）<br><br>
        
         <span>转盘内容：</span><br>
         50元投资代金券，单笔投资≥100000，期限≥6个月，5%概率<br>
         20元投资代金券，单笔投资≥40000，期限≥6个月，10%概率<br>
         10元投资代金券，单笔投资≥20000，期限≥6个月，15%概率<br>
         平台100积分，10%概率<br>
         平台50积分，20%概率<br>
         谢谢参与，40%概率<br><br>
        
         <span>奖励发放：</span><br>
         转盘赢得的相应奖励，会自动进入用户的账号；<br>
         活动截止时间为6月18日，代金券使用时间期限截止6月25日23:59分。 
      </dd>
    </dl>
  </div>
  <div class="main-3">
    <dl>
      <dd>&nbsp;</dd>
    </dl>
  </div>
  <div class="main-4">
    <dl>
      <dd>
        <div id="lottery">
          <table border="0" cellpadding="0" cellspacing="0">
            <tr>
              <td class="lottery-unit lottery-unit-0"><img src="<?php echo $GLOBALS['base_url'] . '/' . drupal_get_path('module', 'cowpro_raffle') . '/images_zongzi/1.png'; ?>"></td>
              <td class="lottery-unit lottery-unit-1"><img src="<?php echo $GLOBALS['base_url'] . '/' . drupal_get_path('module', 'cowpro_raffle') . '/images_zongzi/6.png'; ?>"></td>
              <td class="lottery-unit lottery-unit-2"><img src="<?php echo $GLOBALS['base_url'] . '/' . drupal_get_path('module', 'cowpro_raffle') . '/images_zongzi/2.png'; ?>"></td>
              <td class="lottery-unit lottery-unit-3"><img src="<?php echo $GLOBALS['base_url'] . '/' . drupal_get_path('module', 'cowpro_raffle') . '/images_zongzi/6.png'; ?>"></td>
            </tr>
            <tr>
              <td class="lottery-unit lottery-unit-11"><img src="<?php echo $GLOBALS['base_url'] . '/' . drupal_get_path('module', 'cowpro_raffle') . '/images_zongzi/5.png'; ?>"></td>
              <td colspan="2" rowspan="2"><a href="javascript:void(0);"></a></td>
              <td class="lottery-unit lottery-unit-4"><img src="<?php echo $GLOBALS['base_url'] . '/' . drupal_get_path('module', 'cowpro_raffle') . '/images_zongzi/3.png'; ?>"></td>
            </tr>
            <tr>
              <td class="lottery-unit lottery-unit-10"><img src="<?php echo $GLOBALS['base_url'] . '/' . drupal_get_path('module', 'cowpro_raffle') . '/images_zongzi/6.png'; ?>"></td>
              <td class="lottery-unit lottery-unit-5"><img src="<?php echo $GLOBALS['base_url'] . '/' . drupal_get_path('module', 'cowpro_raffle') . '/images_zongzi/6.png'; ?>"></td>
            </tr>
            <tr>
              <td class="lottery-unit lottery-unit-9"><img src="<?php echo $GLOBALS['base_url'] . '/' . drupal_get_path('module', 'cowpro_raffle') . '/images_zongzi/6.png'; ?>"></td>
              <td class="lottery-unit lottery-unit-8"><img src="<?php echo $GLOBALS['base_url'] . '/' . drupal_get_path('module', 'cowpro_raffle') . '/images_zongzi/5.png'; ?>"></td>
              <td class="lottery-unit lottery-unit-7"><img src="<?php echo $GLOBALS['base_url'] . '/' . drupal_get_path('module', 'cowpro_raffle') . '/images_zongzi/6.png'; ?>"></td>
              <td class="lottery-unit lottery-unit-6"><img src="<?php echo $GLOBALS['base_url'] . '/' . drupal_get_path('module', 'cowpro_raffle') . '/images_zongzi/4.png'; ?>"></td>
            </tr>
          </table>
        </div>
      </dd>
    </dl>
  </div>
  <div class="main-5">
    <dl>
      <dd>
        <span>活动规则：</span><br>
        <span>-活动时间：</span><br>
        6月4日17：30——6月18日23：55<br>
        6月19日——6月21日陆续发放代金券，代金券使用时间期截止6月25日23：59。<br><br>
         
        <span>-参与方式：</span><br>
          点击游戏链接参与线上游戏，完成小游戏后抽奖得到兑奖口令，金贝增公众号里直接回复兑奖口令，查看是否中奖；<br><br>
         
        <span>-活动奖励：</span><br>
          一等奖：5名    50元投资代金券，投资满5万可用<br>
          二等奖：10名   20元投资代金券，投资满2万可用<br>
          三等奖：15名  10元投资代金券，投资满1万可用<br>
          优秀奖：20名  5元投资代金券，投资满5千可用<br><br>
        
        <span>-奖励发放：</span><br>
         中奖后将截图+金贝增平台账号+姓名+电话，发至金贝增公众号，6月19日——6月21日陆续将优惠券发放至中奖用户的金贝增账号； 
      </dd>
    </dl>
  </div> 
  <div class="main-6">
    <dl>
      <dd>&nbsp;</dd>
    </dl>
  </div> 
</div>
  <script type="text/javascript">
    var lottery = {
      index: -1, //当前转动到哪个位置，起点位置
      count: 0, //总共有多少个位置
      timer: 0, //setTimeout的ID，用clearTimeout清除
      speed: 30, //初始转动速度
      times: 0, //转动次数
      cycle: 50, //转动基本次数：即至少需要转动多少次再进入抽奖环节
      prize: -1, //中奖位置
      init: function(id) {
        if (jQuery("#" + id).find(".lottery-unit").length > 0) {
          $lottery = jQuery("#" + id);
          $units = $lottery.find(".lottery-unit");
          this.obj = $lottery;
          this.count = $units.length;
          $lottery.find(".lottery-unit-" + this.index).addClass("active");
        }
      },
      roll: function() {
        var index = this.index;
        var count = this.count;
        var lottery = this.obj;        
        jQuery(lottery).find(".lottery-unit-" + index).removeClass("active");
        index += 1;
        if (index > count-1) {
          index = 0;
        }
        jQuery(lottery).find(".lottery-unit-" + index).addClass("active");
        this.index = index;
        return false;
        },
      stop: function(index) {
          this.prize = index;
          return false;
        }
      };
      function roll() {
        clearTimeout(lottery.timer);
        lottery.times += 1;
        lottery.roll();
        var prize_site = jQuery("#lottery").attr("prize_site");
        if (lottery.times > lottery.cycle + 10 && lottery.index == prize_site) {
          var prize_id = jQuery("#lottery").attr("prize_id");
          var prize_name = jQuery("#lottery").attr("prize_name");
          var points = jQuery("#lottery").attr("points");
          clearTimeout(lottery.timer);
          lottery.prize = 0;
          lottery.times = 0;
          click = false;
          setTimeout(function(){alert("\n抽奖结果："+prize_name)},lottery.timer);
        } else {
          if (lottery.times < lottery.cycle) {
            lottery.speed -= 10;
          } else if (lottery.times == lottery.cycle) {
            var index = Math.random() * (lottery.count) | 0;
            lottery.prize = index;
          } else {
            if (lottery.times > lottery.cycle + 10 && ((lottery.prize == 0 && lottery.index == 7) || lottery.prize == lottery.index + 1)) {
              lottery.speed += 110;
            } else {
              lottery.speed += 20;
            }
          }
          if (lottery.speed < 40) {
            lottery.speed = 40;
          }
          lottery.timer = setTimeout(roll, lottery.speed);
        }
        
        return false;
      }
      var click = false;
      
      jQuery(document).ready(function($) {
        lottery.init('lottery');
        jQuery("#lottery a").click(function() {
          if (click) {
            return false;
          } else {
            lottery.speed = 100;
            jQuery.post("/cowpro/zongzi_ajax", {uid: 1}, function(data) { //获取奖品，也可以在这里判断是否登陆状态
                console.log(data);
              if( !data.err_msg ) {
                $("#lottery").attr("prize_site", data.prize_site);
                $("#lottery").attr("prize_id", data.prize_id);
                $("#lottery").attr("prize_name", data.prize_name);
                $("#lottery").attr("points", data.points);
                roll();
                click = true;
                return false;
              }else{
                alert(data.err_msg);
              }
            }, "json");
          }
        });
      })
    </script>