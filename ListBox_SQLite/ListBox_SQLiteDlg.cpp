
// ListBox_SQLiteDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "ListBox_SQLite.h"
#include "ListBox_SQLiteDlg.h"
#include "afxdialogex.h"
#include "CppSQLite3U.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CListBox_SQLiteDlg 대화 상자



CListBox_SQLiteDlg::CListBox_SQLiteDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_LISTBOX_SQLITE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CListBox_SQLiteDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, viewDB);
}

BEGIN_MESSAGE_MAP(CListBox_SQLiteDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
END_MESSAGE_MAP()


// CListBox_SQLiteDlg 메시지 처리기

BOOL CListBox_SQLiteDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	scanDB();

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CListBox_SQLiteDlg::OnPaint()
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
HCURSOR CListBox_SQLiteDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// DB에서 데이터를 읽어서 리스트에 뿌려줌(더해줌)
void CListBox_SQLiteDlg::scanDB()
{
	CString sTmp;
	CListBox* pListPage;

	// DB 생성
	CppSQLite3DB db;

	try {
		// DB가 있는 경로에서 DB를 open
		db.open(_T("test.db"));

		// SQL 쿼리를 날려, 출력할 테이블의 컬럼을 정안다
		sTmp.Format(_T("select name, region from customer;"));
		CppSQLite3Query q = db.execQuery(sTmp);

		// 컬럼이 없을때까지 출력
		while (!q.eof()) {
			CString nIdx = q.getStringField(0);
			sTmp.Format(_T("%s"), nIdx);
			// ListBox 변수에 DB값 추가
			viewDB.AddString(sTmp);
			q.nextRow();
		}
	}
	catch (CppSQLite3Exception &e) {
		viewDB.AddString(_T("에러"));
	}

	// db종료
	db.close();
}

