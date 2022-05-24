#pragma once

#include <string>
#include <cstring>
#include "../parser/parser.h"

class Lexer {
public:

	Lexer(const char* s) :
		_content(s)
	{
		_start = _cursor = _content;
		_limit = _content + strlen(_content);
	}

	int scan() {
	std:
		_start = _cursor;

		#define YYCTYPE char
		#define YYCURSOR _cursor
		#define YYLIMIT _limit
		#define YYMARKER _marker
		#define YYCTXMARKER _ctxmarker

		/*!re2c
		 	re2c:indent:top		= 1;
		 	re2c:yyfill:enable	= 0;
			re2c:eof			= 0;

		 	[0-9]+		{ return TOKEN_INT; }
		 	"+"			{ return TOKEN_PLUS; }
		 	"-"			{ return TOKEN_MINUS; }
		 	"*"			{ return TOKEN_MULTIPLY; }
		 	"/"			{ return TOKEN_DIVIDE; }
			$			{ return 0; }
			[ ]+		{ goto std; }
		 */
	}

	std::string getTokenValue() const  {
		return std::string(_start, _cursor-_start);
	}

	int getLength() const {
		return strlen(_content);
	}

private:
	const char* _content;
	const char* _start;
	const char* _cursor;
	const char* _limit;
	const char* _marker;
	const char* _ctxmarker;
};
