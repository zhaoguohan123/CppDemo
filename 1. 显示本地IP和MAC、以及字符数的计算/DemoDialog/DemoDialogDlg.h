
// DemoDialogDlg.h : ͷ�ļ�
//

#pragma once
//#include <WinSock2.h>
//#include <Iphlpapi.h>
//#pragma comment(lib,"Iphlpapi.lib") 

// CDemoDialogDlg �Ի���
class CDemoDialogDlg : public CDialogEx
{
// ����
public:
	CDemoDialogDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_DEMODIALOG_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
