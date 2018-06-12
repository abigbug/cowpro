<?php

/**
 * @file
 * Definition of cowpro_fund_journal_handler_field_issuing_title.
 */

/**
 * Field handler to output the title link of cowpro issuing.
 *
 * @ingroup views_field_handlers
 */
class cowpro_fund_journal_handler_field_issuing_title extends views_handler_field {
  function render($values) {
      $msg = "";
      switch( $values->cowpro_fund_journal_type ) {
          case "WITHDRAW";
          case "TOPUP";    
          case "INTERNAL_TRANS";    
              $msg = self::topup_withdraw_render($values);
              break;
          default;
              $msg = self::issuing_render($values);
              break;
          
      }
      return $msg;

  }
  
  function issuing_render($values){
  	global $base_url;
  	$result = '';
        $internal_reference_id = $this->get_value($values);
        $pieces = explode(';', $internal_reference_id);
        $nid = -1;
        $repayment_schedule = -1;
        $period = -1;
        foreach ($pieces as $piece) {
            $ids = explode('-', $piece);
            switch ($ids[0]) {
                    case 'ISSUING':
                            $nid = intval($ids[1]);
                            break;
                    case 'REPAYMENT':
                            $repayment_schedule = intval($ids[1]);
                            break;
                    case 'PERIOD':
                            $period = $ids[1];
                            break;
                    default:
                            break;
            }
        }

        if (($nid == -1) && ($repayment_schedule != -1)) {
            $repayment_query = db_select ( 'cowpro_repayment_schedule', 's');
            $repayment_query->addField('s', 'issuing_id');
            $repayment_query->condition ( 'schedule_id', $repayment_schedule, '=' );
            $repayment = $repayment_query->execute ()->fetchAssoc();
            $nid = $repayment['issuing_id'];
        }

        $node = node_load ( $nid );
        if ($node) {
            $title = $node->title;
            if ($period != -1) {
                    $title = $title . " (第 $period 期还款)";
            }
            $result = "<a href=$base_url/node/$nid>$title</a>";
        }

        return $result;
    }
    
    function topup_withdraw_render($values){
        $msg = "";
        $journal_id = $values->cowpro_fund_journal_journal_id;
    	$entity = entity_load_single('cowpro_fund_journal', $journal_id);
    	$data = $entity->data;
    	if ($data && array_key_exists('interface_module', $data)) {
    		$function = $data['interface_module'] . '_result_parser';
    		if (function_exists($function)) {
    			$msg = $function($values->cowpro_fund_journal_type, $data);
    		}
    	}
        return $msg;
    }
}


