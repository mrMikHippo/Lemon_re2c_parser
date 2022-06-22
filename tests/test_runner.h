#pragma once

#include <exception>
#include <iostream>
#include <sstream>
#include <string>

const std::string red = "\033[31m";
const std::string green = "\033[32m";
const std::string orange = "\033[33m";
const std::string warn = "";//"\033[33m";
const std::string reset = "\033[0m";

template<class T, class U>
void AssertEqual(const T& t, const U& u, const std::string& hint = "") {
	if (t != u) {
		std::ostringstream os;
		os << " Assertion failed: '" << t << "' != '" << u << "' hint: " << hint;
		throw std::runtime_error(os.str());
	}
}

class TestRunner {
public:
	template<class TestFunc>
	void RunTest(TestFunc func, const std::string& name) {
		try {
			func();
			std::cerr << "[ " << green << "OK" << reset << " ] " << name << std::endl;
			++success_count;
		} catch(std::runtime_error &e) {
			++fail_count;
			std::cerr << "[ " << red << "fail" << reset << " ] " << name << e.what() << std::endl;
		} catch(std::exception& ex) {
			++fail_count;
			std::cerr << "[ " << red << "FAIL" << reset << " ] " << name << ex.what() << std::endl;
		}
	}

	int getTotalCount() { return fail_count + success_count; }
	int getFailCount() { return fail_count; }
	int getSuccessCount() { return success_count; }
private:
	int fail_count = 0;
	int success_count = 0;
};
