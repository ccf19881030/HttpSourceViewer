#pragma once

#include "RegExpStrategyInterface.h"
#include "CRegExpATL.h"
#include "RegExpBoost.h"

class CRegExpContext
{
public:
	typedef enum {
		USE_BOOST_REGEXP,
		USE_ATL_REGEXP,
	}REGEXP_RULE;
public:
	CRegExpContext();

	CRegExpContext(REGEXP_RULE reg);
	~CRegExpContext();

	bool RegExpMatch(const wstring& regExp, const wstring& searchText, vector<wstring>& results);

private:
	CRegExpStrategyInterface *m_pRegExpStrategy;
};

