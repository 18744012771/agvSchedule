#pragma once

#include "ADOConn.h"
#include "afxcmn.h"
// CTabTaskInfoDlg �Ի���

class CTabTaskInfoDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CTabTaskInfoDlg)

public:
	CTabTaskInfoDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CTabTaskInfoDlg();

	_RecordsetPtr m_pRs;
	ADOConn m_AdoConn;

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_TASKINFO };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CListCtrl m_ctl;
};
