#pragma once

/*
	ͨ��ģ��
	��M1 M2 M6
	��E1

*/

#include "MsgStruct.h"

class CagvScheduleServerView;
class CTaskAndCarInfoDlg;
class ICarState;

// �����������׽���
class CListenSocket : public CSocket
{
public:
	CListenSocket(CagvScheduleServerView* pView, CTaskAndCarInfoDlg* pDlg);
	virtual ~CListenSocket() {}

	virtual void OnAccept(int nErrorCode);

	CObList				m_clientList;		// ���ӵ�agv
	CCriticalSection	m_csClientList;

	CagvScheduleServerView* m_pView;
	CTaskAndCarInfoDlg*		m_pDlg;

};



// ������ͻ��˵�ͨ��
class CClientSocket : public CSocket
{
public:
	Msg_E1			m_e1;				// �����һ��E1��Ϣ
	Msg_E1			m_prevE1;			// ��һ��E1��Ϣ
	CPoint			m_pt;				// ���һ��E1��Ϣ��Ӧ��С������
	UINT16			m_targetPt = 0;		// Ŀ���
	CListenSocket*	m_pListenSocket;	// ��ָ�����׽���
	CagvScheduleServerView* m_pView;
	CTaskAndCarInfoDlg*		m_pDlg;
	

public:
	CClientSocket(CagvScheduleServerView* pView, 
		CListenSocket* pListenSocket, CTaskAndCarInfoDlg* pDlg);
	virtual void OnReceive(int nErrorCode);
	virtual void OnSend(int nErrorCode);

private:
	void getAgvXY(CClientSocket* pClient, CPoint& pt);
	void setDlgInfo();
	void ShowAGV();
	void TrafficMgn();
	ICarState* GetCarState(UINT16 state);
	void SetMsgE1(char* buf);
};