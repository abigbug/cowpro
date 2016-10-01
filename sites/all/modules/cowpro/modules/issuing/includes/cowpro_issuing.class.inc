<?php
class Issuing {
	public $issuing_id = NULL;
	public $uid = NULL;
	//public $caption = 'hello'; // 标题
	//public $caption_brief = ''; // 短标题,用于邮件，短信的显示，字数不得超过20个字
	//public $category = ''; // 分类：企业流贷, 房贷, 车贷, 信用贷, 创业贷
	public $thumbnail = array (); // 缩略图
	//public $purpose = ''; // 借款用途: 短期周转, 购房借款, 装修借款, 个人消费, 婚礼筹备, 教育培训, 汽车消费, 投资创业, 医疗支出, 其他借款
	public $method_repayment = ''; // 还款方式: 到期还本息
	public $loan_contract_template = ''; // 借款合同范本
	public $transfer_contract_template = ''; // 转让合同范本
	public $loan_amounts = 0.00; // 借款金额
	public $margin = 0.00; // 借款保证金[第三方托管]
	public $bid_method = ''; // 投标类型: 按金额，按份额
	public $bid_min = 0; // 最低投标金额(份额)
	public $bid_max = 0; // 最高投标金额(份额)
	public $loan_term = ''; // 贷款期限(天或者月)
	public $annual_rate = 0; // 年利率(%)
	public $deadline = 7; // 筹标期限(天)
	//public $description = ''; // 贷款描述
	public $risk_level = ''; // 风险等级(高，中，低)
	public $risk_management = ''; // 风险控制
	public $transfer_vouchers = ''; // 放款凭证
	public $start_time = 0; // 开始时间
	public $status = 0; // '0:贷款人发标，末审核; 1:审核通过; 2:流标; 3:满标，等待放款; 4:等待还款; 5:还款完毕;',
	public $created;
	public $changed;

	public function __construct($values) {
		foreach ( $values as $k => $v ) {
			if (property_exists($this, $k )) {
				$this->$k = $v;
			}
		}
	}

	public function toStorableArray() {
		$result = array (
				'issuing_id' => $this->issuing_id,
				'uid' => $this->uid,
				'status' => $this->status,
				'created' => $this->created,
				'changed' => $this->changed,
				'data' => ( array ) $this,
				'caption' => $this->caption,
				'category' => $this->category,
				'purpose' => $this->purpose,
				'method_repayment' => $this->method_repayment,
				'loan_amounts' => $this->loan_amounts,
				'start_time' => $this->start_time,
		);
		return $result;
	}
}