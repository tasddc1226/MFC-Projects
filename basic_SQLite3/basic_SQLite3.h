
// basic_SQLite3.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// Cbasic_SQLite3App:
// �� Ŭ������ ������ ���ؼ��� basic_SQLite3.cpp�� �����Ͻʽÿ�.
//

class Cbasic_SQLite3App : public CWinApp
{
public:
	Cbasic_SQLite3App();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern Cbasic_SQLite3App theApp;