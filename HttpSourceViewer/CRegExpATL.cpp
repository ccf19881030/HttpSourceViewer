#include "stdafx.h"
#include "CRegExpATL.h"

#include <string>
#include <vector>

#include <atlrx.h>

using namespace std;

// ATL中使用正则表达式: https://www.xuebuyuan.com/756122.html
// ATL正则表达式库使用: http://www.cnblogs.com/zdxster/archive/2011/01/27/1945893.html
// ATL正则表达式库使用: https://blog.csdn.net/blueln/article/details/7853391
// AtlServer: https://archive.codeplex.com/?p=AtlServer

CRegExpATL::CRegExpATL()
{
}


CRegExpATL::~CRegExpATL()
{
}

/*
 * Parameters
 *  [in] regExp: Value of type string which is the input regular expression.
 *  [in] searchText: Value of type string reference which is the source to parse.
 *  [out] results: Value of type vecotr of strings which is the output of the parse.
 * Return Value
 *  Returns true if the function succeeds, or false otherwise.
 *
 * Remarks
 *  The output result is devided into groups.  User should get the groups according to the group count.  For example:
 *  1. RegExp = L"{ab}", searchText = L"abcabe", then results = L"ab", L"ab".
 *  2. RegExp = L"{ab}{cd}", searchText = L"abcdeabecd", then results = L"ab", L"cd", L"ab", L"cd".
*/

// 参考代码见：https://github.com/ccf19881030/HttpSourceViewer/blob/master/HttpSourceViewer/HttpSourceViewer/ThirdParty/ATLRegExp/RegExp.h
// 下面的代码需要修改
bool CRegExpATL::RegExpMatch(const wstring& regExp, const wstring& searchText, vector<wstring>& results)
{
	results.clear();
	if (regExp.size() <= 0)
	{
		return false;
	}

	if (searchText.size() <= 0)
	{
		return false;
	}

	bool bRet = false;
	CAtlRegExp<> regex;
	REParseError status = regex.Parse(regExp.c_str());

	if (REPARSE_ERROR_OK != status)
	{
		return false;
	}
	
		CAtlREMatchContext<> mc;
		const CAtlRegExp<>::RECHAR* pCon = searchText.c_str();
		std::vector<wstring> record;
		wchar_t *pSource = new wchar_t[searchText.size() + 1];
		wchar_t *pSourceEnd = pSource + searchText.size();
		if (pSource == NULL)
		{
			return false;
		}
		wcscpy_s(pSource, searchText.size() + 1, searchText.c_str());
		BOOL bSucceed = TRUE;
		const wchar_t *pFrom = pSource;
		const wchar_t *pTo = NULL;
		while (bSucceed)
		{
			bSucceed = regex.Match(pFrom, &mc, &pTo);
			if (bSucceed)
			{
				const wchar_t *pStart = NULL;
				const wchar_t *pEnd = NULL;
				vector<wstring> tempMatch;
				for (UINT nGroupIndex = 0; nGroupIndex < mc.m_uNumGroups; ++nGroupIndex)
				{
					mc.GetMatch(nGroupIndex, &pStart, &pEnd);
					if (pStart != NULL && pEnd != NULL)
					{
						wstring match(pStart, pEnd - pStart);
						tempMatch.push_back(match);
					}
					else
					{
						break;
					}
				}
				bool bAdd = true;
					// Check whether this match already exists in the vector.
					for (vector<wstring>::iterator it = results.begin(); it != results.end();)
					{
						bool bEqual = true;
						for (vector<wstring>::iterator tempMatchIt = tempMatch.begin(); tempMatchIt != tempMatch.end(); tempMatchIt++, it++)
						{
							bool bGroupEqual = true;
							if (true)
							{
								bGroupEqual = (wcscmp(it->c_str(), tempMatchIt->c_str()) == 0);
							}
							else
							{
								bGroupEqual = (_wcsicmp(it->c_str(), tempMatchIt->c_str()) == 0);
							}
							if (!bGroupEqual)
							{
								bEqual = false;
							}
						}
						if (bEqual)
						{
							bAdd = false;
							break;
						}
					}
				if (bAdd)
				{
					for (vector<wstring>::iterator tempMatchIt = tempMatch.begin(); tempMatchIt != tempMatch.end(); tempMatchIt++)
					{
						results.push_back(*tempMatchIt);
					}
				}
				if (pTo < pSourceEnd)
				{
					pFrom = pTo;
				}
				else
				{
					break;
				}
			}
			else
			{
				break;
			}
		}

		delete[] pSource;

		//return true;

	return results.size() != 0;
}
