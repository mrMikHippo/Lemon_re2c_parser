%token_prefix TOKEN_

%left PLUS MINUS.

%token_type {int}

%include {
#include <iostream>
}

%syntax_error {
	perror("Syntax error: ");
}

program ::= expr(A). { std::cout << "Result=" << A << std::endl; }

expr(A) ::= expr(B) PLUS expr(C). { 
	A = B + C; 
	//std::cout << "A = B PLUS C: " << A << " = " << B << " PLUS " << C << std::endl;
} 

expr(A) ::= expr(B) MINUS expr(C). { A = B - C; } 

//expr(A) ::= expr(B) MUL expr(C). { A = B - C; } 

expr(A) ::= INT(B). {
	//std::cout << "1 expr(A) ::= INT(B) [" << A << ";" << B << "]" << std::endl;
	A = B;
	//std::cout << "2 expr(A) ::= INT(B) [" << A << ";" << B << "]" << std::endl;
}