
// DemoDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Demo.h"
#include "DemoDlg.h"
#include "CommonTool.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CDemoDlg �Ի���



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


// CDemoDlg ��Ϣ�������

BOOL CDemoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CDemoDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CDemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CDemoDlg::OnBnClickedOk()
{
	UpdateData(TRUE);   //��ȡ�༭���ֵ��������false��֮
	//MessageBox(m_ServIp, "����ֵ", MB_OK);
	//DataToThread * ptmp = (DataToThread * )malloc(sizeof(DataToThread)); // ������new��malloc�����������malloc,������ù��캯����CString���г�ʼ��
	DataToThread * ptmp = new DataToThread();
	ptmp->_ServIp = m_ServIp;

	UINT idThread = 0;
	HANDLE hThread = (HANDLE)_beginthreadex(NULL, 0, CDemoDlg::ConnectWithServ, ptmp, 0, &idThread);
	//HANDLE hThreadAndEvent[1];
	//hThreadAndEvent[0] = hThread;

	//MsgWaitForMultipleObjects(1, hThreadAndEvent, 2000, QS_ALLEVENTS, MWMO_INPUTAVAILABLE);
	WaitForSingleObject(hThread, INFINITE);  // ����������ʵ��Ľ�,���⿨��

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