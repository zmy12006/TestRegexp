// TestString.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <Locale.h>
#include <ctype.h>
#include "MString.h"

int main()
{
	setlocale(LC_ALL, "chs");

	MString str = X("中文hello");
	str += 100;
	str += X(" data:");
	str += 123;

	str.Printf(X("数字：%d %f"), 100, 1.2f);
	
	xprintf(X("str:%s"), str.c_str());

	wchar_t wc = 'A';
	char cc = '%';

	int a = islower(wc);
	xprintf(X("islower:%d\n"), a);

	int val1 = 0;
	wchar_t char1 = 'A';
	wchar_t warr[10] = { 0 };
	char	carr[10] = { 0 };
	int val2 = 0;
	wchar_t char2 = 'B';

	int* pVal1 = &val1;
	int* pVal2 = &val2;
	wchar_t* pChar1 = &char1;
	wchar_t* pChar2 = &char2;

	wchar_t* pWarr1 = &warr[2];
	wchar_t* pWarr2 = &warr[5];

	char* pCarr1 = &(carr[1]);
	char* pCarr2 = &(carr[2]);

	printf("pVal1:%I64u pVal2:%I64u sub:%I64u\n", pVal1, pVal2, pVal2 - pVal1);
	printf("pChar1:%I64u pChar2:%I64u sub:%I64u\n", pChar1, pChar2, pChar2 - pChar1);
	printf("pWarr1:%I64u pWarr2:%I64u sub:%I64u\n", pWarr1, pWarr2, pWarr2 - pWarr1);//这个差值是3，无论数组与非数组，差值不是地址数值，而是跟指针类型有关

	getchar();
    return 0;
}

