#pragma once

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

/******************************************
*** @作者：            ccf19881030
*** @修改日期：        2019-03-20
*** @类的功能描述:     正则表达式的策略接口类
********************************************/
class CRegExpStrategyInterface
{
public:
	CRegExpStrategyInterface();
	virtual ~CRegExpStrategyInterface(void);

	//regExp为正则表达式,searchText为需要搜索的文本,results为用于存放匹配的结果数组
	virtual bool RegExpMatch(const wstring& regExp, const wstring& searchText,
		vector<wstring>& results) = 0;
};

