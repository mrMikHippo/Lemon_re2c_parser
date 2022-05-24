#include <sstream>
#include <cassert>
#include <cstdlib>
#include "lexer/test_scanner.h"
#include "lemon_p/parser.c"

int main() {

	YYSTYPE yylval;
	Scanner scanner(&std::cin);
	void *pParser = ParseAlloc(malloc);
	int tokenID;


#if 1
    ParseTrace(stderr, (char*)"[Parser] >> ");
#endif
	ParserState state;

	// Parse(pParser, INTEGER, 15);
	// Parse(pParser, PLUS, 0);
	// Parse(pParser, INTEGER, 7);
	// Parse(pParser, 0, 0);

	while (tokenID = scanner.scan(yylval)) {
		Parse(pParser, tokenID, yylval, &state);
	}

	Parse(pParser, 0, yylval, &state);

	ParseFree(pParser, free);

	printf("RESULT: %d\n", state.result);
	
	return 0;
}
