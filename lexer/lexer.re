#pragma once

#include <string>
#include <cstring>
#include <algorithm>
#include <iostream>
// #include "../parser/parser.h"
// #include "lexer.def.h"
// #include "../AST/token.h"
#include "../AST/global_types_map.h"
#include "../module.h"
#include "../parser/parser.c"

class Lexer {
public:

	Lexer(Module* module_) :
		_module(module_)
	{
		// _start = _cursor = _content;
		// _limit = _content + strlen(_content);
	}
	// Lexer(const char* s) :
	// 	_content(s)
	// {
	// 	_start = _cursor = _content;
	// 	_limit = _content + strlen(_content);
	// }

	void scan(const std::string& source) {
		// void scan() {
		_content = source.c_str();
		_start = _cursor = _content;
		_limit = _content + strlen(_content);

		void* pParser = ParseAlloc(malloc);
#if 0
		ParseTrace(stderr, (char*)"[Parser] >> ");
#endif

		for (;;) {
			_start = _cursor;

			 	//"+"			{	return create_token(TOKEN_PLUS, this->getTokenValue()); }
			 	//D+			{	return create_token(TOKEN_LITERAL, this->getTokenValue()); }
			 	//(L)(L|D)*	{	return create_token(TOKEN_ID, this->getTokenValue()); }			 	//";"			{	return create_token(TOKEN_SEMICOLON, this->getTokenValue()); }

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
			 	QS = "\"";
			 	CR = "\r";
			 	LF = "\n";
			 	CRLF = CR?LF;

			 	INT			{
								auto lex = _module->createToken(this->getTokenValue());
								Parse(pParser, LEX_LITERAL_INTEGER, _module->insertToken(lex), _module);
		 						continue;
		 					}
			 	FLOAT		{	std::cout << "[ Lexer ] LEX_LITERAL_FLOAT: " << this->getTokenValue() << std::endl; continue; }
				QS			{	goto string_loop; }
			 	ID			{
			 					// if getTokenID is at global map of types -  create token Type else create token ID
								std::vector<std::string>& mp = GlobalTypeMap::getInstance().types;
								if (std::find(mp.begin(), mp.end(), this->getTokenValue()) != mp.end()) {
									auto lex = _module->createToken(this->getTokenValue());
									Parse(pParser, LEX_TYPE, _module->insertToken(lex), _module);
					 			} else {
									auto lex = _module->createToken(this->getTokenValue());
									Parse(pParser, LEX_ID, _module->insertToken(lex), _module);
					 			}
					 			continue;
			 	 			}
				";"			{
								auto lex = _module->createToken(this->getTokenValue());
								Parse(pParser, LEX_SEMICOLON, _module->insertToken(lex), _module);
								continue;
							}
				"="			{
								auto lex = _module->createToken(this->getTokenValue());
								Parse(pParser, LEX_ASSIGN, _module->insertToken(lex), _module);
								continue;
							}
			 	[^]			{   continue; }
				$			{ 	break; }
			 */
		string_loop:
			/*!re2c
			 	QS			{
								auto lex = _module->createToken(this->getTokenValue());
								Parse(pParser, LEX_LITERAL_STRING, _module->insertToken(lex), _module);
								continue;
							}
			 	[^]			{	goto string_loop; }
			 	$			{ 	continue; }
			 */
		}
		Parse(pParser, 0, 0, _module);
		ParseFree(pParser, free);
	}

	std::string getTokenValue() const  {
		return std::string(_start, _cursor-_start);
	}

	int getLength() const {
		return strlen(_content);
	}

private:
	Module* _module;
	const char* _content;
	const char* _start;
	const char* _cursor;
	const char* _limit;
	const char* _marker;
	const char* _ctxmarker;
};
