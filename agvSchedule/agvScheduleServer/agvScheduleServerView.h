
// agvScheduleServerView.h : CagvScheduleServerView ��Ľӿ�
//

#pragma once


class CagvScheduleServerView : public CView
{
// ����
public:
	unsigned		m_uCurNum = 0;					// ��ǰ���

protected: // �������л�����
	CagvScheduleServerView();
	DECLARE_DYNCREATE(CagvScheduleServerView)

// ����
public:
	CagvScheduleServerDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// ʵ��
public:
	virtual ~CagvScheduleServerView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // agvScheduleServerView.cpp �еĵ��԰汾
inline CagvScheduleServerDoc* CagvScheduleServerView::GetDocument() const
   { return reinterpret_cast<CagvScheduleServerDoc*>(m_pDocument); }
#endif

