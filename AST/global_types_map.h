#pragma once

#include <vector>
#include <string>
#include <map>
#include <memory>

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
		"DBBuffer",
		"Mutex"
	};

	GlobalTypeMap(GlobalTypeMap const&) = delete;
	void operator=(GlobalTypeMap const&) = delete;

private:
	GlobalTypeMap() {}
};

class LiteralExecutor;

class GlobalLiteralTypeMap {
public:
	using StorageType = std::map<std::string, std::shared_ptr<LiteralExecutor>>;
	static GlobalLiteralTypeMap& getInstance() {
		static GlobalLiteralTypeMap instance;
		return instance;
	}

	StorageType& getStorage() {
		return types_w_executor;
	}

	void registerExecutor(const std::string& type_name, std::shared_ptr<LiteralExecutor> literal_executor_) {
		types_w_executor.emplace(std::make_pair(type_name, literal_executor_));
	}

	GlobalLiteralTypeMap(GlobalLiteralTypeMap const&) = delete;
	void operator=(GlobalLiteralTypeMap const&) = delete;

private:
	GlobalLiteralTypeMap() {}
	StorageType types_w_executor;
};
