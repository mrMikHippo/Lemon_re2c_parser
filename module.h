#pragma once

#include <string>
#include <memory>
#include <vector>
#include "AST/token.h"
#include "AST/variable_type.h"
#include "AST/statement.h"

namespace Tools {
	template<typename T, typename... Ts>
	std::unique_ptr<T> make_unique(Ts&&... params) {
		return std::unique_ptr<T>(new T(std::forward<Ts>(params)...));
	}
}

class Module
{
public:
	Module();
	~Module();

	void toggleVerbose();
	void run(const std::string& source);

	void setRootNode(Statement* node);
	Statement* getRootNode() const;

	template<typename T>
	T* getToken(uint64_t _id)
	{
		return static_cast<T*>(tokens.at(_id));
	}

	template<typename T, typename... Args>
	uint64_t createToken(Args&& ... _args)
	{
		tokens.push_back(new T(std::forward<Args>(_args) ...));
		return tokens.size() - 1;
	}

private:
	bool verbose;
	Statement* root;
	std::vector<Token*> tokens;
};
