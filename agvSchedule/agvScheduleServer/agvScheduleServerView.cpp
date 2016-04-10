
// agvScheduleServerView.cpp : CagvScheduleServerView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "agvScheduleServer.h"
#endif

#include "agvScheduleServerDoc.h"
#include "agvScheduleServerView.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CagvScheduleServerView

IMPLEMENT_DYNCREATE(CagvScheduleServerView, CView)

BEGIN_MESSAGE_MAP(CagvScheduleServerView, CView)
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

// CagvScheduleServerView ����/����

CagvScheduleServerView::CagvScheduleServerView()
{
	// TODO: �ڴ˴���ӹ������

}

CagvScheduleServerView::~CagvScheduleServerView()
{
}

BOOL CagvScheduleServerView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CagvScheduleServerView ����

void CagvScheduleServerView::OnDraw(CDC* pDC)
{
	CagvScheduleServerDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
	static RECT rcClient;
	GetClientRect(&rcClient);

	HBITMAP& hBitmap = pDoc->GetBitmap();
	if (hBitmap)
	{
		// ��ȡλͼ�ߴ�
		CBitmap bmpobj;
		bmpobj.Attach(hBitmap);

		BITMAP bm;
		bmpobj.GetBitmap(&bm);

		//�����ڴ�dc
		CDC hdcMem/*, memdc2*/;
		hdcMem.CreateCompatibleDC(pDC);

		// ѡ��λͼ
		hdcMem.SelectObject(&bmpobj);
		
		// ��ͼ
		pDC->StretchBlt(0, 0, rcClient.right, rcClient.bottom, 
			&hdcMem, 0, 0, bm.bmWidth, bm.bmHeight, SRCCOPY);
		bmpobj.Detach();
	}
	
}


// CagvScheduleServerView ���

#ifdef _DEBUG
void CagvScheduleServerView::AssertValid() const
{
	CView::AssertValid();
}

void CagvScheduleServerView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CagvScheduleServerDoc* CagvScheduleServerView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CagvScheduleServerDoc)));
	return (CagvScheduleServerDoc*)m_pDocument;
}
#endif //_DEBUG


// CagvScheduleServerView ��Ϣ�������


void CagvScheduleServerView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	auto pDoc = GetDocument();
	if (EDIT_SET == pDoc->GetEditPushStatus())
	{
		++m_uCurNum;
		// ����������
		pDoc->m_mapPoint[m_uCurNum] = point;
	}

	CView::OnLButtonDown(nFlags, point);
}


void CagvScheduleServerView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	auto pDoc = GetDocument();
	if (EDIT_SET == pDoc->GetEditPushStatus())
	{
		if (pDoc->m_mapPoint.IsEmpty()) {
			m_uCurNum = 0;
			return;
		}

		pDoc->m_mapPoint.RemoveKey(unsigned(pDoc->m_mapPoint.GetCount()));
		--m_uCurNum;
	}

	CView::OnRButtonDown(nFlags, point);
}


void CagvScheduleServerView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	auto pDoc = GetDocument();
	if (EDIT_SET == pDoc->GetEditPushStatus())
	{
		CDC* pDC = GetDC();
		CDC memdc1, memdc2;
		memdc1.CreateCompatibleDC(pDC);
		memdc2.CreateCompatibleDC(pDC);

		// ��ȡ�����С
		RECT rc;
		GetClientRect(&rc);

		CBitmap bitmapSrc, bitmap2;
		bitmapSrc.Attach(pDoc->GetBitmap());
		bitmap2.CreateCompatibleBitmap(pDC, rc.right, rc.bottom);

		memdc1.SelectObject(&bitmap2);	// ������С�ǿͻ�����С
		memdc2.SelectObject(&bitmapSrc);

		BITMAP bm;
		bitmapSrc.GetBitmap(&bm);

		// ��memedc1�ϻ�ͼ���൱���ڿͻ����ϻ�
		memdc1.StretchBlt(0, 0, rc.right, rc.bottom,
			&memdc2, 0, 0, bm.bmWidth, bm.bmHeight, SRCCOPY);

		// ��ʾ����
		POSITION pos = pDoc->m_mapPoint.GetStartPosition();
		unsigned key;
		CPoint pt;
		CString strMsg;
		//memdc1.SetBkMode(TRANSPARENT);
		while (pos)
		{
			pDoc->m_mapPoint.GetNextAssoc(pos, key, pt);
			strMsg.Format(_T("%d"), key);
			memdc1.TextOutW(pt.x, pt.y, strMsg);
		}

		pDC->StretchBlt(0, 0, rc.right, rc.bottom,
			&memdc1, 0, 0, rc.right, rc.bottom, SRCCOPY);

		bitmapSrc.Detach();
	}

	CView::OnMouseMove(nFlags, point);
}
