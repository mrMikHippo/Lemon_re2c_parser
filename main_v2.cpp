#include <iostream>

#include "lexer_v2/lexer.h"
#include "parser/parser.c"

using namespace std;

int main() {

	void* pParser = ParseAlloc(malloc);

#if 0
	ParseTrace(stderr, (char*)"[Parser] >> ");
#endif

	// YYSTYPE yylval;
	bool exit = false;
	int value;
	int tokenID;
	
	while (true) {
		string cmd;
		getline(cin, cmd);

		Lexer lexer(cmd.c_str());

		while(tokenID = lexer.scan()) {
			Parse(pParser, tokenID, atoi(lexer.getTokenValue().c_str()));
		}
		Parse(pParser, 0, 0);
	}

	ParseFree(pParser, free);

	cout << "Finished" << endl;
	return 0;
}