#include <iostream>

#include "AST/variable_type.h"
#include "AST/literal.h"
#include "AST/expression.h"
#include <string>
#include <vector>
#include "test_runner.h"

using namespace std;

void TestLiteralInteger() {
	LiteralInteger* lint = new LiteralInteger({"10"});
	AssertEqual(lint->toString(), "10", " literal integer test");
	delete lint;
}

void TestVariableType() {
	{
		VariableType sub_type({"Integer"}, {});
		VariableType type({"Vector"}, {&sub_type});
		AssertEqual(type.toString(), "Vector(Integer)", " VariableType test"s);
	}
	{
		VariableType sub_type_1({"Integer"}, {});
		VariableType sub_type_2({"Integer"}, {});
		VariableType type({"Map"}, {&sub_type_1, &sub_type_2});
		AssertEqual(type.toString(), "Map(Integer, Integer)", " VariableType test"s);
	}
}

void TestExpressionId() {
	{
		ExpressionId expr({"100500"});
		AssertEqual(expr.toString(), "100500", " test for 100500");
	}
	{
		ExpressionId expr({"id"});
		AssertEqual(expr.toString(), "id", " test for id");
	}
}

void TestLiteralOneParam() {
	ExpressionId expr1({"100500"});
	ExpressionId expr2({"id"});

	VariableType sub_type({"Integer"}, {});
	VariableType type({"Vector"}, {&sub_type});

	LiteralOneParam lvec(&type, {&expr1, &expr2});
	AssertEqual(lvec.toString(), "Vector(Integer)[100500, id]", "");
}

void TestLiteralTwoParam() {
	ExpressionId key1({"100500"});
	ExpressionId value1({"id"});
	ExpressionId key2({"42"});
	ExpressionId value2({"id2"});

	VariableType sub_type1({"Integer"}, {});
	VariableType sub_type2({"Integer"}, {});
	VariableType type({"Map"}, {&sub_type1, &sub_type2});

	LiteralTwoParam lmap(&type, {{&key1, &value1}, {&key2, &value2}});

	AssertEqual(lmap.toString(), "Map(Integer, Integer)[100500 : id, 42 : id2]", "");
}

int main() {

	TestRunner tr;
	tr.RunTest(TestLiteralInteger, "TestLiteralInteger");
	tr.RunTest(TestVariableType, "TestVariableType");
	tr.RunTest(TestExpressionId, "TestExpressionId");
	tr.RunTest(TestLiteralOneParam, "TestLiteralOneParam");
	tr.RunTest(TestLiteralTwoParam, "TestLiteralTwoParam");

	cout << "..................." << endl;
	cout << "Tests: " << tr.getSuccessCount() << "/" << tr.getTotalCount() << endl;
	if (tr.getFailCount())
		cout << "Fail: " << tr.getFailCount() << endl;
	return 0;
}