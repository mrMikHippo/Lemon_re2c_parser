%token_prefix LEX_

%left ASSIGN.

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
	std::string err_msg = " Syntax error! TODO Info message for Error! " + std::to_string(yyminor) + " | " + std::to_string(yymajor);
	throw std::invalid_argument(err_msg.c_str());
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
		statement_simple_definition(left) ::= statement_assign_definition(sad) . {
			left = sad;
		}
			statement_assign_definition(left) ::= variable_type(vt) variable_id(vi) ASSIGN expression(ex) . {
				VariableType* vtype = module->getVariableType(vt);
				Token vid = module->getToken(vi);
				Expression* expr = module->getExpression(ex);
				StatementDefinition* st = module->createStatementDefinition(vtype, vid, expr);
				std::cout << " TYPE(\"" << vtype->toString() << "\")"
						  << " ID(\"" << vid.value << "\") ASSIGN " << expr->toString() << std::endl;
				left = module->insertStatementDefinition(st);
			}


expression(left) ::= expression_literal(el) . {
	left = el;
}
	expression_literal(left) ::= literal(l) . {
		ExpressionLiteral* exp_lit = new ExpressionLiteral(module->getLiteral(l));
		left = module->insertExpression(exp_lit);
	}

variable_type(left) ::= TYPE(T) . {
	auto token = module->getToken(T);
	left = module->createVariableType(module->getToken(T), {});
}

variable_id(left) ::= ID(I) . {
	left = I;
}

literal(left) ::= literal_integer(li) . {
	left = li;
}
	literal_integer(left) ::= LITERAL_INTEGER(LI) . {
		left = module->createLiteral<LiteralInteger>(LI);
	}
literal(left) ::= literal_float(lf) . {
	left = lf;
}
	literal_float(left) ::= LITERAL_FLOAT(LF) . {
		left = module->createLiteral<LiteralFloat>(LF);
	}
literal(left) ::= literal_string(ls) . {
	left = ls;
}
	literal_string(left) ::= LITERAL_STRING(LS) . {
		left = module->createLiteral<LiteralString>(LS);
	}
