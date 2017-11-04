#pragma once
#include "Regexp.h"
#include <string>
#include <vector>

#ifdef USE_WCHAR
#define xstring std::wstring
#else
#define xstring std::string
#endif

class RegexpWrapper
{
public:
	RegexpWrapper(xchar* s);
	~RegexpWrapper();

	std::vector<xstring> GlobalMatch(const xchar* expression);

	std::vector<xstring> match(xchar* s, const xchar* expression);

	 static void match_callback(const xchar * match,          // matching string (not null-terminated)
		const unsigned int length,   // length of matching string
		const MatchState & ms);    // MatchState in use (to get captures)

	 

private:

	static std::vector<xstring> mResults;

	MatchState mState;
};

