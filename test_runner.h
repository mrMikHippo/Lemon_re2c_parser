#pragma once

#include <exception>
#include <iostream>
#include <sstream>
#include <string>


template<class T, class U>
void AssertEqual(const T& t, const U& u, const std::string& hint) {
	if (t != u) {
		std::ostringstream os;
		os << "Assertion failed: " << t << " != " << u << " hint: " << hint;
		throw std::runtime_error(os.str());
	}
}

class TestRunner {
public:
	template<class TestFunc>
	void RunTest(TestFunc func, const std::string& name) {
		try {
			func();
			std::cerr << name << " OK" << std::endl;
			++success_count;
		} catch(std::runtime_error &e) {
			++fail_count;
			std::cerr << name << " fail: " << e.what() << std::endl;
		} catch(...) {
			std::cerr << "Unknown error" << std::endl;
		}
	}

	int getTotalCount() { return fail_count + success_count; }
	int getFailCount() { return fail_count; }
	int getSuccessCount() { return success_count; }
private:
	int fail_count = 0;
	int success_count = 0;
};