
// DemoDialogDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DemoDialog.h"
#include "DemoDialogDlg.h"
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
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CDemoDialogDlg �Ի���




CDemoDialogDlg::CDemoDialogDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDemoDialogDlg::IDD, pParent)
	, m_num1(0)
	, m_num2(0)
	, m_num3(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDemoDialogDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_num1);
	DDX_Text(pDX, IDC_EDIT2, m_num2);
	DDX_Text(pDX, IDC_EDIT3, m_num3);
	DDX_Control(pDX, IDC_EDIT1, m_edit1);
	DDX_Control(pDX, IDC_EDIT2, m_edit2);
	DDX_Control(pDX, IDC_EDIT3, m_edit3);
}

BEGIN_MESSAGE_MAP(CDemoDialogDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CDemoDialogDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CDemoDialogDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CDemoDialogDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CDemoDialogDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CDemoDialogDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CDemoDialogDlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON7, &CDemoDialogDlg::OnBnClickedButton7)
END_MESSAGE_MAP()


// CDemoDialogDlg ��Ϣ�������

BOOL CDemoDialogDlg::OnInitDialog()
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CDemoDialogDlg::OnPaint()
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
HCURSOR CDemoDialogDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CDemoDialogDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int num1,num2,num3;
	TCHAR ch1[12],ch2[12],ch3[12];
	GetDlgItem(IDC_EDIT1)->GetWindowTextW(ch1, 12);
	GetDlgItem(IDC_EDIT2)->GetWindowTextW(ch2, 12);

	num1 = _ttoi(ch1);
	num2 = _ttoi(ch2);

	num3 = num1 + num2;

	_itot(num3,ch3,10);
	GetDlgItem(IDC_EDIT3)->SetWindowTextW(ch3);
}


void CDemoDialogDlg::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int num1,num2,num3;
	TCHAR ch1[12],ch2[12],ch3[12];

	GetDlgItemText(IDC_EDIT1,ch1,12);
	GetDlgItemText(IDC_EDIT2,ch2, 12);

	num1 = _ttoi(ch1);
	num2 = _ttoi(ch2);

	num3 = num1 + num2;

	_itot(num3,ch3,10);
	SetDlgItemText(IDC_EDIT3,ch3);
}


void CDemoDialogDlg::OnBnClickedButton3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int num1,num2,num3;

	num1 = GetDlgItemInt(IDC_EDIT1);
	num2 = GetDlgItemInt(IDC_EDIT2);

	num3 = num1 + num2;

	SetDlgItemInt(IDC_EDIT3,num3);
}


void CDemoDialogDlg::OnBnClickedButton4()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE); //�ӿؼ���ֵ���µ�����
	m_num3 = m_num1 + m_num2;
	UpdateData(FALSE); //�ѱ������µ��ؼ���ֵ
}


void CDemoDialogDlg::OnBnClickedButton5()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int num1,num2,num3;
	TCHAR ch1[12],ch2[12],ch3[12];

	m_edit1.GetWindowTextW(ch1,12);
	m_edit2.GetWindowTextW(ch2,12);

	num1 = _ttoi(ch1);
	num2 = _ttoi(ch2);

	num3 = num1 + num2;
	_itot(num3, ch3, 10);
	m_edit3.SetWindowTextW(ch3);
}





void CDemoDialogDlg::OnBnClickedButton6()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int num1,num2,num3;
	TCHAR ch1[12],ch2[12],ch3[12];

	::SendMessage(GetDlgItem(IDC_EDIT1)->m_hWnd, WM_GETTEXT, 12, (LPARAM) ch1);
	::SendMessage(GetDlgItem(IDC_EDIT2)->m_hWnd, WM_GETTEXT, 12, (LPARAM) ch2);

	num1 = _ttoi(ch1);
	num2 = _ttoi(ch2);

	num3 = num1 + num2;

	_itot(num3, ch3 ,10);

	::SendMessage(GetDlgItem(IDC_EDIT3)->m_hWnd, WM_SETTEXT, 0, (LPARAM)ch3);
}


void CDemoDialogDlg::OnBnClickedButton7()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int num1,num2,num3;
	TCHAR ch1[12],ch2[12],ch3[12];
	SendDlgItemMessage(IDC_EDIT1, WM_GETTEXT, 12, (LPARAM)ch1);
	SendDlgItemMessage(IDC_EDIT2, WM_GETTEXT, 12, (LPARAM)ch2);

	num1 = _ttoi(ch1);
	num2 = _ttoi(ch2);

	num3 = num1 + num2;

	_itot(num3, ch3 ,10);
	SendDlgItemMessage(IDC_EDIT3, WM_SETTEXT ,12 , (LPARAM)ch3);
}
