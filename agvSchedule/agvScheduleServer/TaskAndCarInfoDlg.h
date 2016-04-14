#pragma once
#include "afxcmn.h"


// CTaskAndCarInfoDlg �Ի���
class CTabColorDlg;
class CTabControlDlg;
class CTabTaskInfoDlg;
class CTabCarInfoDlg;
class CTaskAndCarInfoDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CTaskAndCarInfoDlg)

public:
	CTaskAndCarInfoDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CTaskAndCarInfoDlg();

	CTabColorDlg*				m_color;
	CTabControlDlg*				m_control;
	CTabTaskInfoDlg*			m_task;
	CTabCarInfoDlg*				m_car;

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_TASK_CAR_INFO };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CTabCtrl m_tab;
	virtual BOOL OnInitDialog();
	virtual void OnCancel();
	afx_msg void OnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
};
