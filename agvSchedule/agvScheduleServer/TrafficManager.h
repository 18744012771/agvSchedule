#pragma once

/*
	��ͨ����ģ�飨����������
	С����/����
	ȫ����/����
	������ֹͣ
	״̬ģʽ

*/


#include <map>

class ICarState;
enum CAR_STATE;
class CTrafficManager
{
private:

public:
	void SetCurCar(BYTE carno);
	void SetCurCarState();
	
// all user operator
	BOOL SetOnline();	// С������
	BOOL SetOffline();  // С������
	BOOL StartUp();		// С������
	BOOL Stop();		// С��ֹͣ
	BOOL SetAllOnline();// ȫ������
	
	std::map<BYTE, ICarState*>		m_mapCarState;  // ��ͬС���ĵ�ǰ״̬
	BYTE		m_curCarno;	// ��ǰС��
	CAR_STATE   m_curState; // ��ǰС��״̬

};