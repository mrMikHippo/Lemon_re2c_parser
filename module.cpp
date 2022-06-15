#include <iostream>

#include "module.h"
#include "AST/global_types_map.h"
#include "lexer/lexer.h"

using namespace std;

Module::Module()
{
	// cout << "Registered types = [" << endl;
	// for (const auto& t : GlobalTypeMap::getInstance().types)
		// cout << "\t" << t << endl;
	// cout << "]" << endl;
}

Module::~Module()
{
}

void Module::run(const string& source)
{
	Lexer lex(this);
	lex.scan(source);

	// bool first = true;
	// cout << "Tokens: [";
	// for (auto& el : tokens) {
	// 	if (first)
	// 		first = false;
	// 	else
	// 		cout << ",";
	// 	cout << " '" << el->value << "'";
	// }
	// cout << " ]" << endl;
}

void Module::setRootNode(Statement* node)
{
	root = node;
}

Statement* Module::getRootNode() const
{
	return root;
}
