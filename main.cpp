#include <iostream>

#include "AST/literal.h"
#include "AST/variable_type.h"
#include <string>
#include <vector>
#include <cassert>

using namespace std;

template<class T>
void test(T cont, const string& match) {
	assert(cont->toString() == match);
}

int main() {

	cout << "Test for LiteralInteger: ";
	LiteralInteger* lint = new LiteralInteger({"10"});
	cout << lint->toString() << endl;
	delete lint;


	cout << "Test for VariableType: ";
	VariableType v_type({"Vector"});
	VariableType v_sub_type({"Integer"});
	v_type.addSubType(&v_sub_type);
	cout << v_type.toString() << endl;

	cout << "Test for ExpressionId: ";
	ExpressionId* expr1 = new ExpressionId({"100500"});
	ExpressionId* expr2 = new ExpressionId({"id"});
	cout << "[" << expr1->toString() << " " << expr2->toString() << "]" << endl;

	vector<Expression*> v_expressions = {expr1, expr2};

	cout << "Test for LiteralVector: ";
	LiteralVector* lvec = new LiteralVector(&v_type, v_expressions);
	cout << lvec->toString() << endl;
	
	delete expr1;
	delete expr2;
	delete lvec;

	return 0;
}