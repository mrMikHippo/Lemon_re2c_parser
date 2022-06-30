#pragma once

#include <string>
#include <vector>
#include <memory>

// #include "wrapper.h"
#include "variable_type.h"
#include "expression.h"

#include <iostream>

class Statement : public Token
{
public:
	virtual ~Statement() = default;
	virtual void execute() { std::cout << "Statement execute" << std::endl; }
	virtual std::string toString() const = 0;
	virtual std::string print(int level = 0) const override { return "Statement\n"; }
};

//Integer a = 100500
class StatementDefinition : public Statement
{
public:
	StatementDefinition(VariableType* type_, Token* id_, Expression* value_ = nullptr);
	~StatementDefinition();

	void execute() override {
		if (value)
			value->execute();
	}

	std::string toString() const override;
	std::string print(int level = 0) const override {
		std::string res = std::string(level, '\t') + "StatementDefinition(\"" + this->toString() + "\")\n";
		res += type->print(level+1);
		res += std::string(level+1, '\t') + "ID(\"" + id->value + "\")\n";
		if (value)
			res += value->print(level+1);
		return res;
	}

private:
    VariableType* type;
    Token* id;
    Expression* value;
};

// a = 100
class StatementExpression : public Statement
{
public:
	StatementExpression(Expression* expr_);

	void execute() override {
		expr->execute();
	}

	std::string toString() const override;
	std::string print(int level = 0) const override {
		std::string res = std::string(level, '\t') + "StatementExpression(\"" + this->toString() + "\")\n";
		res += expr->print(level+1);
		return res;
	}

private:
    Expression* expr;
};

class StatementList : public Statement
{
public:
	StatementList();
	StatementList(std::vector<Statement*> statements_);

	void addStatement(Statement* statement_);
	std::vector<Statement*> getStatements() const;

	void execute() override {
		for (const auto& st : statements) {
			st->execute();
		}
	}

	std::string toString() const override;
	std::string print(int level = 0) const override {
		std::string res = std::string(level, '\t') + "StatementList\n";
		for (const auto& st : statements)
            res += st->print(level+1);
		return res;
	}

private:
    std::vector<Statement*> statements;
};
