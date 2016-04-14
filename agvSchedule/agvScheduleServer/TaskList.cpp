// TaskList.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "agvScheduleServer.h"
#include "TaskList.h"
#include "afxdialogex.h"


// CTaskList �Ի���

IMPLEMENT_DYNAMIC(CTaskList, CDialogEx)

CTaskList::CTaskList(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_TASKLIST, pParent)
{

}

CTaskList::~CTaskList()
{
}

void CTaskList::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ctl);
}


BEGIN_MESSAGE_MAP(CTaskList, CDialogEx)
END_MESSAGE_MAP()


// CTaskList ��Ϣ�������


BOOL CTaskList::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	CString field[] = { _T("����"), _T("�����"), _T("����ʱ��"), _T("����"),
		_T("���ȼ�"), _T("��ʼ��"),  _T("Ŀ���"),  _T("��Ϣ��ǩ"),  _T("���������"),
		_T("�·�����"), _T("�����߶�") };

	int fieldnum = sizeof(field) / sizeof(field[0]);
	for (int i = 0; i < fieldnum; ++i) {
		// iColΪ�е�λ�ã����㿪ʼ��lpszColumnHeadingΪ��ʾ��������
		// nFormatΪ��ʾ���뷽ʽ�� nWidthΪ��ʾ��ȣ�nSubItemΪ��������е���������
		m_ctl.InsertColumn(i, field[i], LVCFMT_LEFT, 70);
	}

	m_ctl.ShowScrollBar(SB_HORZ);

	// ��ȡ���ݿ�
	m_AdoConn.OnInitADOConn();
	CString sql = _T("select * from tasklist");
	m_pRs = m_AdoConn.GetRecordSet((_bstr_t)sql);

	//CTime time = CTime::GetCurrentTime();
	int i = 0;
	while (!m_pRs->adoEOF) {
		m_ctl.InsertItem(i, (_bstr_t)m_pRs->GetCollect("taskid"));
		m_ctl.SetItemText(i, 1, (_bstr_t)m_pRs->GetCollect("taskno"));
		m_ctl.SetItemText(i, 2, (_bstr_t)m_pRs->GetCollect("starttime"));
		m_ctl.SetItemText(i, 3, (_bstr_t)m_pRs->GetCollect("agvno"));
		m_ctl.SetItemText(i, 4, (_bstr_t)m_pRs->GetCollect("priority"));
		m_ctl.SetItemText(i, 5, (_bstr_t)m_pRs->GetCollect("startPt"));
		m_ctl.SetItemText(i, 6, (_bstr_t)m_pRs->GetCollect("endPt"));
		m_ctl.SetItemText(i, 7, (_bstr_t)m_pRs->GetCollect("msgtag"));
		m_ctl.SetItemText(i, 8, (_bstr_t)m_pRs->GetCollect("taskOptCode"));
		m_ctl.SetItemText(i, 9, (_bstr_t)m_pRs->GetCollect("sidenum"));
		m_ctl.SetItemText(i, 10, (_bstr_t)m_pRs->GetCollect("sideno"));

		m_pRs->MoveNext();
		++i;
	}

	m_AdoConn.ExitConn();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}
