
// agvScheduleServer.h : agvScheduleServer Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������

#include "ADOConn.h"

// CagvScheduleServerApp:
// �йش����ʵ�֣������ agvScheduleServer.cpp
//

class CagvScheduleServerApp : public CWinApp
{
public:
	CagvScheduleServerApp();

	_RecordsetPtr m_pRs;
	ADOConn m_AdoConn;

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CagvScheduleServerApp theApp;
