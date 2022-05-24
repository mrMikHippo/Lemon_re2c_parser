#pragma once

#include <string>
#include <cstring>
#include "../parser/parser.h"
#include "lexer.def.h"

class Lexer {
public:

	Lexer(const char* s) :
		_content(s)
	{
		_start = _cursor = _content;
		_limit = _content + strlen(_content);
	}

	int scan(YYSTYPE& yylval) {
		for (;;) {
			_start = _cursor;

			/*!re2c
				re2c:define:YYCTYPE		= char;
				re2c:define:YYCURSOR 	= _cursor;
				re2c:define:YYLIMIT 	= _limit;
				re2c:define:YYMARKER 	= _marker;
				re2c:define:YYCTXMARKER = _ctxmarker;
			 	re2c:indent:top			= 1;
			 	re2c:yyfill:enable		= 0;
				re2c:eof				= 0;
			 	
			 	D = [0-9];
			 	INT = D+;
			 	FLOAT = D* "." D+;

			 	INT			{
			 				  yylval.kind = TOKEN_INT;
			 				  yylval.int_value = atoi(this->getTokenValue().c_str()); 
			 				  return yylval.kind; 
			 				}
			 	FLOAT		{
			 				  yylval.kind = TOKEN_FLOAT;
			 				  yylval.float_value = atof(this->getTokenValue().c_str());
			 				  return yylval.kind;
			 				}
			 	"+"			{ return TOKEN_PLUS; }
			 	"-"			{ return TOKEN_MINUS; }
			 	"*"			{ return TOKEN_MULTIPLY; }
			 	"/"			{ return TOKEN_DIVIDE; }
				[ ]+		{ continue; }
				"exit"		{ return -1; }
				$			{ return 0; }
			 */
		}
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
