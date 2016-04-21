
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

#include "NetSocketDef.h"
#include "ScheduleDlg.h"
#include "TaskList.h"
#include "CarListDlg.h"
#include "LogDlg.h"
#include "ErrorDlg.h"
#include "TaskAndCarInfoDlg.h"

#include "TrafficManager.h"
#include "CarManager.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CagvScheduleServerDoc

IMPLEMENT_DYNCREATE(CagvScheduleServerDoc, CDocument)

BEGIN_MESSAGE_MAP(CagvScheduleServerDoc, CDocument)
//	ON_COMMAND(ID_FILE_OPEN, &CagvScheduleServerDoc::OnFileOpen)
//ON_COMMAND(ID_FILE_OPEN, &CagvScheduleServerDoc::OnFileOpen)
//ON_UPDATE_COMMAND_UI(ID_FILE_SETXY, &CagvScheduleServerDoc::OnUpdateFileSetxy)
ON_UPDATE_COMMAND_UI(ID_FILE_START, &CagvScheduleServerDoc::OnUpdateFileStart)
//ON_COMMAND(ID_FILE_SETXY, &CagvScheduleServerDoc::OnFileSetxy)
ON_UPDATE_COMMAND_UI(ID_EDIT_SETXY, &CagvScheduleServerDoc::OnUpdateEditSetxy)
ON_COMMAND(ID_EDIT_SETXY, &CagvScheduleServerDoc::OnEditSetxy)
ON_COMMAND(ID_EDIT_IMPORTXY, &CagvScheduleServerDoc::OnEditImportxy)
ON_UPDATE_COMMAND_UI(ID_EDIT_IMPORTXY, &CagvScheduleServerDoc::OnUpdateEditImportxy)
ON_COMMAND(ID_EDIT_RESETXY, &CagvScheduleServerDoc::OnEditResetxy)
ON_UPDATE_COMMAND_UI(ID_EDIT_RESETXY, &CagvScheduleServerDoc::OnUpdateEditResetxy)
ON_COMMAND(ID_EDIT_EXPORT, &CagvScheduleServerDoc::OnEditExport)
ON_UPDATE_COMMAND_UI(ID_EDIT_EXPORT, &CagvScheduleServerDoc::OnUpdateEditExport)
ON_COMMAND(ID_FILE_START, &CagvScheduleServerDoc::OnFileStart)
ON_COMMAND(ID_WINDOW_SCHEDULE, &CagvScheduleServerDoc::OnWindowSchedule)
ON_UPDATE_COMMAND_UI(ID_WINDOW_SCHEDULE, &CagvScheduleServerDoc::OnUpdateWindowSchedule)
ON_COMMAND(ID_WINDOW_TASKLIST, &CagvScheduleServerDoc::OnWindowTasklist)
ON_COMMAND(ID_WINDOW_CARLIST, &CagvScheduleServerDoc::OnWindowCarlist)
ON_COMMAND(ID_WINDOW_LOG, &CagvScheduleServerDoc::OnWindowLog)
ON_COMMAND(ID_WINDOW_ERROR, &CagvScheduleServerDoc::OnWindowError)
ON_COMMAND(ID_WINDOW_TASK_CAR, &CagvScheduleServerDoc::OnWindowTaskCar)
END_MESSAGE_MAP()


// CagvScheduleServerDoc ����/����

CagvScheduleServerDoc::CagvScheduleServerDoc()
{
	// TODO: �ڴ����һ���Թ������
	m_bitmap = nullptr;
	m_pListenSocket = nullptr;
	m_pDlg = nullptr;
	m_pScheDlg = nullptr;
}

CagvScheduleServerDoc::~CagvScheduleServerDoc()
{
	if (m_pTrafficMgn) {
		delete m_pTrafficMgn; m_pTrafficMgn = nullptr;
	}
	if (m_pCarMgn) {
		delete m_pCarMgn; m_pCarMgn = nullptr;
	}
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

	if (!m_pDlg) {
		m_pDlg = new CTaskAndCarInfoDlg;
		m_pDlg->Create(IDD_DIALOG_TASK_CAR_INFO, AfxGetApp()->GetMainWnd());
		m_pDlg->ShowWindow(SW_SHOW);
		m_pDlg->CenterWindow();
	}
	else {
		m_pDlg->ShowWindow(SW_SHOW);
	}

	m_pTrafficMgn = new CTrafficManager;
	m_pCarMgn = new CCarManager;

	return TRUE;
}



void CagvScheduleServerDoc::OnUpdateFileStart(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	if (EDIT_IMPORT == m_uEditPushStatus 
		|| EDIT_SET == m_uEditPushStatus)
		pCmdUI->Enable();
	else
		pCmdUI->Enable(0);

	if (m_bitmap)
		pCmdUI->Enable();
}



void CagvScheduleServerDoc::OnUpdateEditSetxy(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	if (m_bitmap)
		pCmdUI->Enable();
	else
		pCmdUI->Enable(0);

	if (EDIT_IMPORT == m_uEditPushStatus)
		pCmdUI->Enable(0);
}


void CagvScheduleServerDoc::OnEditSetxy()
{
	// TODO: �ڴ���������������
	m_uEditPushStatus = EDIT_SET;
}


void CagvScheduleServerDoc::OnEditImportxy()
{
	// TODO: �ڴ���������������
	m_uEditPushStatus = EDIT_IMPORT; // ����˵�������

	CFileDialog dlg(TRUE, _T(".txt"), 0, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		_T("TXT Files(*.txt)|*.txt||"));
	if (IDOK == dlg.DoModal())
	{
		CString strPath = dlg.GetPathName();
		CStdioFile file(strPath,  CFile::modeRead);
		m_mapPoint.RemoveAll();

		// ��� �����꣩->  2\t233,37
		CString strLine, strNo, strPtX, strPtY;
		while (file.ReadString(strLine))
		{
			int pos1 = strLine.Find(_T("\t"));
			strNo = strLine.Left(pos1);
			int pos2 = strLine.Find(_T(","));
			strPtX = strLine.Mid(pos1 + 1, pos2 - pos1);
			strPtY = strLine.Mid(pos2 + 1, strLine.GetLength() - pos2);

			m_mapPoint[_ttoi(strNo)] = CPoint(_ttoi(strPtX), _ttoi(strPtY));
		}

		//TCHAR szExePath[MAX_PATH];
		//GetModuleFileName(nullptr, szExePath, MAX_PATH);
		//CString str(szExePath);
		//int strPos = str.ReverseFind(_T('\\'));
		//str.Truncate(strPos);
		//str += _T("\\����ĵ��&����.txt");

		//CStdioFile file1(str,
		//	CFile::modeWrite | CFile::modeCreate /*| CFile::typeText*/);
		//POSITION pos = m_mapPoint.GetStartPosition();
		//unsigned key;
		//CPoint pt;
		//CString str1;
		//while (pos)
		//{
		//	m_mapPoint.GetNextAssoc(pos, key, pt);
		//	str1.Format(_T("%d\t%d,%d\n"), key, pt.x, pt.y);
		//	file1.WriteString(str1);
		//}

	}
}


void CagvScheduleServerDoc::OnUpdateEditImportxy(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	if (m_bitmap)
		pCmdUI->Enable();
	else
		pCmdUI->Enable(0);
	
}


void CagvScheduleServerDoc::OnEditResetxy()
{
	// TODO: �ڴ���������������
	m_mapPoint.RemoveAll();
	POSITION pos = GetFirstViewPosition();
	CagvScheduleServerView* pView = (CagvScheduleServerView*)GetNextView(pos);
	pView->m_uCurNum = 0;
}


void CagvScheduleServerDoc::OnUpdateEditResetxy(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	if (m_mapPoint.IsEmpty())
		pCmdUI->Enable(0);
	else
		pCmdUI->Enable();

	if (1 == m_uEditPushStatus)
		pCmdUI->Enable(0);
}


void CagvScheduleServerDoc::OnEditExport()
{
	// TODO: �ڴ���������������
	TCHAR szExePath[MAX_PATH];
	GetModuleFileName(nullptr, szExePath, MAX_PATH);
	CString str(szExePath);
	int strPos = str.ReverseFind(_T('\\'));
	str.Truncate(strPos);
	str += _T("\\���&����.txt");

	CStdioFile file(str,
		CFile::modeWrite | CFile::modeCreate /*| CFile::typeText*/);

	POSITION pos = m_mapPoint.GetStartPosition();
	unsigned key;
	CPoint pt;
	//file.WriteString(_T("���\t����\n"));
	while (pos)
	{
		m_mapPoint.GetNextAssoc(pos, key, pt);
		str.Format(_T("%d\t%d,%d\n"), key, pt.x, pt.y);
		file.WriteString(str);
	}

	file.Close();
	m_mapPoint.RemoveAll();
	m_uEditPushStatus = EDIT_DEFAULT;
	return;
}


void CagvScheduleServerDoc::OnUpdateEditExport(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	if (m_mapPoint.IsEmpty())
		pCmdUI->Enable(0);
	else
		pCmdUI->Enable();
}


void CagvScheduleServerDoc::OnFileStart()
{
	// TODO: �ڴ���������������
	AfxSocketInit();

	// ��ֵview DC
	POSITION pos = GetFirstViewPosition();
	CagvScheduleServerView* pView = (CagvScheduleServerView*)GetNextView(pos);

	m_pListenSocket = new CListenSocket(pView, m_pDlg);
	//�����׽���
	if (m_pListenSocket->Create(SVR_PORT))
	{
		//��ʼ����
		if (!m_pListenSocket->Listen(100))
		{
			delete m_pListenSocket;
			m_pListenSocket = NULL;
			AfxMessageBox(_T("�����׽���ʧ�ܣ�"));
			return;
		}
	}else
	{
		delete m_pListenSocket;
		m_pListenSocket = NULL;
		AfxMessageBox(_T("���������׽���ʧ�ܣ�"));
		return;
	}

}


void CagvScheduleServerDoc::OnWindowSchedule()
{
	// TODO: �ڴ���������������
	//CScheduleDlg dlg(this);
	//if (IDOK == dlg.DoModal())
	//{
	//	
	//}
	if (!m_pScheDlg) {
		m_pScheDlg = new CScheduleDlg(this);
		m_pScheDlg->Create(IDD_DIALOG_SCHEDULE, AfxGetApp()->GetMainWnd());
		m_pScheDlg->ShowWindow(SW_SHOW);
		m_pScheDlg->CenterWindow();
	}
	else {
		m_pScheDlg->ShowWindow(SW_SHOW);
	}
}


void CagvScheduleServerDoc::OnUpdateWindowSchedule(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	if (!m_pListenSocket)
		pCmdUI->Enable(0);
	else
		pCmdUI->Enable(1);
}


void CagvScheduleServerDoc::OnWindowTasklist()
{
	// TODO: �ڴ���������������
	CTaskList tasklist;
	tasklist.DoModal();
}


void CagvScheduleServerDoc::OnWindowCarlist()
{
	// TODO: �ڴ���������������
	CCarListDlg carlist;
	carlist.DoModal();
}


void CagvScheduleServerDoc::OnWindowLog()
{
	// TODO: �ڴ���������������
	CLogDlg logdlg;
	logdlg.DoModal();
}


void CagvScheduleServerDoc::OnWindowError()
{
	// TODO: �ڴ���������������
	CErrorDlg errdlg;
	errdlg.DoModal();
}


void CagvScheduleServerDoc::OnWindowTaskCar()
{
	// TODO: �ڴ���������������
	//CTaskAndCarInfoDlg dlg;
	//dlg.DoModal();

	if (!m_pDlg) {
		m_pDlg = new CTaskAndCarInfoDlg;
		m_pDlg->Create(IDD_DIALOG_TASK_CAR_INFO, AfxGetApp()->GetMainWnd());
		m_pDlg->ShowWindow(SW_SHOW);
		m_pDlg->CenterWindow();
	}
	else {
		m_pDlg->ShowWindow(SW_SHOW);
	}
}

