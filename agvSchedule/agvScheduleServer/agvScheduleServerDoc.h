
// agvScheduleServerDoc.h : CagvScheduleServerDoc ��Ľӿ�
//


#pragma once


class CagvScheduleServerDoc : public CDocument
{
// ��Ա
private:
	HBITMAP				m_bitmap;

// ����
public:
	inline HBITMAP& GetBitmap() { return m_bitmap; }


private:
	

protected: // �������л�����
	CagvScheduleServerDoc();
	DECLARE_DYNCREATE(CagvScheduleServerDoc)

// ����
public:


// ��д
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// ʵ��
public:
	virtual ~CagvScheduleServerDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// ����Ϊ����������������������ݵ� Helper ����
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
//	afx_msg void OnFileOpen();
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
};
