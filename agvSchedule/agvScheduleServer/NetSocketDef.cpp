#include "stdafx.h"

#include <algorithm>
#include "resource.h"
#include "NetSocketDef.h"

#include "agvScheduleServerView.h"
#include "agvScheduleServerDoc.h"
#include "TaskAndCarInfoDlg.h"
#include "TabCarInfoDlg.h"
#include "TabControlDlg.h"

#include "CarDef.h"
#include "TrafficManager.h"
#include "CarManager.h"


#define USER_PRECISION 5	// �û�ָ������ľ������
CString g_cstrCarState[] = { _T("δ֪"), _T("����"),
	_T("�ѷ���"), _T("������"), _T("ȡ��") };

CListenSocket::CListenSocket(CagvScheduleServerView* pView, CTaskAndCarInfoDlg* pDlg)
	: m_pView(pView), m_pDlg(pDlg)
{

}


void CListenSocket::OnAccept(int nErrorCode)
{
	CClientSocket* pClientSocket = new	CClientSocket(m_pView, this, m_pDlg);
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



CClientSocket::CClientSocket(CagvScheduleServerView* pView, 
	CListenSocket* pListenSocket, CTaskAndCarInfoDlg* pDlg)
	: m_pView(pView), m_pListenSocket(pListenSocket), m_pDlg(pDlg)
{

}

void CClientSocket::OnReceive(int nErrorCode)
{
	// TODO: �ڴ����ר�ô����/����û���
	char msge1[24];
	ZeroMemory(msge1, 24);
	int recvBytes = Receive(msge1, 24);

	SetMsgE1(msge1);

	// ��ͨ����С��״̬��
	TrafficMgn();

	// ��dialog����E1��Ϣ
	setDlgInfo();

	// ��ʾС��λ��
	ShowAGV();

	//AsyncSelect();

	CAsyncSocket::OnReceive(nErrorCode);
}


void CClientSocket::SetMsgE1(char* buf)
{
	//const BYTE head[3] = { 0x21, 0x15, 0x41 };  0 1 2
	//const BYTE type[2] = { 0x45, 0x31 }; 3 4
	//BYTE agvno = 0;  5
	//BYTE m1tag = 0;  6
	//BYTE m2tag = 0;  7
	//BYTE m6tag = 0;  8
	//UINT16 curDist = 0;  9 10
	//UINT16 curSec = 0;   11 12  
	//UINT16 curPoint = 0; 13 14  
	//UINT16 agcStatus = 0; 15 16  
	//BYTE agcError = 0;  17
	//BYTE reserve = 0;   18
	//UINT16 curSpeed = 0; 19 20  
	//BYTE moveOrOpt = 0;  21
	//UINT16 curTask = 0;  22  23
	m_e1.agvno = buf[5];
	m_e1.m1tag = buf[6];
	m_e1.m2tag = buf[7];
	m_e1.m6tag = buf[8];
	m_e1.curDist = (buf[10] << 8) | buf[9];
	m_e1.curSec = (unsigned char)buf[11]/*(buf[12] << 8) | buf[11]*/;
	m_e1.curPoint = (buf[14] << 8) | buf[13];
	m_e1.agcStatus = (buf[16] << 8) | buf[15];
	m_e1.agcError = buf[17];
	m_e1.reserve = buf[18];
	m_e1.curSpeed = (buf[20] << 8) | buf[19];
	m_e1.moveOrOpt = buf[21];
	m_e1.curTask = (buf[23] << 8) | buf[22];
}

void CClientSocket::TrafficMgn()
{
	BYTE carno = m_e1.agvno;		// ����
	UINT16 state = m_e1.agcStatus;  // ״̬
	CagvScheduleServerDoc* pDoc = m_pView->GetDocument();
	CTrafficManager* pMgn = pDoc->m_pTrafficMgn;

	pMgn->SetCurCar(carno);
	if (state != m_prevE1.agcStatus) {
		delete pMgn->m_mapCarState[carno];
		pMgn->m_mapCarState[carno] = nullptr;

		pMgn->m_mapCarState[carno] = GetCarState(state);
		pMgn->SetCurCarState();
	}

	//if (!pState) {
	//	pMgn->m_mapCarState[carno] = GetCarState(state);
	//	pMgn->SetCurCarState();
	//}
	//else {
	//	
	//}
	
}

ICarState* CClientSocket::GetCarState(UINT16 state)
{


	unsigned bit = 1;
	if (state == 0 || ((state >> 10 & bit) == 0)) {
		// AGV����ϵͳδ�ܶ�����С������Ϣ��С��δ���뵽ϵͳ��
		return new CCarUnknown;
	}

	if ((state >> 10 & bit) == 1 && (state >> 11 & bit) == 1) {
		// ����û�в��������ǿ��ص�
		return new CCarFree;
	}

	//if (state & bit && state & (bit << 14)) {
	//	// �ػ��������ƶ�
	//	return new CCarAssignmented;
	//}

	if ((state >> 12 & bit) == 1) {
		// С�����ڼ�ͣ���ֶ�״̬
		return new CCarCanceled;
	}

	return nullptr;
}


void CClientSocket::ShowAGV()
{
	auto pDoc = m_pView->GetDocument();
	HBITMAP& hBitmap = pDoc->GetBitmap();
	CDC* pDC = m_pView->GetDC();

	CDC memdc1, memdc2;
	memdc1.CreateCompatibleDC(pDC);
	memdc2.CreateCompatibleDC(pDC);

	// ��ȡ�����С
	RECT rc;
	m_pView->GetClientRect(&rc);

	CBitmap bitmapSrc, bitmap2;
	bitmapSrc.Attach(pDoc->GetBitmap());
	bitmap2.CreateCompatibleBitmap(pDC, rc.right, rc.bottom);

	memdc1.SelectObject(&bitmap2);	// ������С�ǿͻ�����С
	memdc2.SelectObject(&bitmapSrc);

	BITMAP bm;
	bitmapSrc.GetBitmap(&bm);

	// ����memdc1���view�Ĵ�С
	memdc1.StretchBlt(0, 0, rc.right, rc.bottom,
		&memdc2, 0, 0, bm.bmWidth, bm.bmHeight, SRCCOPY);

	CObList& clientList = m_pListenSocket->m_clientList;
	POSITION pos = clientList.GetHeadPosition();
	CPoint curAgvXY;
	CString strAgvNo;
	while (pos) { // �����еĵ㻭����
		CClientSocket* pClient = (CClientSocket*)clientList.GetNext(pos);
		// ��ȡС����ǰ���ڵ������
		getAgvXY(pClient, curAgvXY);
		// ��һ��Բ����ʾ����
		memdc1.Ellipse(curAgvXY.x - 4, curAgvXY.y - 4, curAgvXY.x + 4, curAgvXY.y + 4);
		strAgvNo.Format(_T("%d"), pClient->m_e1.agvno);
		memdc1.TextOutW(curAgvXY.x, curAgvXY.y, strAgvNo);
	}

	pDC->StretchBlt(0, 0, rc.right, rc.bottom,
		&memdc1, 0, 0, rc.right, rc.bottom, SRCCOPY);

	bitmapSrc.Detach();
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


void CClientSocket::getAgvXY(CClientSocket* pClient, CPoint& pt)
{
	/*
	E1: agv�ϱ� 200ms
	45 31
	01 ����
	01 M1��Ϣ��ǩ
	01 M2��Ϣ��ǩ
	01 M6��Ϣ��ǩ
	00 01 ��ǰ���߶ξ���(mm)
	00 01 ��ǰ�κ�
	00 01 ��ǰ���
	00 01 agc״̬λ
	01 agc������
	01 Ԥ��
	00 01 ��ǰ�ٶ�mm/s
	01 �ƶ����&�������
	00 01 ��ǰ�����
	��21�ֽ�
	*/
	const Msg_E1& e1 = pClient->m_e1;
	auto pDoc = m_pView->GetDocument();
	auto& mapSideNo = pDoc->m_sideNo;	// �Σ��κ�
	auto& mapPoint = pDoc->m_mapPoint;	// ��ţ�����									
	auto& vecRoute = pDoc->m_vecRoute;	// ����·��
	
	CPoint curPt;
	BOOL bFind = mapPoint.Lookup(e1.curPoint, curPt); 
	if (!bFind) {
		pt = pClient->m_pt;
		return;
	}
	
	// �����ǰE1���Ǹ��׽��ֵ�E1
	if (e1.agvno != m_e1.agvno) {
		pt = pClient->m_pt;
		return;
	}

	// �����С����ʼλ��
	if (vecRoute.empty()) {
		pt = curPt;
		m_pt = pt;
		return;
	}
	
	UINT16 nxPtNo; // ��һ�����
	auto curPtIter = std::find(vecRoute.begin(), vecRoute.end(), e1.curPoint);
	std::advance(curPtIter, 1);
	if (curPtIter == vecRoute.end()) {
		pt = curPt;
		m_pt = pt;
		return;
	}
		

	nxPtNo = (UINT16)*curPtIter;
	CPoint nxPt; // ��һ����ŵ�����
	mapPoint.Lookup(nxPtNo, nxPt);	

	// �ж���x����y��
	bool bXY = false;	// y��
	bool bPositive = false; // ������
	if (fabs(nxPt.y - curPt.y) < USER_PRECISION) {
		bXY = true;		// x��
		// �ж����������Ƿ�����
		if (curPt.x < nxPt.x)
			bPositive = true;
	}
	else {
		if (curPt.y < nxPt.y)
			bPositive = true;
	}
		

	// ����������� pix�������mm��
	// ��E1��Ϣ�ĵ�ǰ���뻻�����Ļ���� 5�� 1mm  1-2 57pix 
	int curDist = e1.curDist * 15;
	
	// ���㵱ǰ��
	if (bXY) {
		bPositive ? pt.x = curPt.x + curDist : pt.x = curPt.x - curDist;
		pt.y = curPt.y;
	}
	else {
		bPositive ? pt.y = curPt.y + curDist : pt.y = curPt.y - curDist;
		pt.x = curPt.x;	
	}

	pClient->m_pt = pt;
}


void CClientSocket::setDlgInfo()
{
	/*
	E1: agv�ϱ� 200ms
	45 31
	01 ����
	01 M1��Ϣ��ǩ
	01 M2��Ϣ��ǩ
	01 M6��Ϣ��ǩ
	00 01 ��ǰ���߶ξ���(mm)
	00 01 ��ǰ�κ�
	00 01 ��ǰ���
	00 01 agc״̬λ
	01 agc������
	01 Ԥ��
	00 01 ��ǰ�ٶ�mm/s
	01 �ƶ����&�������
	00 01 ��ǰ�����
	��21�ֽ�
	*/
	// ������Ϣ
	static bool bfirst = true;
	if (bfirst) {
		m_prevE1 = m_e1;
		bfirst = false;
	}
	else if (m_e1.curPoint == m_prevE1.curPoint &&
		m_e1.agcStatus == m_prevE1.agcStatus && 
		m_e1.curSec == m_prevE1.curSec) {
		return;
	}

	CListCtrl& ctl = m_pDlg->m_car->m_ctl;
	int nCount = ctl.GetItemCount();
	CString carno, status, curpt, tarpt, curside;
	carno.Format(_T("%d"), m_e1.agvno);

	CTrafficManager* pMgn = m_pView->GetDocument()->m_pTrafficMgn;

	status.Format(_T("%s"), g_cstrCarState[pMgn->m_curState]);
	curpt.Format(_T("%d"), m_e1.curPoint);
	tarpt.Format(_T("%d"), m_targetPt);
	curside.Format(_T("%d"), m_e1.curSec);

	ctl.InsertItem(nCount, carno);
	ctl.SetItemText(nCount, 1, status);
	ctl.SetItemText(nCount, 2, curpt);
	ctl.SetItemText(nCount, 3, tarpt);
	ctl.SetItemText(nCount, 4, curside);

	// �������
	CTabControlDlg* pControl = m_pDlg->m_control;
	unsigned bitMove = 1;
	for (int i = 0; i < 16; ++i) {
		if (m_e1.agcStatus & (bitMove << i)) {
			CStatic* pSts = pControl->m_arrStatus[i];
			pSts->ModifyStyle(0, SS_BITMAP);
			pSts->SetBitmap(LoadBitmap(
				AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP_GREEN)));
		}
	}

	m_prevE1 = m_e1;
}