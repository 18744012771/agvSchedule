
// agvScheduleServerView.h : CagvScheduleServerView ��Ľӿ�
//

#pragma once


class CagvScheduleServerView : public CView
{
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
};

#ifndef _DEBUG  // agvScheduleServerView.cpp �еĵ��԰汾
inline CagvScheduleServerDoc* CagvScheduleServerView::GetDocument() const
   { return reinterpret_cast<CagvScheduleServerDoc*>(m_pDocument); }
#endif

