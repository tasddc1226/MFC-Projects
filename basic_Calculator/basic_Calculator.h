
// basic_Calculator.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// Cbasic_CalculatorApp:
// �� Ŭ������ ������ ���ؼ��� basic_Calculator.cpp�� �����Ͻʽÿ�.
//

class Cbasic_CalculatorApp : public CWinApp
{
public:
	Cbasic_CalculatorApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern Cbasic_CalculatorApp theApp;