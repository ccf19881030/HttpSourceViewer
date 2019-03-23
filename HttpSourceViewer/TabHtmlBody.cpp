// TabHtmlBody.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "HttpSourceViewer.h"
#include "TabHtmlBody.h"
#include "afxdialogex.h"
#include <iostream>
//#include <boost/regex.hpp>
#include "CRegExpContext.h"


// CTabHtmlBody �Ի���

WNDPROC g_lpEditProc;
HWND g_editHwnd;

//typedef regex_iterator<wstring::const_iterator> wsregex_iterator;

IMPLEMENT_DYNAMIC(CTabHtmlBody, CDialogEx)

CTabHtmlBody::CTabHtmlBody(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTabHtmlBody::IDD, pParent)
{

}

CTabHtmlBody::~CTabHtmlBody()
{
}

void CTabHtmlBody::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_RICHEDIT2_HTML_BODY, m_htmlBodyEdit);
	DDX_Control(pDX, IDC_EDIT_SEARCH_TEXT, m_searchEdit);
	DDX_Control(pDX, IDC_COMBO_REG_STYLE, m_RegStyleComboBox);
	DDX_Control(pDX, IDC_EDIT_MATCH_NUMBER, m_matchNumEdit);
}


BEGIN_MESSAGE_MAP(CTabHtmlBody, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR_HTML_BODY, &CTabHtmlBody::OnBnClickedButtonClearHtmlBody)
	ON_BN_CLICKED(IDC_BUTTON_COPY_HTML_BODY, &CTabHtmlBody::OnBnClickedButtonCopyHtmlBody)
	ON_BN_CLICKED(IDC_BUTTON_SEARCH_TEXT, &CTabHtmlBody::OnBnClickedButtonSearchText)
	ON_BN_CLICKED(IDC_BUTTON_GET_MATCH, &CTabHtmlBody::OnBnClickedButtonGetMatch)
	ON_WM_SIZE()
END_MESSAGE_MAP()

BEGIN_EASYSIZE_MAP(CTabHtmlBody)
	EASYSIZE(IDC_EDIT_SEARCH_TEXT, ES_BORDER, ES_BORDER, ES_BORDER, ES_KEEPSIZE, 0)
	EASYSIZE(IDC_BUTTON_SEARCH_TEXT, ES_KEEPSIZE, ES_BORDER, ES_BORDER, ES_KEEPSIZE, 0)
	EASYSIZE(IDC_BUTTON_GET_MATCH, ES_KEEPSIZE, ES_BORDER, ES_BORDER, ES_KEEPSIZE, 0)
	EASYSIZE(IDC_RICHEDIT2_HTML_BODY, ES_BORDER, ES_BORDER, ES_BORDER, ES_BORDER, 0)
END_EASYSIZE_MAP


// CTabHtmlBody ��Ϣ�������


void CTabHtmlBody::OnBnClickedButtonClearHtmlBody()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	m_htmlBodyEdit.SetWindowTextW(TEXT(""));
}


void CTabHtmlBody::OnBnClickedButtonCopyHtmlBody()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	m_htmlBodyEdit.SetSel(0, -1);
	m_htmlBodyEdit.Copy();
	m_htmlBodyEdit.SetSel(0, 0);
}


BOOL CTabHtmlBody::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	// �����ı��������
	InitRichEdit();

	// ��ʼ��������ʽ�������б�
	InitRegexComBox();

	g_editHwnd = m_htmlBodyEdit.GetSafeHwnd();
	// �����µĴ��ڵ�ַ��g_lpEditProc�����ô��ڴ����ַ
	g_lpEditProc = (WNDPROC)::SetWindowLong(g_editHwnd, GWL_WNDPROC, (LONG)&CTabHtmlBody::SubEditProc);

	INIT_EASYSIZE;
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


void CTabHtmlBody::InitRichEdit()
{
	// ��������
	CFont fnt;
	fnt.CreatePointFont(100, TEXT("����"));
	m_htmlBodyEdit.SetFont(&fnt);
	// ��������RichEdit���ڵı༭������������߳���40���ؿ����ʾ�к�
	m_htmlBodyEdit.SendMessage(EM_SETMARGINS, EC_RIGHTMARGIN | EC_LEFTMARGIN, 0x00050005 + 40);
	// ����RichEditΪ���ı��������ƣ�����Ϊ64kb���ı�����
	m_htmlBodyEdit.SendMessage(EM_EXLIMITTEXT, 0, -1);
}


void CTabHtmlBody::OnBnClickedButtonSearchText()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	FindTextInHtml();
}


// ��HTML����������������Ҫ���ı�
void CTabHtmlBody::FindTextInHtml()
{
	// ���ǰһ�ε��ı���ɫ
	ClearTextMark();

	// ��ȡ��Ҫ�������ı�
	CString searchText;
	m_searchEdit.GetWindowText(searchText);
	CString htmlContent;
	m_htmlBodyEdit.GetWindowTextW(htmlContent);

	// �ж��û�ѡ�����ֱ��ʽ
	CRegExpContext::REGEXP_RULE index = (CRegExpContext::REGEXP_RULE)m_RegStyleComboBox.GetItemData(m_RegStyleComboBox.GetCurSel());
	CRegExpContext regExpContext(index);

	// ������ʽ����
	m_vecMatch.clear(); // ÿһ������ǰ����������
	//CRegExpBoost regBoost;
	std::wstring regExp = searchText.GetBuffer();
	std::wstring searchContent = htmlContent.GetBuffer();
	//std::vector<wstring> vecMatch;
	regExpContext.RegExpMatch(regExp, searchContent, m_vecMatch);

	// ��ʾƥ��ĸ���
	size_t matchCount = m_vecMatch.size();
	CString matchCountStr;
	matchCountStr.Format(TEXT("%d"), matchCount);
	m_matchNumEdit.SetWindowTextW(matchCountStr);

	// ��������ƥ������Ȼ����RichEdit�����ƥ�����ݵ���������ɫ
	for (vector<wstring>::iterator it = m_vecMatch.begin(); it != m_vecMatch.end(); ++it)
	{
		CString testStr( (*it).c_str() );
		// ��RichEdit�ı���������Ҫ���ҵ�����
		SearchInHtmlContent(testStr);
	}
}


// ΪRichEdit�е�ָ�������ı�������ɫ����
void CTabHtmlBody::ColorMarkSearch(int startPos, int endPos)
{
	m_htmlBodyEdit.SetSel(startPos, endPos);

	CHARFORMAT2 cf;
	memset(&cf, 0, sizeof(cf));
	cf.cbSize = sizeof(cf);
	cf.dwMask = CFM_BOLD | CFM_COLOR | CFM_BACKCOLOR;
	cf.dwEffects = 1;
	cf.crTextColor = RGB(0, 0, 0);
	cf.crBackColor = RGB(116, 208, 241);

	//m_htmlBodyEdit.SendMessage(EM_SETCHARFORMAT, SCF_SELECTION, (LPARAM)&cf);
	m_htmlBodyEdit.SetSelectionCharFormat(cf);
}


// Ϊ�˼򵥵����RichEdit����ɫ��ʽ
void CTabHtmlBody::ClearTextMark()
{
	CString temp;
	m_htmlBodyEdit.GetWindowText(temp);
	m_htmlBodyEdit.SetWindowTextW(temp);
}


// �ػ�RichEdit��WM_PAINT��Ϣ�����ڵ�RichEditˢ��ʱ��ʾ�к�
long CTabHtmlBody::SubEditProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	//���ܣ��ػ�RichEdit��WM_PAINT��Ϣ�����ڵ�RichEditˢ��ʱ��ʾ�кš�
	//������
	// hWnd, uMsg, wParam, lParam ��Ϊԭ��Windows����RichEdit����Ϣ�Ͳ���
	//����ֵ��û��
	//˵��������Ϣ������Ϻ�������Ϣ���͸�Ĭ�ϵ�RichEdit�Ĵ��ڴ������,
	// lpEditProcΪRichEdit�ľɴ��ڵ�ַ��
	PAINTSTRUCT ps;

	if (uMsg == WM_PAINT)
	{
		::CallWindowProc(g_lpEditProc, hWnd, uMsg, wParam, lParam);
		::BeginPaint(hWnd, &ps);
		//���к��������ʾ�кŵĹ���
		ShowLineNum(g_editHwnd);

		return ::EndPaint(hWnd, &ps);

	}
	return ::CallWindowProc(g_lpEditProc, hWnd, uMsg, wParam, lParam);

}


// ��ʾRichEdit�е��к�
void CTabHtmlBody::ShowLineNum(HWND hWnd)
{
	/*
	���ܣ���ʾ�ı���������
	������
	hWnd��Ҫ��ʾ�кŵ��ı�����ͨ��Edit�ؼ�û�в��Թ�������ֻ��RichEdit

	����ֵ��û�С�
	--------------------------------------------------------------------------------
	*/
	RECT     ClientRect;     //RichEdit�Ŀͻ�����С
	HDC      hdcEdit;         //RichEdit��Dc���豸������
	HDC      hdcCpb;          //��RichEdit���ݵ�Dc
	HBITMAP  hdcBmp;      //RichEdit���ݵ�λͼdc
	int      CharHeight;      //�ַ��ĸ߶�
	int      chHeight;        //�ַ��ĸ߶ȣ�����
	int      FirstLine;       //�ı����еĵ�һ���ɼ��е��кš�
	int      ClientHeight;    //RichEdit�Ŀͻ����߶�
	int      LineCount;       //�ı���������
	wchar_t  countBuf[10];   //��ʾ�кŵĻ�����
	CHARFORMAT     CharFmt;  //RichEdit�е�һ���ṹ�����ڻ�ȡ�ַ���һϵ����Ϣ������ֻ��������ȡ�ַ��߶�

	//��ȡRichEdit��Dc
	hdcEdit = ::GetDC(hWnd);
	::GetClientRect(hWnd, &ClientRect);
	//��ȡRichEdit�Ŀͻ����߶�
	ClientHeight = ClientRect.bottom - ClientRect.top;
	//������RichEdit���ݵ�Dc
	hdcCpb = CreateCompatibleDC(hdcEdit);
	//������RichEdit���ݵ�λͼDc������������ʾ�к��õġ�
	hdcBmp = CreateCompatibleBitmap(hdcEdit, 40, ClientHeight);
	//��λͼdcѡ��RichEdit������
	SelectObject(hdcCpb, hdcBmp);
	//�����ʾ�к�dc�ı�����ɫ����ҿ�������������ɫ
	FillRect(hdcCpb, &ClientRect, CreateSolidBrush(0x8080ff));
	SetBkMode(hdcCpb, TRANSPARENT);
	//��ȡ��ǰRichEdit�ı��е�������
	LineCount = ::SendMessage(hWnd, EM_GETLINECOUNT, 0, 0);

	RtlZeroMemory(&CharFmt, sizeof(CharFmt));
	CharFmt.cbSize = sizeof(CharFmt);
	::SendMessage(hWnd, EM_GETCHARFORMAT, TRUE, (long)&CharFmt);
	//��ȡ�ַ��߶ȣ���Ӣ��Ϊ��λ����ת��Ϊ����
	CharHeight = CharFmt.yHeight / 15;
	chHeight = CharHeight;
	CharHeight = 2;
	//������ʾ�кŵ�ǰ��ɫ
	::SetTextColor(hdcCpb, 0x000000);
	//��ȡ�ı����е�һ���ɼ����е��кţ�û������кţ���ʾ��������ı��Ĺ�����������
	FirstLine = ::SendMessage(hWnd, EM_GETFIRSTVISIBLELINE, 0, 0);
	FirstLine++;
	//��λͼdc��ѭ������к�
	while (FirstLine <= LineCount)
	{
		::TextOut(hdcCpb, 1, CharHeight, countBuf, wsprintf(countBuf, TEXT("%4u"), FirstLine++));
		CharHeight += chHeight + 3;
		if (CharHeight > ClientHeight) break;
	}
	//����"����"��λͼ����"��"��RichEdit��
	::BitBlt(hdcEdit, 0, 0, 40, ClientHeight, hdcCpb, 0, 0, SRCCOPY);
	::DeleteDC(hdcCpb);
	::ReleaseDC(hWnd, hdcEdit);
	::DeleteObject(hdcBmp);
}


//***********************************************
//�������ߣ�ccf19881030 2019/03/17/03/17 16:04:44
//�������ܣ���HTML�����н�������
//����˵����
// ������  searchText����Ҫ���ҵ�html����
// ����ֵ��void
//ע�����
//***********************************************
void CTabHtmlBody::SearchInHtmlContent(CString searchText)
{
	FINDTEXTEX ft;
	// ���������Χ
	ft.chrg.cpMin = 0;
	ft.chrg.cpMax = -1;
	ft.lpstrText = searchText.GetBuffer();
	long lPos = -1;
	int strLen = searchText.GetLength();
	do
	{
		lPos = m_htmlBodyEdit.FindTextW(FR_DOWN | FR_WHOLEWORD, &ft);
		if (-1 == lPos)
		{
			break;
		}
		m_htmlBodyEdit.SetSel(lPos, lPos + strLen);
		//CString strText = m_htmlBodyEdit.GetSelText();
		//AfxMessageBox(strText);
		// ��ѡ�е��ı�������ɫ
		ColorMarkSearch(lPos, lPos + strLen);
		ft.chrg.cpMin = lPos + strLen;
	} while (true);
}

//***********************************************
//�������ߣ�ccf19881030 2019/03/18/03/18 20:27:40
//�������ܣ���ʼ��������ʽ�������б�
//����˵����
// ������
// ����ֵ��
//ע�����
//***********************************************
void CTabHtmlBody::InitRegexComBox()
{
	int index = 0;
	m_RegStyleComboBox.InsertString(index, TEXT("Boost"));
	m_RegStyleComboBox.SetItemData(index++, CRegExpContext::USE_BOOST_REGEXP);
	m_RegStyleComboBox.InsertString(index, TEXT("ATL"));
	m_RegStyleComboBox.SetItemData(index++, CRegExpContext::USE_ATL_REGEXP);
	m_RegStyleComboBox.SetCurSel(0);
}


void CTabHtmlBody::OnBnClickedButtonGetMatch()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	GetMatchRegExp();
}

//***********************************************
//�������ߣ�ccf19881030 2019/03/21/03/21 19:36:22
//�������ܣ�
//����˵����
// ������
// ����ֵ��
//ע�����
//***********************************************
// ��ȡ������������
void CTabHtmlBody::GetMatchRegExp()
{
	// TODO: �ڴ˴����ʵ�ִ���.
	// �����Ի�������Ϣ�������ȡƥ�������
	AfxGetMainWnd()->SendMessage(WM_COMMAND, ID_MAIN_GETMATCH, 0);
}


void CTabHtmlBody::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
	UPDATE_EASYSIZE;
}
