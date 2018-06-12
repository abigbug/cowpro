<?php
//echo \Sodium\crypto_aead_aes256gcm_is_available() . '<br/>';

/*$message = 'We are all living in a yellow submarine';

$key = \Sodium\randombytes_buf(\Sodium\CRYPTO_AEAD_AES256GCM_KEYBYTES);

if (\Sodium\crypto_aead_aes256gcm_is_available()) {
    $nonce = \Sodium\randombytes_buf(\Sodium\CRYPTO_AEAD_AES256GCM_NPUBBYTES);
    $ad = 'Additional (public) data';
    $ciphertext = \Sodium\crypto_aead_aes256gcm_encrypt(
        $message,
        $ad,
        $nonce,
        $key
    );
}
if (\Sodium\crypto_aead_aes256gcm_is_available()) {
    $plaintext = \Sodium\crypto_aead_aes256gcm_decrypt(
        $ciphertext,
        $ad,
        $nonce,
        $key
    );
    if ($decrypted === false) {
        throw new Exception("Bad ciphertext");
    }
}
echo '<br/>';
echo $ciphertext;
echo '<br/>';
echo $plaintext;
echo '<br/>';
echo '<br/>';
echo '<br/>';

  //echo phpinfo();
////////////////////////////////////////////////////////////////////////////////////
/**
 * Encrypt a message
 * 
 * @param string $message - message to encrypt
 * @param string $key - encryption key
 * @return string
 */
function safeEncrypt($message, $key)
{
    $nonce = \Sodium\randombytes_buf(
        \Sodium\CRYPTO_SECRETBOX_NONCEBYTES
    );

    $cipher = base64_encode(
        $nonce.
        \Sodium\crypto_secretbox(
            $message,
            $nonce,
            $key
        )
    );
    \Sodium\memzero($message);
    \Sodium\memzero($key);
    return $cipher;
}

/**
 * Decrypt a message
 * 
 * @param string $encrypted - message encrypted with safeEncrypt()
 * @param string $key - encryption key
 * @return string
 */
function safeDecrypt($encrypted, $key)
{   
    $decoded = base64_decode($encrypted);
    $nonce = mb_substr($decoded, 0, \Sodium\CRYPTO_SECRETBOX_NONCEBYTES, '8bit');
    $ciphertext = mb_substr($decoded, \Sodium\CRYPTO_SECRETBOX_NONCEBYTES, null, '8bit');

    $plain = \Sodium\crypto_secretbox_open(
        $ciphertext,
        $nonce,
        $key
    );
    \Sodium\memzero($ciphertext);
    \Sodium\memzero($key);
    return $plain;
}

// Do this once then store it somehow:
/*$key = \Sodium\randombytes_buf(
    \Sodium\CRYPTO_SECRETBOX_KEYBYTES
);

$ciphertext = safeEncrypt($message, $key);
$plaintext = safeDecrypt($ciphertext, $key);


echo '<br/>';
echo $ciphertext;
echo '<br/>';
echo $plaintext;*/