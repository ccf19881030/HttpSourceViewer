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
		L"�ı��ļ�(*.txt)|*.txt|html�ļ�(*.html)|*.html|�����ļ�(*.*)|*.*|", NULL); // �ļ�����Ի����ʼ��
	if ( IDOK == saveDlg.DoModal() )
	{
		UINT openFlag = CFile::modeWrite | CFile::shareDenyNone | CFile::modeCreate;
		CFile file;
		BOOL isOK = file.Open(saveDlg.GetPathName(), openFlag);
		if (isOK)
		{
			// �ı�����*2����ΪRichEditʹ����Unicode�汾
			file.Write(fileContent.GetBuffer(), fileContent.GetLength() * 2);
			file.Close();
		}
		else
		{
			AfxMessageBox(L"�����ļ�ʧ�ܣ�");
		}
	}
}