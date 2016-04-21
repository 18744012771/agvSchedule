#pragma once

/*
	״̬ö��
*/
enum CAR_STATE
{
	UNKNOWN = 0,	// δ֪ AGV����ϵͳδ�ܶ�����С������Ϣ��С��δ���뵽ϵͳ��
	FREE,			// ���� ����δ����������
	ASSIGNMENTED,	// �ѷ��� �����ѱ���������
	LINKED,			// ������ һ����С���Ѿ�����װ��վ̨�����ػ�״̬
	CANCELED		// ȡ�� С�����ڼ�ͣ���ֶ�״̬

	//LOADING = 0x1,  // �ػ�
	//OBSTACLE = 0x4,	// ��⵽�ϰ���
	//CARERROR = 0x8,	// ����
	//LOWPOWER = 0x10,	// �͵���
	//PLUGIN = 0x400,		// ����ϵͳ
	//ONLINE = 0x800,		// ����
	//SCRAM = 0x1000,		// ��ͣ
};

/*
	С��״̬����
*/

class ICarState
{
protected:
	//BYTE		m_agvno; // ����
	//CAR_STATE	m_state;

public:
	virtual CAR_STATE SetCurCarState() { return UNKNOWN;  }
	virtual BOOL SetOnline() { return TRUE;  }
	virtual BOOL SetOffline() { return TRUE;  }
	virtual BOOL StartUp() { return TRUE;  }
	virtual BOOL Stop(){ return TRUE;  }
	virtual BOOL SetAllOnline() { return TRUE;  }
};


// �̳���ICar��״̬С��
// δ֪
class CCarUnknown : public ICarState
{
public:
	virtual CAR_STATE SetCurCarState() { return UNKNOWN;  }
	virtual BOOL SetOnline() { return TRUE;  }
	virtual BOOL SetOffline() { return TRUE;  }
	virtual BOOL StartUp() { return TRUE;  }
	virtual BOOL Stop() { return TRUE;  }
	virtual BOOL SetAllOnline() { return TRUE;  }
};



// ����
class CCarFree : public ICarState
{
public:
	virtual CAR_STATE SetCurCarState() { return FREE; }
	virtual BOOL SetOnline() { return TRUE;  }
	virtual BOOL SetOffline() { return TRUE;  }
	virtual BOOL StartUp() { return TRUE;  }
	virtual BOOL Stop() { return TRUE;  }
	virtual BOOL SetAllOnline() { return TRUE;  }
};

// �ѷ���
class CCarAssignmented : public ICarState
{
public:
	virtual CAR_STATE SetCurCarState() { return ASSIGNMENTED; }
	virtual BOOL SetOnline() { return TRUE;  }
	virtual BOOL SetOffline() { return TRUE;  }
	virtual BOOL StartUp() { return TRUE;  }
	virtual BOOL Stop() { return TRUE;  }
	virtual BOOL SetAllOnline() { return TRUE;  }
};

// ������
class CCarLinked : public ICarState
{
public:
	virtual CAR_STATE SetCurCarState() { return LINKED; }
	virtual BOOL SetOnline() { return TRUE;  }
	virtual BOOL SetOffline() { return TRUE;  }
	virtual BOOL StartUp() { return TRUE;  }
	virtual BOOL Stop() { return TRUE;  }
	virtual BOOL SetAllOnline() { return TRUE;  }
};

// ȡ��
class CCarCanceled : public ICarState
{
public:
	virtual CAR_STATE SetCurCarState() { return CANCELED; }
	virtual BOOL SetOnline() { return TRUE;  }
	virtual BOOL SetOffline() { return TRUE;  }
	virtual BOOL StartUp() { return TRUE;  }
	virtual BOOL Stop() { return TRUE;  }
	virtual BOOL SetAllOnline() { return TRUE;  }
};




