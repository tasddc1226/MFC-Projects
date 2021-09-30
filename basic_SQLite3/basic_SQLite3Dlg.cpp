
// basic_SQLite3Dlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "basic_SQLite3.h"
#include "basic_SQLite3Dlg.h"
#include "afxdialogex.h"

#include "sqlite3.h"
#include <assert.h>

#pragma comment(lib, "sqlite3.lib")
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// SQLite는 UTF8을 사용하기 때문에 코드 변환이 필요합니다.
int AnsiToUTF8(char* szSrc, char* strDest, int destSize)
{
	WCHAR 	szUnicode[255];
	char 	szUTF8code[255];

	int nUnicodeSize = MultiByteToWideChar(CP_ACP, 0, szSrc, (int)strlen(szSrc), szUnicode, sizeof(szUnicode));
	int nUTF8codeSize = WideCharToMultiByte(CP_UTF8, 0, szUnicode, nUnicodeSize, szUTF8code, sizeof(szUTF8code), NULL, NULL);
	assert(destSize > nUTF8codeSize);
	memcpy(strDest, szUTF8code, nUTF8codeSize);
	strDest[nUTF8codeSize] = 0;
	return nUTF8codeSize;
}

int UTF8ToAnsi(char* szSrc, char* strDest, int destSize)
{
	WCHAR 	szUnicode[255];
	char 	szAnsi[255];

	int nSize = MultiByteToWideChar(CP_UTF8, 0, szSrc, -1, 0, 0);
	int nUnicodeSize = MultiByteToWideChar(CP_UTF8, 0, szSrc, -1, szUnicode, nSize);
	int nAnsiSize = WideCharToMultiByte(CP_ACP, 0, szUnicode, nUnicodeSize, szAnsi, sizeof(szAnsi), NULL, NULL);
	assert(destSize > nAnsiSize);
	memcpy(strDest, szAnsi, nAnsiSize);
	strDest[nAnsiSize] = 0;
	return nAnsiSize;
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


// Cbasic_SQLite3Dlg 대화 상자



Cbasic_SQLite3Dlg::Cbasic_SQLite3Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_BASIC_SQLITE3_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Cbasic_SQLite3Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_name);
	DDX_Control(pDX, IDC_EDIT2, m_tel);
	DDX_Control(pDX, IDC_LIST2, m_list);
	DDX_Control(pDX, IDC_BUTTON1, m_add);
	DDX_Control(pDX, IDC_BUTTON2, m_remove);
	
}

BEGIN_MESSAGE_MAP(Cbasic_SQLite3Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &Cbasic_SQLite3Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &Cbasic_SQLite3Dlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDOK, &Cbasic_SQLite3Dlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &Cbasic_SQLite3Dlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON3, &Cbasic_SQLite3Dlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// Cbasic_SQLite3Dlg 메시지 처리기

BOOL Cbasic_SQLite3Dlg::OnInitDialog()
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
	
	// 한줄 선택
	m_list.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	// 리스트 컨트롤에 컬럼 이름 입력
	m_list.InsertColumn(0, L"이름");
	m_list.SetColumnWidth(0, 120);
	m_list.InsertColumn(1, L"전화번호");
	m_list.SetColumnWidth(1, 240);



	// 데이터베이스 파일 생성 및 열기
	sqlite3 *db;
	sqlite3_stmt *stmt;
	char *errmsg = NULL;

	int rc = sqlite3_open("test.db", &db);

	if (rc != SQLITE_OK)
	{
		printf("Failed to open DB\n");
		sqlite3_close(db);
		exit(1);
	}


	//SQL 테이블 생성
	char *sql;
	sql = "CREATE TABLE IF NOT EXISTS DB("
		"ID INTEGER PRIMARY        KEY     AUTOINCREMENT,"
		"NAME          TEXT     NOT NULL,"
		"TEL           TEXT     NOT NULL);";

	rc = sqlite3_exec(db, sql, NULL, NULL, &errmsg);

	if (rc != SQLITE_OK)
	{
		printf("create table");
		sqlite3_free(errmsg);
		sqlite3_close(db);
		exit(1);
	}
	else {
		printf("create table OK\n");
	}


	// 테이블을 읽어와 리스트 컨트롤에 보여주기
	sqlite3_prepare_v2(db, "select * from db", -1, &stmt, NULL);

	while (sqlite3_step(stmt) != SQLITE_DONE) {
		int i;
		int num_cols = sqlite3_column_count(stmt);


		char szAnsi[300];
		UTF8ToAnsi((char *)sqlite3_column_text(stmt, 1), szAnsi, 300);
		CString name(szAnsi);

		UTF8ToAnsi((char *)sqlite3_column_text(stmt, 2), szAnsi, 300);
		CString tel(szAnsi);

		int nItem = m_list.InsertItem(0, name);
		m_list.SetItemText(nItem, 1, tel);

	}

	sqlite3_finalize(stmt);

	sqlite3_close(db);

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void Cbasic_SQLite3Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void Cbasic_SQLite3Dlg::OnPaint()
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
HCURSOR Cbasic_SQLite3Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


// 추가 버튼 클릭시 수행되어지는 함수
void Cbasic_SQLite3Dlg::OnBnClickedButton1()
{
	// 에디터 박스에 입력된 데이터를 리스트컨트롤에 입력합니다. 
	CString name;
	m_name.GetWindowText(name);

	CString tel;
	m_tel.GetWindowText(tel);

	int nItem = m_list.InsertItem(0, name);
	m_list.SetItemText(nItem, 1, tel);


	m_name.SetWindowTextW(L"");
	m_tel.SetWindowTextW(L"");



	sqlite3 *db;
	int rc = sqlite3_open("test.db", &db);

	if (rc != SQLITE_OK)
	{
		printf("Failed to open DB\n");
		sqlite3_close(db);
		exit(1);
	}



	char * s_name;

	int sLen = WideCharToMultiByte(CP_ACP, 0, name, -1, NULL, 0, NULL, NULL);
	s_name = new char[sLen + 1];
	WideCharToMultiByte(CP_ACP, 0, name, -1, s_name, sLen, NULL, NULL);

	char szName[100];
	AnsiToUTF8(s_name, szName, 100);

	delete[]s_name;




	char * s_tel;

	sLen = WideCharToMultiByte(CP_ACP, 0, tel, -1, NULL, 0, NULL, NULL);
	s_tel = new char[sLen + 1];
	WideCharToMultiByte(CP_ACP, 0, tel, -1, s_tel, sLen, NULL, NULL);

	char szTel[100];
	AnsiToUTF8(s_tel, szTel, 100);

	delete[]s_tel;



	char *errmsg = NULL;
	char sql[255] = { 0 };
	sprintf(sql, "insert into db(name, tel) values('%s','%s');", szName, szTel);

	if (SQLITE_OK != sqlite3_exec(db, sql, NULL, NULL, &errmsg))
	{
		printf("insert");
	}
	else {
		printf("insert OK!\n");
		AfxMessageBox(L"추가 완료되었습니다.");
	}

	sqlite3_close(db);
}

// 삭제 버튼 클릭시 수행
void Cbasic_SQLite3Dlg::OnBnClickedButton2()
{
	// 리스트 컨트롤에서 선택한 아이템을 제거합니다.
	int row = m_list.GetSelectionMark();
	CString name = m_list.GetItemText(row, 0);


	char * s_name;

	int sLen = WideCharToMultiByte(CP_ACP, 0, name, -1, NULL, 0, NULL, NULL);
	s_name = new char[sLen + 1];
	WideCharToMultiByte(CP_ACP, 0, name, -1, s_name, sLen, NULL, NULL);

	char szName[100];
	AnsiToUTF8(s_name, szName, 100);
	printf("%s", s_name);
	delete[]s_name;



	sqlite3 *db;
	int rc = sqlite3_open("test.db", &db);

	if (rc != SQLITE_OK)
	{
		printf("Failed to open DB\n");
		sqlite3_close(db);
		exit(1);
	}


	char *errmsg = NULL;
	char sql[255] = { 0 };
	sprintf(sql, "delete from db where name = '%s';", szName);

	if (SQLITE_OK != sqlite3_exec(db, sql, NULL, NULL, &errmsg))
	{
		printf("delete");
	}
	else {
		printf("delete OK!\n");
	}

	sqlite3_close(db);
	m_list.DeleteItem(row);
}


void Cbasic_SQLite3Dlg::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialogEx::OnOK();
}


void Cbasic_SQLite3Dlg::OnBnClickedCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialogEx::OnCancel();
}

// 이름 검색
void Cbasic_SQLite3Dlg::OnBnClickedButton3()
{
	// TODO : listCtrl에서가 아니라 SQLite3 query를 날려서 이름을 찾아보자.
	CString name;
	GetDlgItemText(IDC_EDIT3, name);

	LVFINDINFO info;
	int idx;

	info.flags = LVFI_STRING;
	info.psz = name;

	idx = m_list.FindItem(&info);
	if (idx != -1) {
		AfxMessageBox(L"검색 완료되었습니다.");
		printf("%d", idx);
		m_list.SetItemState(idx, LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED | LVIS_FOCUSED); // 해당 list 값 focus
	}
	else {
		AfxMessageBox(L"찾지 못했습니다.");
	}

}
