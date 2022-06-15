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

void TestParser(TestRunner& tr)
{
    tr.RunTest(Test_StatementDefinition_SimpleTypes, "Parser: Test_StatementDefinition_SimpleTypes");
    tr.RunTest(Test_StatementDefinition_ComplexTypes, "Parser: Test_StatementDefinition_ComplexTypes");
    tr.RunTest(Test_Statement_Assign_Definition_Simple, "Parser: Test_Statement_Assign_Definition_Simple");
    tr.RunTest(Test_Statement_Assign_Definition_OneParam, "Parser: Test_Statement_Assign_Definition_OneParam");
    tr.RunTest(Test_Statement_Assign_Definition_TwoParam, "Parser: Test_Statement_Assign_Definition_TwoParam");
}
