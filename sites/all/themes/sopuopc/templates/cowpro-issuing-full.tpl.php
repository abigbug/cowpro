
<div class="particular_center clearfix container-fluid">
  <div class="row">
    <div class="particular_center_l col-md-9">
      <h2 class="the-title clearfix"> <?php print $title; ?> <span class="details_id hidden"></span> </h2>
      <div class=" clearfix details-all">
        <div class="row">
          <div class="col-md-4 the-nianhua"> <span class="num-info">
            <ss class="num-family" style="margin-top:8px;" id="loanYearRate"><?php print $annual_rate; ?></ss>
            </span>
            <p class="text-info">预期年化收益率(%)</p>
          </div>
          <div class="col-md-4 the-qixian"> <span class="num-info"><?php print $loan_term_readable; ?> </span>
            <p class="text-info">投资期限(天)</p>
          </div>
          <div class="col-md-4 the-jine"> <span class="num-info"> <?php print $bid_avail; ?></span>
            <p class="text-info">可投资金额(元)</p>
          </div>
        </div>
      </div>
      <div class="clearfix details-list-all">
        <div class="clearfix the-one row">
          <div class="col-md-4">第一还款源：<span class="the-post2017"><?php print theme('username', array('account' => $applicant)); ?></span></div>
          <div class="col-md-4">融资金额:<span class="the-post2017"><font id="appAmount"><?php print $loan_amounts; ?></font>元</span></div>
          <div class="col-md-4 join">融资进度： <span class="chart_1"><?php print $progress; ?>%</span> <span class="chart_bar">
            <ul class="barbox">
              <li class="barline">
                <div w="100" style="width: <?php print $progress; ?>%;" class="charts"></div>
              </li>
            </ul>
            </span></div>
        </div>
        <div class="clearfix the-two row">
          <div class="col-md-4">计息结束日：<span class="the-post2017"><?php print $interest_period; ?></span></div>
          <div class="col-md-4">还款方式：<span class="the-post2017"><?php print $method_repayment_readable; ?></span></div>
          <div class="col-md-4">贷款状态：
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
		$issuing_text2017 = '末审核';
		break;
	case 'AUDITED':
		$class = 'audited_pic';
		$issuing_text2017 = '审核通过';
		break;
	case 'INVITE_BIDS_START':
		$class = 'bidding_pic';
		$issuing_text2017 = '正在投标';
		break;
	case 'INVITE_BIDS_FAILED':
		$class = 'failed_pic';
		$issuing_text2017 = '流标';
		break;
	case 'INVITE_BIDS_SUCCEED':
		$class = 'saleout_pic';
		$issuing_text2017 = '满标，等待放款';
		break;
	case 'REPAYMENT':
		$class = 'repayment_pic';
		$issuing_text2017 = '等待还款';
		break;
	case 'FINISHED':
		$class = 'finished_pic';
		$issuing_text2017 = '还款完毕';
		break;
	default:
		$class = 'undefined_pic';
		$issuing_text2017 = '末审核';
		break;
}
print "<span class=\"issuing-status $class\">".$issuing_text2017 ."</span>";
?>
          </div>
        </div>
        
        
        
      </div>
    </div>
    
    <!-------------------------- 条件语句     --------------------------------> 
    
    <!------------------------ 可投资 ------------------------>
    <div class="particular_center_r col-md-3">
    
     <div class="details_links clearfix"> <?php print $operations; ?> </div>
     </div>
  </div>
</div>

