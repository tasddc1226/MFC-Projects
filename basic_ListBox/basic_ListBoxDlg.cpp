
// basic_ListBoxDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "basic_ListBox.h"
#include "basic_ListBoxDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Cbasic_ListBoxDlg 대화 상자



Cbasic_ListBoxDlg::Cbasic_ListBoxDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_BASIC_LISTBOX_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Cbasic_ListBoxDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_my_list);
}

BEGIN_MESSAGE_MAP(Cbasic_ListBoxDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &Cbasic_ListBoxDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &Cbasic_ListBoxDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// Cbasic_ListBoxDlg 메시지 처리기

BOOL Cbasic_ListBoxDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// 값을 미리 추가할 수도 있다.
	m_my_list.AddString(L"마재승");

	m_my_list.AddString(L"강다혜");

	m_my_list.AddString(L"강철민");

	m_my_list.AddString(L"고다경");

	m_my_list.AddString(L"홍길동");

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void Cbasic_ListBoxDlg::OnPaint()
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
HCURSOR Cbasic_ListBoxDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


// Edit Box에 적은 것을 추가버튼을 눌러서 리스트박스에 추가함.
void Cbasic_ListBoxDlg::OnBnClickedButton1()
{
	CString str;
	GetDlgItemText(IDC_EDIT1, str);

	// 얻은 문자열을 멤버변수를 사용해 리스트박스에 추가
	//m_my_list.AddString(str); // AddString : 위치와 상관없이 문자열 추가 (기본: 오름차순 정렬)
	int index = m_my_list.InsertString(-1, str); // InsertString : Add와 달리 위치를 명시. -1이면 가장 마지막 위치에 추가

	m_my_list.SetCurSel(index); // 현재 위치를 커서가 선택
}

// 선택한 리스트를 삭제한다.
void Cbasic_ListBoxDlg::OnBnClickedButton2()
{
	int index = m_my_list.GetCurSel(); // 선택하지 않으면 -1 반환

	if (index != LB_ERR) {
		CString str;
		m_my_list.GetText(index, str);

		// 확인을 누르면 1, 취소를 누르면 2 반환 (ID_OK), (ID_CANCLE)
		if (IDOK == MessageBox(str, L"정말 삭제할까요?", MB_OKCANCEL | MB_ICONQUESTION)) {
			m_my_list.DeleteString(index); // 선택 위치의 스트링 삭제
		}
	}
}
