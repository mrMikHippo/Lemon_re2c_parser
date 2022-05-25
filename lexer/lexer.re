#pragma once

#include <string>
#include <cstring>
#include "../parser/parser.h"
#include "lexer.def.h"

std::string tokenIDtoString(int tokenID) {
	switch(tokenID) {
	case TOKEN_ADD:
		return "TOKEN_ADD";
	case TOKEN_SUB:
		return "TOKEN_SUB";
	case TOKEN_MUL:
		return "TOKEN_MUL";
	case TOKEN_DIV:
		return "TOKEN_DIV";
	case TOKEN_LBR:
		return "TOKEN_LBR";
	case TOKEN_RBR:
		return "TOKEN_RBR";
	case TOKEN_INT:
		return "TOKEN_INT";
	case TOKEN_FLOAT:
		return "TOKEN_FLOAT";
	}
	return "Unknown";
}

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
			 					yylval.dvalue = atoi(this->getTokenValue().c_str());
			 					return TOKEN_INT; 
			 				}
 				FLOAT		{ 	
 								yylval.dvalue = stod(this->getTokenValue());
 								return TOKEN_FLOAT; 
 							}
			 	"+"			{	return TOKEN_ADD; }
			 	"-"			{ 	return TOKEN_SUB; }
			 	"*"			{ 	return TOKEN_MUL; }
			 	"/"			{ 	return TOKEN_DIV; }
			 	")"			{	return TOKEN_RBR; }
				"("			{	return TOKEN_LBR; }
				[ ]+		{ 	continue; }
				"exit"		{ 	return -1; }
				$			{ 	return 0; }
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