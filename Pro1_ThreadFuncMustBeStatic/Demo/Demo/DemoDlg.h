
// DemoDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"

typedef struct _DataToThread
{
	CString  _ServIp;  // �����IP��������https://

}DataToThread, *pPataToThread;

// CDemoDlg �Ի���
class CDemoDlg : public CDialogEx
{
// ����
public:
	CDemoDlg(CWnd* pParent = NULL);	// ��׼���캯��
	static unsigned __stdcall ConnectWithServ(void * pthis);
// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DEMO_DIALOG };
#endif

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
	afx_msg void OnBnClickedOk();
	// ��������IP
	CString m_ServIp;
};
