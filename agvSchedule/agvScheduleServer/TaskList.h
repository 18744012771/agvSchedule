#pragma once
#include "afxcmn.h"
#include "ADOConn.h"


// CTaskList �Ի���

class CTaskList : public CDialogEx
{
	DECLARE_DYNAMIC(CTaskList)

public:
	CTaskList(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CTaskList();

	_RecordsetPtr m_pRs;
	ADOConn m_AdoConn;

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_TASKLIST };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CListCtrl m_ctl;
};
