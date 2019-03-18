#pragma once

#include <string>
#include <vector>
using namespace std;

class CRegExpStrategyInterface
{
public:
	CRegExpStrategyInterface();
	virtual ~CRegExpStrategyInterface(void);

	virtual bool RegExpMatch(const wstring& regExp, const wstring& searchText,
		vector<wstring>& results) = 0;
};

