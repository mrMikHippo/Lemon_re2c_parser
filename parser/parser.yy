%token_prefix TOKEN_

%right ASSIGN.
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

main ::= expr . {
	std::cout << "\nEnd of parser.yy A" << std::endl; 
}

//expr ::= ID(B) ID(C) SEMICOLON . {
//	std::cout << "In 'ID ID SEMICOLON' statement(A) ID(\"" << B->str << "\") ID(\"" << C->str << "\") SEMICOLON" << std::endl;
//}

//expr ::= expr_two_ids SEMICOLON . {
//	std::cout << "In expr_id SEMICOLON" << std::endl;
//}

//expr ::= ID(B) ID(C) ASSIGN INTEGER(D) SEMICOLON . {
//	std::cout << "In ID(\"" << B->str << "\") ID(\"" << C->str << "\") ASSIGN INTEGER(\"" << D->num << "\") SEMICOLON" << std::endl; 
//}

//expr ::= ID(B) ASSIGN INTEGER(C) SEMICOLON . {
//	std::cout << "In ID(\"" << B->str << "\") ASSIGN INTEGER(\"" << C->num << "\") SEMICOLON" << std::endl; 
//}

//expr ::= ID(B) ASSIGN ID(C) SEMICOLON . {
//	std::cout << "In ID(\"" << B->str << "\") ASSIGN ID(\"" << C->str << "\") SEMICOLON" << std::endl; 
//}

//expr_two_ids ::= ID ID . {
//	std::cout << "In ID ID statement" << std::endl;
//}


expr ::= expr SEMICOLON . {
	std::cout << " SEMICOLON";
}

expr ::= expr ASSIGN . {
	std::cout << " ASSIGN";
}

expr ::= ID(B) . {
	std::cout << " ID(\"" << B->str << "\")";
}

expr ::= expr ID(C) . {
	std::cout << " ID(\"" << C->str << "\")";
}

expr ::= expr INTEGER(C) . {
	std::cout << " INTEGER(\"" << C->num << "\")";
}

expr ::= INTEGER(B) . {
	std::cout << " INTEGER(\"" << B->str << "\")";
}

