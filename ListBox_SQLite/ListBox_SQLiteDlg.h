
// ListBox_SQLiteDlg.h : ��� ����
//

#pragma once

// CListBox_SQLiteDlg ��ȭ ����
class CListBox_SQLiteDlg : public CDialogEx
{
// �����Դϴ�.
public:
	CListBox_SQLiteDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.
	void scanDB();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LISTBOX_SQLITE_DIALOG };
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
	CListBox viewDB;
};
