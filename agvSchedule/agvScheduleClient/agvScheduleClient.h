
// agvScheduleClient.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������

// CagvScheduleClientApp: 
// �йش����ʵ�֣������ agvScheduleClient.cpp
//

class CagvScheduleClientApp : public CWinApp
{
public:
	CagvScheduleClientApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CagvScheduleClientApp theApp;