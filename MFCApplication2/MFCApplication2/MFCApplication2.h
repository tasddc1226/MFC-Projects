
// MFCApplication2.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CMFCApplication2App:
// �� Ŭ������ ������ ���ؼ��� MFCApplication2.cpp�� �����Ͻʽÿ�.
//

class CMFCApplication2App : public CWinApp
{
public:
	CMFCApplication2App();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CMFCApplication2App theApp;