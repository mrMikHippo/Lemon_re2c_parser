#include <iostream>
#include <vector>
#include <string>

#include "tests/test_all.h"
#include "module.h"

using namespace std;

int main() {

	TestAll();

	bool exit = false;
	bool print = false;
	int tokenID;
	string cmd;

	Module module;

	while (!exit) {
		cout << "> ";
		getline(cin, cmd);

		if (cmd == "quit")
			break;
		else if (cmd.empty())
			continue;
		else {
			try {
				module.run(cmd);
			} catch(std::exception& ex) {
				cerr << ex.what() << endl;
			}
		}
	}

	cout << "Finished" << endl;
	return 0;
}
