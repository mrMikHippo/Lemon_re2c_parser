%token_prefix TOKEN_

%left ASSIGN.
%left PLUS MINUS.
%left MUL.

%extra_argument { AST* p_ast}
%token_type { Token* }
%type expr { Expression* }
//%default_type { Expression* }

%include {
#include <iostream>
#include "../token.h"
//#include "../lexer/lexer.def.h"
#include "../ast.h"
}

%syntax_error {
	std::cerr << "Syntax error!" << std::endl;
}

%start_symbol main

main ::= expr(A) . {
	//std::cout << "\nEnd of parser.yy " << std::endl;
	std::cout << std::endl;
	//std::cout << "Create AST... A " << typeid(A).name() << std::endl;
	p_ast->node = A;
	std::cout << "root: '" << p_ast->node->token->value << "'" << std::endl;
}

//expr(A) ::= expr(B) expr(C) SEMICOLON . {
	// Initialization
	// expr(C) = typeof expr(B)
//	std::cout << "Initialization  A B C" << std::endl;
//}

expr(A) ::= expr(B) PLUS(Op) expr(C) . {
	A = new OperatorExpression(Op);
	A->left = B;
	A->right = C;
}

expr(A) ::= expr(B) MINUS(Op) expr(C) . {
	A = new OperatorExpression(Op);
	A->left = B;
	A->right = C;
}

expr(A) ::= expr(B) MUL(Op) expr(C) . {
	A = new OperatorExpression(Op);
	A->left = B;
	A->right = C;
}

expr(A) ::= expr(B) ASSIGN(Op) expr(C) SEMICOLON . {
	A = new OperatorExpression(Op);
	A->left = B;
	A->right = C;
	std::cout << A->token->value << " " << A->left->token->value << " " << A->right->token->value << std::endl;
}

expr(A) ::= ID(B) . {
	A = new IDExpression(B);
	std::cout << " ID(\"" << A->token->value << "\")" << std::endl;
}

expr(A) ::= LITERAL(B) . {
	A = new LiteralExpression(B);
	std::cout << " LITERAL(\"" << A->token->value << "\")" << std::endl;
}

