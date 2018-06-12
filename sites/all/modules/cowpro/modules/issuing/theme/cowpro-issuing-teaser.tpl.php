<?php

/**
 * @file
 * Default theme implementation for rendering loan-amounts
 *
 * Available variables:
 * - $loan_amounts: 贷款总额(元)
 * - $bid_avail： 可投标金额
 * - $status： 贷款申请表的状态
 * - $status_readable：显示给用户的、具有可读性的“状态”
 * - $loan_term：贷款期限
 * - $loan_term_readable：显示给用户的、具有可读性的“贷款期限”
 * - $annual_rate：年利率（实际计算的时候，需要除以100）
 *
 * @ingroup themeable
 */
?>
  <div class="cowpro-issuing-item">
    贷款总额:<?php print $loan_amounts; ?>元
  </div>
  <div class="cowpro-issuing-item">
     可投标金额:<?php print $bid_avail; ?>元
  </div>
  <div class="cowpro-issuing-item">
    <?php print $status_readable; ?>
  </div>
  <div class="cowpro-issuing-item">
    贷款期限:<?php print $loan_term_readable; ?>
  </div>
  <div class="cowpro-issuing-item">
    年利率:<?php print $annual_rate; ?>%
  </div>
