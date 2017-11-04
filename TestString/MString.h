
#ifndef __MYMString__
#define __MYMString__

//#define USE_WCHAR

#ifdef USE_WCHAR
#define xchar wchar_t
//#define xstrlen wcslen

#ifdef USE_WCHAR
#define X(S) L##S
#else
#define X(S) S
#endif // USE_WCHAR



#   define xstrcmp	    wcscmp
#   define xstrncmp	    wcsncmp
#   define xstrlen	    wcslen
#   define xstrcpy	    wcscpy
#   define xstrncpy	    wcsncpy
#   define xstrcat	    wcscat
#   define xstrstr	    wcsstr
#   define xstrchr	    wcschr
#   define xstrcasecmp	    wcscasecmp
#   define xstricmp	    wcsicmp
#   define xstrncasecmp    wcsncasecmp
#   define xstrnicmp	    wcsnicmp
#   define xsprintf	    swprintf
#   define xsnprintf	    snwprintf
#   define xvsprintf	    vswprintf
#	define _xvscprintf		_vscwprintf
#   define xvsnprintf	    vswprintf

#else
#define xchar char
#define X

#   define xstrcmp	    strcmp
#   define xstrncmp	    strncmp
#   define xstrlen	    strlen
#   define xstrcpy	    strcpy
#   define xstrncpy	    strncpy
#   define xstrcat	    strcat
#   define xstrstr	    strstr
#   define xstrchr	    strchr
#   define xstrcasecmp	    strcasecmp
#   define xstricmp	    stricmp
#   define xstrncasecmp    strncasecmp
#   define xstrnicmp	    strnicmp
#   define xsprintf	    sprintf
#   define xsnprintf	    snprintf
#   define xvsprintf	    vsprintf
#	define _xvscprintf		_vscprintf
#   define xvsnprintf	    vsnprintf

#endif // USE_WCHAR



class MString
{
public:
	MString();
	MString(const xchar *);//有参构造函数
	MString(const MString & rhs);    //复制构造
	~MString();

	MString & operator=(const MString & rhs);//赋值运算符的两种情况
	MString & operator=(const xchar *str);

	MString & operator+=(const MString & rhs);
	MString & operator+=(const xchar * str);

	xchar & operator[](int index);
	const xchar & operator[](int index) const;

	int size() const;
	const xchar* c_str() const;
	void debug();

	//MString 类和char相加的几个情况
	friend MString operator+(const MString & s1, const MString & s2);
	friend MString operator+(const MString &, const xchar *);
	friend MString operator+(const xchar *, const MString &);

	friend bool operator==(const MString &, const MString &);
	friend bool operator!=(const MString &, const MString &);

	friend bool operator<(const MString &, const MString &);
	friend bool operator>(const MString &, const MString &);
	friend bool operator<=(const MString &, const MString &);
	friend bool operator>=(const MString &, const MString &);

// #ifdef USE_WCHAR
// 	friend std::wostream & operator<<(std::wostream & os, const MString &s);
// 	friend std::wistream & operator >> (std::wistream & is, MString & s);
// #else
// 	friend std::ostream & operator<<(std::ostream & os, const MString &s);
// 	friend std::istream & operator >> (std::istream & is, MString & s);
// #endif

//============for digital data...............
	MString & operator+=(const int val);
	MString & operator+=(const unsigned int val);
	MString & operator+=(const float val);
	MString & operator+=(const double val);

	MString& Printf(xchar* format, ...);

private:
	xchar *pstr_;
};

#endif