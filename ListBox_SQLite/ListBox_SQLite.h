
// ListBox_SQLite.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CListBox_SQLiteApp:
// �� Ŭ������ ������ ���ؼ��� ListBox_SQLite.cpp�� �����Ͻʽÿ�.
//

class CListBox_SQLiteApp : public CWinApp
{
public:
	CListBox_SQLiteApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CListBox_SQLiteApp theApp;