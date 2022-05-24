#pragma once

#include <string>
#include <cstring>

class Lexer {
public:
	enum token_t {
		TOKEN_END = 0,
		TOKEN_ADD,
		TOKEN_SUB,
		TOKEN_MUL,
		TOKEN_DIV,
		TOKEN_NUMBER,
		TOKEN_ANOTHER
	};

	Lexer(const char* s) :
		_content(s)
	{
		_start = _cursor = _content;
		_limit = _content + strlen(_content);
	}

	token_t scan() {
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

		 	[ ]+ 		{ return TOKEN_ANOTHER; }
		 	[0-9]+		{ return TOKEN_NUMBER; }
		 	"+"			{ return TOKEN_ADD; }
		 	"-"			{ return TOKEN_SUB; }
		 	"*"			{ return TOKEN_MUL; }
		 	"/"			{ return TOKEN_DIV; }
		 	$			{ return TOKEN_END; }
		 */
	}

	std::string getTokenValue() const  {
		return std::string(_start, _cursor-_start);
	}

	int get() const {
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
