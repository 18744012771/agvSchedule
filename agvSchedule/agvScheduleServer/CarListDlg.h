#pragma once
#include "afxcmn.h"
#include "ADOConn.h"

// CCarListDlg �Ի���

class CCarListDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CCarListDlg)

public:
	CCarListDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CCarListDlg();

	_RecordsetPtr m_pRs;
	ADOConn m_AdoConn;

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_CARLIST };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CListCtrl m_ctl;
};
