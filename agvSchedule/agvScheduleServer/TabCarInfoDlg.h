#pragma once
#include "afxcmn.h"


// CTabCarInfoDlg �Ի���

class CTabCarInfoDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CTabCarInfoDlg)

public:
	CTabCarInfoDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CTabCarInfoDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_CARINFO };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_ctl;
	virtual BOOL OnInitDialog();
};
