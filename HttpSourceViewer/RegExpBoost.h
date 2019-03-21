#pragma once
#include "RegExpstrategyinterface.h"

// 使用策略模式(将算法抽离出来)
// Boost正则表达式类
class CRegExpBoost : 
	public CRegExpStrategyInterface
{
public:
	CRegExpBoost();
	virtual ~CRegExpBoost(void);
	virtual bool RegExpMatch(const wstring& regExp, const wstring& searchText, vector<wstring>& results);
};

