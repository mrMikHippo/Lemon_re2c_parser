#pragma once

#include <string>
#include <memory>
#include <vector>
#include "AST/token.h"

class Module
{
public:
	Module();
	void run(const std::string& source);

	std::shared_ptr<Token> createToken(const std::string& token_value);

	uint64_t insertToken(std::shared_ptr<Token> token);

	std::shared_ptr<Token> getToken(uint64_t id);
	std::string getTokenValue(uint64_t id);

	void setRootNode(std::shared_ptr<Token> token);

private:
	std::shared_ptr<Token> root;
	std::vector<std::shared_ptr<Token>> tokens;
};
