#pragma once

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

/******************************************
*** @���ߣ�            ccf19881030
*** @�޸����ڣ�        2019-03-20
*** @��Ĺ�������:     ������ʽ�Ĳ��Խӿ���
********************************************/
class CRegExpStrategyInterface
{
public:
	CRegExpStrategyInterface();
	virtual ~CRegExpStrategyInterface(void);

	//regExpΪ������ʽ,searchTextΪ��Ҫ�������ı�,resultsΪ���ڴ��ƥ��Ľ������
	virtual bool RegExpMatch(const wstring& regExp, const wstring& searchText,
		vector<wstring>& results) = 0;
};

