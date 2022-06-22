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
		"Buffer",
		"Mutex"
	};

	GlobalTypeMap(GlobalTypeMap const&) = delete;
	void operator=(GlobalTypeMap const&) = delete;

private:
	GlobalTypeMap() {}
};
