
// DemoDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Demo.h"
#include "DemoDlg.h"
#include "CommonTool.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CDemoDlg 对话框



CDemoDlg::CDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DEMO_DIALOG, pParent)
	, m_ServIp(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_SRVIP_EDIT, m_ServIp);
	DDV_MaxChars(pDX, m_ServIp, 255);
}

BEGIN_MESSAGE_MAP(CDemoDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CDemoDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CDemoDlg 消息处理程序

BOOL CDemoDlg::OnInitDialog()
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
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
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CDemoDlg::OnPaint()
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
HCURSOR CDemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CDemoDlg::OnBnClickedOk()
{
	UpdateData(TRUE);   //获取编辑框的值到变量，false则反之
	//MessageBox(m_ServIp, "测试值", MB_OK);
	//DataToThread * ptmp = (DataToThread * )malloc(sizeof(DataToThread)); // 这里有new和malloc的区别，如果是malloc,不会调用构造函数对CString进行初始化
	DataToThread * ptmp = new DataToThread();
	ptmp->_ServIp = m_ServIp;

	UINT idThread = 0;
	HANDLE hThread = (HANDLE)_beginthreadex(NULL, 0, CDemoDlg::ConnectWithServ, ptmp, 0, &idThread);
	//HANDLE hThreadAndEvent[1];
	//hThreadAndEvent[0] = hThread;

	//MsgWaitForMultipleObjects(1, hThreadAndEvent, 2000, QS_ALLEVENTS, MWMO_INPUTAVAILABLE);
	WaitForSingleObject(hThread, INFINITE);  // 这里可以做适当改进,以免卡死

	//CDialogEx::OnOK();
}

unsigned __stdcall CDemoDlg::ConnectWithServ(void * pthis) {
	DataToThread * pDataToThread = (DataToThread *)pthis;

	DWORD  dwReadSize = 0;
	char *pData = NULL;
	char  pReq[4096] = { 0 };
	HANDLE hInternet = NULL;
	HANDLE hSession = NULL;
	HANDLE hRequest = NULL;
	const char * apiCsp = "/sangfor/testp";
	OutputDebugStringA("### ConnectServ start.");
	if (!ConnectServ(apiCsp, hInternet, hSession, hRequest, pDataToThread->_ServIp, 80))
	{
		OutputDebugStringA("### ConnectServ failed.");
		return 0;
	}
	OutputDebugStringA("### CreateJsonReqData start.");
	if (CreateJsonReqData(pReq) == FALSE)
	{
		OutputDebugStringA("CreateJsonReqData failed.");
		return 0;
	}
	OutputDebugStringA("### SendRequestToServ start.");
	if (!SendRequestToServ(hRequest, pReq, strlen(pReq)))
	{
		OutputDebugStringA("SendRequestToServer failed.");
		return 0;
	}
	OutputDebugStringA("### ReadServBackData start.");
	if (!ReadServBackData(hRequest, pData, dwReadSize, FALSE))
	{
		OutputDebugStringA("ReadServerBackData failed.");
		return 0;
	}
	OutputDebugStringA("### AnalyzeRecvData start.");
	if (AnalyzeRecvData(pData) == FALSE)
	{
		OutputDebugStringA("AnalyzeRecvData failed.");
		return 0;
	}
	return 1;
}