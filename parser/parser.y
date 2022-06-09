%token_prefix LEX_

/* %left ASSIGN. */

%token_type { uint64_t }
%extra_argument { Module* module}

//%type expr { Expression* }
//%default_type { Expression* }
/* %type statement { Statement* } */
/* %type variable_type { VariableType* } */

%include {
#include <iostream>
//#include "../token.h"
#include "../AST/literal.h"
#include "../AST/expression.h"
#include "../AST/statement.h"
#include "../AST/variable_type.h"
}

%syntax_error {
	std::cerr << " Syntax error! TODO Info message for Error! " << yyminor << " | " << yymajor << std::endl;
}

%start_symbol main

main ::= expr(B) . {

	module->setRootNode(module->getStatement(B));
	std::cout << "\nEnd of parser.yy B=" << B;
	if (module->getStatement(B))
		std::cout << " | statement: '" << module->getStatement(B)->toString() << "'";
	std::cout << std::endl;
}

expr(left) ::= statement(s) . {
	left = s;
}

/* statement(left) ::= statement_expression(se) . {
	left = se;
}
statement(left) ::= statement_list(sl) . {
	left = sl;
} */
statement(left) ::= statement_definition(sd) . {
	left = sd;
}
	statement_definition(left) ::= statement_simple_definition(ss) SEMICOLON . {
		left = ss;
		std::cout << " SEMICOLON";
	}
		statement_simple_definition(left) ::= . {
			left = 0;
		}
		statement_simple_definition(left) ::= statement_type_definition(std) . {
			left = std;
		}
			statement_type_definition(left) ::= variable_type(vt) variable_id(vi) . {
				VariableType* vtype = module->getVariableType(vt);
				Token vid = module->getToken(vi);
				StatementDefinition* st = module->createStatementDefinition(vtype, vid);
				std::cout << " TYPE(\"" << vtype->toString() << "\")"
						  << " ID(\"" << vid.value << "\")";
				left = module->insertStatementDefinition(st);
			}
		/*
		statement_simple(left) ::= statement_simple_definition(ssd) . {
			left = ssd;
		}
			statement_simple_definition(left) ::= variable_definition(vd) . {
				left = vd;
			}
		statement_simple(left) ::= statement_assign_definition(sad) . {
			left = sad;
		}
			statement_assign_definition(left) ::= variable_definition(vd) ASSIGN expression(el) . {
				auto tmp_vd = module->getToken(vd);
				auto tmp_el = module->getToken(el);
				std::string tmp_left_str = tmp_vd->value + " " + tmp_el->value;
				auto tmp_left = module->createToken(tmp_left_str);
				left = module->insertToken(tmp_left);
				std::cout << " ASSIGN";
			} */

/* expression(left) ::= expression_literal(el) . {
	left = el;
}
	expression_literal(left) ::= literal(l) . {
		left = l;
	}
		literal(left) ::= LITERAL_INTEGER(I) . {
			left = I;
			std::cout << " INTEGER(\"" << module->getToken(I)->value << "\")";
		}
		literal(left) ::= LITERAL_STRING(S) . {
			left = S;
			std::cout << " STRING(\"" << module->getToken(S)->value << "\")";
		}

variable_definition(left) ::= variable_value_definition(vvd) . {
	left = vvd;
}
	variable_value_definition(left) ::= variable_type(vt) variable_id(vi) . {
		std::string vvd_string = module->getToken(vt)->value + " " + module->getToken(vi)->value;
		auto t_left = module->createToken(vvd_string);
		left = module->insertToken(t_left);
	} */

variable_type(left) ::= TYPE(T) . {
	auto token = module->getToken(T);
	VariableType* vt = module->createVariableType(token, {});
	/* std::cout << " TYPE(\"" << vt->toString() << "\")"; */
	/* std::cout << " TYPE(\"" << module->getVariableType(id)->toString() << "\")"; */
	left = module->insertVariableType(vt);
}

variable_id(left) ::= ID(I) . {
	left = I;
	/* std::cout << " ID(\"" << module->getToken(I).value << "\")"; */
}
