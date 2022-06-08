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

void Module::run(const string& source) {
	// cout << "[Module] Source: " << source << endl;
	Lexer lex(this);
	lex.scan(source);

	bool first = true;
	cout << "Tokens: [";
	for (auto& el : tokens) {
		if (first)
			first = false;
		else
			cout << ",";
		cout << " '" << el->value << "'";
	}
	cout << " ]" << endl;
}

shared_ptr<Token> Module::createToken(const std::string& token_value) {
	shared_ptr<Token> token = make_shared<Token>(Token{token_value});
	// cout << "[Module] Create token: " << token->value << endl;
	return token;
}

uint64_t Module::insertToken(shared_ptr<Token> token) {
	// cout << "[Module] Insert token: " << token->value << ", id=" << tokens.size() << endl;
	tokens.push_back(token);
	return tokens.size() - 1;
}

std::string Module::getTokenValue(uint64_t id) {
	return tokens.at(id)->value;
}

std::shared_ptr<Token> Module::getToken(uint64_t id) {
	return tokens.at(id);
}

void Module::setRootNode(std::shared_ptr<Token> token) {
	root = token;
}
