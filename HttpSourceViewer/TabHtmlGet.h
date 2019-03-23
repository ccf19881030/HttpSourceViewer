#pragma once
#include "afxwin.h"


// CTabHtmlGet 对话框

class CTabHtmlGet : public CDialogEx
{
	DECLARE_DYNAMIC(CTabHtmlGet)
	DECLARE_EASYSIZE

public:
	CTabHtmlGet(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CTabHtmlGet();

// 对话框数据
	enum { IDD = IDD_DIALOG_TAB_HTML_GET };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_htmlGetEdit;
	afx_msg void OnBnClickedButtonClearHtmlBody();
	afx_msg void OnBnClickedButtonCopyHtmlBody();
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
};
