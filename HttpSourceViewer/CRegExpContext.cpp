#include "stdafx.h"
#include "CRegExpContext.h"


CRegExpContext::CRegExpContext()
{
}


CRegExpContext::~CRegExpContext()
{
	if (m_pRegExpStrategy != nullptr)
	{
		delete m_pRegExpStrategy;
		m_pRegExpStrategy = nullptr;
	}
}

CRegExpContext::CRegExpContext(REGEXP_RULE regTpye)
{
	switch (regTpye)
	{
	case USE_BOOST_REGEXP:
		m_pRegExpStrategy = new CRegExpBoost();
		break;
	case USE_ATL_REGEXP:
		m_pRegExpStrategy = new CRegExpATL();
	default:
		break;
	}
}

bool CRegExpContext::RegExpMatch(const wstring& regExp, const wstring& searchText, vector<wstring>& results)
{
	if (m_pRegExpStrategy != nullptr)
	{
		if (m_pRegExpStrategy->RegExpMatch(regExp, searchText, results))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	return false;
}
