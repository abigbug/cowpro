<h2>当前推广活动列表</h2>
<ul>

<?php foreach ($promotion_info_list as $info): ?>
    <li class=""><span><?php print $row['name'];?></span>&nbsp;&nbsp;&nbsp;&nbsp;<span>奖金：<?php print $row['amount'];?>元</span>&nbsp;&nbsp;&nbsp;&nbsp;<span>代金券：<?php print $row['voucher'];?>元</span></li>
 <?php endforeach; ?>
</ul>

