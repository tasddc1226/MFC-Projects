
// basic_CalculatorDlg.h : ��� ����
//

#pragma once
#include "afxwin.h"


// Cbasic_CalculatorDlg ��ȭ ����
class Cbasic_CalculatorDlg : public CDialogEx
{
// �����Դϴ�.
public:
	Cbasic_CalculatorDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_BASIC_CALCULATOR_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnBnClickedButton1(); // ���ϱ�
	afx_msg void OnBnClickedButton3(); // ����
	afx_msg void OnBnClickedButton4(); // ���ϱ�
	afx_msg void OnBnClickedButton5(); // ������
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);

private:
	char m_op_flag = 0; // 0 : ����, 1 : ����, 2 : ����, 3 : ������
	char m_step_flag = 0; // �����ڰ� ���ȴ��� ���, 1�̸� ���� ���ڸ� ����
	int m_first_value = 0;
	
public:
	afx_msg void OnBnClickedButton6();
};
