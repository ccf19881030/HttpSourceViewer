#pragma once
#include "afxwin.h"


// CTabHtmlHead �Ի���

class CTabHtmlHead : public CDialog
{
	DECLARE_DYNAMIC(CTabHtmlHead)
	DECLARE_EASYSIZE

public:
	CTabHtmlHead(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CTabHtmlHead();

// �Ի�������
	enum { IDD = IDD_DIALOG_TAB_HTML_HEAD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_htmlHeadEdit;
	afx_msg void OnBnClickedButtonClearHtmlHead();
	afx_msg void OnClickedButtonCopyHtmlHead();
	afx_msg void OnSize(UINT nType, int cx, int cy);
//	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonSaveaHtmlHead();
};
