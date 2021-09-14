#include "stdafx.h"
#include <windowsx.h>

// WndProc : Window Procedure의 약자로 어떤 버튼을 눌렀을 때, 어떤게 실행될지 개발자가 결정하는 함수.
// 임시적으로 실행이 되는 함수이므로 CALLBACK이라 적어줌
// 첫 번째 인자 : 메시지가 어떤 윈도우의 메세지인지 확인
// 두 번째 인자 : 메세지 아이디
// 세 번째, 네 번째 : 어떤 메세지가 넘어가느냐에 따라 이 두가지가 유효 or 유효하지 않을 수 있다.
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	// 만약 넘어온 메세지가 윈도우 창을 닫으라는 메세지라면, 아래와 같은 메세지 창을 alert
	if (uMsg == WM_CLOSE) {
		if (IDCANCEL == MessageBox(hWnd, L"날 종료하려고?", L"한번만 살리도!", MB_OKCANCEL | MB_ICONQUESTION)) {
			return 1;
		}
	}
	// 프로그램 내에서 마우스 왼쪽 버튼을 클릭했을 때 반응에 대한 조건문
	else if (uMsg == WM_LBUTTONDOWN) {
		// 클릭한 좌표값을 저장
		int x = GET_X_LPARAM(lParam);
		int y = GET_Y_LPARAM(lParam);
		// 그림을 그리기 위해 해당 윈도우에 DC를 얻어온다.(GetDC)
		HDC h_dc = GetDC(hWnd);

		// 컨트롤키를 누르면서 클릭한다면 원이 나오게 됨.
		if (wParam & MK_CONTROL) {
			Ellipse(h_dc, x - 25, y - 25, x + 25, y + 25);
		}
		// 그게 아니라면 사각형 출력
		else {
			Rectangle(h_dc, x - 25, y - 25, x + 25, y + 25);
		}
		// DC를 더 이상 쓰지 않겠다는 표시
		ReleaseDC(hWnd, h_dc);
	}
	// 프로그램을 종료하라는 메세지 발생하면 메세지큐에 wm_quit 메세지를 넣어 종료하도록 함.
	// 이때 while문에 0이 반환되면서 프로그램이 종료되어짐.
	else if (uMsg == WM_DESTROY) PostQuitMessage(0);
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hlnstance,	HINSTANCE hPrevInstance, LPSTR IpCmdLine, int nCmdShow) {
	WNDCLASS wc;									// 윈도우 클래스를 등록하기 위한 구조체

	wc.cbClsExtra = NULL;
	wc.cbWndExtra = NULL;
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;		// 윈도우 창의 색 지정
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);		// 프로그램 실행 시 마우스 커서 모양 설정
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);		// 프로그램 왼쪽 상단의 아이콘 모양 설정
	wc.hInstance = hlnstance;						// 받아온 인자값을 저장
	wc.lpfnWndProc = WndProc;						// call back 함수 명시
	wc.lpszClassName = L"tipssoft";					// L은 유니코드를 나타냄. win app이 사용하는 고유 이름인 class name을 지정. unique 해야함.
	wc.lpszMenuName = NULL;							// 메뉴 이름을 쓰지 않는 것으로 설정
	wc.style = NULL;								// windows 고유 스타일을 제외한 나머지에 대한 사용 여부 결정

	RegisterClass(&wc);								// 윈도우 클래스를 등록함. 최초 등록한 것 한번만 등록하며 나머지는 무시

	// HWND : H는 Handle WND의 약자
	HWND hWnd = CreateWindow(L"tipssoft", L"www.tipssoft.com",
		WS_OVERLAPPEDWINDOW,100, 90, 400, 350, NULL, NULL, hlnstance, NULL);

	// 윈도우 핸들 값을 넘겨줌
	ShowWindow(hWnd, nCmdShow);
	// 시스템이 어떤 상황이든 보여주는 함수
	UpdateWindow(hWnd);
	// 메세지를 복사해서 가져오며 포인터가 아닌 구조체 이용
	MSG msg;
	// 대부분 1을 반환, wm.quit메세지가 들어오면 0을 반환
	while (GetMessage(&msg, NULL, 0, 0)) {
		// &msg를 이 어플리케이션이 사용 가능한 값으로 변환
		TranslateMessage(&msg);
		// 이 메세지를 실행하라는 의미
		DispatchMessage(&msg);
	}
	// wm_quit메시지의 w_Param값 반환
	return msg.wParam;


}

