#pragma once

typedef union {
	int int_value;
} YYSTYPE;

struct ParserState {
	int result;
	ParserState() : result(0) {}
};