#pragma once
#include "afxwin.h"
#include "afxcmn.h"

#include <string>
#include <vector>

using std::wstring;
using std::vector;

// CTabHtmlBody 对话框

class CTabHtmlBody : public CDialogEx
{
	DECLARE_DYNAMIC(CTabHtmlBody)
	DECLARE_EASYSIZE

public:
	CTabHtmlBody(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CTabHtmlBody();

// 对话框数据
	enum { IDD = IDD_DIALOG_TAB_HTML_BODY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CRichEditCtrl m_htmlBodyEdit;
	afx_msg void OnBnClickedButtonClearHtmlBody();
	afx_msg void OnBnClickedButtonCopyHtmlBody();
	virtual BOOL OnInitDialog();
	void InitRichEdit();
	// 搜索编辑框控件对象
	CEdit m_searchEdit;
	afx_msg void OnBnClickedButtonSearchText();
	// 在HTML内容中搜索出所需要的文本
	void FindTextInHtml();
	// 为RichEdit中的指定区域文本进行着色处理
	void ColorMarkSearch(int startPos, int endPos);
	// 简单的清除RichEdit的着色样式
	void ClearTextMark();
	// 截获RichEdit的WM_PAINT消息，用于当RichEdit刷新时显示行号
	static long SubEditProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	// 显示RichEdit中的行号
	static void ShowLineNum(HWND hWnd);
	// 正则表达式风格组合框控件变量
	CComboBox m_RegStyleComboBox;
	// 匹配的个数的编辑框控件对象
	CEdit m_matchNumEdit;
	// 在HTML内容中进行搜索
	void SearchInHtmlContent(CString searchText);
	// 初始化正则表达式下拉框
	void InitRegexComBox();
public:
	std::vector<wstring> m_vecMatch;
public:
	afx_msg void OnBnClickedButtonGetMatch();
	// 提取搜索到的内容
	void GetMatchRegExp();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBnClickedButtonSaveHtmlBody();
};
