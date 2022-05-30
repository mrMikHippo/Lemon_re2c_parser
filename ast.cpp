#include "ast.h"

#include <iostream>

using std::cout;
using std::endl;

ASTNode* create_literal_ast(scanner_token* token) {
	cout << "Create Literatl AST" << endl;
	ASTNode* node = new ASTNode;
	node->kind = AST_Kind::AST_LITERAL;
	node->token = token;
	return node;
}

ASTNode* create_binary_ast(scanner_token* token, ASTNode* left, ASTNode* right) {
	cout << "Create Binary AST" << endl;
	ASTNode* node = new ASTNode;
	node->kind = AST_Kind::AST_BINARY;
	node->token = token;
	node->node.binary.left = left;
	node->node.binary.right = right;
	return node;
}