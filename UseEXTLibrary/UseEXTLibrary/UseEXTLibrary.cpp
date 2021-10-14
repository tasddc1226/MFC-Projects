// UseEXTLibrary.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
#include "UseEXTLibrary.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ������ ���� ���α׷� ��ü�Դϴ�.

CWinApp theApp;

using namespace std;
typedef void(*EXTLibraryFunc)();
int main()
{
    int nRetCode = 0;

    HMODULE hModule = ::GetModuleHandle(nullptr);

    if (hModule != nullptr)
    {
        // MFC�� �ʱ�ȭ�մϴ�. �ʱ�ȭ���� ���� ��� ������ �μ��մϴ�.
        if (!AfxWinInit(hModule, nullptr, ::GetCommandLine(), 0))
        {
            // TODO: ���� �ڵ带 �ʿ信 ���� �����մϴ�.
            wprintf(L"�ɰ��� ����: MFC�� �ʱ�ȭ���� ���߽��ϴ�.\n");
            nRetCode = 1;
        }
        else
        {
            // TODO: ���� ���α׷��� ������ ���⿡�� �ڵ��մϴ�.
			CString m_str = _T("EXTLibrary.dll");
			HMODULE m_EXTLibrary = LoadLibrary(m_str);

			if (m_EXTLibrary == NULL) {
				cout << "LoadLibrary fail!\n";
			}
			else {
				EXTLibraryFunc func = (EXTLibraryFunc)GetProcAddress(m_EXTLibrary, "ExternFunc");
				system("pause");

			}
        }
    }
    else
    {
        // TODO: ���� �ڵ带 �ʿ信 ���� �����մϴ�.
        wprintf(L"�ɰ��� ����: GetModuleHandle ����\n");
        nRetCode = 1;
    }

    return nRetCode;
}
