
// Thread_EXDlg.cpp : 구현 파일
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

	// 네트워크 카드
	DWORD pcchCounterListLength = 0;
	DWORD pcchInstanceListLength = 0;
	PdhEnumObjectItems(NULL, NULL, TEXT("Network Interface"), NULL, &pcchCounterListLength, NULL, &pcchInstanceListLength, PERF_DETAIL_WIZARD, 0);

	LPTSTR lpCounterList = new TCHAR[pcchCounterListLength];
	m_lpNetAdaptorList = new TCHAR[pcchInstanceListLength];
	if (lpCounterList && m_lpNetAdaptorList) {
		PdhEnumObjectItems(NULL, NULL, TEXT("Network Interface"), lpCounterList, &pcchCounterListLength, m_lpNetAdaptorList, &pcchInstanceListLength, PERF_DETAIL_WIZARD, 0);

		TCHAR* pList = m_lpNetAdaptorList;
		m_NetAdaptorCount = 0; // 어댑터의 개수
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
	//메모리값
	MEMORYSTATUSEX MemoryStatus = { 0 };
	MemoryStatus.dwLength = sizeof(MemoryStatus);
	::GlobalMemoryStatusEx(&MemoryStatus);

	availableMem = (int)((MemoryStatus.ullTotalPhys - MemoryStatus.ullAvailPhys) / (1024 * 1024));
	physicalMem = (int)((MemoryStatus.ullTotalPhys) / (1024 * 1024));
}
void CSystemStatus::getNETStatus(LONG *adapTotalByte, size_t adaptorCount) {
	//네트워크
	PDH_FMT_COUNTERVALUE PFC_Value = { 0 };
	for (int cnt = 0; cnt < adaptorCount; cnt++) {
		PdhGetFormattedCounterValue(m_phCounterNetAdaptor[cnt], PDH_FMT_LONG, NULL, &PFC_Value);
		adapTotalByte[cnt] = PFC_Value.longValue;
	}
}
void CSystemStatus::Update() {
	// 카운트 갱신
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

// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
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


// CThread_EXDlg 대화 상자



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


// CThread_EXDlg 메시지 처리기

BOOL CThread_EXDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
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

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	p1 = NULL;
	CSystemStatus s1;
	s1.Init();

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
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

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CThread_EXDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
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
	// thread 중지
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
		fir->m_staticDisp.Format(_T("%d년 %d월 %d일\n%d시 %d분 %d초"), cTime.GetYear(), cTime.GetMonth(), cTime.GetDay(),
			cTime.GetHour(), cTime.GetMinute(), cTime.GetSecond());
		fir->SetDlgItemText(IDC_STATIC_DISP, fir->m_staticDisp);
		Sleep(1000);
	}
	return 0;
}
