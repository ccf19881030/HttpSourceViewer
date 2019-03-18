// TabHtmlHead.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "HttpSourceViewer.h"
#include "TabHtmlHead.h"
#include "afxdialogex.h"


// CTabHtmlHead �Ի���

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
END_MESSAGE_MAP()


// CTabHtmlHead ��Ϣ�������


void CTabHtmlHead::OnBnClickedButtonClearHtmlHead()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	m_htmlHeadEdit.SetWindowTextW(TEXT(""));
}


void CTabHtmlHead::OnClickedButtonCopyHtmlHead()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	m_htmlHeadEdit.SetSel(0, -1);
	m_htmlHeadEdit.Copy();
	m_htmlHeadEdit.SetSel(0, 0);

	// ��������
	CFont fnt;
	fnt.CreatePointFont(100, TEXT("����"));
	m_htmlHeadEdit.SetFont(&fnt);
}
