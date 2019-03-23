#include "stdafx.h"
#include "CFileProcess.h"


CFileProcess::CFileProcess()
{
}


CFileProcess::~CFileProcess()
{
}

void CFileProcess::SaveFile(CString &fileContent)
{
	CFileDialog saveDlg(FALSE, L"txt", L"html_content.txt", OFN_HIDEREADONLY,
		L"文本文件(*.txt)|*.txt|html文件(*.html)|*.html|所有文件(*.*)|*.*|", NULL); // 文件保存对话框初始化
	if ( IDOK == saveDlg.DoModal() )
	{
		UINT openFlag = CFile::modeWrite | CFile::shareDenyNone | CFile::modeCreate;
		CFile file;
		BOOL isOK = file.Open(saveDlg.GetPathName(), openFlag);
		if (isOK)
		{
			// 文本长度*2是因为RichEdit使用了Unicode版本
			file.Write(fileContent.GetBuffer(), fileContent.GetLength() * 2);
			file.Close();
		}
		else
		{
			AfxMessageBox(L"创建文件失败！");
		}
	}
}