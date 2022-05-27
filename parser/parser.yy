%token_prefix TOKEN_

%left INTEGER.

%token_type { Token* }

%include {
#include <iostream>
#include "../lexer/lexer.def.h"
}

%syntax_error {
	std::cerr << "Syntax error!" << std::endl;
}

%start_symbol main

main ::= expr(A) . {
	std::cout << "End of parser.yy A" << std::endl; 
}

expr(A) ::= ID(B) . {
	std::cout << "In 'ID' statement  | A | B " << std::endl;
	//A->kind = B->kind;
	//A->str = B->str;
	//A->num = B->num;
}

expr(A) ::= ID(B) ID(C) SEMICOLON . {
	std::cout << "In 'ID ID SEMICOLON' statement(A) ID(\"" << B->str << "\") ID(\"" << C->str << "\") SEMICOLON" << std::endl;
}

expr ::= ID(B) ID(C) ASSIGN INTEGER(D) SEMICOLON . {
	std::cout << "In ID(\"" << B->str << "\") ID(\"" << C->str << "\") ASSIGN INTEGER(\"" << D->num << "\") SEMICOLON" << std::endl; 
}

expr(A) ::= INTEGER(B) . {
	std::cout << "In 'INTEGER' statement (A) value=B | kind=" << B->kind << ", val=" << B->num << std::endl;
	//A->kind = B->kind;
	//A->num = B->num;
}

