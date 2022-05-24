%token_prefix TOKEN_

%left PLUS MINUS.
%left MULTIPLY DIVIDE.

%token_type {YYSTYPE}

%include {
#include <iostream>
#include "../lexer_v2/lexer.def.h"
}

%syntax_error {
	perror("Syntax error: ");
}

program ::= expr(A). { std::cout << "Result=" << A.int_value << std::endl; }

expr(A) ::= expr(B) PLUS expr(C). { A.int_value = B.int_value + C.int_value; } 

expr(A) ::= expr(B) MINUS expr(C). { A.int_value = B.int_value - C.int_value; } 

expr(A) ::= expr(B) MULTIPLY expr(C). { A.int_value = B.int_value * C.int_value; } 

expr(A) ::= expr(B) DIVIDE expr(C). { 
	if ( C.int_value != 0) {
		A.int_value = B.int_value / C.int_value;
	} else {
		std::cout << "Divide by zero" << std::endl;
	}
}
 

expr(A) ::= INT(B). {
	A.int_value = B.int_value;
}