
// basic_ListBoxDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "basic_ListBox.h"
#include "basic_ListBoxDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Cbasic_ListBoxDlg ��ȭ ����



Cbasic_ListBoxDlg::Cbasic_ListBoxDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_BASIC_LISTBOX_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Cbasic_ListBoxDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_my_list);
}

BEGIN_MESSAGE_MAP(Cbasic_ListBoxDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &Cbasic_ListBoxDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &Cbasic_ListBoxDlg::OnBnClickedButton2)
	ON_LBN_SELCHANGE(IDC_LIST1, &Cbasic_ListBoxDlg::OnSelchangeList1)
	ON_BN_CLICKED(IDC_BUTTON3, &Cbasic_ListBoxDlg::OnBnClickedButton3)
	ON_LBN_DBLCLK(IDC_LIST1, &Cbasic_ListBoxDlg::OnDblclkList1)
END_MESSAGE_MAP()


// Cbasic_ListBoxDlg �޽��� ó����

BOOL Cbasic_ListBoxDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �� ��ȭ ������ �������� �����մϴ�.  ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// ���� �̸� �߰��� ���� �ִ�.
	/*m_my_list.AddString(L"�����");

	m_my_list.AddString(L"������");

	m_my_list.AddString(L"��ö��");

	m_my_list.AddString(L"��ٰ�");

	m_my_list.AddString(L"ȫ�浿");*/
	
	// ���� ���丮 ����� ����Ʈ�ڽ� ���̾�α׿� �߰�
	m_my_list.Dir(DDL_READWRITE | DDL_DIRECTORY, L"*");

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�.  ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void Cbasic_ListBoxDlg::OnPaint()
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
HCURSOR Cbasic_ListBoxDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


// Edit Box�� ���� ���� �߰���ư�� ������ ����Ʈ�ڽ��� �߰���.
void Cbasic_ListBoxDlg::OnBnClickedButton1()
{
	CString str;
	GetDlgItemText(IDC_EDIT1, str);

	// ���� ���ڿ��� ��������� ����� ����Ʈ�ڽ��� �߰�
	//m_my_list.AddString(str); // AddString : ��ġ�� ������� ���ڿ� �߰� (�⺻: �������� ����)
	int index = m_my_list.InsertString(-1, str); // InsertString : Add�� �޸� ��ġ�� ���. -1�̸� ���� ������ ��ġ�� �߰�

	m_my_list.SetCurSel(index); // ���� ��ġ�� Ŀ���� ����
}

// ������ ����Ʈ�� �����Ѵ�.
void Cbasic_ListBoxDlg::OnBnClickedButton2()
{
	int index = m_my_list.GetCurSel(); // �������� ������ -1 ��ȯ

	if (index != LB_ERR) {
		CString str;
		m_my_list.GetText(index, str);

		// Ȯ���� ������ 1, ��Ҹ� ������ 2 ��ȯ (ID_OK), (ID_CANCLE)
		if (IDOK == MessageBox(str, L"���� �����ұ��?", MB_OKCANCEL | MB_ICONQUESTION)) {
			m_my_list.DeleteString(index); // ���� ��ġ�� ��Ʈ�� ����
		}
	}
}


void Cbasic_ListBoxDlg::OnSelchangeList1()
{
	// ���� ������ ������ �ε����� ����.
	int index = m_my_list.GetCurSel();
	CString str;
	m_my_list.GetText(index, str);

	SetDlgItemText(IDC_EDIT1, str);
}

// ����Ʈ�� ������ ã�´�.
void Cbasic_ListBoxDlg::OnBnClickedButton3()
{
	CString str;

	GetDlgItemText(IDC_EDIT2, str);

	// ��𼭺��� ã�� ������, str�� ��õ� ������ ������ ã��.
	// ������ -1, ������ �ش� index ��ȯ
	//int index = m_my_list.FindString(-1, str); // FindStringExact : ��Ȯ�ϰ� ��ġ�� ���� ã����� �� ���
	
	// �ߺ��� ��� ã�ƺ���.
	int start_index = m_my_list.GetCurSel();

	int index = m_my_list.FindString(start_index, str);

	if (index == LB_ERR) {
		AfxMessageBox(L"ã�� ���߽��ϴ�!");
	} else {
		m_my_list.SetCurSel(index);
		AfxMessageBox(L"ã�ҽ��ϴ�! �ش� ��ġ�� ����ŵ�ϴ�.");
	}
}


void Cbasic_ListBoxDlg::OnDblclkList1()
{
	// �����ڵ带 �����ϴ� ĳ���͸� �ִ� ��α��� ��ŭ �迭 ����
	wchar_t temp_path[MAX_PATH]; 

	// ���� �� ���α׷��� �۾���θ� ���� ��ο� �ִ´�.
	GetCurrentDirectory(MAX_PATH, temp_path);

	// ���� ��ġ�� �ε����� ����
	int index = m_my_list.GetCurSel();
	CString str;
	m_my_list.GetText(index, str); // �ε��� ��ġ�� ���ڿ��� str�� �߰�

	str = L"\\" + str; // ���� ���ϸ� �տ� \�� ����
	str = temp_path + str; // ���� ���� ��� �տ� �� ����
	
	// �θ� ����, ���� ���, ���� ���ϸ�, �� ������ ���, �����ο��� �۾�?, �Ϲݸ���..
	ShellExecute(NULL, L"open", L"notepad.exe", str, NULL, SW_SHOW);

	// ����Ŭ���� �� ���α׷��� ��� ���
	AfxMessageBox(str);
}
