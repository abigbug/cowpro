<?php
include_once 'jiupaipay.issuing_publish.inc';

/**
 * 标的信息同步
 *
 * @param int $nid  标的ID
 */
function jiupaipay_issuing_failing($nid) {
     //标的信息同步(撤标)
     $issuing_publish = jiupaipay_issuing_publish($nid,"P03","02");
     return $issuing_publish;
     
       
}

?>