%token_prefix LEX_

%left COMMA LRB RRB DOT COLON LSB RSB TYPE.
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
#include "../AST/content.h"
}

%syntax_error {
	std::string err_msg = " Syntax error! TODO Info message for Error! " + std::to_string(yyminor) + " | " + std::to_string(yymajor);
	throw std::invalid_argument(err_msg.c_str());
}

%stack_overflow {
    throw std::runtime_error("Parser stack overflow!");
}
/* %stack_size 1000 */

%start_symbol main

main ::= expr(B) . {
	module->setRootNode(module->getToken<Statement>(B));
	std::cout << "End of parser.yy";
	if (module->getToken<Statement>(B))
		std::cout << " | statement: '" << module->getToken<Statement>(B)->toString() << "'";
	std::cout << std::endl;
}

expr(left) ::= statement(s) . {
	left = s;
}

/** Statements **/
/* 	StatementDefinition */
statement(left) ::= statement_definition(sd) SEMICOLON. {
	left = sd;
}
	/* statement_definition(left) ::= statement_simple_definition(ss) . {
		left = ss;
	} */
		/* statement_simple_definition(left) ::= . {
			left = 0;
		} */
		statement_definition(left) ::= statement_type_definition(std) . {
			left = std;
		}
			statement_type_definition(left) ::= variable_type(vt) variable_id(vi) . {
				auto t_vt = module->getToken<VariableType>(vt);
				auto t_vi = module->getToken<Token>(vi);
				left = module->createToken<StatementDefinition>(t_vt, t_vi);
			}
		statement_definition(left) ::= statement_assign_definition(sad) . {
			left = sad;
		}
			statement_assign_definition(left) ::= variable_type(vt) variable_id(vi) ASSIGN expression(e) . {
				auto t_vt = module->getToken<VariableType>(vt);
				auto t_vi = module->getToken<Token>(vi);
				auto t_e = module->getToken<Expression>(e);
				left = module->createToken<StatementDefinition>(t_vt, t_vi, t_e);
			}

/* StatementExpression */
statement(left) ::= statement_expression(se) SEMICOLON . {
    left = se;
}
    statement_expression(left) ::= expression_assign(e) . {
        auto t_e = module->getToken<ExpressionAssign>(e);
		left = module->createToken<StatementExpression>(t_e);
    }
    statement_expression(left) ::= expression_call(ec) . {
        auto t_ec = module->getToken<Expression>(ec);
        left = module->createToken<StatementExpression>(t_ec);
    }

/* StatementList */
/* statement(left) ::= statement_list(sl) . {
	left = sl;
} */



/* Expressions */
expression(left) ::= expression_id(ei) . {
    left = ei;
}
    expression_id(left) ::= variable_id(vi) . {
        auto t_ei = module->getToken<Token>(vi);
        left = module->createToken<ExpressionId>(t_ei);
    }
expression(left) ::= expression_literal(el) . {
    left = el;
}
    expression_literal(left) ::= literal(l) . {
        auto t_l = module->getToken<Literal>(l);
        left = module->createToken<ExpressionLiteral>(t_l);
    }
expression(left) ::= expression_dot(ed) . {
	left = ed;
}
	expression_dot(left) ::= expression(e) DOT variable_id(vi) . {
		auto t_e = module->getToken<Expression>(e);
		auto t_vi = module->getToken<Token>(vi);
		left = module->createToken<ExpressionDot>(t_vi, t_e);
	}
/* expression(left) ::= expression_type(et) . {
	left = et;
}
	expression_type(left) ::= variable_type(vt) . {
		auto t_vt = module->getToken<VariableType>(vt);
		left = module->createToken<ExpressionType>(t_vt);
	} */
/* expression(left) ::= expression_assign(ea) . {
	left = ea;
} */
expression_assign(left) ::= expression(ei) ASSIGN expression(e) . {
	auto eid = module->getToken<Expression>(ei);
	auto expr = module->getToken<Expression>(e);
	left = module->createToken<ExpressionAssign>(eid, expr);
}
/* May be */
/* id.some(); */
/* id.some(arg, arg2); */
/* id.some(key1 = value1, key2 = value2); */
/* id.some(id.func(arg)); */
expression(left) ::= expression_call(ec) . {
	left = ec;
}
	expression_call(left) ::= expression(e) LRB arguments_call(ac) RRB . {
	    auto t_e = module->getToken<ExpressionDot>(e);
	    auto t_ac = module->getToken<Expression>(ac);
	    left = module->createToken<ExpressionCall>(t_e, t_ac);
	}
		arguments_call(left) ::= . {
			std::vector<Expression*> t_params;
			left = module->createToken<ExpressionCallOrdered>(nullptr, t_params);
		}
		arguments_call(left) ::= arguments_call_ordered_content(acoc) . {
			auto t_acoc = module->getToken<OneParamContent>(acoc);
			std::vector<Expression*> params;
			for (auto& el : t_acoc->getElements())
				params.push_back(el);
			left = module->createToken<ExpressionCallOrdered>(nullptr, params);
		}
			arguments_call_ordered_content(left) ::= arguments_call_ordered_body(acob) . {
				left = acob;
			}
				arguments_call_ordered_body(left) ::= expression(e) . {
					auto t_e = module->getToken<Expression>(e);
					left = module->createToken<OneParamContent>(t_e);
				}
				arguments_call_ordered_body(left) ::= arguments_call_ordered_body(acob) COMMA expression(e) . {
					auto t_acob = module->getToken<OneParamContent>(acob);
					auto t_e = module->getToken<Expression>(e);
					t_acob->addElement(t_e);
					left = acob;
				}
				arguments_call_ordered_body(left) ::= arguments_call_ordered_body(acob) COMMA . {
					left = acob;
				}
		arguments_call(left) ::= arguments_call_named_content(acnc) . {
			auto t_acnc = module->getToken<TwoParamContent>(acnc);
			std::vector<std::pair<Token*, Expression*>> params;
			for (auto& el : t_acnc->getElements())
				params.push_back(el);
			left = module->createToken<ExpressionCallNamed>(nullptr, params);
		}
			arguments_call_named_content(left) ::= arguments_call_named_body(acnb) . {
				left = acnb;
			}
				arguments_call_named_body(left) ::= variable_id(vi) ASSIGN expression(ei) . {
					auto t_vi = module->getToken<Token>(vi);
					auto t_ei = module->getToken<Expression>(ei);
					left = module->createToken<TwoParamContent>(std::make_pair(t_vi, t_ei));
				}
				arguments_call_named_body(left) ::= arguments_call_named_body(acnb) COMMA variable_id(vi) ASSIGN expression(e) . {
					auto t_acnb = module->getToken<TwoParamContent>(acnb);
					auto t_vi = module->getToken<Token>(vi);
					auto t_e = module->getToken<Expression>(e);
					t_acnb->addElement(std::make_pair(t_vi, t_e));
					left = acnb;
				}
				arguments_call_named_body(left) ::= arguments_call_named_body(acnb) COMMA . {
					left = acnb;
				}

/* VariableTypes */
variable_type(left) ::= variable_type_simple(vts) . {
	left = vts;
}
	variable_type_simple(left) ::= TYPE(T) . {
		auto t = module->getToken<Token>(T);
		std::vector<VariableType*> vec;
		left = module->createToken<VariableType>(t, vec);
	}
variable_type(left) ::= variable_type_complex(vtc) . {
	left = vtc;
}
	variable_type_complex(left) ::= variable_type_oneparam(vtop) . {
		left = vtop;
	}
		variable_type_oneparam(left) ::= TYPE(T) LRB variable_type(vt) RRB . {
			auto sub_type = module->getToken<VariableType>(vt);
			auto t = module->getToken<Token>(T);
			left = module->createToken<VariableType>(t, std::vector<VariableType*>{sub_type});
		}
	variable_type_complex(left) ::= variable_type_twoparam(vttp) . {
		left = vttp;
	}
		variable_type_twoparam(left) ::= TYPE(T) LRB variable_type(vt1) COMMA variable_type(vt2) RRB . {
			auto sub_type1 = module->getToken<VariableType>(vt1);
			auto sub_type2 = module->getToken<VariableType>(vt2);
			auto t = module->getToken<Token>(T);
			left = module->createToken<VariableType>(t, std::vector<VariableType*>{sub_type1, sub_type2});
		}
variable_id(left) ::= ID(I) . {
	left = I;
}

/* Literals */
literal(left) ::= literal_simple(ls) . {
	left = ls;
}
	literal_simple(left) ::= LITERAL_INTEGER(LI) . {
		auto t = module->getToken<Token>(LI);
		left = module->createToken<LiteralInteger>(t);
	}
	literal_simple(left) ::= LITERAL_FLOAT(LF) . {
		auto t = module->getToken<Token>(LF);
		left = module->createToken<LiteralFloat>(t);
	}
	literal_simple(left) ::= LITERAL_STRING(LS) . {
		auto t = module->getToken<Token>(LS);
		left = module->createToken<LiteralString>(t);
	}
literal(left) ::= literal_with_params(lwp) . {
	left = lwp;
}
	literal_with_params(left) ::= literal_one_param(lop) . {
		left = lop;
	}
		literal_one_param(left) ::= variable_type_oneparam(vtc) LSB literal_oneparam_content(loc) RSB . {
			auto t_vtc = module->getToken<VariableType>(vtc);
			auto t_loc = module->getToken<OneParamContent>(loc);
			std::vector<Expression*> vec;
			for (auto& el : t_loc->getElements()) {
				vec.push_back(el);
			}
			left = module->createToken<LiteralOneParam>(t_vtc, vec);
		}
			literal_oneparam_content(left) ::= literal_oneparam_body(lob) . {
				left = lob;
			}
				literal_oneparam_body(left) ::= . {
					left = module->createToken<OneParamContent>();
				}
				literal_oneparam_body(left) ::= literal_oneparam_body(lob) expression(e) COMMA . {
					auto t_lob = module->getToken<OneParamContent>(lob);
					auto t_e = module->getToken<Expression>(e);
					t_lob->addElement(t_e);
					left = lob;
				}
			literal_oneparam_content(left) ::= literal_oneparam_body(lob) expression(e) . {
				auto t_lob = module->getToken<OneParamContent>(lob);
				auto t_e = module->getToken<Expression>(e);
				t_lob->addElement(t_e);
				left = lob;
			}
	literal_with_params(left) ::= literal_two_param(ltp) . {
		left = ltp;
	}
		literal_two_param(left) ::= variable_type_twoparam(vtc) LSB literal_twoparam_content(ltc) RSB . {
			auto t_vtc = module->getToken<VariableType>(vtc);
			auto t_ltc = module->getToken<TwoParamContent>(ltc);
			std::vector<std::pair<Token*, Expression*>> vec;
			for (auto& el : t_ltc->getElements()) {
				vec.push_back(el);
			}
			left = module->createToken<LiteralTwoParam>(t_vtc, vec);
		}
			literal_twoparam_content(left) ::= literal_twoparam_body(ltb) . {
				left = ltb;
			}
				literal_twoparam_body(left) ::= . {
					left = module->createToken<TwoParamContent>();
				}
				literal_twoparam_body(left) ::= literal_twoparam_body(ltb) expression(e_left) COLON expression(e_right) COMMA . {
					auto t_ltb = module->getToken<TwoParamContent>(ltb);
					auto t_e_left = module->getToken<Expression>(e_left);
					auto t_e_right = module->getToken<Expression>(e_right);
					t_ltb->addElement(std::make_pair(t_e_left, t_e_right));
					left = ltb;
				}
			literal_twoparam_content(left) ::= literal_twoparam_body(ltb) expression(e_left) COLON expression(e_right) . {
				auto t_ltb = module->getToken<TwoParamContent>(ltb);
				auto t_e_left = module->getToken<Expression>(e_left);
				auto t_e_right = module->getToken<Expression>(e_right);
				t_ltb->addElement(std::make_pair(t_e_left, t_e_right));
				left = ltb;
			}
