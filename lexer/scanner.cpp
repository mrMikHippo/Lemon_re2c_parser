
#pragma once

#include <fstream>

class Scanner {
private:
	char* _buffer;	// buffer memory
	char* _cursor; // current position
	char* _limit;
	char* _token;
	char* _marker;
	// int _buffer_size;
	int _line_number;
	std::istream* _ifs;

public:w
	Scanner() :
		_buffer(nullptr),
		_cursor(nullptr),
		_limit(nullptr),
		_toke(nullptr),
		_marker(nullptr),
		// _buffer_size()
		_line_number(1)
		{}

	int increment_line_number() {
		++_line_number;
	}

	int get_line_number() {
		return _line_number;
	}

	int scan(YYSTYPE& yylval) {
	std:
		_token = _cursor;

		/*!re2c
		 	re2c:yyfill:enable = 0;
		 	re2c:define:YYCTYPE = "char";
		 	re2c:define:YYCURSOR = _cursor;
		 	re2c:define:YYMARKER = _marker;

		*/
	}
};	
