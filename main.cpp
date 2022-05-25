#include <iostream>

#include "lexer/lexer.h"
#include "parser/parser.c"

using namespace std;

int main() {

	void* pParser = ParseAlloc(malloc);

#if 0
	ParseTrace(stderr, (char*)"[Parser] >> ");
#endif

	YYSTYPE yylval;
	bool exit = false;
	int tokenID;
	
	while (!exit) {
		string cmd;
		getline(cin, cmd);

		Lexer lexer(cmd.c_str());

		while(tokenID = lexer.scan(yylval)) {
			if (tokenID == -1)
				exit = true;
			else {
				cout << "Parse called for tokenID [" << tokenID << "] " << tokenIDtoString(tokenID) << endl;
				Parse(pParser, tokenID, yylval);
			}
		}
		if (!exit)
			Parse(pParser, 0, yylval);
	}

	ParseFree(pParser, free);

	cout << "Finished" << endl;
	return 0;
}