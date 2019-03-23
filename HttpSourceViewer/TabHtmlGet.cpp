// TabHtmlGet.cpp : 实现文件
//

#include "stdafx.h"
#include "HttpSourceViewer.h"
#include "TabHtmlGet.h"
#include "afxdialogex.h"


// CTabHtmlGet 对话框

IMPLEMENT_DYNAMIC(CTabHtmlGet, CDialogEx)

CTabHtmlGet::CTabHtmlGet(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTabHtmlGet::IDD, pParent)
{

}

CTabHtmlGet::~CTabHtmlGet()
{
}

void CTabHtmlGet::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_HTML_GET, m_htmlGetEdit);
}


BEGIN_MESSAGE_MAP(CTabHtmlGet, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR_HTML_GET, &CTabHtmlGet::OnBnClickedButtonClearHtmlBody)
	ON_BN_CLICKED(IDC_BUTTON_COPY_HTML_GET, &CTabHtmlGet::OnBnClickedButtonCopyHtmlBody)
	ON_WM_SIZE()
END_MESSAGE_MAP()

BEGIN_EASYSIZE_MAP(CTabHtmlGet)
	EASYSIZE(IDC_EDIT_HTML_GET, ES_BORDER, ES_BORDER, ES_BORDER, ES_BORDER, 0)
END_EASYSIZE_MAP


// CTabHtmlGet 消息处理程序


void CTabHtmlGet::OnBnClickedButtonClearHtmlBody()
{
	// TODO:  在此添加控件通知处理程序代码
	m_htmlGetEdit.SetWindowTextW(TEXT(""));
}


void CTabHtmlGet::OnBnClickedButtonCopyHtmlBody()
{
	// TODO:  在此添加控件通知处理程序代码
	m_htmlGetEdit.SetSel(0, -1);
	m_htmlGetEdit.Copy();
	m_htmlGetEdit.SetSel(0, 0);
}


BOOL CTabHtmlGet::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	INIT_EASYSIZE;

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CTabHtmlGet::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	UPDATE_EASYSIZE;
}
