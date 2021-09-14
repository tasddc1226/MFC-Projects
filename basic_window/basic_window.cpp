#include "stdafx.h"
#include <windowsx.h>

// WndProc : Window Procedure�� ���ڷ� � ��ư�� ������ ��, ��� ������� �����ڰ� �����ϴ� �Լ�.
// �ӽ������� ������ �Ǵ� �Լ��̹Ƿ� CALLBACK�̶� ������
// ù ��° ���� : �޽����� � �������� �޼������� Ȯ��
// �� ��° ���� : �޼��� ���̵�
// �� ��°, �� ��° : � �޼����� �Ѿ���Ŀ� ���� �� �ΰ����� ��ȿ or ��ȿ���� ���� �� �ִ�.
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	// ���� �Ѿ�� �޼����� ������ â�� ������� �޼������, �Ʒ��� ���� �޼��� â�� alert
	if (uMsg == WM_CLOSE) {
		if (IDCANCEL == MessageBox(hWnd, L"�� �����Ϸ���?", L"�ѹ��� �츮��!", MB_OKCANCEL | MB_ICONQUESTION)) {
			return 1;
		}
	}
	// ���α׷� ������ ���콺 ���� ��ư�� Ŭ������ �� ������ ���� ���ǹ�
	else if (uMsg == WM_LBUTTONDOWN) {
		// Ŭ���� ��ǥ���� ����
		int x = GET_X_LPARAM(lParam);
		int y = GET_Y_LPARAM(lParam);
		// �׸��� �׸��� ���� �ش� �����쿡 DC�� ���´�.(GetDC)
		HDC h_dc = GetDC(hWnd);

		// ��Ʈ��Ű�� �����鼭 Ŭ���Ѵٸ� ���� ������ ��.
		if (wParam & MK_CONTROL) {
			Ellipse(h_dc, x - 25, y - 25, x + 25, y + 25);
		}
		// �װ� �ƴ϶�� �簢�� ���
		else {
			Rectangle(h_dc, x - 25, y - 25, x + 25, y + 25);
		}
		// DC�� �� �̻� ���� �ʰڴٴ� ǥ��
		ReleaseDC(hWnd, h_dc);
	}
	// ���α׷��� �����϶�� �޼��� �߻��ϸ� �޼���ť�� wm_quit �޼����� �־� �����ϵ��� ��.
	// �̶� while���� 0�� ��ȯ�Ǹ鼭 ���α׷��� ����Ǿ���.
	else if (uMsg == WM_DESTROY) PostQuitMessage(0);
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hlnstance,	HINSTANCE hPrevInstance, LPSTR IpCmdLine, int nCmdShow) {
	WNDCLASS wc;									// ������ Ŭ������ ����ϱ� ���� ����ü

	wc.cbClsExtra = NULL;
	wc.cbWndExtra = NULL;
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;		// ������ â�� �� ����
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);		// ���α׷� ���� �� ���콺 Ŀ�� ��� ����
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);		// ���α׷� ���� ����� ������ ��� ����
	wc.hInstance = hlnstance;						// �޾ƿ� ���ڰ��� ����
	wc.lpfnWndProc = WndProc;						// call back �Լ� ���
	wc.lpszClassName = L"tipssoft";					// L�� �����ڵ带 ��Ÿ��. win app�� ����ϴ� ���� �̸��� class name�� ����. unique �ؾ���.
	wc.lpszMenuName = NULL;							// �޴� �̸��� ���� �ʴ� ������ ����
	wc.style = NULL;								// windows ���� ��Ÿ���� ������ �������� ���� ��� ���� ����

	RegisterClass(&wc);								// ������ Ŭ������ �����. ���� ����� �� �ѹ��� ����ϸ� �������� ����

	// HWND : H�� Handle WND�� ����
	HWND hWnd = CreateWindow(L"tipssoft", L"www.tipssoft.com",
		WS_OVERLAPPEDWINDOW,100, 90, 400, 350, NULL, NULL, hlnstance, NULL);

	// ������ �ڵ� ���� �Ѱ���
	ShowWindow(hWnd, nCmdShow);
	// �ý����� � ��Ȳ�̵� �����ִ� �Լ�
	UpdateWindow(hWnd);
	// �޼����� �����ؼ� �������� �����Ͱ� �ƴ� ����ü �̿�
	MSG msg;
	// ��κ� 1�� ��ȯ, wm.quit�޼����� ������ 0�� ��ȯ
	while (GetMessage(&msg, NULL, 0, 0)) {
		// &msg�� �� ���ø����̼��� ��� ������ ������ ��ȯ
		TranslateMessage(&msg);
		// �� �޼����� �����϶�� �ǹ�
		DispatchMessage(&msg);
	}
	// wm_quit�޽����� w_Param�� ��ȯ
	return msg.wParam;


}

