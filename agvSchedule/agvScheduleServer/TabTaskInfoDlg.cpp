// TabTaskInfoDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "agvScheduleServer.h"
#include "TabTaskInfoDlg.h"
#include "afxdialogex.h"


// CTabTaskInfoDlg �Ի���

IMPLEMENT_DYNAMIC(CTabTaskInfoDlg, CDialogEx)

CTabTaskInfoDlg::CTabTaskInfoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_TASKINFO, pParent)
{

}

CTabTaskInfoDlg::~CTabTaskInfoDlg()
{
}

void CTabTaskInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ctl);
}


BEGIN_MESSAGE_MAP(CTabTaskInfoDlg, CDialogEx)
END_MESSAGE_MAP()


// CTabTaskInfoDlg ��Ϣ�������


BOOL CTabTaskInfoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	CRect rs;
	GetParent()->GetClientRect(&rs);
	m_ctl.MoveWindow(&rs);

	CString field[] = { _T("����"),  _T("����"), _T("���ȼ�"), _T("��ʼ��"),  _T("Ŀ���") };

	int fieldnum = sizeof(field) / sizeof(field[0]);
	for (int i = 0; i < fieldnum; ++i) {
		// iColΪ�е�λ�ã����㿪ʼ��lpszColumnHeadingΪ��ʾ��������
		// nFormatΪ��ʾ���뷽ʽ�� nWidthΪ��ʾ��ȣ�nSubItemΪ��������е���������
		m_ctl.InsertColumn(i, field[i], LVCFMT_LEFT, 70);
	}

	//m_ctl.ShowScrollBar(SB_HORZ);

	// ��ȡ���ݿ�
	//m_AdoConn.OnInitADOConn();
	//CString sql = _T("select * from tasklist");
	//m_pRs = m_AdoConn.GetRecordSet((_bstr_t)sql);

	//int i = 0;
	//while (!m_pRs->adoEOF) {
	//	m_ctl.InsertItem(i, (_bstr_t)m_pRs->GetCollect("taskid"));
	//	m_ctl.SetItemText(i, 1, (_bstr_t)m_pRs->GetCollect("agvno"));
	//	m_ctl.SetItemText(i, 2, (_bstr_t)m_pRs->GetCollect("priority"));
	//	m_ctl.SetItemText(i, 3, (_bstr_t)m_pRs->GetCollect("startPt"));
	//	m_ctl.SetItemText(i, 4, (_bstr_t)m_pRs->GetCollect("endPt"));

	//	m_pRs->MoveNext();
	//	++i;
	//}

	//m_AdoConn.ExitConn();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}
