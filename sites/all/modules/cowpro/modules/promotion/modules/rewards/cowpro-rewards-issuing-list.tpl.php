<?php

/**
 * @file
 * Default theme implementation for rendering 标的奖励列表
 *
 * Available variables:
 * - $journal_list: 标的奖励列表
 *
 * @ingroup themeable
 */
?>
    <div class="view-content">
      <table class="views-table cols-3">
         <thead>
      <tr>
                  <th class="views-field views-field-lender-time" scope="col">
            用户名          </th>
                  <th class="views-field views-field-lender" scope="col">
            奖励类型          </th>
                  <th class="views-field views-field-lender-amount" scope="col">
            奖励金额          </th>
                  <th class="views-field views-field-lender-amount" scope="col">
            奖励时间          </th>
              </tr>
    </thead>
    <tbody>
    <?php
    $count = 0;
    foreach ($journal_list as $journal):
    $count ++;
    ?>

          <tr class="<?php if ($count%2) {echo 'odd';} else {echo 'even';}?>">
                  <td class="views-field views-field-lender-name">
                    <?php print $journal->nick_name; ?>(<?php print $journal->real_name; ?>)          
                  </td>
                  <td class="views-field views-field-lender_type">
                    <?php print $journal->type; ?>  
                  </td>
                  <td class="views-field views-field-lender-amount">
                    <?php print $journal->points; ?>          
                  </td>
                  <td class="views-field views-field-lender-time">
                    <?php print $journal->created; ?>          
                  </td>
              </tr>
    <?php endforeach; ?>
      </tbody>
</table>
    </div>