// UseDLibrary.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
#include "UseDLibrary.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ������ ���� ���α׷� ��ü�Դϴ�.

CWinApp theApp;

using namespace std;

// ���ǵ� �Լ��� �Լ� �����͸� �̿��ϹǷ� main �ۿ��� �Լ� �����͸� ������
typedef void(*DLibraryFunction)();

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
			// DLibrary.dll�� �ҷ����� ���ǵ� �Լ��� ȣ���Ѵ�.
			CString m_str = _T("DLibrary.dll");
			HMODULE m_DLibrary = LoadLibrary(m_str);

			if (m_DLibrary == NULL) {
				cout << "LoadLibrary fail!\n";
			} else {
				DLibraryFunction func = (DLibraryFunction)GetProcAddress(m_DLibrary, "ExternFunction");
			
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
