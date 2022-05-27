#pragma once

#include <string>
#include <cstring>
#include "../parser/parser.h"
// #include "lexer.def.h"
#include "../token.h"

#define TOKEN_EOF 0
#define TOKEN_PRINT 150

class Lexer {
public:

	Lexer(const char* s) :
		_content(s)
	{
		_start = _cursor = _content;
		_limit = _content + strlen(_content);
	}

	Token* scan() {
		for (;;) {
			_start = _cursor;

			// D = [0-9];
		    // L = [A-Za-z_];
    		// ID = (L)(L|D)*
			// INT			{ 	return create_int_token(this->getTokenValue()); }
			 	// "Integer"	{	return create_lex_integer_token(this->getTokenValue()); }
			 	// "quit"		{	return create_token(TOKEN_EOF); }
			 	// "q"			{	return create_token(TOKEN_EOF); }
			 	// L+			{	return create_name_token(this->getTokenValue()); }
			 	// [A-Za-z_0-9]*	{	return create_id_token(this->getTokenValue()); }

			/*!re2c
				re2c:define:YYCTYPE		= char;
				re2c:define:YYCURSOR 	= _cursor;
				re2c:define:YYLIMIT 	= _limit;
				re2c:define:YYMARKER 	= _marker;
				re2c:define:YYCTXMARKER = _ctxmarker;
			 	re2c:yyfill:enable		= 0;
				re2c:eof				= 0;
			 	
			 	D = [0-9];
			 	INT = D+;
			 	FLOAT = D* "." D+;
			 	L = [A-Za-z_];
			 	ID = (L)(L|D)*;
			 	LL = [A-Za-z_];
			 	
			 	"quit"		{	return create_token(TOKEN_EOF); }
			 	"print"		{	return create_token(TOKEN_PRINT); }
			 	D+			{	return create_int_token(this->getTokenValue()); }
			 	(L)(L|D)*	{	return create_id_token(this->getTokenValue()); }
			 	"="			{	return create_token(TOKEN_ASSIGN); }
			 	";"			{	return create_token(TOKEN_SEMICOLON); }
			 	[^]			{   continue; }
				$			{ 	return nullptr; }
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
