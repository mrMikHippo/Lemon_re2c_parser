#include <iostream>

#include "lexer_v2/lexer.h"
#include "parser/parser.c"
#include "lexer_v2/lexer.def.h"

using namespace std;

int main() {

	void* pParser = ParseAlloc(malloc);

#if 0
	ParseTrace(stderr, (char*)"[Parser] >> ");
#endif

	YYSTYPE yylval;
	bool exit = false;
	int tokenID;
	
	while (true) {
		string cmd;
		getline(cin, cmd);

		Lexer lexer(cmd.c_str());

		while(tokenID = lexer.scan(yylval)) {
			Parse(pParser, tokenID, yylval);
		}
		Parse(pParser, 0, yylval);
	}

	ParseFree(pParser, free);

	cout << "Finished" << endl;
	return 0;
}