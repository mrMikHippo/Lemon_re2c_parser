#pragma once

#include <vector>
#include <string>


class GlobalTypeMap {
public:
	static GlobalTypeMap& getInstance() {
		static GlobalTypeMap instance;
		return instance;
	}

	std::vector<std::string> types = {
		"Integer",
		"Float",
		"String",
		"Vector",
		"Map",
		"Type",
	};

	GlobalTypeMap(GlobalTypeMap const&) = delete;
	void operator=(GlobalTypeMap const&) = delete;

private:
	GlobalTypeMap() {}
};

class GlobalLiteralTypeMap {
public:
	static GlobalLiteralTypeMap& getInstance() {
		static GlobalLiteralTypeMap instance;
		return instance;
	}

	std::vector<std::string> types = {
		"Buffer",
		"Mutex"
	};

	GlobalLiteralTypeMap(GlobalLiteralTypeMap const&) = delete;
	void operator=(GlobalLiteralTypeMap const&) = delete;

private:
	GlobalLiteralTypeMap() {}
};
