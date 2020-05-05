
// DemoDialogDlg.h : 头文件
//

#pragma once
//#include <WinSock2.h>
//#include <Iphlpapi.h>
//#pragma comment(lib,"Iphlpapi.lib") 

// CDemoDialogDlg 对话框
class CDemoDialogDlg : public CDialogEx
{
// 构造
public:
	CDemoDialogDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_DEMODIALOG_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnStnClickedStaticOutput();
	afx_msg void OnBnClickedCount();
	afx_msg void OnEnChangeEditInput();
	afx_msg void OnBnClickedShowIpmac();
};
