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
    if( $file_content ) {
        $aes = new AES(JPP_AES_KEY,JPP_AES_IV);
        $file_content = $aes->decrypt($file_content);
         $html = theme ( 'jiupaipay_files_content', array (
                                    'file_content' => $file_content,
                    ) );
        return $html;
    }else{
        drupal_set_message("文件不存在");
        return false;
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