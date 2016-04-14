// LogDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "agvScheduleServer.h"
#include "LogDlg.h"
#include "afxdialogex.h"


// CLogDlg �Ի���

IMPLEMENT_DYNAMIC(CLogDlg, CDialogEx)

CLogDlg::CLogDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_LOG, pParent)
{

}

CLogDlg::~CLogDlg()
{
}

void CLogDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ctl);
}


BEGIN_MESSAGE_MAP(CLogDlg, CDialogEx)
END_MESSAGE_MAP()


// CLogDlg ��Ϣ�������


BOOL CLogDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	CString field[] = { _T("����"),_T("ʱ��"), _T("��Ϣ") };

	// int fieldnum = sizeof(field) / sizeof(field[0]);
	m_ctl.InsertColumn(0, field[0], LVCFMT_LEFT, 60);
	m_ctl.InsertColumn(1, field[1], LVCFMT_LEFT, 90);
	m_ctl.InsertColumn(2, field[2], LVCFMT_LEFT, 500);
	
	m_ctl.ShowScrollBar(SB_HORZ);

	// ��ȡ���ݿ�
	m_AdoConn.OnInitADOConn();
	CString sql = _T("select * from log");
	m_pRs = m_AdoConn.GetRecordSet((_bstr_t)sql);

	int i = 0;
	while (!m_pRs->adoEOF) {
		m_ctl.InsertItem(i, (_bstr_t)m_pRs->GetCollect("ID"));
		m_ctl.SetItemText(i, 1, (_bstr_t)m_pRs->GetCollect("time"));
		m_ctl.SetItemText(i, 2, (_bstr_t)m_pRs->GetCollect("msg"));

		m_pRs->MoveNext();
		++i;
	}

	m_AdoConn.ExitConn();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}
