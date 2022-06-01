#define ENABLE_PARSER 0

#include <iostream>
#include <vector>
#include <string>

// #include "token.h"
// #include "lexer/lexer.h"
// #include "ast.h"

#if ENABLE_PARSER
#include "parser/parser.c"
#endif

// #include "token.h"
// #include "AST/literal.h"
// #include "AST/expression.h"

using namespace std;

#if 0
void printTree(const Expression* node, const string& prefix, bool isLeft) {
	if (node != nullptr) {
		cout << prefix;
		cout << (isLeft ? "├── " : "└── ");
		cout << node->token->value << endl;

		printTree(node->left,  prefix + (isLeft ? "│   " : "    "), true);
        printTree(node->right,  prefix + (isLeft ? "│   " : "    "), false);
	}
}

void printTree(const Expression* node) {
	printTree(node, "", false);
}
#endif



int main() {

#if 0
	bool exit = false;
	void* pParser = ParseAlloc(malloc);
#endif
#if 0
	ParseTrace(stderr, (char*)"[Parser] >> ");
#endif

#if 0
	bool exit = false;
	bool print = false;
	int tokenID;
	Token* token;
	vector<Token *> tokens;
	// AST* ast_root = new AST;

	string cmd;
	getline(cin, cmd);

	Lexer lexer(cmd.c_str());

	while(token = lexer.scan()) {
		tokens.push_back(token);

		Parse(pParser, token->type, token);
	}
	
	Parse(pParser, 0, token);

	// cout << "Tree: " << endl;
	// printTree(ast_root->node);

	ParseFree(pParser, free);

	// delete ast_root;
#endif
	cout << "Finished" << endl;
	return 0;
}