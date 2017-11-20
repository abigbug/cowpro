  <style type="text/css">
    #lottery{width:684px;height:684px;margin:20px auto;background:url(/sites/all/modules/cowpro/modules/raffle/images/bg.jpg) no-repeat;padding:50px 55px;}
    #lottery table td{width:142px;height:142px;text-align:center;vertical-align:middle;font-size:24px;color:#333;font-index:-999}
    #lottery table td a{width:284px;height:284px;line-height:150px;display:block;text-decoration:none;}
    #lottery table td.active{background-color:#ea0000;}
  </style>
  <div id="lottery">
    <table border="0" cellpadding="0" cellspacing="0">
      <tr>
        <td class="lottery-unit lottery-unit-0"><img src="<?php echo $GLOBALS['base_url'] . '/' . drupal_get_path('module', 'cowpro_raffle') . '/images/1.png'; ?>"></td>
        <td class="lottery-unit lottery-unit-1"><img src="<?php echo $GLOBALS['base_url'] . '/' . drupal_get_path('module', 'cowpro_raffle') . '/images/2.png'; ?>"></td>
        <td class="lottery-unit lottery-unit-2"><img src="<?php echo $GLOBALS['base_url'] . '/' . drupal_get_path('module', 'cowpro_raffle') . '/images/8.png'; ?>"></td>
        <td class="lottery-unit lottery-unit-3"><img src="<?php echo $GLOBALS['base_url'] . '/' . drupal_get_path('module', 'cowpro_raffle') . '/images/3.png'; ?>"></td>
      </tr>
      <tr>
        <td class="lottery-unit lottery-unit-11"><img src="<?php echo $GLOBALS['base_url'] . '/' . drupal_get_path('module', 'cowpro_raffle') . '/images/8.png'; ?>"></td>
        <td colspan="2" rowspan="2"><a href="javascript:void(0);"></a></td>
        <td class="lottery-unit lottery-unit-4"><img src="<?php echo $GLOBALS['base_url'] . '/' . drupal_get_path('module', 'cowpro_raffle') . '/images/4.png'; ?>"></td>
      </tr>
      <tr>
        <td class="lottery-unit lottery-unit-10"><img src="<?php echo $GLOBALS['base_url'] . '/' . drupal_get_path('module', 'cowpro_raffle') . '/images/4.png'; ?>"></td>
        <td class="lottery-unit lottery-unit-5"><img src="<?php echo $GLOBALS['base_url'] . '/' . drupal_get_path('module', 'cowpro_raffle') . '/images/8.png'; ?>"></td>
      </tr>
      <tr>
        <td class="lottery-unit lottery-unit-9"><img src="<?php echo $GLOBALS['base_url'] . '/' . drupal_get_path('module', 'cowpro_raffle') . '/images/7.png'; ?>"></td>
        <td class="lottery-unit lottery-unit-8"><img src="<?php echo $GLOBALS['base_url'] . '/' . drupal_get_path('module', 'cowpro_raffle') . '/images/8.png'; ?>"></td>
        <td class="lottery-unit lottery-unit-7"><img src="<?php echo $GLOBALS['base_url'] . '/' . drupal_get_path('module', 'cowpro_raffle') . '/images/6.png'; ?>"></td>
        <td class="lottery-unit lottery-unit-6"><img src="<?php echo $GLOBALS['base_url'] . '/' . drupal_get_path('module', 'cowpro_raffle') . '/images/5.png'; ?>"></td>
      </tr>
    </table>
  </div>
  <div style="width: 80%; margin: 0px auto;">
    <table>
      <tr><td><font color="#FF0308">抽奖规则介绍：</font></td></tr>
      <tr><td>1、登录金贝增账户，满足积分抽奖条件即可参与抽奖；</td></tr>
      <tr><td>2、每次抽奖将消耗15积分，每天不限抽奖次数，多次参与可提高中奖机率；</td></tr>
      <tr><td>3、点击开始抽奖，消耗相应积分，抽奖结果以弹出提示及最终红框选中为准；</td></tr>
      <tr><td>4、中奖奖品将自动存至抽奖账户，抽奖记录可前往<a href="<?php echo $GLOBALS['base_url'] . '/myuserpoints'; ?>" target="_blank"><font color="#FF0308">个人积分交易</font></a>进行查询；</td></tr>
      <tr><td><br></td></tr>
      <tr><td><font color="#FF0308">奖品使用条件：</font></td></tr>
      <tr><td>1、中奖积分将存入积分总数，可用作商城兑换商品或积分抽奖；</td></tr>
      <tr><td>2、10元投资抵用券，7天有效期，单笔投资满10000可使用；</td></tr>
      <tr><td>3、30元投资抵用券，7天有效期，单笔投资满20000可使用；</td></tr>
      <tr><td>4、40元投资抵用券，7天有效期，单笔投资满30000可使用；</td></tr>
      <tr><td>5、100元投资抵用券，7天有效期，单笔投资满50000可使用；</td></tr>
      <tr><td><br></td></tr>
      <tr><td><font color="#FF0308">关于解释权：</font></td></tr>
      <tr><td>本免责声明以及其修改权、更新权及最终解释权均属金贝增。</td></tr>

    </table>  
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
          clearTimeout(lottery.timer);
          lottery.prize = 0;
          lottery.times = 0;
          click = false;
          setTimeout(function(){alert("\n抽奖结果："+prize_name+"\n")},lottery.timer);
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
            jQuery.post("/cowpro/raffle_ajax", {uid: 1}, function(data) { //获取奖品，也可以在这里判断是否登陆状态
                console.log(data);
              if( !data.err_msg ) {
                $("#lottery").attr("prize_site", data.prize_site);
                $("#lottery").attr("prize_id", data.prize_id);
                $("#lottery").attr("prize_name", data.prize_name);
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