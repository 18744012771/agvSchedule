// TabCarInfoDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "agvScheduleServer.h"
#include "TabCarInfoDlg.h"
#include "afxdialogex.h"


// CTabCarInfoDlg �Ի���

IMPLEMENT_DYNAMIC(CTabCarInfoDlg, CDialogEx)

CTabCarInfoDlg::CTabCarInfoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_CARINFO, pParent)
{

}

CTabCarInfoDlg::~CTabCarInfoDlg()
{
}

void CTabCarInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ctl);
}


BEGIN_MESSAGE_MAP(CTabCarInfoDlg, CDialogEx)
END_MESSAGE_MAP()


// CTabCarInfoDlg ��Ϣ�������


BOOL CTabCarInfoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	CRect rs;
	GetParent()->GetClientRect(&rs);
	m_ctl.MoveWindow(&rs);

	CString field[] = { _T("С����"),  _T("��״̬"), _T("��ǰ��"), _T("Ŀ���"),  _T("��ǰ��") };

	int fieldnum = sizeof(field) / sizeof(field[0]);
	for (int i = 0; i < fieldnum; ++i) {
		m_ctl.InsertColumn(i, field[i], LVCFMT_LEFT, 70);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}
