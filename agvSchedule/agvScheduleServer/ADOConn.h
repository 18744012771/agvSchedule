// ADOConn.h: interface for the ADOConn class.
//
//////////////////////////////////////////////////////////////////////

#pragma once


class ADOConn  
{
public:
	BOOL ExecuteSQL(_bstr_t bstrSQL);//ִ��SQL���
	_RecordsetPtr& GetRecordSet(_bstr_t bstrSQL);//
	void ExitConn();//�Ͽ�����
	void OnInitADOConn();//�������ݿ�
	ADOConn();
	virtual ~ADOConn();
	_ConnectionPtr m_pCon;//_ConnectionPtr����
	_RecordsetPtr m_pRs;//_RecordsetPtr����

};

