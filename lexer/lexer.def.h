#pragma once

typedef union {
	double dvalue;
	char* cvalue;
} YYSTYPE;

struct ParserState {
	int result;
	ParserState() : result(0) {}
};