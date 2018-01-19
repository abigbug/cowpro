<?php
include_once 'jiupaipay.const.inc';
include_once ("libs/RSA.php");
include_once ("jiupaipay.fun.inc");
include_once ("libs/AES.php");

/*
  列出九派对账文件
 */
function jiupaipay_get_files_list(){
    $dir = DRUPAL_ROOT."/sites/default/files/jiupaipay";
    $file_list = get_file_list($dir);
    //var_dump($file_list);
    $html = theme ( 'jiupaipay_files_list', array (
				'items' => $file_list,
		) );
    return $html;
}

function jiupaipay_theme() {
	return array (
			'jiupaipay_files_list' => array (
					'variables' => array (
							'items' => NULL,
					),
					'template' => 'jiupaipay-files-list',
			),
                        'jiupaipay_files_content' => array (
					'variables' => array (
							'file_content' => NULL,
					),
					'template' => 'jiupaipay-files-content',
			),
	);
}

function jiupaipay_get_files_content($file_name){
    $dir = DRUPAL_ROOT."/sites/default/files/jiupaipay/".$file_name;
    $file_content = file_get_contents($dir);
    global $base_url;
    if( $file_content ) {
      $aes = new AES(JPP_AES_KEY,JPP_AES_IV);
      $file_content = $aes->decrypt($file_content);
      $left_file_name=explode(".txt",$file_name);
      $result = db_query ( "SELECT * FROM {jiupaipay_files_data} WHERE file_name='".$left_file_name[0]."'" )->fetchAll ();
      if ($result) {
        //输出文本中所有的行，直到文件结束为止。  
        drupal_goto($base_url."/yibin-search");
      }else{
        //以空格分割的第二个元素判断是否有对账信息，如果等于0就直接显示没有对账信息
        $contents=explode(" ", $file_content);
        $sum_money=reset($contents);
        if($sum_money=="0^|0"){
          $html = theme ( 'jiupaipay_files_content', array (
                                    'file_content' => "没有该对账文件信息！",
          ));
          return $html;    
        }else{
          //如果第二个元素不等于0就以“ ”空格分割取第三个元素，就是对账列表
          $contents_end=end($contents);
          //以"_"分割对账文件名称，取时间元素
          $contents_date = explode('_',$left_file_name[0]);
          $file_date=$contents_date[2];
          $con_explode=$file_date.'^|jbz';      //分割对账文件信息
          $contents_right = explode($con_explode,$contents_end);
          $length = sizeof($contents_right);
          for($i=1;$i<$length;$i++){
            $contents_tr=$contents_right[$i];
            if(!empty($contents_tr)){
              $itemArray = explode("^|",$contents_tr); // 将tab分割的各部分内容提取出来
              $file_name = $left_file_name[0];   //文件名称
              $business_no = 'jbz'.$itemArray[0];  //业务流水号
              $business_type=$itemArray[3];   //业务类型
              $turnover = $itemArray[7];    //交易金额
              $file_date_unix= strtotime($file_date);
              if(($business_type === "T01") or ($business_type === "T04") or ($business_type === "W01") or ($business_type === "T12")){ // T01或T04或W01类型
                $uid = $itemArray[4];
                db_insert('jiupaipay_files_data')
                  ->fields(array(
                  'file_date' => $file_date_unix,
                  'file_name' => $file_name,
                  'business_no' => $business_no,
                  'business_type' => $business_type,
                  'uid' => $uid,
                  'turnover' => $turnover,
                  ))
                ->execute();
              }else{
                $uid = $itemArray[5];
                db_insert('jiupaipay_files_data')
                  ->fields(array(
                  'file_date' => $file_date_unix,
                  'file_name' => $file_name,
                  'business_no' => $business_no,
                  'business_type' => $business_type,
                  'uid' => $uid,
                  'turnover' => $turnover,
                  ))
                ->execute();
              }
            } 
          }
          drupal_goto($base_url."/cowpro/jiupaipay/reconciliation");
      }
      }
    }else{
      drupal_set_message("文件不存在","error");
    }
}

function get_file_list($dir){
 //判断目标目录是否是文件夹
    $file_arr = array();
    if(is_dir($dir)){
        //打开
        if($dh = @opendir($dir)){
            //读取
            while(($file = readdir($dh)) !== false){

                if($file != '.' && $file != '..'){
                    $file_arr[] = $file;
                }

            }
            closedir($dh);
        }
        return $file_arr;
    }
}