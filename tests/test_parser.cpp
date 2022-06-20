#include "test_parser.h"

#include "../module.h"
#include "test_runner.h"

#include <iostream>
#include <map>
#include <string>

using namespace std;

void RunTests(map<string, string> tests)
{
    Module module;
    int cnt = 1;
    int size = tests.size();
    for (const auto& t : tests) {
        cout << warn << "[" << cnt << "/" << size << "]: " << reset;
        try {
            module.run(t.first);
            AssertEqual(module.getRootNode()->toString(), t.second);
            cnt++;
        } catch(const std::runtime_error& ex) {
            cout << warn << "[" << ++cnt << "/" << size << "]: " << reset << ex.what() << endl;
            throw;
        } catch(const std::exception& ex) {
            cout << reset << ex.what() << endl;
            throw;
        }
    }
}

void Test_StatementDefinition_SimpleTypes()
{
    map<string, string> tests = {
        {"Integer a;",                "Integer a"},
        {"String b;",                "String b"},
        {"Float c;",                "Float c"},
    };
    RunTests(tests);
}

void Test_StatementDefinition_ComplexTypes()
{
    map<string, string> tests = {
        {"Vector(Integer) vc_1;",                "Vector(Integer) vc_1"},
        {"Vector(String) vc_2;",                "Vector(String) vc_2"},
        {"Vector(Float) vc_3;",                "Vector(Float) vc_3"},
        {"Map(Integer, Integer) m_1;",                "Map(Integer, Integer) m_1"},
        {"Map(Integer, String) m_2;",                "Map(Integer, String) m_2"},
        {"Vector(Vector(Integer)) vc_4;",                "Vector(Vector(Integer)) vc_4"},
        {"Map(Integer, Map(Integer, Integer)) m_3;",                "Map(Integer, Map(Integer, Integer)) m_3"},
    };
    RunTests(tests);
}
void Test_Statement_Assign_Definition_Simple()
{
    map<string, string> tests = {
        {"Integer i_2 = 1;",                "Integer i_2 = 1"},
        {"String str = \"some string\";",   "String str = \"some string\""},
        {"Float f_1 = 10.5;",               "Float f_1 = 10.5"},
    };
    RunTests(tests);

}
void Test_Statement_Assign_Definition_OneParam()
{
    map<string, string> tests = {
        {"Vector(Integer) vc_1 = Vector(Integer)[];",           "Vector(Integer) vc_1 = Vector(Integer)[]"},
        {"Vector(Integer) vc_1 = Vector(Integer)[100];",        "Vector(Integer) vc_1 = Vector(Integer)[100]"},
        {"Vector(Integer) vc_1 = Vector(Integer)[100, 500];",   "Vector(Integer) vc_1 = Vector(Integer)[100, 500]"},
        {"Vector(Integer) vc_1 = Vector(Integer)[abc];",        "Vector(Integer) vc_1 = Vector(Integer)[abc]"},
        {"Vector(Integer) vc_1 = Vector(Integer)[100, abc, 500];",          "Vector(Integer) vc_1 = Vector(Integer)[100, abc, 500]"},
        {"Vector(String) vc_1 = Vector(String)[\"some string\",];",         "Vector(String) vc_1 = Vector(String)[\"some string\"]"},
        {"Vector(Vector(Integer)) vc_2 = Vector(Vector(Integer))[vc_1];",   "Vector(Vector(Integer)) vc_2 = Vector(Vector(Integer))[vc_1]"},
    };
    RunTests(tests);
}

void Test_Statement_Assign_Definition_TwoParam()
{
    map<string, string> tests = {
        {"Map(Integer, Integer) m_1 = Map(Integer, Integer)[];",                        "Map(Integer, Integer) m_1 = Map(Integer, Integer)[]"},
        {"Map(Integer, Integer) m_1 = Map(Integer, Integer)[100 : abc, yoyo : 300];",   "Map(Integer, Integer) m_1 = Map(Integer, Integer)[100 : abc, yoyo : 300]"},
        {"Map(Integer, Integer) m_1 = Map(Integer, Integer)[100 : abc, yoyo : 300,];",  "Map(Integer, Integer) m_1 = Map(Integer, Integer)[100 : abc, yoyo : 300]"},
        {"Map(Integer, String) m_1 = Map(Integer, String)[100 : \"abc\", yoyo : \"300\"];", "Map(Integer, String) m_1 = Map(Integer, String)[100 : \"abc\", yoyo : \"300\"]"},
        {"Map(Integer, Map(Integer, Integer)) m_2 = Map(Integer, Map(Integer, Integer))[10 : m_1];", "Map(Integer, Map(Integer, Integer)) m_2 = Map(Integer, Map(Integer, Integer))[10 : m_1]"},
    };
    RunTests(tests);
}

void Test_StatementExpression_Simple()
{
    map<string, string> tests = {
        {"i_1 = 2;",                 "i_1 = 2"},
        {"str_1 = \"some string\";", "str_1 = \"some string\""},
        {"f_1 = 2.0;",               "f_1 = 2.0"},
        {"i_2 = a_1;",               "i_2 = a_1"},
    };
    RunTests(tests);
}
void Test_StatementExpression_OneParam()
{
    map<string, string> tests = {
        {"vc_1 = Vector(Integer)[100, i_2];",                "vc_1 = Vector(Integer)[100, i_2]"},
        {"vc_1 = Vector(String)[\"some string\", str_var];", "vc_1 = Vector(String)[\"some string\", str_var]"},
        {"vc_1 = Vector(Float)[100.5, i_2];",                "vc_1 = Vector(Float)[100.5, i_2]"},
    };
    RunTests(tests);
}
void Test_StatementExpression_TwoParam()
{
    map<string, string> tests = {
        {"m_1 = Map(Integer, Integer)[i_1: i_1, 100: i_2, abc : 500];",     "m_1 = Map(Integer, Integer)[i_1 : i_1, 100 : i_2, abc : 500]"},
        {"m_1 = Map(Integer, Integer)[i_1: i_1, 100: i_2, abc : 500];",     "m_1 = Map(Integer, Integer)[i_1 : i_1, 100 : i_2, abc : 500]"},
        {"m_1 = Map(Integer, Map(Integer, String))[i_1: mp1, 100: i_2];",   "m_1 = Map(Integer, Map(Integer, String))[i_1 : mp1, 100 : i_2]"},
    };
    RunTests(tests);
}

void Test_ExpressionCallOrdered()
{
    map<string, string> tests = {
        {"id.some();",                  "id.some()"},
        {"id.some(arg1);",              "id.some(arg1)"},
        {"id.some(arg1, arg2);",        "id.some(arg1, arg2)"},
        {"id.some(arg1, arg2, arg3,);", "id.some(arg1, arg2, arg3)"},
        {"id.some(10, 20);",            "id.some(10, 20)"},
        {"id.some(\"some string\", 20);",   "id.some(\"some string\", 20)"},
        {"id.some(\"some string\", arg2, 100500, 10.5,);",  "id.some(\"some string\", arg2, 100500, 10.5)"},
        {"id.some();",                  "id.some()"},
    };
    RunTests(tests);
}

void Test_ExpressionCallNamed()
{
    map<string, string> tests = {
        {"m_1.insert(first = i_1);",                "m_1.insert(first = i_1)"},
        {"m_2.insert(first = i_1, second = i_2);",  "m_2.insert(first = i_1, second = i_2)"},
        {"m_2.insert(first = i_1, second = i_2, third = i_3);",  "m_2.insert(first = i_1, second = i_2, third = i_3)"},
        {"m_2.insert(first = i_1, second = i_2, third = i_3,);",  "m_2.insert(first = i_1, second = i_2, third = i_3)"},
        {"m_2.insert(first = i_1, second = 100500, third = \"Some String\",);",  "m_2.insert(first = i_1, second = 100500, third = \"Some String\")"},
    };

    RunTests(tests);
}

void Test_StatementExpression_Complex()
{
    map<string, string> tests = {
        {"i_1 = id.some(blabla.method());",     "i_1 = id.some(blabla.method())"},
        // {"i_1 = id.some(abc);",                 "i_1 = id.some(abc)"},
    };
    RunTests(tests);
}

void Test_StatementDefinition_Types()
{
    map<string, string> tests = {
        {"Type t = Integer;",                "Type t = Integer"},
    };
    RunTests(tests);
}

void Test_StatementExpression_Equal()
{
    map<string, string> tests = {
        {"a == b;",                "a == b"},
    };
    RunTests(tests);
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
    tr.RunTest(Test_ExpressionCallNamed, "Parser: Test_ExpressionCallNamed");
    tr.RunTest(Test_StatementExpression_Complex, "Parser: Test_StatementExpression_Complex");
    tr.RunTest(Test_StatementDefinition_Types, "Parser: Test_StatementDefinition_Types");
    tr.RunTest(Test_StatementExpression_Equal, "Parser: Test_StatementExpression_Equal");
}
