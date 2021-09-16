
// basic_ListBoxDlg.h : 헤더 파일
//

#pragma once
#include "afxwin.h"


// Cbasic_ListBoxDlg 대화 상자
class Cbasic_ListBoxDlg : public CDialogEx
{
// 생성입니다.
public:
	Cbasic_ListBoxDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_BASIC_LISTBOX_DIALOG };
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
	CListBox m_my_list;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnSelchangeList1();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnDblclkList1();
};
