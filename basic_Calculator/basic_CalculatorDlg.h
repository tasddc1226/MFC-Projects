
// basic_CalculatorDlg.h : 헤더 파일
//

#pragma once
#include "afxwin.h"


// Cbasic_CalculatorDlg 대화 상자
class Cbasic_CalculatorDlg : public CDialogEx
{
// 생성입니다.
public:
	Cbasic_CalculatorDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_BASIC_CALCULATOR_DIALOG };
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
	afx_msg void OnBnClickedButton1(); // 더하기
	afx_msg void OnBnClickedButton3(); // 빼기
	afx_msg void OnBnClickedButton4(); // 곱하기
	afx_msg void OnBnClickedButton5(); // 나누기
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);

private:
	char m_op_flag = 0; // 0 : 덧셈, 1 : 뺄셈, 2 : 곱셈, 3 : 나눗셈
	char m_step_flag = 0; // 연산자가 눌렸는지 기억, 1이면 기존 숫자를 지움
	int m_first_value = 0;
	
public:
	afx_msg void OnBnClickedButton6();
};
