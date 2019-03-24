
// HttpSourceViewerDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "TabHtmlHead.h"
#include "TabHtmlBody.h"
#include "TabHtmlGet.h"
#include "ThirdParty/ATLRegExp/WinHttpClient.h"    // http���ӵİ�װ��

// CHttpSourceViewerDlg �Ի���
class CHttpSourceViewerDlg : public CDialogEx
{
DECLARE_EASYSIZE
// ����
public:
	CHttpSourceViewerDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_HTTPSOURCEVIEWER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CEdit m_urlEdit;
	afx_msg void OnBnClickedButtonPaste();
	afx_msg void OnBnClickedButtonClear();
	// �����ڵ�Tab��ǩҳ
	CTabCtrl m_mainTab;
	void InitTabControl();

	// ��ΪTab�ؼ��ı�ǩҳʹ��
	CTabHtmlHead m_tabHtmlHead;
	CTabHtmlBody m_tabHtmlBody;
	CTabHtmlGet m_tabHtmlGet;
	// �ƶ�ÿ��Tabҳ�浽���ʵ�λ��
	void MoveSubTab();
//	afx_msg void OnSelchangeTabMain(NMHDR *pNMHDR, LRESULT *pResult);
	CProgressCtrl m_htmlReqProgress;
	afx_msg void OnTcnSelchangeTabMain(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonGo();
	// ��ȡURL��ַ��Ȼ��������񣬷���HTMLͷ������
	bool ProcessHttpRequest();
public:
	static bool HtmlRequestProgress(double progress);
	static CHttpSourceViewerDlg* m_pThis;
	afx_msg void OnMainGetmatch();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSizing(UINT fwSide, LPRECT pRect);
	// ����Ѹ������
	afx_msg void OnMainDownload();
	// �����ö�checkBox��Ӧ��Button�ؼ�// �����ö�checkBox��Ӧ��Button�ؼ�
//	CButton m_topMostButton;
	afx_msg void OnClickedCheckTopmostWindow();
	// �������ڶ�Ӧ�Ŀؼ���ť
	CButton m_floatOnWinButton;
	afx_msg void OnClickedCheckFloatOnwindow();
	CButton m_topMostButton;
};
