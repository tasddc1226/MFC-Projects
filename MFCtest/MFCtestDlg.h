
// MFCtestDlg.h : ��� ����
//

#pragma once

#define MAX_CLICK_COUNT 100
// �ּڰ��� �׸��� ���� ������ ������ ����ü ����
struct ClickInfo {
	int flag; // 0->rect, 1->ellipse
	int x;
	int y;
};


// CMFCtestDlg ��ȭ ����
class CMFCtestDlg : public CDialogEx
{
// �����Դϴ�.
public:
	CMFCtestDlg(CWnd* pParent = NULL);		// ǥ�� �������Դϴ�.
	ClickInfo m_pos_list[MAX_CLICK_COUNT];  // 100�� ��ŭ flag�� ���� ����, Ŭ���� ������ŭ ��ȿ

	int m_click_count = 0;					 // Ŭ���� ����

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCTEST_DIALOG };
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
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};
