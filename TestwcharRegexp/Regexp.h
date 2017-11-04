#pragma once
/*
 
 Regular-expression matching library for Arduino.
 
 Written by Nick Gammon.
 Date: 30 April 2011
 
 Heavily based on the Lua regular expression matching library written by Roberto Ierusalimschy. 
 
 Adapted to run on the Arduino by Nick Gammon.
 
 
 VERSION
 
  Version 1.0  - 30th April 2011 : initial release.
  Version 1.1  - 1st May 2011    : added some helper functions, made more modular.
  Version 1.2  - 19th May 2011   : added more helper functions for replacing etc.


 */

#include "MString.h"
// Maximum of captures we can return. 
// Increase if you need more, decrease to save memory.
#define MAXCAPTURES 32

// the "magic escape" character 
#define REGEXP_ESC		'%'

// special characters that have to be escaped
// (not used in the library, but you might need this)
#define REGEXP_SPECIALS	"^$*+?.([%-"

// Result codes from calling regexp:

// we got a match
#define REGEXP_MATCHED 1    

// no match, or not attempted to match yet
#define REGEXP_NOMATCH 0    

// errors when matching
#define ERR_INVALID_CAPTURE_INDEX -1
#define ERR_INVALID_PATTERN_CAPTURE -2
#define ERR_MALFORMED_PATTERN_ENDS_WITH_ESCAPE -3
#define ERR_MALFORMED_PATTERN_ENDS_WITH_RH_SQUARE_BRACKET -4
#define ERR_UNBALANCED_PATTERN -5
#define ERR_TOO_MANY_CAPTURES -6
#define ERR_MISSING_LH_SQUARE_BRACKET_AFTER_ESC_F -7
#define ERR_NO_TARGET_STRING -8


/* macro to `unsign' a character */
#define uchar(c)        ((unsigned xchar)(c))

// special capture "lengths"
#define CAP_UNFINISHED	(-1)
#define CAP_POSITION	(-2)

class MatchState;  // forward definition for the callback routines

typedef void (*GlobalMatchCallback)   (const xchar * match,          // matching string (not null-terminated)
                                       const unsigned int length,   // length of matching string
                                       const MatchState & ms);      // MatchState in use (to get captures)
typedef void (*GlobalReplaceCallback) (const xchar * match,          // matching string (not null-terminated)
                                       const unsigned int length,   // length of matching string
                                       xchar * & replacement,
                                       unsigned int & replacement_length,
                                       const MatchState & ms);      // MatchState in use (to get captures)
typedef class MatchState {
private:
  
  xchar result;  // result of last Match call
  
public:
  
  MatchState () : result (REGEXP_NOMATCH), src (0) {};  // constructor
  MatchState (xchar * s) : result (REGEXP_NOMATCH) 
    { Target (s); };  // constructor from null-terminated string
  MatchState (xchar * s, const unsigned int len) : result (REGEXP_NOMATCH) 
    { Target (s, len); };  // constructor from string and length
  
  // supply these two:
  xchar *src;  /* source string */
  unsigned int src_len;    /* length of source string */

  // used internally  
  xchar *src_end;  /* end of source string */
 
  // returned fields:
  
  unsigned int MatchStart;    // zero-relative offset of start of match
  unsigned int MatchLength;   // length of match
  
  int level;  /* total number of captures in array below (finished or unfinished) */
  
  // capture addresses and lengths
  struct {
    const xchar *init;
    int len;              // might be CAP_UNFINISHED or CAP_POSITION
  } capture[MAXCAPTURES];
  
  // add target string, null-terminated
  void Target (xchar * s);
  // add target string, with specified length
  void Target (xchar * s, const unsigned int len);
  // do a match on a supplied pattern and zero-relative starting point
  xchar Match (const xchar * pattern, unsigned int index = 0);
  // return the matching string
  xchar * GetMatch (xchar * s) const;
  // return capture string n
  xchar * GetCapture (xchar * s, const int n) const;
  // get result of previous match
  xchar GetResult () const { return result; }

  // count number of matches on a supplied pattern
  unsigned int MatchCount (const xchar * pattern);
  // iterate with a supplied pattern, call function f for each match
  // returns count of matches
  unsigned int GlobalMatch (const xchar * pattern, GlobalMatchCallback f);
  // iterate with a supplied pattern, call function f for each match, maximum of max_count matches if max_count > 0
  // returns count of replacements
  unsigned int GlobalReplace (const xchar * pattern, GlobalReplaceCallback f, const unsigned int max_count = 0);
  // iterate with a supplied pattern, replaces with replacement string, maximum of max_count matches if max_count > 0
  // returns count of replacements
  unsigned int GlobalReplace (const xchar * pattern, xchar * replacement, const unsigned int max_count = 0);
  
} MatchState;
