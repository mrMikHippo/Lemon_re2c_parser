#include <iostream>

#include "module.h"
#include "AST/global_types_map.h"
#include "lexer/lexer.h"

using namespace std;

Module::Module() :
	verbose(false), print(false)
{
	// cout << "Registered types = [" << endl;
	// for (const auto& t : GlobalTypeMap::getInstance().types)
		// cout << "\t" << t << endl;
	// cout << "]" << endl;
	cout << "Registered literals:" << endl;
	for (const auto& e : GlobalLiteralTypeMap::getInstance().getStorage())
		cout << "\t[ " << e.first << " ]" << endl;
}

Module::~Module()
{
}

void Module::toggleVerbose()
{
	verbose = !verbose;
	cout << "Verbose set to: " << boolalpha << verbose << endl;
}

void Module::togglePrint()
{
	print = !print;
	cout << "Print tree set to: " << boolalpha << print << endl;
}

void Module::run(const string& source)
{
	Lexer lex(this);
	lex.scan(source, verbose);

	this->printTree();

	root->execute();

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

void Module::printTree()
{
	if (print) {
		cout << "Print tree:" << endl;
		cout << root->print() << endl;
	}
}

// void print(Token* tok, int level = 0)
// {
// 	if (tok) {
// 		cout << "\t"*level << tok->toString();
// 		print(tok, level+1);
// 	}
// }
