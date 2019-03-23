// TabHtmlHead.cpp : 实现文件
//

#include "stdafx.h"
#include "HttpSourceViewer.h"
#include "TabHtmlHead.h"
#include "afxdialogex.h"

#include "CFileProcess.h"

// CTabHtmlHead 对话框

IMPLEMENT_DYNAMIC(CTabHtmlHead, CDialog)


CTabHtmlHead::CTabHtmlHead(CWnd* pParent /*=NULL*/)
	: CDialog(CTabHtmlHead::IDD, pParent)
{

}

CTabHtmlHead::~CTabHtmlHead()
{
}

void CTabHtmlHead::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_HTML_HEAD, m_htmlHeadEdit);
}


BEGIN_MESSAGE_MAP(CTabHtmlHead, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR_HTML_HEAD, &CTabHtmlHead::OnBnClickedButtonClearHtmlHead)
	ON_BN_CLICKED(IDC_BUTTON_COPY_HTML_HEAD, &CTabHtmlHead::OnClickedButtonCopyHtmlHead)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BUTTON_SAVEA_HTML_HEAD, &CTabHtmlHead::OnBnClickedButtonSaveaHtmlHead)
END_MESSAGE_MAP()

BEGIN_EASYSIZE_MAP(CTabHtmlHead)
	EASYSIZE(IDC_EDIT_HTML_HEAD, ES_BORDER, ES_BORDER, ES_BORDER, ES_BORDER, 0)
END_EASYSIZE_MAP


// CTabHtmlHead 消息处理程序


void CTabHtmlHead::OnBnClickedButtonClearHtmlHead()
{
	// TODO:  在此添加控件通知处理程序代码
	m_htmlHeadEdit.SetWindowTextW(TEXT(""));
}


void CTabHtmlHead::OnClickedButtonCopyHtmlHead()
{
	// TODO:  在此添加控件通知处理程序代码
	m_htmlHeadEdit.SetSel(0, -1);
	m_htmlHeadEdit.Copy();
	m_htmlHeadEdit.SetSel(0, 0);

	// 设置字体
	CFont fnt;
	fnt.CreatePointFont(100, TEXT("黑体"));
	m_htmlHeadEdit.SetFont(&fnt);
}


void CTabHtmlHead::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	UPDATE_EASYSIZE;
}



BOOL CTabHtmlHead::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	INIT_EASYSIZE;

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CTabHtmlHead::OnBnClickedButtonSaveaHtmlHead()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strContent;
	m_htmlHeadEdit.GetWindowTextW(strContent);

	CFileProcess::SaveFile(strContent);

}
