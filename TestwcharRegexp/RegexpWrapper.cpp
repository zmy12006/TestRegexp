#include "RegexpWrapper.h"

#ifdef USE_WCHAR
std::vector<std::wstring> RegexpWrapper::mResults;
#else
std::vector<std::string> RegexpWrapper::mResults;
#endif // USE_WCHAR



RegexpWrapper::RegexpWrapper(xchar* s)
{
	mState = MatchState(s);
}


RegexpWrapper::~RegexpWrapper()
{
}

void RegexpWrapper::match_callback(const xchar * match,          // matching string (not null-terminated)
	const unsigned int length,   // length of matching string
	const MatchState & ms)
{
	if ( ms.level > 0 )
	{
		for ( int i = 0; i < ms.level; i ++ )
		{
			xchar tmpStr[256] = { 0 };
			memcpy(tmpStr, ms.capture[i].init, ms.capture[i].len * sizeof(xchar));
			mResults.push_back(tmpStr);
		}
	}
	else
	{
		xchar tmpStr[256] = {0};
		memcpy(tmpStr, match, length * sizeof(xchar));
		mResults.push_back(tmpStr);

	}

}

std::vector<xstring> RegexpWrapper::GlobalMatch(const xchar* expression)
{
	mResults.clear();
	mState.GlobalMatch(expression, &RegexpWrapper::match_callback);
// 	for ( int i = 0; i < mState.level; i ++ )
// 	{
// 		xchar tmpStr[256] = { 0 };
// 		mState.GetCapture(tmpStr, i);
// 		mResults.push_back(tmpStr);
// 	}
	return mResults;
}

std::vector<xstring> RegexpWrapper::match(xchar* s, const xchar* expression)
{
	mResults.clear();
	mState.Target(s);
	mState.GlobalMatch(expression, &RegexpWrapper::match_callback);
	return mResults;
}

/*

6.4.1 ¨C Patterns

Patterns in Lua are described by regular strings, which are interpreted as patterns by the pattern-matching functions string.find, string.gmatch, string.gsub, and string.match. This section describes the syntax and the meaning (that is, what they match) of these strings.

Character Class:

A character class is used to represent a set of characters. The following combinations are allowed in describing a character class:

x: (where x is not one of the magic characters ^$()%.[]*+-?) represents the character x itself.
.: (a dot) represents all characters.
%a: represents all letters.
%c: represents all control characters.
%d: represents all digits.
%g: represents all printable characters except space.
%l: represents all lowercase letters.
%p: represents all punctuation characters.
%s: represents all space characters.
%u: represents all uppercase letters.
%w: represents all alphanumeric characters.
%x: represents all hexadecimal digits.
%x: (where x is any non-alphanumeric character) represents the character x. This is the standard way to escape the magic characters. Any non-alphanumeric character (including all punctuation characters, even the non-magical) can be preceded by a '%' when used to represent itself in a pattern.
[set]: represents the class which is the union of all characters in set. A range of characters can be specified by separating the end characters of the range, in ascending order, with a '-'. All classes %x described above can also be used as components in set. All other characters in set represent themselves. For example, [%w_] (or [_%w]) represents all alphanumeric characters plus the underscore, [0-7] represents the octal digits, and [0-7%l%-] represents the octal digits plus the lowercase letters plus the '-' character.
You can put a closing square bracket in a set by positioning it as the first character in the set. You can put an hyphen in a set by positioning it as the first or the last character in the set. (You can also use an escape for both cases.)

The interaction between ranges and classes is not defined. Therefore, patterns like [%a-z] or [a-%%] have no meaning.

[^set]: represents the complement of set, where set is interpreted as above.
For all classes represented by single letters (%a, %c, etc.), the corresponding uppercase letter represents the complement of the class. For instance, %S represents all non-space characters.

The definitions of letter, space, and other character groups depend on the current locale. In particular, the class [a-z] may not be equivalent to %l.

Pattern Item:

A pattern item can be

a single character class, which matches any single character in the class;
a single character class followed by '*', which matches zero or more repetitions of characters in the class. These repetition items will always match the longest possible sequence;
a single character class followed by '+', which matches one or more repetitions of characters in the class. These repetition items will always match the longest possible sequence;
a single character class followed by '-', which also matches zero or more repetitions of characters in the class. Unlike '*', these repetition items will always match the shortest possible sequence;
a single character class followed by '?', which matches zero or one occurrence of a character in the class. It always matches one occurrence if possible;
%n, for n between 1 and 9; such item matches a substring equal to the n-th captured string (see below);
%bxy, where x and y are two distinct characters; such item matches strings that start with x, end with y, and where the x and y are balanced. This means that, if one reads the string from left to right, counting +1 for an x and -1 for a y, the ending y is the first y where the count reaches 0. For instance, the item %b() matches expressions with balanced parentheses.
%f[set], a frontier pattern; such item matches an empty string at any position such that the next character belongs to set and the previous character does not belong to set. The set set is interpreted as previously described. The beginning and the end of the subject are handled as if they were the character '\0'.
Pattern:

A pattern is a sequence of pattern items. A caret '^' at the beginning of a pattern anchors the match at the beginning of the subject string. A '$' at the end of a pattern anchors the match at the end of the subject string. At other positions, '^' and '$' have no special meaning and represent themselves.

Captures:

A pattern can contain sub-patterns enclosed in parentheses; they describe captures. When a match succeeds, the substrings of the subject string that match captures are stored (captured) for future use. Captures are numbered according to their left parentheses. For instance, in the pattern "(a*(.)%w(%s*))", the part of the string matching "a*(.)%w(%s*)" is stored as the first capture (and therefore has number 1); the character matching "." is captured with number 2, and the part matching "%s*" has number 3.

As a special case, the empty capture () captures the current string position (a number). For instance, if we apply the pattern "()aa()" on the string "flaaap", there will be two captures: 3 and 5.

6.4.2 ¨C Format Strings for Pack and Unpack

The first argument to string.pack, string.packsize, and string.unpack is a format string, which describes the layout of the structure being created or read.

A format string is a sequence of conversion options. The conversion options are as follows:

<: sets little endian
>: sets big endian
=: sets native endian
![n]: sets maximum alignment to n (default is native alignment)
b: a signed byte (xchar)
B: an unsigned byte (xchar)
h: a signed short (native size)
H: an unsigned short (native size)
l: a signed long (native size)
L: an unsigned long (native size)
j: a lua_Integer
J: a lua_Unsigned
T: a size_t (native size)
i[n]: a signed int with n bytes (default is native size)
I[n]: an unsigned int with n bytes (default is native size)
f: a float (native size)
d: a double (native size)
n: a lua_Number
cn: a fixed-sized string with n bytes
z: a zero-terminated string
s[n]: a string preceded by its length coded as an unsigned integer with n bytes (default is a size_t)
x: one byte of padding
Xop: an empty item that aligns according to option op (which is otherwise ignored)
' ': (empty space) ignored
(A "[n]" means an optional integral numeral.) Except for padding, spaces, and configurations (options "xX <=>!"), each option corresponds to an argument (in string.pack) or a result (in string.unpack).

For options "!n", "sn", "in", and "In", n can be any integer between 1 and 16. All integral options check overflows; string.pack checks whether the given value fits in the given size; string.unpack checks whether the read value fits in a Lua integer.

Any format string starts as if prefixed by "!1=", that is, with maximum alignment of 1 (no alignment) and native endianness.

Alignment works as follows: For each option, the format gets extra padding until the data starts at an offset that is a multiple of the minimum between the option size and the maximum alignment; this minimum must be a power of 2. Options "c" and "z" are not aligned; option "s" follows the alignment of its starting integer.

All padding is filled with zeros by string.pack (and ignored by string.unpack).


*/

