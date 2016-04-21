// ScheduleDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "agvScheduleServer.h"
#include "ScheduleDlg.h"
#include "afxdialogex.h"

#include "Graph.h"
#include "agvScheduleServerDoc.h"
#include "NetSocketDef.h"

// ��Ϣ��ǩ 1-255ѭ��ʹ��
static BYTE MSG_TAG = 0;
static UINT16 MSG_TASK = 0;

// CScheduleDlg �Ի���

IMPLEMENT_DYNAMIC(CScheduleDlg, CDialogEx)

//CScheduleDlg::CScheduleDlg(CWnd* pParent /*=NULL*/)
//	: CDialogEx(IDD_DIALOG_SCHEDULE, pParent)
//{
//	m_baseGraph = new Graph();
//}

CScheduleDlg::CScheduleDlg(CagvScheduleServerDoc* pDoc, CWnd* pParent)
	: m_pDoc(pDoc), CDialogEx(IDD_DIALOG_SCHEDULE, pParent)
{
	m_baseGraph = new Graph();
}

CScheduleDlg::~CScheduleDlg()
{
}

void CScheduleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_AGCNO, m_comboAGCNo);
	DDX_Control(pDX, IDC_COMBO_OPT, m_comboOpt);
	DDX_Control(pDX, IDC_COMBO_TARGETNO, m_comboTargetNo);
}


BEGIN_MESSAGE_MAP(CScheduleDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CScheduleDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDM2, &CScheduleDlg::OnClickedIdm2)
	ON_BN_CLICKED(IDM1, &CScheduleDlg::OnClickedIdm1)
END_MESSAGE_MAP()


// CScheduleDlg ��Ϣ�������


BOOL CScheduleDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	CString str;
	for (int i = 1; i < 11; ++i)
	{
		str.Format(_T("%d"), i);
		m_comboAGCNo.AddString(str);
	}
	m_comboAGCNo.SetCurSel(0);

	for (int i = 1; i < 201; ++i)
	{
		str.Format(_T("%d"), i);
		m_comboTargetNo.AddString(str);
	}
	m_comboTargetNo.SetCurSel(0);

	CString strOpt[] = { _T("��ͣ"), _T("�ƶ�"), _T("װ��"), _T("ж��")  };
	for (int i = 0; i < 4; ++i)
	{
		m_comboOpt.AddString(strOpt[i]);
		m_comboOpt.SetItemData(i, i);
	}
	m_comboOpt.SetCurSel(0);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}


void CScheduleDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString strAGCNo, strTargetNo, strOpt;
	m_comboAGCNo.GetWindowTextW(strAGCNo);
	m_comboTargetNo.GetWindowTextW(strTargetNo);
	m_comboOpt.GetWindowTextW(strOpt);

	if (strAGCNo.IsEmpty() || strTargetNo.IsEmpty()
		|| strOpt.IsEmpty())
	{
		AfxMessageBox(_T("�����복�ţ�Ŀ���źͲ�����"));
		return;
	}

	// ����ת��
	BYTE agvno = _ttoi(strAGCNo);
	UINT16 targetno = _ttoi(strTargetNo);
	UINT16 opt = (UINT16)m_comboOpt.GetItemData(m_comboOpt.GetCurSel());

	if (++MSG_TAG > 255)
		MSG_TAG = 0;

	// ������
	UINT16 taskno = ++MSG_TASK;

	// ��Ҫ����E1��Ϣ�����е�M6������tag��һ��Ҫ�ط�
	m_m6.tag = MSG_TAG;
	m_m6.agvno = agvno;
	m_m6.taskno = taskno;
	m_m6.target = targetno;
	
	m_m2.tag = MSG_TAG;
	m_m2.agvno = agvno;
	m_m2.taskno = taskno;
	m_m2.taskopcode = opt;

	m_m1.tag = MSG_TAG;
	m_m1.agvno = agvno;
	m_m1.taskno = taskno;
	// �����������߶κ� ͨ��Dijkstra�㷨����
	// ��ȡС����ǰ���
	CObList& clientList = m_pDoc->m_pListenSocket->m_clientList;
	POSITION pos = clientList.GetHeadPosition();
	CClientSocket* pClient = NULL;
	while (pos)
	{
		pClient = (CClientSocket*)clientList.GetNext(pos);
		if (pClient->m_e1.agvno == agvno)
			break;
	}
	
	// �������·��
	if (!pClient) {
		AfxMessageBox(_T("��û���κ�С�����ӣ�"));
		return;
	}

	pClient->m_targetPt = targetno;

	Dijkstra(pClient->m_e1.curPoint, targetno);
	auto& vecRoute = m_pDoc->m_vecRoute;
	m_m1.secnum = (BYTE)vecRoute.size() - 1; // ����
	// �����߶�
	auto& mapSideNo = m_pDoc->m_sideNo; //<�Σ��κ�>
	auto it = vecRoute.begin();
	int prevSide = *it;
	std::advance(it, 1);
	int i = 0; // ���ƶ�����
	CString strSideNo, strTemp; // ���
	for (auto it2 = it; it2 != vecRoute.end(); ++it2)
	{
		unsigned sideNo = mapSideNo[make_pair(prevSide, *it2)];
		prevSide = *it2;
		memcpy_s(m_m1.secno + i, 50, (char*)&sideNo, 2);
		i += 2;
		strTemp.Format(_T("%d-"), sideNo);
		strSideNo += strTemp;
	}
	if (strSideNo.IsEmpty())
		strSideNo = _T("''");

	Msg_M1M2M6 m1m2m6;
	m1m2m6.m1 = m_m1;
	m1m2m6.m2 = m_m2;
	m1m2m6.m6 = m_m6;

	// д�����ݿ�
	//m_AdoConn.OnInitADOConn();
	//CTime tm = CTime::GetCurrentTime();
	//CString strTm;
	//strTm.Format(_T("%04d/%02d/%02d %02d:%02d:%02d"),
	//	tm.GetYear(), tm.GetMonth(), tm.GetDay(), tm.GetHour(), tm.GetMinute(), tm.GetSecond());
	//CString str; //
	//str.Format(_T("%d,\'%s\',%d,%d,%d,%d,%d,%d,%d,\'%s\'"),
	//	taskno, strTm, agvno, 1, pClient->m_e1.curPoint, \
	//	targetno, MSG_TAG, opt, m_m1.secnum, strSideNo);
	//CString sql = _T("insert into tasklist (")  \
	//	_T("taskno,starttime,agvno,priority,startPt,endPt,msgtag,taskOptCode,sidenum,sideno) ")  \
	//	_T("values(") + str + _T(")");
	//m_AdoConn.ExecuteSQL((_bstr_t)sql);
	//m_AdoConn.ExitConn();

	// ��С������M1,M2,M6��Ϣ
	BYTE buf[11] = { 0 };
	SetBufm6(buf, m_m6);
	int sendBytes = pClient->Send(buf, 11);
	//BYTE buf[82] = { 0 }; // 11(m6) + 11(m2) + 60(m1)
	//SetBuf(buf, m_m6, m_m1, m_m2);
	//int sendBytes = pClient->Send(buf, 82);

	//while(1) {
	//	if (pClient->m_e1.m6tag == m_m6.tag) {
	//		BYTE buf[11] = { 0 };
	//		SetBufm2(buf, m_m2);
	//		sendBytes = pClient->Send(buf, 11);
	//	}	
	//}

	CDialogEx::OnOK();
}

void CScheduleDlg::OnClickedIdm2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CObList& clientList = m_pDoc->m_pListenSocket->m_clientList;
	POSITION pos = clientList.GetHeadPosition();
	CClientSocket* pClient = NULL;
	while (pos)
	{
		pClient = (CClientSocket*)clientList.GetNext(pos);
	}

	if (pClient->m_e1.m6tag == m_m6.tag) {
		BYTE buf[11] = { 0 };
		SetBufm2(buf, m_m2);
		int sendBytes = pClient->Send(buf, 11);
	}	

	CDialogEx::OnOK();
}


void CScheduleDlg::OnClickedIdm1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CObList& clientList = m_pDoc->m_pListenSocket->m_clientList;
	POSITION pos = clientList.GetHeadPosition();
	CClientSocket* pClient = NULL;
	while (pos)
	{
		pClient = (CClientSocket*)clientList.GetNext(pos);
	}

	if (pClient->m_e1.m2tag == m_m2.tag) {
		char buf[60] = { 0 };
		SetBufm1(buf, m_m1);
		int sendBytes = pClient->Send(buf, 60);
		int n = sendBytes;
	}

	CDialogEx::OnOK();
}


void CScheduleDlg::SetBufm6(BYTE* buf, const Msg_M6& m6)
{
	int i = 0;
	buf[i++] = m6.head[0];
	buf[i++] = m6.head[1];
	buf[i++] = m6.head[2];
	buf[i++] = m6.type[0];
	buf[i++] = m6.type[1];
	buf[i++] = m6.tag;
	buf[i++] = m6.agvno;
	memcpy_s(buf + i, 11, (BYTE*)&m6.taskno, 2);
	i += 2;
	memcpy_s(buf + i, 11, (BYTE*)&m6.target, 2);
}

void CScheduleDlg::SetBufm2(BYTE* buf, const Msg_M2& m2)
{
	int i = 0;
	buf[i++] = m2.head[0];
	buf[i++] = m2.head[1];
	buf[i++] = m2.head[2];
	buf[i++] = m2.type[0];
	buf[i++] = m2.type[1];
	buf[i++] = m2.tag;
	buf[i++] = m2.agvno;
	memcpy_s(buf + i, 11, (BYTE*)&m2.taskno, 2);
	i += 2;
	memcpy_s(buf + i, 11, (BYTE*)&m2.taskopcode, 2);
}

void CScheduleDlg::SetBufm1(char* buf, const Msg_M1& m1)
{
	int i = 0;
	buf[i++] = m1.head[0];
	buf[i++] = m1.head[1];
	buf[i++] = m1.head[2];
	buf[i++] = m1.type[0];
	buf[i++] = m1.type[1];
	buf[i++] = m1.tag;
	buf[i++] = m1.agvno;

	memcpy_s(buf + i, 60, (BYTE*)&m1.taskno, 2);
	i += 2;
	buf[i++] = m1.secnum;
	char* pSecno = (char*)&m1.secno;
	while (i < 58) {
		memcpy_s(buf + i, 82, pSecno, 2);
		pSecno += 2;
		i += 2;
	}
}

void CScheduleDlg::SetBuf(BYTE* buf, const Msg_M6& m6, const Msg_M1& m1, const Msg_M2& m2)
{
	int im6(11), im2(22);
	int i = 0;
	buf[i++] = m6.head[0];
	buf[i++] = m6.head[1];
	buf[i++] = m6.head[2];
	buf[i++] = m6.type[0];
	buf[i++] = m6.type[1];
	buf[i++] = m6.tag;
	buf[i++] = m6.agvno;
	memcpy_s(buf + i, 82, (BYTE*)&m6.taskno, 2);
	i += 2;
	memcpy_s(buf + i, 82, (BYTE*)&m6.target, 2);

	i = 0;
	buf[i++ + im6] = m2.head[0];
	buf[i++ + im6] = m2.head[1];
	buf[i++ + im6] = m2.head[2];
	buf[i++ + im6] = m2.type[0];
	buf[i++ + im6] = m2.type[1];
	buf[i++ + im6] = m2.tag;
	buf[i++ + im6] = m2.agvno;
	memcpy_s(buf + i + im6, 82, (BYTE*)&m2.taskno, 2);
	i += 2;
	memcpy_s(buf + i + im6, 82, (BYTE*)&m2.taskopcode, 2);

	i = 0;
	buf[i++ + im2] = m1.head[0];
	buf[i++ + im2] = m1.head[1];
	buf[i++ + im2] = m1.head[2];
	buf[i++ + im2] = m1.type[0];
	buf[i++ + im2] = m1.type[1];
	buf[i++ + im2] = m1.tag;
	buf[i++ + im2] = m1.agvno;
	memcpy_s(buf + i + im2, 82, (BYTE*)&m1.taskno, 2);
	i += 2;
	buf[i++ + im2] = m1.secnum;
	BYTE* pSecno = (BYTE*)&m1.secno;
	while (i < 58) {
		memcpy_s(buf + i + im2, 82, pSecno, 2);
		pSecno += 2;
		i += 2;
	}
	//for (int j = 0; j < 50; j += 2) {
	//	memcpy_s(buf + i + im2, 82, (BYTE*)&(m1.secno + j), 2);
	//	i += 2;
	//}
}


BOOL CScheduleDlg::Dijkstra(UINT16 src, UINT16 des)
{
	Vertex te;
	list<Vertex> newList;

	// ���ɶκ�
	static bool bGen = true;
	if (bGen) {
		m_baseGraph->generateSideNo();
		bGen = false;
	}

	te.vertexNo = src;
	m_baseGraph->UnweightedGraph(&te);

	memset(&te, 0, sizeof(Vertex));
	te.vertexNo = des;
	m_baseGraph->printPath(&te);
	//TRACE("Target(%d)\n", TARGET_VERTEX);
	m_baseGraph->GetRoute().push_back(des);
	m_baseGraph->ResetVertex(); // ���ù�ϵ�����ֻ��2-3������3-2������

	// ���ݵ�doc��ȥ
	m_pDoc->m_vecRoute = std::move(m_baseGraph->GetRoute());
	m_pDoc->m_sideNo = std::move(m_baseGraph->GetSideNoMap());

	return TRUE;
}



