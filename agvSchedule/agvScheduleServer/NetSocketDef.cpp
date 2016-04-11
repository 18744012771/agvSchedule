#include "stdafx.h"

#include <algorithm>
#include "NetSocketDef.h"

#include "agvScheduleServerView.h"
#include "agvScheduleServerDoc.h"


#define USER_PRECISION 5	// �û�ָ������ľ������

CListenSocket::CListenSocket(CagvScheduleServerView* pView)
	: m_pView(pView)
{

}


void CListenSocket::OnAccept(int nErrorCode)
{
	CClientSocket* pClientSocket = new	CClientSocket(m_pView, this);
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



CClientSocket::CClientSocket(CagvScheduleServerView* pView, CListenSocket* pListenSocket)
	: m_pView(pView), m_pListenSocket(pListenSocket)
{

}

void CClientSocket::OnReceive(int nErrorCode)
{
	// TODO: �ڴ����ר�ô����/����û���
	int recvBytes = Receive(&m_e1, sizeof(m_e1));

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
		getAgvXY(pClient->m_e1, curAgvXY);
		// ��һ��Բ����ʾ����
		memdc1.Ellipse(curAgvXY.x - 4, curAgvXY.y - 4, curAgvXY.x + 4, curAgvXY.y + 4);	
		strAgvNo.Format(_T("%d"), pClient->m_e1.agvno);
		memdc1.TextOutW(curAgvXY.x, curAgvXY.y, strAgvNo);
	}

	pDC->StretchBlt(0, 0, rc.right, rc.bottom,
		&memdc1, 0, 0, rc.right, rc.bottom, SRCCOPY);

	bitmapSrc.Detach();

	//AsyncSelect();

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


void CClientSocket::getAgvXY(const Msg_E1& e1, CPoint& pt)
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
	auto pDoc = m_pView->GetDocument();
	auto& mapSideNo = pDoc->m_sideNo;	// �Σ��κ�
	auto& mapPoint = pDoc->m_mapPoint;	// ��ţ�����									
	auto& vecRoute = pDoc->m_vecRoute;	// ����·��
	
	CPoint curPt;
	mapPoint.Lookup(e1.curPoint, curPt); //��ǰ������
	if (vecRoute.empty()) {
		pt = curPt;
		return;
	}	

	UINT16 nxPtNo; // ��һ�����
	auto curPtIter = std::find(vecRoute.begin(), vecRoute.end(), e1.curPoint);
	std::advance(curPtIter, 1);
	if (curPtIter == vecRoute.end())
		return;

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
}
