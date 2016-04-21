
// agvScheduleClientDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include <vector>
#include "agvScheduleClient.h"
#include "agvScheduleClientDlg.h"
#include "afxdialogex.h"

#include "NetSocketDef.h"
#include "MsgStruct.h"
#include "afxwin.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ��С��һ��ָ����·��:С��1 ��1-2-3��
static std::vector<Msg_E1>  g_vecE1;
// С��2����2-3-4-26-24��
static std::vector<Msg_E1>	g_vecE1No2;

void setVecE1()
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
	extern BYTE g_AGVNo;
	Msg_E1 e1;
	if (1 == g_AGVNo)
	{
		e1.m1tag = e1.m2tag = e1.m6tag = 1;
		e1.agvno = g_AGVNo;

		e1.curPoint = 1;
		e1.curDist = 1; // mm

		for (int i = 0; i < 5; ++i)
		{
			// ��1-2����1s 5�� 5mm 1-2��41�����أ�ÿ����1/5 8����
			g_vecE1.push_back(e1);
			++e1.curDist;
		}

		e1.curPoint = 2;
		e1.curDist = 1;
		for (int i = 0; i < 5; ++i)
		{
			// ��2-3����1s 5�� 5mm 1-2��41�����أ�ÿ����1/5 8����
			g_vecE1.push_back(e1);
			++e1.curDist;
		}

		e1.curPoint = 3;
		e1.curDist = 0;
		g_vecE1.push_back(e1);
	}

	if (2 == g_AGVNo) {
		e1.agvno = g_AGVNo;
		e1.m1tag = e1.m2tag = e1.m6tag = 2;
		e1.curPoint = 2;
		e1.curDist = 1; // mm

		for (int i = 0; i < 5; ++i)
		{
			// ��1-2����1s 5�� 5mm 1-2��41�����أ�ÿ����1/5 8����
			g_vecE1No2.push_back(e1);
			++e1.curDist;
		}

		e1.curPoint = 3;
		e1.curDist = 1;
		for (int i = 0; i < 5; ++i)
		{
			// ��2-3����1s 5�� 5mm 1-2��41�����أ�ÿ����1/5 8����
			g_vecE1No2.push_back(e1);
			++e1.curDist;
		}

		e1.curPoint = 4;
		e1.curDist = 1;
		for (int i = 0; i < 5; ++i)
		{
			// ��2-3����1s 5�� 5mm 1-2��41�����أ�ÿ����1/5 8����
			g_vecE1No2.push_back(e1);
			++e1.curDist;
		}

		e1.curPoint = 26;
		e1.curDist = 1;
		for (int i = 0; i < 5; ++i)
		{
			// ��2-3����1s 5�� 5mm 1-2��41�����أ�ÿ����1/5 8����
			g_vecE1No2.push_back(e1);
			++e1.curDist;
		}

		e1.curPoint = 24;
		e1.curDist = 1;
		for (int i = 0; i < 5; ++i)
		{
			// ��2-3����1s 5�� 5mm 1-2��41�����أ�ÿ����1/5 8����
			g_vecE1No2.push_back(e1);
			++e1.curDist;
		}

		e1.curPoint = 24;
		e1.curDist = 0;
		g_vecE1No2.push_back(e1);
	}

}


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
public:
	virtual BOOL OnInitDialog();
	CButton m_ctl;
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDOK, m_ctl);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CagvScheduleClientDlg �Ի���



CagvScheduleClientDlg::CagvScheduleClientDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_AGVSCHEDULECLIENT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CagvScheduleClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CagvScheduleClientDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_CONNECT, &CagvScheduleClientDlg::OnClickedButtonConnect)
	ON_BN_CLICKED(IDC_BUTTON_QUIT, &CagvScheduleClientDlg::OnClickedButtonQuit)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CagvScheduleClientDlg ��Ϣ�������

BOOL CagvScheduleClientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	setVecE1();

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CagvScheduleClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CagvScheduleClientDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CagvScheduleClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CagvScheduleClientDlg::OnClickedButtonConnect()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_pAgvSocket = new CAgvSocket;
	// �����׽��֣��󶨣�ע�������¼�
	if (!m_pAgvSocket->Create()) 
	{
		delete m_pAgvSocket;
		m_pAgvSocket = nullptr;
		AfxMessageBox(_T("�����׽���ʧ�ܣ�"));
		return;
	}

	// ����server��ַ
	TCHAR* ip = _T("127.0.0.1");
	UINT port = SVR_PORT;
	if (!m_pAgvSocket->Connect(ip, port))
	{
		AfxMessageBox(_T("���ӷ�����ʧ�ܣ�"));
		delete m_pAgvSocket;
		m_pAgvSocket = nullptr;
		return;
	}

	// ��ʼ��server����һ��E1��Ϣ���ϱ�С�����ŵ���Ϣ
	extern BYTE g_AGVNo;
	Msg_E1 e1;
	e1.agvno = g_AGVNo;
	e1.curPoint = e1.agvno;
	e1.agcStatus = 1032; // ����ϵͳ

	int sendBytes = m_pAgvSocket->Send(&e1, sizeof(e1));
	//m_pAgvSocket->AsyncSelect();

	SetTimer(1, 200, nullptr);
}


void CagvScheduleClientDlg::OnClickedButtonQuit()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (m_pAgvSocket)
	{
		m_pAgvSocket->Close();
		delete m_pAgvSocket;
		m_pAgvSocket = nullptr;
	}

	EndDialog(0);
}


void CagvScheduleClientDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	extern BYTE g_AGVNo;
	static size_t i = 0;
	if (1 == nIDEvent)
	{
		if (m_pAgvSocket->m_bRecv) {
			if (g_AGVNo == 1) {
				int sendBytes = m_pAgvSocket->Send(&g_vecE1[i++], sizeof(Msg_E1));
				if (i == 11)
					KillTimer(1);
			}
				
			if (g_AGVNo == 2) {
				m_pAgvSocket->Send(&g_vecE1No2[i++], sizeof(Msg_E1));
				if (i == 25)
					KillTimer(1);
			}
			//m_pAgvSocket->AsyncSelect();
		}	
	}

	CDialogEx::OnTimer(nIDEvent);
}


BOOL CAboutDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}
