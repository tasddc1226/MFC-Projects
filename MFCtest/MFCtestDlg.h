
// MFCtestDlg.h : 헤더 파일
//

#pragma once

#define MAX_CLICK_COUNT 100
// 주솟값과 그림에 대한 정보를 저장할 구조체 선언
struct ClickInfo {
	int flag; // 0->rect, 1->ellipse
	int x;
	int y;
};


// CMFCtestDlg 대화 상자
class CMFCtestDlg : public CDialogEx
{
// 생성입니다.
public:
	CMFCtestDlg(CWnd* pParent = NULL);		// 표준 생성자입니다.
	ClickInfo m_pos_list[MAX_CLICK_COUNT];  // 100개 만큼 flag를 저장 가능, 클릭한 개수만큼 유효

	int m_click_count = 0;					 // 클릭한 개수

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCTEST_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};
