// TestRegexp.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Regexp.h"
#include <locale.h>
#include "RegexpWrapper.h"

#include "MString.h"

// called for each match
void match_callback(const xchar * match,          // matching string (not null-terminated)
	const unsigned int length,   // length of matching string
	const MatchState & ms)      // MatchState in use (to get captures)
{
	xchar cap[10];   // must be large enough to hold captures

	xprintf(match);
	xprintf(X("\n"));


}  // end of match_callback 

void printResult(const xchar* exp, std::vector<xstring>& result)
{
	xprintf(X("============================================\n"));
	xprintf(exp);
	xprintf(X("\n"));
	for (int i = 0; i < result.size(); i ++)
	{
		xprintf(result[i].c_str());
		xprintf(X("\n"));
	}
}

void Test1()
{
// 	RegexpWrapper reg("abcefgkbkaaa");
// 	std::vector<std::string> result = reg.GlobalMatch("b..");
// 	printResult("b..", result);
// 
// 	RegexpWrapper reg1("foo 123 bar 45678");
// 	result = reg1.GlobalMatch("%d%d%d");
// 	printResult("%%d%%d%%d", result);
// 
// 	RegexpWrapper reg2("Hello World!!!");
// 	result = reg2.GlobalMatch("%u");
// 	printResult("%%u", result);
// 
// 	result = reg.match("abcd", "[bc][bc]");
// 	printResult("test", result);
// 
// 	result = reg.match("abcd", "[^ad]");//^not a and d
// 	printResult("test", result);
// 
// 	result = reg.match("123bcd234", "[0-9]");
// 	printResult("test", result);
// 	result = reg.match("123bcd234", "[0-9][0-9][0-9]");
// 	printResult("test", result);
// 
// 
// 	result = reg.match("examples", "examples?");
// 	printResult("test", result);
// 	result = reg.match("example", "examples?");
// 	printResult("test", result);
// 	result = reg.match("example", "examples");
// 	printResult("test", result);
// 
// 	//这里唯一不一样，括号内匹配到的，不是按照数组分开来了
// 	result = reg.match("foo: 123 bar: 456", "(%a+):%s*(%d+)%s+(%a+):%s*(%d+)");// %a: letter %s : whitespace
// 	printResult("test", result);


}

void Test2()
{
	RegexpWrapper reg(X("abcefgkbkaaa"));
	std::vector<xstring> result = reg.GlobalMatch(X("b.."));
	printResult(X("b.."), result);

	RegexpWrapper reg1(X("foo 123 bar 45678"));
	result = reg1.GlobalMatch(X("%d%d%d"));
	printResult(X("%%d%%d%%d"), result);

	RegexpWrapper reg2(X("Hello World!!!"));
	result = reg2.GlobalMatch(X("%u"));
	printResult(X("%%u"), result);

	result = reg.match(X("abcd"), X("[bc][bc]"));
	printResult(X("test"), result);

	result = reg.match(X("abcd"), X("[^ad]"));//^not a and d
	printResult(X("test"), result);

	result = reg.match(X("123bcd234"), X("[0-9]"));
	printResult(X("test"), result);
	result = reg.match(X("123bcd234"), X("[0-9][0-9][0-9]"));
	printResult(X("test"), result);


	result = reg.match(X("examples"), X("examples?"));
	printResult(X("test"), result);
	result = reg.match(X("example"), X("examples?"));
	printResult(X("test"), result);
	result = reg.match(X("example"), X("examples"));
	printResult(X("test"), result);

	//这里唯一不一样，括号内匹配到的，不是按照数组分开来了
	result = reg.match(X("foo: 123 bar: 456"), X("(%a+):%s*(%d+)%s+(%a+):%s*(%d+)"));// %a: letter %s : whitespace
	printResult(X("test"), result);


	result = reg.match(X("我爱正则表达式"),X("爱.."));
	printResult(X("爱.."), result);
}

void test3()
{
	MString str = X("abcefgkbkaaa");
	MArray<MString> ret = str.match(X("b..."));

	for ( int i = 0; i < ret.size(); i ++ )
	{
		xprintf(ret[i].c_str());
		xprintf(X("\n"));
	}

}

int main()
{
	setlocale(LC_ALL, "chs");
	xchar buf[100] = X("The quick brown fox jumps over the lazy wolf");

	// match state object
	MatchState ms(buf);

	// search for three letters followed by a space (two captures)
	int count = ms.GlobalMatch(X("(%a+)( )"), match_callback);
	xprintf(X("count:%d\n"), count);
	
	Test2();
	test3();

	getchar();

    return 0;
}

