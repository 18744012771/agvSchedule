
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

void CagvScheduleServerView::OnDraw(CDC* /*pDC*/)
{
	CagvScheduleServerDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
	//// ��ȡλͼ�ߴ�
	//CBitmap bmpobj;
	//bmpobj.Attach(hBitmap);

	//BITMAP bm;
	//bmpobj.GetBitmap(&bm);

	//CView* pView = GetActiveView();

	//// �ı�mainframe��С
	//int cyMenu = GetSystemMetrics(SM_CYMENU);		// �˵�&״̬
	//int cyCaption = GetSystemMetrics(SM_CYCAPTION); // ����

	////MoveWindow(0, 0, bm.bmWidth + cyMenu, bm.bmHeight + 2 * cyMenu + cyCaption);
	////CenterWindow();

	////�����ڴ�dc
	//CDC* pdc = pView->GetDC();
	//CDC hdcMem;
	//hdcMem.CreateCompatibleDC(pdc);

	//// ѡ��λͼ
	//hdcMem.SelectObject(&bmpobj);

	//// ��ͼ
	//pdc->BitBlt(0, 0, bm.bmWidth, bm.bmHeight, &hdcMem, 0, 0, SRCCOPY);
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
