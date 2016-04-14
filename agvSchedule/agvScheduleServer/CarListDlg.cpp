// CarListDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "agvScheduleServer.h"
#include "CarListDlg.h"
#include "afxdialogex.h"


// CCarListDlg �Ի���

IMPLEMENT_DYNAMIC(CCarListDlg, CDialogEx)

CCarListDlg::CCarListDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_CARLIST, pParent)
{

}

CCarListDlg::~CCarListDlg()
{
}

void CCarListDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ctl);
}


BEGIN_MESSAGE_MAP(CCarListDlg, CDialogEx)
END_MESSAGE_MAP()


// CCarListDlg ��Ϣ�������


BOOL CCarListDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	CString field[] = { _T("С����"),_T("�����"), _T("��ǰ��"), _T("��ǰ��"),
		_T("Ŀ���"),_T("������"),_T("״̬"), _T("������") };

	int fieldnum = sizeof(field) / sizeof(field[0]);
	for (int i = 0; i < fieldnum; ++i) {
		// iColΪ�е�λ�ã����㿪ʼ��lpszColumnHeadingΪ��ʾ��������
		// nFormatΪ��ʾ���뷽ʽ�� nWidthΪ��ʾ��ȣ�nSubItemΪ��������е���������
		m_ctl.InsertColumn(i, field[i], LVCFMT_LEFT, 60);
	}

	m_ctl.ShowScrollBar(SB_HORZ);

	// ��ȡ���ݿ�
	m_AdoConn.OnInitADOConn();
	CString sql = _T("select * from carlist");
	m_pRs = m_AdoConn.GetRecordSet((_bstr_t)sql);

	//CTime time = CTime::GetCurrentTime();
	int i = 0;
	while (!m_pRs->adoEOF) {
		m_ctl.InsertItem(i, (_bstr_t)m_pRs->GetCollect("carno"));
		m_ctl.SetItemText(i, 1, (_bstr_t)m_pRs->GetCollect("taskno"));
		m_ctl.SetItemText(i, 2, (_bstr_t)m_pRs->GetCollect("curPoint"));
		m_ctl.SetItemText(i, 3, (_bstr_t)m_pRs->GetCollect("curSide"));
		m_ctl.SetItemText(i, 4, (_bstr_t)m_pRs->GetCollect("targetPoint"));
		m_ctl.SetItemText(i, 5, (_bstr_t)m_pRs->GetCollect("optCode"));
		m_ctl.SetItemText(i, 6, (_bstr_t)m_pRs->GetCollect("agcStatus"));
		m_ctl.SetItemText(i, 7, (_bstr_t)m_pRs->GetCollect("agcErrCode"));

		m_pRs->MoveNext();
		++i;
	}
	m_AdoConn.ExitConn();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}
