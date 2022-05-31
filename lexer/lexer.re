#pragma once

#include <string>
#include <cstring>
#include "../parser/parser.h"
// #include "lexer.def.h"
#include "../ast.h"

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
			 	
			 	D+			{	return create_token(TOKEN_LITERAL, this->getTokenValue()); }
			 	(L)(L|D)*	{	return create_token(TOKEN_ID, this->getTokenValue()); }
			 	"+"			{	return create_token(TOKEN_PLUS, this->getTokenValue()); }
			 	"-"			{	return create_token(TOKEN_MINUS, this->getTokenValue()); }
			 	"*"			{	return create_token(TOKEN_MUL, this->getTokenValue()); }
			 	"="			{	return create_token(TOKEN_ASSIGN, this->getTokenValue()); }
			 	";"			{	return create_token(TOKEN_SEMICOLON, this->getTokenValue()); }
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
