
// Thread_EXDlg.h : ��� ����
//

#pragma once
#include "afxwin.h"


// CThread_EXDlg ��ȭ ����
class CThread_EXDlg : public CDialogEx
{
// �����Դϴ�.
public:
	CThread_EXDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_THREAD_EX_DIALOG };
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
	CWinThread *p1;
	CString m_staticDisp;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	static UINT TimeThread(LPVOID _mothod);
	
	
	CEdit m_strEditOutput;
};
