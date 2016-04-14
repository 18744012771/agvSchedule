// ADOConn.cpp: implementation of the ADOConn class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ADOConn.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ADOConn::ADOConn()
{

}

ADOConn::~ADOConn()
{

}

void ADOConn::OnInitADOConn()//�������ݿ�
{
	
	try
	{
		m_pCon.CreateInstance("ADODB.Connection");
		m_pCon->ConnectionTimeout=3;//���ӳ���ʱ��
		//����Access���ݿ�
		m_pCon->Open("Provider=Microsoft.ACE.OLEDB.12.0;Data Source=agvSchedule.accdb",
			"","", adModeUnknown);
		//m_pCon->Open("Driver=(Microsoft Access Driver (*.mdb,*.accdb));"
		//	"Data Source=H:\agvSchedule.accdb;",
		//		"","", adModeUnknown);
	}
	catch(_com_error e)//��׽�쳣
	{
		AfxMessageBox(e.Description());
	}
}

void ADOConn::ExitConn()//�Ͽ�����
{
	if(m_pRs!=NULL)
		m_pRs->Close();
	m_pCon->Close();
	
}

_RecordsetPtr& ADOConn::GetRecordSet(_bstr_t bstrSQL)//ִ��SQL��ѯ���
{
	try
	{
		if(m_pCon==NULL)
			OnInitADOConn();
		m_pRs.CreateInstance("ADODB.Recordset");//������¼��
		m_pRs->Open(bstrSQL,m_pCon.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);
	}
	catch(_com_error e)//��׽�쳣
	{
		AfxMessageBox(e.Description());
	}
	return m_pRs;//���ؽ����
}

BOOL ADOConn::ExecuteSQL(_bstr_t bstrSQL)//ִ��SQL�������
{
	try
	{
		if(m_pCon==NULL)
			OnInitADOConn();//�������ݿ�
		m_pCon->Execute(bstrSQL,NULL,adCmdText);//ִ��SQL
		return true;
	}
	catch(_com_error e)//��׽�쳣
	{
		AfxMessageBox(e.Description());
		return false;
	}
}
