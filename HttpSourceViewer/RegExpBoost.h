#pragma once
#include "RegExpstrategyinterface.h"

// ʹ�ò���ģʽ(���㷨�������)
// Boost������ʽ��
class CRegExpBoost : 
	public CRegExpStrategyInterface
{
public:
	CRegExpBoost();
	virtual ~CRegExpBoost(void);
	virtual bool RegExpMatch(const wstring& regExp, const wstring& searchText, vector<wstring>& results);
};

