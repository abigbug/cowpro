<?php
/* 测试环境*/
/*
const JPP_OP_BIND_ACCOUNT = '关联宜商行账户';
const JPP_OP_AUTHORIZE = '授权对宜商行帐户操作';

const PLATFORM_ACCOUNT_ON_JIUPAIPAY = 'platform_account_on_jiupaiopay';
const PUBLIC_KEY_ON_JIUPAIPAY = 'public_key_on_jiupaypai';
const PRIVATE_KEY_ON_JIUPAIPAY = 'private_key_on_jiupaipay';

const JPP_AES_KEY = "JBZ123";  //AES秘钥
const JPP_AES_IV = "1a2b3c4c5d6f7d8e";  // AES秘钥偏量

//服务器请求入口地址
const JPP_URL = 'https://36.110.98.254:19002/p2pwg/mfcf/';

// pc设置交易密码URL
const JPP_REGISTER_TRANSACTION_PASSWORD_URL = "https://36.110.98.254:19001/p2ph5/pc/enterPassword.html";

// pc设置修改密码URL
const JPP_MODIFY_TRANSACTION_PASSWORD_URL = "https://36.110.98.254:19001/p2ph5/pc/changePassword.html";

// pc设置重置密码URL
const JPP_RESET_TRANSACTION_PASSWORD_URL = "https://36.110.98.254:19001/p2ph5/pc/forgetPassword.html";

// pc校验交易密码URL
const JPP_CHECK_TRANSACTION_PASSWORD_URL = "https://36.110.98.254:19001/p2ph5/pc/checkPassword.html";

// pc绑定银行卡URL
const JPP_BANK_CARD_URL = "https://36.110.98.254:19001/p2ph5/pc/cardBind2.html";

// standard设置交易密码URL
const JPP_REGISTER_TRANSACTION_PASSWORD_URL_MOBILE = "https://36.110.98.254:19001/p2ph5/standard/enterPassword.html";

// standard设置修改密码URL
const JPP_MODIFY_TRANSACTION_PASSWORD_URL_MOBILE = "https://36.110.98.254:19001/p2ph5/standard/changePassword.html";

// standard设置重置密码URL
const JPP_RESET_TRANSACTION_PASSWORD_URL_MOBILE = "https://36.110.98.254:19001/p2ph5/standard/forgetPassword.html";

// standard校验交易密码URL
const JPP_CHECK_TRANSACTION_PASSWORD_URL_MOBILE = "https://36.110.98.254:19001/p2ph5/standard/checkPassword.html";

// standard绑定银行卡URL
const JPP_BANK_CARD_URL_MOBILE = "https://36.110.98.254:19001/p2ph5/standard/cardBind2.html";

//网关支付前端跳转URL
const JPP_BANK_PAY_FRONT_URL = "/cowpro/jiupaipay/callback/jiupaipay_bank_return";

//网关支付后台通知URL
const JPP_BANK_PAY_BACK_URL = "/cowpro/jiupaipay/callback/jiupaipay_bank_notify";

//网关接口地址
const JPP_BANK_API_URL = "https://tppsgw.dccbj.cn:5188/devportal/ws/cpcnGatePay/rechargerByCpcn";

//测试网关支付秘钥
const PAY_KEY = "87FB9444028A4B14937A1905";

//平台营销台账账号
const JBZ_PM = "jbzPM20171221";
*/


/* 生产环境 */
const JPP_OP_BIND_ACCOUNT = '关联宜商行账户';
const JPP_OP_AUTHORIZE = '授权对宜商行帐户操作';

const PLATFORM_ACCOUNT_ON_JIUPAIPAY = 'platform_account_on_jiupaiopay';
const PUBLIC_KEY_ON_JIUPAIPAY = 'public_key_on_jiupaypai';
const PRIVATE_KEY_ON_JIUPAIPAY = 'private_key_on_jiupaipay';

const JPP_AES_KEY = "83E94F4BBDE54C4F";  //AES秘钥
const JPP_AES_IV = "99A68A539DE6448A";  // AES秘钥偏量

//服务器请求入口地址
const JPP_URL = 'https://icdsc.ibank.ybccb.com/p2pwg/jbz/';

// pc设置交易密码URL
const JPP_REGISTER_TRANSACTION_PASSWORD_URL = "https://icdsp.ibank.ybccb.com/p2ph5/pc/enterPassword.html";

// pc设置修改密码URL
const JPP_MODIFY_TRANSACTION_PASSWORD_URL = "https://icdsp.ibank.ybccb.com/p2ph5/pc/changePassword.html";

// pc设置重置密码URL
const JPP_RESET_TRANSACTION_PASSWORD_URL = "https://icdsp.ibank.ybccb.com/p2ph5/pc/forgetPassword.html";

// pc校验交易密码URL
const JPP_CHECK_TRANSACTION_PASSWORD_URL = "https://icdsp.ibank.ybccb.com/p2ph5/pc/checkPassword.html";

// pc绑定银行卡URL
const JPP_BANK_CARD_URL = "https://icdsp.ibank.ybccb.com/p2ph5/pc/cardBind2.html";

// standard设置交易密码URL
const JPP_REGISTER_TRANSACTION_PASSWORD_URL_MOBILE = "https://icdsp.ibank.ybccb.com/p2ph5/standard/enterPassword.html";

// standard设置修改密码URL
const JPP_MODIFY_TRANSACTION_PASSWORD_URL_MOBILE = "https://icdsp.ibank.ybccb.com/p2ph5/standard/changePassword.html";

// standard设置重置密码URL
const JPP_RESET_TRANSACTION_PASSWORD_URL_MOBILE = "https://icdsp.ibank.ybccb.com/p2ph5/standard/forgetPassword.html";

// standard校验交易密码URL
const JPP_CHECK_TRANSACTION_PASSWORD_URL_MOBILE = "https://icdsp.ibank.ybccb.com/p2ph5/standard/checkPassword.html";

// standard绑定银行卡URL
const JPP_BANK_CARD_URL_MOBILE = "https://icdsp.ibank.ybccb.com/p2ph5/standard/cardBind2.html";

//网关支付前端跳转URL
const JPP_BANK_PAY_FRONT_URL = "/cowpro/jiupaipay/callback/jiupaipay_bank_return";

//网关支付后台通知URL
const JPP_BANK_PAY_BACK_URL = "/cowpro/jiupaipay/callback/jiupaipay_bank_notify";

//网关接口地址
const JPP_BANK_API_URL = "https://tppsgw.ibank.ybccb.com:5188/devportal/ws/cpcnGatePay/rechargerByCpcn";

//网关支付秘钥
const PAY_KEY = "Q3KO3VN7T7G4BPL8J6W36R7S";

//平台营销台账账号
const JBZ_PM = "jbzPM20180102";
