
// MFCtest.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CMFCtestApp:
// �� Ŭ������ ������ ���ؼ��� MFCtest.cpp�� �����Ͻʽÿ�.
//

class CMFCtestApp : public CWinApp
{
public:
	CMFCtestApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CMFCtestApp theApp;