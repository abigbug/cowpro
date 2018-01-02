<?php
class LoanInfoSecondaryBean
{
	/*
	 * 二次收款人ID
	 */
	public $LoanInMoneymoremore = "";
	
	/*
	 * 金额
	 */
	public $Amount = "";
	
	/*
	 * 用途
	 */
	public $TransferName = "";
	
	/*
	 * 备注
	 */
	public $Remark = "";

	public function __construct($LoanInMoneymoremore,$Amount,$TransferName,$Remark)
	{
		$this->LoanInMoneymoremore = $LoanInMoneymoremore;
		$this->Amount = $Amount;
		$this->TransferName = $TransferName;
		$this->Remark = $Remark;
	}
}
?>