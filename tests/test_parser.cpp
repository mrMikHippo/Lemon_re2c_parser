#include "test_parser.h"

#include "../module.h"
#include "test_runner.h"

#include <iostream>

using namespace std;

void Test_StatementDefinition_SimpleTypes()
{
    Module module;
    module.run("Integer a;");
    AssertEqual(module.getRootNode()->toString(), "Integer a");
    module.run("String b;");
    AssertEqual(module.getRootNode()->toString(), "String b");
    module.run("Float c;");
    AssertEqual(module.getRootNode()->toString(), "Float c");
}

void Test_StatementDefinition_ComplexTypes()
{
    Module module;

    module.run("Vector(Integer) vc_1;");
    AssertEqual(module.getRootNode()->toString(), "Vector(Integer) vc_1");
    module.run("Vector(String) vc_2;");
    AssertEqual(module.getRootNode()->toString(), "Vector(String) vc_2");
    module.run("Vector(Float) vc_3;");
    AssertEqual(module.getRootNode()->toString(), "Vector(Float) vc_3");

    module.run("Map(Integer, Integer) m_1;");
    AssertEqual(module.getRootNode()->toString(), "Map(Integer, Integer) m_1");
    module.run("Map(Integer, String) m_2;");
    AssertEqual(module.getRootNode()->toString(), "Map(Integer, String) m_2");

    module.run("Vector(Vector(Integer)) vc_4;");
    AssertEqual(module.getRootNode()->toString(), "Vector(Vector(Integer)) vc_4");
    module.run("Map(Integer, Map(Integer, Integer)) m_3;");
    AssertEqual(module.getRootNode()->toString(), "Map(Integer, Map(Integer, Integer)) m_3");
}
void Test_Statement_Assign_Definition_Simple()
{
    Module module;
    module.run("Integer i_2 = 1;");
    AssertEqual(module.getRootNode()->toString(), "Integer i_2 = 1");
    module.run("String str = \"some string\";");
    AssertEqual(module.getRootNode()->toString(), "String str = \"some string\"");
    module.run("Float f_1 = 10.5;");
    AssertEqual(module.getRootNode()->toString(), "Float f_1 = 10.5");
}
void Test_Statement_Assign_Definition_OneParam()
{
    Module module;

    module.run("Vector(Integer) vc_1 = Vector(Integer)[];");
    AssertEqual(module.getRootNode()->toString(), "Vector(Integer) vc_1 = Vector(Integer)[]");
    module.run("Vector(Integer) vc_1 = Vector(Integer)[100];");
    AssertEqual(module.getRootNode()->toString(), "Vector(Integer) vc_1 = Vector(Integer)[100]");
    module.run("Vector(Integer) vc_1 = Vector(Integer)[100, 500];");
    AssertEqual(module.getRootNode()->toString(), "Vector(Integer) vc_1 = Vector(Integer)[100, 500]");
    module.run("Vector(Integer) vc_1 = Vector(Integer)[abc];");
    AssertEqual(module.getRootNode()->toString(), "Vector(Integer) vc_1 = Vector(Integer)[abc]");
    module.run("Vector(Integer) vc_1 = Vector(Integer)[100, abc, 500];");
    AssertEqual(module.getRootNode()->toString(), "Vector(Integer) vc_1 = Vector(Integer)[100, abc, 500]");
    module.run("Vector(Integer) vc_1 = Vector(Integer)[100,];");
    AssertEqual(module.getRootNode()->toString(), "Vector(Integer) vc_1 = Vector(Integer)[100]");
    module.run("Vector(Vector(Integer)) vc_2 = Vector(Vector(Integer))[vc_1];");
    AssertEqual(module.getRootNode()->toString(), "Vector(Vector(Integer)) vc_2 = Vector(Vector(Integer))[vc_1]");
}

void Test_Statement_Assign_Definition_TwoParam()
{
    Module module;
    module.run("Map(Integer, Integer) m_1 = Map(Integer, Integer)[];");
    AssertEqual(module.getRootNode()->toString(), "Map(Integer, Integer) m_1 = Map(Integer, Integer)[]");
    module.run("Map(Integer, Integer) m_1 = Map(Integer, Integer)[100 : abc, yoyo : 300];");
    AssertEqual(module.getRootNode()->toString(), "Map(Integer, Integer) m_1 = Map(Integer, Integer)[100 : abc, yoyo : 300]");
    module.run("Map(Integer, Integer) m_1 = Map(Integer, Integer)[100 : abc, yoyo : 300,];");
    AssertEqual(module.getRootNode()->toString(), "Map(Integer, Integer) m_1 = Map(Integer, Integer)[100 : abc, yoyo : 300]");
    module.run("Map(Integer, String) m_1 = Map(Integer, String)[100 : \"abc\", yoyo : \"300\"];");
    AssertEqual(module.getRootNode()->toString(), "Map(Integer, String) m_1 = Map(Integer, String)[100 : \"abc\", yoyo : \"300\"]");
    module.run("Map(Integer, Map(Integer, Integer)) m_2 = Map(Integer, Map(Integer, Integer))[10 : m_1];");
    AssertEqual(module.getRootNode()->toString(), "Map(Integer, Map(Integer, Integer)) m_2 = Map(Integer, Map(Integer, Integer))[10 : m_1]");
    // module.run("");
    // AssertEqual(module.getRootNode()->toString(), "");
    // module.run("");
    // AssertEqual(module.getRootNode()->toString(), "");
}

void Test_StatementExpression_Simple()
{
    Module module;
    module.run("i_1 = 2;");
    AssertEqual(module.getRootNode()->toString(), "i_1 = 2");
    module.run("str_1 = \"some string\";");
    AssertEqual(module.getRootNode()->toString(), "str_1 = \"some string\"");
    module.run("f_1 = 2.0;");
    AssertEqual(module.getRootNode()->toString(), "f_1 = 2.0");

    module.run("i_2 = a_1;");
    AssertEqual(module.getRootNode()->toString(), "i_2 = a_1");
}
void Test_StatementExpression_OneParam()
{
    Module module;

    module.run("vc_1 = Vector(Integer)[100, i_2];");
    AssertEqual(module.getRootNode()->toString(), "vc_1 = Vector(Integer)[100, i_2]");
    module.run("vc_1 = Vector(String)[\"some string\", str_var];");
    AssertEqual(module.getRootNode()->toString(), "vc_1 = Vector(String)[\"some string\", str_var]");
    module.run("vc_1 = Vector(Float)[100.5, i_2];");
    AssertEqual(module.getRootNode()->toString(), "vc_1 = Vector(Float)[100.5, i_2]");
}
void Test_StatementExpression_TwoParam()
{
    Module module;

    module.run("m_1 = Map(Integer, Integer)[i_1: i_1, 100: i_2, abc : 500];");
    AssertEqual(module.getRootNode()->toString(), "m_1 = Map(Integer, Integer)[i_1 : i_1, 100 : i_2, abc : 500]");
    module.run("m_1 = Map(Integer, Integer)[i_1: i_1, 100: i_2, abc : 500];");
    AssertEqual(module.getRootNode()->toString(), "m_1 = Map(Integer, Integer)[i_1 : i_1, 100 : i_2, abc : 500]");
    module.run("m_1 = Map(Integer, Map(Integer, String))[i_1: mp1, 100: i_2];");
    AssertEqual(module.getRootNode()->toString(), "m_1 = Map(Integer, Map(Integer, String))[i_1 : mp1, 100 : i_2]");
    // module.run("");
    // AssertEqual(module.getRootNode()->toString(), "");
}

void Test_ExpressionCallOrdered()
{
    Module module;
    module.run("id.some();");
    AssertEqual(module.getRootNode()->toString(), "id.some()");
    module.run("id.some(arg1);");
    AssertEqual(module.getRootNode()->toString(), "id.some(arg1)");
    module.run("id.some(arg1, arg2);");
    AssertEqual(module.getRootNode()->toString(), "id.some(arg1, arg2)");
}

void Test_StatementExpression_Types()
{
    Module module;
    module.run("Type t = Integer;");
    AssertEqual(module.getRootNode()->toString(), "Type t = Integer");
}

void TestParser(TestRunner& tr)
{
    tr.RunTest(Test_StatementDefinition_SimpleTypes, "Parser: Test_StatementDefinition_SimpleTypes");
    tr.RunTest(Test_StatementDefinition_ComplexTypes, "Parser: Test_StatementDefinition_ComplexTypes");
    tr.RunTest(Test_Statement_Assign_Definition_Simple, "Parser: Test_Statement_Assign_Definition_Simple");
    tr.RunTest(Test_Statement_Assign_Definition_OneParam, "Parser: Test_Statement_Assign_Definition_OneParam");
    tr.RunTest(Test_Statement_Assign_Definition_TwoParam, "Parser: Test_Statement_Assign_Definition_TwoParam");
    tr.RunTest(Test_StatementExpression_Simple, "Parser: Test_StatementExpression_Simple");
    tr.RunTest(Test_StatementExpression_OneParam, "Parser: Test_StatementExpression_OneParam");
    tr.RunTest(Test_StatementExpression_TwoParam, "Parser: Test_StatementExpression_TwoParam");
    tr.RunTest(Test_ExpressionCallOrdered, "Parser: Test_ExpressionCallOrdered");
    // tr.RunTest(Test_StatementExpression_Types, "Parser: Test_StatementExpression_Types");
}
