<?php
class LoanInfoBean
{
	/*
	 * ������ID
	 */
	public $LoanOutMoneymoremore = "";

	/*
	 * �տ���ID
	 */
	public $LoanInMoneymoremore = "";

	/*
	 * ������
	 */
	public $OrderNo = "";

	/*
	 * ���
	 */
	public $BatchNo = "";

	/*
	 * ��ת����
	 */
	public $ExchangeBatchNo = "";

	/**
	 * ���ʱ��
	 */
	public $AdvanceBatchNo = "";

	/*
	 * ���
	 */
	public $Amount = "";

	/*
	 * ������
	 */
	public $FullAmount = "";

	/*
	 * ��;
	 */
	public $TransferName = "";

	/*
	 * ��ע
	 */
	public $Remark = "";

	/*
	 * ���η����б�
	 */
	public $SecondaryJsonList = "";

	/*
	 LoanOutMoneymoremore	付款人乾多多标识
LoanInMoneymoremore	收款人乾多多标识
OrderNo	网贷平台订单号，长度50
BatchNo	网贷平台标号，长度50
ExchangeBatchNo	流转标标号，长度50
AdvanceBatchNo	垫资标号，长度50
Amount	金额
FullAmount	满标标额;所有标号相同的转账记录中，以第一笔转账成功的记录中的标额为准，之后的转账可以不填标额
TransferName	用途	投标
Remark	备注
	 */
	public function __construct($LoanOutMoneymoremore,$LoanInMoneymoremore,$OrderNo,$BatchNo,$ExchangeBatchNo,$AdvanceBatchNo,$Amount,$FullAmount,$TransferName,$Remark,$SecondaryJsonList)
	{
		$this->LoanOutMoneymoremore = $LoanOutMoneymoremore;
		$this->LoanInMoneymoremore = $LoanInMoneymoremore;
		$this->OrderNo = $OrderNo;
		$this->BatchNo = $BatchNo;
		$this->ExchangeBatchNo = $ExchangeBatchNo;
		$this->AdvanceBatchNo = $AdvanceBatchNo;
		$this->Amount = $Amount;
		$this->FullAmount = $FullAmount;
		$this->TransferName = $TransferName;
		$this->Remark = $Remark;
		$this->SecondaryJsonList = $SecondaryJsonList;
	}
}
?>