
// Thread_EXDlg.h : 헤더 파일
//

#pragma once
#include "afxwin.h"
#include <Pdh.h>
#include <IPHlpApi.h>
#pragma comment(lib, "pdh.lib")
#pragma comment(lib, "Iphlpapi.lib")

class CSystemStatus {
private:
	HQUERY m_hQuery;
	size_t m_CPUCoreCount;
	HCOUNTER m_hCounterCPUTotal;
	HCOUNTER* m_phCounterCPUCore;

	size_t m_NetAdaptorCount;
	LPTSTR m_lpNetAdaptorList;
	HCOUNTER* m_phCounterNetAdaptor;

public:
	CSystemStatus();
	~CSystemStatus(void);

	void Init();
	void Update();
	void Terminate();

	size_t getCPUCount() { return m_CPUCoreCount; }
	void getCPUStatus(LONG &total, LONG* arrCore, size_t arrCoreSize);
	void getRAMStatus(int &availableMem, int &physicalMem); // 단위 MB

	size_t getNetAdaptorCount() { return m_NetAdaptorCount; }
	const LPTSTR getNetAdaptorList() { return m_lpNetAdaptorList; }
	void getNETStatus(LONG *adapTotalByte, size_t adaptorCount);
};

// CThread_EXDlg 대화 상자
class CThread_EXDlg : public CDialogEx
{
// 생성입니다.
public:
	CThread_EXDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_THREAD_EX_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CWinThread *p1;
	CString m_staticDisp;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	static UINT TimeThread(LPVOID _mothod);
	
	
	CEdit m_strEditOutput;
};
