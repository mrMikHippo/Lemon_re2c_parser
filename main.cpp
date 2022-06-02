#include <iostream>

#include "AST/variable_type.h"
#include "AST/literal.h"
#include "AST/expression.h"
#include "AST/statement.h"
#include <string>
#include <vector>
#include "test_runner.h"

using namespace std;

string arrow_end = ".->\t";
string arrow_bet = "|->\t";

void TestLiteralInteger() {
	LiteralInteger lint({"10"});
	AssertEqual(lint.toString(), "10", " literal integer test");
	cout << arrow_end << lint.toString() << endl;
}

void TestVariableType() {
	{
		VariableType sub_type({"Integer"}, {});
		VariableType type({"Vector"}, {&sub_type});
		AssertEqual(type.toString(), "Vector(Integer)", " VariableType test"s);
		cout << arrow_end << type.toString() << endl;
	}
	{
		VariableType sub_type_1({"Integer"}, {});
		VariableType sub_type_2({"Integer"}, {});
		VariableType type({"Map"}, {&sub_type_1, &sub_type_2});
		AssertEqual(type.toString(), "Map(Integer, Integer)", " VariableType test"s);
		cout << arrow_bet << type.toString() << endl;
	}
}

void TestExpressionId() {
	ExpressionId expr({"id"});
	AssertEqual(expr.toString(), "id", " test for id");
	cout << arrow_end << expr.toString() << endl;
}

void TestLiteralOneParam() {
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
	ExpressionId caller({"id"});
	Token func_name({"some_method"});

	ExpressionDot expr_dot(func_name, &caller);
	AssertEqual(expr_dot.toString(), "id.some_method");
	cout << arrow_end << expr_dot.toString() << endl;
}

void TestExpressionCallOrdered() {
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
	ExpressionId caller({"id"});
	ExpressionId key({"key"});

	ExpressionAt expr(&caller, &key);
	AssertEqual(expr.toString(), "id[key]");
	cout << arrow_end << expr.toString() << endl;
}

void TestExpressionLiteral() {
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

	ExpressionId caller({"id"});
	ExpressionId key({"key"});

	ExpressionAt expr(&caller, &key);

	StatementExpression st(&expr);

	AssertEqual(st.toString(), "id[key]");
	cout << arrow_end << st.toString() << endl;
}

void TestStatementList() {
	// First statement
	VariableType vt_first({"Integer"}, {});
	Token id_first({"a"});
	StatementDefinition st_first(&vt_first, id_first);

	//Second Statement
	VariableType vt_sub({"Integer"}, {});
	VariableType vt({"Vector"}, {&vt_sub});
	Token id({"vec"});

	// Vector(Integer) vec = Vector(Integer)[10, 20]
	VariableType vt_sub_2({"Integer"}, {});
	VariableType vt_2({"Vector"}, {&vt_sub});

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

void Test1() {
	//Integer i_1;
	//ID("Integer") ID("i_1") SEMICOLON
	VariableType vt({"Integer"}, {});
	Token id({"i_1"});

	StatementDefinition st(&vt, id);
	AssertEqual(st.toString(), "Integer i_1");
	cout << arrow_end << st.toString() << endl;
}

void Test2() {
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

void Test3() {
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

void Test4() {
	// i_2 = a_1;
	//ID("i_2") ASSIGN ID("a_1") SEMICOLON

	ExpressionId id_left(Token{"i_2"});	
	ExpressionId id_right(Token{"a_1"});

	ExpressionAssign exprA(&id_left, &id_right);
	AssertEqual(exprA.toString(), "i_2 = a_1");	
	cout << arrow_end << exprA.toString() << endl;
}


void Test5() {
	// Vector(Integer) vc_1 = Vector(Integer)[];
	//ID("Vector") LRB ID("Integer") RRB ID("vc_1") ASSIGN ID("Vector") LRB ID("Integer") RRB LSB RSB SEMICOLON

	// VariableType
	throw std::runtime_error("DUMMMY");
}

void Test6() {
	// Vector(Vector(Integer)) vc_2 = Vector(Vector(Integer))[vc_1];
	//ID("Vector") LRB ID("Vector") LRB ID("Integer") RRB RRB ID("vc_2") ASSIGN ID("Vector") LRB ID("Vector") LRB ID("Integer") RRB RRB LSB ID("vc_1") RSB SEMICOLON
	
	throw std::runtime_error("DUMMMY");
}

void Test7() {
	// vc_1 = Vector(Integer)[i_1, i_2];
	//ID("vc_1") ASSIGN ID("Vector") LRB ID("Integer") RRB LSB ID("i_1") COMMA ID("i_2") RRB SEMICOLON
	
	throw std::runtime_error("DUMMMY");
}

void Test8() {
	// vc_1.pushBack(i_1);
	//ID("vc_1") DOT ID("pushBack") LRB ID("i_1") RRB SEMICOLON
	
}

void Test9() {
	// Map(Integer, Integer) m_1 = Map(Integer, Integer)[];
	//ID("Map") LRB ID("Integer") COMMA ID("Integer") RRB ID("m_1") ASSIGN ID("Map") LRB ID("Integer") COMMA ID("Integer") RRB LSB RSB SEMICOLON
	
}
void Test10() {
	// Map(Integer, Map(Integer, Integer)) m_2 = Map(Integer, Map(Integer, Integer))[m_1];
	//ID("Map") LRB ID("Integer") COMMA ID("Map") LRB ID("Integer") COMMA ID("Integer") RRB RRB ID("m_2") ASSIGN ID("Map") LRB ID("Integer") COMMA ID("Map") LRB ID("Integer") COMMA ID("Integer") RRB RRB LSB ID("m_1") RSB SEMICOLON
	
}
void Test11() {
	// m_1 = Map(Integer, Integer)[i_1: i_1, i_2: i_2];
	//ID("m_1") ASSIGN ID("Map") LRB ID("Integer") COMMA ID("Integer") RRB LSB ID("i_1") COLON ID("i_1") COMMA ID("i_2") COLON ID("i_2") RSB SEMICOLON
	
}
void Test12() {
	// m_1.insert(first = i_1, second = i_2);
	//ID("m_1") DOT ID("insert") LRB ID("first") ASSIGN ID("i_1") COMMA ID("second") ASSIGN ID("i_2") RRB SEMICOLON
	
}
void Test13() {
	// Type t = Integer;
	//ID("ID") ID("IDD") ASSIGN ID("ID") SEMICOLON
	
}

void Test14() {
	// vc_1.type() == Vector(Integer);
	//ID("ID") DOT ID("ID") LRB RRB ASSIGN ASSIGN ID("Vector") LRB ID("Integer") RRB SEMICOLON
	
}

int main() {

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
	tr.RunTest(Test1, "Test Assembly of 'Integer i_1'");
	tr.RunTest(Test2, "Test Assembly of 'Integer i_2 = 1'");
	tr.RunTest(Test3, "Test Assembly of 'i_1 = 2'");
	tr.RunTest(Test4, "Test Assembly of 'i_1 = a_1'");
	tr.RunTest(Test5, "Test Assembly of 'Vector(Integer) vc_1 = Vector(Integer)[]'");
	tr.RunTest(Test6, "Test Assembly of 'Vector(Vector(Integer)) vc_2 = Vector(Vector(Integer))[vc_1]'");
	tr.RunTest(Test7, "Test Assembly of 'vc_1 = Vector(Integer)[i_1, i_2]'");


	cout << "..................." << endl;
	cout << "Tests: " << tr.getSuccessCount() << "/" << tr.getTotalCount() << endl;
	if (tr.getFailCount())
		cout << "Fail: " << tr.getFailCount() << endl;
	return 0;
}