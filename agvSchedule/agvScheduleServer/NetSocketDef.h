#pragma once

#include "MsgStruct.h"

class CagvScheduleServerView;
// �����������׽���
class CListenSocket : public CSocket
{
public:
	CListenSocket(CagvScheduleServerView* pView);
	virtual ~CListenSocket() {}

	virtual void OnAccept(int nErrorCode);

	CObList				m_clientList;		// ���ӵ�agv
	CCriticalSection	m_csClientList;

	CagvScheduleServerView* m_pView;
};



// ������ͻ��˵�ͨ��
class CClientSocket : public CSocket
{
public:
	Msg_E1			m_e1;				// �����һ��E1��Ϣ
	CPoint			m_pt;				// ���һ��E1��Ϣ��Ӧ��С������
	CListenSocket*	m_pListenSocket;	// ��ָ�����׽���
	CagvScheduleServerView* m_pView;

public:
	CClientSocket(CagvScheduleServerView* pView, CListenSocket* pListenSocket);
	virtual void OnReceive(int nErrorCode);
	virtual void OnSend(int nErrorCode);

private:
	void getAgvXY(CClientSocket* pClient, CPoint& pt);
};