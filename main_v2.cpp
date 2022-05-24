#include <iostream>

#include "lexer_v2/lexer.h"
#include "parser/parser.c"

using namespace std;

int main() {

	void* pParser = ParseAlloc(malloc);

#if 0
	ParseTrace(stderr, (char*)"[Parser] >> ");
#endif


#if 1
	// YYSTYPE yylval;
	bool exit = false;
	int value;
	while (true) {
		string cmd;
		getline(cin, cmd);

		Lexer lexer(cmd.c_str());

		Lexer::token_t tokenID;

		do {
			tokenID = lexer.scan();

			switch(tokenID) {
				case Lexer::TOKEN_NUMBER:
					cout << "Num: " << lexer.getTokenValue() << endl;
					value = atoi(lexer.getTokenValue().c_str());		
					Parse(pParser, TOKEN_INT, value);
					break;
				case Lexer::TOKEN_ADD:
					cout << "+: " << lexer.getTokenValue() << endl;
					Parse(pParser, TOKEN_PLUS, 0);
					break;
				case Lexer::TOKEN_SUB:
					cout << "-: " << lexer.getTokenValue() << endl;
					Parse(pParser, TOKEN_MINUS, 0);
					break;
				// case Lexer::TOKEN_MUL:
					// cout << "*: " << lexer.getTokenValue() << endl;
					// Parse(pParser, TOKEN_MUL, 0);
					// break;
				// case Lexer::TOKEN_DIV:
					// cout << "/: " << lexer.getTokenValue() << endl;
					// break;
				case Lexer::TOKEN_END:
					// cout << "end reached" << endl;
					break;
			}
		} while (tokenID != Lexer::TOKEN_END);
		Parse(pParser, 0, 0);
	}
#else
	Parse(pParser, TOKEN_INT, 15);
	Parse(pParser, TOKEN_PLUS, 0);
	Parse(pParser, TOKEN_INT, 2);

#endif
	ParseFree(pParser, free);


	cout << "Finished" << endl;
	return 0;
}