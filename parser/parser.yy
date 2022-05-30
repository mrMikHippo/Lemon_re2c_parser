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
	//std::cout << "\nEnd of parser.yy A" << std::endl; 
	std::cout << std::endl;
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

expr ::= expr ID(C) . {
	std::cout << " ID(\"" << C->str << "\")";
}

expr ::= expr INTEGER(C) . {
	std::cout << " INTEGER(\"" << C->num << "\")";
}

expr ::= expr LRB . {
	std::cout << " LRB";
}

expr ::= expr RRB . {
	std::cout << " RRB";
}

expr ::= expr LSB . {
	std::cout << " LSB";
}

expr ::= expr RSB . {
	std::cout << " RSB";
}

expr ::= expr COMMA . {
	std::cout << " COMMA";
}

expr ::= expr COLON . {
	std::cout << " COLON";
}

expr ::= expr DOT . {
	std::cout << " DOT";
}

expr ::= ID(B) . {
	std::cout << " ID(\"" << B->str << "\")";
}

expr ::= INTEGER(B) . {
	std::cout << " sINTEGER(\"" << B->num << "\")";
}

