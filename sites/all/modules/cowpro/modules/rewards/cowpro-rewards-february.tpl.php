<h2>一级奖励推荐列表</h2>
<ul> 

<?php foreach ($bount1 as $row): ?>
    <li class=""><span><?php print $row['name'];?></span>&nbsp;&nbsp;&nbsp;&nbsp;<span>奖金：<?php print $row['amount'];?>元</span>&nbsp;&nbsp;&nbsp;&nbsp;<span>代金卷：<?php print $row['voucher'];?>元</span></li>
 <?php endforeach; ?>
</ul>


<h2>二级奖励推荐列表</h2>
<ul> 

<?php foreach ($bount2 as $row): ?>
    <li class=""><span><?php print $row['name'];?></span>&nbsp;&nbsp;&nbsp;&nbsp;<span><?php print $row['amount'];?>元</span></li>
 <?php endforeach; ?>
</ul>