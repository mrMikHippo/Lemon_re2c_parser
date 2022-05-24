#pragma once

// typedef union {
// 	int int_value;
// 	float float_value;
// } YYSTYPE;

struct YYSTYPE {
	int kind;
	union {
		int int_value;
		float float_value;
	};
};

struct ParserState {
	int result;
	ParserState() : result(0) {}
};