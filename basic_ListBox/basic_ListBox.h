
// basic_ListBox.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// Cbasic_ListBoxApp:
// �� Ŭ������ ������ ���ؼ��� basic_ListBox.cpp�� �����Ͻʽÿ�.
//

class Cbasic_ListBoxApp : public CWinApp
{
public:
	Cbasic_ListBoxApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern Cbasic_ListBoxApp theApp;