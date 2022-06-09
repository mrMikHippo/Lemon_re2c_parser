#pragma once

#include <string>
#include <vector>
#include <memory>

// #include "wrapper.h"
#include "variable_type.h"
#include "expression.h"

class Statement
{
public:
	virtual ~Statement() = default;
	virtual std::string toString() const = 0;
};

//Integer a = 100500
class StatementDefinition : public Statement
{
public:
	StatementDefinition(VariableType* type_, const Token& id_, Expression* value_ = nullptr);
	~StatementDefinition();

	std::string toString() const override;

private:
    VariableType* type;
    Token id;
    Expression* value;
};

class StatementExpression : public Statement
{
public:
	StatementExpression(Expression* expr_);

	std::string toString() const override;

private:
    Expression* expr;
};

class StatementList : public Statement
{
public:
	StatementList(std::vector<Statement*> statements_);

	void addStatement(Statement* statement_);

	std::string toString() const override;

private:
    std::vector<Statement*> statements;
};
