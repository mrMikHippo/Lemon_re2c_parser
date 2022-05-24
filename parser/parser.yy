%token_prefix TOKEN_

%left PLUS MINUS.
%left MULTIPLY DIVIDE.

%token_type {YYSTYPE}

%include {
#include <iostream>
#include "../lexer_v2/lexer.def.h"
}

%syntax_error {
	std::cerr << "Syntax error!" << std::endl;
}

program ::= expr(A). {
	if (A.kind == TOKEN_INT) {
		std::cout << "Result i=" << A.int_value << std::endl; 
	} else {
		std::cout << "Result f=" << A.float_value << std::endl; 
	}
} 

expr(A) ::= expr(B) PLUS expr(C). {
	switch(A.kind) {
	case TOKEN_INT:
		A.int_value = B.int_value + C.int_value;
		break;
	case TOKEN_FLOAT:
		A.float_value = B.float_value + C.float_value; 
		break;
	}
} 

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
	std::cout << "In INT statement" << std::endl;
	A.int_value = B.int_value;
	A.kind = B.kind;
}

expr(A) ::= FLOAT(B). {
	std::cout << "In FLOAT statement" << std::endl;
	A.float_value = B.float_value;
	A.kind = B.kind;
}