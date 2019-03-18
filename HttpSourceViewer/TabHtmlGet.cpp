// TabHtmlGet.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "HttpSourceViewer.h"
#include "TabHtmlGet.h"
#include "afxdialogex.h"


// CTabHtmlGet �Ի���

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
END_MESSAGE_MAP()


// CTabHtmlGet ��Ϣ�������


void CTabHtmlGet::OnBnClickedButtonClearHtmlBody()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	m_htmlGetEdit.SetWindowTextW(TEXT(""));
}


void CTabHtmlGet::OnBnClickedButtonCopyHtmlBody()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	m_htmlGetEdit.SetSel(0, -1);
	m_htmlGetEdit.Copy();
	m_htmlGetEdit.SetSel(0, 0);
}
