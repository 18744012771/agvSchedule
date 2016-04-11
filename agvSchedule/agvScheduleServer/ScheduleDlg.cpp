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
	Dijkstra(pClient->m_e1.curPoint, targetno);
	auto& vecRoute = m_pDoc->m_vecRoute;
	m_m1.secnum = (BYTE)vecRoute.size() - 1; // ����
	// �����߶�
	auto& mapSideNo = m_pDoc->m_sideNo; //<�Σ��κ�>
	auto it = vecRoute.begin();
	int prevSide = *it;
	std::advance(it, 1);
	int i = 0; // ���ƶ�����
	for (auto it2 = it; it2 != vecRoute.end(); ++it2)
	{
		unsigned sideNo = mapSideNo[make_pair(prevSide, *it2)];
		prevSide = *it2;
		m_m1.secno[i++] = sideNo;
	}

	Msg_M1M2M6 m1m2m6;
	m1m2m6.m1 = m_m1;
	m1m2m6.m2 = m_m2;
	m1m2m6.m6 = m_m6;

	// ��С������M1,M2,M6��Ϣ
	pClient->Send(&m1m2m6, sizeof(m1m2m6));

	CDialogEx::OnOK();
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