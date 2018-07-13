<?php

/**
 * @file
 * Template to display a view as a table.
 *
 * - $title : The title of this group of rows.  May be empty.
 * - $header: An array of header labels keyed by field id.
 * - $caption: The caption for this table. May be empty.
 * - $header_classes: An array of header classes keyed by field id.
 * - $fields: An array of CSS IDs to use for each field id.
 * - $classes: A class or classes to apply to the table, based on settings.
 * - $row_classes: An array of classes to apply to each row, indexed by row
 *   number. This matches the index in $rows.
 * - $rows: An array of row items. Each row is an array of content.
 *   $rows are keyed by row number, fields within rows are keyed by field ID.
 * - $field_classes: An array of classes to apply to each field, indexed by
 *   field id, then row number. This matches the index in $rows.
 * @ingroup views_templates
 */
?>
<style>
body,html{width:100%;font-size:90.5797px;}
.handle_swip{padding:0 .16rem; padding-bottom: 0.3rem;}
.apply{height:.32rem;font-size:.12rem;color:#ff7745;text-align:center;line-height:.32rem;box-shadow:0 0 2px #ccc;background:#fff;margin:.15rem .2rem 0;box-sizing:border-box}

.apply>span{padding-right:.1rem;background-size:.06rem auto}

.handle-list>li{margin-top:.2rem;background-size:100% auto;background:#f7f7f7!important;}

.handle-list1>li,.handle-list2>li{background-size:100% auto}

.handle-list>li>.list-text{position:relative;left:0;top:0;padding:.15rem .2rem .2rem;color:#ffffff;background:#ff7745;overflow:hidden;margin-bottom: 0px!important;}

.handle-list1>li>.list-text{color:#999;background-size:.7rem auto}

.handle-list2>li>.list-text{color:#999;background-size:.7rem auto}

.list-text>.list-text-l{position:absolute;left:.2rem;top:60%;transform:translateY(-50%);-webkit-transform:translateY(-50%)}

.list-text>.list-text-r{max-width:2.1rem;float:right;font-size:.12rem;line-height:.2rem;overflow:hidden}

.list-text>.list-text-r>p{width:100%;overflow:hidden;margin: 0rem;}

.list-text>.list-text-r>p>span:first-of-type{display:block;float:left;min-width:.6rem}

.list-text>.list-text-r>p>span:last-of-type{display:block;overflow:hidden;text-align:justify}

.list-text>.list-text-l>i{font-style:normal;font-size:.12rem;padding:0 .16rem 0 .18rem}

.handle-list i{background-size:100% auto}

.handle-list1 i,.handle-list2 i{background-size:100% auto}

.list-text>.list-text-l>p{font-size:.28rem}

.list-text>.list-text-l>p>i{font-style:normal;font-size:.14rem;background:0 0}

.list-text>.list-text-l>p>s{text-decoration:none;font-size:.12rem}

.list-day{padding:0 .2rem;height:.3rem;line-height:.3rem;overflow:hidden;background:#f7f7f7}

.list-day>.list-day-l{float:left;color:#999;font-size:.12rem}

.list-day>.list-day-r{float:right;padding-right:.2rem;color:#ff7745;font-size:.1rem;background-size:.12rem auto}

.list-day>.list-day-r.current{background-size:.12rem auto}

.handle-list1 .list-day>.list-day-r{color:#444}

.list-slid{background:#fff;padding:.1rem .2rem;font-size:.12rem;color:#999;border-top:1px dashed #ccc;line-height:.2rem;box-sizing:border-box;-webkit-box-sizing:border-box;display:none}

.list-slid.current{display:block}

.nobg{width:2.1rem;height:2.3rem;margin:1.5rem auto;background-size:100% auto;}

footer ul li p {
    font-size: 0.15rem;
}
</style>
            <div class="handle_swip">
              <ul class="handle-list">
              <?php foreach ($rows as $row_count => $row): ?>
                <?php 
                  $d1=$row['changed'];
                  $d2="";
                  if(empty($row['expirydate'])){
                    $d2=date("Y/m/d",strtotime("+6 month",strtotime($d1)));
                  }else{
                    $d2=$row['expirydate'];
                  }
                  $validity=floor((strtotime($d2)-strtotime($d1))/3600/24/30);
                ?>
                <li>
                  <div class="list-text">
                    <span class="list-text-l"><i>代金券</i><p><s>￥</s><!-- react-text: 53 --><?php print $row['points']; ?><!-- /react-text --></p></span>
                    <span class="list-text-r">
                      <p><span>使用规则：</span><span><?php print $row['the_rules']; ?></span></p>
                      <p><span>适用产品：</span><span>全场通用 </span></p>
                      <p><span>适用期限：</span><span><?php print $validity; ?>个月及以上</span></p>
                    </span>
                  </div>
                  <div class="list-day">
                    <span class="list-day-l"><!-- react-text: 66 -->有效日期：<!-- /react-text --><!-- react-text: 67 --><?php print $d1; ?> - <?php print $d2; ?><!-- /react-text --></span>
                  </div>
                </li>
              <?php endforeach; ?>
              </ul>
            </div>