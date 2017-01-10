<?php

/**
 * @file
 * Default theme implementation for rendering 投资人列表
 *
 * Available variables:
 * - $journal_list: 用户投标日记账列表
 *
 * @ingroup themeable
 */
?>
    <div class="view-content">
      <table class="views-table cols-3">
         <thead>
      <tr>
                  <th class="views-field views-field-lender" scope="col">
            投资人          </th>
                  <th class="views-field views-field-lender-time" scope="col">
            投资时间          </th>
                  <th class="views-field views-field-lender-amount" scope="col">
            投资金额（元）          </th>
              </tr>
    </thead>
    <tbody>
    <?php
    $count = 0;
    $maskit = TRUE;
    global $user;
    $role = user_role_load_by_name('manager');
    if (user_has_role($role->rid, $user)) {
    	$maskit = FALSE;
    }
    foreach ($journal_list as $journal):
    $journal_user = user_load($journal->uid);
    $count ++;
    ?>

          <tr class="<?php if ($count%2) {echo 'odd';} else {echo 'even';}?>">
                  <td class="views-field views-field-lender">
            <?php
            if ($maskit && $user->uid != $journal_user->uid) {
	            if (mb_strlen($journal_user->name) < 11) {
	            	print mb_substr($journal_user->name, 0, 2) . '***';
	            } else {
	            	print mb_substr($journal_user->name, 0, 4) . '****' . mb_substr($journal_user->name, -3, 3);
	            }
			} else {
				print $journal_user->name;
			}
			?>          </td>
                  <td class="views-field views-field-lender-time">
            <?php print date('Y/m/d H:i', $journal->created); ?>          </td>
                  <td class="views-field views-field-lender-amount">
            <?php print $journal->amount; ?>          </td>
              </tr>
    <?php endforeach; ?>
      </tbody>
</table>
    </div>