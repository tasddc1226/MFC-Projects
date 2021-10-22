
// Thread_EXDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "Thread_EX.h"
#include "Thread_EXDlg.h"
#include "afxdialogex.h"
#include <string>
#include <tchar.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CSystemStatus::CSystemStatus(void)
	:m_hQuery(NULL), m_hCounterCPUTotal(NULL), m_CPUCoreCount(0), m_phCounterCPUCore(nullptr), m_NetAdaptorCount(0)
{
}

CSystemStatus::~CSystemStatus(void)
{
}

void CSystemStatus::Init() {
	PdhOpenQuery(NULL, 0, &m_hQuery);

	// CPU Total
	PdhAddCounter(m_hQuery, TEXT("\\Processor(_Total)\\% Processor Time"), 1, &m_hCounterCPUTotal);

	// CPU core information
	SYSTEM_INFO SystemInfo = { 0 };
	if (SystemInfo.dwNumberOfProcessors > 0) {
		m_CPUCoreCount = SystemInfo.dwNumberOfProcessors;
		m_phCounterCPUCore = new HCOUNTER[m_CPUCoreCount];
		for (int cnt = 0; cnt < m_CPUCoreCount; cnt++) {
			TCHAR szFullCounterPath[1024] = { 0 };
			wsprintf(szFullCounterPath, TEXT("\\Processor(%d)\\%% Processor Time"), cnt);
			PdhAddCounter(m_hQuery, szFullCounterPath, 1, &m_phCounterCPUCore[cnt]);
		}
	}

	// ��Ʈ��ũ ī��
	DWORD pcchCounterListLength = 0;
	DWORD pcchInstanceListLength = 0;
	PdhEnumObjectItems(NULL, NULL, TEXT("Network Interface"), NULL, &pcchCounterListLength, NULL, &pcchInstanceListLength, PERF_DETAIL_WIZARD, 0);

	LPTSTR lpCounterList = new TCHAR[pcchCounterListLength];
	m_lpNetAdaptorList = new TCHAR[pcchInstanceListLength];
	if (lpCounterList && m_lpNetAdaptorList) {
		PdhEnumObjectItems(NULL, NULL, TEXT("Network Interface"), lpCounterList, &pcchCounterListLength, m_lpNetAdaptorList, &pcchInstanceListLength, PERF_DETAIL_WIZARD, 0);

		TCHAR* pList = m_lpNetAdaptorList;
		m_NetAdaptorCount = 0; // ������� ����
		while (*pList) {
			m_NetAdaptorCount++;
			pList += (1 + _tcslen(pList));
		}

		m_phCounterNetAdaptor = new HCOUNTER[m_NetAdaptorCount];
		memset(m_phCounterNetAdaptor, 0, sizeof(HCOUNTER)*m_NetAdaptorCount);

		TCHAR* szInstanceName = m_lpNetAdaptorList;
		for (size_t cnt = 0; cnt < m_NetAdaptorCount; cnt++) {
			TCHAR szFullCounterPath[1024] = { 0 };
			DWORD dwFullPathSize = 1024;

			PDH_COUNTER_PATH_ELEMENTS pcpe = { 0 };
			pcpe.szObjectName = TEXT("Network Interface");
			pcpe.szInstanceName = szInstanceName;
			pcpe.dwInstanceIndex = -1;
			pcpe.szCounterName = TEXT("Bytes Total/sec");
			PdhMakeCounterPath(&pcpe, szFullCounterPath, &dwFullPathSize, 0);
			PdhAddCounter(m_hQuery, szFullCounterPath, 1, &m_phCounterNetAdaptor[cnt]);

			szInstanceName += (1 + _tcslen(szInstanceName));
		}
		delete lpCounterList;
	}
}

void CSystemStatus::getCPUStatus(LONG &total, LONG* arrCore, size_t arrCoreSize) {
	PDH_FMT_COUNTERVALUE PFC_Value = { 0 };
	PdhGetFormattedCounterValue(m_hCounterCPUTotal, PDH_FMT_LONG, NULL, &PFC_Value);
	total = PFC_Value.longValue;

	if (arrCore != nullptr && arrCoreSize > 0) {
		for (size_t c1 = 0; c1 < arrCoreSize; c1++) {
			PDH_FMT_COUNTERVALUE PFC_Value = { 0 };
			PdhGetFormattedCounterValue(m_phCounterCPUCore[c1], PDH_FMT_LONG, NULL, &PFC_Value);
			arrCore[c1] = PFC_Value.longValue;
		}
	}
}

void CSystemStatus::getRAMStatus(int &availableMem, int &physicalMem) {
	//�޸𸮰�
	MEMORYSTATUSEX MemoryStatus = { 0 };
	MemoryStatus.dwLength = sizeof(MemoryStatus);
	::GlobalMemoryStatusEx(&MemoryStatus);

	availableMem = (int)((MemoryStatus.ullTotalPhys - MemoryStatus.ullAvailPhys) / (1024 * 1024));
	physicalMem = (int)((MemoryStatus.ullTotalPhys) / (1024 * 1024));
}
void CSystemStatus::getNETStatus(LONG *adapTotalByte, size_t adaptorCount) {
	//��Ʈ��ũ
	PDH_FMT_COUNTERVALUE PFC_Value = { 0 };
	for (int cnt = 0; cnt < adaptorCount; cnt++) {
		PdhGetFormattedCounterValue(m_phCounterNetAdaptor[cnt], PDH_FMT_LONG, NULL, &PFC_Value);
		adapTotalByte[cnt] = PFC_Value.longValue;
	}
}
void CSystemStatus::Update() {
	// ī��Ʈ ����
	PdhCollectQueryData(m_hQuery);
}
void CSystemStatus::Terminate() {
	PdhRemoveCounter(m_hCounterCPUTotal);

	for (int cnt = 0; cnt < m_CPUCoreCount; cnt++)
		PdhRemoveCounter(m_phCounterCPUCore[cnt]);
	delete(m_phCounterCPUCore);
	for (int cnt = 0; cnt < m_NetAdaptorCount; cnt++)
		PdhRemoveCounter(m_phCounterNetAdaptor[cnt]);
	delete[] m_phCounterNetAdaptor;
	delete[] m_lpNetAdaptorList;
}

// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

// �����Դϴ�.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CThread_EXDlg ��ȭ ����



CThread_EXDlg::CThread_EXDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_THREAD_EX_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CThread_EXDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CThread_EXDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON1, &CThread_EXDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CThread_EXDlg::OnBnClickedButton2)
	
END_MESSAGE_MAP()


// CThread_EXDlg �޽��� ó����

BOOL CThread_EXDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// �� ��ȭ ������ �������� �����մϴ�.  ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	p1 = NULL;
	CSystemStatus s1;
	s1.Init();

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

void CThread_EXDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�.  ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CThread_EXDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CThread_EXDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CThread_EXDlg::OnBnClickedButton1()
{
	p1 = AfxBeginThread(TimeThread, this);

	if (p1 == NULL) {
		AfxMessageBox(L"Error!");
	}
}

void CThread_EXDlg::OnBnClickedButton2()
{
	// thread ����
	if (NULL != p1) {
		::SuspendThread(p1->m_hThread);
	}
	SYSTEM_INFO stSysInfo;
	GetSystemInfo(&stSysInfo);
	
}

UINT CThread_EXDlg::TimeThread(LPVOID _mothod)
{
	CThread_EXDlg *fir = (CThread_EXDlg*)_mothod;
	while (1) {
		CTime cTime = CTime::GetCurrentTime();
		fir->m_staticDisp.Format(_T("%d�� %d�� %d��\n%d�� %d�� %d��"), cTime.GetYear(), cTime.GetMonth(), cTime.GetDay(),
			cTime.GetHour(), cTime.GetMinute(), cTime.GetSecond());
		fir->SetDlgItemText(IDC_STATIC_DISP, fir->m_staticDisp);
		Sleep(1000);
	}
	return 0;
}
