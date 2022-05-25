%token_prefix TOKEN_

%left ADD SUB.
%left MUL DIV.

%token_type { YYSTYPE }

%include {
#include <iostream>
#include "../lexer/lexer.def.h"
}

%syntax_error {
	std::cerr << "Syntax error!" << std::endl;
}

%start_symbol main

main ::= expr(A). {
	std::cout << "Result=" << A.dvalue << std::endl; 
}

expr(A) ::= expr(B) ADD expr(C). { 
	std::cout << "expr ADD expr " << B.dvalue << " + " << C.dvalue << " = ";
	A.dvalue = B.dvalue + C.dvalue; 
	std::cout << A.dvalue << std::endl; 
}

expr(A) ::= expr(B) SUB expr(C). { 
	std::cout << "expr SUB expr " << B.dvalue << " - " << C.dvalue << " = ";
	A.dvalue = B.dvalue - C.dvalue; 
	std::cout << A.dvalue << std::endl; 
}

expr(A) ::= expr(B) MUL expr(C). { 
	std::cout << "expr MUL expr " << B.dvalue << " * " << C.dvalue << " = ";
	A.dvalue = B.dvalue * C.dvalue;
	std::cout << A.dvalue << std::endl; 
}

expr(A) ::= expr(B) DIV expr(C). { 
	if (C.dvalue != 0) {
		std::cout << "expr DIV expr " << B.dvalue << " * " << C.dvalue << " = ";
		A.dvalue = B.dvalue / C.dvalue;
		std::cout << A.dvalue << std::endl; 
	} else {
		std::cout << "Division by Zero!" << std::endl;
	}
}

expr(A) ::= LBR expr(B) RBR. {
	std::cout << "LBR expr RBR 	(" << B.dvalue << ")" << std::endl;
	A.dvalue = B.dvalue;
}

expr(A) ::= INT(B). {
	std::cout << "In INT statement " << B.dvalue << std::endl;
	A.dvalue = B.dvalue;
}

expr(A) ::= FLOAT(B). {
	std::cout << "In FLOAT statement " << B.dvalue << std::endl;
	A.dvalue = B.dvalue;	
}