// CPUCheck.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include <math.h>
#define _WIN32_DCOM
#include <iostream>
using namespace std;
#include <comdef.h>
#include <WbemIdl.h>

#pragma comment(lib, "wbemuuid.lib")

int GetValues(IWbemServices *pSvc, ULONG *ulVal, int n) {
	int nError = 0;

	// 6단계
	// WMI의 요청을 만들기 위해 IWbemServices 포인터를 사용
	// 예를들어, OS의 이름을 가져오려면
	IEnumWbemClassObject* pEnumerator = NULL;
	HRESULT hres = pSvc->ExecQuery(
		bstr_t("WQL"),
		bstr_t("SELECT * FROM Win32_PerfRawData_PerfOS_Processor"),
		WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
		NULL,
		&pEnumerator);

	if (FAILED(hres))
	{
		cout << "Query for operating system name failed."
			<< " Error code = 0x"
			<< hex << hres << endl;

		return 1;               // Fxn has failed.
	}

	// 7단계
	// 6단계에서 날린 Query에 대한 데이터를 받아옴
	IWbemClassObject *pclsObj;
	ULONG uReturn = 0;
	int nCtr = 0;

	while (nCtr<n)
	{
		HRESULT hr = pEnumerator->Next(WBEM_INFINITE, 1,
			&pclsObj, &uReturn);

		if (0 == uReturn)
		{
			break;
		}

		VARIANT vtProp;
		VariantInit(&vtProp);

		hr = pclsObj->Get(L"PercentProcessorTime", 0, &vtProp, 0, 0);
		ulVal[nCtr] = _wtol(vtProp.bstrVal);
		VariantClear(&vtProp);

		hr = pclsObj->Get(L"TimeStamp_Sys100NS", 0, &vtProp, 0, 0);
		ulVal[nCtr + 1] = _wtol(vtProp.bstrVal);
		VariantClear(&vtProp);
		nCtr += 2;
	}
	pclsObj->Release();
	pEnumerator->Release();
	return nError;
}

int main(int argc, char**argv)
{
	SYSTEM_INFO stSysInfo;
	GetSystemInfo(&stSysInfo);

	int nproc = stSysInfo.dwNumberOfProcessors;		  // CPU의 스레드 개수로 CPU의 코어 개수가 아님!
	int proc_Arch = stSysInfo.wProcessorArchitecture; // 설치된 운영 체제의 프로세서 아키텍처
	int page_Size = stSysInfo.dwPageSize;			  // 페이지 크기
	int proc_Type = stSysInfo.dwProcessorType;		  // 프로세서 type

	MEMORYSTATUSEX memInfo;
	memInfo.dwLength = sizeof(_MEMORYSTATUSEX);
	GlobalMemoryStatusEx(&memInfo);
	static DWORDLONG totalVirtualMem = memInfo.ullTotalPageFile;						   // 총 가상 메모리
	DWORDLONG vitualMemUsed = totalVirtualMem - memInfo.ullAvailPageFile;		   // 현재 사용 중인 가상 메모리

	static DWORDLONG totalPhysMem = memInfo.ullTotalPhys;					// 총 물리적 메모리(RAM)
	DWORDLONG physMemAvail;							// 물리적 메모리 여유량
	DWORDLONG physMemUsed;				            // 현재 사용 중인 물리 메모리
	
	for (int i = 0; i < 10; i++) {
		physMemAvail = memInfo.ullAvailPhys;
		physMemUsed = totalPhysMem - physMemAvail;
		cout << "여유 물리 메모리:\t" << physMemAvail << "\n";
		cout << "사용중인 물리 메모리:\t" << physMemUsed << "\n";
		cout << "총 물리 메모리:\t\t" << totalPhysMem << "\n";
		Sleep(1000);
	}
	
	//cout << "사용중인 가상 메모리:\t" << vitualMemUsed << "\n";
	//cout << "총 가상 메모리:\t\t" << totalVirtualMem << "\n";

	

	// 1단계
	// COM 초기화
	HRESULT hres;
	hres = CoInitializeEx(0, COINIT_MULTITHREADED);
	if (FAILED(hres)) {
		cout << "Failed to initialize COM library. Error code = 0x" << hex << hres << endl;
		return 1;                  // Program has failed.
	}

	//cout << "Please enter the # of processors : ";
	//cin >> nproc;
	


	ULONG *ulinitVal = new ULONG[(nproc + 1) * 2]; // +1 for the total
	int i = 0;
	ULONG *ulVal = new ULONG[(nproc + 1) * 2]; // +1 for the total

	// 2단계
	// COM 보안 수준 설정
	hres = CoInitializeSecurity(
		NULL,
		-1,
		NULL,
		NULL,
		RPC_C_AUTHN_LEVEL_DEFAULT,
		RPC_C_IMP_LEVEL_IMPERSONATE,
		NULL,
		EOAC_NONE,
		NULL
	);

	if (FAILED(hres)) {
		cout << "Failed to initialize security. Error code = 0x" << hex << hres << endl;
		CoUninitialize();
		return 1;                    // Program has failed.
	}

	// 3단계
	// WMI에 대한 초기 로케이터 가져오기
	IWbemLocator *pLoc = NULL;

	hres = CoCreateInstance(
		CLSID_WbemLocator,
		0,
		CLSCTX_INPROC_SERVER,
		IID_IWbemLocator, (LPVOID *)&pLoc
	);

	if (FAILED(hres)) {
		cout << "Failed to create IWbemLocator object." << " Err code = 0x" << hex << hres << endl;
		CoUninitialize();
		return 1;                 // Program has failed.
	}

	// 4단계
	// IWbemLocator::ConnectServer 방법으로 WMI 연결하기
	IWbemServices *pSvc = NULL;

	// Connect to the root\cimv2 namespace with
	// the current user and obtain pointer pSvc
	// to make IWbemServices calls.
	hres = pLoc->ConnectServer(
		_bstr_t(L"ROOT\\CIMV2"), // Object path of WMI namespace
		NULL,                    // User name. NULL = current user
		NULL,                    // User password. NULL = current
		0,                       // Locale. NULL indicates current
		NULL,                    // Security flags.
		0,                       // Authority (e.g. Kerberos)
		0,                       // Context object 
		&pSvc                    // pointer to IWbemServices proxy
	);

	if (FAILED(hres))
	{
		cout << "Could not connect. Error code = 0x" << hex << hres << endl;
		pLoc->Release();
		CoUninitialize();
		return 1;                // Program has failed.
	}

	// 연결 성공
	cout << "Connected to ROOT\\CIMV2 WMI namespace" << endl;

	// 5단계
	// 프록시에서 보안 수준 설정
	CoSetProxyBlanket(
		pSvc,                        // Indicates the proxy to set
		RPC_C_AUTHN_WINNT,           // RPC_C_AUTHN_xxx
		RPC_C_AUTHZ_NONE,            // RPC_C_AUTHZ_xxx
		NULL,                        // Server principal name 
		RPC_C_AUTHN_LEVEL_CALL,      // RPC_C_AUTHN_LEVEL_xxx 
		RPC_C_IMP_LEVEL_IMPERSONATE, // RPC_C_IMP_LEVEL_xxx
		NULL,                        // client identity
		EOAC_NONE                    // proxy capabilities 
	);

	if (FAILED(hres))
	{
		cout << "Could not set proxy blanket. Error code = 0x" << hex << hres << endl;
		pSvc->Release();
		pLoc->Release();
		CoUninitialize();
		return 1;               // Program has failed.
	}

	char szVal[64];

	while (i++ < 1000) {
		// 초기값 가져오기
		if (GetValues(pSvc, ulinitVal, (nproc + 1)*2))
		{
			delete ulinitVal;
			goto Cleanup;
		}

		Sleep(2000);

		//Get the initial Values
		GetValues(pSvc, ulVal, (nproc + 1)*2);

		if ((ulVal[1] - ulinitVal[1])>0)
		{
			sprintf(szVal, "%0.2f", fabs(100.0 - ((float)(ulVal[0] - ulinitVal[0]) / (ulVal[1] - ulinitVal[1])) * 100));
			cout << "PercentProcessorTime CPU 0: \t\t" << szVal << endl;
		}
		else
		{
			cout << "Divide by zero for Processor 0" << endl;
		}

		if (nproc>1)
		{
			if ((ulVal[3] - ulinitVal[3])>0)
			{
				sprintf(szVal, "%0.2f", fabs(100.0 - ((float)(ulVal[2] - ulinitVal[2]) / (ulVal[3] - ulinitVal[3])) * 100));
				cout << "PercentProcessorTime CPU 1:\t\t" << szVal << endl;
			}
			else
			{
				cout << "Divide by zero for Processor 1" << endl;
			}

			if ((ulVal[5] - ulinitVal[5])>0)
			{
				sprintf(szVal, "%0.2f", fabs(100.0 - ((float)(ulVal[4] - ulinitVal[4]) / (ulVal[5] - ulinitVal[5])) * 100));
				cout << "PercentProcessorTime  CPU Total:\t" << szVal << endl;
			}
			else
			{
				cout << "Divide by zero for total" << endl;
			}
		}
		else
		{
			if ((ulVal[3] - ulinitVal[3])>0)
			{
				sprintf(szVal, "%0.2f", fabs(100.0 - ((float)(ulVal[2] - ulinitVal[2]) / (ulVal[3] - ulinitVal[3])) * 100));
				cout << "PercentProcessorTime  CPU Total:\t" << szVal << endl;
			}
			else
			{
				cout << "Divide by zero for total" << endl;
			}
		}


	}
	delete ulinitVal;
	delete ulVal;

Cleanup:
	pSvc->Release();
	pLoc->Release();
	CoUninitialize();

	getchar();
    return 0; // Program successfully completed.
}

