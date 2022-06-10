%token_prefix LEX_

%left ASSIGN.

%token_type { uint64_t }
%extra_argument { Module* module}

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

	module->setRootNode(module->getToken<Statement>(B));
	std::cout << "\nEnd of parser.yy";
	if (module->getToken<Statement>(B))
		std::cout << " | statement: '" << module->getToken<Statement>(B)->toString() << "'";
	std::cout << std::endl;
}

expr(left) ::= statement(s) . {
	left = s;
}

/* Statements */
/* 	StatementDefinition */
statement(left) ::= statement_definition(sd) SEMICOLON. {
	left = sd;
	std::cout << " SEMICOLON";
}
	statement_definition(left) ::= statement_simple_definition(ss) . {
		left = ss;
	}
		statement_simple_definition(left) ::= . {
			left = 0;
		}
		statement_simple_definition(left) ::= statement_type_definition(std) . {
			left = std;
		}
			statement_type_definition(left) ::= variable_type(vt) variable_id(vi) . {
				VariableType* vtype = module->getToken<VariableType>(vt);
				Token* vid = module->getToken<Token>(vi);
				std::cout << " TYPE(\"" << vtype->toString() << "\")"
						  << " ID(\"" << vid->value << "\")";
				left = module->createToken<StatementDefinition>(vtype, vid);
			}
		statement_simple_definition(left) ::= statement_assign_definition(sad) . {
			left = sad;
		}
			statement_assign_definition(left) ::= variable_type(vt) variable_id(vi) ASSIGN expression(ex) . {
				VariableType* vtype = module->getToken<VariableType>(vt);
				Token* vid = module->getToken<Token>(vi);
				Expression* expr = module->getToken<Expression>(ex);
				std::cout << " TYPE(\"" << vtype->toString() << "\")"
						  << " ID(\"" << vid->value << "\") ASSIGN " << expr->toString();
				  left = module->createToken<StatementDefinition>(vtype, vid, expr);
		}
	/* statement_definition(left) ::=  */
/* StatementExpression */
statement(left) ::= statement_expression(se) SEMICOLON . {
	left = se;
}
	statement_expression(left) ::= expression_id(vi) ASSIGN expression(e) . {
		auto vid = module->getToken<ExpressionId>(vi);
		auto expr = module->getToken<Expression>(e);
		left = module->createToken<ExpressionAssign>(vid, expr);
	}
/* StatementList */
/* statement(left) ::= statement_list(sl) . {
	left = sl;
} */

/* Expressions */
expression(left) ::= expression_literal(el) . {
	left = el;
}
	expression_literal(left) ::= literal(l) . {
		left = module->createToken<ExpressionLiteral>(module->getToken<Literal>(l));
	}
	expression_literal(left) ::= literal_one_param(lop) . {
		left = module->createToken<ExpressionLiteral>(module->getToken<LiteralOneParam>(lop));
	}
expression(left) ::= . {
	left = 0;
}
expression(left) ::= expression_id(ei) . {
	left = ei;
}
	expression_id(left) ::= variable_id(vi) . {
		left = module->createToken<ExpressionId>(module->getToken<Token>(vi));
	}

/* VeriableTypes */
variable_type(left) ::= variable_type_simple(vts) . {
	left = vts;
}
	variable_type_simple(left) ::= TYPE(T) . {
		auto t = module->getToken<Token>(T);
		std::vector<VariableType*> vec;
		left = module->createToken<VariableType>(t, vec);
	}
variable_type(left) ::= variable_type_complex(vtx) . {
	left = vtx;
}
	variable_type_complex(left) ::= TYPE(T) LRB variable_type(vt) RRB . {
		auto sub_type = module->getToken<VariableType>(vt);
		auto t = module->getToken<Token>(T);
		left = module->createToken<VariableType>(t, std::vector<VariableType*>{sub_type});
	}
	variable_type_complex(left) ::= TYPE(T) LRB variable_type(vt1) COMMA variable_type(vt2) RRB . {
		auto sub_type1 = module->getToken<VariableType>(vt1);
		auto sub_type2 = module->getToken<VariableType>(vt2);
		auto t = module->getToken<Token>(T);
		left = module->createToken<VariableType>(t, std::vector<VariableType*>{sub_type1, sub_type2});
	}
variable_id(left) ::= ID(I) . {
	left = I;
}

/* Literals */
literal(left) ::= literal_integer(li) . {
	left = li;
}
	literal_integer(left) ::= LITERAL_INTEGER(LI) . {
		auto t = module->getToken<Token>(LI);
		left = module->createToken<LiteralInteger>(t);
	}
literal(left) ::= literal_float(lf) . {
	left = lf;
}
	literal_float(left) ::= LITERAL_FLOAT(LF) . {
		auto t = module->getToken<Token>(LF);
		left = module->createToken<LiteralFloat>(t);
	}
literal(left) ::= literal_string(ls) . {
	left = ls;
}
	literal_string(left) ::= LITERAL_STRING(LS) . {
		auto t = module->getToken<Token>(LS);
		left = module->createToken<LiteralString>(t);
	}
literal_one_param(left) ::= variable_type_complex(vtc) LSB expression RSB . {
	auto t_vtc = module->getToken<VariableType>(vtc);
	left = module->createToken<LiteralOneParam>(t_vtc, std::vector<Expression*>{});
}
