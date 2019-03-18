
// HttpSourceViewerDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "TabHtmlHead.h"
#include "TabHtmlBody.h"
#include "TabHtmlGet.h"
#include "ThirdParty/ATLRegExp/WinHttpClient.h"

// CHttpSourceViewerDlg �Ի���
class CHttpSourceViewerDlg : public CDialogEx
{
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
	afx_msg void OnBnClickedButton1();
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
};
