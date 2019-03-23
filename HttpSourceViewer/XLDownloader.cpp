#include "stdafx.h"
#include "XLDownloader.h"

#include "ThirdParty/XLDownLoad/XLDownload.h"
#include "ThirdParty/XLDownLoad/XLError.h"

#pragma  comment(lib, "ThirdParty/XLDownLoad/XLDownload.lib")

#include <list>
using std::list;

XLDownloader::XLDownloader()
{
	// 1����ʼ����������
	if (FALSE == XLInitDownloadEngine())
	{
		AfxMessageBox(L"Initialize download engine failed.");
	}
}


XLDownloader::~XLDownloader()
{
	// 5���ͷ���Դ
	XLUninitDownloadEngine();
}

//[in] pszUrl������URL
//[in] pszFileName�����ر�����ļ���
//[in] pszReferUrl������ҳURL
//[in] taskId������ID��
LONG XLDownloader::CreateTaskByThunder(wchar_t *pszUrl, wchar_t *pszFileName, wchar_t *pszReferUrl,
	                  LONG taskId)
{
	// 2������������
	 // PS����������޷�ͨ������ѹ������ԡ���wchar_t����Ϊ��������        (/Zc:wchar_t)������ΪYes
	LONG   lTaskId = 0;

	DWORD  dwRet = XLURLDownloadToFile(pszUrl, pszFileName, pszReferUrl, lTaskId);

	if (XL_SUCCESS != dwRet)
	{
		XLUninitDownloadEngine();
		CString strMes;
		strMes.Format(L"Create new task failed, error code:%d.", dwRet);
		AfxMessageBox(strMes);
		return 1;
	}

	AfxMessageBox(L"Begin download file.");

	// 3����ѯ����״̬
	do
	{
		::Sleep(1000);

		ULONGLONG   ullFileSize = 0;
		ULONGLONG   ullRecvSize = 0;
		LONG        lStatus = -1;
		CString strMsg;

		dwRet = XLQueryTaskInfo(lTaskId, &lStatus, &ullFileSize, &ullRecvSize);
		if (XL_SUCCESS == dwRet)
		{
			// ���������Ϣ
			if (0 != ullFileSize)
			{
				double  douProgress = (double)ullRecvSize / (double)ullFileSize;
				douProgress *= 100.0;
				strMsg.Format(L"Download progress:%.2f%%", douProgress);
				AfxMessageBox(strMsg);
			}
			else
			{
				AfxMessageBox(L"File size is zero.");
			}

			if (enumTaskStatus_Success == lStatus)
			{
				AfxMessageBox(L"Download successfully.");
				break;
			}

			if (enumTaskStatus_Fail == lStatus)
			{
				AfxMessageBox(L"Download failed.");
				break;
			}
		}
	} while (XL_SUCCESS == dwRet);

	// 4�������Ƿ����سɹ������������XLStopTask
	XLStopTask(lTaskId);


	return 0;
}
