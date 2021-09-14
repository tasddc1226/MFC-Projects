
// MFCtestDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "MFCtest.h"
#include "MFCtestDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCtestDlg 대화 상자



CMFCtestDlg::CMFCtestDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MFCTEST_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCtestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCtestDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// CMFCtestDlg 메시지 처리기

BOOL CMFCtestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CMFCtestDlg::OnPaint()
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
		CPaintDC dc(this);

		for (int i = 0; i < m_click_count; i++) {
			if (m_pos_list[i].flag) {
				dc.Ellipse(m_pos_list[i].x - 25, m_pos_list[i].y - 25, m_pos_list[i].x + 25, m_pos_list[i].y + 25);
			} else {
				dc.Rectangle(m_pos_list[i].x - 25, m_pos_list[i].y - 25, m_pos_list[i].x + 25, m_pos_list[i].y + 25);
			}
		}
		//CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CMFCtestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


// 첫 번째 인자 : 마우스가 클릭되었을 때 조합키가 있는지 여부 확인
// 두 번째 인자 : 클릭된 위치의 좌표값
void CMFCtestDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (m_click_count >= MAX_CLICK_COUNT) return; // 에러 처리는 위에서

	CClientDC dc(this);

	ClickInfo *p_pos = m_pos_list;

	// 클릭시 x, y값 backup
	m_pos_list[m_click_count].x = point.x;
	m_pos_list[m_click_count].y = point.y;

	if (nFlags & MK_CONTROL){
		m_pos_list[m_click_count].flag = 1; // 1 -> 원을, 0 -> 사각형
		dc.Ellipse(point.x - 25, point.y - 25, point.x + 25, point.y + 25);
	}
	else {
		m_pos_list[m_click_count].flag = 0;
		dc.Rectangle(point.x - 25, point.y - 25, point.x + 25, point.y + 25);
	}

	m_click_count++; // 카운터 증가
	CDialogEx::OnLButtonDown(nFlags, point);


	// :: 스코프연산자를 사용해서 API의 GetDC를 사용함을 명시
	//HDC h_dc = ::GetDC(m_hWnd);

	// DC를 얻어온 후, 클릭했을 때 사각형이 나타남
	//Rectangle(h_dc, point.x - 15, point.y - 15, point.x + 15, point.y + 15);

	// Release 또한 MFC에 존재하므로 :: 연산자로 호출
	//::ReleaseDC(m_hWnd, h_dc);
}
