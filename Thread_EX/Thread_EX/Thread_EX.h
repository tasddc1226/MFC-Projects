
// Thread_EX.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CThread_EXApp:
// �� Ŭ������ ������ ���ؼ��� Thread_EX.cpp�� �����Ͻʽÿ�.
//

class CThread_EXApp : public CWinApp
{
public:
	CThread_EXApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CThread_EXApp theApp;