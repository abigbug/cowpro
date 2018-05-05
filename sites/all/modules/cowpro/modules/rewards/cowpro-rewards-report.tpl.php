<style type="text/css">
.gridtable {
    font-family: verdana,arial,sans-serif;
    font-size:14px;
    color:#333333;
    margin: 0px auto;
    height: 40px;
    line-height: 40px;
    width: 60%;
}
.gridtable_tit {
    float: left;
    width: 30%;
 }
.gridtable_right {
    float: right;
    width: 60%;
}
.order_c{
    border: 0.5px dashed #999999;
    margin-bottom: 20px;
    margin-top: 20px;
}
.g_title{
    font-size: 18px;
    width: 80%;
}
.gridtable_tid{
    float: left;
    width: 20%;
}
.gridtable_1{
    font-family: verdana,arial,sans-serif;
    font-size:14px;
    color:#333333;
    margin: 0px auto;
    height: 40px;
    line-height: 40px;
    width: 60%;
}
</style>

<div class="gridtable" style="font-size:16px;"><b>平台整体运营数据</b></div>
<div class="gridtable">
    <div class="gridtable_tit">平台借出总额</div><div class="gridtable_right"><?php echo number_format($result['lend_total'],2);?></div>
</div>
<div class="gridtable">
    <div class="gridtable_tit">已还利息总额</div><div class="gridtable_right"><?php echo number_format($result['interest_paid_total'],2);?></div>
</div>
<div class="gridtable">
    <div class="gridtable_tit">已还总额(本金加利息)</div><div class="gridtable_right"><?php echo number_format($result['paid_total'],2);?></div>
</div>
<div class="gridtable">
    <div class="gridtable_tit">待还总额(本金加利息)</div><div class="gridtable_right"><?php echo number_format($result['wait_paid_total'],2);?></div>
</div>
<div class="gridtable">
    <div class="gridtable_tit">所有待还本金</div><div class="gridtable_right"><?php echo number_format($result['all_total_capital'],2);?></div>
</div>
<div class="gridtable">
    <div class="gridtable_tit">所有待还利息</div><div class="gridtable_right"><?php echo number_format($result['all_total_interest'],2);?></div>
</div>
<div class="gridtable">
    <div class="gridtable_tit">会员总人数</div><div class="gridtable_right"><?php echo number_format($result['user_total'],2);?></div>
</div>
<div class="gridtable">
    <div class="gridtable_tit">已投资会员数</div><div class="gridtable_right"><?php echo number_format($result['user_bid_total'],2);?></div>
</div>
<div class="gridtable">
    <div class="gridtable_tit">在投用户数</div><div class="gridtable_right"><?php echo number_format($result['user_biding_total'],2);?></div>
</div>

<div class="order_c"></div>

<div class="gridtable" style="font-size:16px;"><b>平台资金到期数据</b></div>

<div class="gridtable">
    <div class="gridtable_tit">本月到期本金</div><div class="gridtable_right"><?php echo $result['month_capital_total'] ? number_format($result['month_capital_total'],2) : 0;?></div>
</div>
<div class="gridtable">
    <div class="gridtable_tit">本月到期利息</div><div class="gridtable_right"><?php echo $result['month_revenus_total'] ? number_format($result['month_revenus_total'],2) : 0;?></div>
</div>
<div class="gridtable">
    <div class="gridtable_tit">本月到期总额</div><div class="gridtable_right"><?php echo $result['month_total'] ? number_format($result['month_total'],2) : 0;?></div>
</div>
<div class="gridtable">
    <div class="gridtable_tit">今日到期本金</div><div class="gridtable_right"><?php echo $result['day_capital_total'] ? number_format($result['day_capital_total'],2) : 0;?></div>
</div>
<div class="gridtable">
    <div class="gridtable_tit">今日到期利息</div><div class="gridtable_right"><?php echo $result['day_revenus_total'] ? number_format($result['day_revenus_total'],2) : 0;?></div>
</div>
<div class="gridtable">
    <div class="gridtable_tit">今日到期总额</div><div class="gridtable_right"><?php echo $result['day_total'] ? number_format($result['day_total'],2) : 0;?></div>
</div>

<div class="order_c"></div>

<div class="gridtable" style="font-size:16px;"><b>今日投标数据</b></div>
<div class="gridtable">
    <div class="gridtable_tit">今日投标总额</div><div class="gridtable_right"><?php echo $result['day_total_bid'] ? number_format($result['day_total_bid'],2) : 0;?></div>
</div>

<div class="gridtable">
    <div class="gridtable_tit">今日3个月投标总额</div><div class="gridtable_right"><?php echo $result['day_total_bid_3'] ? number_format($result['day_total_bid_3'],2) : 0;?></div>
</div>

<div class="gridtable">
    <div class="gridtable_tit">今日6个月投标总额</div><div class="gridtable_right"><?php echo $result['day_total_bid_6'] ? number_format($result['day_total_bid_6'],2) : 0;?></div>
</div>

<div class="gridtable">
    <div class="gridtable_tit">今日12个月投标总额</div><div class="gridtable_right"><?php echo $result['day_total_bid_12'] ? number_format($result['day_total_bid_12'],2) : 0;?></div>
</div>

<div class="order_c"></div>

<div class="gridtable" style="font-size:16px;"><b>平台充值数据</b></div>

<div class="gridtable">
    <div class="gridtable_tit">今日投资人充值</div><div class="gridtable_right"><?php echo $result['lender_topup'] ? number_format($result['lender_topup'],2) : 0;?></div>
</div>
<div class="gridtable">
    <div class="gridtable_tit">今日融资人充值</div><div class="gridtable_right"><?php echo $result['debtor_topup'] ? number_format($result['debtor_topup'],2) : 0;?></div>
</div>
<div class="gridtable">
    <div class="gridtable_tit">今日客户充值总额</div><div class="gridtable_right"><?php echo $result['users_topup'] ? number_format($result['users_topup'],2) : 0;?></div>
</div>


<div class="order_c"></div>

<div class="gridtable" style="font-size:16px;"><b>平台提现数据</b></div>
<div class="gridtable">
    <div class="gridtable_tit">今日投资人提现</div><div class="gridtable_right"><?php echo $result['lender_withdraw'] ? number_format($result['lender_withdraw'],2) : 0;?></div>
</div>
<div class="gridtable">
    <div class="gridtable_tit">今日融资人提现</div><div class="gridtable_right"><?php echo $result['debtor_withdraw'] ? number_format($result['debtor_withdraw'],2) : 0;?></div>
</div>
<div class="gridtable">
    <div class="gridtable_tit">今日客户提现总额</div><div class="gridtable_right"><?php echo $result['users_withdraw'] ? number_format($result['users_withdraw'],2) : 0;?></div>
</div>

<div class="order_c"></div>

<div class="gridtable" style="font-size:16px;"><b style="float:left; height:40px;margin-right:20px;padding-top: 6px">融资人余额明细</b><?php echo $result['output_html'];?></div>
 <div class="gridtable">
        <div class="gridtable_tit">融资人账号总余额</div><div class="gridtable_right">
            
            <?php echo $result['debtor_total_balance'] ? number_format($result['debtor_total_balance'],2) : 0;?></div>
    </div>
<div class="gridtable_1"> 
    <div class="gridtable_tid">融资人昵称</div><div class="gridtable_tid">融资人姓名</div><div class="gridtable_tid">账户余额</div>
</div>
<?php foreach( $result['debtor_total_balance_list'] as $value ) {?>
<div class="gridtable_1">
    <div class="gridtable_tid"><?php echo $value->nickname; ?></div><div class="gridtable_tid"><?php echo $value->name; ?></div><div class="gridtable_tid"><?php echo number_format($value->balance,2); ?></div>
</div>
<?php } 

