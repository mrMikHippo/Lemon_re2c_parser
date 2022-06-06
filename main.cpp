#include <iostream>
#include <vector>
#include <string>

#include "tests/test_all.h"
#include "lexer/lexer.h"
#include "AST/global_types_map.h"

using namespace std;


// static void InitGlobalTypesMap() {
// 	GlobalTypeMap::getInstance().types.push_back(string("Integer"));
// 	GlobalTypeMap::getInstance().types.push_back(string("String"));
// 	GlobalTypeMap::getInstance().types.push_back(string("Vector"));
// 	GlobalTypeMap::getInstance().types.push_back(string("Map"));
// }

int main() {

	TestAll();

	bool exit = false;
	bool print = false;
	int tokenID;
	string cmd;

	// InitGlobalTypesMap();

	for (const auto& t : GlobalTypeMap::getInstance().types)
		cout << t << endl;

	while (!exit) {
		cout << "> ";
		getline(cin, cmd);

		if (cmd == "quit")
			break;
		else if (cmd.empty())
			continue;
		else {
			Lexer lexer(cmd.c_str());

			lexer.scan();
		}
	}

	cout << "Finished" << endl;
	return 0;
}