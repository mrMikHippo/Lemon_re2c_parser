%token_prefix TOKEN_

%left PLUS MINUS.

%token_type {int}

%include {
#include <iostream>
}

%syntax_error {
	std::cerr << "Syntax error!" << std::endl;
}

program ::= expr(A). { std::cout << "Result=" << A << std::endl; }

expr(A) ::= expr(B) PLUS expr(C). { A = B + C; } 

expr(A) ::= INT(B). {
	A = B;
}