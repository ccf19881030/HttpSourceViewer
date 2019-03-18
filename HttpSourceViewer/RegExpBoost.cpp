#include "stdafx.h"
#include "RegExpBoost.h"
#include <boost/xpressive/xpressive.hpp>

//#pragma warning(disable : 4996)

using namespace boost::xpressive;

CRegExpBoost::CRegExpBoost()
{
}


CRegExpBoost::~CRegExpBoost(void)
{
}

//***********************************************
//程序作者：ccf19881030 2019/03/18/03/18 20:49:47
//函数功能：使用boost库中的xpressive正则表达式搜索
//参数说明：
// 参数：
// 返回值：
//注意事项：
//***********************************************
bool CRegExpBoost::RegExpMatch(const wstring& regExp, const wstring& searchText, vector<wstring>& results)
{
	//using namespace boost::xpressive;

	try
	{
		// 参考资料：Boost xpressive 正则表达式
		//https://blog.csdn.net/freehyan/article/details/51583551
		wsregex reg = wsregex::compile(regExp.c_str(), regExp.size(), boost::xpressive::icase);
		
		// 构造函数传入分词区间和正则表达式对象,之后可以反复调用operator++，使用*或者->获取匹配的结果match_results对象
		// https://docs.microsoft.com/zh-cn/previous-versions/bb982177(v=vs.120)
		wsregex_iterator pos(searchText.begin(), searchText.end(), reg);
		wsregex_iterator rend;
		while (pos != rend)
		{
			results.push_back( (*pos)[0] );  //operator*返回一个match_results对象
			++pos;
		}

		return true;
	}
	catch (...)
	{
		return false;
	}
}