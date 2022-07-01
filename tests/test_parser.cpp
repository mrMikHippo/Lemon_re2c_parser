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
        auto& test_str = tests.at(i).first;
        auto& statement = tests.at(i).second;
        try
        {
            module.run(test_str);
            AssertEqual(module.getRootNode()->print(), statement->print());
        } catch(const std::runtime_error& ex) {
            cout << warn << "[" << i+1 << "/" << size << "]: " << reset << "Failed!" << endl;
            throw;
        } catch(const std::exception& ex) {
            cout << reset << "'" << test_str << "' - " << ex.what() << endl;
            throw;
        }
    }
}

void Test_StatementDefinition_SimpleTypes()
{
    // vector<pair<string, string>> tests = {
    //     {"Integer a;",                "Integer a"},
    //     {"String b;",                "String b"},
    //     {"Float c;",                "Float c"},
    // };
    // RunTests(tests);
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

    StatementList lst_int({&st_int});
    StatementList lst_float({&st_float});
    StatementList lst_string({&st_string});

    RunTestsV2({
        {t1, &lst_int},
        {t2, &lst_float},
        {t3, &lst_string}
    });
}

void Test_StatementDefinition_ComplexTypes()
{
    // vector<pair<string, string>> tests = {
    //     {"Vector(Integer) vc_1;",                "Vector(Integer) vc_1"},
    //     {"Vector(String) vc_2;",                "Vector(String) vc_2"},
    //     {"Vector(Float) vc_3;",                "Vector(Float) vc_3"},
    //     {"Map(Integer, Integer) m_1;",                "Map(Integer, Integer) m_1"},
    //     {"Map(Integer, String) m_2;",                "Map(Integer, String) m_2"},
    //     {"Vector(Vector(Integer)) vc_4;",                "Vector(Vector(Integer)) vc_4"},
    //     {"Map(Integer, Map(Integer, Integer)) m_3;",                "Map(Integer, Map(Integer, Integer)) m_3"},
    // };
    // RunTests(tests);

    string t1 = "Vector(Integer) cont;";
    string t2 = "Map(Integer, Integer) cont;";
    string t3 = "Map(Integer, String) cont;";
    string t4 = "Vector(Vector(Integer)) cont;";
    string t5 = "Map(Integer, Map(Integer, Integer)) cont;";

    Token token_int("Integer");
    Token token_string("String");
    Token token_vector("Vector");
    Token token_map("Map");

    Token token_id("cont");

    VariableType var_type_int(&token_int, {});
    VariableType var_type_string(&token_string, {});

    VariableType var_type_vector(&token_vector, {&var_type_int});
    VariableType var_type_map_1(&token_map, {&var_type_int, &var_type_int});
    VariableType var_type_map_2(&token_map, {&var_type_int, &var_type_string});
    VariableType var_type_vector_vec(&token_vector, {&var_type_vector});
    VariableType var_type_map_map(&token_map, {&var_type_int, &var_type_map_1});

    StatementDefinition st_vector(&var_type_vector, &token_id);
    StatementDefinition st_map_1(&var_type_map_1, &token_id);
    StatementDefinition st_map_2(&var_type_map_2, &token_id);
    StatementDefinition st_vector_vec(&var_type_vector_vec, &token_id);
    StatementDefinition st_map_map(&var_type_map_map, &token_id);

    StatementList lst_vector({&st_vector});
    StatementList lst_map_1({&st_map_1});
    StatementList lst_map_2({&st_map_2});
    StatementList lst_vector_vec({&st_vector_vec});
    StatementList lst_map_map({&st_map_map});

    RunTestsV2({
        {t1, &lst_vector},
        {t2, &lst_map_1},
        {t3, &lst_map_2},
        {t4, &lst_vector_vec},
        {t5, &lst_map_map},
    });
}

void Test_Statement_Assign_Definition_Simple()
{
    // vector<pair<string, string>> tests = {
    //     {"Integer i_2 = 1;",                "Integer i_2 = 1"},
    //     {"String str = \"some string\";",   "String str = \"some string\""},
    //     {"Float f_1 = 10.5;",               "Float f_1 = 10.5"},
    // };
    // RunTests(tests);

    string t1 = "Integer abc = 1;";
    string t2 = "String abc = \"some string\";";
    string t3 = "Float abc = 10.5;";

    Token token_int("Integer");
    Token token_string("String");
    Token token_float("Float");

    Token token_id("abc");

    VariableType expr_type_int(&token_int, {});
    VariableType expr_type_float(&token_float, {});
    VariableType expr_type_string(&token_string, {});

    LiteralInteger lit_int(new Token("1"));
    ExpressionLiteral expr_lit_int(&lit_int);

    LiteralString lit_str(new Token("\"some string\""));
    ExpressionLiteral expr_lit_str(&lit_str);

    LiteralFloat lit_float(new Token("10.5"));
    ExpressionLiteral expr_lit_float(&lit_float);

    StatementDefinition st_int(&expr_type_int, &token_id, &expr_lit_int);
    StatementDefinition st_string(&expr_type_string, &token_id, &expr_lit_str);
    StatementDefinition st_float(&expr_type_float, &token_id, &expr_lit_float);

    StatementList lst_int({&st_int});
    StatementList lst_string({&st_string});
    StatementList lst_float({&st_float});

    RunTestsV2({
        {t1, &lst_int},
        {t2, &lst_string},
        {t3, &lst_float},
    });
}
void Test_Statement_Assign_Definition_OneParam()
{
    // throw std::runtime_error(" DUMMY");
    // vector<pair<string, string>> tests = {
    //     {"Vector(Integer) vc_1 = Vector(Integer)[];",           "Vector(Integer) vc_1 = Vector(Integer)[]"},
    //     {"Vector(Integer) vc_1 = Vector(Integer)[100];",        "Vector(Integer) vc_1 = Vector(Integer)[100]"},
    //     {"Vector(Integer) vc_1 = Vector(Integer)[100, 500];",   "Vector(Integer) vc_1 = Vector(Integer)[100, 500]"},
    //     {"Vector(Integer) vc_1 = Vector(Integer)[abc];",        "Vector(Integer) vc_1 = Vector(Integer)[abc]"},
    //     {"Vector(Integer) vc_1 = Vector(Integer)[100, abc, 500];",          "Vector(Integer) vc_1 = Vector(Integer)[100, abc, 500]"},
    //     {"Vector(String) vc_1 = Vector(String)[\"some string\",];",         "Vector(String) vc_1 = Vector(String)[\"some string\"]"},
    //     {"Vector(Vector(Integer)) vc_2 = Vector(Vector(Integer))[vc_1];",   "Vector(Vector(Integer)) vc_2 = Vector(Vector(Integer))[vc_1]"},
    // };
    // RunTests(tests);

    string t1 = "Vector(Integer) vc_1 = Vector(Integer)[];";
    string t2 = "Vector(Integer) vc_1 = Vector(Integer)[100];";
    string t3 = "Vector(Integer) vc_1 = Vector(Integer)[100, 500];";
    string t4 = "Vector(Integer) vc_1 = Vector(Integer)[abc];";
    string t5 = "Vector(Integer) vc_1 = Vector(Integer)[100, abc, 500];";
    string t6 = "Vector(String) vc_1 = Vector(String)[\"some string\",];";
    string t7 = "Vector(Vector(Integer)) vc_1 = Vector(Vector(Integer))[v2];";

    Token token_int("Integer");
    Token token_string("String");
    Token token_vector("Vector");

    Token token_id("vc_1");

    VariableType var_type_int(&token_int, {});
    VariableType var_type_string(&token_string, {});

    VariableType var_type_vector_int(&token_vector, {&var_type_int});
    VariableType var_type_vector_str(&token_vector, {&var_type_string});
    VariableType var_type_vector_vec(&token_vector, {&var_type_vector_int});

    // Vector(Integer)[];
    LiteralOneParam lit_op_1(&var_type_vector_int, {});
    ExpressionLiteral l1(&lit_op_1);

    // Vector(Integer)[100];
    LiteralInteger lit_int_100(new Token("100"));
    ExpressionLiteral expr_lit_int_100(&lit_int_100);
    LiteralOneParam lit_op_2(&var_type_vector_int, {&expr_lit_int_100});
    ExpressionLiteral l2(&lit_op_2);

    // Vector(Integer)[100, 500];
    LiteralInteger lit_int_500(new Token("500"));
    ExpressionLiteral expr_lit_int_500(&lit_int_500);
    LiteralOneParam lit_op_3(&var_type_vector_int, {&expr_lit_int_100, &expr_lit_int_500});
    ExpressionLiteral l3(&lit_op_3);

    // Vector(Integer)[abc];
    ExpressionId expr_id_abc(new Token("abc"));
    LiteralOneParam lit_op_4(&var_type_vector_int, {&expr_id_abc});
    ExpressionLiteral l4(&lit_op_4);

    // Vector(Integer)[100, abc, 500];
    LiteralOneParam lit_op_5(&var_type_vector_int, {&expr_lit_int_100, &expr_id_abc, &expr_lit_int_500});
    ExpressionLiteral l5(&lit_op_5);

    // Vector(String)[\"some string\",];
    LiteralString lit_string(new Token("\"some string\""));
    ExpressionLiteral expr_lit_string(&lit_string);
    LiteralOneParam lit_op_6(&var_type_vector_str, {&expr_lit_string});
    ExpressionLiteral l6(&lit_op_6);

    // Vector(Vector(Integer))[vc_1];
    ExpressionId v2(new Token("v2"));
    LiteralOneParam lit_op_7(&var_type_vector_vec, {&v2});
    ExpressionLiteral l7(&lit_op_7);


    StatementDefinition st_1(&var_type_vector_int, &token_id, &l1);
    StatementDefinition st_2(&var_type_vector_int, &token_id, &l2);
    StatementDefinition st_3(&var_type_vector_int, &token_id, &l3);
    StatementDefinition st_4(&var_type_vector_int, &token_id, &l4);
    StatementDefinition st_5(&var_type_vector_int, &token_id, &l5);
    StatementDefinition st_6(&var_type_vector_str, &token_id, &l6);
    StatementDefinition st_7(&var_type_vector_vec, &token_id, &l7);
    //
    StatementList lst_1({&st_1});
    StatementList lst_2({&st_2});
    StatementList lst_3({&st_3});
    StatementList lst_4({&st_4});
    StatementList lst_5({&st_5});
    StatementList lst_6({&st_6});
    StatementList lst_7({&st_7});

    RunTestsV2({
        {t1, &lst_1},
        {t2, &lst_2},
        {t3, &lst_3},
        {t4, &lst_4},
        {t5, &lst_5},
        {t6, &lst_6},
        {t7, &lst_7},
    });
}

void Test_Statement_Assign_Definition_Simple_OneParam()
{
    // throw std::runtime_error(" DUMMY");
    // vector<pair<string, string>> tests = {
    //     {"Buffer b_1 = Buffer[];",           "Buffer b_1 = Buffer[]"},
    //     {"Buffer b2 = Buffer[some_var];",        "Buffer b2 = Buffer[some_var]"},
    //     {"Buffer b2 = Buffer[some_var1, some_var2];",        "Buffer b2 = Buffer[some_var1, some_var2]"},
    //     {"Buffer b2 = Buffer[var1, var2,];",        "Buffer b2 = Buffer[var1, var2]"},
    // };
    // RunTests(tests);

    string t1 = "DBBuffer b1 = DBBuffer[];";
    Token id("b1");

    VariableType var_type_buf(new Token("DBBuffer"), {});

    // Buffer[]
    LiteralOneParam lit_op(&var_type_buf, {});
    ExpressionLiteral expr_lit(&lit_op);

    StatementDefinition st(&var_type_buf, &id, &expr_lit);
    StatementList lst({&st});

    RunTestsV2({
        {t1, &lst},
    });

    LiteralInteger int_lit(new Token("100"));
    LiteralFloat float_lit(new Token("20.5"));
    LiteralString string_lit(new Token("some string"));
    ExpressionLiteral int_expr(&int_lit);
    ExpressionLiteral float_expr(&float_lit);
    ExpressionLiteral string_expr(&string_lit);

    LiteralOneParam dbbuffer_lit_op(&var_type_buf, {&int_expr, &float_expr, &string_expr});

    ExpressionLiteral dbbuffer_expr(&dbbuffer_lit_op);

    dbbuffer_expr.execute();
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
    // RunTests(tests);

    string t1 = "Map(Integer, Integer) m_1 = Map(Integer, Integer)[];";
    string t2 = "Map(Integer, Integer) m_1 = Map(Integer, Integer)[100 : abc, yoyo : 300];";

    VariableType var_type_int(new Token("Integer"), {});
    VariableType var_type_map(new Token("Map"), {&var_type_int, &var_type_int});

    // Map(Integer, Integer)[]
    LiteralTwoParam lit_two_param(&var_type_map, {});
    ExpressionLiteral expr_lit_1(&lit_two_param);

    // Map(Integer, Integer)[100 : abc, yoyo : 300]
    LiteralInteger lit_int_100(new Token("100"));
    LiteralInteger lit_int_300(new Token("300"));
    ExpressionLiteral expr_lit_int_100(&lit_int_100);
    ExpressionLiteral expr_lit_int_300(&lit_int_300);
    ExpressionId id_expr_abc(new Token("abc"));
    ExpressionId id_expr_100(new Token("100"));
    ExpressionId id_expr_yoyo(new Token("yoyo"));
    LiteralTwoParam lit_two_param_w_params(&var_type_map, {
        {&expr_lit_int_100, &id_expr_abc},
        {&id_expr_yoyo, &expr_lit_int_300},
    });
    ExpressionLiteral expr_lit_2(&lit_two_param_w_params);

    StatementDefinition st_1(&var_type_map, new Token("m_1"), &expr_lit_1);
    StatementDefinition st_2(&var_type_map, new Token("m_1"), &expr_lit_2);
    StatementList lst_1({&st_1});
    StatementList lst_2({&st_2});

    RunTestsV2({
        {t1, &lst_1},
        {t2, &lst_2},
    });
}

void Test_StatementExpression_Simple()
{
    // vector<pair<string, string>> tests = {
    //     {"i_1 = 2;",                 "i_1 = 2"},
    //     {"str_1 = \"some string\";", "str_1 = \"some string\""},
    //     {"f_1 = 2.0;",               "f_1 = 2.0"},
    //     {"i_2 = a_1;",               "i_2 = a_1"},
    // };
    // RunTests(tests);

    string t1 = "i_1 = 2;";
    string t2 = "i_1 = \"some string\";";
    string t3 = "i_1 = 2.0;";
    string t4 = "i_1 = a_1;";

    ExpressionId expr_id(new Token("i_1"));

    LiteralInteger lit_int(new Token("2"));
    ExpressionLiteral expr_lit_int(&lit_int);
    ExpressionAssign expr_asgn_1(&expr_id, &expr_lit_int);

    LiteralString lit_str(new Token("\"some string\""));
    ExpressionLiteral expr_lit_str(&lit_str);
    ExpressionAssign expr_asgn_2(&expr_id, &expr_lit_str);

    LiteralFloat lit_float(new Token("2.0"));
    ExpressionLiteral expr_lit_float(&lit_float);
    ExpressionAssign expr_asgn_3(&expr_id, &expr_lit_float);

    ExpressionId expr_id_val(new Token("a_1"));
    ExpressionAssign expr_asgn_4(&expr_id, &expr_id_val);

    StatementExpression st_int(&expr_asgn_1);
    StatementExpression st_str(&expr_asgn_2);
    StatementExpression st_float(&expr_asgn_3);
    StatementExpression st_id_val(&expr_asgn_4);

    StatementList lst_int({&st_int});
    StatementList lst_str({&st_str});
    StatementList lst_float({&st_float});
    StatementList lst_id_val({&st_id_val});

    RunTestsV2({
        {t1, &lst_int},
        {t2, &lst_str},
        {t3, &lst_float},
        {t4, &lst_id_val},
    });

}
void Test_StatementExpression_OneParam()
{
    // throw std::runtime_error(" DUMMY");
    // vector<pair<string, string>> tests = {
    //     {"vc_1 = Vector(Integer)[100, i_2];",                "vc_1 = Vector(Integer)[100, i_2]"},
    //     {"vc_1 = Vector(String)[\"some string\", str_var];", "vc_1 = Vector(String)[\"some string\", str_var]"},
    //     {"vc_1 = Vector(Float)[100.5, i_2];",                "vc_1 = Vector(Float)[100.5, i_2]"},
    // };
    // RunTests(tests);

    string t1 = "vc_1 = Vector(Integer)[100, i_2];";

    ExpressionId expr_left_id(new Token("vc_1"));

    VariableType var_type_int(new Token("Integer"), {});
    VariableType var_type_vector(new Token("Vector"), {&var_type_int});

    // Vector(Integer)[100, i_2];
    LiteralInteger lit_int(new Token("100"));
    ExpressionLiteral expr_lit_100(&lit_int);
    ExpressionId expr_id(new Token("i_2"));
    LiteralOneParam lit_op(&var_type_vector, {&expr_lit_100, &expr_id});
    ExpressionLiteral expr_lit_op(&lit_op);

    ExpressionAssign expr_assign(&expr_left_id, &expr_lit_op);

    StatementExpression st(&expr_assign);
    StatementList lst({&st});

    RunTestsV2({
        {t1, &lst},
    });


}
void Test_StatementExpression_TwoParam()
{
    // throw std::runtime_error(" DUMMY");
    vector<pair<string, string>> tests = {
        {"m_1 = Map(Integer, Integer)[i_1: i_1, 100: i_2, abc : vec.at(0)];",     "m_1 = Map(Integer, Integer)[i_1 : i_1, 100 : i_2, abc : vec.at(0)]"},
        {"m_1 = Map(Integer, Integer)[i_1: i_1, 100: i_2, abc : 500];",     "m_1 = Map(Integer, Integer)[i_1 : i_1, 100 : i_2, abc : 500]"},
        {"m_1 = Map(Integer, Map(Integer, String))[i_1: mp1, 100: i_2];",   "m_1 = Map(Integer, Map(Integer, String))[i_1 : mp1, 100 : i_2]"},
    };
    // RunTests(tests);
    string t1 = "m_1 = Map(Integer, Integer)[i_1: a_1, 100: i_2, abc : vec.at(0)];";

    VariableType var_type_int(new Token("Integer"), {});
    VariableType var_type_map(new Token("Map"), {&var_type_int, &var_type_int});

    ExpressionId i_1_arg_key(new Token("i_1"));
    ExpressionId abc_arg_key(new Token("abc"));
    ExpressionId i_2_arg_val(new Token("i_2"));
    ExpressionId a_1_arg_val(new Token("a_1"));
    ExpressionLiteral lit_100_arg_key(new LiteralInteger(new Token("100")));

    // vec.at
    ExpressionDot vec_at_expr_dot(new Token("at"), new ExpressionId(new Token("vec")));

    // (0)
    LiteralInteger int_0_lit(new Token("0"));
    ExpressionLiteral int_0_expr_lit(&int_0_lit);
    ExpressionCallOrdered arguments_expr_0({&int_0_expr_lit});
    ExpressionCall vec_at_expr_call(&vec_at_expr_dot, &arguments_expr_0);

    // Map(Integer, Integer)[i_1: a_1, 100: i_2, abc : vec.at(0)]
    LiteralTwoParam lit_2param(&var_type_map, {
        {&i_1_arg_key, &a_1_arg_val},
        {&lit_100_arg_key, &i_2_arg_val},
        {&abc_arg_key, &vec_at_expr_call},
    });
    ExpressionLiteral lit_expr(&lit_2param);
    ExpressionId id_expr(new Token("m_1"));

    ExpressionAssign expr_assign(&id_expr, &lit_expr);

    StatementExpression st(&expr_assign);

    StatementList lst({&st});

    RunTestsV2({
        {t1, &lst}
    });
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
    string t5 = "id.some(10);";
    string t6 = "id.some(vec.size);";

    Token token_id("id");
    Token token_method("some");
    Token token_arg1("arg1");
    Token token_arg2("arg2");
    Token token_arg3("arg3");

    // id.some
    ExpressionId expr_id(&token_id);
    ExpressionDot expr_dot(&token_method, &expr_id);

    // id.some()
    ExpressionCallOrdered expr_co_1;
    ExpressionCall expr_call_1(&expr_dot, &expr_co_1);

    // id.some(arg1)
    ExpressionId expr_arg_id_1(&token_arg1);
    ExpressionCallOrdered expr_co_2({
        &expr_arg_id_1
    });
    ExpressionCall expr_call_2(&expr_dot, &expr_co_2);

    // id.some(arg1, arg2)
    ExpressionId expr_arg_id_2(&token_arg2);
    ExpressionCallOrdered expr_co_3({
        &expr_arg_id_1,
        &expr_arg_id_2
    });
    ExpressionCall expr_call_3(&expr_dot, &expr_co_3);

    // id.some(arg1, arg2, arg3)
    ExpressionId expr_arg_id_3(&token_arg3);
    ExpressionCallOrdered expr_co_4({
        &expr_arg_id_1,
        &expr_arg_id_2,
        &expr_arg_id_3
    });
    ExpressionCall expr_call_4(&expr_dot, &expr_co_4);
    // id.some(10)
    LiteralInteger lit_int(new Token("10"));
    ExpressionLiteral lit_expr(&lit_int);
    ExpressionCallOrdered expr_co_5({&lit_expr});
    ExpressionCall expr_call_5(&expr_dot, &expr_co_5);

    // id.some(vec.size)
    ExpressionId vec_expr_id(new Token("vec"));
    ExpressionDot vec_expr_dot(new Token("size"), &vec_expr_id);
    ExpressionCallOrdered expr_co_6({&vec_expr_dot});
    ExpressionCall expr_call_6(&expr_dot, &expr_co_6);

    StatementExpression st_expr_1(&expr_call_1);
    StatementExpression st_expr_2(&expr_call_2);
    StatementExpression st_expr_3(&expr_call_3);
    StatementExpression st_expr_4(&expr_call_4);
    StatementExpression st_expr_5(&expr_call_5);
    StatementExpression st_expr_6(&expr_call_6);

    StatementList st_lst_1({&st_expr_1});
    StatementList st_lst_2({&st_expr_2});
    StatementList st_lst_3({&st_expr_3});
    StatementList st_lst_4({&st_expr_4});
    StatementList st_lst_5({&st_expr_5});
    StatementList st_lst_6({&st_expr_6});

    RunTestsV2({
        {t1, &st_lst_1},
        {t2, &st_lst_2},
        {t3, &st_lst_3},
        {t4, &st_lst_4},
        {t5, &st_lst_5},
        {t6, &st_lst_6},
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
    string t3 = "m_1.insert(first = i_1, second = 100500, third = \"Some String\",);";

    Token token_id("m_1");
    Token token_method("insert");

    Token token_key_1("first");
    Token token_val_1("i_1");
    Token token_key_2("second");
    Token token_val_2("100500");
    Token token_key_3("third");
    Token token_val_3("\"Some String\"");

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

void Test_StatementExpression_Complex_CallOrdered()
{
    // vector<pair<string, string>> tests = {
    //     {"id.some(a_1.method());",                  "id.some(a_1.method())"},
    //     {"id.some(a_1.method(100));",                  "id.some(a_1.method(100))"},
    //     {"id.some(a_1.method(100), abc);",                  "id.some(a_1.method(100), abc)"},
    //     {"i_1 = id.some(a_1.method());",     "i_1 = id.some(a_1.method())"},
    //     {"i_1 = id.some(arg1, a_1.method());",     "i_1 = id.some(arg1, a_1.method())"},
    // };
    // RunTests(tests);

    string t1 = "id.some(a_1.method());";
    string t2 = "id.some(a_1.method(100));";
    string t3 = "id.some(a_1.method(100), arg);";
    string t4 = "i_1 = id.some(a_1.method());";
    // string t5 = "i_1 = id.some(a_1.method(id_2[100]));";
    // string t6 = "i_1 = id.some(arg, a_1.method());";
    string t7 = "id.some(id_2[0]);";

    Token tok_method_some("some");
    Token tok_method_method("method");
    ExpressionId id_expr(new Token("id"));
    ExpressionId a_1_expr(new Token("a_1"));
    ExpressionId id_2_expr(new Token("id_2"));

    // id.some
    ExpressionDot expr_dot(&tok_method_some, &id_expr);
    // id.some()
    ExpressionCallOrdered expr_co_1, expr_co_2, expr_co_3, expr_co_4, expr_co_7;//, expr_co_5;
    ExpressionCall expr_call_1(&expr_dot, &expr_co_1);
    ExpressionCall expr_call_2(&expr_dot, &expr_co_2);
    ExpressionCall expr_call_3(&expr_dot, &expr_co_3);
    ExpressionCall expr_call_4(&expr_dot, &expr_co_4);
    // ExpressionCall expr_call_5(&expr_dot, &expr_co_5);
    ExpressionCall expr_call_7(&expr_dot, &expr_co_7);

    // a_1.method()
    ExpressionDot a_1_expr_dot_inner(&tok_method_method, &a_1_expr);

    ExpressionCallOrdered expr_co_inner_1;
    ExpressionCallOrdered expr_co_inner_2;
    ExpressionCallOrdered expr_co_inner_3;
    ExpressionCallOrdered expr_co_inner_4;
    // ExpressionCallOrdered expr_co_inner_5;
    ExpressionCall expr_call_inner_1(&a_1_expr_dot_inner, &expr_co_inner_1);
    ExpressionCall expr_call_inner_2(&a_1_expr_dot_inner, &expr_co_inner_2);
    ExpressionCall expr_call_inner_3(&a_1_expr_dot_inner, &expr_co_inner_3);
    ExpressionCall expr_call_inner_4(&a_1_expr_dot_inner, &expr_co_inner_4);
    // ExpressionCall expr_call_inner_5(&a_1_expr_dot_inner, &expr_co_inner_5);


    // id.some(a_1.method())
    expr_co_1.addArg(&expr_call_inner_1);


    // id.some(a_1.method(100))
    LiteralInteger lit_int_100(new Token("100"));
    ExpressionLiteral lit_int_100_expr(&lit_int_100);
    expr_co_inner_2.addArg(&lit_int_100_expr);
    expr_co_2.addArg(&expr_call_inner_2);

    // id.some(a_1.method(100), abc)
    expr_co_inner_3.addArg(&lit_int_100_expr);
    expr_co_3.addArg(&expr_call_inner_3);
    ExpressionId arg_expr_id(new Token("arg"));
    expr_co_3.addArg(&arg_expr_id);

    // i_1 = id.some(a_1.method());
    ExpressionId i_1_expr(new Token("i_1"));
    expr_co_4.addArg(&expr_call_inner_4);
    ExpressionAssign expr_assign_4(&i_1_expr, &expr_call_4);

    // id.some(arg1, a_1.method())
    // expr_co_5.addArg(&expr_call_inner_5);

    // ExpressionId expr_arg_id_1(&token_arg1);
    // ExpressionCallOrdered expr_co_2({
    //     &expr_arg_id_1
    // });
    // ExpressionCall expr_call_2(&expr_dot, &expr_co_2);
    //
    // ExpressionId id_expr(new Token("i_1"));

    // id.some(id_2[0])
    LiteralInteger lit_int(new Token("0"));
    ExpressionLiteral lit_int_expr(&lit_int);
    ExpressionAt expr_at(&id_2_expr, &lit_int_expr);
    expr_co_7.addArg(&expr_at);

    StatementExpression st_1(&expr_call_1);
    StatementExpression st_2(&expr_call_2);
    StatementExpression st_3(&expr_call_3);
    StatementExpression st_4(&expr_assign_4);
    StatementExpression st_7(&expr_call_7);

    StatementList lst_1({&st_1});
    StatementList lst_2({&st_2});
    StatementList lst_3({&st_3});
    StatementList lst_4({&st_4});
    StatementList lst_7({&st_7});

    RunTestsV2({
        {t1, &lst_1},
        {t2, &lst_2},
        {t3, &lst_3},
        {t4, &lst_4},
        {t7, &lst_7},
    });
}

void Test_StatementExpression_Complex_CallOrdered_WithType()
{
    string t1 = "id.some(Integer);";

    VariableType var_type_int(new Token("Integer"), {});
    ExpressionId id_expr(new Token("id"));
    ExpressionDot id_some_expr_dot(new Token("some"), &id_expr);

    ExpressionType type_int_expr(&var_type_int);
    ExpressionCallOrdered arg_int({&type_int_expr});
    ExpressionCall expr_call(&id_some_expr_dot, &arg_int);

    StatementExpression st(&expr_call);
    StatementList lst({&st});

    RunTestsV2({
        {t1, &lst},
    });
}

void Test_StatementExpression_Complex_CallNamed_WithType()
{
    string t1 = "id.some(key = Integer);";

    VariableType var_type_int(new Token("Integer"), {});
    ExpressionId id_expr(new Token("id"));
    ExpressionDot id_some_expr_dot(new Token("some"), &id_expr);

    ExpressionType type_int_expr(&var_type_int);
    ExpressionCallNamed arg_int({
        {new Token("key"), &type_int_expr},
    });
    ExpressionCall expr_call(&id_some_expr_dot, &arg_int);

    StatementExpression st(&expr_call);
    StatementList lst({&st});

    RunTestsV2({
        {t1, &lst},
    });
}

void Test_StatementExpression_Complex_CallNamed()
{
    // throw std::runtime_error("DUMMY");
    vector<pair<string, string>> tests = {
        {"i_1 = id.some(key = another.method());",     "i_1 = id.some(key = another.method())"},
        {"i_1 = id.some(key = another.method(abc, 100), key2 = 500);",     "i_1 = id.some(key = another.method(abc, 100), key2 = 500)"},
        {"i_1 = id.some(key = another.method(), key2 = 9999);",     "i_1 = id.some(key = another.method(), key2 = 9999)"},
        {"i_1 = id.some(key = another.method(abc = 100), key2 = 500);",     "i_1 = id.some(key = another.method(abc = 100), key2 = 500)"},
    };
    // RunTests(tests);
    string t1 = "i_1 = id.some(key = another.method());";
    string t2 = "i_1 = id.some(key = another.method(abc, 100), key2 = 500);";

    ExpressionId i_1_expr(new Token("i_1"));
    ExpressionId id_expr(new Token("id"));
    ExpressionId another_expr(new Token("another"));
    Token some_token("some");
    Token method_token("method");
    Token arg_key_token("key");
    Token arg_key2_token("key2");

    // id.some
    ExpressionDot expr_dot(&some_token, &id_expr);

    // another.method
    ExpressionDot arg_expr_dot(&method_token, &another_expr);
    ExpressionCallOrdered arg_co_empty;
    // another.method()
    ExpressionCall arg_func_expr_1(&arg_expr_dot, &arg_co_empty);

    ExpressionCallNamed expr_cn_1({
        {&arg_key_token, &arg_func_expr_1},
    });
    ExpressionCall expr_call_1(&expr_dot, &expr_cn_1);

    // another.method(abc, 100)
    ExpressionId abc_arg_inner_expr(new Token("abc"));
    ExpressionLiteral arg_int_100_expr(new LiteralInteger(new Token("100")));
    ExpressionCallOrdered arg_co_another({&abc_arg_inner_expr, &arg_int_100_expr});
    ExpressionCall arg_another_func_expr(&arg_expr_dot, &arg_co_another);

    ExpressionLiteral arg_int_500_expr(new LiteralInteger(new Token("500")));
    ExpressionCallNamed expr_cn_2({
        {&arg_key_token, &arg_another_func_expr},
        {&arg_key2_token, &arg_int_500_expr},
    });
    // another.method()
    ExpressionCall expr_call_2(&expr_dot, &expr_cn_2);


    ExpressionAssign expr_assign_1(&i_1_expr, &expr_call_1);
    ExpressionAssign expr_assign_2(&i_1_expr, &expr_call_2);

    StatementExpression st_1(&expr_assign_1);
    StatementExpression st_2(&expr_assign_2);
    // StatementExpression st_3(&expr_assign_3);
    // StatementExpression st_4(&expr_assign_4);

    StatementList lst_1({&st_1});
    StatementList lst_2({&st_2});
    // StatementList lst_3({&st_3});
    // StatementList lst_4({&st_4});

    RunTestsV2({
        {t1, &lst_1},
        {t2, &lst_2},
        // {t3, &lst_3},
        // {t4, &lst_4},
    });
}

void Test_StatementDefinition_Types()
{
    // vector<pair<string, string>> tests = {
    //     {"Type t = Integer;",           "Type t = Integer"},
    //     {"Type t = Vector(String);",    "Type t = Vector(String)"},
    //     {"Type t = Map(Integer, Map(String, Float));",    "Type t = Map(Integer, Map(String, Float))"},
    // };
    // RunTests(tests);

    string t1 = "Type t = Integer;";
    string t2 = "Type t = Vector(Integer);";

    VariableType var_type_type(new Token("Type"), {});
    VariableType var_type_int(new Token("Integer"), {});
    VariableType var_type_vec(new Token("Vector"), {&var_type_int});

    ExpressionType expr_type(&var_type_int);
    ExpressionType expr_type_vector(&var_type_vec);

    StatementDefinition st_1(&var_type_type, new Token("t"), &expr_type);
    StatementDefinition st_2(&var_type_type, new Token("t"), &expr_type_vector);
    StatementList lst_1({&st_1});
    StatementList lst_2({&st_2});

    RunTestsV2({
        {t1, &lst_1},
        {t2, &lst_2},
    });
}

void Test_StatementExpression_Types()
{
    // vector<pair<string, string>> tests = {
    //     {"t = Integer;",           "t = Integer"},
    //     {"t = Vector(String);",    "t = Vector(String)"},
    //     {"t = Map(Integer, Map(String, Float));",    "t = Map(Integer, Map(String, Float))"},
    // };
    // RunTests(tests);

    string t1 = "t = Integer;";
    string t2 = "t = Vector(Integer);";

    VariableType var_type_int(new Token("Integer"), {});
    VariableType var_type_vec(new Token("Vector"), {&var_type_int});

    ExpressionType expr_type(&var_type_int);
    ExpressionType expr_type_vector(&var_type_vec);

    ExpressionId expr_id(new Token("t"));
    ExpressionAssign expr_assign_1(&expr_id, &expr_type);
    ExpressionAssign expr_assign_2(&expr_id, &expr_type_vector);

    StatementExpression st_1(&expr_assign_1);
    StatementExpression st_2(&expr_assign_2);
    StatementList lst_1({&st_1});
    StatementList lst_2({&st_2});

    RunTestsV2({
        {t1, &lst_1},
        {t2, &lst_2},
    });
}

void Test_StatementExpression_At()
{
    // throw std::runtime_error(" DUMMY");
    // vector<pair<string, string>> tests = {
    //     {"id[10];",    "id[10]"},
    //     {"id[key];",    "id[key]"},
    //     {"id[vec.at(0)];", "id[vec.at(0)]"},
    //     {"id.some[key];", "id.some[key]"},
    //     {"id.some()[key];", "id.some()[key]"},
    //     {"id.some(abc)[key];", "id.some(abc)[key]"},
    //     {"id.some(abc = val)[key];", "id.some(abc = val)[key]"},
    // };
    // RunTests(tests);

    string t1 = "id[10];";
    string t2 = "id[key];";
    string t3 = "id[vec.at(0)];";
    string t4 = "id.some[key];";
    string t5 = "id.some()[key];";
    string t6 = "id.some(arg)[key];";
    // string t7 = "id.some(arg = val)[key];";

    ExpressionId id_expr(new Token("id"));

    // id[10]
    LiteralInteger lit_10_int(new Token("10"));
    ExpressionLiteral lit_10_expr(&lit_10_int);
    ExpressionAt expr_at_1(&id_expr, &lit_10_expr);

    // vec.at(0)
    ExpressionId vec_expr(new Token("vec"));
    ExpressionDot expr_dot_at(new Token("at"), &vec_expr);
    LiteralInteger lit_0_int(new Token("0"));
    ExpressionLiteral lit_0_expr(&lit_0_int);
    ExpressionCallOrdered expr_co({&lit_0_expr});
    ExpressionCall expr_call(&expr_dot_at, {&expr_co});

    // key
    ExpressionId key_expr(new Token("key"));
    // id[key]
    ExpressionAt expr_at_2(&id_expr, &key_expr);

    // id[vec.at(0)]
    ExpressionAt expr_at_3(&id_expr, &expr_call);

    // id.some()[key]
    ExpressionDot expr_dot_some(new Token("some"), &id_expr);
    ExpressionAt expr_at_4(&expr_dot_some, &key_expr);

    // id.some()[key];
    ExpressionCall expr_call_rb(&expr_dot_some, {new ExpressionCallOrdered});
    ExpressionAt expr_at_5(&expr_call_rb, &key_expr);

    // id.some(arg)[key];
    ExpressionId ei_arg(new Token("arg"));
    ExpressionCall expr_call_rb_w_arg(&expr_dot_some, {new ExpressionCallOrdered({&ei_arg})});
    ExpressionAt expr_at_6(&expr_call_rb_w_arg, &key_expr);

    StatementExpression st_1(&expr_at_1);
    StatementExpression st_2(&expr_at_2);
    StatementExpression st_3(&expr_at_3);
    StatementExpression st_4(&expr_at_4);
    StatementExpression st_5(&expr_at_5);
    StatementExpression st_6(&expr_at_6);
    StatementList lst_1({&st_1});
    StatementList lst_2({&st_2});
    StatementList lst_3({&st_3});
    StatementList lst_4({&st_4});
    StatementList lst_5({&st_5});
    StatementList lst_6({&st_6});

    RunTestsV2({
        {t1, &lst_1},
        {t2, &lst_2},
        {t3, &lst_3},
        {t4, &lst_4},
        {t5, &lst_5},
        {t6, &lst_6},
    });
}

void Test_StatementExpression_Equal()
{
    // throw std::runtime_error(" DUMMY");
    vector<pair<string, string>> tests = {
        {"a == b;",                "a == b"},
        {"a == 10;",                "a == 10"},
        {"a == \"string\";",                "a == \"string\""},
        {"vc_1.type() == Vector(Integer);", "vc_1.type() == Vector(Integer)"},
    };

    string t1 = "a == b;";
    string t2 = "a == 10;";
    string t3 = "a == \"string\";";
    string t4 = "vc_1.type() == Vector(Integer);";
    // RunTests(tests);
    ExpressionId id_expr(new Token("a"));

    ExpressionId b_expr(new Token("b"));
    ExpressionEqual expr_equal_1(&id_expr, &b_expr);

    LiteralInteger lit_int(new Token("10"));
    ExpressionEqual expr_equal_2(&id_expr, new ExpressionLiteral(&lit_int));

    LiteralString lit_string(new Token("\"string\""));
    ExpressionEqual expr_equal_3(&id_expr, new ExpressionLiteral(&lit_string));

    ExpressionId expr_vc_1(new Token("vc_1"));
    ExpressionDot expr_dot(new Token("type"), &expr_vc_1);

    ExpressionCallOrdered expr_co;
    ExpressionCall expr_call(&expr_dot, &expr_co);

    VariableType var_type_int(new Token("Integer"), {});
    VariableType var_type_vector(new Token("Vector"), {&var_type_int});

    ExpressionEqual expr_equal_4(&expr_call, new ExpressionType(&var_type_vector));

    StatementExpression st_1(&expr_equal_1);
    StatementExpression st_2(&expr_equal_2);
    StatementExpression st_3(&expr_equal_3);
    StatementExpression st_4(&expr_equal_4);
    StatementList lst_1({&st_1});
    StatementList lst_2({&st_2});
    StatementList lst_3({&st_3});
    StatementList lst_4({&st_4});

    RunTestsV2({
        {t1, &lst_1},
        {t2, &lst_2},
        {t3, &lst_3},
        {t4, &lst_4},
    });
}

void Test_StatementList()
{
    // throw std::runtime_error(" DUMMY");
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
    // RunTests(tests);
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
    tr.RunTest(Test_StatementExpression_Complex_CallOrdered, "Parser: Test_StatementExpression_Complex_CallOrdered");
    tr.RunTest(Test_StatementExpression_Complex_CallOrdered_WithType, "Parser: Test_StatementExpression_Complex_CallOrdered_WithType");
    tr.RunTest(Test_StatementExpression_Complex_CallNamed, "Parser: Test_StatementExpression_Complex_CallNamed");
    tr.RunTest(Test_StatementExpression_Complex_CallNamed_WithType, "Parser: Test_StatementExpression_Complex_CallNamed_WithType");
    tr.RunTest(Test_StatementDefinition_Types, "Parser: Test_StatementDefinition_Types");
    tr.RunTest(Test_StatementExpression_Types, "Parser: Test_StatementExpression_Types");
    tr.RunTest(Test_StatementExpression_At, "Parser: Test_StatementExpression_At");
    tr.RunTest(Test_StatementExpression_Equal, "Parser: Test_StatementExpression_Equal");
    tr.RunTest(Test_Statement_Assign_Definition_Simple_OneParam, "Parser: Test_Statement_Assign_Definition_Simple_OneParam");
    // tr.RunTest(Test_StatementList, "Parser: Test_StatementList");

}
