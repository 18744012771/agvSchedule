#pragma once


// CTabColorDlg �Ի���

class CTabColorDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CTabColorDlg)

public:
	CTabColorDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CTabColorDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_COLOR };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
