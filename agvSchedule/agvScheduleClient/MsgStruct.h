#pragma once

/*
	M6: ����Ŀ���
	21 08 41 (21 41 ��ʼ���� 08 ���峤��)
	4D 36 (4D 36��ʾ����Ϣ��M6��Ϣ) 
	01 (��Ϣ��ǩ1-255ѭ������) 
	01 (AGC����) 
	01 00 (��������λ��ָ��2�ֽ�) 
	06 00 (����Ŀ���2�ֽ�)
	��8�ֽ�
*/
struct Msg_M6
{
	const BYTE head[3] = { 0x21, 0x08, 0x41 };		// ��ͷ
	const BYTE type[2] = { 0x4D, 0x36 };			// ��Ϣ����
	BYTE tag = 0;					// ��Ϣ��ǩ
	BYTE agvno = 0;					// AGV����
	UINT16 taskno = 0;				// ������
	UINT16 target = 0;				// ����Ŀ���

	Msg_M6& operator=(const Msg_M6& m6) {
		tag = m6.tag;
		agvno = m6.agvno;
		taskno = m6.taskno;
		target = m6.target;
		return *this;
	}
};

/*
	M1: �ƶ�·��
	21(��ͷ��ʼ��־)10(���峤��) 41(��ͷ������־)
	4D 31(M1)
	01(��Ϣ��ǩ1-255)
	01(AGC����)
	01 00(����������λ�������M6���һ��)
	01(����Ŀ1-25)
	00 02(�����߶κ�,2Bһ��)
	00 03 00 04 00 05 00   ԭ���ϲ������57�ֽ�(0x39)�����������ᳬ��25
*/
struct Msg_M1
{
	const BYTE head[3] = { 0x21, 0x39, 0x41 };
	const BYTE type[2] = { 0x4D, 0x31 };
	BYTE tag = 0;
	BYTE agvno = 0;
	UINT16 taskno = 0;
	BYTE secnum = 0;			// �ε���Ŀ
	UINT16 secno[25] = { 0 };

	Msg_M1& operator=(const Msg_M1& m1) {
		tag = m1.tag;
		agvno = m1.agvno;
		taskno = m1.taskno;
		secnum = m1.secnum;
		memcpy_s(secno, 50, m1.secno, 50);
		return *this;
	}
};


/*
	M2: ���������
	21 08 41
	4D 32(M2)
	01(��Ϣ��ǩ1-255)
	01(AGC����)
	01 00(����������λ�������M6���һ��)
	90 01(���������)
*/
struct Msg_M2
{
	const BYTE head[3] = { 0x21, 0x08, 0x41 };
	const BYTE type[2] = { 0x4D, 0x32 };
	BYTE tag = 0;
	BYTE agvno = 0;
	UINT16 taskno = 0;
	UINT16 taskopcode = 0;			// ���������

	Msg_M2& operator=(const Msg_M2& m2) {
		tag = m2.tag;
		agvno = m2.agvno;
		taskno = m2.taskno;
		taskopcode = m2.taskopcode;
		return *this;
	}
};



/*
	E1: agv�ϱ� 200ms
	45 31
	01 ����
	01 M1��Ϣ��ǩ
	01 M2��Ϣ��ǩ
	01 M6��Ϣ��ǩ
	00 01 ��ǰ���߶ξ���(mm)
	00 01 ��ǰ�κ�
	00 01 ��ǰ���
	00 01 agc״̬λ
	01 agc������
	01 Ԥ��
	00 01 ��ǰ�ٶ�mm/s
	01 �ƶ����&�������
	00 01 ��ǰ�����
	��21�ֽ�
*/
struct Msg_E1
{
	const BYTE type[2] = { 0x45, 0x31 };
	BYTE agvno = 0;
	BYTE m1tag = 0;
	BYTE m2tag = 0;
	BYTE m6tag = 0;
	UINT16 curDist = 0;
	UINT16 curSec = 0;
	UINT16 curPoint = 0;
	UINT16 agcStatus = 0;
	BYTE agcError = 0;
	BYTE reserve = 0;
	UINT16 curSpeed = 0;
	BYTE moveOrOpt = 0;
	UINT16 curTask = 0;
};



struct Msg_M1M2M6
{
	Msg_M1 m1;
	Msg_M2 m2;
	Msg_M6 m6;
};