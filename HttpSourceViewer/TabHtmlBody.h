#pragma once
#include "afxwin.h"
#include "afxcmn.h"

#include <string>
#include <vector>

using std::wstring;
using std::vector;

// CTabHtmlBody �Ի���

class CTabHtmlBody : public CDialogEx
{
	DECLARE_DYNAMIC(CTabHtmlBody)
	DECLARE_EASYSIZE

public:
	CTabHtmlBody(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CTabHtmlBody();

// �Ի�������
	enum { IDD = IDD_DIALOG_TAB_HTML_BODY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CRichEditCtrl m_htmlBodyEdit;
	afx_msg void OnBnClickedButtonClearHtmlBody();
	afx_msg void OnBnClickedButtonCopyHtmlBody();
	virtual BOOL OnInitDialog();
	void InitRichEdit();
	// �����༭��ؼ�����
	CEdit m_searchEdit;
	afx_msg void OnBnClickedButtonSearchText();
	// ��HTML����������������Ҫ���ı�
	void FindTextInHtml();
	// ΪRichEdit�е�ָ�������ı�������ɫ����
	void ColorMarkSearch(int startPos, int endPos);
	// �򵥵����RichEdit����ɫ��ʽ
	void ClearTextMark();
	// �ػ�RichEdit��WM_PAINT��Ϣ�����ڵ�RichEditˢ��ʱ��ʾ�к�
	static long SubEditProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	// ��ʾRichEdit�е��к�
	static void ShowLineNum(HWND hWnd);
	// ������ʽ�����Ͽ�ؼ�����
	CComboBox m_RegStyleComboBox;
	// ƥ��ĸ����ı༭��ؼ�����
	CEdit m_matchNumEdit;
	// ��HTML�����н�������
	void SearchInHtmlContent(CString searchText);
	// ��ʼ��������ʽ������
	void InitRegexComBox();
public:
	std::vector<wstring> m_vecMatch;
public:
	afx_msg void OnBnClickedButtonGetMatch();
	// ��ȡ������������
	void GetMatchRegExp();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBnClickedButtonSaveHtmlBody();
};
