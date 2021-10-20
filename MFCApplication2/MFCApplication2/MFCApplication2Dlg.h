
// MFCApplication2Dlg.h : ��� ����
//

#pragma once
#include "afxwin.h"
#include <Pdh.h>
#include <PdhMsg.h>
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
	HCOUNTER* m_phCounterNetAdapter;

public:
	CSystemStatus();
	~CSystemStatus(void);

	void Init();
	void Update();
	void Terminate();

	size_t getCPUCount() { return m_CPUCoreCount; }
	void getCPUStatus(LONG &total, LONG* arrCore, size_t arrCoreSize);
	void getRAMStatus(int &availableMem, int &physicalMem); // ���� : MB

	size_t getNetAdaptorCount() { return m_NetAdaptorCount; }
	const LPTSTR getNetAdatorList() { return m_lpNetAdaptorList; }
	void getNETStatus(LONG* adapTotalByte, size_t adaptorCount);

};

// CMFCApplication2Dlg ��ȭ ����
class CMFCApplication2Dlg : public CDialogEx
{
// �����Դϴ�.
public:
	CMFCApplication2Dlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.
	

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCAPPLICATION2_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CEdit m_strEditOutput;
};
