%token_prefix TOKEN_

%left LEXEME_INTEGER.

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

expr(A) ::= LEXEME_INTEGER(B) . {
	std::cout << "In LEXEME_INTEGER statement A | name=" << B->data.str << std::endl;
}

expr(A) ::= NAME(B) . {
	std::cout << "In NAME statement" << B->data.str << std::endl;
	A->kind = B->kind;
	A->data.str = B->data.str;
}

expr(A) ::= LEXEME_INTEGER NAME(B) SEMICOLON . {
	std::cout << "In LEXEME_INTEGER NAME SEMICOLON statement (A) name=" << B->data.str << std::endl;
}

