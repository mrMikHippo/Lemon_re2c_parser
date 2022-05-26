#define ENABLE_PARSER 1

#include <iostream>
#include <vector>

#include "token.h"
#include "lexer/lexer.h"

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
	int tokenID;
	Token* token;
	vector<Token *> tokens;

	while (!exit) {
		string cmd;
		getline(cin, cmd);

		Lexer lexer(cmd.c_str());

		while(token = lexer.scan()) {
			if (token->kind == TOKEN_EOF) {
				exit = true;
				break;
			}
			tokens.push_back(token);
			cout << "Parse called for token [" << token->kind << "] " 
				 << tokenKindToString(token->kind) << " ";
			if (token->data.str)
				cout << "name=" << token->data.str << endl;
			else
				cout << "num=" << token->data.num << endl;
#if ENABLE_PARSER
			Parse(pParser, token->kind, token);
#endif
		}
#if ENABLE_PARSER
		if (!exit)
			Parse(pParser, 0, token);
#endif

	}

	for (const auto& el : tokens) {
		delete el;
	}

#if ENABLE_PARSER
	ParseFree(pParser, free);
#endif

	cout << "Finished" << endl;
	return 0;
}