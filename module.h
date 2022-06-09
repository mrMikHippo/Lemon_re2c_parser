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
	void run(const std::string& source);

	uint64_t insertToken(const Token& token);
	Token getToken(uint64_t id);
	std::string getTokenValue(uint64_t id);

	void setRootNode(Statement* node);

	VariableType* createVariableType(const Token& token, const std::vector<VariableType*> types_);
	uint64_t insertVariableType(VariableType* vtype);
	VariableType* getVariableType(uint64_t id);

	StatementDefinition* createStatementDefinition(VariableType* type, const Token& id, Expression* value = nullptr);
	uint64_t insertStatementDefinition(StatementDefinition* st);
	Statement* getStatement(uint64_t id);

private:
	Statement* root;
	std::vector<Token> tokens;
	std::vector<VariableType*> vtypes;
	std::vector<Statement*> statements;
};
