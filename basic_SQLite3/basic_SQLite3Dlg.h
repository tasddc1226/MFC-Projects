
// basic_SQLite3Dlg.h : 헤더 파일
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// Cbasic_SQLite3Dlg 대화 상자
class Cbasic_SQLite3Dlg : public CDialogEx
{
// 생성입니다.
public:
	Cbasic_SQLite3Dlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_BASIC_SQLITE3_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CEdit m_name;
	CEdit m_tel;
	CButton m_add;
	CButton m_remove;
	CListCtrl m_list;
	afx_msg void OnBnClickedButton1(); // 추가 버튼
	afx_msg void OnBnClickedButton2(); // 삭제 버튼
	
};
