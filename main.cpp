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

		if (cmd == "quit" || cmd == "q")
			break;
		else if (cmd.empty())
			continue;
		else if (cmd == "verbose") {
			module.toggleVerbose();
		} else if (cmd == "help") {
			cout << "quit or q : for quit" << endl;
			cout << "verbose   : toggle parser verbose mode" << endl;
			cout << "[string]  : string to parse" << endl;
		} else {
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
