
// basic_ListBoxDlg.h : ��� ����
//

#pragma once
#include "afxwin.h"


// Cbasic_ListBoxDlg ��ȭ ����
class Cbasic_ListBoxDlg : public CDialogEx
{
// �����Դϴ�.
public:
	Cbasic_ListBoxDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_BASIC_LISTBOX_DIALOG };
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
	CListBox m_my_list;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnSelchangeList1();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnDblclkList1();
};
