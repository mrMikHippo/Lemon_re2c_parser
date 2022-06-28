%token_prefix LEX_

%left ASSIGN .
%left EQUAL .
%left TYPE .
%left LSB LRB .
%left DOT .
%left ID .

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
#include "../colored_o.h"
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

main ::= statement(S) . {
	module->setRootNode(module->getToken<Statement>(S));
	std::cout << "End of parser.y";
	if (module->getToken<Statement>(S))
		std::cout << " | statement: '" << module->getToken<Statement>(S)->toString() << "'";
	std::cout << std::endl;
	module->printTree();
}

/** Statements **/
/* StatementList */
statement(left) ::= statement_list(sl) . {
	left = sl;
}
	statement_list(left) ::= . {
		left = module->createToken<StatementList>();
	}
	statement_list(left) ::= statement_list(slb) statement_content(sc) . {
		auto t_slb = module->getToken<StatementList>(slb);
		auto t_sc = module->getToken<Statement>(sc);
		t_slb->addStatement(t_sc);
		left = slb;
	}
	/* For statement lists in statement lists */
	/* LCB statement_list RCB . */

/* 	StatementDefinition */
statement_content(left) ::= statement_definition(sd) SEMICOLON. {
	left = sd;
}
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
statement_content(left) ::= statement_expression(se) SEMICOLON . {
    left = se;
}
	statement_expression(left) ::= expression(e) . {
		auto t_e = module->getToken<Expression>(e);
		left = module->createToken<StatementExpression>(t_e);
	}

/** Expressions **/
expression(left) ::= expression_wo_assign(ewa) . {
	left = ewa;
}
	expression_wo_assign(left) ::= expression_id(ei) . {
	    left = ei;
	}
	    expression_id(left) ::= variable_id(vi) . {
	        auto t_ei = module->getToken<Token>(vi);
	        left = module->createToken<ExpressionId>(t_ei);
	    }
	expression_wo_assign(left) ::= expression_literal(el) . {
	    left = el;
	}
	    expression_literal(left) ::= literal(l) . {
	        auto t_l = module->getToken<Literal>(l);
	        left = module->createToken<ExpressionLiteral>(t_l);
	    }
	expression_wo_assign(left) ::= expression_at(ea) . {
		left = ea;
	}
		expression_at(left) ::= expression_wo_assign(ei) LSB expression(e) RSB . {
			auto t_ei = module->getToken<Expression>(ei);
			auto t_e = module->getToken<Expression>(e);
			left = module->createToken<ExpressionAt>(t_ei, t_e);
		}
	expression_wo_assign(left) ::= expression_dot(ed) . {
		left = ed;
	}
		expression_dot(left) ::= expression_wo_assign(e) DOT variable_id(vi) . {
			auto t_e = module->getToken<Expression>(e);
			auto t_vi = module->getToken<Token>(vi);
			left = module->createToken<ExpressionDot>(t_vi, t_e);
		}

	expression_wo_assign(left) ::= expression_call(ec) . {
		left = ec;
	}
		expression_call(left) ::= expression_wo_assign(e) LRB arguments_call(ac) RRB . {
		    auto t_e = module->getToken<Expression>(e);
		    auto t_ac = module->getToken<Expression>(ac);
		    left = module->createToken<ExpressionCall>(t_e, t_ac);
		}
			arguments_call(left) ::= . {
				left = module->createToken<ExpressionCallOrdered>(std::vector<Expression*>{});
			}
			arguments_call(left) ::= arguments_call_ordered_content(acoc) . {
				auto t_acoc = module->getToken<OneParamContent>(acoc);
				left = module->createToken<ExpressionCallOrdered>(t_acoc->getElements());
			}
				arguments_call_ordered_content(left) ::= arguments_call_ordered_body(acob) . {
					left = acob;
				}
					arguments_call_ordered_body(left) ::= expression_wo_assign(e) . {
						auto t_e = module->getToken<Expression>(e);
						left = module->createToken<OneParamContent>(t_e);
					}
					arguments_call_ordered_body(left) ::= arguments_call_ordered_body(acob) COMMA expression_wo_assign(e) . {
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
				left = module->createToken<ExpressionCallNamed>(t_acnc->getElements());
			}
				arguments_call_named_content(left) ::= arguments_call_named_body(acnb) . {
					left = acnb;
				}
					// do not use expression_assign ()
					arguments_call_named_body(left) ::= ID(I) ASSIGN expression_wo_assign(ei) . [DOT] {
						auto t_vi = module->getToken<Token>(I);
						auto t_ei = module->getToken<Expression>(ei);
						left = module->createToken<TwoParamContent>(std::make_pair(t_vi, t_ei));
					}
					arguments_call_named_body(left) ::= arguments_call_named_body(acnb) COMMA variable_id(vi) ASSIGN expression_wo_assign(e) . {
						auto t_acnb = module->getToken<TwoParamContent>(acnb);
						auto t_vi = module->getToken<Token>(vi);
						auto t_e = module->getToken<Expression>(e);
						t_acnb->addElement(std::make_pair(t_vi, t_e));
						left = acnb;
					}
					arguments_call_named_body(left) ::= arguments_call_named_body(acnb) COMMA . {
						left = acnb;
					}

expression(left) ::= expression_equal(ee) . {
	left = ee;
}
	expression_equal(left) ::= expression(e1) EQUAL expression(e2) . {
		auto t_e1 = module->getToken<Expression>(e1);
		auto t_e2 = module->getToken<Expression>(e2);
		left = module->createToken<ExpressionEqual>(t_e1, t_e2);
	}

expression(left) ::= expression_type(et) . {
	left = et;
}
	expression_type(left) ::= variable_type(vt) . {
		auto t_vt = module->getToken<VariableType>(vt);
		left = module->createToken<ExpressionType>(t_vt);
	}
expression(left) ::= expression_assign(e) . {
	left = e;
}
	expression_assign(left) ::= expression(ei) ASSIGN expression(e) . {
		auto t_ei = module->getToken<Expression>(ei);
		auto t_e = module->getToken<Expression>(e);
		left = module->createToken<ExpressionAssign>(t_ei, t_e);
	}


variable_type(left) ::= variable_type_simple(vts) . {
	left = vts;
}
	variable_type_simple(left) ::= TYPE(T) . {
		auto t = module->getToken<Token>(T);
		left = module->createToken<VariableType>(t, std::vector<VariableType*>{});
	}
variable_type(left) ::= variable_type_complex(vtc) . {
	left = vtc;
}
	variable_type_complex(left) ::= variable_type_oneparam(vtop) . {
		left = vtop;
	}
		variable_type_oneparam(left) ::= TYPE(T) LRB variable_type(vt) RRB . {
			auto t_vt = module->getToken<VariableType>(vt);
			auto t_T = module->getToken<Token>(T);
			left = module->createToken<VariableType>(t_T, std::vector<VariableType*>{t_vt});
		}
	variable_type_complex(left) ::= variable_type_twoparam(vttp) . {
		left = vttp;
	}
		variable_type_twoparam(left) ::= TYPE(T) LRB variable_type(vt1) COMMA variable_type(vt2) RRB . {
			auto t_vt1 = module->getToken<VariableType>(vt1);
			auto t_vt2 = module->getToken<VariableType>(vt2);
			auto t_T = module->getToken<Token>(T);
			left = module->createToken<VariableType>(t_T, std::vector<VariableType*>{t_vt1, t_vt2});
		}

/* Variable ID */
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
		literal_one_param(left) ::= literal_simple_one_param(lcop) . {
			left = lcop;
		}
			literal_simple_one_param(left) ::= TYPE(T) LSB literal_oneparam_content(loc) RSB . {
				auto t_T = module->getToken<Token>(T);
				auto t_idx = module->createToken<VariableType>(t_T, std::vector<VariableType*>{});
				auto t_vts = module->getToken<VariableType>(t_idx);
				auto t_loc = module->getToken<OneParamContent>(loc);
				left = module->createToken<LiteralOneParam>(t_vts, t_loc->getElements());
			}
		literal_one_param(left) ::= TYPE(T) LRB variable_type(vt) RRB LSB literal_oneparam_content(loc) RSB . {
			auto t_T = module->getToken<Token>(T);
			auto t_vt = module->getToken<VariableType>(vt);
			auto t_idx = module->createToken<VariableType>(t_T, std::vector<VariableType*>{t_vt});
			auto t_vtc = module->getToken<VariableType>(t_idx);
			auto t_loc = module->getToken<OneParamContent>(loc);
			left = module->createToken<LiteralOneParam>(t_vtc, t_loc->getElements());
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
		literal_two_param(left) ::= TYPE(T) LRB variable_type(vt1) COMMA variable_type(vt2) RRB LSB literal_twoparam_content(ltc) RSB . {
			auto t_T = module->getToken<Token>(T);
			auto t_vt1 = module->getToken<VariableType>(vt1);
			auto t_vt2 = module->getToken<VariableType>(vt2);
			auto t_idx = module->createToken<VariableType>(t_T, std::vector<VariableType*>{t_vt1, t_vt2});
			auto t_vtc = module->getToken<VariableType>(t_idx);

			auto t_ltc = module->getToken<TwoParamContent>(ltc);
			left = module->createToken<LiteralTwoParam>(t_vtc, t_ltc->getElements());
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
