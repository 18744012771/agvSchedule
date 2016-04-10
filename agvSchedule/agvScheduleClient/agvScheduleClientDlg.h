
// agvScheduleClientDlg.h : ͷ�ļ�
//

#pragma once


// CagvScheduleClientDlg �Ի���
class CAgvSocket;
class CagvScheduleClientDlg : public CDialogEx
{
// ����
public:
	CagvScheduleClientDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_AGVSCHEDULECLIENT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

private:
	CAgvSocket*				m_pAgvSocket = NULL;

public:
	afx_msg void OnClickedButtonConnect();
	afx_msg void OnClickedButtonQuit();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
