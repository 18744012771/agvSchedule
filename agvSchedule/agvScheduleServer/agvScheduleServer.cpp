
// agvScheduleServer.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "agvScheduleServer.h"
#include "MainFrm.h"

#include "agvScheduleServerDoc.h"
#include "agvScheduleServerView.h"
#include "LoginDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CagvScheduleServerApp

BEGIN_MESSAGE_MAP(CagvScheduleServerApp, CWinApp)
	ON_COMMAND(ID_APP_ABOUT, &CagvScheduleServerApp::OnAppAbout)
	// �����ļ��ı�׼�ĵ�����
	ON_COMMAND(ID_FILE_NEW, &CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinApp::OnFileOpen)
END_MESSAGE_MAP()


// CagvScheduleServerApp ����

CagvScheduleServerApp::CagvScheduleServerApp()
{
	// TODO: ������Ӧ�ó��� ID �ַ����滻ΪΨһ�� ID �ַ�����������ַ�����ʽ
	//Ϊ CompanyName.ProductName.SubProduct.VersionInformation
	SetAppID(_T("agvScheduleServer.AppID.NoVersion"));

	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}

// Ψһ��һ�� CagvScheduleServerApp ����

CagvScheduleServerApp theApp;


// CagvScheduleServerApp ��ʼ��

BOOL CagvScheduleServerApp::InitInstance()
{
	if (!AfxOleInit()) { return FALSE; }

	struct Msg_E1
	{
		const BYTE head[3] = { 0x21, 0x15, 0x41 };
		const BYTE type[2] = { 0x45, 0x31 };
		BYTE agvno = 0;
		BYTE m1tag = 0;
		BYTE m2tag = 0;
		BYTE m6tag = 0;
		BYTE moveOrOpt = 0;
		UINT16 curDist = 0;
		UINT16 curSec = 0;
		UINT16 curPoint = 0;
		UINT16 agcStatus = 0;
		BYTE agcError = 0;
		BYTE reserve = 0;
		UINT16 curSpeed = 0;
		UINT16 curTask = 0;

		Msg_E1& operator=(const Msg_E1& e1) {
			agvno = e1.agvno;
			m1tag = e1.m1tag;
			m2tag = e1.m2tag;
			m6tag = e1.m6tag;
			curDist = e1.curDist;
			curSec = e1.curSec;
			curPoint = e1.curPoint;
			agcStatus = e1.agcStatus;
			agcError = e1.agcError;
			reserve = e1.reserve;
			curSpeed = e1.curSpeed;
			moveOrOpt = e1.moveOrOpt;
			curTask = e1.curTask;
			return *this;
		}
	};

	size_t a = sizeof(Msg_E1);

	// ��¼
	/*CLoginDlg dlgLogin;
	if (IDOK == dlgLogin.DoModal()) {
		CString name = dlgLogin.m_account;
		CString sql = _T("select * from register where username = '") + name + _T("'");
		m_AdoConn.OnInitADOConn();
		m_pRs = m_AdoConn.GetRecordSet((_bstr_t)sql);
		if (m_pRs->adoEOF) {
			AfxMessageBox(_T("�˺Ŵ���"));
			return(FALSE);
		}

		CString passwd = (_bstr_t)m_pRs->GetCollect("password");
		if (passwd != dlgLogin.m_passwd) {
			AfxMessageBox(_T("�������"));
			return(FALSE);
		}
	}*/

	CWinApp::InitInstance();

	EnableTaskbarInteraction(FALSE);

	// ʹ�� RichEdit �ؼ���Ҫ AfxInitRichEdit2()	
	// AfxInitRichEdit2();

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));
	LoadStdProfileSettings(4);  // ���ر�׼ INI �ļ�ѡ��(���� MRU)


	// ע��Ӧ�ó�����ĵ�ģ�塣  �ĵ�ģ��
	// �������ĵ�����ܴ��ں���ͼ֮�������
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CagvScheduleServerDoc),
		RUNTIME_CLASS(CMainFrame),       // �� SDI ��ܴ���
		RUNTIME_CLASS(CagvScheduleServerView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);


	// ������׼ shell ���DDE�����ļ�������������
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);



	// ��������������ָ�������  ���
	// �� /RegServer��/Register��/Unregserver �� /Unregister ����Ӧ�ó����򷵻� FALSE��
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// Ψһ��һ�������ѳ�ʼ���������ʾ����������и���
	m_pMainWnd->ShowWindow(SW_SHOWMAXIMIZED);
	m_pMainWnd->UpdateWindow();
	return TRUE;
}

// CagvScheduleServerApp ��Ϣ�������


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// �������жԻ����Ӧ�ó�������
void CagvScheduleServerApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CagvScheduleServerApp ��Ϣ�������




