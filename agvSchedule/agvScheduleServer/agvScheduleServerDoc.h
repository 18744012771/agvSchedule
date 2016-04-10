
// agvScheduleServerDoc.h : CagvScheduleServerDoc ��Ľӿ�
//


#pragma once


/* �˵����£�
��ʼ0��
1Ϊ����˵�������
2Ϊ�������������
*/
enum EDIT_PUSH_STATUS{
	EDIT_DEFAULT = 0,
	EDIT_IMPORT,
	EDIT_SET
};


class CListenSocket;
class CagvScheduleServerDoc : public CDocument
{
// ��Ա
private:
	HBITMAP				m_bitmap;
	EDIT_PUSH_STATUS	m_uEditPushStatus = EDIT_DEFAULT;
	
public:
	CMap<unsigned, unsigned, CPoint, CPoint> m_mapPoint;	// (��ţ�����)��ӳ��
	CListenSocket*		m_pListenSocket;

// ����
public:
	inline HBITMAP& GetBitmap() { return m_bitmap; }
	inline UINT8 GetEditPushStatus() const { return m_uEditPushStatus;  }

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
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	afx_msg void OnUpdateFileStart(CCmdUI *pCmdUI);
	afx_msg void OnUpdateEditSetxy(CCmdUI *pCmdUI);
	afx_msg void OnEditSetxy();
	afx_msg void OnEditImportxy();
	afx_msg void OnUpdateEditImportxy(CCmdUI *pCmdUI);
	afx_msg void OnEditResetxy();
	afx_msg void OnUpdateEditResetxy(CCmdUI *pCmdUI);
	afx_msg void OnEditExport();
	afx_msg void OnUpdateEditExport(CCmdUI *pCmdUI);
	afx_msg void OnFileStart();
	afx_msg void OnWindowSchedule();
};
