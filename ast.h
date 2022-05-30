#pragma once


enum class AST_Kind {
	AST_LITERAL,
	AST_BINARY
};

struct ASTNode {
	enum AST_Kind kind;

	Token* token;

	union {
		struct {
			struct ASTNode* left;
			struct ASTNode* right;
		} binary;
	} node;
};

ASTNode* create_literal_ast(Token *token);
ASTNode* create_binary_ast(Token *token, ASTNode* left, ASTNode* right);