#pragma once

#include <string>

class Lexer {
public:
	enum token_t {
		TOKEN_END = 0,
		TOKEN_PLUS,
		TOKEN_NUMBER
	};

	Lexer(const char* s);
	token_t scan();

	std::string getTokenValue() const;

private:
	const char* _content;
	const char* _start;
	const char* _cursor;
	const char* _limit;
	const char* _marker;
	const char* _ctxmarker;
};