
// agvScheduleServerDoc.cpp : CagvScheduleServerDoc ���ʵ��
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

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CagvScheduleServerDoc

IMPLEMENT_DYNCREATE(CagvScheduleServerDoc, CDocument)

BEGIN_MESSAGE_MAP(CagvScheduleServerDoc, CDocument)
//	ON_COMMAND(ID_FILE_OPEN, &CagvScheduleServerDoc::OnFileOpen)
//ON_COMMAND(ID_FILE_OPEN, &CagvScheduleServerDoc::OnFileOpen)
END_MESSAGE_MAP()


// CagvScheduleServerDoc ����/����

CagvScheduleServerDoc::CagvScheduleServerDoc()
{
	// TODO: �ڴ����һ���Թ������
	m_bitmap = nullptr;

}

CagvScheduleServerDoc::~CagvScheduleServerDoc()
{
}

BOOL CagvScheduleServerDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// CagvScheduleServerDoc ���л�

void CagvScheduleServerDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: �ڴ���Ӵ洢����
	}
	else
	{
		// TODO: �ڴ���Ӽ��ش���
	}
}

#ifdef SHARED_HANDLERS

// ����ͼ��֧��
void CagvScheduleServerDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// �޸Ĵ˴����Ի����ĵ�����
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// ������������֧��
void CagvScheduleServerDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// ���ĵ����������������ݡ�
	// ���ݲ���Ӧ�ɡ�;���ָ�

	// ����:     strSearchContent = _T("point;rectangle;circle;ole object;")��
	SetSearchContent(strSearchContent);
}

void CagvScheduleServerDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CagvScheduleServerDoc ���

#ifdef _DEBUG
void CagvScheduleServerDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CagvScheduleServerDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CagvScheduleServerDoc ����

//void CagvScheduleServerDoc::OnFileOpen()
//{
//	// TODO: �ڴ���������������
//	// �򿪶Ի���
//	CFileDialog fileDlg(TRUE, nullptr, nullptr, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
//		_T("place files(*.bmp)|*.bmp"));
//	
//	CString strPath;
//	if (IDOK == fileDlg.DoModal())
//		strPath = fileDlg.GetPathName();
//	else
//		return;
//	
//	// ����λͼ
//	HBITMAP hBitmap = (HBITMAP)LoadImage(AfxGetInstanceHandle(), strPath,
//		IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION | LR_DEFAULTSIZE);
//	
//	// ��ֵ��Ա
//	m_bitmap = hBitmap;
//}


BOOL CagvScheduleServerDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;

	// TODO:  �ڴ������ר�õĴ�������
	// ����λͼ
	HBITMAP hBitmap = (HBITMAP)LoadImage(AfxGetInstanceHandle(), lpszPathName,
		IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION | LR_DEFAULTSIZE);
		
	// ��ֵ��Ա
	m_bitmap = hBitmap;

	return TRUE;
}
