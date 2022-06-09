#include <iostream>

#include "module.h"
#include "AST/global_types_map.h"
#include "lexer/lexer.h"

using namespace std;

Module::Module() {
	cout << "Registered types = [" << endl;
	for (const auto& t : GlobalTypeMap::getInstance().types)
		cout << "\t" << t << endl;
	cout << "]" << endl;
}

Module::~Module() {
	for (auto t : vtypes)
		delete t;
	for (auto st : statements)
		delete st;
}

void Module::run(const string& source) {
	Lexer lex(this);
	lex.scan(source);

	bool first = true;
	cout << "Tokens: [";
	for (auto& el : tokens) {
		if (first)
			first = false;
		else
			cout << ",";
		cout << " '" << el.value << "'";
	}
	cout << " ]" << endl;
}

uint64_t Module::insertToken(const Token& token) {
	tokens.push_back(token);
	return tokens.size() - 1;
}

Token Module::getToken(uint64_t id) {
	cout << "[getToken] id=" << id << ", tokens.size=" << tokens.size() << endl;
	if (id < tokens.size())
		return tokens.at(id);
	return {"None"};
}

void Module::setRootNode(Statement* node) {
	root = node;
}

VariableType* Module::createVariableType(const Token& token, const vector<VariableType*> types_) {
	return new VariableType(token, types_);
}
uint64_t Module::insertVariableType(VariableType* vtype) {
	vtypes.push_back(vtype);
	return vtypes.size() - 1;
}

VariableType* Module::getVariableType(uint64_t id) {
	if (id < vtypes.size())
		return vtypes.at(id);
	return nullptr;
}

StatementDefinition* Module::createStatementDefinition(VariableType* type, const Token& id, Expression* value) {
	return new StatementDefinition(type, id, value);
}

uint64_t Module::insertStatementDefinition(StatementDefinition* st) {
	statements.push_back(st);
	return statements.size() - 1;
}

Statement* Module::getStatement(uint64_t id) {
	if (id < statements.size())
		return statements.at(id);
	return nullptr;
}
