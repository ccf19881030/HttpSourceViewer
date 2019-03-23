#include "stdafx.h"
#include "XLDownloader.h"

#include "ThirdParty/XLDownLoad/XLDownload.h"
#include "ThirdParty/XLDownLoad/XLError.h"

#pragma  comment(lib, "ThirdParty/XLDownLoad/XLDownload.lib")

#include <list>
using std::list;

XLDownloader::XLDownloader()
{
	// 1、初始化下载引擎
	if (FALSE == XLInitDownloadEngine())
	{
		AfxMessageBox(L"Initialize download engine failed.");
	}
}


XLDownloader::~XLDownloader()
{
	// 5、释放资源
	XLUninitDownloadEngine();
}

//[in] pszUrl，任务URL
//[in] pszFileName，下载保存的文件名
//[in] pszReferUrl，引用页URL
//[in] taskId，任务ID号
LONG XLDownloader::CreateTaskByThunder(wchar_t *pszUrl, wchar_t *pszFileName, wchar_t *pszReferUrl,
	                  LONG taskId)
{
	// 2、启动新任务
	 // PS：如果链接无法通过，请把工程属性“将wchar_t设置为内置类型        (/Zc:wchar_t)”设置为Yes
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

	// 3、查询任务状态
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
			// 输出进度信息
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

	// 4、无论是否下载成功，都必须调用XLStopTask
	XLStopTask(lTaskId);


	return 0;
}
