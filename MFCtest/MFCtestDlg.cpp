
// MFCtestDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "MFCtest.h"
#include "MFCtestDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCtestDlg ��ȭ ����



CMFCtestDlg::CMFCtestDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MFCTEST_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCtestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCtestDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// CMFCtestDlg �޽��� ó����

BOOL CMFCtestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �� ��ȭ ������ �������� �����մϴ�.  ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�.  ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CMFCtestDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CPaintDC dc(this);

		for (int i = 0; i < m_click_count; i++) {
			if (m_pos_list[i].flag) {
				dc.Ellipse(m_pos_list[i].x - 25, m_pos_list[i].y - 25, m_pos_list[i].x + 25, m_pos_list[i].y + 25);
			} else {
				dc.Rectangle(m_pos_list[i].x - 25, m_pos_list[i].y - 25, m_pos_list[i].x + 25, m_pos_list[i].y + 25);
			}
		}
		//CDialogEx::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CMFCtestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


// ù ��° ���� : ���콺�� Ŭ���Ǿ��� �� ����Ű�� �ִ��� ���� Ȯ��
// �� ��° ���� : Ŭ���� ��ġ�� ��ǥ��
void CMFCtestDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (m_click_count >= MAX_CLICK_COUNT) return; // ���� ó���� ������

	CClientDC dc(this);

	ClickInfo *p_pos = m_pos_list;

	// Ŭ���� x, y�� backup
	m_pos_list[m_click_count].x = point.x;
	m_pos_list[m_click_count].y = point.y;

	if (nFlags & MK_CONTROL){
		m_pos_list[m_click_count].flag = 1; // 1 -> ����, 0 -> �簢��
		dc.Ellipse(point.x - 25, point.y - 25, point.x + 25, point.y + 25);
	}
	else {
		m_pos_list[m_click_count].flag = 0;
		dc.Rectangle(point.x - 25, point.y - 25, point.x + 25, point.y + 25);
	}

	m_click_count++; // ī���� ����
	CDialogEx::OnLButtonDown(nFlags, point);


	// :: �����������ڸ� ����ؼ� API�� GetDC�� ������� ���
	//HDC h_dc = ::GetDC(m_hWnd);

	// DC�� ���� ��, Ŭ������ �� �簢���� ��Ÿ��
	//Rectangle(h_dc, point.x - 15, point.y - 15, point.x + 15, point.y + 15);

	// Release ���� MFC�� �����ϹǷ� :: �����ڷ� ȣ��
	//::ReleaseDC(m_hWnd, h_dc);
}
