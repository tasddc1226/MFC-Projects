
// basic_SQLite3Dlg.h : ��� ����
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// Cbasic_SQLite3Dlg ��ȭ ����
class Cbasic_SQLite3Dlg : public CDialogEx
{
// �����Դϴ�.
public:
	Cbasic_SQLite3Dlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_BASIC_SQLITE3_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
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
	afx_msg void OnBnClickedButton1(); // �߰� ��ư
	afx_msg void OnBnClickedButton2(); // ���� ��ư
	
};
