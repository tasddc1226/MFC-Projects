// getProcessList.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include <Windows.h>
#include <TlHelp32.h>
#include <stdio.h>
#include <iostream>

using namespace std;


int main(int argc, char* argv[])
{
	HANDLE hSnap;
	PROCESSENTRY32 sttPE;

	hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	if (hSnap == INVALID_HANDLE_VALUE) {
		printf("CreateTolhelp32Snapshor error\n");
		return 0;
	}

	sttPE.dwSize = sizeof(PROCESSENTRY32);
	if (!Process32First(hSnap, &sttPE)) {
		printf("Process32First error\n");
	}
	else {
		do {
			printf("%s (pid=%d)\n", sttPE.szExeFile, sttPE.th32ProcessID);

		} while (Process32Next(hSnap, &sttPE));
	}

	CloseHandle(hSnap);
	int t;
	cin >> t;

    return 0;
}

