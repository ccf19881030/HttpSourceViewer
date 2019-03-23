#pragma once

#include <windows.h>
#include <tchar.h>
#include <vector>
#include <string>

using std::vector;
using std::wstring;

class XLDownloader
{
public:
	XLDownloader();
	~XLDownloader();

public:
	LONG CreateTaskByThunder(wchar_t *pszUrl, wchar_t *pszFileName, wchar_t *pszReferUrl,
		LONG taskId);

private:
	std::vector<wstring> m_vec;
	LONG m_taskId;
};