#include "stdafx.h"


/*************************************************************************
> File Name: myMString.cc
> Author: lukey
> Mail: lukey123@foxmail.com
> Created Time: Wed 17 Jun 2015 09:18:55 PM CST
************************************************************************/

#include<iostream>
#include<cstring>
#include<string.h>
#include<stdlib.h>
#include "MString.h"
#include "MArray.h"
#include "Regexp.h"

#pragma warning (disable: 4996)//All off
//#pragma warning (once: 4996)//shows only one

//using namespace std;


//构造函数
MString::MString()
{
	std::cout << "MString()" << std::endl;
	pstr_ = new xchar[1];//new 已经初始化了
}
MString::MString(const xchar *str)//有参构造函数
{
	std::cout << "MString(const xchar * str)" << std::endl;
	pstr_ = new xchar[xstrlen(str) + 1];
	xstrcpy(pstr_, str);
}
MString::MString(const MString & rhs)    //复制构造，考虑自复制情况？
{
	std::cout << "MString(const MString & rhs)" << std::endl;
	pstr_ = new xchar[xstrlen(rhs.pstr_) + 1];
	xstrcpy(pstr_, rhs.pstr_);
}
MString::~MString()
{
	std::cout << "~MString()" << std::endl;
	delete[]pstr_;
}

MString & MString::operator=(const MString & rhs)//赋值运算符的两种情况,考虑自赋值情况
{
	std::cout << "MString & operator=(const MString & rhs)" << std::endl;
	if (this == &rhs)
		return *this;
	delete[]pstr_;
	pstr_ = new xchar[xstrlen(rhs.pstr_) + 1];
	xstrcpy(pstr_, rhs.pstr_);
	return *this;
}
MString & MString::operator=(const xchar *str)
{
	std::cout << "MString & operator=(const xchar *str)" << std::endl;
	pstr_ = new xchar[xstrlen(str) + 1];
	xstrcpy(pstr_, str);
	return *this;
}

MString & MString::operator+=(const MString & rhs)    //rhs连接到pstr_后面
{
	std::cout << "operator+=(const MString & rhs)" << std::endl;
	int len = (int)xstrlen(rhs.pstr_) + (int)xstrlen(pstr_);
	pstr_ = (xchar *)realloc(pstr_, (len + 1)*sizeof(xchar));
	xstrcat(pstr_, rhs.pstr_);
	return *this;
}
MString & MString::operator+=(const xchar * str)
{
	std::cout << "operator+=(const xchar * str)" << std::endl;
	int len = int(xstrlen(str) + xstrlen(pstr_));
	pstr_ = (xchar *)realloc(pstr_, (len + 1) * sizeof(xchar));
	xstrcat(pstr_, str);
	//_tcscat
	return *this;
}

//下标运算符，非常量，可以修改值
xchar & MString::operator[](int index)
{
	return pstr_[index];
}

//常量对象取下标，不能为其赋值
const xchar & MString::operator[](int index) const
{
	return pstr_[index];
}

//字符串容量
int MString::size() const
{
	return (int)xstrlen(pstr_);
}

//转换成c类型字符串，以'\0'结尾
const xchar* MString::c_str() const
{
	int len = (int)xstrlen(pstr_);

	pstr_[len /*+ 1*/] = '\0';
	return pstr_;
}

//不懂？打印出字符串？
void MString::debug()
{
	std::cout << pstr_ << std::endl;
}

void mstr_match_callback(const xchar * match,          // matching string (not null-terminated)
	const unsigned int length,   // length of matching string
	const MatchState & ms)
{
	if (ms.level > 0)
	{
		for (int i = 0; i < ms.level; i++)
		{
			xchar tmpStr[256] = { 0 };
			memcpy(tmpStr, ms.capture[i].init, ms.capture[i].len * sizeof(xchar));
			//mResults.push_back(tmpStr);
			if ( ms.UserData != nullptr )
			{
				((MArray<MString>*)(ms.UserData))->push(tmpStr);
			}
		}
	}
	else
	{
		xchar tmpStr[256] = { 0 };
		memcpy(tmpStr, match, length * sizeof(xchar));
		//mResults.push_back(tmpStr);
		if (ms.UserData != nullptr)
		{
			((MArray<MString>*)(ms.UserData))->push(tmpStr);
		}
	}

}

MArray<MString>	MString::match(xchar* expression)
{
	MArray<MString> result;
	MatchState state = MatchState(pstr_);
	state.UserData = (void*)&result;
	state.GlobalMatch(expression, &mstr_match_callback);
	return result;
}

MString operator+(const MString & s1, const MString & s2)
{
	std::cout << "operator+(const MString & s1,const MString & s2)" << std::endl;
	MString ret_str = s1.pstr_;
	ret_str += s2.pstr_;
	return ret_str;
}

MString operator+(const MString & s, const xchar * str)
{
	std::cout << "operator+(MString, xchar *)" << std::endl;
	MString temp(str);
	return (s + temp);    //直接调用上面的(+)函数

}

MString operator+(const xchar * str, const MString & s)
{
	std::cout << "operator+( xchar *, MString)" << std::endl;
	MString temp(str);
	return (s + temp);    //直接调用上面的(+)函数
}

bool operator==(const MString & lstr, const MString & rstr)
{
	std::cout << "==" << std::endl;
	if (xstrcmp(lstr.pstr_, rstr.pstr_) == 0)
		return true;
	else
		return false;
}

bool operator!=(const MString & lstr, const MString & rstr)
{
	std::cout << "!=" << std::endl;
	return !(lstr == rstr);
}

bool operator<(const MString & lstr, const MString & rstr)
{
	std::cout << "<" << std::endl;
	if (xstrcmp(lstr.pstr_, rstr.pstr_) < 0)
		return true;
	else
		return false;
}

bool operator>(const MString & lstr, const MString & rstr)
{
	std::cout << ">" << std::endl;
	if (xstrcmp(lstr.pstr_, rstr.pstr_) > 0)
		return true;
	else
		return false;
}
bool operator<=(const MString & lstr, const MString & rstr)
{
	std::cout << "<=" << std::endl;
	if (xstrcmp(lstr.pstr_, rstr.pstr_) <= 0)
		return true;
	else
		return false;
}

bool operator>=(const MString & lstr, const MString & rstr)
{
	std::cout << ">=" << std::endl;
	if (xstrcmp(lstr.pstr_, rstr.pstr_) >= 0)
		return true;
	else
		return false;
}

// #ifdef USE_WCHAR
// std::wostream & operator<<(std::wostream & os, const MString &s)
// {
// 	os << s.pstr_ << " ";
// 	return os;
// }
// std::wistream & operator >> (std::wistream & is, MString & s)
// {
// 	is >> s.pstr_;
// 	return is;        //貌似有坑, 目前不能输入空格
// }
// #else
// std::ostream & operator<<(std::ostream & os, const MString &s)
// {
// 	os << s.pstr_ << " ";
// 	return os;
// }
// std::istream & operator >> (std::istream & is, MString & s)
// {
// 	is >> s.pstr_;
// 	return is;        //貌似有坑, 目前不能输入空格
// }
// #endif // USE_WCHAR

MString & MString::operator+=(const int val)
{
	xchar tmp[256] = { 0 };

	xsprintf(tmp, X("%d"), val);

	return *this += tmp;
}

MString & MString::operator+=(const unsigned int val)
{
	xchar tmp[256] = { 0 };
	xsprintf(tmp, X("%u"), val);
	return *this += tmp;
}

MString & MString::operator+=(const float val)
{
	xchar tmp[256] = { 0 };
	xsprintf(tmp, X("%f"), val);
	return *this += tmp;
}

MString & MString::operator+=(const double val)
{
	xchar tmp[256] = { 0 };
	xsprintf(tmp, X("%f"), val);
	return *this += tmp;
}
#include <stdarg.h>
MString& MString::Printf(xchar* format, ...)
{
	xchar buffer[1024] = { 0 };
	va_list ArgPtr;
	va_start(ArgPtr, format);
	int Length  = /*_vscwprintf*/_xvscprintf(format, ArgPtr) + 1;//gcc没有
	//mWBuffer.resize(Length);
	/*vswprintf_s*/xvsnprintf(&buffer[0], Length, format, ArgPtr);//gcc没有
	va_end(ArgPtr);
	return *this = buffer;

	
}
