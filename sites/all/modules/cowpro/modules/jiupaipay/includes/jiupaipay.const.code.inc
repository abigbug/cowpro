<?php
// PHP 5.6.0 或者更新的版本，才可以声明array类型的常量，所以考虑到兼容性，这里直接声明成变量
$YBCCB_TXN_TYPE = array (
		'U00001' => '客户信息同步',
		'U00004' => '客户委托协议签署/撤销',
		'C00002' => '数据信息查询',
		'O00001' => '标的信息同步',
		'T00001' => '客户/平台资金充值/提现',
		'T00004' => '资金交易',
);

$YBCCB_CALLBACK_ACTION = array (
		'register_password' => '设置交易密码',
		'modify_password' => '修改交易密码',
		'reset_password' => '重置交易密码',
		'jiupaipay_step_1' => '宜商行绑定银行卡，校验交易密码回调',
		'jiupaipay_step_2' => '宜商行解绑银行卡',
		'jiupaipay_step_3' => '宜商行绑定银行卡再次回调',
		'jiupaipay_step_4' => '宜商行授权',
		'jiupaipay_step_5' => '宜商行充值回调',
		'jiupaipay_bank_return' => '银行充值回调同步',
		'jiupaipay_bank_notify' => '银行充值回调同步',
		'jiupaipay_step_7' => '提现校验密码回调',
);
