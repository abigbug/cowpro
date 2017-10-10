<?php if ($is_permissions) :?>
    <?php if ($winning['id']==1) :?>
    <p style="width: 90%;margin: 0px auto;text-align: center;"><img src="<?php echo $GLOBALS['base_url'] . '/' . drupal_get_path('module', 'cowpro_draw') . '/images/jf-20.png'; ?>"></p>
    <?php endif; ?>
    <?php if ($winning['id']==2) :?>
    <p style="width: 90%;margin: 0px auto;text-align: center;"><img src="<?php echo $GLOBALS['base_url'] . '/' . drupal_get_path('module', 'cowpro_draw') . '/images/jf-50.png'; ?>"></p>
    <?php endif; ?>
    <?php if ($winning['id']==3) :?>
    <p style="width: 90%;margin: 0px auto;text-align: center;"><img src="<?php echo $GLOBALS['base_url'] . '/' . drupal_get_path('module', 'cowpro_draw') . '/images/jf-100.png'; ?>"></p>
    <?php endif; ?>
    <?php if ($winning['id']==4) :?>
    <p style="width: 90%;margin: 0px auto;text-align: center;"><img src="<?php echo $GLOBALS['base_url'] . '/' . drupal_get_path('module', 'cowpro_draw') . '/images/djq-20.png'; ?>"></p>
    <?php endif; ?>
    <?php if ($winning['id']==5) :?>
    <p style="width: 90%;margin: 0px auto;text-align: center;"><img src="<?php echo $GLOBALS['base_url'] . '/' . drupal_get_path('module', 'cowpro_draw') . '/images/djq-50.png'; ?>"></p>
    <?php endif; ?>
    <?php if ($winning['id']==6) :?>
    <p style="width: 90%;margin: 0px auto;text-align: center;"><img src="<?php echo $GLOBALS['base_url'] . '/' . drupal_get_path('module', 'cowpro_draw') . '/images/djq-100.png'; ?>"></p>
    <?php endif; ?>
    <?php if ($winning['id']==7) :?>
    <p style="width: 90%;margin: 0px auto;text-align: center;">您没有中奖，谢谢参与！</p>
    <?php endif; ?>
<?php else:?>
    <p>您没有获得抽奖的资格，投资满足年化10000即可抽奖！</p>
<?php endif; ?>

<p style="width: 100%; padding-top: 50px; margin: 0px auto; text-align:center;"><input type="button" name="back" value="返 回" onclick="javascript:history.back(-1);"></p>