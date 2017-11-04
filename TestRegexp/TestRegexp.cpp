// TestRegexp.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Regexp.h"

#include "RegexpWrapper.h"

// called for each match
void match_callback(const char * match,          // matching string (not null-terminated)
	const unsigned int length,   // length of matching string
	const MatchState & ms)      // MatchState in use (to get captures)
{
	char cap[10];   // must be large enough to hold captures

	printf(match);
	printf("\n");



}  // end of match_callback 

void printResult(const char* exp, std::vector<std::string>& result)
{
	printf("============================================\n");
	printf(exp);
	printf("\n");
	for (int i = 0; i < result.size(); i ++)
	{
		printf(result[i].c_str());
		printf("\n");
	}
}

void Test1()
{
	RegexpWrapper reg("abcefgkbkaaa");
	std::vector<std::string> result = reg.GlobalMatch("b..");
	printResult("b..", result);

	RegexpWrapper reg1("foo 123 bar 45678");
	result = reg1.GlobalMatch("%d%d%d");
	printResult("%%d%%d%%d", result);

	RegexpWrapper reg2("Hello World!!!");
	result = reg2.GlobalMatch("%u");
	printResult("%%u", result);

	result = reg.match("abcd", "[bc][bc]");
	printResult("test", result);

	result = reg.match("abcd", "[^ad]");//^not a and d
	printResult("test", result);

	result = reg.match("123bcd234", "[0-9]");
	printResult("test", result);
	result = reg.match("123bcd234", "[0-9][0-9][0-9]");
	printResult("test", result);


	result = reg.match("examples", "examples?");
	printResult("test", result);
	result = reg.match("example", "examples?");
	printResult("test", result);
	result = reg.match("example", "examples");
	printResult("test", result);

	//����Ψһ��һ����������ƥ�䵽�ģ����ǰ�������ֿ�����
	result = reg.match("foo: 123 bar: 456", "(%a+):%s*(%d+)%s+(%a+):%s*(%d+)");// %a: letter %s : whitespace
	printResult("test", result);


}

int main()
{
	char buf[100] = "The quick brown fox jumps over the lazy wolf";

	// match state object
	MatchState ms(buf);

	// search for three letters followed by a space (two captures)
	int count = ms.GlobalMatch("(%a+)( )", match_callback);
	printf("count:%d\n", count);

	Test1();

	getchar();

    return 0;
}

