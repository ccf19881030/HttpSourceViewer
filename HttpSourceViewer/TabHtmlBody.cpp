// TabHtmlBody.cpp : 实现文件
//

#include "stdafx.h"
#include "HttpSourceViewer.h"
#include "TabHtmlBody.h"
#include "afxdialogex.h"
#include <iostream>
//#include <boost/regex.hpp>
#include "CRegExpContext.h"


// CTabHtmlBody 对话框

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


// CTabHtmlBody 消息处理程序


void CTabHtmlBody::OnBnClickedButtonClearHtmlBody()
{
	// TODO:  在此添加控件通知处理程序代码
	m_htmlBodyEdit.SetWindowTextW(TEXT(""));
}


void CTabHtmlBody::OnBnClickedButtonCopyHtmlBody()
{
	// TODO:  在此添加控件通知处理程序代码
	m_htmlBodyEdit.SetSel(0, -1);
	m_htmlBodyEdit.Copy();
	m_htmlBodyEdit.SetSel(0, 0);
}


BOOL CTabHtmlBody::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	// 设置文本框的字体
	InitRichEdit();

	// 初始化正则表达式下拉框列表
	InitRegexComBox();

	g_editHwnd = m_htmlBodyEdit.GetSafeHwnd();
	// 设置新的窗口地址，g_lpEditProc的内置窗口处理地址
	g_lpEditProc = (WNDPROC)::SetWindowLong(g_editHwnd, GWL_WNDPROC, (LONG)&CTabHtmlBody::SubEditProc);

	INIT_EASYSIZE;
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


void CTabHtmlBody::InitRichEdit()
{
	// 设置字体
	CFont fnt;
	fnt.CreatePointFont(100, TEXT("黑体"));
	m_htmlBodyEdit.SetFont(&fnt);
	// 这里设置RichEdit窗口的编辑区域，我们在左边超出40像素宽度显示行号
	m_htmlBodyEdit.SendMessage(EM_SETMARGINS, EC_RIGHTMARGIN | EC_LEFTMARGIN, 0x00050005 + 40);
	// 设置RichEdit为无文本长度限制，否则为64kb的文本长度
	m_htmlBodyEdit.SendMessage(EM_EXLIMITTEXT, 0, -1);
}


void CTabHtmlBody::OnBnClickedButtonSearchText()
{
	// TODO:  在此添加控件通知处理程序代码
	FindTextInHtml();
}


// 在HTML内容中搜索出所需要的文本
void CTabHtmlBody::FindTextInHtml()
{
	// 清除前一次的文本着色
	ClearTextMark();

	// 获取需要搜索的文本
	CString searchText;
	m_searchEdit.GetWindowText(searchText);
	CString htmlContent;
	m_htmlBodyEdit.GetWindowTextW(htmlContent);

	// 判断用户选择哪种表达式
	CRegExpContext::REGEXP_RULE index = (CRegExpContext::REGEXP_RULE)m_RegStyleComboBox.GetItemData(m_RegStyleComboBox.GetCurSel());
	CRegExpContext regExpContext(index);

	// 正则表达式搜索
	m_vecMatch.clear(); // 每一次搜索前清除结果数组
	//CRegExpBoost regBoost;
	std::wstring regExp = searchText.GetBuffer();
	std::wstring searchContent = htmlContent.GetBuffer();
	//std::vector<wstring> vecMatch;
	regExpContext.RegExpMatch(regExp, searchContent, m_vecMatch);

	// 显示匹配的个数
	size_t matchCount = m_vecMatch.size();
	CString matchCountStr;
	matchCountStr.Format(TEXT("%d"), matchCount);
	m_matchNumEdit.SetWindowTextW(matchCountStr);

	// 遍历所有匹配结果，然后在RichEdit里进行匹配内容的搜索和着色
	for (vector<wstring>::iterator it = m_vecMatch.begin(); it != m_vecMatch.end(); ++it)
	{
		CString testStr( (*it).c_str() );
		// 在RichEdit文本中搜索需要查找的内容
		SearchInHtmlContent(testStr);
	}
}


// 为RichEdit中的指定区域文本进行着色处理
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


// 为了简单的清除RichEdit的着色样式
void CTabHtmlBody::ClearTextMark()
{
	CString temp;
	m_htmlBodyEdit.GetWindowText(temp);
	m_htmlBodyEdit.SetWindowTextW(temp);
}


// 截获RichEdit的WM_PAINT消息，用于当RichEdit刷新时显示行号
long CTabHtmlBody::SubEditProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	//功能：截获RichEdit的WM_PAINT消息，用于当RichEdit刷新时显示行号。
	//参数：
	// hWnd, uMsg, wParam, lParam 都为原有Windows发给RichEdit的消息和参数
	//返回值：没有
	//说明：当消息处理完毕后必须把消息回送给默认的RichEdit的窗口处理过程,
	// lpEditProc为RichEdit的旧窗口地址。
	PAINTSTRUCT ps;

	if (uMsg == WM_PAINT)
	{
		::CallWindowProc(g_lpEditProc, hWnd, uMsg, wParam, lParam);
		::BeginPaint(hWnd, &ps);
		//下列函数完成显示行号的功能
		ShowLineNum(g_editHwnd);

		return ::EndPaint(hWnd, &ps);

	}
	return ::CallWindowProc(g_lpEditProc, hWnd, uMsg, wParam, lParam);

}


// 显示RichEdit中的行号
void CTabHtmlBody::ShowLineNum(HWND hWnd)
{
	/*
	功能：显示文本的总行数
	参数：
	hWnd：要显示行号的文本框，普通的Edit控件没有测试过，这里只用RichEdit

	返回值：没有。
	--------------------------------------------------------------------------------
	*/
	RECT     ClientRect;     //RichEdit的客户区大小
	HDC      hdcEdit;         //RichEdit的Dc（设备环境）
	HDC      hdcCpb;          //与RichEdit兼容的Dc
	HBITMAP  hdcBmp;      //RichEdit兼容的位图dc
	int      CharHeight;      //字符的高度
	int      chHeight;        //字符的高度，常量
	int      FirstLine;       //文本框中的第一个可见行的行号。
	int      ClientHeight;    //RichEdit的客户区高度
	int      LineCount;       //文本的总行数
	wchar_t  countBuf[10];   //显示行号的缓冲区
	CHARFORMAT     CharFmt;  //RichEdit中的一个结构，用于获取字符的一系列信息，这里只用它来获取字符高度

	//获取RichEdit的Dc
	hdcEdit = ::GetDC(hWnd);
	::GetClientRect(hWnd, &ClientRect);
	//获取RichEdit的客户区高度
	ClientHeight = ClientRect.bottom - ClientRect.top;
	//创建与RichEdit兼容的Dc
	hdcCpb = CreateCompatibleDC(hdcEdit);
	//创建与RichEdit兼容的位图Dc，我们用来显示行号用的。
	hdcBmp = CreateCompatibleBitmap(hdcEdit, 40, ClientHeight);
	//将位图dc选入RichEdit环境中
	SelectObject(hdcCpb, hdcBmp);
	//填充显示行号dc的背景颜色。大家可以试试其它颜色
	FillRect(hdcCpb, &ClientRect, CreateSolidBrush(0x8080ff));
	SetBkMode(hdcCpb, TRANSPARENT);
	//获取当前RichEdit文本中的总行数
	LineCount = ::SendMessage(hWnd, EM_GETLINECOUNT, 0, 0);

	RtlZeroMemory(&CharFmt, sizeof(CharFmt));
	CharFmt.cbSize = sizeof(CharFmt);
	::SendMessage(hWnd, EM_GETCHARFORMAT, TRUE, (long)&CharFmt);
	//获取字符高度，以英寸为单位，需转化为磅。
	CharHeight = CharFmt.yHeight / 15;
	chHeight = CharHeight;
	CharHeight = 2;
	//设置显示行号的前景色
	::SetTextColor(hdcCpb, 0x000000);
	//获取文本框中第一个可见的行的行号，没有这个行号，显示不会跟着文本的滚动而滚动。
	FirstLine = ::SendMessage(hWnd, EM_GETFIRSTVISIBLELINE, 0, 0);
	FirstLine++;
	//在位图dc中循环输出行号
	while (FirstLine <= LineCount)
	{
		::TextOut(hdcCpb, 1, CharHeight, countBuf, wsprintf(countBuf, TEXT("%4u"), FirstLine++));
		CharHeight += chHeight + 3;
		if (CharHeight > ClientHeight) break;
	}
	//将已"画好"的位图真正"贴"到RichEdit中
	::BitBlt(hdcEdit, 0, 0, 40, ClientHeight, hdcCpb, 0, 0, SRCCOPY);
	::DeleteDC(hdcCpb);
	::ReleaseDC(hWnd, hdcEdit);
	::DeleteObject(hdcBmp);
}


//***********************************************
//程序作者：ccf19881030 2019/03/17/03/17 16:04:44
//函数功能：在HTML内容中进行搜索
//参数说明：
// 参数：  searchText，需要查找的html内容
// 返回值：void
//注意事项：
//***********************************************
void CTabHtmlBody::SearchInHtmlContent(CString searchText)
{
	FINDTEXTEX ft;
	// 标记搜索范围
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
		// 对选中的文本进行着色
		ColorMarkSearch(lPos, lPos + strLen);
		ft.chrg.cpMin = lPos + strLen;
	} while (true);
}

//***********************************************
//程序作者：ccf19881030 2019/03/18/03/18 20:27:40
//函数功能：初始化正则表达式下拉框列表
//参数说明：
// 参数：
// 返回值：
//注意事项：
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
	// TODO: 在此添加控件通知处理程序代码
	GetMatchRegExp();
}

//***********************************************
//程序作者：ccf19881030 2019/03/21/03/21 19:36:22
//函数功能：
//参数说明：
// 参数：
// 返回值：
//注意事项：
//***********************************************
// 提取搜索到的内容
void CTabHtmlBody::GetMatchRegExp()
{
	// TODO: 在此处添加实现代码.
	// 向主对话框发送消息，让其获取匹配的内容
	AfxGetMainWnd()->SendMessage(WM_COMMAND, ID_MAIN_GETMATCH, 0);
}


void CTabHtmlBody::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	UPDATE_EASYSIZE;
}
