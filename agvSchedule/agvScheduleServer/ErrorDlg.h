#pragma once
#include "afxcmn.h"
#include "ADOConn.h"

// CErrorDlg �Ի���

class CErrorDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CErrorDlg)

public:
	CErrorDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CErrorDlg();

	_RecordsetPtr m_pRs;
	ADOConn m_AdoConn;

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_ERROR };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CListCtrl m_ctl;
};
