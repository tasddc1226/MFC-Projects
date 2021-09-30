
// basic_SQLite3Dlg.cpp : ���� ����
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

// SQLite�� UTF8�� ����ϱ� ������ �ڵ� ��ȯ�� �ʿ��մϴ�.
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


// Cbasic_SQLite3Dlg ��ȭ ����



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


// Cbasic_SQLite3Dlg �޽��� ó����

BOOL Cbasic_SQLite3Dlg::OnInitDialog()
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
	
	// ���� ����
	m_list.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	// ����Ʈ ��Ʈ�ѿ� �÷� �̸� �Է�
	m_list.InsertColumn(0, L"�̸�");
	m_list.SetColumnWidth(0, 120);
	m_list.InsertColumn(1, L"��ȭ��ȣ");
	m_list.SetColumnWidth(1, 240);



	// �����ͺ��̽� ���� ���� �� ����
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


	//SQL ���̺� ����
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


	// ���̺��� �о�� ����Ʈ ��Ʈ�ѿ� �����ֱ�
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

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
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

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�.  ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void Cbasic_SQLite3Dlg::OnPaint()
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
HCURSOR Cbasic_SQLite3Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


// �߰� ��ư Ŭ���� ����Ǿ����� �Լ�
void Cbasic_SQLite3Dlg::OnBnClickedButton1()
{
	// ������ �ڽ��� �Էµ� �����͸� ����Ʈ��Ʈ�ѿ� �Է��մϴ�. 
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
		AfxMessageBox(L"�߰� �Ϸ�Ǿ����ϴ�.");
	}

	sqlite3_close(db);
}

// ���� ��ư Ŭ���� ����
void Cbasic_SQLite3Dlg::OnBnClickedButton2()
{
	// ����Ʈ ��Ʈ�ѿ��� ������ �������� �����մϴ�.
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
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CDialogEx::OnOK();
}


void Cbasic_SQLite3Dlg::OnBnClickedCancel()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CDialogEx::OnCancel();
}

// �̸� �˻�
void Cbasic_SQLite3Dlg::OnBnClickedButton3()
{
	// TODO : listCtrl������ �ƴ϶� SQLite3 query�� ������ �̸��� ã�ƺ���.
	CString name;
	GetDlgItemText(IDC_EDIT3, name);

	LVFINDINFO info;
	int idx;

	info.flags = LVFI_STRING;
	info.psz = name;

	idx = m_list.FindItem(&info);
	if (idx != -1) {
		AfxMessageBox(L"�˻� �Ϸ�Ǿ����ϴ�.");
		printf("%d", idx);
		m_list.SetItemState(idx, LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED | LVIS_FOCUSED); // �ش� list �� focus
	}
	else {
		AfxMessageBox(L"ã�� ���߽��ϴ�.");
	}

}
