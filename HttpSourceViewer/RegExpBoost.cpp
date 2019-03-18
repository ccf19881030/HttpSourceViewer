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
//�������ߣ�ccf19881030 2019/03/18/03/18 20:49:47
//�������ܣ�ʹ��boost���е�xpressive������ʽ����
//����˵����
// ������
// ����ֵ��
//ע�����
//***********************************************
bool CRegExpBoost::RegExpMatch(const wstring& regExp, const wstring& searchText, vector<wstring>& results)
{
	//using namespace boost::xpressive;

	try
	{
		// �ο����ϣ�Boost xpressive ������ʽ
		//https://blog.csdn.net/freehyan/article/details/51583551
		wsregex reg = wsregex::compile(regExp.c_str(), regExp.size(), boost::xpressive::icase);
		
		// ���캯������ִ������������ʽ����,֮����Է�������operator++��ʹ��*����->��ȡƥ��Ľ��match_results����
		// https://docs.microsoft.com/zh-cn/previous-versions/bb982177(v=vs.120)
		wsregex_iterator pos(searchText.begin(), searchText.end(), reg);
		wsregex_iterator rend;
		while (pos != rend)
		{
			results.push_back( (*pos)[0] );  //operator*����һ��match_results����
			++pos;
		}

		return true;
	}
	catch (...)
	{
		return false;
	}
}