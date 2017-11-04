// TestString.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <Locale.h>
#include <ctype.h>
#include "MString.h"

int main()
{
	setlocale(LC_ALL, "chs");

	MString str = X("ÖÐÎÄhello");
	str += 100;
	str += X(" data:");
	str += 123;

	str.Printf(X("Êý×Ö£º%d %f"), 100, 1.2f);
	
	xprintf(X("str:%s"), str.c_str());

	wchar_t wc = 'A';
	char cc = '%';

	int a = islower(wc);
	xprintf(X("islower:%d\n"), a);

	getchar();
    return 0;
}

