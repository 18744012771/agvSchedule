#pragma once


class CAgvSocket : public CSocket
{
public:
	UINT16				m_target = 0;		// С��Ŀ����
	UINT16				m_curPointNo = 0;	// С����ǰ���

	bool				m_bRecv = false;	// ���յ�ָ��

public:
	virtual void OnReceive(int nErrorCode);
	virtual void OnSend(int nErrorCode);
};