#pragma once
#include "Regexp.h"
#include <string>
#include <vector>



class RegexpWrapper
{
public:
	RegexpWrapper(char* s);
	~RegexpWrapper();

	std::vector<std::string> GlobalMatch(const char* expression);

	std::vector<std::string> match(char* s, const char* expression);

	 static void match_callback(const char * match,          // matching string (not null-terminated)
		const unsigned int length,   // length of matching string
		const MatchState & ms);    // MatchState in use (to get captures)

	 

private:
	static std::vector<std::string> mResults;
	MatchState mState;
};

