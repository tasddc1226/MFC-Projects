
// basic_clock.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// Cbasic_clockApp:
// �� Ŭ������ ������ ���ؼ��� basic_clock.cpp�� �����Ͻʽÿ�.
//

class Cbasic_clockApp : public CWinApp
{
public:
	Cbasic_clockApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern Cbasic_clockApp theApp;