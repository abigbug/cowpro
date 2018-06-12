<?php
   /**
    * @file
    * Default theme implementation for rendering 贷款申请表的部分项目
    *
    * Available variables:
    * - $title: 贷款标题
    * - $issuing_id: 贷款编号
    * - $applicant: 贷款人(user object)
    * - $loan_amounts: 贷款总额(元)
    * - $bid_avail： 可投标金额
    * - $status： 贷款申请表的状态
    * - $status_readable：显示给用户的、具有可读性的“状态”
    * - $loan_term：贷款期限(天)
    * - $loan_term_readable：显示给用户的、具有可读性的“贷款期限”
    * - $method_repayment：还款方式
    * - $method_repayment_readable：显示给用户的、具有可读性的“还款方式”
    * - $annual_rate：年利率（实际计算的时候，需要除以100）
    * - $created：提交贷款申请的时间（unixtimestamp）
    * - $start：开始投标的时间（unixtimestamp）
    * - $make_loans_time：开始记息（放款）的时间（unixtimestamp）
    * - $deadline：投标期（天）
    * - $progress:进度（%）
    * - $links:当前用户可以对当前issuing可以进行的操作，以链接形式存储在数组中，数组里的每一项是一个link
    */
   ?>

<div class="details" style="margin: 0 auto">
   <div class="details_links">
   <?php print $operations; ?>
   </div>
   <div class="details_title">
      <span class="details_name"><?php print $title; ?></span> <span
         class="details_id"><?php print $issuing_id; ?></span>
   </div>
   <div class="details_main">
	   <div class="details_block-1">
         <table>
            <tbody>
               <tr>
                  <td class="details_money"><font style="margin-top: 8px;"
                     class="num-family" id="appAmount"><?php print $loan_amounts; ?></font><span>元</span></td>
                  <td class="details_count">
                     <font class="num-family" style="margin-top: 8px;">
                        <ss class="num-family" style="margin-top:8px;" id="loanYearRate"><?php print $annual_rate; ?></ss>
                     </font>
                     <span>%</span>
                  </td>
                  <td class="details_time"><font class="num-family"><?php print $loan_term_readable; ?></font>
                  </td>
               </tr>
               <tr>
                  <td class="details_tex">计划金额</td>
                  <td class="details_tex">预期年收益</td>
                  <td class="details_tex">理财期限</td>
               </tr>
            </tbody>
         </table>
	   </div>
	   <div class="details_block-2">
      <div class="details_left">
         <div class="details_words">
            <ul class="bidAmount">
               <li class="repayment">借款人<span>
               <?php
               $maskit = TRUE;
               global $user;
               $account = $applicant;
               if ($maskit && $user->uid != $applicant->uid) {
               	if (mb_strlen($applicant->name) < 11) {
               		$account->name = mb_substr($applicant->name, 0, 2) . '***';
               	} else {
               		$account->name = mb_substr($applicant->name, 0, 4) . '****' . mb_substr($applicant->name, -3, 3);
               	}
               }
               print theme('username', array('account' => $account)); ?>
               </span></li>
               <li class="safeguard">保障方式<span>本金+利息</span></li>
               <li class="repayment">还款方式<span><?php print $method_repayment_readable; ?></span></li>
               <li class="join">
                  加入进度 <span class="chart_1"><?php print $progress; ?>%</span>
                  <span class="chart_bar">
                     <ul class="barbox">
                        <li class="barline">
                           <div w="100" style="width: <?php print $progress; ?>%;" class="charts"></div>
                        </li>
                     </ul>
                  </span>
               </li>
            </ul>
         </div>
      </div>
      <!--贷款状态开始-->
      <div class="details_right">
<?php
/*
UNAUDITED:贷款人填写《贷款申请表》，末审核;
AUDITED:审核通过;
INVITE_BIDS_START:正在投标;
INVITE_BIDS_FAILED:流标;
INVITE_BIDS_SUCCEED:满标，等待放款;
REPAYMENT:等待还款;
FINISHED:还款完毕
*/
switch ($status) {
	case 'UNAUDITED':
		$class = 'unaudited_pic';
		break;
	case 'AUDITED':
		$class = 'audited_pic';
		break;
	case 'INVITE_BIDS_START':
		$class = 'bidding_pic';
		break;
	case 'INVITE_BIDS_FAILED':
		$class = 'failed_pic';
		break;
	case 'INVITE_BIDS_SUCCEED':
		$class = 'saleout_pic';
		break;
	case 'REPAYMENT':
		$class = 'repayment_pic';
		break;
	case 'FINISHED':
		$class = 'finished_pic';
		break;
	default:
		$class = 'undefined_pic';
		break;
}
print "<ul><li class=\"issuing-status $class\"></li></ul>";
?>
      </div>
	   </div>
      <!--贷款状态结束-->
   </div>
</div>
<div class="clearfix"></div>
<div class="details issuing-plan">
   <div class="details_title">
      <span class="details_name">计划进度</span>
   </div>
	<div class="item-list">
		<ul>
			<li class="views-row">
				<div class="views-field views-field-field-slide-icon">
					<div class="field-content">
						<span class="icon-span flaticon-circular152"></span>
					</div>
          <div class="issuing-plan-label">
	          <p> 计划发布</p>
            <p><?php print date("Y-m-d", $created); ?></p>
          </div>
				</div>
			</li>
			<li class="views-row">
				<div class="views-field views-field-field-slide-icon">
					<div class="field-content">
						<span class="icon-span flaticon-persons8"></span>
					</div>
          <div class="issuing-plan-label">
	          <p>开始投资</p>
            <p><?php print date("Y-m-d", $start); ?></p>
          </div>
				</div>
			</li>
			<li class="views-row">
				<div class="views-field views-field-field-slide-icon">
					<div class="field-content">
						<span class="icon-span flaticon-ascending7"></span>
					</div>
          <div class="issuing-plan-label">
	          <p>开始计息</p>
            <p><?php print date("Y-m-d", $make_loans_time); ?></p>
          </div>
				</div>
			</li>
			<li class="views-row">
				<div class="views-field views-field-field-slide-icon">
					<div class="field-content">
						<span class="icon-span flaticon-trophy17"></span>
					</div>
          <div class="issuing-plan-label">
	          <p>投资到期</p>
            <p><?php print date("Y-m-d", $make_loans_time + $loan_term * 24 * 60 * 60); ?></p>
          </div>
				</div>
			</li>
    </ul>
  </div>

</div>
<div class="clearfix"></div>
