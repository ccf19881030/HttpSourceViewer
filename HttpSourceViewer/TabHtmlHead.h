#pragma once
#include "afxwin.h"


// CTabHtmlHead �Ի���

class CTabHtmlHead : public CDialog
{
	DECLARE_DYNAMIC(CTabHtmlHead)

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
};
