#pragma once

typedef union {
	double dvalue;
} YYSTYPE;

struct ParserState {
	int result;
	ParserState() : result(0) {}
};