#include <iostream>

#include "lexer_v2/lexer.h"
#include "parser/parser.c"

using namespace std;

int main() {

	while (true) {
		string cmd;
		getline(cin, cmd);

		Lexer lexer(cmd.c_str());

		Lexer::token_t token;

		do {
			token = lexer.scan();

			switch(token) {
				case Lexer::TOKEN_NUMBER:
					cout << "Num: " << lexer.getTokenValue() << endl;
					break;
				case Lexer::TOKEN_ADD:
					cout << "+: " << lexer.getTokenValue() << endl;
					break;
				case Lexer::TOKEN_SUB:
					cout << "-: " << lexer.getTokenValue() << endl;
					break;
				case Lexer::TOKEN_MUL:
					cout << "*: " << lexer.getTokenValue() << endl;
					break;
				case Lexer::TOKEN_DIV:
					cout << "/: " << lexer.getTokenValue() << endl;
					break;
				case Lexer::TOKEN_END:
					cout << "end reached" << endl;
					break;
			}
		} while (token != Lexer::TOKEN_END);

	}


	cout << "Finished" << endl;
	return 0;
}