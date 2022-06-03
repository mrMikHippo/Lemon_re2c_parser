#include "test_all.h"

#include "../AST/variable_type.h"
#include "../AST/literal.h"
#include "../AST/expression.h"
#include "../AST/statement.h"
#include <string>
#include <vector>
#include "test_runner.h"

using namespace std;

string arrow_end = ".->\t";
string arrow_bet = "|->\t";

bool verbose = true;


void TestLiteralInteger() {
	// 10
	LiteralInteger lint({"10"});
	AssertEqual(lint.toString(), "10", " literal integer test");
	std::cout << arrow_end << lint.toString() << endl;
}

void TestVariableType() {
	{
		// Vector(Integer)
		VariableType sub_type({"Integer"}, {});
		VariableType type({"Vector"}, {&sub_type});
		AssertEqual(type.toString(), "Vector(Integer)", " VariableType test"s);
		cout << arrow_end << type.toString() << endl;
	}
	{
		// Map(Integer, Integer)
		VariableType sub_type_1({"Integer"}, {});
		VariableType sub_type_2({"Integer"}, {});
		VariableType type({"Map"}, {&sub_type_1, &sub_type_2});
		AssertEqual(type.toString(), "Map(Integer, Integer)", " VariableType test"s);
		cout << arrow_bet << type.toString() << endl;
	}
}

void TestExpressionId() {
	// id
	ExpressionId expr({"id"});
	AssertEqual(expr.toString(), "id", " test for id");
	cout << arrow_end << expr.toString() << endl;
}

void TestLiteralOneParam() {
	// Vector(Integer)[100500, id]
	LiteralInteger lit_int({"100500"});
	ExpressionLiteral expr_lit(&lit_int);
	ExpressionId expr_id({"id"});

	VariableType sub_type({"Integer"}, {});
	VariableType type({"Vector"}, {&sub_type});

	LiteralOneParam lvec(&type, {&expr_lit, &expr_id});
	AssertEqual(lvec.toString(), "Vector(Integer)[100500, id]");
	cout << arrow_end << lvec.toString() << endl;
}

void TestLiteralTwoParam() {
	// Map(Integer, Integer)[100500 : id, 42 : id2]
	LiteralInteger lit_int_1({"100500"});
	ExpressionLiteral key1(&lit_int_1);
	ExpressionId value1({"id"});

	LiteralInteger lit_int_2({"42"});
	ExpressionLiteral key2(&lit_int_2);
	ExpressionId value2({"id2"});

	VariableType sub_type1({"Integer"}, {});
	VariableType sub_type2({"Integer"}, {});
	VariableType type({"Map"}, {&sub_type1, &sub_type2});

	LiteralTwoParam lmap(&type, {{&key1, &value1}, {&key2, &value2}});

	AssertEqual(lmap.toString(), "Map(Integer, Integer)[100500 : id, 42 : id2]");
	cout << arrow_end << lmap.toString() << endl;
}

void TestExpressionDot() {
	// id.some_method
	ExpressionId caller({"id"});
	Token func_name({"some_method"});

	ExpressionDot expr_dot(func_name, &caller);
	AssertEqual(expr_dot.toString(), "id.some_method");
	cout << arrow_end << expr_dot.toString() << endl;
}

void TestExpressionCallOrdered() {
	// id.some_method(arg1, arg2)
	ExpressionId caller({"id"});
	Token func_name({"some_method"});

	ExpressionId arg1({"arg1"});
	ExpressionId arg2({"arg2"});

	ExpressionDot expr_dot(func_name, &caller);

	ExpressionCallOrdered expr_co(&expr_dot, {&arg1, &arg2});
	AssertEqual(expr_co.toString(), "id.some_method(arg1, arg2)");
	cout << arrow_end << expr_co.toString() << endl;
}

void TestExpressionCallNamed() {
	
	//id.some(key = arg1, key2 = arg2)

	ExpressionId caller({"id"});
	Token func_name({"some_method"});

	// Expression* callee
	ExpressionDot expr_dot(func_name, &caller);

	// std::vector<std::pair<Token*, Expression*>>
	Token key1({"key1"});
	Token key2({"key2"});
	ExpressionId val1({"arg1"});
	ExpressionId val2({"arg2"});

	ExpressionCallNamed expr_cn(&expr_dot, {
			make_pair<Token*, Expression*>(&key1, &val1),
			make_pair<Token*, Expression*>(&key2, &val2)
		}
	);

	AssertEqual(expr_cn.toString(), "id.some_method(key1 = arg1, key2 = arg2)");
	cout << arrow_end << expr_cn.toString() << endl;
}

void TestExpressionAt() {
	// id[key]
	ExpressionId caller({"id"});
	ExpressionId key({"key"});

	ExpressionAt expr(&caller, &key);
	AssertEqual(expr.toString(), "id[key]");
	cout << arrow_end << expr.toString() << endl;
}

void TestExpressionLiteral() {
	// Vector(Integer)[100500]
	LiteralInteger lit_int({"100500"});
	ExpressionLiteral expr1(&lit_int);

	VariableType sub_type({"Integer"}, {});
	VariableType type({"Vector"}, {&sub_type});

	LiteralOneParam lvec(&type, {&expr1});
	ExpressionLiteral expr_literal(&lvec);

	AssertEqual(expr_literal.toString(), "Vector(Integer)[100500]");
	cout << arrow_end << expr_literal.toString() << endl;
}

void TestStatementDefinition() {
	
	//Integer a
	{
		VariableType vt({"Integer"}, {});
		Token id({"a"});
		StatementDefinition st(&vt, id);

		AssertEqual(st.toString(), "Integer a");	
		cout << arrow_end << st.toString() << endl;
	}
	
	//Integer a = 100500
	{
		VariableType vt({"Integer"}, {});
		Token id({"a"});
		LiteralInteger lit_int({"12345"});
		ExpressionLiteral exp_lit(&lit_int);

		StatementDefinition st(&vt, id, &exp_lit);
		AssertEqual(st.toString(), "Integer a = 12345");
		cout << arrow_bet << st.toString() << endl;
	}
	
	// Vector(Integer) vec = Vector(Integer)[10, 20];
	{
		// Vector(Integer) vec
		VariableType vt_sub({"Integer"}, {});
		VariableType vt({"Vector"}, {&vt_sub});
		Token id({"vec"});

		// Vector(Integer)[10, 20]
		VariableType vt_sub_2({"Integer"}, {});
		VariableType vt_2({"Vector"}, {&vt_sub});

		LiteralInteger l_int_1({"10"});
		LiteralInteger l_int_2({"20"});
		ExpressionLiteral exp_l_1(&l_int_1);
		ExpressionLiteral exp_l_2(&l_int_2);

		LiteralOneParam lit_one_param(&vt_2, {&exp_l_1, &exp_l_2});
		ExpressionLiteral expr_lit(&lit_one_param);

		StatementDefinition st(&vt, id, &expr_lit);

		AssertEqual(st.toString(), "Vector(Integer) vec = Vector(Integer)[10, 20]");
		cout << arrow_bet << st.toString() << endl;
	}
}

void TestStatementExpression() {
	// id == key
	ExpressionId left({"id"});
	ExpressionId right({"key"});

	ExpressionEqual expr(&left, &right);

	StatementExpression st(&expr);

	AssertEqual(st.toString(), "id == key");
	cout << arrow_end << st.toString() << endl;
}

void TestStatementList() {
	// First statement: Integer a
	VariableType vt_first({"Integer"}, {});
	Token id_first({"a"});
	StatementDefinition st_first(&vt_first, id_first);

	//Second Statement: Vector(Integer)
	VariableType vt_sub({"Integer"}, {});
	VariableType vt({"Vector"}, {&vt_sub});
	Token id({"vec"});

	// Vector(Integer) vec = Vector(Integer)[10, 20]
	VariableType vt_sub_2({"Integer"}, {});
	VariableType vt_2({"Vector"}, {&vt_sub});

	// Vector(Integer)[10,20]
	LiteralInteger l_int_1({"10"});
	LiteralInteger l_int_2({"20"});
	ExpressionLiteral exp_l_1(&l_int_1);
	ExpressionLiteral exp_l_2(&l_int_2);

	LiteralOneParam lit_one_param(&vt_2, {&exp_l_1, &exp_l_2});
	ExpressionLiteral expr_lit(&lit_one_param);

	StatementDefinition st_sec(&vt, id, &expr_lit);

	StatementList st_list({&st_first, &st_sec});

	AssertEqual(st_list.toString(), "Integer a, Vector(Integer) vec = Vector(Integer)[10, 20]");
	cout << arrow_end << st_list.toString() << endl;
}

void TestDefinition() {
	//Integer i_1;
	VariableType vt({"Integer"}, {});
	Token id({"i_1"});

	StatementDefinition st(&vt, id);
	AssertEqual(st.toString(), "Integer i_1");
	cout << arrow_end << st.toString() << endl;
}

void TestDefinitionInitialization() {
	// Integer i_2 = 1;
	//ID("Integer") ID("i_2") ASSIGN INTEGER("1") SEMICOLON
	VariableType vt({"Integer"}, {});
	Token id({"i_2"});

	LiteralInteger lit_int({"1"});
	ExpressionLiteral expr(&lit_int);

	StatementDefinition st(&vt, id, &expr);
	AssertEqual(st.toString(), "Integer i_2 = 1");
	cout << arrow_end << st.toString() << endl;
}

void TestIdAssignmentLiteral() {
	// i_1 = 2;
	//ID("i_1") ASSIGN INTEGER("2") SEMICOLON
	ExpressionId id(Token{"i_1"});

	LiteralInteger lit_int(Token{"2"});
	ExpressionLiteral elit(&lit_int);

	// i_1 = 2
	ExpressionAssign exprA = ExpressionAssign(&id, &elit);
	AssertEqual(exprA.toString(), "i_1 = 2");
	cout << arrow_end << exprA.toString() << endl;
}

void TestIdAssignmentId() {
	// i_2 = a_1;
	//ID("i_2") ASSIGN ID("a_1") SEMICOLON

	ExpressionId id_left(Token{"i_2"});	
	ExpressionId id_right(Token{"a_1"});

	ExpressionAssign exprA(&id_left, &id_right);
	AssertEqual(exprA.toString(), "i_2 = a_1");	
	cout << arrow_end << exprA.toString() << endl;
}


void TestVTypeOneParamInitialization() {
	// Vector(Integer) vc_1 = Vector(Integer)[];
	//ID("Vector") LRB ID("Integer") RRB ID("vc_1") ASSIGN ID("Vector") LRB ID("Integer") RRB LSB RSB SEMICOLON

	VariableType sub_type({"Integer"}, {});
	VariableType type({"Vector"}, {&sub_type});
	Token id({"vc_1"});

	VariableType sub_type_right({"Integer"}, {});
	VariableType type_right({"Vector"}, {&sub_type_right});
	LiteralOneParam one_param_right(&type_right, {});
	ExpressionLiteral expr_right(&one_param_right);

	StatementDefinition st_def(&type, id, &expr_right);

	AssertEqual(st_def.toString(), "Vector(Integer) vc_1 = Vector(Integer)[]");
	cout << arrow_end << st_def.toString() << endl;
}

void TestVTypeVTypeOneParamInitialization() {
	// Vector(Vector(Integer)) vc_2 = Vector(Vector(Integer))[vc_1];
	//ID("Vector") LRB ID("Vector") LRB ID("Integer") RRB RRB ID("vc_2") ASSIGN ID("Vector") LRB ID("Vector") LRB ID("Integer") RRB RRB LSB ID("vc_1") RSB SEMICOLON

	// Create Vector(Vector(Integer))
	VariableType vc_sub_sub_type({"Integer"}, {});
	VariableType vc_sub_type({"Vector"}, {&vc_sub_sub_type});
	VariableType vc_type({"Vector"}, {&vc_sub_type});

	// Create token vc_1
	Token vc_1_token({"vc_1"});
	ExpressionId vc_1_id(vc_1_token);

	LiteralOneParam vc_literal(&vc_type, {&vc_1_id});
	ExpressionLiteral vc_exp(&vc_literal);

	// Create left side
	VariableType ltype({"Vector"}, {&vc_sub_type});

	Token id_token({"vc_2"});
	StatementDefinition st_def(&ltype, id_token, &vc_exp);

	AssertEqual(st_def.toString(), "Vector(Vector(Integer)) vc_2 = Vector(Vector(Integer))[vc_1]");
	cout << arrow_end << st_def.toString() << endl;
}

void TestIdAssignmentExpression() {
	// vc_1 = Vector(Integer)[i_1, i_2];
	//ID("vc_1") ASSIGN ID("Vector") LRB ID("Integer") RRB LSB ID("i_1") COMMA ID("i_2") RRB SEMICOLON

	Token left_token({"vc_1"});
	ExpressionId left_id(left_token);

	VariableType sub_type({"Integer"}, {});
	VariableType type({"Vector"}, {&sub_type});

	ExpressionId first(Token{"i_1"});
	ExpressionId sec(Token{"i_2"});

	LiteralOneParam vec(&type, {&first, &sec});
	ExpressionLiteral assigned_vector(&vec);

	ExpressionAssign exprA(&left_id, &assigned_vector);

	AssertEqual(exprA.toString(), "vc_1 = Vector(Integer)[i_1, i_2]");

	cout << arrow_end << exprA.toString() << endl;
}

void TestExpressionCallPushBack() {
	// vc_1.pushBack(i_1);
	//ID("vc_1") DOT ID("pushBack") LRB ID("i_1") RRB SEMICOLON

	ExpressionId callee(Token{"vc_1"});
	ExpressionId id_to_push(Token{"i_1"});

	Token method_name({"pushBack"});

	ExpressionDot expr(method_name, &callee);

	ExpressionCallOrdered expr_co(&expr, {&id_to_push});

	AssertEqual(expr_co.toString(), "vc_1.pushBack(i_1)");
	cout << arrow_end << expr_co.toString() << endl;
}

void TestStatementTwoParamInitializationEmpty() {
	// Map(Integer, Integer) m_1 = Map(Integer, Integer)[];
	//ID("Map") LRB ID("Integer") COMMA ID("Integer") RRB ID("m_1") ASSIGN ID("Map") LRB ID("Integer") COMMA ID("Integer") RRB LSB RSB SEMICOLON
	
	VariableType sub_type1({"Integer"}, {});
	VariableType sub_type2({"Integer"}, {});
	VariableType type_left({"Map"}, {&sub_type1, &sub_type2});
	Token id({"m_1"});

	VariableType rtype({"Map"}, {&sub_type1, &sub_type2});

	LiteralOneParam rliteral(&rtype, {});
	ExpressionLiteral rexp_lit(&rliteral);

	StatementDefinition st(&type_left, id, &rexp_lit);

	AssertEqual(st.toString(), "Map(Integer, Integer) m_1 = Map(Integer, Integer)[]");
	cout << arrow_end << st.toString() << endl;

}

void TestStatementTwoParamInitializationWithValue() {
	// Map(Integer, Map(Integer, Integer)) m_2 = Map(Integer, Map(Integer, Integer))[10 : m_1];
	//ID("Map") LRB ID("Integer") COMMA ID("Map") LRB ID("Integer") COMMA ID("Integer") RRB RRB ID("m_2") ASSIGN ID("Map") LRB ID("Integer") COMMA ID("Map") LRB ID("Integer") COMMA ID("Integer") RRB RRB LSB ID("m_1") RSB SEMICOLON
	VariableType int_type(Token{"Integer"}, {});
	VariableType sec_type_left(Token{"Map"}, {&int_type, &int_type});
	VariableType ltype(Token{"Map"}, {&int_type, &sec_type_left});

	VariableType rtype(Token{"Map"}, {&int_type, &sec_type_left});

	LiteralInteger rint_literal(Token{"10"});
	ExpressionLiteral rint(&rint_literal);

	ExpressionId r_id(Token{"m_1"});
	LiteralTwoParam rtp(&rtype, {make_pair(&rint, &r_id)});
	ExpressionLiteral rmap(&rtp);

	Token id({"m_2"});
	StatementDefinition st(&ltype, id, &rmap);

	AssertEqual(st.toString(), "Map(Integer, Map(Integer, Integer)) m_2 = Map(Integer, Map(Integer, Integer))[10 : m_1]");
	cout << arrow_end << st.toString() << endl;
}

void TestIdAssignmentExpressionTwoParam() {
	// m_1 = Map(Integer, Integer)[i_1: i_1, i_2: i_2];
	//ID("m_1") ASSIGN ID("Map") LRB ID("Integer") COMMA ID("Integer") RRB LSB ID("i_1") COLON ID("i_1") COMMA ID("i_2") COLON ID("i_2") RSB SEMICOLON
	ExpressionId id(Token{"m_1"});
	VariableType int_type(Token{"Integer"}, {});
	VariableType map_type(Token{"Map"}, {&int_type, &int_type});

	ExpressionId key1(Token{"i_1"});
	ExpressionId val1(Token{"j_1"});
	ExpressionId key2(Token{"i_2"});
	ExpressionId val2(Token{"j_2"});

	LiteralTwoParam map_container(&map_type, {{&key1, &val1}, {&key2, &val2}});
	ExpressionLiteral map_expr_cont(&map_container);

	ExpressionAssign exprA(&id, &map_expr_cont);
	
	AssertEqual(exprA.toString(), "m_1 = Map(Integer, Integer)[i_1 : j_1, i_2 : j_2]");
	cout << arrow_end << exprA.toString() << endl;
}

void TestExpressionDotCallNamed() {
	// m_1.insert(first = i_1, second = i_2);
	//ID("m_1") DOT ID("insert") LRB ID("first") ASSIGN ID("i_1") COMMA ID("second") ASSIGN ID("i_2") RRB SEMICOLON

	ExpressionId callee(Token{"m_1"});
	Token method_name({"insert"});

	ExpressionDot expr_dot(method_name, &callee);

	Token first({"first"});
	ExpressionId first_val({"i_1"});
	Token second({"second"});
	ExpressionId second_val({"i_2"});

	ExpressionCallNamed expr_cn(&expr_dot, {{&first, &first_val}, {&second, &second_val}});

	AssertEqual(expr_cn.toString(), "m_1.insert(first = i_1, second = i_2)");
	cout << arrow_end << expr_cn.toString() << endl;
}

void TestTypeInitialization() {
	// Type type_var = Integer;
	//ID("ID") ID("IDD") ASSIGN ID("ID") SEMICOLON

	VariableType vtype({"Type"}, {});
	// LiteralType lltype(&vtype);
	// ExpressionLiteral eltype(&lltype);

	Token id({"type_var"});

	VariableType t_int({"Integer"}, {});
	LiteralType ll_type_int(&t_int);
	ExpressionLiteral el_type_int(&ll_type_int);

	// ???
	StatementDefinition st(&vtype, id, &el_type_int);
	AssertEqual(st.toString(), "Type type_var = Integer");
	cout << arrow_end << st.toString() << endl;
}

void TestExprDotStatementExpressionVarType() {
	// vc_1.type() == Vector(Integer);
	//ID("ID") DOT ID("ID") LRB RRB ASSIGN ASSIGN ID("Vector") LRB ID("Integer") RRB SEMICOLON

	Token method_name({"type"});
	ExpressionId callee(Token{"vc_1"});
	ExpressionDot expr_dot(method_name, &callee);
	ExpressionCallOrdered expr_co(&expr_dot, {});

	VariableType sub_vt({"Integer"}, {});
	VariableType vt({"Vector"}, {&sub_vt});
	LiteralType vt_literal(&vt);

	ExpressionLiteral vt_el(&vt_literal);

	ExpressionEqual expr_eq_eq(&expr_co, &vt_el);

	StatementExpression st_expr(&expr_eq_eq);
										// exprCall exprDOt exprId  | expr tpye
	AssertEqual(st_expr.toString(), "vc_1.type() == Vector(Integer)");
	cout << arrow_end << st_expr.toString() << endl;
}

void TestAll() {
	TestRunner tr;
	tr.RunTest(TestLiteralInteger, "TestLiteralInteger");
	tr.RunTest(TestVariableType, "TestVariableType");
	tr.RunTest(TestExpressionId, "TestExpressionId");
	tr.RunTest(TestLiteralOneParam, "TestLiteralOneParam");
	tr.RunTest(TestLiteralTwoParam, "TestLiteralTwoParam");
	tr.RunTest(TestExpressionDot, "TestExpressionDot");
	tr.RunTest(TestExpressionCallOrdered, "TestExpressionCallOrdered");
	tr.RunTest(TestExpressionCallNamed, "TestExpressionCallNamed");
	tr.RunTest(TestExpressionAt, "TestExpressionAt");
	tr.RunTest(TestExpressionLiteral, "TestExpressionLiteral");
	tr.RunTest(TestStatementDefinition, "TestStatementDefinition");
	tr.RunTest(TestStatementExpression, "TestStatementExpression");
	tr.RunTest(TestStatementList, "TestStatementList");
	tr.RunTest(TestDefinition, "TestDefinition");
	tr.RunTest(TestDefinitionInitialization, "TestDefinitionInitialization");
	tr.RunTest(TestIdAssignmentLiteral, "TestIdAssignmentLiteral");
	tr.RunTest(TestIdAssignmentId, "TestIdAssignmentId");
	tr.RunTest(TestVTypeOneParamInitialization, "TestVTypeOneParamInitialization");
	tr.RunTest(TestVTypeVTypeOneParamInitialization, "TestVTypeVTypeOneParamInitialization");
	tr.RunTest(TestIdAssignmentExpression, "TestIdAssignmentExpression");
	tr.RunTest(TestExpressionCallPushBack, "TestExpressionCallPushBack");
	tr.RunTest(TestStatementTwoParamInitializationEmpty, "TestStatementTwoParamInitializationEmpty");
	tr.RunTest(TestStatementTwoParamInitializationWithValue, "TestStatementTwoParamInitializationWithValue");
	tr.RunTest(TestIdAssignmentExpressionTwoParam, "TestIdAssignmentExpressionTwoParam");
	tr.RunTest(TestExpressionDotCallNamed, "TestExpressionDotCallNamed");
	tr.RunTest(TestTypeInitialization, "TestTypeInitialization");
	tr.RunTest(TestExprDotStatementExpressionVarType, "TestExprDotStatementExpressionVarType");

	cout << "..................." << endl;
	cout << "Tests: " << tr.getSuccessCount() << "/" << tr.getTotalCount() << endl;
	if (tr.getFailCount())
		cout << "Fail: " << tr.getFailCount() << endl;
}