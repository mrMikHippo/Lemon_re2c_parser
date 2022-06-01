#include <iostream>

#include "AST/variable_type.h"
#include "AST/literal.h"
#include "AST/expression.h"
#include "AST/statement.h"
#include <string>
#include <vector>
#include "test_runner.h"

using namespace std;

void TestLiteralInteger() {
	LiteralInteger lint({"10"});
	AssertEqual(lint.toString(), "10", " literal integer test");
	cout << ".->\t" << lint.toString() << endl;
}

void TestVariableType() {
	{
		VariableType sub_type({"Integer"}, {});
		VariableType type({"Vector"}, {&sub_type});
		AssertEqual(type.toString(), "Vector(Integer)", " VariableType test"s);
		cout << ".->\t" << type.toString() << endl;
	}
	{
		VariableType sub_type_1({"Integer"}, {});
		VariableType sub_type_2({"Integer"}, {});
		VariableType type({"Map"}, {&sub_type_1, &sub_type_2});
		AssertEqual(type.toString(), "Map(Integer, Integer)", " VariableType test"s);
		cout << "|->\t" << type.toString() << endl;
	}
}

void TestExpressionId() {
	ExpressionId expr({"id"});
	AssertEqual(expr.toString(), "id", " test for id");
	cout << ".->\t" << expr.toString() << endl;
}

void TestLiteralOneParam() {
	LiteralInteger lit_int({"100500"});
	ExpressionLiteral expr_lit(&lit_int);
	ExpressionId expr_id({"id"});

	VariableType sub_type({"Integer"}, {});
	VariableType type({"Vector"}, {&sub_type});

	LiteralOneParam lvec(&type, {&expr_lit, &expr_id});
	AssertEqual(lvec.toString(), "Vector(Integer)[100500, id]");
	cout << ".->\t" << lvec.toString() << endl;
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
	cout << ".->\t" << lmap.toString() << endl;
}

void TestExpressionDot() {
	ExpressionId caller({"id"});
	Token func_name({"some_method"});

	ExpressionDot expr_dot(func_name, &caller);
	AssertEqual(expr_dot.toString(), "id.some_method");
	cout << ".->\t" << expr_dot.toString() << endl;
}

void TestExpressionCallOrdered() {
	ExpressionId caller({"id"});
	Token func_name({"some_method"});

	ExpressionId arg1({"arg1"});
	ExpressionId arg2({"arg2"});

	ExpressionDot expr_dot(func_name, &caller);

	ExpressionCallOrdered expr_co(&expr_dot, {&arg1, &arg2});
	AssertEqual(expr_co.toString(), "id.some_method(arg1, arg2)");
	cout << ".->\t" << expr_co.toString() << endl;
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
	cout << ".->\t" << expr_cn.toString() << endl;
}

void TestExpressionAt() {
	ExpressionId caller({"id"});
	ExpressionId key({"key"});

	ExpressionAt expr(&caller, &key);
	AssertEqual(expr.toString(), "id[key]");
	cout << ".->\t" << expr.toString() << endl;
}

void TestExpressionLiteral() {
	LiteralInteger lit_int({"100500"});
	ExpressionLiteral expr1(&lit_int);

	VariableType sub_type({"Integer"}, {});
	VariableType type({"Vector"}, {&sub_type});

	LiteralOneParam lvec(&type, {&expr1});
	ExpressionLiteral expr_literal(&lvec);

	AssertEqual(expr_literal.toString(), "Vector(Integer)[100500]");
	cout << ".->\t" << expr_literal.toString() << endl;
}

void TestStatementDefinition() {
	
	//Integer a
	{
		VariableType vt({"Integer"}, {});
		Token id({"a"});
		StatementDefinition st(&vt, id);

		AssertEqual(st.toString(), "Integer a");	
		cout << ".->\t" << st.toString() << endl;
	}
	
	//Integer a = 100500
	{
		VariableType vt({"Integer"}, {});
		Token id({"a"});
		LiteralInteger lit_int({"12345"});
		ExpressionLiteral exp_lit(&lit_int);

		StatementDefinition st(&vt, id, &exp_lit);
		AssertEqual(st.toString(), "Integer a = 12345");
		cout << "|->\t" << st.toString() << endl;
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
		cout << "|->\t" << st.toString() << endl;
	}
}

void TestStatementExpression() {

	ExpressionId caller({"id"});
	ExpressionId key({"key"});

	ExpressionAt expr(&caller, &key);

	StatementExpression st(&expr);

	AssertEqual(st.toString(), "id[key]");
	cout << ".->\t" << st.toString() << endl;
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
	cout << ".->\t" << st_list.toString() << endl;
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

	cout << "..................." << endl;
	cout << "Tests: " << tr.getSuccessCount() << "/" << tr.getTotalCount() << endl;
	if (tr.getFailCount())
		cout << "Fail: " << tr.getFailCount() << endl;
	return 0;
}