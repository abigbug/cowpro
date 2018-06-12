<?php
/**
 * AES加密解密类
 * 密码模式：CBC,秘钥长度为16位
 */
class AES {
    private $iv;                        // 密钥偏移量IV
    private $encryptKey;                // 密钥
    
    public function __construct($Key,$keyIv){
        $this->encryptKey = $Key;
        $this->iv = $keyIv;
    }
    
    /**
     * 加密
     * @param $encryptStr String 加密数据
     * @return String
     */
    public function encrypt($encryptStr) {
        $localIV = $this->iv;
        $encryptKey = $this->encryptKey;
        $module = mcrypt_module_open(MCRYPT_RIJNDAEL_128, '', MCRYPT_MODE_CBC, $localIV);
        mcrypt_generic_init($module, $encryptKey, $localIV);
        $block = mcrypt_get_block_size(MCRYPT_RIJNDAEL_128, MCRYPT_MODE_CBC);
        $pad = $block - (strlen($encryptStr) % $block);
        $encryptStr .= str_repeat(chr($pad), $pad);
    
        $encrypted = mcrypt_generic($module, $encryptStr);

        mcrypt_generic_deinit($module);
        mcrypt_module_close($module);
    
        return base64_encode($encrypted);
    
    }
    
    /**
     * 解密
     * @param $decryptStr String 解密数据
     * @return string
     */
    public function decrypt($encryptStr) {
        $localIV = $this->iv;
        $encryptKey = $this->encryptKey;
        
        $encryptedData = base64_decode($encryptStr);
        $module = mcrypt_module_open(MCRYPT_RIJNDAEL_128, '', MCRYPT_MODE_CBC, $localIV);

        mcrypt_generic_init($module, $encryptKey, $localIV);
    
        $encryptedData = mdecrypt_generic($module, $encryptedData);
    
        return rtrim($encryptedData,"\x00..\x1F");
    }
    
}