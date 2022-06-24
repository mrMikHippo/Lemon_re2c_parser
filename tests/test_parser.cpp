#include "test_parser.h"

#include "../module.h"
#include "test_runner.h"
#include "../AST/literal.h"

#include <iostream>
#include <map>
#include <string>

using namespace std;

void RunTests(vector<pair<string, string>> tests)
{
    Module module;
    int size = tests.size();
    for (size_t i = 0; i < size; ++i) {
        cout << warn << "[" << i+1 << "/" << size << "]: " << reset;
        try {
            module.run(tests.at(i).first);
            AssertEqual(module.getRootNode()->toString(), tests.at(i).second);
        } catch(const std::runtime_error& ex) {
            cout << warn << "[" << i+1 << "/" << size << "]: " << reset << ex.what() << endl;
            throw;
        } catch(const std::exception& ex) {
            cout << reset << ex.what() << endl;
            throw;
        }
    }
}

void RunTestsV2(vector<pair<string, Statement*>> tests)
{
    Module module;
    auto size = tests.size();
    for (auto i = 0; i < size; ++i) {
        cout << warn << "[" << i+1 << "/" << size << "]: " << reset;
        try
        {
            auto& test_str = tests.at(i).first;
            auto& statement = tests.at(i).second;
            module.run(test_str);
            AssertEqual(module.getRootNode()->print(), statement->print());
        } catch(const std::runtime_error& ex) {
            cout << warn << "[" << i+1 << "/" << size << "]: " << reset << "Failed!" << endl;
            throw;
        } catch(const std::exception& ex) {
            cout << reset << ex.what() << endl;
            throw;
        }
    }
}

void Test_StatementDefinition_SimpleTypes()
{
    vector<pair<string, string>> tests = {
        {"Integer a;",                "Integer a"},
        {"String b;",                "String b"},
        {"Float c;",                "Float c"},
    };
    RunTests(tests);
}

void Test_StatementDefinition_ComplexTypes()
{
    vector<pair<string, string>> tests = {
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
    vector<pair<string, string>> tests = {
        {"Integer i_2 = 1;",                "Integer i_2 = 1"},
        {"String str = \"some string\";",   "String str = \"some string\""},
        {"Float f_1 = 10.5;",               "Float f_1 = 10.5"},
    };
    RunTests(tests);

}
void Test_Statement_Assign_Definition_OneParam()
{
    vector<pair<string, string>> tests = {
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

void Test_Statement_Assign_Definition_Simple_OneParam()
{
    vector<pair<string, string>> tests = {
        {"Buffer b_1 = Buffer[];",           "Buffer b_1 = Buffer[]"},
        {"Buffer b2 = Buffer[some_var];",        "Buffer b2 = Buffer[some_var]"},
        {"Buffer b2 = Buffer[some_var1, some_var2];",        "Buffer b2 = Buffer[some_var1, some_var2]"},
        {"Buffer b2 = Buffer[var1, var2,];",        "Buffer b2 = Buffer[var1, var2]"},
    };
    RunTests(tests);
}

void Test_Statement_Assign_Definition_TwoParam()
{
    vector<pair<string, string>> tests = {
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
    vector<pair<string, string>> tests = {
        {"i_1 = 2;",                 "i_1 = 2"},
        {"str_1 = \"some string\";", "str_1 = \"some string\""},
        {"f_1 = 2.0;",               "f_1 = 2.0"},
        {"i_2 = a_1;",               "i_2 = a_1"},
    };
    RunTests(tests);
}
void Test_StatementExpression_OneParam()
{
    vector<pair<string, string>> tests = {
        {"vc_1 = Vector(Integer)[100, i_2];",                "vc_1 = Vector(Integer)[100, i_2]"},
        {"vc_1 = Vector(String)[\"some string\", str_var];", "vc_1 = Vector(String)[\"some string\", str_var]"},
        {"vc_1 = Vector(Float)[100.5, i_2];",                "vc_1 = Vector(Float)[100.5, i_2]"},
    };
    RunTests(tests);
}
void Test_StatementExpression_TwoParam()
{
    vector<pair<string, string>> tests = {
        {"m_1 = Map(Integer, Integer)[i_1: i_1, 100: i_2, abc : 500];",     "m_1 = Map(Integer, Integer)[i_1 : i_1, 100 : i_2, abc : 500]"},
        {"m_1 = Map(Integer, Integer)[i_1: i_1, 100: i_2, abc : 500];",     "m_1 = Map(Integer, Integer)[i_1 : i_1, 100 : i_2, abc : 500]"},
        {"m_1 = Map(Integer, Map(Integer, String))[i_1: mp1, 100: i_2];",   "m_1 = Map(Integer, Map(Integer, String))[i_1 : mp1, 100 : i_2]"},
    };
    RunTests(tests);
}

void Test_ExpressionCallOrdered()
{
    // vector<pair<string, string>> tests = {
    //     {"id.some();",                  "id.some()"},
    //     {"id.some(arg1);",              "id.some(arg1)"},
    //     {"id.some(arg1, arg2);",        "id.some(arg1, arg2)"},
    //     {"id.some(arg1, arg2, arg3,);", "id.some(arg1, arg2, arg3)"},
    //     {"id.some(10, 20);",            "id.some(10, 20)"},
    //     {"id.some(\"some string\", 20);",   "id.some(\"some string\", 20)"},
    //     {"id.some(\"some string\", arg2, 100500, 10.5,);",  "id.some(\"some string\", arg2, 100500, 10.5)"},
    // };
    // RunTests(tests);

    string t1 = "id.some();";
    string t2 = "id.some(arg1);";
    string t3 = "id.some(arg1, arg2);";
    string t4 = "id.some(arg1, arg2, arg3,);";

    Token token_id("id");
    Token token_method("some");
    Token token_arg1("arg1");
    Token token_arg2("arg2");
    Token token_arg3("arg3");

    ExpressionId expr_id(&token_id);
    ExpressionDot expr_dot(&token_method, &expr_id);

    ExpressionCallOrdered expr_co_1;
    ExpressionCall expr_call_1(&expr_dot, &expr_co_1);

    ExpressionId expr_arg_id_1(&token_arg1);
    ExpressionCallOrdered expr_co_2({&expr_arg_id_1});
    ExpressionCall expr_call_2(&expr_dot, &expr_co_2);

    ExpressionId expr_arg_id_2(&token_arg2);
    ExpressionCallOrdered expr_co_3({&expr_arg_id_1, &expr_arg_id_2});
    ExpressionCall expr_call_3(&expr_dot, &expr_co_3);

    ExpressionId expr_arg_id_3(&token_arg3);
    ExpressionCallOrdered expr_co_4({&expr_arg_id_1, &expr_arg_id_2, &expr_arg_id_3});
    ExpressionCall expr_call_4(&expr_dot, &expr_co_4);

    StatementExpression st_expr_1(&expr_call_1);
    StatementExpression st_expr_2(&expr_call_2);
    StatementExpression st_expr_3(&expr_call_3);
    StatementExpression st_expr_4(&expr_call_4);

    StatementList st_lst_1({&st_expr_1});
    StatementList st_lst_2({&st_expr_2});
    StatementList st_lst_3({&st_expr_3});
    StatementList st_lst_4({&st_expr_4});

    RunTestsV2({
        {t1, &st_lst_1},
        {t2, &st_lst_2},
        {t3, &st_lst_3},
        {t4, &st_lst_4},
    });
}

void Test_ExpressionCallNamed()
{
    // vector<pair<string, string>> tests = {
    //     {"m_1.insert(first = i_1);",                "m_1.insert(first = i_1)"},
    //     {"m_2.insert(first = i_1, second = i_2);",  "m_2.insert(first = i_1, second = i_2)"},
    //     {"m_2.insert(first = i_1, second = i_2, third = i_3);",  "m_2.insert(first = i_1, second = i_2, third = i_3)"},
    //     {"m_2.insert(first = i_1, second = i_2, third = i_3,);",  "m_2.insert(first = i_1, second = i_2, third = i_3)"},
    //     {"m_2.insert(first = i_1, second = 100500, third = \"Some String\",);",  "m_2.insert(first = i_1, second = 100500, third = \"Some String\")"},
    // };
    //
    // RunTests(tests);

    string t1 = "m_1.insert(first = i_1);";
    string t2 = "m_1.insert(first = 100500, second = i_1,);";
    // string t3 = "m_1.insert(first = i_1, second = i_2, third = i_3,);";
    string t3 = "m_1.insert(first = i_1, second = 100500, third = \"Some String\",);";

    Token token_id("m_1");
    Token token_method("insert");

    Token token_key_1("first");
    Token token_val_1("i_1");
    Token token_key_2("second");
    Token token_val_2("100500");
    Token token_key_3("third");
    Token token_val_3("Some String");

    // m_1.some
    ExpressionId expr_id(&token_id);
    ExpressionDot expr_dot(&token_method, &expr_id);

    // (first = i_1)
    ExpressionId expr_val_1(&token_val_1);
    ExpressionCallNamed expr_cn_1({
        {&token_key_1, &expr_val_1},
    });
    // m_1.some(first = i_1)
    ExpressionCall expr_call_1(&expr_dot, &expr_cn_1);

    // (first = 100500, second = i_1)
    LiteralInteger lit_int(&token_val_2);
    ExpressionLiteral expr_val_2(&lit_int);
    ExpressionCallNamed expr_cn_2({
        {&token_key_1, &expr_val_2},
        {&token_key_2, &expr_val_1},
    });
    // m_1.insert(first = 100500, second = i_1)
    ExpressionCall expr_call_2(&expr_dot, &expr_cn_2);

    // (first = i_1, second = 100500, third = \"Some String\",)
    LiteralString lit_string(&token_val_3);
    ExpressionLiteral expr_val_3(&lit_string);
    ExpressionCallNamed expr_cn_3({
        {&token_key_1, &expr_val_1},
        {&token_key_2, &expr_val_2},
        {&token_key_3, &expr_val_3},
    });
    // m_1.insert(first = i_1, second = 100500, third = \"Some String\",);
    ExpressionCall expr_call_3(&expr_dot, &expr_cn_3);

    StatementExpression st_expr_1(&expr_call_1);
    StatementExpression st_expr_2(&expr_call_2);
    StatementExpression st_expr_3(&expr_call_3);

    StatementList st_lst_1({&st_expr_1});
    StatementList st_lst_2({&st_expr_2});
    StatementList st_lst_3({&st_expr_3});

    RunTestsV2({
        {t1, &st_lst_1},
        {t2, &st_lst_2},
        {t3, &st_lst_3},
    });
}

void Test_StatementExpression_Complex()
{
    vector<pair<string, string>> tests = {
        {"id.some(method.blabla());",                  "id.some(method.blabla())"},
        {"id.some(method.blabla(100));",                  "id.some(method.blabla(100))"},
        {"id.some(method.blabla(100), abc);",                  "id.some(method.blabla(100), abc)"},
        {"i_1 = id.some(blabla.method());",     "i_1 = id.some(blabla.method())"},
        {"i_1 = id.some(arg1, blabla.method());",     "i_1 = id.some(arg1, blabla.method())"},
        {"i_1 = id.some(key = blabla.method());",     "i_1 = id.some(key = blabla.method())"},
        {"i_1 = id.some(key = blabla.method(abc, 100), key2 = 500);",     "i_1 = id.some(key = blabla.method(abc, 100), key2 = 500)"},
        {"i_1 = id.some(key = blabla.method(), key2 = 9999);",     "i_1 = id.some(key = blabla.method(), key2 = 9999)"},
        {"i_1 = id.some(key = blabla.method(abc = 100), key2 = 500);",     "i_1 = id.some(key = blabla.method(abc = 100), key2 = 500)"},
    };
    RunTests(tests);
}

void Test_StatementDefinition_Types()
{
    vector<pair<string, string>> tests = {
        {"Type t = Integer;",           "Type t = Integer"},
        {"Type t = Vector(String);",    "Type t = Vector(String)"},
        {"Type t = Map(Integer, Map(String, Float));",    "Type t = Map(Integer, Map(String, Float))"},
    };
    RunTests(tests);
}

void Test_StatementExpression_Types()
{
    vector<pair<string, string>> tests = {
        {"t = Integer;",           "t = Integer"},
        {"t = Vector(String);",    "t = Vector(String)"},
        {"t = Map(Integer, Map(String, Float));",    "t = Map(Integer, Map(String, Float))"},
    };
    RunTests(tests);
}

void Test_StatementExpression_At()
{
    vector<pair<string, string>> tests = {
        {"id[10];",    "id[10]"},
        {"id[key];",    "id[key]"},
        {"id[vec.at(0)];", "id[vec.at(0)]"},
        {"id.some[key];", "id.some[key]"},
        {"id.some()[key];", "id.some()[key]"},
        {"id.some(abc)[key];", "id.some(abc)[key]"},
        {"id.some(abc = val)[key];", "id.some(abc = val)[key]"},
    };
    RunTests(tests);
}

void Test_StatementExpression_Equal()
{
    vector<pair<string, string>> tests = {
        {"a == b;",                "a == b"},
        {"a == 10;",                "a == 10"},
        {"a == \"string\";",                "a == \"string\""},
        {"vc_1.type() == Vector(Integer);", "vc_1.type() == Vector(Integer)"},
    };
    RunTests(tests);
}

void Test_StatementList()
{
    vector<pair<string, string>> tests = {
        {
            "Integer abc; abc = 10;",
            "Integer abc | abc = 10"
        },
        {
            "Integer abc;\n"
            "abc = 10;",
            "Integer abc | "
            "abc = 10"
        },
        {
            "Integer abc = 10; Vector(Integer) v1 = Vector(Integer)[100500, abc];",
            "Integer abc = 10 | Vector(Integer) v1 = Vector(Integer)[100500, abc]"
        },
        {
            "Integer abc = 10;"
            "Vector(Integer) v1 = Vector(Integer)[100500, abc];"
            "Vector(Integer) v2 = Vector(Integer)[100, 500];",
            "Integer abc = 10 | "
            "Vector(Integer) v1 = Vector(Integer)[100500, abc] | "
            "Vector(Integer) v2 = Vector(Integer)[100, 500]",
        },
        {
            "Integer abc = 10;"
            "Vector(Integer) v1 = Vector(Integer)[100500, abc];"
            "Vector(Integer) v2 = Vector(Integer)[100, 500];"
            "Map(Integer, Vector(Integer)) mp1;"
            "mp1 = Map(Integer, Vector(Integer))["
            "   10 : v1,"
            "   15 : v2"
            "];",
            "Integer abc = 10 | "
            "Vector(Integer) v1 = Vector(Integer)[100500, abc] | "
            "Vector(Integer) v2 = Vector(Integer)[100, 500] | "
            "Map(Integer, Vector(Integer)) mp1 | "
            "mp1 = Map(Integer, Vector(Integer))[10 : v1, 15 : v2]"
        },
    };
    RunTests(tests);
}

void Test()
{
    string t1 = "Integer abc;";
    string t2 = "Float abc;";
    string t3 = "String abc;";

    Token token_int("Integer");
    Token token_float("Float");
    Token token_string("String");

    Token token_id("abc");

    VariableType expr_type_int(&token_int, {});
    VariableType expr_type_float(&token_float, {});
    VariableType expr_type_string(&token_string, {});

    StatementDefinition st_int(&expr_type_int, &token_id);
    StatementDefinition st_float(&expr_type_float, &token_id);
    StatementDefinition st_string(&expr_type_string, &token_id);

    StatementList lst_int(std::vector<Statement*>{&st_int});
    StatementList lst_float(std::vector<Statement*>{&st_float});
    StatementList lst_string(std::vector<Statement*>{&st_string});

    vector<pair<string, Statement*>> tests = {
        {t1, &lst_int},
        {t2, &lst_float},
        {t3, &lst_string}
    };
    RunTestsV2(tests);
}

void TestParser(TestRunner& tr)
{
    tr.RunTest(Test_StatementDefinition_SimpleTypes, "Parser: Test_StatementDefinition_SimpleTypes");
    tr.RunTest(Test_StatementDefinition_ComplexTypes, "Parser: Test_StatementDefinition_ComplexTypes");
    tr.RunTest(Test_Statement_Assign_Definition_Simple, "Parser: Test_Statement_Assign_Definition_Simple");
    tr.RunTest(Test_Statement_Assign_Definition_OneParam, "Parser: Test_Statement_Assign_Definition_OneParam");
    tr.RunTest(Test_Statement_Assign_Definition_Simple_OneParam, "Parser: Test_Statement_Assign_Definition_Simple_OneParam");
    tr.RunTest(Test_Statement_Assign_Definition_TwoParam, "Parser: Test_Statement_Assign_Definition_TwoParam");
    tr.RunTest(Test_StatementExpression_Simple, "Parser: Test_StatementExpression_Simple");
    tr.RunTest(Test_StatementExpression_OneParam, "Parser: Test_StatementExpression_OneParam");
    tr.RunTest(Test_StatementExpression_TwoParam, "Parser: Test_StatementExpression_TwoParam");
    tr.RunTest(Test_ExpressionCallOrdered, "Parser: Test_ExpressionCallOrdered");
    tr.RunTest(Test_ExpressionCallNamed, "Parser: Test_ExpressionCallNamed");
    tr.RunTest(Test_StatementExpression_Complex, "Parser: Test_StatementExpression_Complex");
    tr.RunTest(Test_StatementDefinition_Types, "Parser: Test_StatementDefinition_Types");
    tr.RunTest(Test_StatementExpression_Types, "Parser: Test_StatementExpression_Types");
    tr.RunTest(Test_StatementExpression_At, "Parser: Test_StatementExpression_At");
    tr.RunTest(Test_StatementExpression_Equal, "Parser: Test_StatementExpression_Equal");
    tr.RunTest(Test_StatementList, "Parser: Test_StatementList");

    tr.RunTest(Test, "Parser: Test");
}
