#include "stdafx.h"
#include "NetSocketDef.h"
#include "MsgStruct.h"


CListenSocket::CListenSocket()
{

}


void CListenSocket::OnAccept(int nErrorCode)
{
	CClientSocket* pClientSocket = new	CClientSocket;
	if (! Accept(*pClientSocket))
	{
		delete pClientSocket;
		pClientSocket = nullptr;
	}

	// �����ӵ�agvС������list
	m_csClientList.Lock();
	m_clientList.AddTail(pClientSocket);
	m_csClientList.Unlock();

	CSocket::OnAccept(nErrorCode);
}





void CClientSocket::OnReceive(int nErrorCode)
{
	// TODO: �ڴ����ר�ô����/����û���
	Msg_E1 e1;
	Receive(&e1, sizeof(e1));

	m_agvno = e1.agvno;
	m_curPointNo = e1.curPoint;

	CAsyncSocket::OnReceive(nErrorCode);
}


void CClientSocket::OnSend(int nErrorCode)
{
	// TODO: �ڴ����ר�ô����/����û���
	/*
		������ȴ��ڵ�ok������M1,M2,M6��Ϣ
		�뿴CScheduleDlg::OnBnClickedOk()
	*/
	// 

	CAsyncSocket::OnSend(nErrorCode);
}
