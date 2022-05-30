#define ENABLE_PARSER 1

#include <iostream>
#include <vector>

#include "token.h"
#include "lexer/lexer.h"
#include "ast.h"

#if ENABLE_PARSER
#include "parser/parser.c"
#endif

using namespace std;


int main() {

#if ENABLE_PARSER
	void* pParser = ParseAlloc(malloc);
#endif

#if 0
	ParseTrace(stderr, (char*)"[Parser] >> ");
#endif

	bool exit = false;
	bool print = false;
	int tokenID;
	Token* token;
	vector<Token *> tokens;

	while (!exit) {
		string cmd;
		getline(cin, cmd);

		Lexer lexer(cmd.c_str());

		while(token = lexer.scan()) {
			tokens.push_back(token);
			
			if (token->kind == TOKEN_EOF) {
				exit = true;
				break;
			}

			if (token->kind == TOKEN_PRINT) {
				cout << "Registered tokens (" << tokens.size() << "):" << endl;
				for (const auto& el : tokens) {
					string name = tokenKindToString(el->kind);
					if (name != "Unknown")
						cout << "[" << name << "] " << (el->str ? "value="s + string(el->str) : "") << endl;
				}
				print = true;
			} 
#if ENABLE_PARSER
			else {
				Parse(pParser, token->kind, token);
				print = false;
			}
#endif
		}
#if ENABLE_PARSER
		if (!exit && !print)
			Parse(pParser, 0, token);
#endif

	}

	for (const auto& el : tokens) {
		if (el)
			delete el;
	}

#if ENABLE_PARSER
	ParseFree(pParser, free);
#endif

	cout << "Finished" << endl;
	return 0;
}