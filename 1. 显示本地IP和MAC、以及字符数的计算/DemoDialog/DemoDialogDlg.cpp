
// DemoDialogDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "DemoDialog.h"
#include "DemoDialogDlg.h"
#include "afxdialogex.h"
#pragma comment(lib,"iphlpapi.lib")

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CDemoDialogDlg 对话框




CDemoDialogDlg::CDemoDialogDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDemoDialogDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDemoDialogDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CDemoDialogDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_COUNT, &CDemoDialogDlg::OnBnClickedCount)
	ON_EN_CHANGE(IDC_EDIT_INPUT, &CDemoDialogDlg::OnEnChangeEditInput)
	ON_BN_CLICKED(IDC_SHOW_IPMAC, &CDemoDialogDlg::OnBnClickedShowIpmac)
END_MESSAGE_MAP()


// CDemoDialogDlg 消息处理程序

BOOL CDemoDialogDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CDemoDialogDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CDemoDialogDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CDemoDialogDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CDemoDialogDlg::OnBnClickedCount()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strInput; 

	GetDlgItemText(IDC_EDIT_INPUT, strInput);

	int nLen = strInput.GetLength();

	CString strOutput;

	strOutput.Format(TEXT("字符串长度： %d, 字符个数 ： %d"), nLen, nLen);

	SetDlgItemText(IDC_STATIC_OUTPUT, strOutput);
}


void CDemoDialogDlg::OnEnChangeEditInput()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CDemoDialogDlg::OnBnClickedShowIpmac()
{
	// TODO: 在此添加控件通知处理程序代码
	CString myIP, myMAC, Show_addInfo_buf;
	ULONG outBufLen = 0;
	DWORD dwRetVal = 0;

	PIP_ADAPTER_INFO pAdapterInfo;
	PIP_ADAPTER_INFO pAdapterInfoTmp = NULL;

	pAdapterInfo = (IP_ADAPTER_INFO *)GlobalAlloc(GMEM_ZEROINIT, sizeof(IP_ADAPTER_INFO));

	//异常处理
	if (GetAdaptersInfo(pAdapterInfo, &outBufLen)!= ERROR_SUCCESS)
	{
		GlobalFree(pAdapterInfo);
		pAdapterInfo = (IP_ADAPTER_INFO *)GlobalAlloc(GMEM_ZEROINIT, outBufLen);
	}

	if ((dwRetVal = GetAdaptersInfo(pAdapterInfo, &outBufLen)) == NO_ERROR)
	{
		pAdapterInfoTmp = pAdapterInfo;
		myIP = "";
		while (pAdapterInfoTmp)
		{
			if (pAdapterInfoTmp->Type == MIB_IF_TYPE_ETHERNET)
			{
				if (pAdapterInfoTmp->CurrentIpAddress)
				{
					myIP = pAdapterInfoTmp->CurrentIpAddress->IpAddress.String;
				} 
				else
				{
					myIP = pAdapterInfoTmp->IpAddressList.IpAddress.String;
				}
			}
			if (!myIP.IsEmpty() && myIP.CompareNoCase(TEXT("0.0.0.0"))!=0)
			{
				myMAC.Format(TEXT("%02X-%02X-%02X-%02X-%02X-%02X"),
					pAdapterInfoTmp->Address[0],
					pAdapterInfoTmp->Address[1],
					pAdapterInfoTmp->Address[2],
					pAdapterInfoTmp->Address[3],
					pAdapterInfoTmp->Address[4],
					pAdapterInfoTmp->Address[5]);
				break;
			}
			pAdapterInfoTmp =  pAdapterInfoTmp->Next;
		}
	}
	//得到了Cstring类型的 IP和mac信息
	Show_addInfo_buf.Format(TEXT("IP： %s \n\n mac: %s"), myIP, myMAC);

	SetDlgItemText(IDC_STATIC_OUTPUT2, Show_addInfo_buf);
	GlobalFree(pAdapterInfo);
}






