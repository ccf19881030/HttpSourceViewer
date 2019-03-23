// TabHtmlGet.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "HttpSourceViewer.h"
#include "TabHtmlGet.h"
#include "afxdialogex.h"
#include "CFileProcess.h"

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
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BUTTON_SAVE_HTML_GET, &CTabHtmlGet::OnBnClickedButtonSaveHtmlGet)
	ON_BN_CLICKED(IDC_BUTTON_OPEN_DOWNLOAD, &CTabHtmlGet::OnBnClickedButtonOpenDownload)
END_MESSAGE_MAP()

BEGIN_EASYSIZE_MAP(CTabHtmlGet)
	EASYSIZE(IDC_EDIT_HTML_GET, ES_BORDER, ES_BORDER, ES_BORDER, ES_BORDER, 0)
END_EASYSIZE_MAP


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


BOOL CTabHtmlGet::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	INIT_EASYSIZE;

	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}


void CTabHtmlGet::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
	UPDATE_EASYSIZE;
}


void CTabHtmlGet::OnBnClickedButtonSaveHtmlGet()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString content;
	m_htmlGetEdit.GetWindowTextW(content);

	CFileProcess::SaveFile(content);
}


void CTabHtmlGet::OnBnClickedButtonOpenDownload()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	AfxGetMainWnd()->SendMessage(WM_COMMAND, ID_MAIN_DOWNLOAD, 0);
}

