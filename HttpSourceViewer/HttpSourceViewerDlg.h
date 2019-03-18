
// HttpSourceViewerDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "TabHtmlHead.h"
#include "TabHtmlBody.h"
#include "TabHtmlGet.h"
#include "ThirdParty/ATLRegExp/WinHttpClient.h"

// CHttpSourceViewerDlg 对话框
class CHttpSourceViewerDlg : public CDialogEx
{
// 构造
public:
	CHttpSourceViewerDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_HTTPSOURCEVIEWER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	CEdit m_urlEdit;
	afx_msg void OnBnClickedButtonPaste();
	afx_msg void OnBnClickedButtonClear();
	// 主窗口的Tab标签页
	CTabCtrl m_mainTab;
	void InitTabControl();

	// 作为Tab控件的标签页使用
	CTabHtmlHead m_tabHtmlHead;
	CTabHtmlBody m_tabHtmlBody;
	CTabHtmlGet m_tabHtmlGet;
	// 移动每个Tab页面到合适的位置
	void MoveSubTab();
//	afx_msg void OnSelchangeTabMain(NMHDR *pNMHDR, LRESULT *pResult);
	CProgressCtrl m_htmlReqProgress;
	afx_msg void OnTcnSelchangeTabMain(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonGo();
	// 获取URL地址，然后请求服务，返回HTML头和内容
	bool ProcessHttpRequest();
public:
	static bool HtmlRequestProgress(double progress);
	static CHttpSourceViewerDlg* m_pThis;
};
