#pragma once
#include "RegExpStrategyInterface.h"
class CRegExpATL :
	public CRegExpStrategyInterface
{
public:
	CRegExpATL();
	virtual ~CRegExpATL();

	virtual bool RegExpMatch(const wstring& regExp, const wstring& searchText, vector<wstring>& results);
};

