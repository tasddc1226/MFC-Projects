
// basic_clockDlg.h : ��� ����
//

#pragma once


// Cbasic_clockDlg ��ȭ ����
class Cbasic_clockDlg : public CDialogEx
{
// �����Դϴ�.
public:
	Cbasic_clockDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_BASIC_CLOCK_DIALOG };
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
	CString mDay;
	CString mTime;
	afx_msg void OnBnClickedButton1();
	static UINT TimeThread(LPVOID _mothod);
};
