#pragma once


// CTabControlDlg �Ի���

class CTabControlDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CTabControlDlg)

public:
	CTabControlDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CTabControlDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_CONTROL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
