
// basic_clockDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "basic_clock.h"
#include "basic_clockDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Cbasic_clockDlg ��ȭ ����



Cbasic_clockDlg::Cbasic_clockDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_BASIC_CLOCK_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Cbasic_clockDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(Cbasic_clockDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &Cbasic_clockDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// Cbasic_clockDlg �޽��� ó����

BOOL Cbasic_clockDlg::OnInitDialog()
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

void Cbasic_clockDlg::OnPaint()
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
		CDialogEx::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR Cbasic_clockDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void Cbasic_clockDlg::OnBnClickedButton1()
{
	CWinThread *p1 = NULL;
	p1 = AfxBeginThread(TimeThread, this);

	if (p1 == NULL) {
		AfxMessageBox(L"Error!");
	}
}

UINT Cbasic_clockDlg::TimeThread(LPVOID _mothod)
{
	Cbasic_clockDlg *fir = (Cbasic_clockDlg*)_mothod;
	while (1) {
		CTime cTime = CTime::GetCurrentTime();
		fir->mDay.Format(L"%04d.%02d.%02d", cTime.GetYear(), cTime.GetMonth(), cTime.GetDay());
		fir->mTime.Format(L"%02d:%02d:%02d", cTime.GetHour(), cTime.GetMinute(), cTime.GetSecond());
		fir->SetDlgItemText(IDC_DaySTATIC, fir->mDay);
		fir->SetDlgItemText(IDC_TimeSTATIC, fir->mTime);
		Sleep(10);
	}
	return 0;
}
