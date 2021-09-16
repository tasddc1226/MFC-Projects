
// basic_CalculatorDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "basic_Calculator.h"
#include "basic_CalculatorDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Cbasic_CalculatorDlg 대화 상자



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


// Cbasic_CalculatorDlg 메시지 처리기

BOOL Cbasic_CalculatorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void Cbasic_CalculatorDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR Cbasic_CalculatorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


// 더하기
void Cbasic_CalculatorDlg::OnBnClickedButton1()
{
	m_op_flag = 0;
	m_step_flag = 1; // + 연산자가 눌림
}
// 빼기
void Cbasic_CalculatorDlg::OnBnClickedButton3()
{
	m_op_flag = 1;
	m_step_flag = 1;
}

// 곱하기
void Cbasic_CalculatorDlg::OnBnClickedButton4()
{
	m_op_flag = 2;
	m_step_flag = 1;
}

// 나누기
void Cbasic_CalculatorDlg::OnBnClickedButton5()
{
	m_op_flag = 3;
	m_step_flag = 1;
}

// = 버튼 : 연산 처리
void Cbasic_CalculatorDlg::OnBnClickedButton6()
{
	CString str;
	GetDlgItemText(IDC_EDIT1, str); // EDIT1의 문자열을 str에 저장
	double second_value = _wtof(str); // 문자열을 실수로 변환

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
	str.TrimRight(L"0"); // 0이 사라질 때까지 오른쪽 방향으로 가면서 지움
	SetDlgItemText(IDC_EDIT1, str);
	m_step_flag = 1;
}


BOOL Cbasic_CalculatorDlg::OnCommand(WPARAM wParam, LPARAM lParam)
{
	if (IDC_NUM10 <= wParam && wParam <= IDC_NUM9) {
		CString str, num_str;
		num_str.Format(L"%d", wParam - IDC_NUM10);

		// 값이 입력되지 않았을 때, 사용자가 입력한 값을 가져옴
		if (m_step_flag == 0) GetDlgItemText(IDC_EDIT1, str); 
		else {
			m_first_value = GetDlgItemInt(IDC_EDIT1); // 값을 백업
			m_step_flag = 0;
		}
		SetDlgItemText(IDC_EDIT1, str + num_str);
	}
	return CDialogEx::OnCommand(wParam, lParam);
}


// clear button
void Cbasic_CalculatorDlg::OnBnClickedButton2()
{
	m_step_flag = 1;			  // 기존 숫자를 지워야 하므로 1로 설정
	count = 0;					  // 초기 연산하는 것 처럼 count 초기화
	num = 0;					  // 이전 연산값도 초기화
	SetDlgItemText(IDC_EDIT1, 0); // 0으로 set
}
