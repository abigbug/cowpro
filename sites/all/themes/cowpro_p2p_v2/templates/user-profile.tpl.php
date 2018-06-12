<?php

/**
 * @file
 * Default theme implementation to present all user profile data.
 *
 * This template is used when viewing a registered member's profile page,
 * e.g., example.com/user/123. 123 being the users ID.
 *
 * Use render($user_profile) to print all profile items, or print a subset
 * such as render($user_profile['user_picture']). Always call
 * render($user_profile) at the end in order to print all remaining items. If
 * the item is a category, it will contain all its profile items. By default,
 * $user_profile['summary'] is provided, which contains data on the user's
 * history. Other data can be included by modules. $user_profile['user_picture']
 * is available for showing the account picture.
 *
 * Available variables:
 *   - $user_profile: An array of profile items. Use render() to print them.
 *   - Field variables: for each field instance attached to the user a
 *     corresponding variable is defined; e.g., $account->field_example has a
 *     variable $field_example defined. When needing to access a field's raw
 *     values, developers/themers are strongly encouraged to use these
 *     variables. Otherwise they will have to explicitly specify the desired
 *     field language, e.g. $account->field_example['en'], thus overriding any
 *     language negotiation rule that was previously applied.
 *
 * @see user-profile-category.tpl.php
 *   Where the html is handled for the group.
 * @see user-profile-item.tpl.php
 *   Where the html is handled for each item in the group.
 * @see template_preprocess_user_profile()
 *
 * @ingroup themeable
 */
?> 
  <?php
       global $base_url;
       global $user;
       $points = userpoints_get_current_points($user->uid);
       $username = @$user->name;
  ?>
        <div class="member_info Jmember_info" id="info_blue_center">
          <!-- 蓝色信息部分 -->
          <div class="info_blue">    
            <div style="padding-top: 25px; padding-left: 15px; padding-right: 25px;">    
              <div class="ui-notlogin">        
                <div class="cell-user"><a href="<?php global $base_url; print $base_url;?>/registration_wizard"><i class="icon-user-av">&nbsp;</i></a></div>        
                <div class="cell-user">
                  <a href="<?php global $base_url; print $base_url;?>/registration_wizard" class="arrow-user">
                    <dl>
                      <dd><?php echo $username;?></dd>                              
                    </dl>            
                  </a>        
                </div>    
              </div>
            </div>    
            <div class="ui-clear"></div>
            <div style="padding:0 10px; margin-bottom: 20px;">    
              <div class="info-user-bot" style="padding-top: 10px;">        
                <div class="user-cell Jlink">            
                  <dl class="has-line">                
                    <dd><label class="icon-small icon-small-2">待收本息(元)</label><em id="changeAssets" class="icon-eye"></em></dd>                
                    <dd><strong class="user-total x-amount x-amount-zi1"><?php echo $user_profile['debtor']['debtor_4']['#markup']?></strong></dd>            
                  </dl>        
                </div>  
                <div class="user-cell Jlink">            
                  <dl>                
                    <dd><label class="icon-small icon-small-1">已收本息(元)</label></dd>                
                    <dd><strong class="x-amount x-amount-ji1"><?php echo $user_profile['debtor']['debtor_3']['#markup']?></strong></dd>            
                  </dl>        
                </div>
              </div>
            </div>
            <div class="safe-text"><span id="safe">账户受宜宾市商业银行保护</span></div>
          </div><!-- 充值提现 -->
          <div class="recharge_cash">    
            <div style="margin: 0 27px;">        
              <ul>                  
                  <li id="popBox_tx" data-state="2" class="icon-sp"><a href="<?php global $base_url; print $base_url;?>/cowpro/fund/withdraw"><span class="cash-label" style="float: left;"><i class="icon-cash-1"></i>提现</span></a></li>           
                  <li id="popBox" data-state="2"><a href="<?php global $base_url; print $base_url;?>/cowpro/fund/topup"><span class="cash-label"><i class="icon-cash-2"></i>充值</span><label class="cash-text">免手续费</label></a></li>               
              </ul>    
            </div>
          </div><!-- 个人信息列表 -->    
          <div class="info_list" id="info_list">        
            <ul>                
              <li onmouseover="this.style.cursor='pointer'" class="balance_li">
                <span class="info-right"><?php if(empty($user_profile['fund']['fund_2'])){ ?><font style="line-height:45px;"><?php echo $user_profile['fund']['fund_1']['#markup']?>元</font><?php }else{?><div class="balance_right"><?php echo $user_profile['fund']['fund_1']['#markup']?>元<br><font style="font-size: 12px; color: #C9C5C5;"><?php echo $user_profile['fund']['fund_2']['#markup']?></font></div><?php }?><i></i></span>
                <span class="info-left null_1">可用余额</span>
              </li>                
              <li onmouseover="this.style.cursor='pointer'" onclick="document.location='<?php print $base_url;?>/issuing-list/bid';">                    
                <span class="info-right"><?php echo $user_profile['debtor']['debtor_2']['#markup']?>笔<i></i></span>
                <span class="info-left null_2">我的投资</span>
              </li>   
              <li onmouseover="this.style.cursor='pointer'" onclick="document.location='<?php print $base_url;?>/issuing-list/lender-due-in';">                
                <span class="info-right"><i></i></span>                
                <span class="info-left null_3">待收明细</span>      
              </li>            
              <li class="current" onmouseover="this.style.cursor='pointer'" onclick="document.location='<?php print $base_url;?>/cowpro/fund';">
                <span class="info-right"><i></i></span>                    
                <span class="info-left null_jiao">资金记录</span>                
              </li>        
            </ul>
            <ul>
              <li onmouseover="this.style.cursor='pointer'" onclick="document.location='<?php print $base_url;?>/user/<?php print $user->uid ;?>/points';">                
                <span class="info-right"><?php print $points;?><i></i></span>                
                <span class="info-left null_ji">我的积分</span>        
              </li>
              <li onmouseover="this.style.cursor='pointer'" onclick="document.location='<?php print $base_url;?>/registration_wizard';">                
                <span class="info-right"><i></i></span>                
                <span class="info-left null_5">安全中心</span>            
              </li>                     
              <li onmouseover="this.style.cursor='pointer'" onclick="document.location='<?php print $base_url;?>/node/2717';">                
                <span class="info-right">信息披露<i></i></span>                
                <span class="info-left null_7">更多</span>            
              </li>       
            </ul>    
          </div>    
          <!--底部导航-->
          <div class="Jbottomnavs index-about-white"></div>
        </div>