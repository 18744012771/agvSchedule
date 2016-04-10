#pragma once

// �����������׽���
class CListenSocket : public CSocket
{
public:
	CListenSocket();
	virtual ~CListenSocket() {}

	virtual void OnAccept(int nErrorCode);

	CObList				m_clientList;		// ���ӵ�agv
	CCriticalSection	m_csClientList;
};



// ������ͻ��˵�ͨ��
class CClientSocket : public CAsyncSocket
{
public:
	UINT16				m_curPointNo = 0;	// С����ǰ���ڵ��
	BYTE				m_agvno = 0;		// С������

public:
	virtual void OnReceive(int nErrorCode);
	virtual void OnSend(int nErrorCode);
};