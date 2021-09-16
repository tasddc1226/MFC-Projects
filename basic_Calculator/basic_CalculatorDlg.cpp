
// basic_CalculatorDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "basic_Calculator.h"
#include "basic_CalculatorDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Cbasic_CalculatorDlg ��ȭ ����



Cbasic_CalculatorDlg::Cbasic_CalculatorDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_BASIC_CALCULATOR_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Cbasic_CalculatorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(Cbasic_CalculatorDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &Cbasic_CalculatorDlg::OnBnClickedButton1)

	ON_BN_CLICKED(IDC_BUTTON3, &Cbasic_CalculatorDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &Cbasic_CalculatorDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &Cbasic_CalculatorDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &Cbasic_CalculatorDlg::OnBnClickedButton6)

	ON_BN_CLICKED(IDC_BUTTON2, &Cbasic_CalculatorDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// Cbasic_CalculatorDlg �޽��� ó����

BOOL Cbasic_CalculatorDlg::OnInitDialog()
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

void Cbasic_CalculatorDlg::OnPaint()
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
HCURSOR Cbasic_CalculatorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


// ���ϱ�
void Cbasic_CalculatorDlg::OnBnClickedButton1()
{
	m_op_flag = 0;
	m_step_flag = 1; // + �����ڰ� ����
}
// ����
void Cbasic_CalculatorDlg::OnBnClickedButton3()
{
	m_op_flag = 1;
	m_step_flag = 1;
}

// ���ϱ�
void Cbasic_CalculatorDlg::OnBnClickedButton4()
{
	m_op_flag = 2;
	m_step_flag = 1;
}

// ������
void Cbasic_CalculatorDlg::OnBnClickedButton5()
{
	m_op_flag = 3;
	m_step_flag = 1;
}

// = ��ư : ���� ó��
void Cbasic_CalculatorDlg::OnBnClickedButton6()
{
	CString str;
	GetDlgItemText(IDC_EDIT1, str); // EDIT1�� ���ڿ��� str�� ����
	double second_value = _wtof(str); // ���ڿ��� �Ǽ��� ��ȯ

	switch (m_op_flag) {
	case 0:
		if (count != 0 && m_first_value == second_value) {
			str.Format(L"%f", m_first_value += num);
		}
		else {
			num = second_value;
			str.Format(L"%f", m_first_value += second_value);
		}
		count++;
		break;

	case 1:
		if (count != 0 && m_first_value == second_value) {
			str.Format(L"%f", m_first_value -= num);
		}
		else {
			num = second_value;
			str.Format(L"%f", m_first_value -= second_value);
		}
		count++;
		break;

	case 2:
		if (count != 0 && m_first_value == second_value) {
			str.Format(L"%f", m_first_value *= second_value);
		}
		else {
			num = second_value;
			str.Format(L"%f", m_first_value *= second_value);
		}
		count++;
		break;

	case 3:
		if (second_value != 0) {
			if (count != 0 && m_first_value == second_value) {
				str.Format(L"%f", m_first_value /= num);
			}
			else {
				num = second_value;
				str.Format(L"%f", m_first_value /= second_value);
			}
		} else {
			m_first_value = 0;
		}
		count++;
		break;
	}
	str.TrimRight(L"0"); // 0�� ����� ������ ������ �������� ���鼭 ����
	SetDlgItemText(IDC_EDIT1, str);
	m_step_flag = 1;
}


BOOL Cbasic_CalculatorDlg::OnCommand(WPARAM wParam, LPARAM lParam)
{
	if (IDC_NUM10 <= wParam && wParam <= IDC_NUM9) {
		CString str, num_str;
		num_str.Format(L"%d", wParam - IDC_NUM10);

		// ���� �Էµ��� �ʾ��� ��, ����ڰ� �Է��� ���� ������
		if (m_step_flag == 0) GetDlgItemText(IDC_EDIT1, str); 
		else {
			m_first_value = GetDlgItemInt(IDC_EDIT1); // ���� ���
			m_step_flag = 0;
		}
		SetDlgItemText(IDC_EDIT1, str + num_str);
	}
	return CDialogEx::OnCommand(wParam, lParam);
}


// clear button
void Cbasic_CalculatorDlg::OnBnClickedButton2()
{
	m_step_flag = 1;			  // ���� ���ڸ� ������ �ϹǷ� 1�� ����
	count = 0;					  // �ʱ� �����ϴ� �� ó�� count �ʱ�ȭ
	num = 0;					  // ���� ���갪�� �ʱ�ȭ
	SetDlgItemText(IDC_EDIT1, 0); // 0���� set
}
