
// HttpSourceViewerDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "HttpSourceViewer.h"
#include "HttpSourceViewerDlg.h"
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


// CHttpSourceViewerDlg 对话框

CHttpSourceViewerDlg* CHttpSourceViewerDlg::m_pThis = NULL;

CHttpSourceViewerDlg::CHttpSourceViewerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CHttpSourceViewerDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pThis = this;
}

void CHttpSourceViewerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_URL, m_urlEdit);
	DDX_Control(pDX, IDC_TAB_MAIN, m_mainTab);
	DDX_Control(pDX, IDC_STATIC_HTML_REQ_PROGRESS, m_htmlReqProgress);
}

BEGIN_MESSAGE_MAP(CHttpSourceViewerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(ID_BUTTON_PASTE, &CHttpSourceViewerDlg::OnBnClickedButtonPaste)
	ON_BN_CLICKED(ID_BUTTON_CLEAR, &CHttpSourceViewerDlg::OnBnClickedButtonClear)
//	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_MAIN, &CHttpSourceViewerDlg::OnSelchangeTabMain)
ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_MAIN, &CHttpSourceViewerDlg::OnTcnSelchangeTabMain)
ON_BN_CLICKED(ID_BUTTON_GO, &CHttpSourceViewerDlg::OnBnClickedButtonGo)
ON_COMMAND(ID_MAIN_GETMATCH, &CHttpSourceViewerDlg::OnMainGetmatch)
END_MESSAGE_MAP()


// CHttpSourceViewerDlg 消息处理程序

BOOL CHttpSourceViewerDlg::OnInitDialog()
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

	// TODO:  在此添加额外的初始化代码
	InitTabControl();
	m_urlEdit.SetWindowTextW(TEXT("http://www.5566.net"));
	m_htmlReqProgress.SetRange(0, 100);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CHttpSourceViewerDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CHttpSourceViewerDlg::OnPaint()
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
HCURSOR CHttpSourceViewerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CHttpSourceViewerDlg::OnBnClickedButtonPaste()
{
	// TODO:  在此添加控件通知处理程序代码
	m_urlEdit.Paste();
}


void CHttpSourceViewerDlg::OnBnClickedButtonClear()
{
	// TODO:  在此添加控件通知处理程序代码
	m_urlEdit.SetWindowTextW(TEXT(""));
}


void CHttpSourceViewerDlg::InitTabControl()
{
	// 插入3个Tab页面
	m_mainTab.InsertItem(0, TEXT("HTML 头"));
	m_mainTab.InsertItem(1, TEXT("HTML 内容"));
	m_mainTab.InsertItem(2, TEXT("提取内容"));

	// 关联对话框，并且将IDC_TAB_MAIN控件设为父窗口
	m_tabHtmlHead.Create(IDD_DIALOG_TAB_HTML_HEAD, GetDlgItem(IDC_TAB_MAIN));
	m_tabHtmlBody.Create(IDD_DIALOG_TAB_HTML_BODY, GetDlgItem(IDC_TAB_MAIN));
	m_tabHtmlGet.Create(IDD_DIALOG_TAB_HTML_GET, GetDlgItem(IDC_TAB_MAIN));

	// 移动每个Tab页面到合适的位置
	MoveSubTab();

	// 分别设置隐藏和显示
	m_tabHtmlHead.ShowWindow(true);
	m_tabHtmlBody.ShowWindow(false);
	m_tabHtmlGet.ShowWindow(false);

	// 设置默认的选项卡
	m_mainTab.SetCurSel(0);
}


// 移动每个Tab页面到合适的位置
void CHttpSourceViewerDlg::MoveSubTab()
{
	static bool isFirstTime = true;

	if (isFirstTime)
	{
		// 获得IDC_TAB_MAIN的客户区大小
		CRect rectClient;
		m_mainTab.GetClientRect(&rectClient);
		
		// 调整子对话框在父窗口中的位置
		rectClient.top += 30;
		rectClient.bottom -= 10;
		rectClient.left += 10;
		rectClient.right -= 10;

		// 设置子对话框尺寸并移动到指定位置
		m_tabHtmlHead.MoveWindow(&rectClient);
		m_tabHtmlBody.MoveWindow(&rectClient);
		m_tabHtmlGet.MoveWindow(&rectClient);
	}
	isFirstTime = false;
}

void CHttpSourceViewerDlg::OnTcnSelchangeTabMain(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO:  在此添加控件通知处理程序代码
		int CurSel = m_mainTab.GetCurSel();
		switch (CurSel)
		{
		case 0:
			m_tabHtmlHead.ShowWindow(true);
			m_tabHtmlBody.ShowWindow(false);
			m_tabHtmlGet.ShowWindow(false);
			break;
		case 1:
			m_tabHtmlHead.ShowWindow(false);
			m_tabHtmlBody.ShowWindow(true);
			m_tabHtmlGet.ShowWindow(false);
			break;
		case 2:
			m_tabHtmlHead.ShowWindow(false);
			m_tabHtmlBody.ShowWindow(false);
			m_tabHtmlGet.ShowWindow(true);
			break;
		default:
			break;
		}

		*pResult = 0;
}


void CHttpSourceViewerDlg::OnBnClickedButtonGo()
{
	// TODO:  在此添加控件通知处理程序代码
	ProcessHttpRequest();
}


// 获取URL地址，然后请求服务，返回HTML头和内容
bool CHttpSourceViewerDlg::ProcessHttpRequest()
{
	// 获取需要请求的URL地址
	CString strUrl;
	m_urlEdit.GetWindowTextW(strUrl);

	// 构造HTTP客户端，发起请求
	WinHttpClient client(strUrl.GetBuffer(), &CHttpSourceViewerDlg::HtmlRequestProgress);
	// Send http request, a GET request by default.
	client.SendHttpRequest();

	//收集服务器返回的Http头和HTML内容
	// The response header.
	wstring httpResponseHeader = client.GetResponseHeader();

	// The response content.
	wstring httpResponseContent = client.GetResponseContent();

	//把Http头和Html内容显示在Tab标签页的文本框中
	// Set URL.
	m_tabHtmlHead.m_htmlHeadEdit.SetWindowTextW(httpResponseHeader.c_str());
	m_tabHtmlBody.m_htmlBodyEdit.SetWindowTextW(httpResponseContent.c_str());

	return true;
}


bool CHttpSourceViewerDlg::HtmlRequestProgress(double progress)
{
	m_pThis->m_htmlReqProgress.SetPos( static_cast<int>(progress) );
	return true;
}

void CHttpSourceViewerDlg::OnMainGetmatch()
{
	// TODO: 在此添加命令处理程序代码
	CString temp;

	for (vector<wstring>::iterator it = m_tabHtmlBody.m_vecMatch.begin(); it != m_tabHtmlBody.m_vecMatch.end(); ++it)
	{
		temp += (*it).c_str();
		temp += L"\r\n";
		// 下面的代码耦合性太高了，需要改进，可以通过从CTabHtmlBody给CHttpSourceViewerDlg主对话框发送消息来实现
		/* CHttpSourceViewerDlg* pHttpSourceViewDlg = ((CHttpSourceViewerDlg*)AfxGetMainWnd());
		pHttpSourceViewDlg->m_tabHtmlGet.m_htmlGetEdit.SetWindowTextW(temp);
		*/
		m_tabHtmlGet.m_htmlGetEdit.SetWindowTextW(temp);
	}
}
