// TaskAndCarInfoDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "agvScheduleServer.h"
#include "TaskAndCarInfoDlg.h"
#include "afxdialogex.h"

#include "TabColorDlg.h"
#include "TabControlDlg.h"
#include "TabTaskInfoDlg.h"
#include "TabCarInfoDlg.h"

// CTaskAndCarInfoDlg �Ի���

IMPLEMENT_DYNAMIC(CTaskAndCarInfoDlg, CDialogEx)

CTaskAndCarInfoDlg::CTaskAndCarInfoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_TASK_CAR_INFO, pParent)
{

}

CTaskAndCarInfoDlg::~CTaskAndCarInfoDlg()
{
}

void CTaskAndCarInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB1, m_tab);
}


BEGIN_MESSAGE_MAP(CTaskAndCarInfoDlg, CDialogEx)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CTaskAndCarInfoDlg::OnSelchangeTab1)
END_MESSAGE_MAP()


// CTaskAndCarInfoDlg ��Ϣ�������


BOOL CTaskAndCarInfoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_color = new CTabColorDlg;
	m_control = new CTabControlDlg;
	m_task = new CTabTaskInfoDlg;
	m_car = new CTabCarInfoDlg;

	m_tab.InsertItem(0, _T("��ɫע��"));
	m_tab.InsertItem(1, _T("�������"));
	m_tab.InsertItem(2, _T("������Ϣ"));
	m_tab.InsertItem(3, _T("������Ϣ"));

	m_color->Create(IDD_DIALOG_COLOR, this);
	m_control->Create(IDD_DIALOG_CONTROL, this);
	m_task->Create(IDD_DIALOG_TASKINFO, this);
	m_car->Create(IDD_DIALOG_CARINFO, this);

	// �ƶ��Ի���
	CRect rs;
	m_tab.GetClientRect(&rs);
	rs.top += 33;
	rs.bottom += 8;
	rs.left -= 8;
	rs.right += 8;

	m_color->MoveWindow(&rs);
	m_control->MoveWindow(&rs);
	m_task->MoveWindow(&rs);
	m_car->MoveWindow(&rs);

	m_color->ShowWindow(TRUE);
	m_control->ShowWindow(FALSE);
	m_task->ShowWindow(FALSE);
	m_car->ShowWindow(FALSE);
	
	m_tab.SetCurSel(0);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}


void CTaskAndCarInfoDlg::OnCancel()
{
	// TODO: �ڴ����ר�ô����/����û���
	//if (m_color) {
	//	delete m_color; m_color = nullptr;
	//	delete m_control; m_control = nullptr;
	//	delete m_task; m_task = nullptr;
	//	delete m_car; m_car = nullptr;
	//}

	CDialogEx::OnCancel();
}


void CTaskAndCarInfoDlg::OnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int sel = m_tab.GetCurSel();
	switch (sel)
	{
	case 0:
		m_color->ShowWindow(TRUE);
		m_control->ShowWindow(FALSE);
		m_task->ShowWindow(FALSE);
		m_car->ShowWindow(FALSE);
		break;
	case 1:
		m_color->ShowWindow(FALSE);
		m_control->ShowWindow(TRUE);
		m_task->ShowWindow(FALSE);
		m_car->ShowWindow(FALSE);
		break;
	case 2:
		m_color->ShowWindow(FALSE);
		m_control->ShowWindow(FALSE);
		m_task->ShowWindow(TRUE);
		m_car->ShowWindow(FALSE);
		break;
	case 3:
		m_color->ShowWindow(FALSE);
		m_control->ShowWindow(FALSE);
		m_task->ShowWindow(FALSE);
		m_car->ShowWindow(TRUE);
		break;
	}

	*pResult = 0;
}
